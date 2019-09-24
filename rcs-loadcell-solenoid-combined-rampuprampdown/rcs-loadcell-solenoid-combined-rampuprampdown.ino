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
#define PULSES 3

HX711 loadCell;
Button button(BUTTON_PIN);

unsigned long startTime;
unsigned long now;
unsigned long trueStartTime;

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
  trueStartTime = startTime;
  Serial.print("Start: ");
  Serial.println(startTime);
}

void loop() {
  /*now = millis();
  logLoad();
  if(now - startTime >= OPEN_TIME){
    if(now - startTime >= CLOSE_TIME){
      closeSolenoid();
    }else {
      openSolenoid();
    }
  }*/
  for(int i = 0;i<PULSES;i++){
    while(millis()-startTime <= OPEN_TIME){
      logLoad();
    }
    openSolenoid();
    while(millis()-startTime <= CLOSE_TIME){
      logLoad();
    }
    closeSolenoid();
    startTime = millis();
  }
  int c = 0;
  while(c < 50){
    logLoad();
    c++;
  }
  while(1){};
}

void openSolenoid(){
  // example output: t:<milliseconds> SO
  digitalWrite(SOLENOID_PIN, HIGH);
}

void closeSolenoid(){
  // example output: t:<milliseconds> SC
  digitalWrite(SOLENOID_PIN, LOW);
}

void logLoad(){
  // example output: t:<milliseconds> L<loadcellvalue>
  float valInNewtons = loadCell.get_units()*9.81/1000;
  Serial.print(millis() - trueStartTime);
  Serial.print(",");
  Serial.print(digitalRead(SOLENOID_PIN));
  Serial.print(",");
  Serial.println(valInNewtons, 3); //returns a float. 2nd param is # of decimal places to display/record. In grams the 1st dec is definitely unreliable. 
}

