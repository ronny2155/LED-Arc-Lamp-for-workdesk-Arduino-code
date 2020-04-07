void updateEncoder() {
  int MSB = digitalRead(ROTARY_PIN1); //MSB = most significant bit
  int LSB = digitalRead(ROTARY_PIN2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum = (lastEncoded[input_mode] << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue[input_mode] --;
    directionUp = false;
  }

  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue[input_mode] ++;
    directionUp = true;
  }

  lastEncoded[input_mode] = encoded; //store this value for next time }

  // Update relevant variant
  if (input_mode == 0) {
    segment_middle = min( max( 0 , encoderValue[input_mode] ) , NUMPIXELS-1 );
    encoderValue[input_mode] = segment_middle;
  } else if (input_mode == 1) {
    segment_ss_width = min( max(0,encoderValue[input_mode]), 255 );
    encoderValue[input_mode] = segment_ss_width;
  } else if (input_mode == 2) {
    segment_brightness = min( max(MIN_BRIGHTNESS,encoderValue[input_mode]), MAX_BRIGHTNESS );
    encoderValue[input_mode] = segment_brightness;
  }

  encoderMovementTimer = millis();
  updateSaved2Eeprom = false;

}
