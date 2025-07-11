#include <commands.h>
#include <CAN.h>

// the following code works, but is unused at this time - you may delete this file and delete the corresponding function in commands.h (located under /include/commands.h) to save on board flash storage


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