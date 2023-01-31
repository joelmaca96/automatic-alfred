/********************* INCLUDES ***********************/
#include "JAL_RTC.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "ESP32Time.h"

/********************* GLOBALS ***********************/
JAL_DEBUG dbg_rtc("[RTC]", DEBUG_RTC);
ESP32Time s_rtc;

/******************* PUBLIC METHODS ********************/
void  JAL_RTC_INIT(){

}

bool  JAL_RTC_SYNC(){
    /*
    *| 1. Comprobar si el wifi está conectado, sino no se puede actualizar
    */
    if(!JAL_WIFI_CHECK_CONNECTION()) return false;

    /*
    *| 2. Obtener la hora actual de un servidor ntp 
    */
    
    /* Crear el objeto para la conexion */
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);

    /* Conectar al servidor y obrener la hora */
    timeClient.begin();
    timeClient.update();

    /* Actualizar la hora del RTC */
    s_rtc.setTime(timeClient.getEpochTime());

    /* Mostrar el resultado por pantalla */
    JAL_RTC_PRINT_DATE_TIME();

    return true;
}

fecha JAL_RTC_GET_DATE(){
    fecha s_fecha;
    
    s_fecha.u8_dia  = (uint8_t)s_rtc.getDay();
    s_fecha.u8_mes  = (uint8_t)s_rtc.getMonth();
    s_fecha.u16_aino = (uint16_t)s_rtc.getYear();
    
    return s_fecha;
}

hora  JAL_RTC_GET_TIME(){
    hora s_tiempo;
    
    s_tiempo.u8_hora    = (uint8_t)s_rtc.getHour(true); //el true es para el formato 24 horas
    s_tiempo.u8_minuto  = (uint8_t)s_rtc.getMinute();
    s_tiempo.u8_segundo = (uint16_t)s_rtc.getSecond();
    s_tiempo.u16_milisegundo = (uint16_t)s_rtc.getMillis();
    s_tiempo.u32_microsegundo = (uint16_t)s_rtc.getMicros();
    
    return s_tiempo;
}

uint32_t JAL_RTC_GET_TIMESTAMP(){
    return s_rtc.getEpoch();
}

void JAL_RTC_PRINT_DATE_TIME(){
    #if DEBUG_RTC
        Serial.println(s_rtc.getTimeDate(true));
    #endif
}