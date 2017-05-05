using UnityEngine;
using System.Collections;
using System.Net;
using System.Text;
using System.Threading;
using System.IO;
using Newtonsoft.Json.Linq;
using System;
using UnityEngine.UI;
using Quobject.SocketIoClientDotNet.Client;

public static class DefineConstant
{
    public const int WIDTH_SIZE = 10;
    public const int HEIGHT_SIZE = 11;
    public const char splitToken = ' ';
    public const int positionSize = 4;
}


public class ConnectServer : MonoBehaviour
{
    Socket socket;
    static int count = 1;

    static ConnectServer instance;
    public static ConnectServer Instance { get { return instance; } }

    void Start()
    {
        instance = this;
    }

    public void Execute()
    {
        // CONNECT TO SERVER SOCKET.IO
        socket = IO.Socket("Http://203.246.112.146:6110");

        socket.On("Initialize", (_receivedData) =>
        {
            string start = _receivedData.ToString();
            Console.WriteLine(start);
        });

        // RECEIVE BOARD DATA FROM SERVER
        socket.On("Response", (_receivedPos) =>
        {
            Console.WriteLine("Received from server: {0}\n", _receivedPos);
            int tempsIndex = 0;
            string[] temps = _receivedPos.ToString().Split(DefineConstant.splitToken);
            int[] tempsNum = new int[DefineConstant.positionSize];

            tempsNum[0] = int.Parse(temps[tempsIndex]) / 10;
            tempsNum[1] = int.Parse(temps[tempsIndex++]) % 10;
            tempsNum[2] = int.Parse(temps[tempsIndex]) / 10;
            tempsNum[3] = int.Parse(temps[tempsIndex++]) % 10;

            Console.WriteLine("{0}, {1}, {2}, {3}", tempsNum[0], tempsNum[1], tempsNum[2], tempsNum[3]);
        });
    }
    public void SendUnitBoard(int prevXPos, int prevYPos, int postXPos, int postYPos)
    //public void SendUnitBoard()
    {
        char[,] _boardPos = new char[,]
        {
                { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
                { '-', 'C', 'X', 'H', 'S', '-', 'S', 'X', 'H', 'C' },
                { '-', '-', '-', '-', '-', 'K', '-', '-', '-', '-' },
                { '-', '-', 'P', '-', '-', '-', '-', '-', 'P', '-' },
                { '-', 'J', '-', 'J', '-', 'J', '-', 'J', '-', 'J' },
                { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
                { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
                { '-', 'j', '-', 'j', '-', 'j', '-', 'j', '-', 'j' },
                { '-', '-', 'p', '-', '-', '-', '-', '-', 'p', '-' },
                { '-', '-', '-', '-', '-', 'k', '-', '-', '-', '-' },
                { '-', 'c', 'h', 'x', 's', '-', 's', 'h', 'x', 'c' }
        };

        //_BoardData _preJsonData = new _BoardData() { host = 1, board = Board };
        _BoardData _preJsonData = new _BoardData() { host = 1, board = _boardPos };
        string JsonData = _preJsonData.ToJsonString();

        // SEND BOARD DATAT TO SERVER
        socket.Emit("Request", JsonData);
        Console.WriteLine("Data Transmitted > {0}", count++);
    }

    void SendUnitOrder(int _order)
    {
        socket.Emit("Order", _order);
    }

    public void Close()
    {
        socket.Emit("Disconnect");
        socket.Off();
        socket.Close();
    }
}
