void pongMode(){
  
  shootBall( pongDirection , SNAKE_SIZE , pongStepSize , pongDelayMsec );
  if ( digitalRead(ROTARY_BTN) == 0 ) {
    
    pongDirection = !pongDirection;
    
    if ( pongDelayMsec>0 ) {
      pongDelayMsec--;
    } else {
      pongStepSize+=0.1;
    }
  } else {
    pong_mode = false;
    rotaryBtnPressedTimer = 2147483647; // max signed long
    pongDirection = false;
    pongDelayMsec = PONG_INIT_DELAY_MSEC;
    pongStepSize = PONG_INIT_STEP_SIZE;
    input_mode = 0;
  }
  


  
}
