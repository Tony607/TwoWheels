
/**comm_read_state machine to parse serial data to set 2 motor speed*/
void stateMachine(unsigned char newbyte){
   switch (comm_read_state)
   {
   case INITIAL_STATE:
      if(newbyte == START_BYTE){
         comm_read_state = READ_LEFT;
      }else{
         comm_read_state = INITIAL_STATE;
      }
      break;
   case READ_LEFT:
      if(newbyte == START_BYTE){
         comm_read_state = INITIAL_STATE;
      }else {
         set_speed_left = (int)newbyte - 100;
         comm_read_state = READ_RIGHT;
      }
      break;
   case READ_RIGHT:
      if(newbyte == START_BYTE){
         comm_read_state = INITIAL_STATE;
      }else {
         set_speed_right = (int)newbyte - 100;
         new_speed_data = true;
         //State Machine cycle is complete
         comm_read_state = INITIAL_STATE;
      }
      break;
   default:
      comm_read_state = INITIAL_STATE;
      break;
   }
}
/// <summary>
/// Prints the data.
/// </summary>
void printData(){//initialize those local variables to a non zero value since the motor is stopped when started, the count will be zero.
   static unsigned int last_pulse_count_left=255, last_pulse_count_right=255;
   if(last_pulse_count_left!= pulse_count_left || last_pulse_count_right!= pulse_count_right){
      last_pulse_count_left= pulse_count_left;
      last_pulse_count_right= pulse_count_right;
      SERIAL_PORT.print("P");
      SERIAL_PORT.print(pulse_count_left);
      SERIAL_PORT.print(":");
      SERIAL_PORT.println(pulse_count_right);
   }
}