/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 27.06.2016 18:29:48
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

void setup()
{

    // write your setup code here, to run once
    Braccio.begin();

}

void loop()
{

    // write your main code here, to run repeatedly

    delay(5000);    
                       //(step delay    M1,  M2,   M3,   M4,  M5,  M6);
    // Rest
    Braccio.ServoMovement(30,           45,  105,  180,  180,  75,  40);    
    delay(15000);
    
    // Stand straight up
    Braccio.ServoMovement(30,           120,  105,  95,  90,  90,  40);
    delay(5000);

    // braccio.begin pos
    Braccio.ServoMovement(30,           90,  45,  180,  180,  90,  10);
    delay(10000);    
}
