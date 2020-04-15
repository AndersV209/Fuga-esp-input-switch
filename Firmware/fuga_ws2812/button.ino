void button_handle(){
  // Go through each button and set the corresponding LED function
  for (int i=0; i<buttons; i++){
    // Update state of all buitton
    button[i].Update();
  
    // Save click codes in LEDfunction, as clicks counts are reset at next Update()
    if (button[i].clicks != 0){
      LEDfunction[i] = button[i].clicks;
      
    }
      //Serial.print("button ");
      //Serial.print(i);
      //Serial.print(" : ");
      //Serial.println(button[i].clicks);
      
    if(button[i].changed){
      

      // Simply toggle LED on single clicks
      // (Cant use LEDfunction like the others here,
      //  as it would toggle on and off all the time)
      if(button[i].clicks == 1){
        button_pressed_state[i] = true;
        //ledState[i] = !ledState[i];
      }
  
      // blink faster if double clicked
      if(LEDfunction[i] == 2){
        //ledState[i] = (millis()/500)%2;
        button_double_pressed_state[i] = true;
      }
  
      // blink even faster if triple clicked
      if(LEDfunction[i] == 3){
        //ledState[i] = (millis()/200)%2;
        button_triple_pressed_state[i] = true;
      }
  
      // slow blink (must hold down button. 1 second long blinks)
      if(LEDfunction[i] == -1){
        //ledState[i] = (millis()/1000)%2;
        button_long_pressed_state[i] = true;
      }
  
      // slower blink (must hold down button. 2 second loong blinks)
      if(LEDfunction[i] == -2){
        //ledState[i] = (millis()/2000)%2;
        button_double_long_pressed_state[i] = true;
      }
  
      // even slower blink (must hold down button. 3 second looong blinks)
      if(LEDfunction[i] == -3){
        //ledState[i] = (millis()/3000)%2;
        button_double_long_pressed_state[i] = true;
      }
    }//if(button[i].changed)
  
    if(button_long_pressed_state[i] == true || button_double_long_pressed_state[i] == true){
      if(digitalRead(button_pin[i]) == LOW){
        //Serial.println("button still pressed");
        //button_long_pressed_state[i] = true;
      }
      else{
        button_long_pressed_state[i] = false;
        button_double_long_pressed_state[i] = false;
      }
    }
    
  }

  
  
  
  }
