
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the command is complete
char inByte = 0;         // incoming serial byte
int proto_kp = 0;
int proto_ki = 0;
int proto_kd = 0;
int proto_steeering = 0;
int proto_Throttle = 0;
int getSteering(){return proto_steeering;}
int getThrottle(){return proto_Throttle;}
int getP(){return proto_kp;}
int getI(){return proto_ki;}
int getD(){return proto_kd;}
uint8_t parseLenProto(){
	uint8_t returnValue = 0;
	if (Serial.available() > 0) {
		// get incoming byte:
		inByte = Serial.read();
		// if the incoming character is a '$', set a flag
		// so the main loop can do something about it:
		if (inByte == '$') { // end sign
			stringComplete = true;
			returnValue = parseString(inputString);
		} else if(inByte == '@'){ // start sign
			inputString = "";
		} else { // stack up
			inputString += String(inByte);
		}
	}
	return returnValue;
}

uint8_t parseString(String str){
	uint8_t returnValue = 0;
	int endindex = 0;
	String subString = str;
	while(str.length() > 0){
		endindex = str.indexOf('#');
		if(endindex < 0){//-1 not found
			break;
		}
		subString = str.substring(0, endindex);
		returnValue = processSubString(subString);
		if(endindex+1 >= str.length()){//reach end of str
			break;
		}
		str = str.substring(endindex+1);
	}
	return returnValue;
}
uint8_t processSubString(String str){
	uint8_t returnValue = 0;
	char cmd = str.charAt(0);
	uint16_t value = str.substring(1).toInt();
	switch (cmd)
	{
		case 'T'://throttle
			proto_Throttle = value;
			returnValue = CONTROLVAL;
			break;
		case 'S'://steering
			proto_steeering = value;
			returnValue = CONTROLVAL;
			break;
		case 'P':
			proto_kp = value;
			returnValue = PIDVAL;
			break;
		case 'I':
			proto_ki = value;
			returnValue = PIDVAL;
			break;
		case 'D':
			proto_kd = value;
			returnValue = PIDVAL;
			break;
		default:
			break;
	}
	return returnValue;
}
