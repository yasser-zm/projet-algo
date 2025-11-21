document.querySelectorAll("button").forEach(btn => {
    btn.addEventListener("click", () => {
        console.log("Button pressed:", btn.textContent);
    });
});
