/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 27.06.2016 20:23:49
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

boolean debug_info = false;

int base_pos;
int base_pin = 4;
int shoulder_pos;
int shoulder_pin = 8;
int elbow_pos;
int elbow_pin = 12;
int wrist_ver_pos;
int wrist_ver_pin = 16;
int wrist_rot_pos;
int wrist_rot_pin = 20;
int gripper_pos;
int gripper_pin = 24;

uint16_t servo_time = 1000;

void setup()
{

    // write your setup code here, to run once
    Serial.begin(9600);
}

void loop()
{

    // write your main code here, to run repeatedly
    Serial.print("Hello World!");
}

//=========================================================
// Functions
//=========================================================
// Servo Move Example: "#5 P1600 T1000 "
// Servo Group Move Example: "#5 P1600 #10 P750 T2500 "

// Servo Move Example: "#5 P1600 T1000 "
// Servo Group Move Example: "#5 P1600 #10 P750 T2500 "
void move(int base_pin, int base_pos, 
int shoulder_pin, int shoulder_pos, 
int elbow_pin, int elbow_pos,
int wrist_ver_pin, int wrist_ver_pos,
int wrist_rot_pin, int wrist_rot_pos,
int gripper_pin, int gripper_pos,
) {
    Serial.print("#");
    Serial.print(base_pin);
    Serial.print(" P");
    Serial.print(base_pos);
    Serial.print("#");
    Serial.print(shoulder_pin);
    Serial.print(" P");
    Serial.print(shoulder_pos);
    Serial.print("#");
    Serial.print(elbow_pin);
    Serial.print(" P");
    Serial.print(elbow_pos);
    Serial.print("#");
    Serial.print(wrist_ver_pin);
    Serial.print(" P");
    Serial.print(wrist_ver_pos);
    Serial.print("#");
    Serial.print(wrist_rot_pin);
    Serial.print(" P");
    Serial.print(wrist_rot_pos);
    Serial.print(" #");
    Serial.print(gripper_pin);
    Serial.print(" P");
    Serial.print(gripper_pos);
    Serial.print(" T");
    Serial.println(servo_time);
}

/*  Angle (degree) to pulse width in microseconds 
conversion part A pos value of 500 corresponds to 0.50mS pulse 
and a pos value of 2500 corresponds to a 2.50mS pulse.  

Note normal or extended range usage. 0.50mS = pos value 
500 = -90 degrees 1.50mS = pos value 1500 = 0 degree 2.5 mS = pos value 2500 = +90 graden 
use arduino map function */ 
int pulse_length_to_angle(int pulse_length){
   int angle;
   angle = map(pulse_length, 500, 2500, -90, 90);
   return angle;
}

int angle_to_pulse_length(int angle){
   int pulse_length;
   pulse_length = map(angle, -90, 90, 500, 2500);
   if (debug_info == true){
       Serial.print("Converting ");
       Serial.print(angle);
       Serial.print(" degree(s) to ");
       Serial.print(pulse_length);
       Serial.println(" pulse length.");
   }
   return pulse_length;
}