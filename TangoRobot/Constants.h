
#define maxvolt   1200                                      // 100% battery voltage
#define maxspeed 680                                      // encoder pulses per second for speed=100% with battery at 100%
#define MOTOR_CONTROL_INTERVAL_MS 30
#define DEBUG_PRINT_INTERVAL_MS 100


#define INITIAL_STATE 0
#define READ_LEFT 1
#define READ_RIGHT 2
#define READ_SERVO2 3
#define START_BYTE 0XFF

#define KP 305820
#define SERIAL_PORT Serial