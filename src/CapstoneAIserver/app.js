#!/usr/bin/env node

var express = require('express');

var cluster = require('cluster');
cluster.schedulingPolicy = cluster.SCHED_RR;

var os = require('os');
var Redis = require('redis');
var RedisServer = require('redis-server');
var rserver = new RedisServer(6379);
rserver.open((err) => { if (err) throw err; });
var redis = Redis.createClient(6379, 'localhost');

var order_identifier = 'order';
var board_identifier = 'board';

var modules = [];
var tmp;

function client_connection(data) {
  redis.rpush('users', data.id, function(err, res) {
    if (err) throw err;
  });
  return data.id;
}

function client_disconnection(data) {
  redis.lrem('users', 0, data.id, function(err, res) {
    if (err) throw err;
  });
}

function module_connection(data) {
  // redis.rpush('modules', data.name, function(err, res) {
  //   if (err) throw err;
  //   redis.set(data.name, 0);
  // });
  modules.push({
    id: data.id,
    status: 0,
    value: data
  });
}

function module_disconnection(data) {
  // delete modules.data.id;

  // redis.lrem('modules', 0, data.name, function(err, res) {
  //   if (err) throw err; 
  // });
}

function find_idle_module() {
  // redis.lrange('modules', 0, -1, function (error, module_id) {
  //   if (error) throw error
  //     var picked = modules.find(o => o.key == module_id);
  //     console.log(picked);
  //     if(redis.get(module_id) == 0) {
  //       redis.set(module_id, 1);
  //       return picked.value;
  //     }
  // });
  var selected = modules.find(o => o.status == 0);
  // modules.find(o => o.status == 0).status = 1;
  // console.log('Find: ' + selected.id)
  return selected;
}

function parse_fomula(data) {
  var parsed = data.toString().split(' ');
  var identifier = parsed[0];
  var socket_id = parsed[1];

  if(identifier == order_identifier) {
    var order = parsed[2];

    return {
      identifier : order_identifier,
      socket_id : socket_id, 
      order : order
    };
  }
  else {
    var prev_pos = parsed[2];
    var next_pos = parsed[3];

    return {
      identifier : board_identifier,
      socket_id : socket_id, 
      prev_pos : prev_pos, 
      next_pos : next_pos
    };
  }
}


//-----Connection Between Unity & Graph Module-----

if (cluster.isMaster) {
  let workers = []
  //create worker as posible as the cpu can manage it
  os.cpus().forEach(function (cpu) {
      const worker = cluster.fork();
      workers.push(worker);

    cluster.on('online', function (worker) {
    // console.log('created worker id : ' + worker.process.pid);
    });

  //if worker dead
    cluster.on('exit', function(worker, code, signal) {
      console.log('worker exit : ' + worker.id);
      if (code == 200) { cluster.fork(); }
    });
  });

  // before start service, clean all databases
  redis.flushall( function (err, res) {
    console.log(res); // will be true if successfull
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
    // console.log('PID [' + cluster.worker.process.pid + '] ' + 'Socket.IO Server');
  });
  net_server.listen(6120, function() {
    // console.log('NET server listening on port 6120');
    // console.log('PID [' + cluster.worker.process.pid + '] ' + 'NET Server');
  })

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
        clients.forEach(function (client) { 
          console.log('users : ' + client);
        });
      });
      modules.forEach(function(module) {
        console.log('module : ' + module.id.toString());
      })
    });

    socket.on('Order', function(data) {
      // console.log(data);
      var parsed_data = JSON.parse(data);
      var fomula = order_identifier + ' ' + socket.id + ' ' + parsed_data.toString();
      console.log('fomula: ' + fomula);

      //redis에서 module를 활성화 상태로 표시
      // var net_socket = find_idle_module();
      // console.log("module id: " + net_socket.id);
      // net_socket.write(fomula); // correction needed
      tmp.write(fomula);
    });

    socket.on('Request', function(data) {
      // console.log(data);
      var parsed_data = JSON.parse(data);
      var fomula = board_identifier + ' ' + socket.id + ' ' +
      parsed_data.Host.toString() + ' ' + parsed_data.Board.toString();
      console.log('fomula: ' + fomula);

      // var net_socket = find_idle_module();
      // console.log("module id: " + net_socket.id);
      // net_socket.write(fomula); // correction needed
      tmp.write(fomula);
    });

    socket.on('Disconnect', function() {
      console.log("Client Disconnect");
      //remove client from user database
      client_disconnection(socket);
      socket.disconnect();
    });
  });

  //worker queue에는 module, socket_id 형식으로 저장 할 예정.

    // TCP server connection access
  net_server.on('connection', function(socket) {
    console.log('New Module Connected (worker pid: ' + cluster.worker.process.pid + 
      ' ID : ' + socket.remoteAddress + ':' + socket.remotePort + ')');
    socket.id = (Math.random()+1).toString(36).slice(2, 18);
    module_connection(socket);

    tmp = socket;

    socket.on('data', function(data) {
      console.log("from graph: " + data);
      response = parse_fomula(data);

      if (response.identifier == board_identifier) {
        io.to(response.socket_id).emit('Response', response.prev_pos + ' ' + response.next_pos);
        console.log('From: ' + cluster.worker.process.pid);
      }

      else if (response.identifier == order_identifier) {
        io.to(response.socket_id).emit('AI_Order', response.order); 
        console.log('From: ' + cluster.worker.process.pid);
      }
    });

    socket.on('end', function() {
      console.log(socket.remoteAddress + ':' + socket.remotePort + ' Module Disconnect');
      module_disconnection(socket);
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
