#define CAPTURE 13
#define TRIG 3
#define ledPin 2

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
  TCCR3B |= (1 << WGM32);   // CTC mode
  TCCR3B |= (1 << CS32);    // 256 prescaler 
  //TIMSK3 |= (1 << OCIE3A);  // enable timer compare interrupt
  TIMSK3 |= ((1 << ICIE3)| (1 << TOIE3));   //Set capture interrupt
  interrupts();             // enable all interrupts
  TCCR3B |= (1 << ICNC3);               // Input Capture Noise Canceler
  TCCR3B |= (1 << ICES3);               //Set capture rising edge
  Serial1.begin(115200);
}

ISR(TIMER3_COMPA_vect)          // timer compare interrupt service routine
{
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
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
	Serial1.println(TCNT3);
	Serial1.print("W");
	Serial1.println(pulseWidth);
	digitalWrite(TRIG, digitalRead(TRIG) ^ 1);
}
