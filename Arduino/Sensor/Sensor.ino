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
#include "ParkEkran.h"
#include "ParkUtils.h"
#include "Config.h"

ParkSerial pSerial;
SensorDurumu sensorDurum;
ParkSensorler pSensorler;
ParkEkran pEkran;

void setup() {
  pSerial.init();
  pSensorler.init();
  pEkran.init();
}

void loop() {
  pSerial.handle(sensorDurum);
  pSensorler.handle(sensorDurum);
  pEkran.handle(sensorDurum);
}
