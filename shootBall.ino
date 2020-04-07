void shootBall( boolean direction , int snakeSize , float stepSize , int dly) {

  int clr = ((int)random(0, 3)) * 8;

  int intensityCtr = 0;
  uint32_t intensity = 0;
  

  if ( direction == true ) {
    for ( float k = 0.0; k < NUMPIXELS ; k += stepSize ) {
      for (int m = (round(k) - stepSize - snakeSize) ; m < (round(k)- snakeSize) ; m++) {
        strip.setPixelColor(m, 0x00000000);        
      }
      for (int m = (round(k)- snakeSize) ; m < round(k); m++) {
        intensityCtr++;
        intensity = map( intensityCtr , 0, snakeSize, 0 , 127 );
        strip.setPixelColor(m, intensity << clr);
      }
      strip.show();
      delay(dly);
    }
  } else {
    for ( float k = NUMPIXELS - 1.0; k >= 0.0  ; k -= stepSize ) {
      for (int m = (ceil(k)+ stepSize + snakeSize) ; m >= (ceil(k)- snakeSize) ; m--) {
        strip.setPixelColor(m, 0x00000000);
      }

      intensityCtr = 0;
      intensity = 0;

      for (int m = (round(k)+ snakeSize) ; m >= round(k); m--) {
        intensityCtr++;
        intensity = map( intensityCtr , 0, snakeSize, 0 , 127 );
        strip.setPixelColor(m, intensity << clr);
      }
      strip.show();
      delay(dly);
    }
  }


  for ( int k = 0; k < NUMPIXELS ; k ++ ) {
    strip.setPixelColor(k, 0x00000000);
  }
  strip.show();



}
