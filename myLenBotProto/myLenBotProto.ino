
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the command is complete
char inByte = 0;         // incoming serial byte
int kp = 0;
int ki = 0;
int kd = 0;
uint32_t time = 1000;
void setup()
{
	// start physical serial port at 115200 bps
	Serial.begin(115200);
}

void loop()
{
	
	// if we get a valid byte
	if (Serial.available() > 0) {
		// get incoming byte:
		inByte = Serial.read();
		// if the incoming character is a '$', set a flag
		// so the main loop can do something about it:
		if (inByte == '$') { // end sign
			stringComplete = true;
			parseString(inputString);
		} else if(inByte == '@'){ // start sign
			inputString = "";
		} else { // stack up
			inputString += String(inByte);
		}
	} else {
		if(millis() > time){
			time = millis()+100;
			Serial.print("kp=");Serial.print(kp);Serial.print("\t");
			Serial.print("ki=");Serial.print(ki);Serial.print("\t");
			Serial.print("kd=");Serial.print(kd);Serial.println("#");
			//Serial.println(inputString.concat(12345));
		}
	}
}
void parseString(String str){
	int endindex = 0;
	String subString = str;
	while(str.length() > 0){
		endindex = str.indexOf('#');
		if(endindex < 0){//-1 not found
			break;
		}
		subString = str.substring(0, endindex);
		processSubString(subString);
		if(endindex+1 >= str.length()){//reach end of str
			break;
		}
		str = str.substring(endindex+1);
	}
}
void processSubString(String str){
	char cmd = str.charAt(0);
	uint16_t value = str.substring(1).toInt();
	switch (cmd)
	{
		case 'P':
			kp = value;
			break;
		case 'I':
			ki = value;
			//Serial.println("set I = ");
			break;
		case 'D':
			kd = value;
			//Serial.println("set D = ");
			break;
		default:
			break;
	}
}
