void detectPongMode() {

  rotaryBtnDown = !digitalRead(ROTARY_BTN);

  if ( ( true == rotaryBtnDown ) && ( false ==  lastRotaryBtnDown) ) {
    rotaryBtnPressedTimer = millis();
  }

  if ( ( false == rotaryBtnDown ) ) {
    rotaryBtnPressedTimer = 2147483647; // max signed long
  }

  if ( ( true == rotaryBtnDown ) && ( (millis() - rotaryBtnPressedTimer) > PONG_TIME_MSEC ) ) {    
    boolean onlyLeftLEDon = true;     
    for (int k = 0 ; k < (NUMPIXELS-1) ; k++) {
      onlyLeftLEDon = ( onlyLeftLEDon ) && !boolean(strip.getPixelColor(k));
      Serial.println( onlyLeftLEDon );
    }
    onlyLeftLEDon = ( onlyLeftLEDon ) && boolean(strip.getPixelColor(NUMPIXELS-1));
    Serial.println( onlyLeftLEDon );

    if ( true == onlyLeftLEDon ) {
      pong_mode = true;
    }

  }

  lastRotaryBtnDown = rotaryBtnDown;
}
