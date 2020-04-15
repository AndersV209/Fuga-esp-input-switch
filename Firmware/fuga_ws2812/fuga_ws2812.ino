/*  

  openhab fuga esp control inputs 
 
 */
//include settings
#include "definitions.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_NeoPixel.h>
#include "ClickButton.h"              //https://github.com/marcobrianza/ClickButton




// pins 
#define led_pin 3 // pin for ws2812 
const int button_pin[4] = {5,12,4,13};

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size

int httpCode_send = 0;

const int pollingInterval = 500; //how often is the actual state of the Sonos fetched from the openHAB server [ms]
const unsigned long postingInterval_longpress = 1000;  // delay between updates, in milliseconds
int lastPoll;        //used to store the millis() of the last time a value was requested
int lastPost_longpress[4] = {0,0,0,0};        //used to store the millis() of the last time a value was requested

boolean getupdate = true;        //Indicates if a switch has been pushed since last send


//state holder for buttons and light 
boolean button_pressed_state[4] = {false};              //single click
boolean button_double_pressed_state[4] = {false};       //double click
boolean button_triple_pressed_state[4] = {false};       //triple click
boolean button_long_pressed_state[4] = {false};         //single long press
boolean button_double_long_pressed_state[4] = {false};  //double long press
unsigned int light_state[4] = {0};
unsigned int light_state_last[4] = {0};


Adafruit_NeoPixel strip(NUMPIXELS, led_pin, NEO_GRB + NEO_KHZ800);

// buttons setup 
const int buttons = 4;
int LEDfunction[buttons]  = { 0, 0, 0, 0 };
//int LEDfunction[buttons]  = { 0, 0, 0, 0 };

// Instantiate ClickButton objects in an array
ClickButton button[buttons] = {
  ClickButton (button_pin[0], LOW, CLICKBTN_PULLUP),
  ClickButton (button_pin[1], LOW, CLICKBTN_PULLUP),
  ClickButton (button_pin[2], LOW, CLICKBTN_PULLUP),
  ClickButton (button_pin[3], LOW, CLICKBTN_PULLUP),
};


void setup() {
  
  Serial.begin(115200);
  Serial.println("Firing up...");
  for (int i = 0; i <4; i++){
    pinMode(button_pin[i], INPUT_PULLUP);  

    // Setup button timers (all in milliseconds / ms)
    // (These are default if not set, but changeable for convenience)
    button[i].debounceTime   = 20;   // Debounce timer in ms
    button[i].multiclickTime = 250;  // Time limit for multi clicks
    button[i].longClickTime  = 1000; // Time until long clicks register
    
  }

  WiFi.mode(WIFI_STA);  
  //Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // ***************************************************************************
  // Setup: MDNS responder
  // ***************************************************************************
  //String hostname(HOSTNAME);
  MDNS.begin(HOSTNAME);
  ////Serial.print("Open http://");
  ////Serial.print(HOSTNAME);
  ////Serial.println(".local/edit to see the file browser");

  ArduinoOTA.begin();

  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.clear();   // 
  strip.show();   // Send the updated pixel colors to the hardware.
   
  Serial.println("Setup done!");
}

void loop() {

  button_handle(); // handle buttons read
    
  
  //set state of led on the buttons 
 /* if(light_state != light_state_last){// || light_state2 != light_state2_last ){
    for(int i = 0; i < 4; i++){
      if(bitRead(light_state, i)){
        strip.setPixelColor(i, strip.Color(0, 0, 150));  
      }
      else {
        strip.setPixelColor(i, strip.Color(0, 0, 0));  
      }
    }
    strip.show();   // Send the updated pixel colors to the hardware.
    light_state_last = light_state;
  }*/

    //set state of led on the buttons 
  
  for(int i = 0; i < 4; i++){
    if(light_state[i] != light_state_last[i]){// || light_state2 != light_state2_last ){
      if(light_state[i] == 1){
        strip.setPixelColor(i, strip.Color(0, 0, 150));  
      }
      else if(light_state[i] == 2) {
        strip.setPixelColor(i, strip.Color(0, 150, 0));  
      }
      else if(light_state[i] == 3) {
        strip.setPixelColor(i, strip.Color(150, 0, 0));  
      }
      else{
        strip.setPixelColor(i, strip.Color(0, 0, 0));  
      }
    
    strip.show();   // Send the updated pixel colors to the hardware.
    light_state_last[i] = light_state[i];
    }
  }



  changestates();  //change light state

  getstates();  //get light state 

  ArduinoOTA.handle();  //handle ota update 

  delay(1); //let cpu think 
}
