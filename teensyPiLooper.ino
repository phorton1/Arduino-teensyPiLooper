// 2025-03-09  rework for compatability with TE3
//
// There are 3 serial ports involved in this scheme.
//
//     SERIAL_PORT_USB = Serial -the main usb serial port on the
//          teensy 3.2, either connected to my windows machine, or not.
//     SERIAL_PORT_RPI = Serial1 - the serial port connected to the rPi
//     SERIAL_PORT_TE  = Serial2 - the serial port connected to the
//          teensyExpression by a 1/8" stereo audio cable
//
// For consistency, this program *should* be modified to leverage off
// of the ctrl-E bracketing for binary file uploads, and the a formalization
// of ctrl-A behavior for fileServer mode.
//
// OLD COMMENTS:
//
// This program has to accomplish the following, all simultaneously.
//
//     - echo the SERIAL_PORT_RPI to SERIAL_PORT_USB for "normal"
//       Looper (rPi) debugging output.  This "normal" echo
//       of REGULAR TEXT (and CR,LF, and ESC) is also used
//
//           (a) by the console.pm program to notice that the
//               pi has rebooted and to upload a kernel.img
//               using the "serial protocol"
//
//           (b) within the kernel upload binary serial protocol"
//               for ACK, NAK, and QUIT ("k","n",and "q") sent from
//               the rPi to the console.pm program. Note that these are
//               still "plain text.
//
//     - echo whatever comes in over the main usb serial port to the rPi
//       This is primarly used in the bootloader to receive a kernel.img.
//       via the (binary) "serial protocol", but can also be used to send
//       text commands to the rPi Looper program from the Windows console.
//
//     - handle ctrl-B key from the main usb serial port and reboot the rPi.
//       We use an idle time check to make sure the ctrl-B was not part of an
//       incoming "serial protocol", and call rebootPi() directly, so that
//       rebooting the pi does require it to be running (i.e. ready).
//
//     - Pass bi-directional "serial commands" (serial midi) between the
//       rPi (Serial1) and teensyExpression (Serial2).  This is done by
//       detecting a low character besides CR/LF/ESCAPE (in either direction).
//       and building a "packet" and sending it on.
//
//     - Because we sensed the TE "command" packets, we can ALSO echo the
//       TE debugging output to the main serial port.  We buffer full lines,
//       and to differentiate the TE from the rPi on the windows receiving end,
//       we prepend "TE: " to those lines of text we send to the windows console.
//       This is a 2nd order debugging thing, to allow me to potentilly debug
//       the TE, via the Looper2 teensy connected to a windows machine, while
//       the TE is actually connected to the iPad.
//
//     - handle "file_server" traffic coming in over the main Serial and
//       send it to Serial2 (the teensyExpression serial port).  This is
//       weird and the ultimate complexity. File_serve_mode is turned on
//       by a ctrl-A and lasts for 10 seconds (as long as there is some
//       Serial traffic coming in).
//
//       The console.pm program sends out the ctrl-A if -rpi and -file_server
//
//       need both -rpi and -file_server !!! CONSOLE 3 -RPI -FILE_SERVER !!!!
//
//
// Note that we DONT use the READY state any of this, though concievably
// we could use it to filter stuff without looking at it so much, I don't
// want to build that dependency into the code at this point.
//
//------------------------------------
// My midi protocol
//------------------------------------
//
// is 4 byte packets that look just like USB midi packets
//
//     CIN           |  MIDI0   |  MIDI1   |  MIDI2   |
//    byte0          |  byte1   |  byte2   |  byte3   |
//-------------------------------------------------------
// cable  |  code    |          |          |          |
// number |  index   |          |          |          |
//        |  number  |          |          |          |
//
// The "cable number" is always zero.
//
// The CIN may be one of the standard values from 0x00 to 0x0F,
// EXCEPT that 0xA and 0xD, which are seldom used MIDI packets
// for "poly-keypress" and "channel pressure" ARE NOT USED.
// Those values are "reserved" for TEXT carriage returns and
// linefeeds, so that this protocol can be sent "within" a
// potential text streem (i.e. debugging output).
//
// Thus, when we see a byte 0x0 thru 0xF (except 0xA and 0xD)
// we presume there is a 4 byte (32 bit) midi packet present,
// which we pass onto the raspberry pi via the main serial
// port.
//
// The protocol is bi-directional.

// So, if we identify a packet, we pass it on to the rPI.
// otherwise, we echo the output to the teensyPi USB port
// and see what happens.  To make debugging output look right,
// we have to buffer, and break on carriage returns,
// and present a "header" before the line oriented degug output

