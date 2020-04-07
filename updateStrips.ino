void updateStrips() {

  // first, clearing the strips
  for (int k = 0 ; k < NUMPIXELS ; k++) {
    strip.setPixelColor(k, 0 );
  }

  for (int k = 0 ; k < NUMPIXELS ; k++) {
    if ( ( k >= ((int)segment_middle - (int)segment_ss_width) ) && ( k <= ((int)segment_middle + (int)segment_ss_width)  ) ) {      
        strip.setPixelColor(k, ((long)segment_brightness) << 24 );
        strip.setPixelColor(k, ((long)segment_brightness) << 24 );      
    }
  }

  strip.show();
}
