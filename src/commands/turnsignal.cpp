#include <commands.h>
#include <CAN.h>

bool left_signal_internal = false;
bool right_signal_internal = false;

void leftSignalInit(){
    CAN.beginPacket(0x1F6);

    CAN.write(0x91);
    CAN.write(0xF2);

    CAN.endPacket();
    left_signal_internal = true;
}

void rightSignalInit(){
    CAN.beginPacket(0x1F6);
    
    CAN.write(0xA1);
    CAN.write(0xF2);

    CAN.endPacket();
    right_signal_internal = true;
}



void runTurnSignal(){
    if (left_signal_internal){
        CAN.beginPacket(0x1F6);

        CAN.write(0x91);
        CAN.write(0xF1);

        CAN.endPacket();
    }

    if (right_signal_internal){
        CAN.beginPacket(0x1F6);

        CAN.write(0xA1);
        CAN.write(0xF1);

        CAN.endPacket();
    }
}

void signalOff(){
    left_signal_internal = false;
    right_signal_internal = false;

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
            left_signal_internal = false;
        }
    }else{
        if (indicator){
            rightSignalInit();
        }else{
            right_signal_internal = false;
        }
    }

    if (!left_signal_internal && !right_signal_internal){
        signalOff();
    }
}
