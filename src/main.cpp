#include <CAN.h>
#include <commands.h>

#define lo8(x) (uint8_t)((x)&0xff)
#define hi8(x) (uint8_t)(((x) >> 8) & 0xff)


const uint8_t CS_PIN = 9;
const uint8_t IRQ_PIN = 2;


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


// void sendRPM(uint16_t rpm)
// {
//  uint16_t tempRpm = rpm * 4;


//  CAN.beginPacket(0x0AA);


//  CAN.write(0xFE);
//  CAN.write(0xFE);
//  CAN.write(0xFF);
//  CAN.write(0x00);
//  CAN.write(lo8(tempRpm));
//  CAN.write(hi8(tempRpm));
//  CAN.write(0xFE);
//  CAN.write(0x99);


//  CAN.endPacket();
// }


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


// void sendFuelLevel(uint16_t litres)
// {
//  uint16_t sensor = litres * 160;


//  CAN.beginPacket(0x349);


//  CAN.write(lo8(sensor));
//  CAN.write(hi8(sensor));
//  CAN.write(lo8(sensor));
//  CAN.write(hi8(sensor));
//  CAN.write(0x00);


//  CAN.endPacket();
// }


void sendAirbagSeatbeltCounter()
{
 static uint8_t count = 0x00;


 CAN.beginPacket(0x0D7);


 CAN.write(count);
 CAN.write(0xFF);


 CAN.endPacket();


 count++;
}


// void sendABSBrakeCounter2()
// {
//  CAN.beginPacket(0x19E);


//  CAN.write(0x00);
//  CAN.write(0xE0);
//  CAN.write(0xB3);
//  CAN.write(0xFC);
//  CAN.write(0xF0);
//  CAN.write(0x43);
//  CAN.write(0x00);
//  CAN.write(0x65);


//  CAN.endPacket();
// }


void sendABSBrakeCounter1()
{
 static uint8_t count = 0xF0;


 CAN.beginPacket(0x0C0);


 CAN.write(count);
 CAN.write(0xFF);


 CAN.endPacket();


 count++;
 if (count == 0x00)
 {
   count = 0xF0;
 }
}


void seatbeltLight(bool state)
{
 uint8_t thirdBit;


 if (state == false)
 {
   CAN.beginPacket(0x581);
   thirdBit = 0x28;
 }
 else
 {
   CAN.beginPacket(0x394);
   thirdBit = 0x29;
 }


 CAN.write(0x40);
 CAN.write(0x4D);
 CAN.write(0x00);
 CAN.write(thirdBit);
 CAN.write(0xFF);
 CAN.write(0xFF);
 CAN.write(0xFF);
 CAN.write(0xFF);


 CAN.endPacket();
}


// void sendSpeed(uint16_t speed)
// {
//  static uint32_t lastTimeSent = 0;
//  static uint16_t lastReading = 0;
//  static uint16_t count = 0xF000;


//  uint16_t speedValToSend = ((millis() - lastTimeSent) / 50) * speed / 2;
//  speedValToSend += lastReading;


//  lastReading = speedValToSend;
//  lastTimeSent = millis();


//  CAN.beginPacket(0x1A6);


//  CAN.write(lo8(speedValToSend));
//  CAN.write(hi8(speedValToSend));
//  CAN.write(lo8(speedValToSend));
//  CAN.write(hi8(speedValToSend));
//  CAN.write(lo8(speedValToSend));
//  CAN.write(hi8(speedValToSend));
//  CAN.write(lo8(count));
//  CAN.write(hi8(count));


//  CAN.endPacket();
// }


void tmpTest(){
 CAN.beginPacket(0x2CA);


 CAN.write(0x61);
 CAN.write(0xFF);


 CAN.endPacket();
}


// void sendTimeTest(){
//  CAN.beginPacket(0x2F8);


//  CAN.write(0x13);
//  CAN.write(0x2E);
//  CAN.write(0x1E);
//  CAN.write(0x01);
//  CAN.write(0x4F);
//  CAN.write(0xDC);
//  CAN.write(0x07);
//  CAN.write(0xFD);


//  CAN.endPacket();
//  }


void sendLightsOff()
{
 CAN.beginPacket(0x21A);


 CAN.write(0b00000000);
 CAN.write(0b00000000);
 CAN.write(0x00);


 CAN.endPacket();
}


void sendLightsOn(){
 CAN.beginPacket(0x21A);
 CAN.write(0b00000101);
 CAN.write(0b00010000);
 CAN.write(0x00);


 CAN.endPacket();
}


void tireSpeed(){
 CAN.beginPacket(0x0CE);


 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);
 CAN.write(0x00);


 CAN.endPacket();
}


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
   Serial.println("CAN BUS Shield init fail");
   Serial.println(" Init CAN BUS Shield again");
   delay(100);
 }
 Serial.println("CAN BUS Shield init ok!");


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
bool left_fuckass_signal = false;
bool right_fuckass_signal = false;
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
  left_fuckass_signal = (parts[9] == "1");
  right_fuckass_signal = (parts[10] == "1");
  hazard_signal = (parts[11] == "1");
  highbeams = (parts[12] == "1");
  handbrake = (parts[13] == "1");
  headlight = (parts[14] == "1");

  // Serial.println("Packet parsed successfully");
  // Serial.println(right_fuckass_signal);
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




