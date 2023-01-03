#include "JAL_DEBUG.h"

void JAL_DEBUG::init(int _i_serial_speed){
    Serial.begin(_i_serial_speed);
}

void JAL_DEBUG::print(const char * format)
{
    if(g_b_enabled){
        Serial.print(g_s_module_name);
        Serial.print(format);
    }
}