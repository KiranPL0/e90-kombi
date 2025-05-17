#include <commands.h>
#include <CAN.h>

bool left_signal = false;
bool right_signal = false;

void leftSignalInit(){
    CAN.beginPacket(0x1F6);

    CAN.write(0x91);
    CAN.write(0xF2);

    CAN.endPacket();
    left_signal = true;
}

void rightSignalInit(){
    CAN.beginPacket(0x1F6);
    
    CAN.write(0xA1);
    CAN.write(0xF2);

    CAN.endPacket();
    right_signal = true;
}



void runTurnSignal(){
    if (left_signal){
        CAN.beginPacket(0x1F6);

        CAN.write(0x91);
        CAN.write(0xF1);

        CAN.endPacket();
    }

    if (right_signal){
        CAN.beginPacket(0x1F6);

        CAN.write(0xA1);
        CAN.write(0xF1);

        CAN.endPacket();
    }
}

void signalOff(){
    left_signal = false;
    right_signal = false;

    CAN.beginPacket(0x1F6);

    CAN.write(0x80);
    CAN.write(0xF0);

    CAN.endPacket();
}


void updateTurnSignal(bool left, bool indicator){
    if (left){
        if (indicator){
            // left turn ON
            leftSignalInit();
        }else{
            signalOff();
        }
    }else{
        if (indicator){
            rightSignalInit();
        }else{
            signalOff();
        }
    }
}
