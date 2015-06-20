
// define IO pins
//Encoder pins
#define lmencpin    2                                     //  D2/INT0, left encoder
#define rmencpin    3                                     //  D3/INT1, right encoder
//Output pins for motors
#define lmIN1pin    7
#define lmIN2pin    8
#define lmpwmpin    9                                     //  D9  left  motor PWM

#define rmIN1pin    14
#define rmIN2pin    15
#define rmpwmpin    10                                     //  D10 right motor PWM
#define stby        16
//Battery voltage measurement analog pin
//#define MEASURE_BATTERY_V
#ifdef MEASURE_BATTERY_V
#define powerpin    A0                                     //  A7  monitors battery voltage
#endif
//#define OPENLOOPTEST