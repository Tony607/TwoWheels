// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@open.com.au)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
#include <TimerThree.h>
#include <AccelStepper.h>
#define pinStep1 5
#define pinDirection1 4
#define pinStep2 7
#define pinDirection2 6

AccelStepper stepper1(AccelStepper::DRIVER, pinStep1, pinDirection1);
AccelStepper stepper2(AccelStepper::DRIVER, pinStep2, pinDirection2);
volatile int m1speed = 50; 
volatile int m2speed = -50;
const int led = 13;  // the pin with a LED
void setup()
{  
    pinMode(led, OUTPUT);
	stepper1.setMaxSpeed(1000);
	stepper1.setSpeed(50);
	stepper2.setMaxSpeed(1000);
	stepper2.setSpeed(-50);
	Timer3.initialize(150000);
	Timer3.attachInterrupt(rampSpeed); // blinkLED to run every 0.15 seconds
	Serial.begin(9600);
}

int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void rampSpeed(void){
	if(m1speed < 500){
		m1speed++;
	}
	if(m2speed > -500){
		m2speed--;
	}
	if (ledState == LOW) {
		ledState = HIGH;
		blinkCount = blinkCount + 1;  // increase when LED turns on
	} else {
		ledState = LOW;
	}
	digitalWrite(led, ledState);
}
void loop()
{   
	unsigned long blinkCopy;  // holds a copy of the blinkCount
	noInterrupts();
	stepper1.setSpeed(50);
	stepper2.setSpeed(50);
	blinkCopy = blinkCount;
	interrupts();
	stepper1.runSpeed();
	stepper2.runSpeed();
}
