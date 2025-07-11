#include <commands.h>
#include <CAN.h>

uint8_t rollingCounter = 0;

void sendGear(int gear, bool manual = false, int manualgear = 0, bool sport = false){
    uint8_t shiftleverposition = 0x08; // we default in D in case
    switch(gear){
        case 1:
        //park
        shiftleverposition = 0x01;
        break;
        case 2:
        // reverse
        shiftleverposition = 0x02;
        break;
        case 3:
        // neutral
        shiftleverposition = 0x04;
        break;
        case 4:
        // drive
        shiftleverposition = 0x08;
        break;

    }

    

    CAN.beginPacket(0x1D2);
    CAN.write((shiftleverposition & 0x0F) | ((shiftleverposition ^ 0x0F) & 0x0F) << 4);
    if (manual == false){
        CAN.write(0x0B);
    }else{
        CAN.write(((manualgear /* gear */ + 4) & 0x0F) << 4);
    }
    CAN.write(0x00);
    uint8_t byte3 = (rollingCounter << 4) & 0xF0;
    CAN.write(byte3);
    if (manual == false && sport == false){
        CAN.write(0x00);
    }else if (sport)
    {
        CAN.write(0x01);
    }else{
        CAN.write(0x02);
    }
    
    CAN.write(0xFF);
    CAN.endPacket();
    rollingCounter++;
    if (rollingCounter > 14){
        rollingCounter = 0;
    }
}