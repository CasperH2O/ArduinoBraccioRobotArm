/* Servo control for AL5D arm */
 
/* Arm dimensions( mm ) */
#define BASE_HGT 72.50      //base hight 
#define HUMERUS 126.5      //shoulder-to-elbow "bone" 
#define ULNA 125.0        //elbow-to-wrist "bone" 
#define GRIPPER 190.00          //gripper (incl. wrist rotate mechanism)
#define ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))  //float to long conversion
 
/* Servo names/numbers */
/* Base servo HS-485HB */
#define BAS_SERVO 0
/* Shoulder Servo HS-5745-MG */
#define SHL_SERVO 1
/* Elbow Servo HS-5745-MG */
#define ELB_SERVO 2
/* Wrist servo HS-645MG */
#define WRI_SERVO 3
/* Wrist rotate servo HS-485HB */
#define WRO_SERVO 4
/* Gripper servo HS-422 */
#define GRI_SERVO 5
 
/* pre-calculations */
float hum_sq = HUMERUS*HUMERUS;
float uln_sq = ULNA*ULNA;
 
boolean debug_info = false;

float base_pos;
int base_pos_lim_low = -90;
int base_pos_lim_high = 90;
int base_pos_pulse;
int base_pin = 24; //label 1

float shoulder_pos;
int shoulder_pos_lim_low = -75;
int shoulder_pos_lim_high = 75;
int shoulder_pos_pulse;
int shoulder_pin = 12; //label 2

float elbow_pos;
int elbow_pos_lim_low = -90;
int elbow_pos_lim_high = 90;
int elbow_pos_pulse;
int elbow_pin = 8; //label 3

float wrist_ver_pos;
int wrist_ver_pos_lim_low = -90;
int wrist_ver_pos_lim_high = 90;
int wrist_ver_pos_pulse;
int wrist_ver_pin = 28; //label 4

float wrist_rot_pos;
int wrist_rot_pos_lim_low = -90;
int wrist_rot_pos_lim_high = 90;
int wrist_rot_pos_pulse;
int wrist_rot_pin = 15; //label 5

float gripper_pos;
int gripper_pos_lim_low = -80;
int gripper_pos_lim_high = -17;
int gripper_pos_pulse;
int gripper_pin = 31; //label 6

uint16_t servo_time = 8000; // use range 130 - 250  
 
void setup()
{
    Serial.begin( 38400 );
    Serial.println("==== Start Setup =====");
    delay( 500 );
    
    //set_arm( 0, 250, 150, 0);    
    //delay( 8000 );
    //
    //set_arm( 0, 250, 250, 0 );     
    //delay( 8000 );
    
    //set_arm( 0, 350, 250, 0 );    
    //delay( 8000 );
    //
    //set_arm( 0, 260, 300, 0 );    
    //delay( 8000 );
    //
    //set_arm( 0, 200, 320, 0 );    
    position2();
    delay( 8000 );  
  Serial.println("==== End Setup ====");
  Serial.println(" ");    
    
  //zero_x();
    
}
 
void loop()
{
  //line();
  //circle();
  //zero_x();
 
  //Serial.println("==== End ====");
  //Serial.println(" ");
  
  position3();
  delay( 8000 );    
  position4();  
  delay( 8000 );      
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
    base_pos = 0;
    shoulder_pos = 0;
    elbow_pos = 45;
    wrist_ver_pos = 50;
    wrist_rot_pos = -50;
    gripper_pos = -30;
    servo_time = 5000;
    moveServos(); 
} 

void position3() {
    // Some position
    base_pos = 0;
    shoulder_pos = 0;
    elbow_pos = 45;
    wrist_ver_pos = 50;
    wrist_rot_pos = 0;
    gripper_pos = -50;
    servo_time = 5000;
    moveServos(); 
} 

