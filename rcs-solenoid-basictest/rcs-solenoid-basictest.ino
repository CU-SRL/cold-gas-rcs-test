/*
 * This sketch simply turns the solenoid on and off  
 * at 1 second intervals.
 * 
 * This was tested on 9/8/2019 with a relay instead of a
 * solenoid and a 2N4401 NPN transistor with 2 1k resistors 
 * for the voltage divider values (R1 and R2 in the schematic)
 * 
 */

// this pin is attached to the base pin of the transistor that's driving the solenoid
int solenoidPin = 12; 
int delayVal = 1000; // 1000 ms = 1 sec

void setup() {
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  digitalWrite(solenoidPin, HIGH);
  delay(delayVal);
  digitalWrite(solenoidPin, LOW);
  delay(delayVal);
}
