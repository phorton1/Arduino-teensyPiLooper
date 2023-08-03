EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R?
U 1 1 64CCBE5B
P 6950 3500
F 0 "R?" H 7020 3546 50  0000 L CNN
F 1 "220" V 6950 3500 50  0000 C CNN
F 2 "" V 6880 3500 50  0001 C CNN
F 3 "~" H 6950 3500 50  0001 C CNN
	1    6950 3500
	0    -1   -1   0   
$EndComp
Text GLabel 5500 2850 2    50   Input ~ 0
TEENSY_PROG
Text GLabel 7350 3500 2    50   Input ~ 0
PI_RUN
Text GLabel 6800 3500 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 64CF1712
P 7150 3800
F 0 "Q?" H 7341 3846 50  0000 L CNN
F 1 "BC547" H 7341 3755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 7350 3725 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 7150 3800 50  0001 L CNN
	1    7150 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64CF464E
P 7250 4100
F 0 "#PWR?" H 7250 3850 50  0001 C CNN
F 1 "GND" H 7255 3927 50  0000 C CNN
F 2 "" H 7250 4100 50  0001 C CNN
F 3 "" H 7250 4100 50  0001 C CNN
	1    7250 4100
	1    0    0    -1  
$EndComp
Text GLabel 6950 3800 0    50   Input ~ 0
PI_REBOOT
Wire Wire Line
	7100 3500 7250 3500
Wire Wire Line
	7250 3600 7250 3500
Connection ~ 7250 3500
Wire Wire Line
	7250 3500 7350 3500
Wire Wire Line
	7250 4000 7250 4100
Text Notes 4950 4650 0    50   ~ 0
is soldered to\nground for \nsome unknown\nnon-reason
$Comp
L power:GND #PWR?
U 1 1 64D5E298
P 4800 5300
F 0 "#PWR?" H 4800 5050 50  0001 C CNN
F 1 "GND" V 4800 5100 50  0000 C CNN
F 2 "" H 4800 5300 50  0001 C CNN
F 3 "" H 4800 5300 50  0001 C CNN
	1    4800 5300
	-1   0    0    1   
$EndComp
Text GLabel 5000 5300 1    50   Input ~ 0
TX2
Text GLabel 4900 5300 1    50   Input ~ 0
RX2
Text GLabel 5000 3600 3    50   Input ~ 0
TX2
Text GLabel 4900 3600 3    50   Input ~ 0
RX2
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 64D54F6F
P 4900 5500
F 0 "J?" V 4900 5750 50  0000 L CNN
F 1 "TeensyExpression Serial" V 5050 5350 50  0000 L CNN
F 2 "" H 4900 5500 50  0001 C CNN
F 3 "~" H 4900 5500 50  0001 C CNN
	1    4900 5500
	0    1    1    0   
$EndComp
Text GLabel 5200 2150 1    50   Input ~ 0
ONBOARD_LED
Text GLabel 5000 2150 1    50   Input ~ 0
LED_PI_RUN
Text GLabel 5100 2150 1    50   Input ~ 0
LED_PI_READY
Text GLabel 4600 5300 1    50   Input ~ 0
I2S_LED2
Text GLabel 4500 5300 1    50   Input ~ 0
I2S_LED1
Text GLabel 3900 2150 1    50   Input ~ 0
VUSB
Text GLabel 4200 5300 1    50   Input ~ 0
VUSB
Text GLabel 4000 5300 1    50   Input ~ 0
RX1
Text GLabel 4100 5300 1    50   Input ~ 0
TX1
Text GLabel 4000 3600 3    50   Input ~ 0
RX1
Text GLabel 4100 3600 3    50   Input ~ 0
TX1
$Comp
L power:GND #PWR?
U 1 1 64D08031
P 3900 5300
F 0 "#PWR?" H 3900 5050 50  0001 C CNN
F 1 "GND" V 3900 5100 50  0000 C CNN
F 2 "" H 3900 5300 50  0001 C CNN
F 3 "" H 3900 5300 50  0001 C CNN
	1    3900 5300
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64D0323E
P 3900 3600
F 0 "#PWR?" H 3900 3350 50  0001 C CNN
F 1 "GND" V 3900 3400 50  0000 C CNN
F 2 "" H 3900 3600 50  0001 C CNN
F 3 "" H 3900 3600 50  0001 C CNN
	1    3900 3600
	1    0    0    -1  
