/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 27.06.2016 20:23:49
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

boolean debug_info = false;

int base_pos;
int base_pos_lim_low = -90;
int base_pos_lim_high = 90;
int base_pos_pulse;
int base_pin = 24; //label 1

int shoulder_pos;
int shoulder_pos_lim_low = -75;
int shoulder_pos_lim_high = 75;
int shoulder_pos_pulse;
int shoulder_pin = 12; //label 2

int elbow_pos;
int elbow_pos_lim_low = -90;
int elbow_pos_lim_high = 90;
int elbow_pos_pulse;
int elbow_pin = 8; //label 3

int wrist_ver_pos;
int wrist_ver_pos_lim_low = -90;
int wrist_ver_pos_lim_high = 90;
int wrist_ver_pos_pulse;
int wrist_ver_pin = 28; //label 4

int wrist_rot_pos;
int wrist_rot_pos_lim_low = -90;
int wrist_rot_pos_lim_high = 90;
int wrist_rot_pos_pulse;
int wrist_rot_pin = 15; //label 5

int gripper_pos;
int gripper_pos_lim_low = -80;
int gripper_pos_lim_high = -17;
int gripper_pos_pulse;
int gripper_pin = 31; //label 6

uint16_t servo_time = 8000; // use range 130 - 250    

void setup()
{

    // write your setup code here, to run once
    Serial.begin(38400);
    position0();
}

// write your main code here, to run repeatedly
void loop()
{   
        
}

//=========================================================
// Functions
//=========================================================

void position0() {
    // Some position 0
    base_pos = 0;
    shoulder_pos = 0;
    elbow_pos = 0;
    wrist_ver_pos = 0;
    wrist_rot_pos = 0;
    gripper_pos = 0;
    servo_time = 5000;
    moveServos(); 
}

void position1() {
    // Some position beyond limits
    base_pos = 100;
    shoulder_pos = -100;
    elbow_pos = 95;
    wrist_ver_pos = -2200;
    wrist_rot_pos = 300;
    gripper_pos = -20;
    servo_time = 5000;
    moveServos(); 
}

void position2() {
    // Some position
    base_pos = 50;
    shoulder_pos = 0;
    elbow_pos = 45;
    wrist_ver_pos = 50;
    wrist_rot_pos = 0;
    gripper_pos = -30;
    servo_time = 5000;
    moveServos(); 
}

// Servo Move Example: "#5 P1600 T1000 "
// Servo Group Move Example: "#5 P1600 #10 P750 T2500 "

// Servo Move Example: "#5 P1600 T1000 "
// Servo Group Move Example: "#5 P1600 #10 P750 T2500 "
void instructSSC32() {
    Serial.print("#");
    Serial.print(base_pin);
    Serial.print(" P");
    Serial.print(base_pos_pulse);
    Serial.print(" #");
    Serial.print(shoulder_pin);
    Serial.print(" P");
    Serial.print(shoulder_pos_pulse);
    Serial.print(" #");
    Serial.print(elbow_pin);
    Serial.print(" P");
    Serial.print(elbow_pos_pulse);
    Serial.print(" #");
    Serial.print(wrist_ver_pin);
    Serial.print(" P");
    Serial.print(wrist_ver_pos_pulse);
    Serial.print(" #");
    Serial.print(wrist_rot_pin);
    Serial.print(" P");
    Serial.print(wrist_rot_pos_pulse);
    Serial.print(" #");
    Serial.print(gripper_pin);
    Serial.print(" P");
    Serial.print(gripper_pos_pulse);
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

// Function to apply offsets for arm1
void applyOffsets(){
    // Todo subtract/add for any servo offsets    
    base_pos = base_pos + 52;
    shoulder_pos = shoulder_pos + 10;
    elbow_pos = elbow_pos + 5;
    wrist_ver_pos = wrist_ver_pos - 0;
    wrist_rot_pos = wrist_rot_pos - 12;
    gripper_pos = gripper_pos - 0;
}

// Function to apply limits if needed
void applyLimit(){
 
    if(base_pos > base_pos_lim_high){base_pos = base_pos_lim_high;}
    if(base_pos < base_pos_lim_low){base_pos = base_pos_lim_low;}

    if(shoulder_pos > shoulder_pos_lim_high){shoulder_pos = shoulder_pos_lim_high;}
    if(shoulder_pos < shoulder_pos_lim_low){shoulder_pos = shoulder_pos_lim_low;}

    if(elbow_pos > elbow_pos_lim_high){elbow_pos = elbow_pos_lim_high;}
    if(elbow_pos < elbow_pos_lim_low){elbow_pos = elbow_pos_lim_low;}    

    if(wrist_ver_pos > wrist_ver_pos_lim_high){wrist_ver_pos = wrist_ver_pos_lim_high;}
    if(wrist_ver_pos < wrist_ver_pos_lim_low){wrist_ver_pos = wrist_ver_pos_lim_low;}

    if(wrist_rot_pos > wrist_rot_pos_lim_high){wrist_rot_pos = wrist_rot_pos_lim_high;}
    if(wrist_rot_pos < wrist_rot_pos_lim_low){wrist_rot_pos = wrist_rot_pos_lim_low;}

    if(gripper_pos > gripper_pos_lim_high){gripper_pos = gripper_pos_lim_high;}
    if(gripper_pos < gripper_pos_lim_low){gripper_pos = gripper_pos_lim_low;}    

}

void convertAllServoToPulse(){
    // Convert all angles to pulse
    // TODO check if value has actually changed, otherwise you convert the value yet again.
    base_pos_pulse = angle_to_pulse_length(base_pos);
    shoulder_pos_pulse = angle_to_pulse_length(shoulder_pos);
    elbow_pos_pulse = angle_to_pulse_length(elbow_pos);
    wrist_ver_pos_pulse = angle_to_pulse_length(wrist_ver_pos);
    wrist_rot_pos_pulse = angle_to_pulse_length(wrist_rot_pos);
    gripper_pos_pulse = angle_to_pulse_length(gripper_pos);
}

void moveServos(){
    applyOffsets();
    applyLimit();
    convertAllServoToPulse();
    instructSSC32();
}

