using System;
using Quobject.SocketIoClientDotNet.Client;
using UnityEngine;
using UnityEngine.UI;

public static class DefineConstant
{
    public const int WIDTH_SIZE = 10;
    public const int HEIGHT_SIZE = 11;
    public const char splitToken = ' ';
    public const int tokenSize = 4;
}

public class ConnectServer : MonoBehaviour
{
    
    static int count = 1;

    public static bool flag = false;

    public int FromY;
    public int FromX;
    public int ToY;
    public int ToX;


    static ConnectServer instance;
    public static Socket socket;
    public static ConnectServer Instance { get { return instance; } }

    public int Charim;

    public static char[,] Board;

	public void ReStartGame(){

		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 9; j++) {
				if (i < 5) {
					switch (GameManager.Instance.board [i-1] [j-1]) {
					case '0':
						Board [i, j] = 'J';
						break;
					case '1':
						Board [i, j] = 'C';
						break;
					case '2':
						Board [i, j] = 'H';
						break;
					case '3':
						Board [i, j] = 'X';
						break;
					case '4':
						Board [i, j] = 'P';
						break;
					case '5':
						Board [i, j] = 'S';
						break;
					case '6':
						Board [i, j] = 'K';
						break;
					default:
						Board [i, j] = '-';
						break;
					}
				}
				else {
					switch (GameManager.Instance.board [i-1] [j-1]) {
					case '0':
						Board [i, j] = 'j';
						break;
					case '1':
						Board [i, j] = 'c';
						break;
					case '2':
						Board [i, j] = 'h';
						break;
					case '3':
						Board [i, j] = 'x';
						break;
					case '4':
						Board [i, j] = 'p';
						break;
					case '5':
						Board [i, j] = 's';
						break;
					case '6':
						Board [i, j] = 'k';
						break;
					default:
						Board [i, j] = '-';
						break;
					}
				}
			}
		}
	}

    void Start()
    {
        instance = this;

        Board = new char[,]
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
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 9; j++) {
				if (i < 5) {
					switch (GameManager.Instance.board [i-1] [j-1]) {
					case '0':
						Board [i, j] = 'J';
						break;
					case '1':
						Board [i, j] = 'C';
						break;
					case '2':
						Board [i, j] = 'H';
						break;
					case '3':
						Board [i, j] = 'X';
						break;
					case '4':
						Board [i, j] = 'P';
						break;
					case '5':
						Board [i, j] = 'S';
						break;
					case '6':
						Board [i, j] = 'K';
						break;
					default:
						Board [i, j] = '-';
						break;
					}
				}
				else {
					switch (GameManager.Instance.board [i-1] [j-1]) {
					case '0':
						Board [i, j] = 'j';
						break;
					case '1':
						Board [i, j] = 'c';
						break;
					case '2':
						Board [i, j] = 'h';
						break;
					case '3':
						Board [i, j] = 'x';
						break;
					case '4':
						Board [i, j] = 'p';
						break;
					case '5':
						Board [i, j] = 's';
						break;
					case '6':
						Board [i, j] = 'k';
						break;
					default:
						Board [i, j] = '-';
						break;
					}
				}
			}
		}
    }
    void Update()
    {
		//Debug.Log ("Server fromy : " + FromY);
		//Debug.Log ("Server fromx : " + FromX);
		//Debug.Log ("Server toy : " + ToY);
		//Debug.Log ("Server tox :" + ToX);
		//if (flag == true) {
			flag = false;
			//Debug.Log ("inside");
			GameManager.Instance.MovePlayer (FromY - 1, FromX - 1, ToY - 1, ToX - 1);
		//}
    }

    public void Execute()
    {
        // CONNECT TO SERVER SOCKET.IO
        socket = IO.Socket("Http://203.246.112.146:6110");

        //SendUnitOrder (Charim);
        SendUnitOrder(0);

        socket.On("Initialize", (_receivedData) =>
        {
            string start = _receivedData.ToString();
            //GameManager.Instance.SetStartGame(0);
            Console.WriteLine(start);
        });

        // RECEIVE BOARD DATA FROM SERVER
		socket.On ("Response", (_receivedPos) => {

			Console.WriteLine ("Received from server: {0}\n", _receivedPos);

			int tempsIndex = 0;
			string[] temps = _receivedPos.ToString ().Split (DefineConstant.splitToken);
			int[] tempsNum = new int[DefineConstant.tokenSize];

			tempsNum [0] = int.Parse (temps [tempsIndex]) / 10;
			tempsNum [1] = int.Parse (temps [tempsIndex++]) % 10;
			tempsNum [2] = int.Parse (temps [tempsIndex]) / 10;
			tempsNum [3] = int.Parse (temps [tempsIndex++]) % 10;

			Console.WriteLine ("{0}, {1}, {2}, {3}", tempsNum [0], tempsNum [1], tempsNum [2], tempsNum [3]);

			FromY = tempsNum [0];
			FromX = tempsNum [1];
			ToY = tempsNum [2];
			ToX = tempsNum [3];

			if (FromY == 0)
				FromY = 10;
			if (ToY == 0)
				ToY = 10;

			Debug.Log ("Server fromy : " + FromY);
			Debug.Log ("Server fromx : " + FromX);
			Debug.Log ("Server toy : " + ToY);
			Debug.Log ("Server tox :" + ToX);


			Board [ToY, ToX] = Board [FromY, FromX];
			Board [FromY, FromX] = '-';

		});

		socket.On ("AI_Order", (_receivedOrder) => {
			//int order = int.Parse (_receivedOrder.ToString ());
			GameManager.Instance.OtherCharim = int.Parse (_receivedOrder.ToString ());
		});
    }
    //public void SendUnitBoard(int _host, char[,] _boardPos)
    public void SendUnitBoard(int FromY, int FromX, int ToY, int ToX)
    {

        Board[ToY + 1, ToX + 1] = Board[FromY + 1, FromX + 1];
        Board[FromY + 1, FromX + 1] = '-';

		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j <= 9; j++) {
				Console.Write (Board[i,j]);
			}
			Console.WriteLine ("");
		}


        _BoardData _preJsonData = new _BoardData() { host = 1, board = Board };
        //BoardClass jsonData = new BoardClass() { host = _host, board = _boardPos };
        string JsonData = _preJsonData.ToJsonString();

        // SEND BOARD DATAT TO SERVER
        socket.Emit("Request", JsonData);
        Console.WriteLine("Data Transmitted > {0}", count++);
    }

    void SendUnitOrder(int _order)
    {
        //마상마상 = 0, 마상상마 = 1, 상마마상 = 2, 상마상마 = 3
        socket.Emit("Order", _order);
    }

    public void Close()
    {
        socket.Emit("Disconnect");
        socket.Off();
        socket.Close();
    }
	void temp(){

	}
}