//Testing Code some are commented need more explaning each step

//Including MPU 6050 Sensor & Bluetooth serial function & ESP-32 Library
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include <Wire.h>
#include "BluetoothSerial.h"

//Enabeling Bluetooth Serial 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Initialize class 
BluetoothSerial SerialBT;

//Enabeling Accelometer MPU6050
Adafruit_MPU6050 mpu;

//Intial value to avoid letter repetition 
char temp = '0';


//Name of the fingers on the flex sensor input pins 
int flexsensor_5 = 13; //Pinkie D13
int flexsensor_4 = 14; // Ring D14
int flexsensor_3 = 26; // MiddleFinger D26
int flexsensor_2 = 33; //Index D33
int flexsensor_1 = 35;//Thumb D35


//Name of the variables before the flex sensor values
//set initial values for the minimum and maximum sensor values
int flexvalue_5 ;
int sensorMin5 = 4095; 
int sensorMax5 = 0;

int flexvalue_4 ;
int sensorMin4 = 4095; 
int sensorMax4 = 0;

int flexvalue_3 ;
int sensorMin3 = 4095; 
int sensorMax3 = 0;

int flexvalue_2 ;
int sensorMin2 = 4095; 
int sensorMax2 = 0;

int flexvalue_1;
int sensorMin1 = 4095; 
int sensorMax1 = 0;


void setup(void) {
  Serial.begin(115200);
  
  SerialBT.begin("LeftGlove"); //Bluetooth device name will show up on the phone 
  Serial.println("The device started, now you can pair it with bluetooth!");
  
//ESP32 Analog Input Pins
pinMode(flexsensor_5,INPUT);
pinMode(flexsensor_4,INPUT);
pinMode(flexsensor_3,INPUT);
pinMode(flexsensor_2,INPUT);
pinMode(flexsensor_1,INPUT);
 // calibrate during the first five seconds
while (millis() < 5000) {
    flexvalue_5 = analogRead(flexsensor_5);
    flexvalue_4 = analogRead(flexsensor_4);
    flexvalue_3 = analogRead(flexsensor_3);
    flexvalue_2 = analogRead(flexsensor_2);
    flexvalue_1 = analogRead(flexsensor_1);
    
 // record the maximum sensor values for all flex sensors then record the minimum sensor values
 
    if (flexvalue_5 > sensorMax5) {
      sensorMax5 = flexvalue_5;
    }

    if (flexvalue_5 < sensorMin5) {
      sensorMin5 = flexvalue_5;
    }

    if (flexvalue_4 > sensorMax4) {
      sensorMax4 = flexvalue_4;
    }

    if (flexvalue_4 < sensorMin4) {
      sensorMin4 = flexvalue_4;
    }
    if (flexvalue_3 > sensorMax3) {
      sensorMax3 = flexvalue_3;
    }

    if (flexvalue_3 < sensorMin3) {
      sensorMin3 = flexvalue_3;
    }
    if (flexvalue_2 > sensorMax2) {
      sensorMax2 = flexvalue_2;
    }

    if (flexvalue_2 < sensorMin2) {
      sensorMin2 = flexvalue_2;
    }
    if (flexvalue_1 > sensorMax1) {
      sensorMax1 = flexvalue_1;
    }

    if (flexvalue_1 < sensorMin1) {
      sensorMin1 = flexvalue_1;
    }
  }
  while (!Serial)

    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("MPU6050 Sensor Ready!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
//  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
//    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
//    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
//    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
//    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
//  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
//    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
//    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
//    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
//    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
//  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
//    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
//    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
//    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
//    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
//  Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
//    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
//    Serial.println("5 Hz");
    break;
  }

  //Serial.println("");
  //delay(100);

 
}

//void printfun(char cp) //to avoid printing repeating symbols
//{
//if(cp!=temp)
//{
//Serial.print(cp);
//temp=cp;
//}
//}
void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g , &temp);

  //Print out the values of MPU
  //Serial.print("Acceleration X: ");
  //Serial.print(a.acceleration.x);
  //Serial.print(", Y: ");
  //Serial.print(a.acceleration.y);
  //Serial.print(", Z: ");
  //Serial.print(a.acceleration.z);
  //Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  //Serial.print(", Z: ");
  //Serial.print(g.gyro.z);
  //Serial.println(" rad/s");

  flexvalue_5 = analogRead(flexsensor_5);
  Serial.print("Flex-5-");
  Serial.println(flexvalue_5);
  flexvalue_4 = analogRead(flexsensor_4);
  Serial.print("Flex-4-");
  Serial.println(flexvalue_4);
  flexvalue_3 = analogRead(flexsensor_3);
  Serial.print("Flex-3-");
  Serial.println(flexvalue_3);
  flexvalue_2 = analogRead(flexsensor_2);
  Serial.print("Flex-2-");
  Serial.println(flexvalue_2);
  flexvalue_1 = analogRead(flexsensor_1);
  Serial.print("Flex-1-:");
  Serial.println(flexvalue_1);
  Serial.println("New Values");
