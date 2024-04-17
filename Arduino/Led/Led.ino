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

#include "ParkLed.h"
#include "ParkSerial.h"
#include "ParkUtils.h"
#include "Config.h"

ParkSerial pSerial;
ParkDurumu pDurumu;
ParkLed pLED;

void setup() {
  pSerial.init();
  pLED.init();
}

void loop() {
  pSerial.handle(pDurumu);
  pLED.handle();
}