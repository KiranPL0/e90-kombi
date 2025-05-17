#include <commands.h>
#include <CAN.h>

void sendTrunkStatus(bool opened){
    CAN.beginPacket(0x0F2);
    if (opened){
        CAN.write(0xF1);
        CAN.write(0xFF);
        CAN.write(0x87);
        CAN.write(0xC1);
        CAN.write(0xFF);
        CAN.write(0xFF);
        CAN.write(0xFF);
        CAN.write(0xFF);
    }
}

// code doesnt WORK