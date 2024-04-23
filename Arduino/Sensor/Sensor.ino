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
#include "ParkCihazlar.h"
#include "ParkSerial.h"
#include "ParkEkran.h"
#include "ParkUtils.h"
#include "Config.h"

SensorDurumu sensorDurum;
CihazDurumu cihazDurum;

ParkSerial pSerial;
ParkSensorler pSensorler;
ParkCihazlar pCihazlar;
ParkEkran pEkran;

void setup() {
  pSerial.init();
  pSensorler.init();
  pCihazlar.init();
  pEkran.init();

  beep(BeepCodes::STARTUP);
}

void loop() {
  pSerial.handle(sensorDurum, cihazDurum);
  pSensorler.handle(sensorDurum);
  pCihazlar.handle(sensorDurum, cihazDurum);
  pEkran.handle(sensorDurum, cihazDurum);
}
