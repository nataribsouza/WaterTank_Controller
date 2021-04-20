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

void ReedSwitch :: run(){
    timer();
    if(hasTimePassed){
    getSwitchRead();
    }
    processData();
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
    if(switchs[0] && switchs[1] && switchs[2] && switchs[3]){
        activateValve();
    }
    if(switchs[0] && switchs[1] && switchs[2] && isValveActivated == false){
        activatePump();
    }
    if(isValveActivated && switchs[2] == false){
        deactivateValve();
    }
    if(isPumpActivated && switchs[0] == false){
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

ReedSwitch reedSwitch;