#!/usr/bin/env node

var express = require('express');

var cluster = require('cluster');
cluster.schedulingPolicy = cluster.SCHED_RR;

var os = require('os');
var redis = require('redis');

//-----Connection Between Unity & Graph Module-----
// var socketEvents = require('./socket.js');
// // const server = app.listen(6110, function () {
// //     //console.log("Unity Socket App on port 6110");
// // });
// var server = require('http').Server(app);
// var io = require('socket.io')(server);
// var net = require('net');

// server.listen(6000);
var pub = redis.createClient(10000, "127.0.0.1");
var sub = redis.createClient(10000, "127.0.0.1");
var store = redis.createClient(10000, "127.0.0.1");

if (cluster.isMaster) {

  //create worker as posible as the cpu can manage it
  os.cpus().forEach(function (cpu) {
        cluster.fork();
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
  var socketEvents = require('./socket.js');
  // const server = app.listen(6110, function () {
  //     //console.log("Unity Socket App on port 6110");
  // });
  var server = require('http').Server(app);
  var io = require('socket.io')(server);
  var net = require('net');

  server.listen(6000);

  io.configure(function() {
    io.set('log level', 1);
    io.set('store', new io.RedisStore({
      redis: redis,
      redisPub: pub,
      redisSubL: sub,
      redisClient: store
    }));
  });

  // socketEvents(io, net);
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
