#include <commands.h>
#include <CAN.h>

void sendLights(int exterior_lighting_type, int interior_lighting_type){
    
    CAN.beginPacket(0x21A);


    switch(exterior_lighting_type){
        case 0:
        //all lights off
        CAN.write(0b00000000);
        break;
        case 1:
        // brake light only
        CAN.write(0b10000000);
        break;
        case 2:
        CAN.write(0b00000100);
        break;
        case 3:
        // dip beam only
        CAN.write(0b00000101);
        break;
        case 4:
        // main beam only -> high beam
        CAN.write(0b00000111);
        break;
        case 5:
        // front fog lamps
        CAN.write(0b00100101);
        break;
        case 6:
        // rear fog lamps
        CAN.write(0b01000101);
        break;

    }

    switch(interior_lighting_type){
        case 0:
        // all lights off
        CAN.write(0b00000000);
        break;
        case 1:
        // tail reverse lights (reversing)
        CAN.write(0b00000001);
        break;
        case 2:
        // main interior light is on
        CAN.write(0b00010000);
        break;
        case 3:
        // interior light and exterior light is on
        CAN.write(0b00010010);
        break;
    }

    CAN.endPacket();
}