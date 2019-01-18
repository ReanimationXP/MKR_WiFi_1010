/*

  This example  prints the board's MAC address, and
  scans for available WiFi networks using the NINA module.
  Every ten seconds, it scans again. It doesn't actually
  connect to any network, so no encryption scheme is specified.
  BSSID and WiFi channel are printed

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  This example is based on ScanNetworksAdvanced

  created 18 Jan 2019
  by Drew Alden (ReanimationXP)
*/

#include <SPI.h>
#include <WiFiNINA.h> //https://github.com/arduino-libraries/WiFiNINA
#include <utility/wifi_drv.h> //included with WiFiNINA

//RGB LED pin definitions for MKR WiFi 1010
#define GREEN_LED_pin   25
#define BLUE_LED_pin    27
#define RED_LED_pin     26

int loopCount = 0;

void setup() {
  /*   
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
  */
  
  //set ESP32 wifi module RGB led pins to output
  WiFiDrv::pinMode(RED_LED_pin, OUTPUT);   //RED
  WiFiDrv::pinMode(GREEN_LED_pin, OUTPUT); //GREEN
  WiFiDrv::pinMode(BLUE_LED_pin, OUTPUT);  //BLUE

  //turn off ESP32 wifi module RGB led
  WiFiDrv::digitalWrite(RED_LED_pin, LOW);    //values are uint8_t
  WiFiDrv::digitalWrite(GREEN_LED_pin, LOW);
  WiFiDrv::digitalWrite(BLUE_LED_pin, LOW);

  //set ESP32 wifi module RGB led color
  WiFiDrv::analogWrite(RED_LED_pin, 0);     //Red off
  WiFiDrv::analogWrite(GREEN_LED_pin, 255); //Green to 100%
  WiFiDrv::analogWrite(BLUE_LED_pin, 0);    //Blue off

  //set ESP32 wifi module RGB led color with setLEDColor(R,G,B) function. Range is 0-255 for each color.
  setLEDColor(0,255,0); //Green to 100%
  delay(2000);

  setLEDColor(0,0,0); //All LEDs off
  delay(500);

}

void loop() {

  rainbowStep(3, loopCount);
  loopCount++;
  
}

void setLEDColor(uint8_t R, uint8_t G, uint8_t B){
  //R, G, and B values should not exceed 255 or be lower than 0.
  
  //set ESP32 wifi module RGB led color
  WiFiDrv::analogWrite(RED_LED_pin, R); //Red
  WiFiDrv::analogWrite(GREEN_LED_pin, G); //Green
  WiFiDrv::analogWrite(BLUE_LED_pin, B);  //Blue
}

void rainbowStep(int delaytime, int counter){

    //increase red
    for(int i=0; i<255; i++){
        WiFiDrv::analogWrite(RED_LED_pin, i); //Red
        delay(delaytime);
    }
    
    //if this is 2nd run or higher, then decrease blue.
    if( counter > 0){
        loopCount = 5; //reset global to low number so memory never blows up

        //decrease blue
        for(int i=254; i>=0; i--){
            WiFiDrv::analogWrite(BLUE_LED_pin, i);  //Blue
            delay(delaytime);
        }
    }
    
    //increase green
    for(int i=0; i<255; i++){
        WiFiDrv::analogWrite(GREEN_LED_pin, i); //Green
        delay(delaytime);
    }
    
    //decrease red
    for(int i=254; i>=0; i--){
        WiFiDrv::analogWrite(RED_LED_pin, i);
        delay(delaytime);
    }

    //increase blue
    for(int i=0; i<255; i++){
        WiFiDrv::analogWrite(BLUE_LED_pin, i);
        delay(delaytime);
    }
    
    //decrease green
    for(int i=254; i>=0; i--){
        WiFiDrv::analogWrite(GREEN_LED_pin, i);
        delay(delaytime);
    }
}
