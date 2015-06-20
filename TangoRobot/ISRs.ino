
//======================================================= ISR for left encoder =======================================================
void encoder_left_ISR()
{
  pulse_us_left=micros()-last_pulse_us_left;                               // time between last state change and this state change
  last_pulse_us_left=micros();                                      // update last_pulse_us_left with time of most recent state change
  pulse_count_left++;                                            // increment left motor distance counter
}


//======================================================= ISR for right encoder ======================================================
void encoder_right_ISR()
{
  pulse_us_right=micros()-last_pulse_us_right;                               // time between last state change and this state change
  last_pulse_us_right=micros();                                      // update last_pulse_us_left with time of most recent state change
  pulse_count_right++;                                            // increment right motor distance counter
}

