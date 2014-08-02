// var SerialPort  = require('serialport').SerialPort;
// var portName = 'COM3';
var emulateSerialData = false;
var http = require('http');

var express = require('express'), app = express();
var io = require('socket.io');
var server = http.createServer(app);
var arduinoPort;
io = io.listen(server); //this return the new object we want to listen to
server.listen(8888);

app.set('views', __dirname + '/');
//serving files in ./js
app.use(express.static(__dirname + '/'));

app.get('/', function (req, res) {
	var homePage = process.argv[2]? process.argv[2]: 'index.html';
	console.log("send file: "+homePage);
	res.sendfile(homePage);
});

// var sp = new SerialPort(); // instantiate the serial port.
/*sp.open(portName, { // portName is instatiated to be COM3, replace as necessary
baudRate: 9600, // this is synced to what was set for the Arduino Code
dataBits: 8, // this is the default for Arduino serial communication
parity: 'none', // this is the default for Arduino serial communication
stopBits: 1, // this is the default for Arduino serial communication
flowControl: false // this is the default for Arduino serial communication
});*/
function arduProto(functionCode, setvalue){
	if(functionCode.length===1){//one function code
		return String(functionCode+setvalue+"#");
	}else if (functionCode.length > 1){
		var funLength = functionCode.length;
		var result = "@";//start sign
		for(var i = 0;i< funLength;i++){
			result += functionCode[i]+setvalue[i]+"#"
		}
		result += "$";//end sign
		return result;
	}
	
}
io.sockets.on('connection', function (socket) {
	// If socket.io receives message from the client browser then
	// this call back will be executed.
	socket.on('message', function (msg) {
		if(msg.length===3){
			console.log("P="+msg[0]+"\tI="+msg[1]+"\tD="+msg[2]);
			var sendData = arduProto("PID", msg);
			console.log(sendData);
			if(arduinoPort){
				arduinoPort.write(sendData, function (err, results) {
					console.log('err ' + err);
					console.log('results ' + results);
				});
			}
		}		
	});
	socket.on('move', function (msg) {
		console.log("X="+msg.x.toFixed()+"\tY="+msg.y.toFixed());
		var moveArray = [msg.x.toFixed(),msg.y.toFixed()];
		var sendData = arduProto("ST", moveArray);
		console.log(sendData);
		if(arduinoPort){
			arduinoPort.write(sendData, function (err, results) {
				console.log('err ' + err);
				console.log('results ' + results);
			});
		}
	});
	// If a web browser disconnects from Socket.IO then this callback is called.
	socket.on('disconnect', function () {
		console.log('disconnected');
	});
});
// var cleanData = ''; // this stores the clean data
// var readData = '';  // this stores the buffer
// sp.on('data', function (data) { // call back when data is received
// readData += data.toString(); // append data to buffer
// if the letters 'A' and 'B' are found on the buffer then isolate what's in the middle
// as clean data. Then clear the buffer.
// if (readData.indexOf('B') >= 0 && readData.indexOf('A') >= 0) {
// cleanData = readData.substring(readData.indexOf('A') + 1, readData.indexOf('B'));
// readData = '';
// io.sockets.emit('message', cleanData);
// }
// });
var angle = 0;
Vector3 = function ( x, y, z ) {

	this.x = x || 0;
	this.y = y || 0;
	this.z = z || 0;

};
var vect = new Vector3( Math.sqrt(1/3), Math.sqrt(1/3), Math.sqrt(1/3) );
Quaternion = function ( x, y, z, w ) {

	this._x = x || 0;
	this._y = y || 0;
	this._z = z || 0;
	this._w = ( w !== undefined ) ? w : 1;

};
Quaternion.prototype = {

	constructor: Quaternion,

	_x: 0,_y: 0, _z: 0, _w: 0,

	get x () {
		return this._x;
	},

	set x ( value ) {
		this._x = value;
	},

	get y () {
		return this._y;
	},

	set y ( value ) {
		this._y = value;
	},

	get z () {
		return this._z;
	},

	set z ( value ) {
		this._z = value;
	},

	get w () {
		return this._w;
	},

	set w ( value ) {

		this._w = value;
	},

	set: function ( x, y, z, w ) {

		this._x = x;
		this._y = y;
		this._z = z;
		this._w = w;
		return this;
	},
	
	setFromAxisAngle: function ( axis, angle ) {
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
		// assumes axis is normalized
		var halfAngle = angle / 2, s = Math.sin( halfAngle );

		this._x = axis.x * s;
		this._y = axis.y * s;
		this._z = axis.z * s;
		this._w = Math.cos( halfAngle );

		return this;

	},
};

setInterval(function () {
	if (emulateSerialData) {
		if (angle < Math.PI * 2.0) {
			angle += Math.PI / 300.0;
		} else {
			angle = 0;
		}
		var quaternion = new Quaternion();
		quaternion.setFromAxisAngle( vect, angle );
		io.sockets.emit('message', quaternion);
	}
}, 20);


if (!emulateSerialData) {
	var serialPort = require("serialport");	
	console.log("---available serial ports---");
	serialPort.list(function (err, ports) {
		ports.forEach(function (port) {
			console.log(port.comName);
			console.log("pnpId:\t"+port.pnpId);
			console.log("manufacturer:\t"+port.manufacturer);
			if ((port.pnpId+port.manufacturer).indexOf("Arduino") >= 0) {
				console.log("---Arduino port found---");
				var serialport = require("serialport");
				var SerialPort = serialport.SerialPort; // localize object constructor
				arduinoPort = new SerialPort(port.comName, {
						baudrate : 115200,
						parser : serialPort.parsers.readline("#")
					});
				arduinoPort.on("open", function () {
					console.log('open');
					arduinoPort.on('data', function (data) {
						console.log(data.toString());
						var str_parser = /^(-?\d+\.?\d*?):(-?\d+\.?\d*?):(-?\d+\.?\d*?):(-?\d+\.?\d*?)$/;
						var parsedArray = str_parser.exec(data.toString());
						if(parsedArray){
							var msg_q=new Quaternion(parseFloat(parsedArray[2]),parseFloat(parsedArray[3]),parseFloat(parsedArray[4]),parseFloat(parsedArray[1]));
						}
						io.sockets.emit('message', msg_q);
						console.log("X");
					});
					arduinoPort.write("ls\n", function (err, results) {
						console.log('err ' + err);
						console.log('results ' + results);
					});
				});
			}else{
				console.log("---No Arduino Port discovered, using emulated serial data---");
				emulateSerialData = true;
			}
		});
	});
}
