#include <Arduino.h>

void sendRPM(uint16_t rpm);
void sendSpeed(uint16_t input_speed);
void sendParkingBreak(bool state);
void sendClock(int hour, int minute);
void sendAbs();
void sendAbsCount();
void sendTireSpeed(int rawspeed);
void updateTurnSignal(bool left, bool indicator);
void runTurnSignal();
void sendLights(int exterior_lighting_type, int interior_lighting_type);
void sendGear(int gear, bool manual = false, int manualgear = 0, bool sport = false);
void activateCruiseControl(int vehicle_speed);
void disengageCruiseControl();
void sendFuelLevel(int percent);
void sendTripInformation(int averagelitres, int range, int fuelpercentage);
void sendTrunkStatus(bool opened);