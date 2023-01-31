/****************** INCLUDES ******************/
#include <Arduino.h>
#include <WiFi.h>
#include "painlessMesh.h"

/* Project includes */
#include "config.h"
#include "secret_info.h"
#include "fauxmoESP.h"

/* JAL Joel */
#include "JAL_DEBUG.h"
#include "JAL_WIFI.h"
#if SLAVE
#include "JAL_ALEXA.h"
#endif
#include "JAL_RTC.h"

/************ GLOBAL DEFINITIONS **************/
//painlessMesh  mesh;
//Scheduler userScheduler;

/******** PRIVATE METHODS PROTOTIPES ***********/
void receivedCallback( uint32_t from, String &msg );
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset);
void newConnectionCallback(uint32_t nodeId);

/************* PRIVATE METHODS *****************/
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

  /* 1.3 Módulo RTC, debe ir despues del wifi para sincronizarse con el ntp*/
  JAL_RTC_SYNC();

  /* 
  *| 2. Configuracion de Alexa (solo esclavos)
  */

  #if SLAVE
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
  #endif

  /* 
  *| 3. Configuracion de la red para reconocer el resto de dispositivos
  */
  /*mesh.setDebugMsgTypes( ERROR | STARTUP );

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);*/

}

void loop() {
  #if SLAVE
  /* Loop del modulo de alexa */
  JAL_ALEXA_LOOP();
  #endif

  /* Loop de la mesh */
  //mesh.update();
}

void receivedCallback( uint32_t from, String &msg ){}
void changedConnectionCallback(){}
void nodeTimeAdjustedCallback(int32_t offset){}


void newConnectionCallback(uint32_t nodeId){
  #if MASTER
    Serial.printf("New Connection, nodeId = %u\n", nodeId);
  #endif
}
/*
void sendMessage() {
  String msg = "Hi from node1";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}
*/