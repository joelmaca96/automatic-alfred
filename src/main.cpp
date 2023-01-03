/****************** INCLUDES ******************/
#include <Arduino.h>
#include <WiFi.h>

/* Project includes */
#include "config.h"
#include "secret_info.h"

/* JAL Joel */
#include "JAL_DEBUG.h"
#include "JAL_WIFI.h"

void setup() {
  /*
  *| 1. Configuracion de los modulos
  */

  /* 1.1 Modulo de debug, debe ser el primero para no perder tramas*/
  JAL_DEBUG dbg("[MAIN]", DEBUG);
  dbg.init(SERIAL_SPEED);

  /* 1.2 Modulo wifi */
  JAL_WIFI_CONNECT(MY_SSID, MY_PASSWD);
  JAL_WIFI_PRINT_INFO();

}

void loop() {
  
}