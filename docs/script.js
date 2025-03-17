// script.js

function toggle(event, element) {
    // Prevent the default link action if the element has children
    const nestedList = element.nextElementSibling;
    if (nestedList) {
        event.preventDefault(); // Prevent navigation if it has children
        if (nestedList.style.display === "block") {
            nestedList.style.display = "none";
            element.classList.remove('expanded'); // Remove expanded class
        } else {
            nestedList.style.display = "block";
            element.classList.add('expanded'); // Add expanded class
        }
    }
}
