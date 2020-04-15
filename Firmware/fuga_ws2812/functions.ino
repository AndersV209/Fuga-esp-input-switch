//read state of light from openhab
void getstates(){

  if (millis() > lastPoll + pollingInterval || getupdate) {
  
    if (WiFi.status() == WL_CONNECTED) {
      
        
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address+state_address);
        //
        int httpCode = http.GET();
        
        lastPoll = millis();        //Remember when the states was fetched from the server
        getupdate = false;
        Serial.print("get update at: ");
        Serial.println(lastPoll);
        
        //Check the returning code                                                                  
        if (httpCode > 0) {
          //Serial.println("http");
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          const size_t capacity = 20*JSON_ARRAY_SIZE(0) + 30*JSON_ARRAY_SIZE(1) + 14*JSON_ARRAY_SIZE(2) + 6*JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(27) + 7*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 18*JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(10) + 7*JSON_OBJECT_SIZE(11) + 5810;
          DynamicJsonDocument doc(capacity);
          deserializeJson(doc, http.getString());
          

            //Serial.print("Array size of: ");
            //Serial.println(doc.size());

            for(int i= 0; i < doc.size(); i++){
          JsonObject root_temp = doc[i];
          
          const char* root_temp_name = root_temp["name"];
          const char* root_temp_state = root_temp["state"];
          
          Serial.print("name: ");
          Serial.print(root_temp_name);
          Serial.print("  state: ");
          Serial.println(root_temp_state);
          //Serial.println();
          
          for(int j = 0; j < 4; j++){
            if(root_temp["name"] == OH_led_item_name[j]){
              //Serial.println(OH_led_item_name[j]);
              for(int k = 0; k < Number_of_Led_states; k++){
                if(root_temp["state"] == Led_states[k]){
                  light_state[j] = k;
                  //light_state[0] = true;
                }
                else if (root_temp["state"] == "NULL"){
                  light_state[j] = 0;
                }
              } 
              
              }// if 
          }

      }//end for loop


          
        }
        else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
        http.end();   //Close connection
      }
      
    } //end if mills 
  
}



//change states 
void changestates(){
 for(int i = 0; i < 4; i++){ 
      // send button changes
    //single click
    if (button_pressed_state[i]){
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address + change_state_address + OH_post_item_name_string[i]);
        //if (bitRead(light_state, i)){
        //   httpCode_send = http.POST("OFF");
        //  }
        //  else {
        //    httpCode_send = http.POST("ON");
        //  }

        httpCode_send = http.POST("SHORT_PRESSED");
        //Check the returning code                                                                  
        if (httpCode_send > 0) {
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          Serial.println("POST message succes");
            
        }
        http.end();   //Close connection
      }
      getupdate=true;
      button_pressed_state[i] = false;
    }

    //double click 
    if (button_double_pressed_state[i]){
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address + change_state_address + OH_post_item_name_string[i]);
        //if (bitRead(light_state, i)){
        //   httpCode_send = http.POST("OFF");
        //  }
        //  else {
        //    httpCode_send = http.POST("ON");
        //  }

        httpCode_send = http.POST("DOUBLE_PRESSED");
        //Check the returning code                                                                  
        if (httpCode_send > 0) {
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          Serial.println("POST message succes");
            
        }
        http.end();   //Close connection
      }
      getupdate=true;
      button_double_pressed_state[i] = false;
    }
    //triple click
    if (button_triple_pressed_state[i]){
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address + change_state_address + OH_post_item_name_string[i]);
        //if (bitRead(light_state, i)){
        //   httpCode_send = http.POST("OFF");
        //  }
        //  else {
        //    httpCode_send = http.POST("ON");
        //  }

        httpCode_send = http.POST("TRIPLE_PRESSED");
        //Check the returning code                                                                  
        if (httpCode_send > 0) {
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          Serial.println("POST message succes");
            
        }
        http.end();   //Close connection
      }
      getupdate=true;
      button_triple_pressed_state[i] = false;
    }
    //long click
    if (button_long_pressed_state[i] && millis() > lastPost_longpress[i] + postingInterval_longpress){
      if (WiFi.status() == WL_CONNECTED) {
        lastPost_longpress[i] = millis();
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address + change_state_address + OH_post_item_name_string[i]);
        //if (bitRead(light_state, i)){
        //   httpCode_send = http.POST("OFF");
        //  }
        //  else {
        //    httpCode_send = http.POST("ON");
        //  }

        httpCode_send = http.POST("LONG_PRESSED");
        //Check the returning code                                                                  
        if (httpCode_send > 0) {
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          Serial.println("POST message succes");
            
        }
        http.end();   //Close connection
      }
      getupdate=true;
      //button_long_pressed_state[i] = false;
    }
    //double long click 
    if (button_double_long_pressed_state[i] && millis() > lastPost_longpress[i] + postingInterval_longpress){
      if (WiFi.status() == WL_CONNECTED) {
        lastPost_longpress[i] = millis();
        HTTPClient http;  //Object of class HTTPClient
        http.begin(host_address + change_state_address + OH_post_item_name_string[i]);
        //if (bitRead(light_state, i)){
        //   httpCode_send = http.POST("OFF");
        //  }
        //  else {
        //    httpCode_send = http.POST("ON");
        //  }

        httpCode_send = http.POST("LONG_DOUBLE_PRESSED");
        //Check the returning code                                                                  
        if (httpCode_send > 0) {
          // Get the request response payload
          //String payload = http.getString();
          // TODO: Parsing
          Serial.println("POST message succes");
            
        }
        http.end();   //Close connection
      }
      getupdate=true;
      //button_double_long_pressed_state[i] = false;
    }


     
  }

  //Serial.println("write to led");
  /*for (int i = 0; i < 8; i++){
    digitalWrite(LED[i], light_state[i]);
  }*/
  

  
}
