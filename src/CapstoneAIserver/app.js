#!/usr/bin/env node

var express = require('express');

var cluster = require('cluster');
cluster.schedulingPolicy = cluster.SCHED_RR;

var os = require('os');
var redis = require('socket.io-redis');

var clients = [];

function client_connection(data) {
  var game_id = (Math.random()+1).toString(36).slice(2, 18);
  var client_info = new Object();
  client_info.socket_id = data.id;
  client_info.game_id = game_id;
  clients.push(client_info);

  return game_id;
}

function print_clients(cluster) {
  if (!(cluster.isMaster)) {
    console.log('worker id : ' + cluster.worker.process.id);
    console.log('current worker clients : ');
    for(var idx in clients) {
      console.log(clients[idx]);
    }
  }
}


//-----Connection Between Unity & Graph Module-----

if (cluster.isMaster) {
  //create worker as posible as the cpu can manage it
  os.cpus().forEach(function (cpu) {
        cluster.fork();
  });

  cluster.on('online', function (worker) {
    console.log('created worker id : ' + worker.process.pid);
  });

  //if worker dead
  cluster.on('exit', function(worker, code, signal) {
    console.log('worker exit : ' + worker.id);

    if (code == 200) {
      cluster.fork();
    }

  });
}
else {
  var app = express();
  var net = require('net')
  var io_server = require('http').createServer(app);
  var io = require('socket.io')(io_server);
  var net_server = net.createServer();

  io_server.listen(6110, function() {
    console.log('Socket IO server listening on port 6110');
  });
  net_server.listen(6120, function() {
    console.log('NET server listening on port 6120');
  })

  io.adapter(redis({
    host:'localhost',
    port:6379
  }));

  // TCP server connection access
  net_server.on('connection', function(socket) {
    console.log('New Module Connected (ID : ' + socket.id + ')');

    socket.on('data', function(data) {
      console.log(data);
    });
    socket.on('end', function() {
      console.log(socket.id + ' Module Disconnect');
    });
  });

  // TCP server connection end
  net_server.on('close', function(){
      console.log('server closed...');
  })

  // TCP server connection error
  net_server.on('error', function(err){
      console.log('error'+err.message);
  })



  io.on('connection', function(socket) {
    console.log('New Client Connected (ID : ' + socket.id + ')');
    console.log('worker id : ' + cluster.worker.id + 
      ", worker pid: " + cluster.worker.process.pid);

    socket.emit('Initialize', client_connection(socket));

    socket.on('Order', function(data) {
      console.log(data);
      var parsed_data = JSON.parse(data);
      // net_server.write('order|' + parsed_data.order.toString());
    });

    socket.on('Request', function(data) {
      console.log(data);
      var parsed_data = JSON.parse(data);
      // net_server.write(parsed_data.Host.toString() + '|' + 
      //   parsed_data.Board.toString());
    });

    socket.on('Disconnect', function() {
      console.log("Client Disconnect");

      //remove client from user database
      for (var i = 0; i < clients.length; i++) {
        var client = clients[i];
        if (client.id == socket.id) {
          client.splice(i, 1);
          break;
        }
      }

      socket.disconnect();
    });

  });

  // catch 404 and forward to error handler
  app.use(function (req, res, next) {
      var err = new Error('Not Found');
      err.status = 404;
      next(err);
  });

  // error handler
  app.use(function (err, req, res, next) {
      // set locals, only providing error in development
      res.locals.message = err.message;
      res.locals.error = req.app.get('env') === 'development' ? err : {};

      // render the error page
      res.status(err.status || 500);
      res.render('error');
  });
}

module.exports = app;
