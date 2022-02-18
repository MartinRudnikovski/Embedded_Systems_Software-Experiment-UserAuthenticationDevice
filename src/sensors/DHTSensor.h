#include <DHTesp.h>
#include <iostream>
#include <AsyncEventSource.h>

namespace dht
{
    namespace 
    {
        AsyncEventSource humidity("/h");
        AsyncEventSource temperature("/t");
        DHTesp dht;
        TempAndHumidity tah;

        void dhtTask(void* p){
            while (1)
            {
                tah = dht.getTempAndHumidity();

                humidity.send((String((float)tah.humidity) + "%" ).c_str());
                temperature.send((String((float)tah.temperature) + " C" ).c_str());

                std::cout << "Temperature: " << tah.temperature << " Humidity: " << tah.humidity << '\n';

                vTaskDelay(pdMS_TO_TICKS(4000));                
            }

            vTaskDelete(NULL);
        }

    } // namespace 
    
    void init(AsyncWebServer* server, const uint8_t pin){
        server->addHandler(&humidity);
        server->addHandler(&temperature);
        
        dht.setup(pin, DHTesp::DHT11);

        xTaskCreate(
            dhtTask,
            "Temperature and humidity sensor task",
            4096,
            NULL,
            1,
            NULL
        );
    }
} // namespace dht
