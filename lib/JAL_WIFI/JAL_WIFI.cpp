#include "JAL_WIFI.h"

JAL_DEBUG dbg("[WIFI]", DEBUG_WIFI);


/******************* PUBLIC METHODS ********************/
void JAL_WIFI_INIT(){
    
}

bool JAL_WIFI_STOP(){
    //Si ya esta conectado no es necesario hacer nada
    if(WiFi.status() != WL_CONNECTED) return true;

    WiFi.disconnect();
    uint8_t u8_timeout = 100;

    while (WiFi.status() != WL_DISCONNECTED && --u8_timeout >0)
    {
        delay(5);
    }

    if(u8_timeout == 0){
        dbg.print(" error en la desconexion \n");
        return false;
    }

    return true;
}

bool JAL_WIFI_CONNECT(char* SSID, char* PWD){
    /*
    *| 1. Desconexión de la red actual (De haberla)
    */
    JAL_WIFI_STOP();

    /*
    *| 2. conexión a la red almacenada
    */
    dbg.print(" Conectando al Wifi...\n");
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PWD);

    /* 2.2 Esperar a aque se conecte o se pase el timeout */
    uint8_t u8_timeout = 100;
    while(WiFi.status() != WL_CONNECTED && u8_timeout >0){
        delay(500);
    }

    if(WiFi.status() == WL_CONNECTED){
        dbg.print(" Conectado al Wifi!\n");

        /*2.3 Establecer la configuracion de la red */
        WiFi.setAutoReconnect(true);
        return true;
    }

    return false;
    
}

void JAL_WIFI_PRINT_INFO(){
   /*
   *| 1. Comprobar el estado de la conexión
   */
   if(WiFi.status() != WL_CONNECTED) {
    dbg.print("No estas conectado!\n");
    return;
   }

   /*
   *| 2. Obtener los datos de la conexion
   */
   String s_ipAddress =  WiFi.localIP().toString();

   /*
   *| 3. Visualizarlos por pantalla
   */
   dbg.printf(" Direccion IP: %s \n",s_ipAddress);


}

void JAL_WIFI_SCAN(){
    /*
    *| 1. Desconexión de la red actual (De haberla)
    */
    JAL_WIFI_STOP();

    /*
    *| 2. escanear las redes disponibles
    */
   
    int n = WiFi.scanNetworks();
    dbg.print("scan done \n");
    if (n == 0) {
        dbg.print("sin redes disponibles \n");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
}


