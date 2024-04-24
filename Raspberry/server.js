//  (               )   (         )     (               *      (      (      (             (               )
//  )\ )         ( /(   )\ )   ( /(     )\ )          (  `     )\ )   )\ )   )\ )          )\ )         ( /(
// (()/(   (     )\()) (()/(   )\())   (()/(    (     )\))(   (()/(  (()/(  (()/(    (    (()/(   (     )\())
//  /(_))  )\   ((_)\   /(_)) ((_)\     /(_))   )\   ((_)()\   /(_))  /(_))  /(_))   )\    /(_))  )\   ((_)/
//  _(_)  ((_)   _((_) (_))    _((_)   (_))_   ((_)  (_()((_) (_))   (_))   (_))_   ((_)  (_))   ((_)   _((_)
// |   \  | __| | \| | |_ _|  |_  /     |   \  | __| |  \/  | |_ _|  | _ \   |   \  | __| | |    | __| | \| |
// | |) | | _|  | .` |  | |    / /      | |) | | _|  | |\/| |  | |   |   /   | |) | | _|  | |__  | _|  | .` |
// |___/  |___| |_|\_| |___|  /___|     |___/  |___| |_|  |_| |___|  |_|_\   |___/  |___| |____| |___| |_|\_|
//
// Copyright (c) 2024 Deniz DEMIRDELEN

const express = require('express');
const fs = require('fs').promises;

const app = express()
const keys = ["w3hLUCppceviC3UyA4hw0M2qFqQJi1v4"];
const statusFile = "data.json";
const cmdFile = "cmd.json";
const port = process.env.PORT || 8080
const retryCount = 5;

app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})

app.get('/', async (req, res) => {
    const apiKey = req.query.key;
    let status;

    res.setHeader("Access-Control-Allow-Origin", "*");

    if (!keys.includes(apiKey)) {
        res.sendStatus(401);
        return;
    }

    try {
        status = await readStatus();
    } catch (error) {
        console.log(error);
        res.sendStatus(500);
        return;
    }

    res.json(status);
})

app.get('/giris', async (req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    
    try {
        await writeStatus({"enter":true,"exit":false});
    } catch (error) {
        console.log(error);
    }

    res.sendStatus(200);
})

app.get('/cikis', async (req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");

    try {
        await writeStatus({"enter":false,"exit":true});
    } catch (error) {
        console.log(error);
    }

    res.sendStatus(200);
})


function readStatus() {
    return new Promise(async (resolve, reject) => {
        var retries = 0;

        while (retries < retryCount) {
            try {
                resolve(JSON.parse(await fs.readFile(statusFile)));
                break;
            } catch (error) {
                console.log(`JSON okunurken hata oluştu. : ${error}`)
                retries++;
            }

            await wait(250);
        }

        if (retries == retryCount) {
            console.log(`JSON 5 tekrardan sonra bile okunamadı.`);
            reject(`OutOfRetries`);
        }
    })
}

function writeStatus(status) {
    return new Promise(async (resolve, reject) => {
        var retries = 0;

        while (retries < retryCount) {
            try {
                resolve(await fs.writeFile(cmdFile, JSON.stringify(status)))
                break;
            } catch (error) {
                console.log(`JSON yazılırken hata oluştu. : ${error}`)
                retries++;
            }

            await wait(250);
        }

        if (retries == retryCount) {
            console.log(`JSON 5 tekrardan sonra bile yazılamadı.`);
            reject(`OutOfRetries`);
        }
    })
}

//async bekleme
function wait(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}