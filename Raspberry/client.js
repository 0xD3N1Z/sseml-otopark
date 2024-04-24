const enterButton = document.querySelector(".gate-enter");
const exitButton = document.querySelector(".gate-exit");
const doluParkE = document.querySelector(".dolu-park");
const bosParkE = document.querySelector(".bos-park");

$(document).ready(async function () {
    const main_response = await fetch("http://192.168.31.92:8080/?key=w3hLUCppceviC3UyA4hw0M2qFqQJi1v4");
    const json = await main_response.json();

    const doluPark = ((json["parkA"].match(/1/g) || []).length) + ((json["parkB"].match(/1/g) || []).length);
    const bosPark = 27 - doluPark

    doluParkE.innerHTML = doluPark;
    bosParkE.innerHTML = bosPark;
}); 

$(".gate-enter").on("click", async function() {
    alert("giriş kapısı açıldı")
    const response = await fetch("http://192.168.31.92:8080/giris");
    
})

$(".gate-exit").on("click", async function() {
    alert("çıkış kapısı açıldı")
    const response = await fetch("http://192.168.31.92:8080/cikis");
})