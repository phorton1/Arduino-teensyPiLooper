// script.js

function toggle(element) {
    const nestedList = element.nextElementSibling;
    if (nestedList.style.display === "block") {
        nestedList.style.display = "none";
        element.classList.remove('expanded'); // Remove expanded class
    } else {
        nestedList.style.display = "block";
        element.classList.add('expanded'); // Add expanded class
    }
}