// void handleSerialData(){
//     serialBuffer += Serial.readStringUntil('&');
//     serialBuffer += '&';
//     String parts[16];
//     int partCount = 0;
//     int start = 0;
//     int end = serialBuffer.indexOf('-');

//     while (end != -1 && partCount < 16){
//       parts[partCount++] = serialBuffer.substring(start, end);
//       start = end + 1;
//       end = serialBuffer.indexOf('-', start);

//     }
//     if (start < serialBuffer.length()){
//       parts[partCount++] = serialBuffer.substring(start);
//     }
//     speed = parts[0].toInt();
//     rpm = parts[1].toInt();
//     absStatus = parts[2];
//     gear = parts[3];
//     fuelpercentage = parts[4].toInt();
//     engineStatus = (parts[5] == "True") ? true : false;
//     tcLevel = parts[6].toInt();
//     hour = parts[7].toInt();
//     minute = parts[8].toInt();
//     left_fuckass_signal = (parts[9] == "True") ? true : false;
//     right_fuckass_signal = (parts[10] == "True") ? true : false;
//     hazard_signal = (parts[11] == "True") ? true : false;
//     highbeams = (parts[12] == "True") ? true : false;
//     handbrake = (parts[13] == "True") ? true : false;
//     headlight = (parts[14] == "True") ? true : false;
//     Serial.print("speed: " + String(speed) + " rpm: "+ String(rpm) + " abs level: " + String(absStatus) + " gear:" + gear + " fuel percentage: " + String(fuelpercentage) + " engine status:" + String(engineStatus) + " traction level: " + String(tcLevel) + " hour: " + String(hour) + " minute: " + String(minute) + " left signal: " + String(left_fuckass_signal) + " right signal: " + String(right_fuckass_signal) + " hazard lights: " + String(hazard_signal) + " high beams:" + String(highbeams) + " handbrake: " + String(handbrake) + " headlights: " + String(headlight));
//     fuelPercentageforcalc = fuelpercentage;
//     serialBuffer = "";
//     // Serial.println(parts[0] + parts[1]);
// }

void loop()
{
  checkSerial();

  if (millis() - lastSerialRecieved > 1000){
    engineStatus = false;
    speed =0;
    rpm = 0;
    fuelpercentage = 0;
  }

  // while (Serial.available()){
  //   char c = Serial.read();
  //   serialBuffer + c;
  //   if (serialBuffer.indexOf("EOF") > 0){
  //     Serial.print(serialBuffer);
  //     serialBuffer = "";
  //   }
  // }
 // while (Serial.available()) {
 //   char inChar = (char)Serial.read();
 //   if (inChar == '\n') {
 //     inputComplete = true;
 //   } else if (inChar != '\r') {  // Ignore carriage return
 //     inputString += inChar;
 //   }
 // }
 //   if (inputComplete) {
 //   number = inputString.toInt();  // Convert string to int
 //   rpmValue = number;
 //   Serial.println("recieved " + number);
 //   // Reset for next input
 //   inputString = "";
 //   inputComplete = false;
 // }



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
   // gear type (1 = p, 2 = r,  3= n, 4 = d, ), manual mode?, manual gear, sport mode?
   timestamp100ms = millis();
 }


 if (millis() - timestamp200ms > 199)
 {
  
   sendFuelLevel((fuelPercentageforcalc/100) * 50); // max 51, logarithmically - keep at 51 unless ets
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


   
  //  sendTripInformation(10, 10, 100);
   sendAirbagSeatbeltCounter();
   disengageCruiseControl();
  //  sendTrunkStatus(true);
    sendAbsCount();
   // seatbeltLight(true);
  //  sendLightsOn();
  //  tmpTest();
   tireSpeed();
   timestamp200ms = millis();
 }




 if (millis() - timestamp1000ms > 667){

if (hazard_signal) {
  updateTurnSignal(true, true);
  updateTurnSignal(false, true);
} else {
  updateTurnSignal(true, left_fuckass_signal);
  updateTurnSignal(false, right_fuckass_signal);
}



  timestamp1000ms = millis();
  runTurnSignal();
 }
// int timestamp2ndms = 0;
//  if (millis() - timestamp2ndms > 9999){
//      activateCruiseControl(0);
//      timestamp2ndms = 0;
//  }

//  if (millis() - timestamp5000ms > 4999){
//     if (testRound) {
//       speed = 0;
//       RPM = 600;
//       testRound = false;
//     }else {
//       speed = 120;
//       RPM = 4200;
//       testRound = true;
//     }

//  }


}

