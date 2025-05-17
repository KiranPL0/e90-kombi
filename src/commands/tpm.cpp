#include <commands.h>
#include <CAN.h>

void sendTireSpeed(int vehicle_speed){
    int rawspeed = vehicle_speed * 24;
     
    int fl = rawspeed;
    int fr = rawspeed + 2;
    int rl = rawspeed + 2;
    int rr = rawspeed - 1;

    // Serial.println(rawspeed);
    // Serial.println(fl & 0xFF);
    // Serial.println((fl >> 8) & 0xFF);

    CAN.beginPacket(0x0CE);

    CAN.write(fl & 0xFF);
    CAN.write((fl >> 8) & 0xFF);
    CAN.write(fr & 0xFF);
    CAN.write((fr >> 8) & 0xFF);
    CAN.write(rl & 0xFF);
    CAN.write((rl >> 8) & 0xFF);
    CAN.write(rr & 0xFF);
    CAN.write((rr >> 8) & 0xFF);

    CAN.endPacket();

}