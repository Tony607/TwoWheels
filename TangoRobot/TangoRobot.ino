#include "IOpins.h"
#include "Constants.h"



// define global variables here
volatile unsigned int pulse_us_left=100000;                      // width of left and right encoder pulses in uS
volatile unsigned int pulse_us_right=100000;                      // width of left and right encoder pulses in uS
volatile unsigned int pulse_count_left,pulse_count_right;                      // left and right pulse counters to measure distance

byte pwm_left = 21,pwm_right = 21;                                           // left and right motor speeds pwm generated from the processor
int set_speed_left,set_speed_right;                                        // left and right motor speeds requested by the user -100~100
unsigned long bestspeed=maxspeed;                         // encoder pulses per second for speed=100% (less than actual to allow for load)
unsigned int batvolt;                                     // battery voltage to 2 decimal places e.g. 751 = 7.51V
unsigned long last_motor_update_MS;                                      // "no go" timer used to re-start motors when both motors stopped
unsigned long btime;                                      // timer used to check battery voltage
unsigned long last_debug_us;
volatile unsigned long last_pulse_us_left;                             // remembers time of left  encoders last state change in uS
volatile unsigned long last_pulse_us_right;                             // remembers time of right encoders last state change in uS

unsigned long desired_pulse_us_left;
unsigned long desired_pulse_us_right;

//comm
int inByte = 0;         // incoming serial byte
unsigned char comm_read_state = 0;
bool new_speed_data = false;

/// <summary>
/// Setups this instance.
/// </summary>
void setup()
{
  pinMode(stby, OUTPUT);
  pinMode(lmIN1pin,OUTPUT);
  pinMode(lmIN2pin,OUTPUT);
  pinMode(rmIN1pin,OUTPUT);
  pinMode(rmIN2pin,OUTPUT);
  pinMode(lmpwmpin,OUTPUT);
  pinMode(rmpwmpin,OUTPUT);
  
  digitalWrite(lmencpin,1);                               // enable pullup resistor for left  encoder sensor
  digitalWrite(rmencpin,1);                               // enable pullup resistor for right encoder sensor
  attachInterrupt(0,encoder_left_ISR,CHANGE);                     // trigger left  encoder ISR on state change
  attachInterrupt(1,encoder_right_ISR,CHANGE);                     // trigger right encoder ISR on state change
  set_speed_left=0;set_speed_right=0;
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  SERIAL_PORT.begin(115200);
}



void loop()
{ 
	if (SERIAL_PORT.available() > 0) {
		// get incoming byte:
		inByte = SERIAL_PORT.read();
		stateMachine(inByte);
      if(new_speed_data){
			new_speed_data = false;
		}
	}
  //======================================================== Motor Speed Control =========================================================
  if(millis()-last_motor_update_MS>MOTOR_CONTROL_INTERVAL_MS)                                  // Call motor control function every mS
  {
    last_motor_update_MS=millis();                                       // reset motor timer
    MotorControl();                                       // update motor speeds    
    
#ifdef MEASURE_BATTERY_V
    unsigned int temp;                                      // temporary variable for calculationa
    batvolt=analogRead(powerpin);                         // read battery voltage  
    temp=50*batvolt/maxvolt*batvolt/maxvolt*(maxspeed/50);// calculate best possible speed with available battery voltage as an integer
    bestspeed=long(temp);                                 // convert to long                                
#endif
  }
  if(millis()-last_debug_us > DEBUG_PRINT_INTERVAL_MS){//every 50ms/20hz
     last_debug_us = millis();
     printData();
  }
  
  //======================================================== Your Code ====================================================================
  
  // The tutorial for this code can be found here: http://letsmakerobots.com/node/38636
  
  // Adjust the maxvolt and maxspeed values in the "Constants.h" tab to suit your battery and gearbox as instructed in the tutorial
  // Adjust the IO pin definitions in the "IOpins.h" tab to suit your controller and wiring scheme
  
  // Use the variable set_speed_left to control the left  motor speed. -100 to +100.  Negative values indicate reverse direction
  // Use the variable set_speed_right to control the right motor speed. -100 to +100.  Negative values indicate reverse direction
  
  // use the variables pulse_count_left and pulse_count_right to measure distance travelled. These counters increment every time the encoders output changes state
  // for best accuracy, make sure the robot comes to a complete stop before resetting the counters
}












