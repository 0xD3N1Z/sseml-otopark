//  (      (              *      (           )                )    (                (          )  
//  )\ )   )\ )         (  `     )\ )     ( /(     *   )   ( /(    )\ )     (       )\ )    ( /(  
// (()/(  (()/(   (     )\))(   (()/(     )\())  ` )  /(   )\())  (()/(     )\     (()/(    )\()) 
//  /(_))  /(_))  )\   ((_)()\   /(_))   ((_)\    ( )(_)) ((_)\    /(_)) ((((_)(    /(_)) |((_)\  
// (_))   (_))   ((_)  (_()((_) (_))       ((_)  (_(_())    ((_)  (_))    )\ _ )\  (_))   |_ ((_) 
// / __|  / __|  | __| |  \/  | | |       / _ \  |_   _|   / _ \  | _ \   (_)_\(_) | _ \  | |/ /  
// \__ \  \__ \  | _|  | |\/| | | |__    | (_) |   | |    | (_) | |  _/    / _ \   |   /    ' <   
// |___/  |___/  |___| |_|  |_| |____|    \___/    |_|     \___/  |_|     /_/ \_\  |_|_\   _|\_\  
//                                                                                           
// Sensörler için

#include "ParkSensorler.h"
#include "ParkSerial.h"
#include "ParkUtils.h"
#include "Config.h"

ParkSerial pSerial;
//ParkSensorler pSensorler;

void setup() {
  pSerial.init();
  //pSensorler.init();
}

void loop() {
  pSerial.handle();
  /*pLED.handle(pDurumu); */
}
