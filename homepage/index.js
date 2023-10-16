document.addEventListener('DOMContentLoaded', function() {
    document.querySelector('form').addEventListener('submit', function(e) {
        document.querySelector('p').innerText = 'Subscribed!';
        e.preventDefault();
    });
});