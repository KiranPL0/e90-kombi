#include <commands.h>
#include <CAN.h>

void sendParkingBreak(bool state){
    if (state) {
        // parking break ON
        CAN.beginPacket(0x34F);

        CAN.write(0xFE);
        CAN.write(0xFF);

        CAN.endPacket();
    }else{
        CAN.beginPacket(0x34F);
        
        CAN.write(0xFD);
        CAN.write(0xFF);

        CAN.endPacket();

    }
}