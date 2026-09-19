#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;

// HC05: RX=10, TX=11
SoftwareSerial BT(7, 8);

// Flex sensor pins
int flexThumb  = A0;   // Potentiometer (thumb)
int flexIndex  = A1;   // black sensor
int flexMiddle = A2;   // flex2

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU FAILED!");
    BT.println("MPU FAILED!");
    while (1);
  }

  Serial.println("MPU OK");
  BT.println("MPU OK");
}

void loop() {

  
  // FLEX SENSOR INPUTS
  int thumb  = analogRead(flexThumb);  
  int index  = analogRead(flexIndex);
  int middle = analogRead(flexMiddle);

  bool thumbStraight = (thumb < 300);
  bool thumbBent     = (thumb > 500);

  bool indexStraight = (index < 200);
  bool indexBent     = (index > 500);

  bool middleStraight = (middle > 270);
  bool middleBent     = (middle < 269);

  // Imu
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float AY = ay / 16384.0;
  float AX = ax / 16384.0;

  bool rightTilt  = (AY > 0.40);
  bool leftTilt   = (AY < -0.40);
  bool neutralTilt = (AY > -0.30 && AY < 0.30);

  bool tiltUp = (AX > 0.45);
  bool tiltDown  = (AX < -0.10);
  //bool tiltFlat  = (AX > -0.10 && AX < 0.30);
  bool handVertical = (AY > -0.30 && AY < 0.30);

 
  Serial.print("Thumb:");
  Serial.print(thumb);
  Serial.print(" Index:");
  Serial.print(index);
  Serial.print(" Middle:");
  Serial.print(middle);

  Serial.print(" | AY:");
  Serial.print(AY, 2);

  Serial.print(" Tilt:");
  if (rightTilt) Serial.print("RIGHT");
  else if (leftTilt) Serial.print("LEFT");
  else if(tiltUp)  Serial.print("Up");
  else if(tiltDown) Serial.print("Down");
  else Serial.print("NEUTRAL");

  Serial.println();

  
  // GESTURE 1: CALL ME 🤙 (needs right tilt)
  
  if (thumbStraight && indexBent && middleBent && rightTilt) {
    Serial.println("CALL ME");
    BT.println(" CALL ME");
    delay(400);
    return;
  }

 
  // GESTURE 2: I LOVE YOU 🤟
  
  if (thumbStraight && indexStraight && middleBent &&neutralTilt &&!tiltUp) {
    Serial.println("I LOVE YOU");
    BT.println(" I LOVE YOU");
    delay(400);
    return;
  }

  
  // GESTURE 3: GOOD LUCK 🤞
  if (thumbBent && indexStraight && middleStraight) {
    Serial.println("GOOD LUCK");
    BT.println(" GOOD LUCK");
    delay(400);
    return;
  } 

//Gesture 4:loser
if (thumbStraight && indexStraight &&middleBent && tiltUp) {
    Serial.println("LOSER");
    BT.println(" LOSER");
    delay(400);
    return;
}


// Gesture5:ROCK ON 🤘
// thumb bent + index straight + middle bent
if (thumbBent && indexStraight && middleBent) {
    Serial.println(" ROCK ON");
    BT.println(" ROCK ON");
    delay(400);
    return;
}

// Gesture 6:PAIN ✊
// all fingers bent -> fist
if (tiltDown && thumbBent && indexBent) {
    Serial.println("PAIN");
    BT.println(" PAIN");
    delay(400);
    return;
}
//Gesture 7: Hi
  else if(tiltUp){
   Serial.println("Hi");
    BT.println(" Hi");
    delay(400);

}
  else {
    Serial.println("Nothing");
    BT.println(" Nothing");
    delay(400);
    return;
  }

  delay(80);
}

