#!/usr/bin/env node

var express = require('express');

var cluster = require('cluster');
cluster.schedulingPolicy = cluster.SCHED_RR;

var os = require('os');
var Redis = require('redis');
var redis = Redis.createClient(6379, 'localhost');

var clients = redis.multi();

function client_connection(data) {
  clients.rpush("users", data.id);
  clients.exec(function(err, res) {
    if(err) throw err;
  })
  return data.id;;
}

function client_disconnection(data) {
  redis.lrem('users', 0, data.id, function(err, res) {
    if (err) throw err
  });
}

//-----Connection Between Unity & Graph Module-----

if (cluster.isMaster) {
  //create worker as posible as the cpu can manage it
  os.cpus().forEach(function (cpu) {
        cluster.fork();
  });

  cluster.on('online', function (worker) {
    // console.log('created worker id : ' + worker.process.pid);
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
    // console.log('Socket IO server listening on port 6110');
    console.log('PID [' + cluster.worker.process.pid + '] ' +
    'Socket.IO Server');
  });
  net_server.listen(6120, function() {
    // console.log('NET server listening on port 6120');
  })

  redis.on('subscribe', function(channel, data) {
    console.log("client subscribe channel " + channel );
  });
  redis.on("message", function (channel, message) {
    console.log("client message channel " + channel + ": " + message);
  });

  io.on('connection', function(socket) {
    console.log('worker id : ' + cluster.worker.id + 
      ", worker pid: " + cluster.worker.process.pid + 
      ' New Client Connected ID : ' + socket.id);

    socket.emit('Initialize', client_connection(socket));
    //받은 클라이언트 아이디를 모든 node가 공유할 수 있는 배열에 저장한다.
    //Request일 때는 socket.id와 데이터를 쌍으로 만들어 모두가 공유하는 큐에 넣고 모듈로 일을 넘기고 기다린다.
    //Response에 socket.id를 기반으로 다시 데이터를 송신한다.

    socket.on('test', function(data) {
      console.log(cluster.worker.process.pid);
      redis.lrange('users', 0, -1, function (error, clients) {
      if (error) throw error
        clients.forEach(function (client) { console.log(client); });
      });
    });

    socket.on('Order', function(data) {
      console.log(data);
      var parsed_data = JSON.parse(data);
      net_server.write('order|' + parsed_data.order.toString());
    });

    socket.on('Request', function(data) {
      console.log(data);
      var parsed_data = JSON.parse(data);
      net_server.write(parsed_data.Host.toString() + '|' + 
        parsed_data.Board.toString());
    });

    socket.on('Disconnect', function() {
      console.log("Client Disconnect");
      //remove client from user database
      client_disconnection(socket);
      socket.disconnect();
    });
  });

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
