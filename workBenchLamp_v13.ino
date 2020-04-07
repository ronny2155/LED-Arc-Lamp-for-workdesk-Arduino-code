// Ver 1.3
// float step size for pong snake

// LED Strip related:
#include <Adafruit_NeoPixel.h>
#define             NEO_PIN         (9)  // NeoPixel DATA
#define             NEO_PTYPE       NEO_GRBW  // f.e. SK6812
#define             NUMPIXELS       (169)
#define             BRIGHTNESS      (255) // set max brightness - library
#define             MIN_BRIGHTNESS  (20) // 
#define             MAX_BRIGHTNESS  (255)// set max brightness in rz code
Adafruit_NeoPixel   strip = Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_PTYPE + NEO_KHZ800);

// StateMachine and UX Related
#include <EEPROM.h>
boolean         updateSaved2Eeprom =      false;
byte            segment_middle =          70; // middle of the segment at unfolded mode
byte            segment_ss_width =        21;// single-sided width of segment at unfolded mode
byte            segment_brightness =      255; // bightness at unfolded mode
int             input_mode =              0; // 0-middle, 1-width, 2-brigtness
boolean         pong_mode =               false;

// Rotary encoder related
#define       ROTARY_PIN1             (2)
#define       ROTARY_PIN2             (3)
#define       ROTARY_BTN              (5)
volatile int  lastEncoded[] =         {0, 0, 0};
volatile long encoderValue[] =        {segment_middle, segment_ss_width, segment_brightness};
long          lastencoderValue[] =    {0, 0, 0};
int           lastMSB[] =             {0, 0, 0};
int           lastLSB[] =             {0, 0, 0};
boolean       directionUp =           true;

boolean rotaryBtnDown =                 false;
boolean lastRotaryBtnDown =                 false;

// Timers
long rotaryBtnDebounceTimer =           millis();
#define ROTARY_BTN_DEBOUNCE_TIME_MSEC   (150)
long encoderMovementTimer =             millis();
#define EEPROM_WRITE_TIME_MSEC          (5000)
long rotaryBtnPressedTimer =             millis();
#define PONG_TIME_MSEC                  (5000)

// Pong easter egg related
#define SNAKE_SIZE (10)
#define PONG_INIT_DELAY_MSEC (6)
#define PONG_INIT_STEP_SIZE   (1.0)

int pongDelayMsec = 6;
float pongStepSize = 1.0;
bool pongDirection = false;

// Supply voltage sensing related
#define SENSE_PIN (A0)      // evebtually not used, kept in code sinse physical connection is there.

void setup() {
  pinMode(ROTARY_PIN1, INPUT_PULLUP);
  pinMode(ROTARY_PIN2, INPUT_PULLUP);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  pinMode(ROTARY_BTN, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("WorkBench LED Lamp - unit test");

  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(BRIGHTNESS); // set brightness
  strip.show(); // Initialize all pixels to 'off'

  if ( EEPROM.read(0) == 123 ) {
    segment_middle = EEPROM.read(1);
    segment_ss_width = EEPROM.read(2);
    segment_brightness = EEPROM.read(3);
    encoderValue[0] = segment_middle;
    encoderValue[1] = segment_ss_width;
    encoderValue[2] = segment_brightness;
    updateSaved2Eeprom = true;
  } else {
    EEPROM.write(0, 123);
    EEPROM.write(1, segment_middle);
    EEPROM.write(2, segment_ss_width);
    EEPROM.write(3, segment_brightness);
    Serial.println("Saved to eeprom!");
  }
}

void loop() {
  if ( true == pong_mode ) {
    pongMode();
  } else {
    detectPongMode();

    if (  ( digitalRead(ROTARY_BTN) == 0 ) &&  ( (millis() - rotaryBtnDebounceTimer) > ROTARY_BTN_DEBOUNCE_TIME_MSEC ) ) {
      rotaryBtnDebounceTimer = millis();
      encoderMovementTimer = millis();
      input_mode = (input_mode + 1) % 3 ;
    }

    if ( ((millis() - encoderMovementTimer) > EEPROM_WRITE_TIME_MSEC) && ( false == updateSaved2Eeprom ) ) {
      write2EEprom();
    }

    updateStrips();
    delay(10);

    Serial.print("[ ");
    Serial.print("input mode: ");
    Serial.print(input_mode);
    Serial.print(" , ");
    Serial.print(" Rotary btn: ");
    Serial.print(digitalRead(ROTARY_BTN));
    Serial.print(" , ");
    Serial.print(" Encoder Value: ");
    Serial.print(encoderValue[0]);
    Serial.print(" , ");
    Serial.print(" Segment middle: ");
    Serial.print(segment_middle);
    Serial.print(" , ");
    Serial.print(" Stop-Start width ");
    Serial.print(segment_ss_width);
    Serial.print(" , ");
    Serial.print(" Brightness: ");
    Serial.print(segment_brightness);
    Serial.print(" , ");
    Serial.print(" DirectionUp: ");
    Serial.print(directionUp);
    Serial.print(" , ");
    Serial.print(" Supply: ");
    Serial.print(analogRead( SENSE_PIN ));
    Serial.print(" , ");
    Serial.println(" ]");
  }
}
