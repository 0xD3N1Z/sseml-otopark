const enterButton = document.querySelector(".gate-enter");
const exitButton = document.querySelector(".gate-exit");
const doluParkE = document.querySelector(".dolu-park");
const bosParkE = document.querySelector(".bos-park");
const saat = document.querySelector(".saat");
const sicaklik = document.querySelector(".sicaklik");
const nem = document.querySelector(".nem");
const solar = document.querySelector(".solar");
const pil = document.querySelector(".pil");

$(document).ready(async function () {
    refresh();
});

setInterval(function () {
    refresh();
}, 1000);

async function refresh() {
    const main_response = await fetch("http://192.168.43.100:8080/?key=w3hLUCppceviC3UyA4hw0M2qFqQJi1v4");
    const json = await main_response.json();

    const doluPark = ((json["parkA"].match(/1/g) || []).length) + ((json["parkB"].match(/1/g) || []).length);
    const bosPark = 28 - doluPark

    doluParkE.innerHTML = doluPark;
    bosParkE.innerHTML = bosPark;

    const date = new Date();
    saat.innerHTML = `${date.getHours()}.${date.getMinutes().toString().padStart(2, '0')} ${(date.getHours() > 12 ? 'PM' : 'AM')}`

    const weather = json["weather"].split(";")
    const power = json["power"].split(";")

    sicaklik.innerHTML = `${weather[0]} ℃`
    nem.innerHTML = `${weather[1]}%`

    power[1] == 1 ? solar.innerHTML = "Takılı - " + power[3] + 'v' : solar.innerHTML = "Takılı Değil";

    pil.innerHTML = power[2] + 'v';
}

$(".gate-enter").on("click", async function () {
    alert("giriş kapısı açıldı")
    const response = await fetch("http://192.168.43.100:8080/giris");
})

$(".gate-exit").on("click", async function () {
    alert("çıkış kapısı açıldı")
    const response = await fetch("http://192.168.43.100:8080/cikis");
})