#include <commands.h>
#include <CAN.h>
#define lo8(x) (uint8_t)((x)&0xff)
#define hi8(x) (uint8_t)(((x) >> 8) & 0xff)



void sendClock(int hour, int minute){
    CAN.beginPacket(0x39E);
    CAN.write(hour); // hour
    CAN.write(minute); // min
    CAN.write(0); // second
    CAN.write(0x0D); // day
    CAN.write(0x5F); // 1F = jan (month)
    CAN.write(lo8(2025)); // year low
    CAN.write(hi8(2025)); // year high
    CAN.write(0xF2); // static
    CAN.endPacket();
}