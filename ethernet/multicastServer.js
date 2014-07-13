var news = [
    "Borussia Dortmund wins German championship",
    "Tornado warning for the Bay Area",
    "More rain for the weekend",
    "Android tablets take over the world",
    "iPad2 sold out",
    "Nation's rappers down to last two samples"
  ];
 
  var dgram = require('dgram'); 
  var server = dgram.createSocket("udp4"); 
  server.bind( function() {
    server.setBroadcast(true)
    server.setMulticastTTL(128);
    setInterval(broadcastNew, 3000);
  });
  
  
  
  function broadcastNew() {
      var message = new Buffer(news[Math.floor(Math.random()*news.length)]);
      server.send(message, 0, message.length, 5007, "224.1.1.1");
      console.log("Sent " + message + " to the wire...");
  }


  server.on('listening', function () {
      var address = server.address();
      console.log('UDP server listening on ' + address.address + ":" + address.port);
      //server.addMembership('localhost');
  });
  
  server.on('message', function (message, remote) {   
      console.log('A: Have A Client!');
      console.log('B: From: ' + remote.address + ':' + remote.port +' - ' + message);
  });