// Testing Calibration 
//flexvalue_5 = constrain(flexvalue_5,sensorMin5, sensorMax5);
//flexvalue_4 = constrain(flexvalue_4,sensorMin4, sensorMax4);
//flexvalue_3 = constrain(flexvalue_3,sensorMin3, sensorMax3);
//flexvalue_2 = constrain(flexvalue_2,sensorMin2, sensorMax2);
//flexvalue_1 = constrain(flexvalue_1,sensorMin1, sensorMax1);


//  float angle5= map(flexvalue_5, sensorMin5, sensorMax5, 0, 90);
//  float angle4= map(flexvalue_4, sensorMin4, sensorMax4, 0, 90);
//  float angle3= map(flexvalue_3, sensorMin3, sensorMax3, 0, 90);
//  float angle2= map(flexvalue_2, sensorMin2, sensorMax2, 0, 90);
//  float angle1= map(flexvalue_1, sensorMin1, sensorMax1, 0, 90); 

//Testing Diffrent Letters and Words
//The values of flex sensor and MPU6050 need to be taken manually gesture by gesture 

/*Example 

  if((flexvalue_1>??)and(flexvalue_1<=??)and(flexvalue_2>??)and(flexvalue_2<=??)(flexvalue_3>??)and(flexvalue_3<=??)and(flexvalue_4>??)and(flexvalue_4<=??)(flexvalue_5>??)and(flexvalue_5<=??)) {
  SerialBT.println("The required Letter or WOrd"); }
  
  Else if((flexvalue_1>??)and(flexvalue_1<=??)and(flexvalue_2>??)and(flexvalue_2<=??)(flexvalue_3>??)and(flexvalue_3<=??)and(flexvalue_4>??)and(flexvalue_4<=??)and(flexvalue_5>??)and(flexvalue_5<=??)and(Xgyro>??)and(Xgyro<=??)and(Ygyro>??)and(Ygyro<=??)){
  SerialBT.println("The required Letter or WOrd"); } */
  
if((flexvalue_1>2700)and(flexvalue_1<=2900)and(flexvalue_2>3900)and(flexvalue_2<=4095)and(flexvalue_3>3500)and(flexvalue_3<=3700)and(flexvalue_4>3800)and(flexvalue_4<=4000)and(flexvalue_5>3900)and(flexvalue_5<=4095)) {
  SerialBT.println('A');
  Serial.println("Letter A");
  delay(2000); // can change the delay depending on your requirements  
}
else if((flexvalue_1>3100)and(flexvalue_1<=3300)and(flexvalue_2>3900)and(flexvalue_2<=4095)and(flexvalue_3>3500)and(flexvalue_3<=3700)and(flexvalue_4>3600)and(flexvalue_4<=3800)and(flexvalue_5>2500)and(flexvalue_5<=2700)){
  SerialBT.println('I');
  Serial.println("Letter I");
  delay(2000);}
 else if((flexvalue_1>2500)and(flexvalue_1<=2700)and(flexvalue_2>2300)and(flexvalue_2<=2500)and(flexvalue_3>3700)and(flexvalue_3<=3900)and(flexvalue_4>3700)and(flexvalue_4<=3900)and(flexvalue_5>3900)and(flexvalue_5<=4095)){
  SerialBT.println('Z');
  Serial.println("Letter Z");
  delay(2000); // can change the delay depending on your requirements  
 }
 else if((flexvalue_1>3100)and(flexvalue_1<=3300)and(flexvalue_2>2700)and(flexvalue_2<=2900)and(flexvalue_3>3000)and(flexvalue_3<=3200)and(flexvalue_4>3300)and(flexvalue_4<=3500)and(flexvalue_5>3700)and(flexvalue_5<=3900)){
  SerialBT.println('D');
  Serial.println("Letter D");
  delay(2000);
 }
}
