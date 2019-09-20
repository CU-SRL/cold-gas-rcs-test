#include <ButtonLib.h>

#include <HX711.h>

// HX711 library: https://github.com/bogde/HX711
// this is also in the lib manager - authors Bogdan Necula, Andreas Motl

//#define calibration_factor 386050.00 // kg
#define calibration_factor 421.0 //g

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

#define BUTTON_PIN 8
#define SOLENOID_PIN 12

#define OPEN_TIME 5000
#define CLOSE_TIME 10000

HX711 loadCell;
Button button(BUTTON_PIN);

unsigned long startTime;
unsigned long now;

void setup() {
  Serial.begin(115200);
  button.begin();
  pinMode(SOLENOID_PIN, OUTPUT);
  closeSolenoid();
  loadCell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadCell.set_scale(calibration_factor);
  loadCell.tare(); // zero at startup
  Serial.println("Waiting for start signal");
  while(button.getState()){
    //Serial.println(button.getState());
  } // button is pulled LOW when pressed.
  startTime = millis();
  Serial.print("Start: ");
  Serial.println(startTime);
}

void loop() {
  now = millis();
  logLoad();
  if(now - startTime >= OPEN_TIME){
    if(now - startTime >= CLOSE_TIME){
      closeSolenoid();
    }else {
      openSolenoid();
    }
  }
  
}

void openSolenoid(){
  // example output: t:<milliseconds> SO
  Serial.print("t:");
  Serial.print(millis() - startTime);
  Serial.println(" SO");
  digitalWrite(SOLENOID_PIN, HIGH);
}

void closeSolenoid(){
  // example output: t:<milliseconds> SC
  Serial.print("t:");
  Serial.print(millis() - startTime);
  Serial.println(" SC");
  digitalWrite(SOLENOID_PIN, LOW);
}

void logLoad(){
  // example output: t:<milliseconds> L<loadcellvalue>
  float valInNewtons = loadCell.get_units()*9.81/1000;
  Serial.print("t:");
  Serial.print(millis() - startTime);
  Serial.print(" L");
  Serial.print(valInNewtons, 3); //returns a float. 2nd param is # of decimal places to display/record. In grams the 1st dec is definitely unreliable. 
  Serial.println(" N");
}

