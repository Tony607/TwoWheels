var net = require('net');
//Parse host and port from command-line arguments
var host = process.argv[2];
var port = Number(process.argv[3]);
//Create socket instance and begin connecting to server
var socket = net.connect(port, host);
//Handle connect event when a connection to server is established
socket.on('connect', function () {
	//Pipe process's stdin to socket
	process.stdin.pipe(socket);
	//Pipe socket's data to process's stdout
	socket.pipe(process.stdout);
	//Call resume() on stdin to begin reading data
	//only necessary for node prior v0.10
	//process.stdin.resume();
});
//Pause stdin when end event happens
socket.on('end', function () {
	process.stdin.pause();
});