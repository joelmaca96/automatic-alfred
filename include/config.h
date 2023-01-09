

#ifndef __CONFIG__H
#define __CONFIG__H


/******************** CONFIG DEFINITIONS ********************/

//Debug
#define DEBUG (1)
#if DEBUG
    #define SERIAL_SPEED (115200)

    #define DEBUG_WIFI   (1)
    #define DEBUG_ALEXA  (1)
    #define DEBUG_RTC    (1)
#endif



#endif