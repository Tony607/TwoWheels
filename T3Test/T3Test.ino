#define CAPTURE 13
#define TRIG 3
#define ledPin 2
//new pull
volatile unsigned int pulseWidth = 2013;

void setup()
{
  pinMode(CAPTURE, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(TRIG, OUTPUT);
  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;

  OCR3A = 65533;            // compare match register 16MHz/256/2Hz
  TCCR3B |= (1 << CS32);    // 256 prescaler 
  TIMSK3 |= ((1 << ICIE3)| (1 << TOIE3));   //Set capture interrupt
  interrupts();             // enable all interrupts
  TCCR3B |= (1 << ICNC3);               // Input Capture Noise Canceler
  TCCR3B |= (1 << ICES3);               //Set capture rising edge
}

ISR(TIMER3_CAPT_vect){
	if(TCCR3B & (1 << ICES3)){
		TCNT3  = 0;
		digitalWrite(ledPin, HIGH);
	}else{
	  digitalWrite(ledPin, LOW);
      pulseWidth = ICR3;               //copy capture value
	}
	TCCR3B ^= 1 << ICES3;
}
void loop()
{
	delay(50);
	Serial.println(TCNT3);
	Serial.print("D");
	Serial.println(pulseWidth*0.2616);
	digitalWrite(TRIG, digitalRead(TRIG) ^ 1);
}
