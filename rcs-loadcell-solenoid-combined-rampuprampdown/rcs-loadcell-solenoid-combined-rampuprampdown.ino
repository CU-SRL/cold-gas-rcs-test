#include <HX711.h>

// HX711 library: https://github.com/bogde/HX711
// this is also in the lib manager - authors Bogdan Necula, Andreas Motl

//#define calibration_factor 386050.00 // kg
#define calibration_factor 421.0 //g
//I calibrated this using random stuff i had lying around (207g battery pack, 120g solenoid, 3kg metal stock)
//it's not great. I'm also wondering if we should calibrate it using known loads that are close to what we expect to be measuring?

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

#define SOLENOID_PIN 12

#define OPEN_TIME 5000
#define CLOSE_TIME 10000

HX711 loadCell;
void setup() {
  Serial.begin(115200);
  pinMode(SOLENOID_PIN, OUTPUT);
  loadCell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadCell.set_scale(calibration_factor);
  loadCell.tare(); // zero at startup
  //while(!button){}
  unsigned long startTime = millis();
}

void loop() {
  unsigned long t = millis();
  logLoad();
  if(startTime - t == OPEN_TIME){
     openSolenoid();
  } else if(startTime - t == CLOSE_TIME){
     closeSolenoid();
  }
  
}

void openSolenoid(){
  // example output: t:<milliseconds> SO
  Serial.print("t:");
  Serial.print(millis());
  Serial.println(" SO");
  digitalWrite(SOLENOID_PIN, HIGH);
}

void closeSolenoid(){
  // example output: t:<milliseconds> SC
  Serial.print("t:");
  Serial.print(millis());
  Serial.print(" SC");
  digitalWrite(SOLENOID_PIN, LOW);
}

void logLoad(){
  // example output: t:<milliseconds> L<loadcellvalue>
  int valInNewtons = loadCell.get_units()*9.81/1000;
  unsigned long t = millis(); // 4 bytes
  Serial.print("t:");
  Serial.print(millis());
  Serial.print(" L");
  Serial.print(valInNewtons, 3); //returns a float. 2nd param is # of decimal places to display/record. In grams the 1st dec is definitely unreliable. 
  //Serial.println(" N"); //You can change this to kg but you'll need to refactor the calibration_factor
}

