void write2EEprom() {

  if ( (123==EEPROM.read(0)) && (segment_middle==EEPROM.read(1)) && (segment_ss_width==EEPROM.read(2)) && (segment_brightness==EEPROM.read(3)) ) {
    // No need to write to EEprom, data is the same
  } else {

    EEPROM.write(0, 123);
    EEPROM.write(1, segment_middle);
    EEPROM.write(2, segment_ss_width);
    EEPROM.write(3, segment_brightness);
    updateSaved2Eeprom = true;

    // Blink twice and return to old value.
    long first_pixel = strip.getPixelColor(0);
    long last_pixel = strip.getPixelColor(NUMPIXELS - 1);
    strip.setPixelColor(0, 0 );
    strip.setPixelColor(NUMPIXELS - 1, 0 );
    strip.show();
    delay(50);
    strip.setPixelColor(0, 0xFF000000 );
    strip.setPixelColor(NUMPIXELS - 1, 0xFF000000 );
    strip.show();
    delay(50);
    strip.setPixelColor(0, 0 );
    strip.setPixelColor(NUMPIXELS - 1, 0 );
    strip.show();
    delay(50);
    strip.setPixelColor(0, 0xFF000000 );
    strip.setPixelColor(NUMPIXELS - 1, 0xFF000000 );
    strip.show();
    delay(50);
    strip.setPixelColor(0, first_pixel );
    strip.setPixelColor(NUMPIXELS - 1, last_pixel );
    strip.show();

    Serial.println(">>>>>>>>>>>>>>>>>>>.Saved to eeprom!<<<<<<<<<<<<<<<");
  }

}
