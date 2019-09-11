#include <ButtonLib.h>

/*
 * This sketch turns the solenoid on and off at a button press. 
 * The default button setting used here is default HIGH, so 
 * pressing the button pulls it LOW and the actual event triggers 
 * on the following rising edge. 
 * 
 * Note that immediately after the rising edge, the solenoid shuts off... 
 * 
 * This was tested on 9/8/2019 with a relay instead of a
 * solenoid and a 2N4401 NPN transistor with 2 1k resistors 
 * for the voltage divider values (R1 and R2 in the schematic)
 * 
 * The button was simply a jumper wire that we connected and disconnect
 * to ground. 
 * 
 */

// this pin is attached to the base pin of the transistor that's driving the solenoid
int solenoidPin = 10;
int buttonPin = 8; 
boolean solenoidState = false; // 0 = closed, 1 = open
Button toggleButton(buttonPin);

void setup() {
  pinMode(solenoidPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  boolean pressed = toggleButton.isPressed();
  Serial.println(pressed);
  if(pressed){
    digitalWrite(solenoidPin, HIGH);    
  } else {
    digitalWrite(solenoidPin, LOW);
  }
  delay(100);

}
