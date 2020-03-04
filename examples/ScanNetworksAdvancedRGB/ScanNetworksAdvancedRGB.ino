/*

  This example  prints the board's MAC address, and
  scans for available WiFi networks using the NINA module.
  Every ten seconds, it scans again. It doesn't actually
  connect to any network, so no encryption scheme is specified.
  BSSID and WiFi channel are printed.

  This example has been modified from ScanNetworksAdvanced with pin definitions
  for the onboard RGB LED, and a setLEDColor() function which changes the LED state
  from Red (init) to Blue (scanning for wifi) and finally Green (idling).

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  modified 18 Jan 2019
  by Drew Alden (ReanimationXP)
*/


//#include <SPI.h>
#include <WiFiNINA.h> //https://github.com/arduino-libraries/WiFiNINA
#include <utility/wifi_drv.h> //included with WiFiNINA

//RGB LED pin definitions for MKR WiFi 1010
#define GREEN_LED_pin   25
#define BLUE_LED_pin    27
#define RED_LED_pin     26


void setup() {
   
  //Initialize serial
  Serial.begin(115200);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}

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

  //Alternate instantiation method:
  //WiFiDrv *WifiDriver = new WiFiDrv();
  
  //WifiDriver->pinMode(RED_LED_pin, OUTPUT);   //RED
  //WifiDriver->pinMode(GREEN_LED_pin, OUTPUT); //GREEN
  //WifiDriver->pinMode(BLUE_LED_pin, OUTPUT);  //BLUE

  //set ESP32 wifi module RGB led pins to output -RXP
  WiFiDrv::pinMode(RED_LED_pin, OUTPUT);   //RED
  WiFiDrv::pinMode(GREEN_LED_pin, OUTPUT); //GREEN
  WiFiDrv::pinMode(BLUE_LED_pin, OUTPUT);  //BLUE

  //turn off ESP32 wifi module RGB led
  WiFiDrv::digitalWrite(RED_LED_pin, LOW);    //values are uint8_t
  WiFiDrv::digitalWrite(GREEN_LED_pin, LOW);
  WiFiDrv::digitalWrite(BLUE_LED_pin, LOW);

  //set ESP32 wifi module RGB led color
  WiFiDrv::analogWrite(RED_LED_pin, 255); //Red to 100%
  WiFiDrv::analogWrite(GREEN_LED_pin, 0); //Green off
  WiFiDrv::analogWrite(BLUE_LED_pin, 0);  //Blue off

  //set ESP32 wifi module RGB led color with setLEDColor(R,G,B) function. Range is 0-255 for each color.
  setLEDColor(255,0,0); //Red to 100%

  delay(2000);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  printMacAddress(mac);

  setLEDColor(0,0,255); //RGB to Blue
  // scan for existing networks:
  Serial.println();
  Serial.println("Scanning available networks...");
  listNetworks();
}

void loop() {
  setLEDColor(0,255,0); //RGB to Green
  delay(10000);

  setLEDColor(0,0,255); //RGB to Blue
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a WiFi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks: ");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet + 1);
    Serial.print(") ");
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\t\tSSID: ");
    Serial.println(WiFi.SSID(thisNet));
    
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
    Serial.print("\tChannel: ");
    Serial.print(WiFi.channel(thisNet));
    byte bssid[6];
    Serial.print("\tBSSID: ");
    printMacAddress(WiFi.BSSID(thisNet, bssid));
    
    Serial.flush();
  }
  Serial.println();
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.print("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.print("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.print("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.print("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.print("Auto");
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      Serial.print("Unknown");
      break;
  }
}

void print2Digits(byte thisByte) {
  if (thisByte < 0xF) {
    Serial.print("0");
  }
  Serial.print(thisByte, HEX);
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}

void setLEDColor(uint8_t R, uint8_t G, uint8_t B){
  //R, G, and B values should not exceed 255 or be lower than 0.
  
  //set ESP32 wifi module RGB led color
  WiFiDrv::analogWrite(RED_LED_pin, R); //Red
  WiFiDrv::analogWrite(GREEN_LED_pin, G); //Green
  WiFiDrv::analogWrite(BLUE_LED_pin, B);  //Blue
}
