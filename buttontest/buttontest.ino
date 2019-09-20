#include <ButtonLib.h>

#define BUTTON_PIN 8

Button button(BUTTON_PIN);

void setup() {
  button.begin();
  Serial.begin(9600);
}

void loop() {
  Serial.print("getState(): ");
  Serial.print(button.getState());
  Serial.print("  isPressed(): ");
  Serial.print(button.isPressed());
  Serial.print("  isHeld(1000): ");
  Serial.print(button.isHeld(1000));
  Serial.print("  isReleased(): ");
  Serial.print(button.isReleased());
  Serial.print("  stateChanged(): ");
  Serial.print(button.stateChanged());
  Serial.println("");
  delay(100);
}
