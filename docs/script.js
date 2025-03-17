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

function loadContent(file) {
    const contentArea = document.getElementById('content');
    fetch(file)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.text();
        })
        .then(data => {
            contentArea.innerHTML = data; // Load the content into the content area
            updateOnThisPage(); // Update the right sidebar if needed
        })
        .catch(error => {
            console.error('There was a problem with the fetch operation:', error);
            contentArea.innerHTML = '<p>Error loading content.</p>';
        });
}

function updateOnThisPage() {
    // This function can be customized to update the right sidebar based on the loaded content
    const onThisPage = document.getElementById('on-this-page');
    onThisPage.innerHTML = ''; // Clear existing items
    // Example: Add new sections based on the loaded content
    onThisPage.innerHTML += '<li><a href="#section1">Section 1</a></li>';
    onThisPage.innerHTML += '<li><a href="#section2">Section 2</a></li>';
}
