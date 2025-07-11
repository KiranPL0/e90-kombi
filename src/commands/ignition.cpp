#include <commands.h>
#include <CAN.h>


void sendIgnitionKeyOn()
{
 CAN.beginPacket(0x130);


 CAN.write(0x45);
 CAN.write(0x40);
 CAN.write(0x21);
 CAN.write(0x8F);
 CAN.write(0xFE);


 CAN.endPacket();
}


void sendIgnitionStatus()
{
 CAN.beginPacket(0x26E);


 CAN.write(0x40);
 CAN.write(0x40);
 CAN.write(0x7F);
 CAN.write(0x50);
 CAN.write(0xFF);
 CAN.write(0xFF);
 CAN.write(0xFF);
 CAN.write(0xFF);


 CAN.endPacket();
}


