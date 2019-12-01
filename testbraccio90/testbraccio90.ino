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
    Braccio.begin();
    delay(5000);
}

void loop()
{
                       //(step delay    M1,  M2,   M3,   M4,  M5,  M6);
    Braccio.ServoMovement(20,           95,  95,   97,   85,  90,  73);
    delay(5000);
    Braccio.ServoMovement(20,           45, 135,   10,   10,  90,  10);
    delay(1500);
    Braccio.ServoMovement(20,           45, 135,   10,   10,  90,  35);
    delay(2000);
    Braccio.ServoMovement(20,           125, 135,   10,   10,  90,  35);
    delay(1500);
    Braccio.ServoMovement(20,           125, 135,   10,   10,  90,  10);
    delay(2000);    
}
