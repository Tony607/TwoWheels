var dgram = require('dgram');
var message = new Buffer("Some bytes");
var client = dgram.createSocket("udp4");
client.send(message, 0, message.length, 1337, "192.168.2.23", function (err, bytes) {
	client.close();
});