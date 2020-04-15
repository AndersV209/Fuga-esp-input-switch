// WiFi Parameters
const char* ssid = "SSID";
const char* password = "PASS";

//hostname for this switch 
#define HOSTNAME "Fuga-esp-client-office"     // Friedly hostname

//Openhab (String) item names for the led status 
const String OH_led_item_name[4] = {
  "LED_Office_1",
  "LED_Office_2",
  "LED_Office_3",
  "LED_Office_4",
};

//Openhab String item names for the buttons 
const String OH_post_item_name_string[4] = {
  "BUTTON_Office_1", 
  "BUTTON_Office_2",
  "BUTTON_Office_3",
  "BUTTON_Office_4",
};

//States of the buttons (not used atm) 
/*const String Switch_states[4] = {
  "OFF",
  "SHORT_PRESSED",
  "DOUBLE_PRESSED",
  "LONG_PRESSED",
};*/

//States of Led 
const String Led_states[4] = {
  "OFF",
  "BLUE",
  "GREEN",
  "RED",
};

const int Number_of_Led_states = 4;


//Adress for openhab server 
const String host_address  = "http://OPENHAB IP:8080";
//const String state_address = "/rest/items?tags=Switchable&recursive=false";
const String state_address = "/rest/items?tags=Buttons&recursive=false"; //button items need tag buttons in openhab
const String change_state_address = "/rest/items/";
