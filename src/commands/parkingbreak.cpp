#include <commands.h>
#include <CAN.h>

void sendParkingBreak(bool state){
    if (state) {
        // parking break ON
        CAN.beginPacket(0x34F);

        CAN.write(0xFE);
        CAN.write(0xFF);

        CAN.endPacket();
        // CAN.beginPacket(436);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0b01000000);
        // CAN.write(0x00);
        // CAN.write(0x00);
    }else{
        CAN.beginPacket(0x34F);
        
        CAN.write(0xFD);
        CAN.write(0xFF);

        CAN.endPacket();
        // CAN.beginPacket(436);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0x00);
        // CAN.write(0b00000000);
        // CAN.write(0x00);
        // CAN.write(0x00);

    }
}