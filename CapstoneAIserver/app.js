#!/usr/bin/env node

var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var index = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', index);
app.use('/users', users);

//-----------------------------Connection Between Unity & Graph Module--------------------
var Socket = require('socket.io');
var socketEvents = require('./socket.js');
const server = app.listen(6110, function () {
    console.log("Unity Socket App on port 6110");
});

const io = new Socket(server);
var net = require('net');

var exec = require('child_process').exec;
exec('ulimit', ['-s 1073741824']);

//, ['-Wl,--stack,1073741824,--heap,1073741824 -j 4']
// var spawn = require('child_process').spawn;
// GraphSocket = spawn('./_PreGraphModule');
// GraphSocket.stdout.on('data', function (log) {
//     console.log('==========================MODULE OUTPUT====================================================');
//     console.log("MODULE > " + log.toString());
//     console.log('===========================================================================================');
// });
socketEvents(io, net);
//=====================================================================================

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

module.exports = app;
