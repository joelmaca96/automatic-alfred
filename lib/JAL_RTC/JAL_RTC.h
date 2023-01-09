#ifndef __JAL_RTC__H
#define __JAL_RTC__H


/********************* INCLUDES ***********************/
#include "../../include/config.h"
#include "Arduino.h"
#include "ESP32Time.h"

/* Joel Hal */
#include "JAL_RTC.h"
#include "JAL_DEBUG.h"
#include "JAL_WIFI.h"

/******************** DEFINITIONS **********************/

/******************** TYPEDEFS **********************/
typedef struct st_hora
{
    uint8_t  u8_hora;
    uint8_t  u8_minuto;
    uint8_t  u8_segundo;
    uint16_t u16_milisegundo;
    uint32_t u32_microsegundo;
}hora;

typedef struct st_fecha
{
    uint8_t  u8_dia;
    uint8_t  u8_mes;
    uint16_t u16_aino;
}fecha;

typedef struct st_dateTime
{
    fecha s_fecha;
    hora  s_hora;
}dateTimeM;


/******************* PUBLIC METHODS ********************/
void  JAL_RTC_INIT();
bool  JAL_RTC_SYNC();
fecha JAL_RTC_GET_DATE();
hora  JAL_RTC_GET_TIME();
void JAL_RTC_PRINT_DATE_TIME();

#endif