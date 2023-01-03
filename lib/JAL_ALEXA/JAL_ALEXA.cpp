#include "JAL_ALEXA.h"

/******************* GLOBAL ITEMS ********************/
fauxmoESP alexa;
JAL_DEBUG dbg_alexa("[ALEXA]", DEBUG_ALEXA);
alexaItem st_alexaItems[10];
uint8_t u8_numberOfItems;

/******************* PUBLIC METHODS ********************/
bool JAL_ALEXA_INIT(alexaItem* _p_st_alexaItems, uint8_t _u8_numberOfItems){
    u8_numberOfItems = _u8_numberOfItems;

    /* 1. configuracion del servidor emuladro de philips hue*/
    alexa.createServer(true);
    alexa.setPort(80);

    /* 1.1 Habilitacion del servidor */
    alexa.enable(true);

    /* 2. Añadir los dispositivos al servidor e inicializar los puertos */
    for(uint8_t u8_i;u8_i < _u8_numberOfItems;u8_i ++){
        alexa.addDevice(_p_st_alexaItems[u8_i].s_activationName.c_str());
        dbg_alexa.printf(" Añadido %s a los dispositivos \n", _p_st_alexaItems[u8_i].s_activationName.c_str());
        st_alexaItems[u8_i].s_activationName = _p_st_alexaItems[u8_i].s_activationName;
        st_alexaItems[u8_i].u8_gpio = _p_st_alexaItems[u8_i].u8_gpio;

        pinMode(_p_st_alexaItems[u8_i].u8_gpio, OUTPUT);
        digitalWrite(_p_st_alexaItems[u8_i].u8_gpio, LOW);
    }

    /* 3. Configurar el callback */
    alexa.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        dbg_alexa.printf(" Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        for(uint8_t u8_i;u8_i < u8_numberOfItems;u8_i ++){
            if ( (strcmp(device_name, st_alexaItems[u8_i].s_activationName.c_str()) == 0) ){
                digitalWrite(st_alexaItems[u8_i].u8_gpio, state);
            }
        }

    });

    return true;
}

void JAL_ALEXA_LOOP(){
    alexa.handle();
}


