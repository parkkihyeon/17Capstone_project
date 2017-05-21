using UnityEngine;
using System.Collections;
using DG.Tweening;
using UnityStandardAssets.Cameras;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
	public GameObject[] PlayerPref; // 7가지 장기알(병사)의 프리펩
	public bool flag;
	public bool check = false;

	public bool IsGameOver = false;

	public int FromY, FromX, ToY, ToX;

	public GameObject OverGame;

	public Soldier tempSoldier = null;


	// 장기판은 9x10 사이즈이므로 그 사이즈에 해당하는 Board 클래스 배열을 만들어준다.
	// Board 클래스에는 그 위치에 있는 병사의 종류, 실제 병사를 가리킬 오브젝트, 팀 정보 등이 담겨있다.
	public Board[][] Cell = {   new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9],
		new Board[9]
	};

	// 초기 병사 생성을 위한 문자 배열
	// "마상마상", "마상상마", "상마마상", "상마상마" 등으로 포진을 바꾸고 싶을땐 이 배열의 값을 미리 바꿔주면 된다.
	public char[][] board = {  
		new char[] { '1', '2', '3', '5', 'X', '5', '2', '3', '1' },
		new char[] { 'X', 'X', 'X', 'X', '6', 'X', 'X', 'X', 'X' },
		new char[] { 'X', '4', 'X', 'X', 'X', 'X', 'X', '4', 'X' },
		new char[] { '0', 'X', '0', 'X', '0', 'X', '0', 'X', '0' },
		new char[] { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
		new char[] { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
		new char[] { '0', 'X', '0', 'X', '0', 'X', '0', 'X', '0' },
		new char[] { 'X', '4', 'X', 'X', 'X', 'X', 'X', '4', 'X' },
		new char[] { 'X', 'X', 'X', 'X', '6', 'X', 'X', 'X', 'X' },
		new char[] { '1', '2', '3', '5', 'X', '5', '2', '3', '1' },
	};

	//@@@@차림 1 : 상마상마, 2 : 상마마상, 3 : 마상상마, 4 : 마상마상
	public int MyCharim, OtherCharim;

	public Soldier ClikedSoldier = null; // 플레이어가 클릭한 병사
	static GameManager instance; // 싱글톤 오브젝트
	public static GameManager Instance { get { return instance; } } // GameManager의 싱글톤 인스턴스

	public Material[] MyMatrial; // 블루팀과 레드팀의 매터리얼
	public Transform[] Team; // 하이어라키에 있는 블루팀과 레드팀의 병사들이 소속될 부모 오브젝트

	public Texture[] Red, Blue; // 블루팀과 레드팀의 텍스쳐
	public GameObject Explosion; // 하이어라키에 있는 폭발 이펙트
	public AutoCam myAutoCam; // 우측 하단에 있는 프리뷰에 보여질 카메라 (유니티 기본 플러그인을 사용했다)
	public OVRCameraRig cameraContriller = null;

	public Transform OverPopup, NoticePopup; // 게임오버 팝업, 노티 팝업 오브젝트
	public bool StartGame = false, Moving = false, DontTouch = false; // 각각 게임이 시작된 상태, 병사이 움직이는 상태, 터치 금지 상태를 나타낸다.
	//public string NickName; // 나의 닉네임을 저장한다.

	Vector3 origin, cameraPos;

	public SolTeam CurTurn = SolTeam.BLUE; // 현재 레드팀 턴인지, 블루팀 턴인지 나타낸다.
	public SolTeam MyTeam = SolTeam.BLUE; // 내가 레드팀인지 블루팀인지 나타낸다.


	public Transform CameraPivot; // 메인 카메라 오브젝트, 팀에 따라 이 카메라의 회전값을 바꿔 내 진영이 무조건 아래쪽에 보이도록 한다.
	public GameObject Status; // "상대를 기다리고 있습니다" 텍스트 오브젝


	public void SetStartGame(int team) // 게임 시작을 처리하는 함수, 0이면 블루팀, 1이면 레드팀으로 설정된다.
	{
		//@@@@차림 0 : 마상마상, 1 : 마상상마, 2 : 상마마상, 3 : 상마상마
		// ma : 2, sang : 3
		Debug.Log("MyCharim : " + MyCharim);

		switch (MyCharim) {
		case 0:
				//마상마상
			board [9] [1] = '2';
			board [9] [2] = '3';
			board [9] [6] = '2';
			board [9] [7] = '3';
				//0마상마상
			board [0] [1] = '2';
			board [0] [2] = '3';
			board [0] [6] = '2';
			board [0] [7] = '3';
			break;
		case 1:
				//마상상마
			board [9] [1] = '2';
			board [9] [2] = '3';
			board [9] [6] = '3';
			board [9] [7] = '2';
				//3상마상마
			board [0] [1] = '3';
			board [0] [2] = '2';
			board [0] [6] = '3';
			board [0] [7] = '2';
			break;
		case 2:
				//상마마상
			board [9] [1] = '3';
			board [9] [2] = '2';
			board [9] [6] = '2';
			board [9] [7] = '3';
				//1마상상마
			board [0] [1] = '2';
			board [0] [2] = '3';
			board [0] [6] = '3';
			board [0] [7] = '2';
			break;
		case 3:
				//상마상마
			board [9] [1] = '3';
			board [9] [2] = '2';
			board [9] [6] = '3';
			board [9] [7] = '2';
				//3상마상마
			board [0] [1] = '3';
			board [0] [2] = '2';
			board [0] [6] = '3';
			board [0] [7] = '2';
			break;
		default:
				//마상상마
			board [9] [1] = '2';
			board [9] [2] = '3';
			board [9] [6] = '3';
			board [9] [7] = '2';
				//상마상마
			board [0] [1] = '3';
			board [0] [2] = '2';
			board [0] [6] = '3';
			board [0] [7] = '2';
			break;
		}
		CurTurn = SolTeam.BLUE; // 시작은 무조건 블루팀이 먼저 한다.
		MyTeam = (SolTeam)team; // 유저에 따라 블루팀은 team이 0으로 레드팀은 1로 호출된다.
		//myAutoCam.gameObject.SetActive(true); // 프리뷰 카메라를 활성화시킨다.
		StartGame = true; //게임이 시작된 상태로 설정한다.
		ConnectServer.Instance.ReStartGame();
		DoStart(); // 게임 시작 처리를 위한 함수 호출
	}

	public void Popup(string text) // 팝업 메세지를 처리한다.
	{
		NoticePopup.GetChild(0).GetComponent<Text>().text = text;
		NoticePopup.gameObject.SetActive(true);
	}

	public void QuitPopup(string text) // 게임오버 팝업 메세지를 처리한다.
	{
		OverPopup.GetChild (0).GetComponent<Text> ().text = text;
		OverPopup.gameObject.SetActive (true);
	}

	public void exit(){
		ConnectServer.Instance.Close ();
	}

	void Awake()
	{
		DOTween.Init(false, true, LogBehaviour.ErrorsOnly); // DotTween을 초기화한다. (트윈 계열 무료 플러그인이다)
		instance = this;
	}

	void Start()
	{
        for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				Cell[y][x] = transform.GetChild(y).GetChild(x).GetComponent<Board>(); // 하이어라키의 Board 밑에 있는 자식 오브젝트들의 Board 컴포넌트를 가져온다.
				Cell[y][x].SetPosition(x, y); // 각 오브젝트의 위치값을 설정한다.
				Cell[y][x].Type = SoldierType.NONE; // 초기화를 위해 Type을 전부 None으로 설정해준다.
			}
		}
	}

	public void ResetGame() // 게임이 진행중인 상태에서도 이 함수만 호출되면 모든 오브젝트가 초기화되고 준비 상태로 돌아간다.
	{
		ClikedSoldier = null; // 클릭한 병사를 초기화한다.
		Explosion.SetActive(false); // 폭발 파티클을 안보이게 한다.
		ShowRoot(false);

		GameObject[] temp = GameObject.FindGameObjectsWithTag("Player"); // Player 태그를 가진 병사들을 모두 가져온다.
		for (int i = 0; i < temp.Length; i++) Destroy(temp[i]); // 모든 병사들을 파괴한다.

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				Cell[y][x].Type = SoldierType.NONE; // Board 배열을 원래 상태로 초기화한다.
				Cell[y][x].Player = null;
			}
		}
	}

	void DoStart() // 게임 시작 처리를 위한 함수
	{
		ResetGame(); // 게임판을 초기화한다.

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				Cell[y][x] = transform.GetChild(y).GetChild(x).GetComponent<Board>(); // 하이어라키의 Board 밑에 있는 자식 오브젝트들의 Board 컴포넌트를 가져온다.
				Cell[y][x].SetPosition(x, y); // 각 오브젝트의 위치값을 설정한다.
				Cell[y][x].Type = SoldierType.NONE; // 초기화를 위해 Type을 전부 None으로 설정해준다.

				if (board[y][x] >= '0' && board[y][x] <= '6') // board의 문자가 0~6 사이면 병사를 나타내므로
				{
					GameObject temp = Instantiate(PlayerPref[board[y][x] - '0']); // 문자값에서 '0'을 빼서 실제 숫자를 인덱스 값으로 사용한다.
					temp.transform.SetParent(Team[y <= 4 ? 0 : 1]); // 해당 병사의 팀에 맞는 부모 객체에 추가해준다.
					temp.transform.position = Cell[y][x].transform.position; // 화면상의 위치로 이동시켜준다.
					temp.transform.localRotation = Quaternion.Euler(0f, y <= 4 ? 180f : 0f, 0f); // 화면 위쪽에 있으면 레드팀이므로 180도 회전시켜 병사들이 마주보게 해준다.

					Soldier player = temp.GetComponent<Soldier>(); // 방금 생성한 병사에서 Soldier 컴포넌트를 얻어온다.
					SoldierType type = (SoldierType)(board[y][x] - '0'); // 병사 타입을 설정해준다.
					player.SType = type;
					player.MyMatrial = MyMatrial[y <= 4 ? 0 : 1]; // 레드팀인지 블루팀인지에 따라 매터리얼을 바꿔준다.
					player.PosX = Cell[y][x].PosX; // X축 위치를 설정한다.
					player.PosY = Cell[y][x].PosY; // Y축 위치를 설정한다.
					player.MyTeam = y <= 4 ? SolTeam.RED : SolTeam.BLUE; // 장기판의 위쪽은 레드팀, 아래쪽은 블루팀으로 설정해준다.

					if (player.SType == SoldierType.왕) // 왕인 경우 다른 병사보다 1.3배 스케일을 키워준다.
					{
						temp.transform.localScale *= 1.3f;
					}

					if (y <= 4) // 레드팀인 경우
					{
						temp.transform.GetChild(1).GetComponent<MeshRenderer>().material.mainTexture = Red[board[y][x] - '0'];
					}
					else // 블루팀인 경우
					{
						temp.transform.GetChild(1).GetComponent<MeshRenderer>().material.mainTexture = Blue[board[y][x] - '0'];
						temp.transform.GetChild(1).localRotation = Quaternion.Euler(-90f, 180f, 0f);
					}
					Cell[y][x].Player = player;
					Cell[y][x].Team = y <= 4 ? SolTeam.RED : SolTeam.BLUE;
					Cell[y][x].Type = type;
				}
			}
		}
		CameraPivot.rotation = Quaternion.Euler(0f, MyTeam == SolTeam.RED ? 180f : 0f, 0f); // 레드팀이면 카메라도 180도 회전시켜 레드팀이 아래쪽, 블루팀이 위쪽으로 거꾸로 보이게 해준다.
		Moving = false;

	}

	void Update()
	{
		if (Input.GetKeyDown(KeyCode.Escape)) // ESC키를 누르면 종료 팝업이 뜨도록 해준다.
		{
			DontTouch = true;
			QuitPopup("게임을 종료하시겠습니까?");
		}

		// 게임이 시작한 상태, 움직이는 말이 없는 경우, 터치할 수 있는 상태인 경우, 내 턴인 경우, 마우스(터치)가 클릭된 상태이면
		//if (StartGame && !Moving && !DontTouch && CurTurn == MyTeam && flag) 
		if (StartGame && !Moving && !DontTouch && CurTurn == MyTeam && (Input.GetMouseButtonDown(0)))
		{
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//레이케스트저장하기확인해서꼭해야함
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); // 마우스(터치)를 기준으로 레이캐스트를 생성한다.
			//Ray ray = new Ray(cameraContriller.centerEyeAnchor.position, cameraContriller.centerEyeAnchor.forward);
				
			bool click = false;
			RaycastHit[] hit = Physics.RaycastAll(ray); // 레이캐스트에 검출되는 모든 오브젝트를 가져온다.

			int i;

			for (i = 0; i < hit.Length; i++)
			{
				if (ClikedSoldier == null) // 병사가 클릭되지 않은 상태이면 병사 선택을 우선으로 한다.
				{
					if (hit[i].collider.gameObject.layer == 8) // 병사의 레이어 번호
					{
						click = true;
						break;
					}
				}
				else // 병사를 클릭한 상태이면 바닥에 있는 Board의 레이어 번호만 검출한다. Board에는 BoxCollider가 들어있어서 이동할 위치를 가져오기 위해 충돌을 감지한다.
				{
					if (hit[i].collider.gameObject.layer == 9) // Board 오브젝트를 가져온다.
					{
						click = true;
						break;
					}
				}
			}

			if (click) // 병사를 클릭했든 Board를 클릭했든 둘중 하나
			{
				if (ClikedSoldier == null) // 군인 선택시
				{
					if (hit[i].collider.tag.Equals("Player")) // 충돌한 객체의 태그가 Player가 맞는지 다시 확인
					{
						if (MyTeam == hit[i].transform.GetComponentInParent<Soldier>().MyTeam) // 내 팀의 병사들인지 체크한다.
						{
							GetComponent<AudioSource>().Play(); // 클릭 사운드 플레이
							ClikedSoldier = hit[i].transform.GetComponentInParent<Soldier>(); // ClikedSoldier를 방금 클릭한 병사로 설정
							Debug.Log(ClikedSoldier.SType);
							Debug.Log (ClikedSoldier.PosX);
							ClikedSoldier.HUD.SetActive(false);
							myAutoCam.SetTarget(ClikedSoldier.transform); // 프리뷰의 타겟 오브젝트로 방금 클릭한 병사를 설정
							ShowRoot(true); // 클릭한 병사가 이동할 수 있는 위치의 스프라이트만 활성화 시켜준다.
						}
					}
				}
				else // 목표지점 선택시
				{
					GetComponent<AudioSource>().Play(); // 클릭 사운드 플레이

					if (ClikedSoldier == hit[i].collider.GetComponent<Board>().Player) // 선택한 병사가 있는 위치의 Board를 클릭했으면 병사 선택을 취소해준다.
					{
						//Debug.Log("cancel click");
					}
					else // 클릭한 병사가 아닌 이동할 위치의 Board를 클릭한 경우
					{
						
						//int from = (ClikedSoldier.PosY * 9) + ClikedSoldier.PosX; // X,Y 좌표를 이용해 현재 지점의 offset 값을 구한다.
						//int to = (hit[i].collider.GetComponent<Board>().PosY * 9) + hit[i].collider.GetComponent<Board>().PosX; // X,Y 좌표를 이용해 이동할 지점의 offset 값을 구한다.

						FromY = ClikedSoldier.PosY;
						FromX = ClikedSoldier.PosX;

						ToY = hit [i].collider.GetComponent<Board> ().PosY;
						ToX = hit [i].collider.GetComponent<Board> ().PosX;

						tempSoldier = ClikedSoldier;

						//ConnectServer.Instance.SendUnitBoard (ClikedSoldier.PosY, ClikedSoldier.PosX, hit [i].collider.GetComponent<Board> ().PosY, hit [i].collider.GetComponent<Board> ().PosX);
                        MovePlayer(ClikedSoldier.PosY, ClikedSoldier.PosX, hit[i].collider.GetComponent<Board>().PosY, hit[i].collider.GetComponent<Board>().PosX);
						//ConnectServer.Instance.SendMovePlayer(from, to); // 서버로 현재 위치와 이동할 위치를 보낸다.
						Moving = true; // 병사이 이동중임을 나타낸다.
					}

					//CheckJang ();

					ClikedSoldier = null; // 클릭된 병사를 초기화한다.
					ShowRoot(false); // 이동 가능한 루트를 모두 비활성화시킨다.
				}
			}
			flag = false;
			/*if (check) {
				//장군입니다. 팝업으로 알려주기

				Popup ("장군입니다.");

				check = false;
			}*/
		}
	}

	public void MovePlayer(int FromY, int FromX, int ToY, int ToX) // 실제로 병사를 이동시켜주는 함수
	{
		//int x = from % 9, y = from / 9; // offset값을 좌표로 변환한다.
		//if (FromY >= 0 && FromX >= 0 && ToY >= 0 && ToX >= 0) {

			//ConnectServer.Instance.FromY = 0;
			//ConnectServer.Instance.FromX = 0;
			//ConnectServer.Instance.ToY = 0;
			//ConnectServer.Instance.ToX = 0;

			Debug.Log ("FromY : " + FromY);
			Debug.Log ("FromX : " + FromX);
			Debug.Log ("ToY : " + ToY);
			Debug.Log ("ToX : " + ToX);

			Cell [FromY] [FromX].Player.MoveTo (Cell [ToY] [ToX]); // from 위치에 있는 병사를 이동시킨다.
			Cell [FromY] [FromX].Player = null; // 현재 위치에 있는 병사가 다른 위치로 이동할 것이므로 현재 위치의 오브젝트를 초기화해준다.
			Cell [FromY] [FromX].Type = SoldierType.NONE; // 현재 위치의 병사 타입도 NONE으로 초기화
			Moving = true;
		//}

	}

	public void ChangeTurn() // 병사의 이동이 끝나면 턴을 바꿔준다.
	{
		CurTurn = (CurTurn == SolTeam.RED) ? SolTeam.BLUE : SolTeam.RED;
		Moving = false;
		myAutoCam.gameObject.SetActive (false);

		//Invoke ("", 5.0f);

		//StartCoroutine (Wait(2.5f));

		CheckJang ();

		//ConnectServer.flag = true;

		if (IsGameOver) {
			OverGame.SetActive (true);
		}
			
		if (tempSoldier.MyTeam == MyTeam ) {

			tempSoldier = null;
			ConnectServer.Instance.SendUnitBoard (FromY, FromX, ToY, ToX);

			Status.SetActive (true);
		}
	}

	//IEnumerator Wait(float waitTime){
	//	yield return new WaitForSeconds (waitTime);
	//}


	public SoldierType GetType(int x, int y) // 해당 좌표의 병사 타입을 얻어온다.
	{
		return Cell[y][x].Type;
	}

	public SolTeam GetTeam(int x, int y) // 해당 좌표의 팀 종류를 얻어온다.
	{
		return Cell[y][x].Team;
	}

	public bool isEmemy(int x, int y, SolTeam team) // 해당 위치에 지정한 팀의 병사가 있는지 체크한다.
	{
		return Cell[y][x].Type != SoldierType.NONE && Cell[y][x].Team != team ? true : false;
	}

	void ShowPointTexture(int x, int y, bool show) // 이동할 수 있는 위치를 나타내는 포인트 스프라이트를 끄거나 켜준다.
	{
		if (x >= 0 && x < 9 && y >= 0 && y < 10)
		{
			if (show && Cell[y][x].Type != SoldierType.NONE)
			{
				if (Cell[y][x].Team == ClikedSoldier.MyTeam) return;
			}
			Cell[y][x].gameObject.SetActive(true);
			Cell[y][x].transform.GetChild(0).gameObject.SetActive(show);
		}
	}

	void ShowRoot(bool isshow) // 선택된 캐릭터가 이동할 수 있는 위치를 표시해준다.
	{
		if (isshow)
		{
			if (ClikedSoldier != null) // 선택한 병사가 있는지 확인
			{
				int x = ClikedSoldier.PosX; // 병사의 좌표를 얻어온다.
				int y = ClikedSoldier.PosY;

				ShowPointTexture(x, y, false); // 병사가 있는 현재 위치는 무조건 비활성화 시킨다. 같은 자리로 또 이동할 이유가 없기 때문이다.

				if (ClikedSoldier.SType == SoldierType.졸) // '졸' 병사의 이동 가능한 위치 설정
				{
					ShowPointTexture(x, y - (ClikedSoldier.MyTeam == SolTeam.RED ? -1 : 1), true);
					ShowPointTexture(x - 1, y, true);
					ShowPointTexture(x + 1, y, true);

					if (ClikedSoldier.MyTeam == SolTeam.BLUE)
					{
						if (x == 3 && y == 2)
						{
							ShowPointTexture(x + 1, y - 1, true);
						}
						if (x == 5 && y == 2)
						{
							ShowPointTexture(x - 1, y - 1, true);
						}
						if (x == 4 && y == 1)
						{
							ShowPointTexture(x - 1, y - 1, true);
							ShowPointTexture(x + 1, y - 1, true);
						}
					}
					else
					{
						if (x == 3 && y == 7)
						{
							ShowPointTexture(x + 1, y + 1, true);
						}
						if (x == 5 && y == 7)
						{
							ShowPointTexture(x - 1, y + 1, true);
						}
						if (x == 4 && y == 8)
						{
							ShowPointTexture(x - 1, y + 1, true);
							ShowPointTexture(x + 1, y + 1, true);
						}
					}
				}
				else if (ClikedSoldier.SType == SoldierType.왕 || ClikedSoldier.SType == SoldierType.사) // '왕','사' 병사의 이동 가능한 위치 설정
				{
					if (x == 4)
					{
						if (y == 1 || y == 8)
						{
							ShowPointTexture(x, y - 1, true);
							ShowPointTexture(x, y + 1, true);
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x - 1, y - 1, true);
							ShowPointTexture(x + 1, y - 1, true);
							ShowPointTexture(x - 1, y + 1, true);
							ShowPointTexture(x + 1, y + 1, true);
						}
						if (y == 0 || y == 7)
						{
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x, y + 1, true);
						}
						if (y == 2 || y == 9)
						{
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x, y - 1, true);
						}
					}
					if (x == 3)
					{
						if (y == 0 || y == 7) // 좌상단
						{
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x, y + 1, true);
							ShowPointTexture(x + 1, y + 1, true);
						}
						if (y == 1 || y == 8) // 좌
						{
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x, y - 1, true);
							ShowPointTexture(x, y + 1, true);
						}
						if (y == 2 || y == 9) // 좌하단
						{
							ShowPointTexture(x + 1, y, true);
							ShowPointTexture(x, y - 1, true);
							ShowPointTexture(x + 1, y - 1, true);
						}
					}
					if (x == 5)
					{
						if (y == 0 || y == 7) // 우상단
						{
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x, y + 1, true);
							ShowPointTexture(x - 1, y + 1, true);
						}
						if (y == 1 || y == 8) // 우
						{
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x, y - 1, true);
							ShowPointTexture(x, y + 1, true);
						}
						if (y == 2 || y == 9) // 우하단
						{
							ShowPointTexture(x - 1, y, true);
							ShowPointTexture(x, y - 1, true);
							ShowPointTexture(x - 1, y - 1, true);
						}
					}
				}
				else if (ClikedSoldier.SType == SoldierType.차) // '차' 병사의 이동 가능한 위치 설정
				{
					for (int i = x + 1; i < 9; i++)
					{
						if (Cell[y][i].Type != SoldierType.NONE)
						{
							if (Cell[y][i].Team == ClikedSoldier.MyTeam) break;
						}
						ShowPointTexture(i, y, true);
						if (Cell[y][i].Type != SoldierType.NONE) break;
					}
					for (int i = x - 1; i >= 0; i--)
					{
						if (Cell[y][i].Type != SoldierType.NONE)
						{
							if (Cell[y][i].Team == ClikedSoldier.MyTeam) break;
						}
						ShowPointTexture(i, y, true);
						if (Cell[y][i].Type != SoldierType.NONE) break;
					}
					for (int i = y + 1; i < 10; i++)
					{
						if (Cell[i][x].Type != SoldierType.NONE)
						{
							if (Cell[i][x].Team == ClikedSoldier.MyTeam) break;
						}
						ShowPointTexture(x, i, true);
						if (Cell[i][x].Type != SoldierType.NONE) break;
					}
					for (int i = y - 1; i >= 0; i--)
					{
						if (Cell[i][x].Type != SoldierType.NONE)
						{
							if (Cell[i][x].Team == ClikedSoldier.MyTeam) break;
						}
						ShowPointTexture(x, i, true);
						if (Cell[i][x].Type != SoldierType.NONE) break;
					}

					if (x == 4)
					{
						if (y == 1 || y == 8)
						{
							ShowPointTexture(x - 1, y - 1, true);
							ShowPointTexture(x + 1, y - 1, true);
							ShowPointTexture(x - 1, y + 1, true);
							ShowPointTexture(x + 1, y + 1, true);
						}
					}

					if (x == 3)
					{
						if (y == 0 || y == 7) // 좌상단
						{
							ShowPointTexture(x + 1, y + 1, true);
							ShowPointTexture(x + 2, y + 2, true);
						}
						if (y == 2 || y == 9) // 좌하단
						{
							ShowPointTexture(x + 1, y - 1, true);
							ShowPointTexture(x + 2, y - 2, true);
						}
					}

					if (x == 5)
					{
						if (y == 0 || y == 7) // 우상단
						{
							ShowPointTexture(x - 1, y + 1, true);
							ShowPointTexture(x - 2, y + 2, true);
						}
						if (y == 2 || y == 9) // 우하단
						{
							ShowPointTexture(x - 1, y - 1, true);
							ShowPointTexture(x - 2, y - 2, true);
						}
					}
				}
				else if (ClikedSoldier.SType == SoldierType.포) // '포' 병사의 이동 가능한 위치 설정
				{
					int count = 0;

					for (int i = x + 1; i < 9; i++)
					{
						if (Cell[y][i].Type == SoldierType.포) break;

						if (count > 0)
						{
							if (Cell[y][i].Type != SoldierType.NONE)
							{
								if (Cell[y][i].Team == ClikedSoldier.MyTeam) break;
							}
							ShowPointTexture(i, y, true);
							if (Cell[y][i].Type != SoldierType.NONE) break;
						}
						else
						{
							if (Cell[y][i].Type != SoldierType.NONE) count = 1;
						}
					}
					count = 0;

					for (int i = x - 1; i >= 0; i--)
					{
						if (Cell[y][i].Type == SoldierType.포) break;

						if (count > 0)
						{
							if (Cell[y][i].Type != SoldierType.NONE)
							{
								if (Cell[y][i].Team == ClikedSoldier.MyTeam) break;
							}
							ShowPointTexture(i, y, true);
							if (Cell[y][i].Type != SoldierType.NONE) break;
						}
						else
						{
							if (Cell[y][i].Type != SoldierType.NONE) count = 1;
						}
					}
					count = 0;

					for (int i = y + 1; i < 10; i++)
					{
						if (Cell[i][x].Type == SoldierType.포) break;

						if (count > 0)
						{
							if (Cell[i][x].Type != SoldierType.NONE)
							{
								if (Cell[i][x].Team == ClikedSoldier.MyTeam) break;
							}
							ShowPointTexture(x, i, true);
							if (Cell[i][x].Type != SoldierType.NONE) break;
						}
						else
						{
							if (Cell[i][x].Type != SoldierType.NONE) count = 1;
						}
					}
					count = 0;

					for (int i = y - 1; i >= 0; i--)
					{
						if (Cell[i][x].Type == SoldierType.포) break;

						if (count > 0)
						{
							if (Cell[i][x].Type != SoldierType.NONE)
							{
								if (Cell[i][x].Team == ClikedSoldier.MyTeam) break;
							}
							ShowPointTexture(x, i, true);
							if (Cell[i][x].Type != SoldierType.NONE) break;
						}
						else
						{
							if (Cell[i][x].Type != SoldierType.NONE) count = 1;
						}
					}
				}
				else if (ClikedSoldier.SType == SoldierType.마) // '마' 병사의 이동 가능한 위치 설정
				{
					
					if (y - 1 >= 0 && Cell[y - 1][x].Type == SoldierType.NONE)
					{
						ShowCell(x - 1, y - 2);
						ShowCell(x + 1, y - 2);
					}
					if (y + 1 < 10 && Cell[y + 1][x].Type == SoldierType.NONE)
					{
						ShowCell(x - 1, y + 2);
						ShowCell(x + 1, y + 2);
					}
					if (x - 1 >= 0 && Cell[y][x - 1].Type == SoldierType.NONE)
					{
						ShowCell(x - 2, y - 1);
						ShowCell(x - 2, y + 1);
					}
					if (x + 1 < 9 && Cell[y][x + 1].Type == SoldierType.NONE)
					{
						ShowCell(x + 2, y - 1);
						ShowCell(x + 2, y + 1);
					}
				}
				else if (ClikedSoldier.SType == SoldierType.상) // '상' 병사의 이동 가능한 위치 설정
				{
					if (y - 1 >= 0 && Cell[y - 1][x].Type == SoldierType.NONE) // 상 좌우
					{
						if (x - 2 >= 0 && y - 3 >= 0) // 
						{
							if (Cell[y - 2][x - 1].Type == SoldierType.NONE) ShowCell(x - 2, y - 3);
						}
						if (x + 2 >= 0 && y - 3 >= 0)
						{
							if (Cell[y - 2][x + 1].Type == SoldierType.NONE) ShowCell(x + 2, y - 3);
						}
					}
					if (y + 1 < 10 && Cell[y + 1][x].Type == SoldierType.NONE) // 하 좌우
					{
						if (x - 2 >= 0 && y + 3 < 10)
						{
							if (Cell[y + 2][x - 1].Type == SoldierType.NONE) ShowCell(x - 2, y + 3);
						}
						if (x + 2 >= 0 && y + 3 < 10)
						{
							if (Cell[y + 2][x + 1].Type == SoldierType.NONE) ShowCell(x + 2, y + 3);
						}
					}
					if (x - 1 >= 0 && Cell[y][x - 1].Type == SoldierType.NONE) // 좌 상하
					{
						if (x - 3 >= 0 && y - 2 >= 0)
						{
							if (Cell[y - 1][x - 2].Type == SoldierType.NONE) ShowCell(x - 3, y - 2);
						}
						if (x - 3 >= 0 && y + 2 < 10)
						{
							if (Cell[y + 1][x - 2].Type == SoldierType.NONE) ShowCell(x - 3, y + 2);
						}
					}
					if (x + 1 < 9 && Cell[y][x + 1].Type == SoldierType.NONE) // 우 상하
					{
						if (x + 3 < 9 && y - 2 >= 0)
						{
							if (Cell[y - 1][x + 2].Type == SoldierType.NONE) ShowCell(x + 3, y - 2);
						}
						if (x + 3 < 9 && y + 2 < 10)
						{
							if (Cell[y + 1][x + 2].Type == SoldierType.NONE) ShowCell(x + 3, y + 2);
						}
					}
				}
			}
		}
		else
		{
			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 9; x++)
				{
					Cell[y][x].gameObject.SetActive(isshow);
				}
			}
		}
	}

	void ShowCell(int x, int y)
	{
		if (x >= 0 && x < 9 && y >= 0 && y < 10)
		{
			if (Cell[y][x].Type == SoldierType.NONE) ShowPointTexture(x, y, true);
			else if (Cell[y][x].Team != ClikedSoldier.MyTeam) ShowPointTexture(x, y, true);
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	void CheckJang() // 선택된 캐릭터가 이동할 수 있는 위치를 표시해준다. 파라미터로 움직인 병사 받아오기, 클릭된 병사가 아닌 움직인 병사를 확인해야 한다.
	{

		if (tempSoldier != null) { // 선택한 병사가 있는지 확인
			int x = tempSoldier.PosX; // 병사의 좌표를 얻어온다.
			int y = tempSoldier.PosY;

			if (tempSoldier.SType == SoldierType.졸) { // '졸' 병사의 이동 가능한 위치 설정
				CheckPointTexture (x, y - (tempSoldier.MyTeam == SolTeam.RED ? -1 : 1));
				CheckPointTexture (x - 1, y);
				CheckPointTexture (x + 1, y);

				if (tempSoldier.MyTeam == SolTeam.BLUE) {
					if (x == 3 && y == 2) {
						CheckPointTexture (x + 1, y - 1);
					}
					if (x == 5 && y == 2) {
						CheckPointTexture (x - 1, y - 1);
					}
					if (x == 4 && y == 1) {
						CheckPointTexture (x - 1, y - 1);
						CheckPointTexture (x + 1, y - 1);
					}
				} else {
					if (x == 3 && y == 7) {
						CheckPointTexture (x + 1, y + 1);
					}
					if (x == 5 && y == 7) {
						CheckPointTexture (x - 1, y + 1);
					}
					if (x == 4 && y == 8) {
						CheckPointTexture (x - 1, y + 1);
						CheckPointTexture (x + 1, y + 1);
					}
				}
			} else if (tempSoldier.SType == SoldierType.차) { // '차' 병사의 이동 가능한 위치 설정
				for (int i = x + 1; i < 9; i++) {
					if (Cell [y] [i].Type != SoldierType.NONE) {
						if (Cell [y] [i].Team == tempSoldier.MyTeam)
							break;
					}
					CheckPointTexture (i, y);
					if (Cell [y] [i].Type != SoldierType.NONE)
						break;
				}
				for (int i = x - 1; i >= 0; i--) {
					if (Cell [y] [i].Type != SoldierType.NONE) {
						if (Cell [y] [i].Team == tempSoldier.MyTeam)
							break;
					}
					CheckPointTexture (i, y);
					if (Cell [y] [i].Type != SoldierType.NONE)
						break;
				}
				for (int i = y + 1; i < 10; i++) {
					if (Cell [i] [x].Type != SoldierType.NONE) {
						if (Cell [i] [x].Team == tempSoldier.MyTeam)
							break;
					}
					CheckPointTexture (x, i);
					if (Cell [i] [x].Type != SoldierType.NONE)
						break;
				}
				for (int i = y - 1; i >= 0; i--) {
					if (Cell [i] [x].Type != SoldierType.NONE) {
						if (Cell [i] [x].Team == tempSoldier.MyTeam)
							break;
					}
					CheckPointTexture (x, i);
					if (Cell [i] [x].Type != SoldierType.NONE)
						break;
				}

				if (x == 4) {
					if (y == 1 || y == 8) {
						CheckPointTexture (x - 1, y - 1);
						CheckPointTexture (x + 1, y - 1);
						CheckPointTexture (x - 1, y + 1);
						CheckPointTexture (x + 1, y + 1);
					}
				}

				if (x == 3) {
					if (y == 0 || y == 7) { // 좌상단
						CheckPointTexture (x + 1, y + 1);
						CheckPointTexture (x + 2, y + 2);
					}
					if (y == 2 || y == 9) { // 좌하단
						CheckPointTexture (x + 1, y - 1);
						CheckPointTexture (x + 2, y - 2);
					}
				}

				if (x == 5) {
					if (y == 0 || y == 7) { // 우상단
						CheckPointTexture (x - 1, y + 1);
						CheckPointTexture (x - 2, y + 2);
					}
					if (y == 2 || y == 9) { // 우하단
						CheckPointTexture (x - 1, y - 1);
						CheckPointTexture (x - 2, y - 2);
					}
				}
			} else if (tempSoldier.SType == SoldierType.포) { // '포' 병사의 이동 가능한 위치 설정
				int count = 0;

				for (int i = x + 1; i < 9; i++) {
					if (Cell [y] [i].Type == SoldierType.포)
						break;

					if (count > 0) {
						if (Cell [y] [i].Type != SoldierType.NONE) {
							if (Cell [y] [i].Team == tempSoldier.MyTeam)
								break;
						}
						CheckPointTexture (i, y);
						if (Cell [y] [i].Type != SoldierType.NONE)
							break;
					} else {
						if (Cell [y] [i].Type != SoldierType.NONE)
							count = 1;
					}
				}
				count = 0;

				for (int i = x - 1; i >= 0; i--) {
					if (Cell [y] [i].Type == SoldierType.포)
						break;

					if (count > 0) {
						if (Cell [y] [i].Type != SoldierType.NONE) {
							if (Cell [y] [i].Team == tempSoldier.MyTeam)
								break;
						}
						CheckPointTexture (i, y);
						if (Cell [y] [i].Type != SoldierType.NONE)
							break;
					} else {
						if (Cell [y] [i].Type != SoldierType.NONE)
							count = 1;
					}
				}
				count = 0;

				for (int i = y + 1; i < 10; i++) {
					if (Cell [i] [x].Type == SoldierType.포)
						break;

					if (count > 0) {
						if (Cell [i] [x].Type != SoldierType.NONE) {
							if (Cell [i] [x].Team == tempSoldier.MyTeam)
								break;
						}
						CheckPointTexture (x, i);
						if (Cell [i] [x].Type != SoldierType.NONE)
							break;
					} else {
						if (Cell [i] [x].Type != SoldierType.NONE)
							count = 1;
					}
				}
				count = 0;

				for (int i = y - 1; i >= 0; i--) {
					if (Cell [i] [x].Type == SoldierType.포)
						break;

					if (count > 0) {
						if (Cell [i] [x].Type != SoldierType.NONE) {
							if (Cell [i] [x].Team == tempSoldier.MyTeam)
								break;
						}
						CheckPointTexture (x, i);
						if (Cell [i] [x].Type != SoldierType.NONE)
							break;
					} else {
						if (Cell [i] [x].Type != SoldierType.NONE)
							count = 1;
					}
				}
			} else if (tempSoldier.SType == SoldierType.마) { // '마' 병사의 이동 가능한 위치 설정
				if (y - 1 >= 0 && Cell [y - 1] [x].Type == SoldierType.NONE) {
					CheckCell (x - 1, y - 2);
					CheckCell (x + 1, y - 2);
				}
				if (y + 1 < 10 && Cell [y + 1] [x].Type == SoldierType.NONE) {
					CheckCell (x - 1, y + 2);
					CheckCell (x + 1, y + 2);
				}
				if (x - 1 >= 0 && Cell [y] [x - 1].Type == SoldierType.NONE) {
					CheckCell (x - 2, y - 1);
					CheckCell (x - 2, y + 1);
				}
				if (x + 1 < 9 && Cell [y] [x + 1].Type == SoldierType.NONE) {
					CheckCell (x + 2, y - 1);
					CheckCell (x + 2, y + 1);
				}
			} else if (tempSoldier.SType == SoldierType.상) { // '상' 병사의 이동 가능한 위치 설정
				if (y - 1 >= 0 && Cell [y - 1] [x].Type == SoldierType.NONE) { // 상 좌우
					if (x - 2 >= 0 && y - 3 >= 0) { // 
						if (Cell [y - 2] [x - 1].Type == SoldierType.NONE)
							CheckCell (x - 2, y - 3);
					}
					if (x + 2 >= 0 && y - 3 >= 0) {
						if (Cell [y - 2] [x + 1].Type == SoldierType.NONE)
							CheckCell (x + 2, y - 3);
					}
				}
				if (y + 1 < 10 && Cell [y + 1] [x].Type == SoldierType.NONE) { // 하 좌우
					if (x - 2 >= 0 && y + 3 < 10) {
						if (Cell [y + 2] [x - 1].Type == SoldierType.NONE)
							CheckCell (x - 2, y + 3);
					}
					if (x + 2 >= 0 && y + 3 < 10) {
						if (Cell [y + 2] [x + 1].Type == SoldierType.NONE)
							CheckCell (x + 2, y + 3);
					}
				}
				if (x - 1 >= 0 && Cell [y] [x - 1].Type == SoldierType.NONE) { // 좌 상하
					if (x - 3 >= 0 && y - 2 >= 0) {
						if (Cell [y - 1] [x - 2].Type == SoldierType.NONE)
							CheckCell (x - 3, y - 2);
					}
					if (x - 3 >= 0 && y + 2 < 10) {
						if (Cell [y + 1] [x - 2].Type == SoldierType.NONE)
							CheckCell (x - 3, y + 2);
					}
				}
				if (x + 1 < 9 && Cell [y] [x + 1].Type == SoldierType.NONE) { // 우 상하
					if (x + 3 < 9 && y - 2 >= 0) {
						if (Cell [y - 1] [x + 2].Type == SoldierType.NONE)
							CheckCell (x + 3, y - 2);
					}
					if (x + 3 < 9 && y + 2 < 10) {
						if (Cell [y + 1] [x + 2].Type == SoldierType.NONE)
							CheckCell (x + 3, y + 2);
					}
				}
			}
		}
		//@@@@@@@@@@@@@@@@@@@@@@
		//장군입니다. 팝업으로 알려주기
		if (check) {
			//장군입니다. 팝업으로 알려주기
			check = false;
			Popup ("장군입니다.");
		}

	}

	void CheckPointTexture(int x, int y) // 이동할 수 있는 위치를 나타내는 포인트 스프라이트를 끄거나 켜준다.
	{
		if (x >= 0 && x < 9 && y >= 0 && y < 10)
		{
			if (Cell[y][x].Type != SoldierType.NONE)
			{
				if (Cell [y] [x].Type == SoldierType.왕) {
					check = true;
					return;
				};
			}
		}
	}

	void CheckCell(int x, int y)
	{
		if (x >= 0 && x < 9 && y >= 0 && y < 10)
		{
			if (Cell[y][x].Type == SoldierType.NONE) CheckPointTexture(x, y);
			else if (Cell[y][x].Team != tempSoldier.MyTeam) CheckPointTexture(x, y);
		}
	}

}
