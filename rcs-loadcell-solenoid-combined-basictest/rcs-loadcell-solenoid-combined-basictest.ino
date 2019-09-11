#include <HX711.h>

// HX711 library: https://github.com/bogde/HX711
// this is also in the lib manager - authors Bogdan Necula, Andreas Motl

//#define calibration_factor 386050.00 // kg
#define calibration_factor 421.0 //g
//I calibrated this using random stuff i had lying around (207g battery pack, 120g solenoid, 3kg metal stock)
//it's not great. I'm also wondering if we should calibrate it using known loads that are close to what we expect to be measuring?

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

int solenoidPin = 12; 
int delayVal = 1000; // 1000 ms = 1 sec

HX711 loadCell;
void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  loadCell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadCell.set_scale(calibration_factor);
  loadCell.tare(); // zero at startup
}

void loop() {
  digitalWrite(solenoidPin, HIGH);
  logLoad();
  delay(delayVal);
  digitalWrite(solenoidPin, LOW);
  logLoad();
  delay(delayVal);

}

void logLoad(){
  Serial.print("Reading: ");
  Serial.print(loadCell.get_units(), 0); //returns a float. 2nd param is # of decimal places to display/record. In grams the 1st dec is definitely unreliable. 
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}

