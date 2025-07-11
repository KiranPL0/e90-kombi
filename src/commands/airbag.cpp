#include <commands.h>
#include <CAN.h>


void sendAirbagSeatbeltCounter()
{
 static uint8_t count = 0x00;


 CAN.beginPacket(0x0D7);


 CAN.write(count);
 CAN.write(0xFF);


 CAN.endPacket();


 count++;
}