void position4() {
    // Some position
    base_pos = 0;
    shoulder_pos = 0;
    elbow_pos = 45;
    wrist_ver_pos = 50;
    wrist_rot_pos = 50;
    gripper_pos = 0;
    servo_time = 5000;
    moveServos(); 
} 

/* arm positioning routine utilizing inverse kinematics */
/* z is height, y is distance from base center out, x is side to side. y,z can only be positive */
//void set_arm( uint16_t x, uint16_t y, uint16_t z, uint16_t grip_angle )
void set_arm( float x, float y, float z, float grip_angle_d )
{

if (debug_info == true){
       Serial.print("sa:");
       Serial.print(" X: "); Serial.print(x);
       Serial.print(" Y: "); Serial.print(y);
       Serial.print(" Z: "); Serial.println(z);
    }

  float grip_angle_r = radians( grip_angle_d );    //grip angle in radians for use in calculations
  /* Base angle and radial distance from x,y coordinates */
  float bas_angle_r = atan2( x, y );
  float rdist = sqrt(( x * x ) + ( y * y ));
  /* rdist is y coordinate for the arm */
  y = rdist;
  /* Grip offsets calculated based on grip angle */
  float grip_off_z = ( sin( grip_angle_r )) * GRIPPER;
  float grip_off_y = ( cos( grip_angle_r )) * GRIPPER; 
  /* Wrist position */
  float wrist_z = ( z - grip_off_z ) - BASE_HGT;
  float wrist_y = y - grip_off_y;
  /* Shoulder to wrist distance ( AKA sw ) */
  float s_w = ( wrist_z * wrist_z ) + ( wrist_y * wrist_y );
  float s_w_sqrt = sqrt( s_w );
  /* s_w angle to ground */
  //float a1 = atan2( wrist_y, wrist_z ); 
  float a1 = atan2( wrist_z, wrist_y );
  /* s_w angle to humerus */
  float a2 = acos((( hum_sq - uln_sq ) + s_w ) / ( 2 * HUMERUS * s_w_sqrt ));
  /* shoulder angle */
  float shl_angle_r = a1 + a2;
  float shl_angle_d = degrees( shl_angle_r ); 
  /* elbow angle */
  float elb_angle_r = acos(( hum_sq + uln_sq - s_w ) / ( 2 * HUMERUS * ULNA ));
  float elb_angle_d = degrees( elb_angle_r );
  float elb_angle_dn = -( 180.0 - elb_angle_d );
  /* wrist angle */
  float wri_angle_d = ( grip_angle_d - elb_angle_dn ) - shl_angle_d;
 
  /* Servo pulses */
  float bas_servopulse = 1500.0 - (( degrees( bas_angle_r )) * 11.11 );
  float shl_servopulse = 1500.0 + (( shl_angle_d - 90.0 ) * 6.6 );
  float elb_servopulse = 1500.0 -  (( elb_angle_d - 90.0 ) * 6.6 );
  float wri_servopulse = 1500 + ( wri_angle_d  * 11.1 );

//if (debug_info == true){
//       Serial.println("-- Calc stuff --");
//       Serial.print("Base: "); Serial.print(bas_servopulse);
//       Serial.print(" Shoulder: "); Serial.print(shl_servopulse);
//       Serial.print(" Elbow: "); Serial.print(elb_servopulse);
//       Serial.print(" Wrist Vert: "); Serial.println(wri_servopulse);
//    }  
  
  base_pos = degrees( bas_angle_r );
  shoulder_pos = ((shl_angle_d - 90.0) * -1);
  elbow_pos = (180 - elb_angle_d);
  wrist_ver_pos = (wri_angle_d * -1);
  wrist_rot_pos = grip_angle_d;
  gripper_pos = -30;  
  
  /* Set servos */
  //servos.setposition( BAS_SERVO, ftl( bas_servopulse ));
  //servos.setposition( WRI_SERVO, ftl( wri_servopulse ));
  //servos.setposition( SHL_SERVO, ftl( shl_servopulse ));
  //servos.setposition( ELB_SERVO, ftl( elb_servopulse ));
  
  moveServos();
  //servo_time = 101;
  
}
 
