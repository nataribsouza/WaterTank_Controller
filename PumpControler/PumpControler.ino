#include "src/ReedSwitch.h"

void setup(){
  Serial.begin(9600);
}

void loop(){
  reedSwitch.run();
}
