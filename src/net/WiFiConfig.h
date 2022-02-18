#include <WiFi.h>
#include <iostream>

namespace wifi
{
    /*This function configures the WiFi connection with a local router.
    ______________________________________________________
    const char* ssid : routers ssid
    const char* password : routers LAN connection password*/
    void init(const char* ssid, const char* password){

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            std::cout << ".";
            vTaskDelay(pdMS_TO_TICKS( 1000));
        }
        
        std::cout << "\nAddress: " << WiFi.localIP().toString().c_str() << '\n';
    }
} // namespace wifi