void zero_x()
{
  for( double yaxis = 200.0; yaxis < 350.0; yaxis += 1 ) {
    set_arm( 0, yaxis, 250.0, 0 );
    delay( 50 );
  }
  for( double yaxis = 200.0; yaxis > 350.0; yaxis -= 1 ) {
    set_arm( 0, yaxis, 250.0, 0 );
    delay( 50 );
  }
}
 
/* moves arm in a straight line */
void line()
{
    for( double xaxis = -200.0; xaxis < 200.0; xaxis += 20 ) {
      set_arm( xaxis, 250, 250, 0 );
      delay( 100 );
    }
    for( float xaxis = 200.0; xaxis > -200.0; xaxis -= 20 ) {
      set_arm( xaxis, 250, 250, 0 );
      delay( 100 );
    }
}
 
void circle()
{
  #define RADIUS 80.0
  //float angle = 0;
  float zaxis,yaxis;
  for( float angle = 0.0; angle < 360.0; angle += 1.0 ) {
      yaxis = RADIUS * sin( radians( angle )) + 200;
      zaxis = RADIUS * cos( radians( angle )) + 200;
      set_arm( 0, yaxis, zaxis, 0 );
      delay( 1 );
  }
}

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

void convertAllServoToPulse(){
    // Convert all angles to pulse
    base_pos_pulse = angle_to_pulse_length(base_pos);
    shoulder_pos_pulse = angle_to_pulse_length(shoulder_pos);
    elbow_pos_pulse = angle_to_pulse_length(elbow_pos);
    wrist_ver_pos_pulse = angle_to_pulse_length(wrist_ver_pos);
    wrist_rot_pos_pulse = angle_to_pulse_length(wrist_rot_pos);
    gripper_pos_pulse =  angle_to_pulse_length(gripper_pos);
}

void moveServos(){

if (debug_info == true){
       Serial.print("mS:");
       Serial.print(" Base: "); Serial.print(base_pos);
       Serial.print(" Shoulder: "); Serial.print(shoulder_pos);
       Serial.print(" Elbow: "); Serial.print(elbow_pos);
       Serial.print(" Wrist Vert: "); Serial.print(wrist_ver_pos);
       Serial.print(" Wrist Rot: "); Serial.println(wrist_rot_pos);
    }

    applyOffsets();
    
if (debug_info == true){
       Serial.println("-- Apply Offsets --");
       Serial.print("Base: "); Serial.print(base_pos);
       Serial.print(" Shoulder: "); Serial.print(shoulder_pos);
       Serial.print(" Elbow: "); Serial.print(elbow_pos);
       Serial.print(" Wrist Vert: "); Serial.print(wrist_ver_pos);
       Serial.print(" Wrist Rot: "); Serial.println(wrist_rot_pos);
    }
    
    applyLimit();
    
if (debug_info == true){
       Serial.println("-- Apply Limits --");
       Serial.print("Base: "); Serial.print(base_pos);
       Serial.print(" Shoulder: "); Serial.print(shoulder_pos);
       Serial.print(" Elbow: "); Serial.print(elbow_pos);
       Serial.print(" Wrist Vert: "); Serial.print(wrist_ver_pos);
       Serial.print(" Wrist Rot: "); Serial.println(wrist_rot_pos);
    }
    
    convertAllServoToPulse();
    instructSSC32();
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

    //if(gripper_pos > gripper_pos_lim_high){gripper_pos = gripper_pos_lim_high;}
    //if(gripper_pos < gripper_pos_lim_low){gripper_pos = gripper_pos_lim_low;}    

}

int angle_to_pulse_length(float angle){
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
    wrist_ver_pos = wrist_ver_pos - 5;
    wrist_rot_pos = wrist_rot_pos - 12;
    gripper_pos = gripper_pos - 0;
}