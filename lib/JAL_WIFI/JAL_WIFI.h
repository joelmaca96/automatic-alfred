#ifndef __JAL_WIFI__H
#define __JAL_WIFI__H


/********************* INCLUDES ***********************/
#include "../../include/config.h"
#include "Arduino.h"
#include "WiFi.h"

/* Joel Hal */
#include "JAL_DEBUG.h"

/******************** DEFINITIONS **********************/

/******************* PUBLIC METHODS ********************/
void JAL_WIFI_INIT();
bool JAL_WIFI_CONNECT(char* SSID, char* PWD);
void JAL_WIFI_PRINT_INFO();
bool JAL_WIFI_STOP();
void JAL_WIFI_SCAN();
bool JAL_WIFI_CHECK_CONNECTION();

#endif