#include "dht.h"
#define dht_apin A0
dht DHT;

const int sensorMin = 0;
const int sensorMax = 1024;

int smokeAnalogPin = A4;
int sensorThres = 400;


class Sensor{
              private:
                
              public:
//              --------------------Smoke Sensor-------------------------------              
                void printSmoke(){
                    int analogSensor = analogRead(smokeAnalogPin);
                    Serial.print("Smoke Reading--Pin A4: ");
                    Serial.println(analogSensor);
                    }
//            --------------------Temperature And Humidity-------------------------
            
                void printhumidity(){
                      DHT.read11(dht_apin);
                      Serial.println((String)"Humidity:"+DHT.humidity+"% || Temp: "+DHT.temperature+"C");
                     }
//            -----------------------------Flame Sensor-----------------------
                void printFire(){
                   int sensorReading = analogRead(A2);
                   int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
                    switch (range) {
                      case 0:    // A fire closer than 1.5 feet away.
                        Serial.println("** Close Fire **");
                        break;
                      case 1:    // A fire between 1-3 feet away.
                        Serial.println("** Distant Fire **");
                        break;
                      case 2:    // No fire detected.
                        Serial.println("No Fire");
                        break;
                    }
                }
//         ------------------------------------------------------------------------
            };

void setup() {
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(smokeAnalogPin, INPUT);
}


void loop() {
Sensor readData;
readData.printhumidity();
readData.printFire();
readData.printSmoke();
Serial.println("---------------------------------");
delay(1000);

}
