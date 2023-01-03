#ifndef __JAL_ALEXA__H
#define __JAL_ALEXA__H


/********************* INCLUDES ***********************/
#include "../../include/config.h"
#include "Arduino.h"
#include "fauxmoESP.h"

/* Joel Hal */
#include "JAL_DEBUG.h"
/******************** TYPEDEFS **********************/
typedef struct st_alexaItem
{
    String s_activationName;
    uint8_t u8_gpio;
}alexaItem;

/******************** DEFINITIONS **********************/

/******************* PUBLIC METHODS ********************/
bool JAL_ALEXA_INIT(alexaItem* _p_st_alexaItems, uint8_t _u8_numberOfItems);
void JAL_ALEXA_LOOP();

#endif