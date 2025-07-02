#include <commands.h>
#include <CAN.h>

uint16_t byte2 = 0xB3;

void sendAbs(){

    byte2 = ((((byte2 >> 4) + 3) << 4) & 0xF0) | 0x03;
    CAN.beginPacket(0x19E);

    CAN.write(0x00);
    CAN.write(0xE0);
    CAN.write(byte2);
    CAN.write(0xFC);
    CAN.write(0xF0);
    CAN.write(0x43);
    CAN.write(0x00);
    CAN.write(0x65);

    CAN.endPacket();
    
}

// void sendAbs(){

//     byte2 = ((((byte2 >> 4) + 3) << 4) & 0xF0) | 0x03;
//     CAN.beginPacket(0x19E);

//     CAN.write(0x00);
//     CAN.write(0xE0);
//     CAN.write(byte2);
//     CAN.write(0xFC);
//     CAN.write(0xF0);
//     CAN.write(0x43);
//     CAN.write(0x31);
//     CAN.write(0x65);

//     CAN.endPacket();
    
// }



void sendAbsCount(){
    static uint8_t lower = 0;
    CAN.beginPacket(0x0C0);
    // Serial.println(0xF0 | (lower & 0x0F));
    CAN.write(0xF0 | (lower & 0x0F));
    CAN.write(0xFF);
    
    CAN.endPacket();

    lower = (lower + 1) & 0x0F;

}