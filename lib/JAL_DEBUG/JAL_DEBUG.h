#ifndef __JAL_DEBUG__H
#define __JAL_DEBUG__H


/********************* INCLUDES ***********************/
#include "config.h"
#include "Arduino.h"
#include "stdio.h"
/******************** DEFINITIONS **********************/

/****************** CLASS DEFINITION ********************/

/******************* PUBLIC METHODS ********************/
class JAL_DEBUG {
  private:
    String g_s_module_name;
    bool g_b_enabled;
  public:
    //constructor
    JAL_DEBUG(String _s_module_intro, bool _b_enabled){
        g_s_module_name = _s_module_intro;
        g_b_enabled = _b_enabled;
    }

    //public methods
    template <typename ...Args>
    String sprintf(const char * format, Args ...args)
    {
        char buffer[256];

        snprintf(buffer, 256, format, args...);

        return String(buffer);
    }

    void print(const char * format);
    void init(int _i_serial_speed);

    template <typename ...Args>
    void printf(const char * format, Args ...args)
    {
        if(g_b_enabled){
            Serial.print(g_s_module_name);
            Serial.print(this->sprintf(format, args...));
        }
    }

};
#endif