#include <myDebug.h>

#define dbg_fs_data  1
#define dbg_midi_data  0

#define TEENSY_PI_LOOPER_VERSION  "v2.2"

#define SERIAL_PORT_USB     Serial      // the usb serial port on the teensy 3.2
#define SERIAL_PORT_RPI     Serial1     // the serial port connected to the rPi
#define SERIAL_PORT_TE      Serial2     // the serial port with a 1/8" jack to the TE1/2



#define SENSE_RPI_RUN       11      // sense rpi RUN (REBBOOT) pin, HIGH == rpi has voltage
#define SENSE_RPI_READY     4       // sense rpi GPIO25, HIGH == my program has initialized

#define LED_ONBOARD         13      // built in teensy onboard led
#define LED_RPI_RUN         15      // show state of RPI_RUN sense
#define LED_RPI_READY       14      // show state of RPI_READY sense
#define PIN_PI_REBOOT       12      // HIGH == REBOOT (to base of transistor)

#define BLINK_ON_TIME       50
#define BLINK_OFF_TIME      950
    // for the onboard led

#define KEYPRESS_IDLE_TIME  200
#define FILE_SERVER_TIMEOUT 16000

#define MAX_LINE_BUFFER     512


//-------------------
// vars
//-------------------

int blink_state = 0;
elapsedMillis blink_time = 0;

uint8_t rpi_running;
uint8_t rpi_ready;

uint8_t m_key_pressed;
elapsedMillis  m_key_timer;

int line_ptr = 0;
unsigned char line_buffer[MAX_LINE_BUFFER];

bool file_server_mode = 0;
elapsedMillis file_server_time = 0;




//-------------------------------------------------

void rebootPi()
{
    display(0,"teensyPiLooper::rebootPi() called",0);
    digitalWrite(LED_RPI_RUN,0);
    digitalWrite(LED_RPI_READY,0);
    digitalWrite(PIN_PI_REBOOT,1);
    // rpi_running = 0;
    // rpi_ready = 0;
    delay(900);
    digitalWrite(PIN_PI_REBOOT,0);
}




void setup()
{
    SERIAL_PORT_USB.begin(115200);
    delay(5000);
    setColorString(COLOR_CONST_DEFAULT, "\033[94m");       // bright blue
    display(0,"teensyPiLooper " TEENSY_PI_LOOPER_VERSION " started",0);
    SERIAL_PORT_RPI.begin(115200);
    SERIAL_PORT_TE.begin(115200);

    rpi_running = 0;
    rpi_ready = 0;
    m_key_pressed = 0;
    m_key_timer = 0;

    pinMode(SENSE_RPI_RUN,INPUT_PULLUP);
    pinMode(SENSE_RPI_READY,INPUT_PULLDOWN);

    pinMode(LED_ONBOARD,OUTPUT);
    pinMode(LED_RPI_RUN,OUTPUT);
    pinMode(LED_RPI_READY,OUTPUT);
    pinMode(PIN_PI_REBOOT,OUTPUT);

    digitalWrite(PIN_PI_REBOOT,0);
    digitalWrite(LED_RPI_RUN,0);
    digitalWrite(LED_RPI_READY,1);

    display(0,"%s",file_server_mode?"FILE_SERVER_MODE ON":"FILE_SERVER_MODE OFF");

    rebootPi();
        // if both are started at the same time,
        // the teensy supresses the pi bootstrap
}




volatile int fu = 0;


bool handleMidi(int snum, int c)
    // called with snum=0 for SERIAL_PORT_RPI (from rPi) or
    // snum=1 for SERIAL_PORT_TE (from TE).  This is the
    // algorithm I finally came up with ...
{
    // if we see a serial midi start token,
    // gobble up 4 bytes and send them to the
    // other port, checking the port's available() status
    // in a tight loop with incrementing a volatile int for
    // some code to run.

    if (c == 0x0B)     // <= 0xf && c != 0xA && c != 0xD)
    {
        unsigned char buf[4];

        buf[0] = c;
        for (int i=0; i<3; i++)
        {
            if (snum)
            {
                while (!SERIAL_PORT_TE.available())    {fu++;}
                buf[i+1] = SERIAL_PORT_TE.read();
            }
            else
            {
                while (!SERIAL_PORT_RPI.available())    {fu++;}
                buf[i+1] = SERIAL_PORT_RPI.read();
            }
        }

        display(dbg_midi_data,"teensyLooper - serial midi %s (0x%02x 0x%02x 0x%02x 0x%02x) snum=%d",
            snum ? "TE-->RPI" : "RPI-->TE", buf[0],buf[1],buf[2],buf[3],snum);

        if (snum)
            SERIAL_PORT_RPI.write(buf,4);
        else
            SERIAL_PORT_TE.write(buf,4);

        return true;
    }
    return false;
}




