var serialPort = require("serialport");
serialPort.list(function (err, ports) {
  ports.forEach(function(port) {
    console.log(port.comName);
    console.log(port.pnpId);
    console.log(port.manufacturer);
	//open Arduion serialpot or usb-serial adapter
	if(port.pnpId.indexOf("Arduino")>=0 || port.pnpId.indexOf("usb")>=0){
	var SerialPort = serialPort.SerialPort; // localize object constructor
	var arduinoPort = new SerialPort(port.comName, {
	  baudrate: 115200,
	  parser: serialPort.parsers.readline("#")
	});
	arduinoPort.on("open", function () {
	  console.log('open');
	  process.stdin.pipe(arduinoPort);
	  arduinoPort.on('data', function(data) {
		console.log(data.toString());
		console.log("X");
	  });
	  arduinoPort.write("ls\n", function(err, results) {
		console.log('err ' + err);
		console.log('results ' + results);
	  });
	});	
	}
  });
});
