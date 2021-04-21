#include "ReedSwitch.h"

ReedSwitch :: ReedSwitch(){
    pinMode(SWITCH_1, INPUT_PULLUP);
    pinMode(SWITCH_2, INPUT_PULLUP);
    pinMode(SWITCH_3, INPUT_PULLUP);
    pinMode(SWITCH_4, INPUT_PULLUP);

    pinMode(PUMP, OUTPUT);
    pinMode(VALVE, OUTPUT);
    digitalWrite(PUMP, LOW);
    digitalWrite(VALVE, LOW);
}

void ReedSwitch :: loopSwitch(){
    timer();
    if(hasTimePassed){
    getSwitchRead();
    processData();
    }
    hasTimePassed = false;
}

void ReedSwitch :: timer(){
    if((millis() - timeSinceLastRead) >= TIME){
        hasTimePassed = true;
        timeSinceLastRead = millis();    
    }
}

void ReedSwitch :: getSwitchRead(){
    for(int i = 0; i < 4; i++){
        if(!digitalRead(switchs[i])){
            switchState[i] = true;
        } else{
            switchState[i] = false;
        }
    }
}

void ReedSwitch :: processData(){
    printOnSerial();

    if(!switchState[0] && !switchState[1] && !switchState[2] && !switchState[3]){
        Serial.println("Valve activated");
        activateValve();
    }
    if(!switchState[0] && !switchState[1] && !switchState[2] && isValveActivated == false){
        Serial.println("Pump activated");
        activatePump();
    }
    if(isValveActivated && !switchState[2] == false){
        Serial.println("Valve deactivated");
        deactivateValve();
    }
    if(isPumpActivated && !switchState[0] == false){
        Serial.println("Pump deactivated");
        deactivatePump();
    }
}

void ReedSwitch :: activatePump(){
    digitalWrite(PUMP, HIGH);
    isPumpActivated = true;
}

void ReedSwitch :: activateValve(){
    digitalWrite(VALVE, HIGH);
    isValveActivated = true;
}

void ReedSwitch :: deactivatePump(){
    digitalWrite(PUMP, LOW);
    isPumpActivated = false;
}

void ReedSwitch :: deactivateValve(){
    digitalWrite(VALVE, LOW);
    isValveActivated = false;
}

void ReedSwitch :: printOnSerial(){
    Serial.println("The valve levels are:");
    for(int i = 0; i < 4; i++){
        Serial.println(String(i) + ": " + switchState[i]);
    }
    Serial.println("---------------------");
}

ReedSwitch reedSwitch;