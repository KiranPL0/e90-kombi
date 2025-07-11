#include <CAN.h>
#include <commands.h>

#define lo8(x) (uint8_t)((x)&0xff)
#define hi8(x) (uint8_t)(((x) >> 8) & 0xff)


const uint8_t CS_PIN = 9; // assuming use of board defined in readme
const uint8_t IRQ_PIN = 2;



uint32_t timestamp100ms = 0;
uint32_t timestamp200ms = 0;
uint32_t timestamp1000ms = 0;


void setup()
{
 Serial.begin(115200);
 while (!Serial)
 {
 };


 CAN.setPins(CS_PIN, IRQ_PIN);
 CAN.setSPIFrequency(1E6);


 while (!CAN.begin(100E3))
 {
   Serial.println("[CANBUS] Init Failed");
   Serial.println("[CANBUS] Retrying Init...");
   delay(100);
 }
 Serial.println("[CANBUS] Init Success!");


 timestamp100ms = millis();
 timestamp200ms = millis();
 timestamp1000ms = millis();


 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);

//  updateTurnSignal(true, true);
}
int rpmValue = 0;
int incByte = 0;
bool inputComplete = false;
String inputString = "";
int number = 0;

bool testRound = false;
int timestamp5000ms = millis();

int speed = 0;
int rpm = 0;
bool absStatus; // unused for now
String gear = "P";
int fuelpercentage = 0;
bool engineStatus = false;
int tcLevel = 0; // unused for now
int hour = 0;
int minute = 0;
bool left_turn_signal = false;
bool right_turn_signal = false;
bool hazard_signal = false;
bool highbeams = false;
bool handbrake = false;
bool headlight = false;
float fuelPercentageforcalc = 0;

String serialBuffer = "";
bool packetReady = false;

unsigned long lastSerialRecieved = 0;

void parseSerialPacket(String packet){
  String parts[16];
  int partCount = 0;
  int start = 0;
  int end = packet.indexOf('-');

    while (end != -1 && partCount < 16) {
    parts[partCount++] = packet.substring(start, end);
    start = end + 1;
    end = packet.indexOf('-', start);
  }

  if (start < packet.length() && partCount < 16) {
    parts[partCount++] = packet.substring(start);
  }

  speed = parts[0].toInt();
  rpm = parts[1].toInt();
  absStatus = (parts[2] == "1");
  gear = parts[3];
  fuelpercentage = parts[4].toInt();
  engineStatus = (parts[5] == "1");
  tcLevel = parts[6].toInt();
  hour = parts[7].toInt();
  minute = parts[8].toInt();
  left_turn_signal = (parts[9] == "1");
  right_turn_signal = (parts[10] == "1");
  hazard_signal = (parts[11] == "1");
  highbeams = (parts[12] == "1");
  handbrake = (parts[13] == "1");
  headlight = (parts[14] == "1");

  fuelPercentageforcalc = fuelpercentage;
    Serial.println((fuelPercentageforcalc/100) * 50);
}


void checkSerial() {
  while (Serial.available()){
    char c = Serial.read();
    if (c == '&'){
      packetReady = true;
      break;
    }
    serialBuffer += c;
  }

  if (packetReady) {
    parseSerialPacket(serialBuffer);

    Serial.println("OK");

    serialBuffer = "";
    packetReady = false;
    lastSerialRecieved = millis();
  }
}






void loop()
{
  checkSerial();

  if (millis() - lastSerialRecieved > 1000){
    engineStatus = false;
    speed =0;
    rpm = 0;
    fuelpercentage = 0;
  }


 if (millis() - timestamp100ms > 10)
 {
  if (engineStatus == true){
   sendIgnitionKeyOn();
  }
   sendRPM(rpm);
   sendSpeed(speed);
   sendTireSpeed(speed);
    sendClock(hour, minute);
   sendAbs();
  if (gear == "P"){
    sendGear(1, false, 1, false);
  }else if (gear == "N"){
    sendGear(3, false, 1, false);
  }else if (gear == "R"){
    sendGear(2, false, 1, false);
  }else{
    sendGear(4, true, gear.toInt(), false);
  }
   // gear type (1 = p, 2 = r,  3= n, 4 = d, ), manual mode?, manual gear, sport mode? (display as DS on dash)
   timestamp100ms = millis();
 }


 if (millis() - timestamp200ms > 199)
 {
  
   sendFuelLevel((fuelPercentageforcalc/100) * 50); // max 51, logarithmically
   sendParkingBreak(handbrake);

   if (engineStatus){
    sendIgnitionStatus();
   }

   if (headlight && !highbeams){
      sendLights(2, 3);
   }else if (highbeams){
      sendLights(4, 3);
   }
   else
   {
       sendLights(0, 0);
   }


   
   sendAirbagSeatbeltCounter();
   disengageCruiseControl();
    sendAbsCount();
   timestamp200ms = millis();
 }




 if (millis() - timestamp1000ms > 667){

if (hazard_signal) {
  updateTurnSignal(true, true);
  updateTurnSignal(false, true);
} else {
  updateTurnSignal(true, left_turn_signal);
  updateTurnSignal(false, right_turn_signal);
}



  timestamp1000ms = millis();
  runTurnSignal();
 }

}

