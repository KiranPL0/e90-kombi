#include <commands.h>
#include <CAN.h>


const uint32_t CAN_BUS_ID = 0x1A6;

uint8_t speedFrame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0};

uint16_t lastSpeed = 0;

void sendSpeed(uint16_t input_speed)
{
    uint16_t speed = input_speed + lastSpeed;

    uint16_t counter = (speedFrame[6] | (speedFrame[7] << 8));
    counter += 315;

    speedFrame[0] = speed;
    speedFrame[1] = (speed >> 8);
    speedFrame[2] = speedFrame[0];
    speedFrame[3] = speedFrame[1];
    speedFrame[4] = speedFrame[0];
    speedFrame[5] = speedFrame[1];
    speedFrame[6] = counter;
    speedFrame[7] = ((counter >> 8) | 0xF0);

    CAN.beginPacket(0x1A6);
    CAN.write(speedFrame[0]);
    CAN.write(speedFrame[1]);
    CAN.write(speedFrame[2]);
    CAN.write(speedFrame[3]);
    CAN.write(speedFrame[4]);
    CAN.write(speedFrame[5]);
    CAN.write(speedFrame[6]);
    CAN.write(speedFrame[7]);

    CAN.endPacket();
    lastSpeed = speed;
}