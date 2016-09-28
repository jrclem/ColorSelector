/* File:    colorSelector.ino
 * By:      Jean René Clemenceau
 * Created: 09/23/2016
 * Controls 1 Adafruit Neopixels according to live values
 * 
 * Operation:
 * Press a color selection button to modify its color value.
 * Turn the potentiometer to select a color value.
 * Press the print button to print the values to the Serial connection.
*/
#include <Adafruit_NeoPixel.h>

//Set pins
const byte RED_BUTTON =  4; //Digital IO pin connected to the red button.
const byte GREEN_BUTTON =3; //Digital IO pin connected to the green button.
const byte BLUE_BUTTON = 2; //Digital IO pin connected to the blue button.
const byte PRINT_BUTTON =6; //Digital IO pin connected to the green button.

const byte PIXEL_PIN = 8;   //Digital IO pin connected to the vase's NeoPixel ring.
const byte KNOB_PIN = 0;    //ANALOG input pin connected to the potentiometer.

//Initialize NeoPixel
Adafruit_NeoPixel PIXEL = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800 );

//Declare color value variables
uint32_t red_val, green_val, blue_val;

int color_count = 0; //Counter for printed colors

/**Runs Once**/
void setup() {
  //Initialize Serial port
  Serial.begin(9600);
  
  //Initialize Pins
  pinMode(RED_BUTTON, INPUT_PULLUP); //(HIGH = unpressed, LOW = pressed)
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(PRINT_BUTTON, INPUT_PULLUP);
  pinMode(PIXEL_PIN, OUTPUT);

  // Initialize all Neopixels to 'off'
  PIXEL.begin();
  PIXEL.show(); 
  
  //Initialize color values
  red_val = 0;
  green_val = 0;
  blue_val = 0;

  color_count = 0; //Counter for printed colors
}

void loop() {
  bool red_state = digitalRead(RED_BUTTON);
  bool green_state = digitalRead(GREEN_BUTTON);
  bool blue_state = digitalRead(BLUE_BUTTON);
  bool print_state = digitalRead(PRINT_BUTTON);

  //Read value from knob
  int sensor_val = map(analogRead(KNOB_PIN),0,1023,0,255);

  //Apply knob values to the selected colors
  if(red_state == LOW){
    red_val = sensor_val;
  }
  if(green_state == LOW){
    green_val = sensor_val;
  }
  if(blue_state == LOW){
    blue_val = sensor_val;
  }

  //Send color settings to NeoPixel for display
  PIXEL.setPixelColor(0, PIXEL.Color(red_val,green_val,blue_val) );
  PIXEL.show();

  //If print button is pressed, output values to Serial
  if(print_state == LOW){
    Serial.print(++color_count);
    Serial.print(": R=");
    Serial.print(red_val);
    Serial.print(", G=");
    Serial.print(green_val);
    Serial.print(", B=");
    Serial.println(blue_val);
    delay(200);
  }
  
}