$EndComp
Text GLabel 5200 3600 3    50   Input ~ 0
PI_REBOOT
Text GLabel 5100 3600 3    50   Input ~ 0
SENS_PI_RUN
Text GLabel 4300 5300 1    50   Input ~ 0
PI_RUN
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 64CE18FB
P 4200 5500
F 0 "J?" V 4200 6050 50  0000 R CNN
F 1 "RPI" V 4350 5500 50  0000 R CNN
F 2 "" H 4200 5500 50  0001 C CNN
F 3 "~" H 4200 5500 50  0001 C CNN
	1    4200 5500
	0    -1   1    0   
$EndComp
$Comp
L 0_my_teensy:myTeensy3.2 U?
U 1 1 64CC40AE
P 4450 2850
F 0 "U?" H 4600 2850 60  0000 L CNN
F 1 "myTeensy3.2" H 4500 3000 60  0000 L CNN
F 2 "" H 4450 2100 60  0000 C CNN
F 3 "" H 4450 2100 60  0000 C CNN
	1    4450 2850
	1    0    0    -1  
$EndComp
Text GLabel 4400 5300 1    50   Input ~ 0
SENS_PI_READY
Text GLabel 4400 3600 3    50   Input ~ 0
SENS_PI_READY
Wire Notes Line
	4800 3700 4800 4950
Text GLabel 6600 1900 3    50   Input ~ 0
ONBOARD_LED
Text GLabel 6800 1900 3    50   Input ~ 0
LED_PI_RUN
Text GLabel 6900 1900 3    50   Input ~ 0
LED_PI_READY
Text GLabel 7000 1900 3    50   Input ~ 0
I2S_LED1
Text GLabel 7100 1900 3    50   Input ~ 0
I2S_LED2
$Comp
L power:GND #PWR?
U 1 1 64D14989
P 6700 1900
F 0 "#PWR?" H 6700 1650 50  0001 C CNN
F 1 "GND" V 6700 1700 50  0000 C CNN
F 2 "" H 6700 1900 50  0001 C CNN
F 3 "" H 6700 1900 50  0001 C CNN
	1    6700 1900
	1    0    0    -1  
$EndComp
Text GLabel 7200 1900 3    50   Input ~ 0
TEENSY_PROG
Text GLabel 7300 1900 3    50   Input ~ 0
PI_RUN
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 64CCC22C
P 7000 1700
F 0 "J?" V 7000 1100 50  0000 R CNN
F 1 "LED_BOARD" V 7150 1800 50  0000 R CNN
F 2 "" H 7000 1700 50  0001 C CNN
F 3 "~" H 7000 1700 50  0001 C CNN
	1    7000 1700
	0    1    -1   0   
$EndComp
Text Notes 4050 5800 3    50   ~ 0
RPI TX PIN  8
Text Notes 3950 5800 3    50   ~ 0
RPI GND PIN  6
Text Notes 4150 5800 3    50   ~ 0
RPI RX PIN 10
Text Notes 4250 5800 3    50   ~ 0
RPI 5V PIN  2
Text Notes 4350 5800 3    50   ~ 0
RPI RUN PIN
Text Notes 4450 5800 3    50   ~ 0
RPI GPIO25 PIN 22
Text Notes 4550 5800 3    50   ~ 0
RPI GPIO12 PIN 32
Text Notes 4650 5800 3    50   ~ 0
RPI GPIO16 PIN 36
Text Notes 4850 5800 3    50   ~ 0
GND
Text Notes 4950 5800 3    50   ~ 0
SLEEVE
Text Notes 5050 5800 3    50   ~ 0
TIP
$EndSCHEMATC
