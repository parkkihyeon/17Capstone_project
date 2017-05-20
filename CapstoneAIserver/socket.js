/**
 * Created by Netapp on 2017-04-01.
 */

var _Socket_;

// io = FROM UNITY ENGINE & _Socket_ = FROM GRAPH ENGINE

module.exports = function (io, net) {
//-----------------------------CONNECTION BETWEEN GRAPH ENGINE---------------------------------------------------------
    net.createServer(function (_socket) {
        // IDENTIFY THIS CLIENT
        _socket.name = _socket.remoteAddress + ":" + _socket.remotePort
        _Socket_ = _socket;

        console.log('==========================SERVER OUTPUT====================================================');
        process.stdout.write(_socket.name + " GRAPH MODULE CONNECTED\n", _Socket_)

        // HANDLE INCOMING MESSAGES FROM CLIENTS.
        _Socket_.on('data', function (data) {
            console.log('==========================DATA FROM GRAPH==================================================');
            //process.stdout.write(_Socket_.name + "> " + data + "\n", _Socket_);

            var tempsR = data.toString().split('|');

            //CHECK IF RECEIVED DATA IS ORDER OR BOARD
            if (tempsR[0] == 'ORDER') {
                var _AI_Order = tempsR[1];
                io.emit('AI_Order', _AI_Order);
                console.log('AI Unit Order: ' + _AI_Order);
            }
            else {
                // SEND LOCATIONS TO UNITY CLIENT
                var nextPos = tempsR[1];
                io.emit('Response', nextPos);
                console.log("JSON DATA TRANSMIT: " + nextPos);
            }
        });

        // REMOVE THE CLIENT FROM THE LIST WHEN IT LEAVES
        _Socket_.on('end', function () {
            process.stdout.write(_Socket_.name + " Graph Module Disconnected.\n");
        });
    }).listen(6120);
    console.log("Graph Socket App on port 6120");
//-----------------------------CONNECTION BETWEEN UNITY ENGINE----------------------------------------------------------
    io.on('connection', function (socket) {
        console.log('==========================SERVER OUTPUT====================================================');
        console.log('Unity Game Engine Connected');

        io.emit('Initialize', "START");

        socket.on('Order', function (_order) {
            console.log('==========================SERVER OUTPUT====================================================');
            console.log('User Unit Order: ' + _order);
            //Need to define Protocol===================================================================================
            //_Socket_.write(_order);
            var _orderMSG = 'order|' + _order;
            _Socket_.write(_orderMSG);
        });

        // ANDROID SEND REQUEST & SERVER SEND RESPONSE
        socket.on('Request', function (pos) {
            console.log('==========================DATA FROM UNITY==================================================');
            console.log(pos);

            // JSON OBJECT PARSING
            var _sendMSG = JSON.parse(pos);
            _Socket_.write(_sendMSG.Host.toString() + '|' + _sendMSG.Board.toString());
        });

        // USER DISCONNECTED
        socket.on('Disconnect', function () {
            socket.disconnect();
            console.log('Unity Engine Disconnected');
        });
    });
};