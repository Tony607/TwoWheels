
//======================================================= Control speed and direction of left and right motors ==========================================
void MotorControl()
{
   //initialize those local variables to a non zero value since the motor is stopped when started, the count will be zero.
   static unsigned int last_pulse_count_left=255, last_pulse_count_right=255;
   int pwm_temp;
   digitalWrite(stby, HIGH); //disable standby
   //unsigned long actual;                                // stores temporary calculation of actual left and right motor speeds in uS between encoder pulses
   if(set_speed_left<-100) set_speed_left=-100;                         // limit left and right motor speeds to allowed values
   if(set_speed_right<-100) set_speed_right=-100;
   if(set_speed_left>100) set_speed_left=100;
   if(set_speed_right>100) set_speed_right=100;

   //if(micros()-last_pulse_us_left>20000 && set_speed_left!=0) pwm_left+=2;       // jumpstart stalled motor
   //if(micros()-last_pulse_us_right>20000 && set_speed_right!=0) pwm_right+=2;       // jumpstart stalled motor

   digitalWrite(lmIN1pin,set_speed_left>0);                     // set direction of left  motor
   digitalWrite(lmIN2pin,set_speed_left<0);                     // set direction of left  motor
   digitalWrite(rmIN1pin,set_speed_right>0);                     // set direction of right motor
   digitalWrite(rmIN2pin,set_speed_right<0);                     // set direction of right motor
   if(last_pulse_count_left!= pulse_count_left){
      last_pulse_count_left= pulse_count_left;
      if(set_speed_left!=0){
         desired_pulse_us_left = desired_pulse_us_left=1000000/(abs(set_speed_left)*bestspeed/100);          // calculate desired time in uS between encoder pulses
         pwm_temp = pwm_left + KP*((float)pulse_us_left - (float)desired_pulse_us_left)/(pulse_us_left*desired_pulse_us_left);
      } else {
         pwm_temp = 0;
      }
      if(pwm_temp > 255){
         pwm_temp = 255;
      } else if(pwm_temp < 20){
         pwm_temp = 20;
      }
      pwm_left= pwm_temp;

#ifdef OPENLOOPTEST
      analogWrite(lmpwmpin,128);                          // update speed for left  motor
#else
      analogWrite(lmpwmpin,pwm_left);
#endif
   }
   if(last_pulse_count_right!= pulse_count_right){
      last_pulse_count_right= pulse_count_right;
      if(set_speed_right!=0){
         desired_pulse_us_right=1000000/(abs(set_speed_right)*bestspeed/100);          // calculate desired time in uS between encoder pulses
         pwm_temp = pwm_right + KP*((float)pulse_us_right - (float)desired_pulse_us_right)/(pulse_us_right*desired_pulse_us_right);
      } else {
         pwm_temp = 0;
      }
      if(pwm_temp > 255){
         pwm_temp = 255;
      } else if(pwm_temp < 20){
         pwm_temp = 20;
      }
      pwm_right = pwm_temp;
      //if(desired_pulse_us_right>pulse_us_right && pwm_right>0) pwm_right -= (desired_pulse_us_right - pulse_us_right);                  // if motor is running too fast then decrease PWM
      //if(desired_pulse_us_right<pulse_us_right && pwm_right<254) pwm_right += (pulse_us_right - desired_pulse_us_right);                // if motor is running too slow then increase PWM
#ifdef OPENLOOPTEST
      analogWrite(rmpwmpin,255);                          // update speed for right  motor
#else
      analogWrite(rmpwmpin,pwm_right);
#endif
   }
}

/*
Power    SC/sec     μS/SC
100%  =   1900  =   526μS
90%  =   1710  =   585μS
80%  =   1520  =   658μS
70%  =   1330  =   751μS
60%  =   1140  =   877μS
50%  =    950  =  1053μS
40%  =    760  =  1316μS
30%  =    570  =  1754μS
20%  =    380  =  2631μS
10%  =    190  =  5263μS
1%  =     19  = 52632μS 
*/

