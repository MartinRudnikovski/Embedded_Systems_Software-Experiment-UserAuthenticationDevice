#include <AsyncEventSource.h>

namespace sms
{
    namespace
    {
        AsyncEventSource events("/");
        const uint16_t maximum = 2760;
        const uint16_t minimum = 1110;

        uint16_t current_moisture = -1;
        uint8_t temp;
        uint16_t x;
        int n;

        uint8_t soil_moisture_pin;
        void soilMoistureTask(void* p){
            while(1)
            {
                x = analogRead(soil_moisture_pin);
                n = 1;  

                for (size_t i = 0; i < 6; i++)
                {
                    x = ((x*n) + analogRead(soil_moisture_pin)) / (n+1);
                    n++;

                    temp =  map( x , maximum, minimum, 0, 10);
                    
                    if (current_moisture != temp)
                    {
                        current_moisture = temp;
                        events.send( (String(current_moisture) + "/10" ).c_str() );
                    }
                    
                    vTaskDelay(pdMS_TO_TICKS(2000));
                }
            }

            vTaskDelete(NULL);
        }
    }
    /*
    This method is the only one to be used outside of this file and it configures an event-based data source for changes in soil moisture based on the sensor.
    Must make sure to be connected to WiFi first!
    The AsyncWebServer should be managed by the proggramer, as this function only uses it to asign the AsyncWebSource to it.
    ________________________________________________________________
    AsyncWebServer* server : the server object used to send the data
    const uint8_t : soil moisture sensor pin number*/
    void init(AsyncWebServer* server, const uint8_t pin){
        
        server->addHandler(&events);

        soil_moisture_pin = pin;
        pinMode(soil_moisture_pin, INPUT);

        xTaskCreate(
            soilMoistureTask,
            "Soil moisture sensor task",
            4096,
            NULL,
            1,
            NULL
        );
        
    }
} // namespace sms