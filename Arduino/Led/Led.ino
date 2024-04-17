//  (      (              *      (           )                )    (                (          )  
//  )\ )   )\ )         (  `     )\ )     ( /(     *   )   ( /(    )\ )     (       )\ )    ( /(  
// (()/(  (()/(   (     )\))(   (()/(     )\())  ` )  /(   )\())  (()/(     )\     (()/(    )\()) 
//  /(_))  /(_))  )\   ((_)()\   /(_))   ((_)\    ( )(_)) ((_)\    /(_)) ((((_)(    /(_)) |((_)\  
// (_))   (_))   ((_)  (_()((_) (_))       ((_)  (_(_())    ((_)  (_))    )\ _ )\  (_))   |_ ((_) 
// / __|  / __|  | __| |  \/  | | |       / _ \  |_   _|   / _ \  | _ \   (_)_\(_) | _ \  | |/ /  
// \__ \  \__ \  | _|  | |\/| | | |__    | (_) |   | |    | (_) | |  _/    / _ \   |   /    ' <   
// |___/  |___/  |___| |_|  |_| |____|    \___/    |_|     \___/  |_|     /_/ \_\  |_|_\   _|\_\  
//                                                                                           
// Ledler için

#include "Led.h"
#include "Config.h"

ParkLed led;
String command;

void setup() {
  Serial.begin(9600);

  led.init();
}

void loop() {
  //Seri porttan gelen komutu oku
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
  }

  //Komut algılandığında işle
  if (command != "") {
    if (command.equals("SERIAL-ID?")) Serial.println(SERIAL_ID);

    if (command.startsWith())

    command = "";
  }
}
