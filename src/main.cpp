/****************** INCLUDES ******************/
#include <Arduino.h>
#include <WiFi.h>

/* Project includes */
#include "config.h"
#include "secret_info.h"
#include "fauxmoESP.h"

/* JAL Joel */
#include "JAL_DEBUG.h"
#include "JAL_WIFI.h"
#include "JAL_ALEXA.h"
#include "JAL_RTC.h"

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

  /* 1.3 Módulo RTC */
  JAL_RTC_SYNC();

  /* 
  *| 2. Configuracion de Alexa
  */

  /* 2.1 Creacion de los dispositivos fisicos, añadir los necesarios*/
  alexaItem st_pantalla = {
    .s_activationName = "pantalla",
    .u8_gpio = 26
  };

  alexaItem st_balda = {
    .s_activationName = "balda",
    .u8_gpio = 27
  };
  alexaItem s_dispositivos[2] = {st_pantalla, st_balda};

  /* 2.2 Inicialización del módulo*/
  JAL_ALEXA_INIT(s_dispositivos,2);
}

void loop() {
  /* Loop del modulo de alexa */
  JAL_ALEXA_LOOP();

}