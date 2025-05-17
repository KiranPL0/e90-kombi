#include <commands.h>
#include <CAN.h>

uint8_t cruisetimer = 0;
void activateCruiseControl(int vehicle_speed){
    
    cruisetimer += 17;
    CAN.beginPacket(0x193);
    CAN.write(cruisetimer);
    CAN.write(vehicle_speed * 0.621371); // speed in KM/H --> MPH
    CAN.write(0xF5);
    CAN.write(0x00);
    CAN.write(0xF8);
    CAN.write(0x58);
    CAN.write(0x00);
    CAN.write(0x00);

    CAN.endPacket();

}

void disengageCruiseControl(){
    CAN.beginPacket(0x193);
    CAN.write(0x27);
    CAN.write(0xFE);
    CAN.write(0xF1);
    CAN.write(0x00);
    CAN.write(0xF8);
    CAN.write(0x50);
    CAN.write(0x00);
    CAN.write(0x00);
}