#ifndef Reed_Switch
#define Reed_Switch

#include "Arduino.h"

#define SWITCH_1 12
#define SWITCH_2 8
#define SWITCH_3 7
#define SWITCH_4 4

#define PUMP 11
#define VALVE 6

#define TIME 1000

class ReedSwitch{
    public:
    void loopSwitch();
    ReedSwitch();

    private:
    void timer();
    void getSwitchRead();
    void processData();
    void activatePump();
    void activateValve();
    void deactivatePump();
    void deactivateValve();
    void printOnSerial();

    bool hasTimePassed = false;
    bool isPumpActivated = false;
    bool isValveActivated = false;
    bool switchState[4] = {false, false, false, false};

    int switchs[4] = {12, 8, 7, 4};

    unsigned long timeSinceLastRead = 0;
};

extern ReedSwitch reedSwitch;
#endif