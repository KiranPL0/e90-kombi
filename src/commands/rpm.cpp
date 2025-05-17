#include <commands.h>
#include <CAN.h>
#define lo8(x) (uint8_t)((x)&0xff)
#define hi8(x) (uint8_t)(((x) >> 8) & 0xff)

void sendRPM(uint16_t rpm)
{
 uint16_t tempRpm = rpm * 4;


 CAN.beginPacket(0x0AA);


 CAN.write(0xFE);
 CAN.write(0xFE);
 CAN.write(0xFF);
 CAN.write(0x00);
 CAN.write(lo8(tempRpm));
 CAN.write(hi8(tempRpm));
 CAN.write(0xFE);
 CAN.write(0x99);


 CAN.endPacket();
}