void loop()
{
    if (digitalRead(SENSE_RPI_RUN) != rpi_running)
    {
        rpi_running = !rpi_running;
        digitalWrite(LED_RPI_RUN,rpi_running);
        display(0,"rpi %s",(rpi_running ? "RUNNING" : "NOT RUNNING"));
    }
    if (digitalRead(SENSE_RPI_READY) != rpi_ready)
    {
        rpi_ready = !rpi_ready;
        digitalWrite(LED_RPI_READY,rpi_ready);
        display(0,"rpi %s",(rpi_ready ? "READY" : "NOT READY"));
    }


    if (SERIAL_PORT_USB.available())
    {
        int c = SERIAL_PORT_USB.read();

        if (dbg_fs_data==0 && file_server_mode)
        {
            display(0,"teensyPiLoper got USB: chr=0x%02x '%c'",c,c>32?c:' ');
        }

        if (m_key_pressed)
        {
            SERIAL_PORT_USB.write(m_key_pressed);
            SERIAL_PORT_RPI.write(c);
            m_key_pressed = c;
            m_key_timer = 0;
        }
        else if ((c == 1 || c == 2) &&            // ctrlA or ctrlB
            m_key_timer > KEYPRESS_IDLE_TIME)
        {
            m_key_pressed = c;
            m_key_timer = 0;
        }
        else
        {
            // normally we write the incoming bytes to the rPi ..
            // in file_server_mode, we write them to the teenssyExpression
            // over the SERIAL_PORT_TE port

            if (file_server_mode)
            {
                display(dbg_fs_data,"teensyPiLoper sending TE: chr=0x%02x '%c'",c,c>32?c:' ');
                SERIAL_PORT_TE.write(c);
            }
            else
            {
                SERIAL_PORT_RPI.write(c);
            }

            m_key_timer = 0;
        }
    }
    else if (m_key_pressed &&
        m_key_timer > KEYPRESS_IDLE_TIME)
    {
        uint32_t delayed_key = m_key_pressed;
        m_key_timer = 0;
        m_key_pressed = 0;
        if (delayed_key == 1)
        {
            file_server_mode = 1;
            display(0,"%s",file_server_mode?"FILE_SERVER_MODE ON":"FILE_SERVER_MODE OFF");
            file_server_time = 0;
        }
        if (delayed_key == 2)
        {
            rebootPi();
        }
    }


    if (SERIAL_PORT_RPI.available())
    {
        int c = SERIAL_PORT_RPI.read();
        if (!handleMidi(0,c))
            SERIAL_PORT_USB.write(c);
    }


    if (SERIAL_PORT_TE.available())
    {
        int c = SERIAL_PORT_TE.read();
        if (!handleMidi(1,c))
        {
            if (file_server_mode)
            {
                SERIAL_PORT_USB.write(c);
                file_server_time = 0;
            }
            else
            {
                #if 0
                    display(0,"te: 0x%02x",c);
                #else

                    if (c == 0xA || c == 0xD || line_ptr >= MAX_LINE_BUFFER-3)
                    {
                        if (line_ptr)
                        {
                            SERIAL_PORT_USB.print("TE: ");
                            SERIAL_PORT_USB.println((const char *)line_buffer);
                        }
                        line_buffer[0] = 0;
                        line_ptr = 0;
                    }
                    else
                    {
                        line_buffer[line_ptr++] = c;
                        line_buffer[line_ptr] = 0;
                    }
                #endif

            }   // Not file_server_mode (TE alternate debugging/monitor output)
        }   // Not 0x0b (midi message start)
    }   // SERIAL_PORT_TE.available()


    if (file_server_mode && file_server_time > FILE_SERVER_TIMEOUT)
    {
        file_server_mode = 0;
        display(0,"%s",file_server_mode?"FILE_SERVER_MODE ON":"file_server_mode_off");
    }


    if (blink_time > (blink_state ? BLINK_ON_TIME : BLINK_OFF_TIME))
    {
        blink_time = 0;
        blink_state = !blink_state;
        digitalWrite(LED_ONBOARD,blink_state);
    }
}
