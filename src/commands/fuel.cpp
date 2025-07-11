#include <commands.h>
#include <CAN.h>
#define lo8(x) (uint8_t)((x)&0xff)
#define hi8(x) (uint8_t)(((x) >> 8) & 0xff)



void sendFuelLevel(int percent){
    uint16_t sensor = static_cast<uint16_t>(percent * 160);


    CAN.beginPacket(0x349);


    CAN.write(lo8(sensor));
    CAN.write(hi8(sensor));
    CAN.write(lo8(sensor));
    CAN.write(hi8(sensor));
    CAN.write(0x00);


    CAN.endPacket();

}
