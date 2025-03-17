// script.js

function toggle(element) {
    const nestedList = element.nextElementSibling;
    if (nestedList.style.display === "block") {
        nestedList.style.display = "none";
    } else {
        nestedList.style.display = "block";
    }
}
