using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using DG.Tweening;

public enum SoldierType // 각 병사의 타입을 정한다.
{
    NONE = -1,
    졸,
    차,
    마,
    상,
    포,
    사,
    왕,
}

public enum SolTeam // 팀을 정한다. 블루가 초나라, 레드가 한나라이다.
{
    BLUE = 0,
    RED,
}

public class Soldier : MonoBehaviour
{
    public Board Target; // 병사 위치에 있는 Board 객체
    public GameObject MyGun; // 병사가 총을 가지고 있는 경우
    public SoldierType SType; // 병사의 타입
    public Material MyMatrial; // 병사의 매터리얼
    public int PosX, PosY; // 병사의 장기판 위에서의 위치
    public SolTeam MyTeam; // 병사의 팀
    public GameObject HUD; // 병사 머리 위에 보여질 실제 장기알 이미지 오브젝트

    public ParticleSystem Blood; // 공격 당했을때 피가 터지는 파티클

    Animator anim; // 애니메이터 오브젝트
    List<Board> MoveList = new List<Board>(); // 이동할 위치를 순차적으로 저장할 리스트
    Quaternion[] Rot = { Quaternion.Euler(0f, 0f, 0f), Quaternion.Euler(0f, 180f, 0f) }; // 팀에 따른 병사의 회전값

    public AudioSource DamageAudio, DeadAudio; // 데미지 입었을때의 오디오 소스, 죽을때의 오디오소스


    void Awake()
    {
        anim = GetComponentInChildren<Animator>();
    }

    void Start()
	{
        HUD = transform.GetChild(1).gameObject;

        if (GameManager.Instance.MyTeam == SolTeam.RED) // 팀에 따라 머리위의 장기말 이미지의 회전값을 설정해준다.
        {
            HUD.transform.localRotation = Quaternion.Euler(-90f, MyTeam == SolTeam.BLUE ? 0f : 180f, 0f);
        }
        else
        {
            HUD.transform.localRotation = Quaternion.Euler(-90f, MyTeam == SolTeam.RED ? 0f : 180f, 0f);
        }
        MeshRenderer[] temp = GetComponentsInChildren<MeshRenderer>(); // 오브젝트의 메쉬 렌더러를 모두 가져온다.

        for (int i = 0; i < temp.Length; i++)
        {
            if (temp[i].material.name.Substring(0, 3) == "red") temp[i].material = MyMatrial; // red로 시작하는 매터리얼만 현재 병사의 팀 매터리얼로 바꿔준다.
        }
        anim.Play("Idle"); // 대기 상태를 애니메이션한다.
    }

	void Update()
	{
		bool show = GameManager.Instance.ClikedSoldier == this ? false : true;

        if (ViewerButton.isClick) // 우측 상단의 UI에서 장기말 버튼을 누르고 있는 경우
        {
            if (!HUD.activeInHierarchy) // 병사 머리 위의 장기말이 보이지 않는 상태면
            {
                LeanTween.cancel(HUD);
                HUD.transform.localScale = new Vector3(0f, 0f, 0f);
                LeanTween.scale(HUD, new Vector3(-0.8f, 0.8f, 1f), 1f).setEase(LeanTweenType.easeOutElastic);
                HUD.SetActive(show); // 병사 머리 위의 장기말을 보이게 한다.
            }
        }
        else
        {
            if (show)
            {
                if (!HUD.activeInHierarchy)
                {
                    LeanTween.cancel(HUD);
                    HUD.transform.localScale = new Vector3(0f, 0f, 0f);
                    LeanTween.scale(HUD, new Vector3(-0.8f, 0.8f, 1f), 1f).setEase(LeanTweenType.easeOutElastic);
                }
            }
			HUD.SetActive(true); // 병사 머리 위의 장기말을 보이지 않게 한다.	수정
        }

        if (Target != null)
        {
            PosX = Target.PosX;
            PosY = Target.PosY;
        }
    }

    void Complete()
    {
        Target = null;
    }

    public void GetMoveList(Board target) // 장기말의 종류에 따라 이동할 위치를 나타내는 target으로 한칸씩 루트를 만들어 MoveList에 추가시킨다.
    {
        int x = PosX, y = PosY;
        int tx = target.PosX, ty = target.PosY;

        MoveList.Clear(); // 이동 루트 리스트를 초기화한다.

        if (SType == SoldierType.졸 || SType == SoldierType.왕 || SType == SoldierType.사) // 1칸씩 움직이는 졸,왕,사의 경우 시작 위치와 타겟 위치만 넣어주면 된다.
        {
            MoveList.Add(GameManager.Instance.Cell[y][x]);
            MoveList.Add(GameManager.Instance.Cell[ty][tx]);
        }
        else if (SType == SoldierType.차) // 차의 이동 루트 처리
        {
            int distX = tx - x, distY = ty - y;

            if (distX != 0 && distY != 0)
            {
                int xx = distX < 0 ? -1 : 1;
                int yy = distY < 0 ? -1 : 1;

                for (int i = 0; i <= Mathf.Abs(distX); i++)
                {
                    MoveList.Add(GameManager.Instance.Cell[y + (i * yy)][x + (i * xx)]);
                }
            }
            else
            {
                if (tx > x) // RIGHT
                {
                    for (int i = x; i <= tx; i++) MoveList.Add(GameManager.Instance.Cell[ty][i]);
                }
                else if (tx < x) // LEFT
                {
                    for (int i = x; i >= tx; i--) MoveList.Add(GameManager.Instance.Cell[ty][i]);
                }
                else if (ty > y) // DOWN
                {
                    for (int i = y; i <= ty; i++) MoveList.Add(GameManager.Instance.Cell[i][tx]);
                }
                else if (ty < y) // UP
                {
                    for (int i = y; i >= ty; i--) MoveList.Add(GameManager.Instance.Cell[i][tx]);
                }
            }
        }
        else if (SType == SoldierType.마) // 마의 이동 루트 처리
        {
            int distX = x - tx, distY = y - ty;

            MoveList.Add(GameManager.Instance.Cell[y][x]);

            if (Mathf.Abs(distY) == 2)
            {
                MoveList.Add(GameManager.Instance.Cell[y - (distY / 2)][x]);
                MoveList.Add(GameManager.Instance.Cell[y - distY][x - distX]);
            }
            else if (Mathf.Abs(distX) == 2)
            {
                MoveList.Add(GameManager.Instance.Cell[y][x - (distX / 2)]);
                MoveList.Add(GameManager.Instance.Cell[y - distY][x - distX]);
            }
        }
        else if (SType == SoldierType.상) // 상의 이동 루트 처리
        {
            int distX = x - tx, distY = y - ty;

            MoveList.Add(GameManager.Instance.Cell[y][x]);

            if (Mathf.Abs(distY) == 3)
            {
                MoveList.Add(GameManager.Instance.Cell[y - (distY / 3)][x]);
                MoveList.Add(GameManager.Instance.Cell[y - (int)(distY / 1.5f)][x - (distX / 2)]);
                MoveList.Add(GameManager.Instance.Cell[y - distY][x - distX]);
            }
            else if (Mathf.Abs(distX) == 3)
            {
                MoveList.Add(GameManager.Instance.Cell[y][x - (distX / 3)]);
                MoveList.Add(GameManager.Instance.Cell[y - (distY / 2)][x - (int)(distX / 1.5f)]);
                MoveList.Add(GameManager.Instance.Cell[y - distY][x - distX]);
            }
        }
        else if (SType == SoldierType.포) // 포의 이동 루트 처리
        {
            if (tx > x) // RIGHT
            {
                for (int i = x; i <= tx; i++) MoveList.Add(GameManager.Instance.Cell[ty][i]);
            }
            else if (tx < x) // LEFT
            {
                for (int i = x; i >= tx; i--) MoveList.Add(GameManager.Instance.Cell[ty][i]);
            }
            else if (ty > y) // DOWN
            {
                for (int i = y; i <= ty; i++) MoveList.Add(GameManager.Instance.Cell[i][tx]);
            }
            else if (ty < y) // UP
            {
                for (int i = y; i >= ty; i--) MoveList.Add(GameManager.Instance.Cell[i][tx]);
            }
        }
    }

    public void MoveTo(Board target) // 실제로 병사를 이동시켜주는 함수
    {
        anim.Play("Walk"); // 걷는 애니메이션으로 바꿔준다.
        GetMoveList(target); // 이동 루트를 계산해서 얻어온다.

        Target = target;
        Vector3 dir = MoveList[1].transform.position - transform.position;

        Quaternion angle = Quaternion.LookRotation(dir); // 현재 위치에서 이동할 다음 칸의 각도를 구한다.
        float timer = Quaternion.Angle(transform.rotation, angle) / 900f; // 현재 각도에서 목표 회전값의 차를 구한 후, 이 값을 다시 900으로 나눠 회전하는데 필요한 적당한 속도를 얻는다.

        int tx = target.PosX, ty = target.PosY;
        bool enemy = GameManager.Instance.isEmemy(tx, ty, MyTeam); // 목표 지점에 적이 있는지 여부를 체크한다. 적이 있으면 먼저 공격을 해야 하기 때문이다.

        transform.DOLookAt(MoveList[1].transform.position, timer).SetEase(Ease.Linear);

        // 아래 루틴은 각 말의 종류에 따라 MoveList에 저장된 값들을 토대로 순차적으로 이동시켜주는 부분이다.
        // DotTween을 사용했기 때문에 트윈 플러그인의 메카니즘을 먼저 이해한 후에 분석해야 한다.

        if (SType == SoldierType.졸)
        {
            if (enemy)
			{
				//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                transform.DOMove(MoveList[0].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                timer += 2f;
            }
            transform.DOMove(MoveList[1].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
            timer += 0.3f;

            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }
        else if (SType == SoldierType.차)
        {
            for (int i = 1; i < MoveList.Count; i++)
            {
                if (enemy && i == 1)
                {
					//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                    transform.DOMove(MoveList[0].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                    timer += 2f;
                }
                transform.DOMove(MoveList[i].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
                timer += 0.3f;
            }
            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }
        else if (SType == SoldierType.포)
        {
            for (int i = 1; i < MoveList.Count; i++)
            {
                if (enemy && i == 1)
                {
					//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                    transform.DOMove(MoveList[0].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                    timer += 2f;
                }
                transform.DOMove(MoveList[i].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
                timer += 0.3f;
            }
            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }
        else if (SType == SoldierType.마)
        {
            transform.DOMove(MoveList[1].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear);
            timer += 0.3f;

            transform.DOLookAt(MoveList[2].transform.position, 0.1f).SetDelay(timer).SetEase(Ease.Linear);
            timer += 0.1f;

            if (enemy)
            {
				//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                transform.DOMove(MoveList[1].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                timer += 2f;
            }
            transform.DOMove(MoveList[2].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
            timer += 0.3f;

            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }
        else if (SType == SoldierType.상)
        {
            transform.DOMove(MoveList[1].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear);
            timer += 0.3f;

            transform.DOLookAt(MoveList[2].transform.position, 0.1f).SetDelay(timer).SetEase(Ease.Linear);
            timer += 0.1f;

            if (enemy)
            {
				//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                transform.DOMove(MoveList[1].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                timer += 2f;
            }
            transform.DOMove(MoveList[2].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
            timer += 0.3f;

            transform.DOMove(MoveList[3].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear);
            timer += 0.3f;

            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }
        else if (SType == SoldierType.왕 || SType == SoldierType.사)
        {
            int distX = Mathf.Abs(PosX - tx), distY = Mathf.Abs(PosY - ty);

            if (distX == 1 && distY == 1)
            {
                transform.DOLookAt(MoveList[1].transform.position, 0.1f).SetDelay(timer).SetEase(Ease.Linear);
                timer += 0.1f;
            }

            if (enemy)
            {
				//AutoCame@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GameManager.Instance.myAutoCam.gameObject.SetActive (true);

                transform.DOMove(MoveList[0].transform.position, 1f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteAttack).OnStart(Attack);
                timer += 2f;
            }
            transform.DOMove(MoveList[1].transform.position, 0.3f).SetDelay(timer).SetEase(Ease.Linear).OnStart(StartMove);
            timer += 0.3f;

            transform.DORotate(Rot[(int)MyTeam].eulerAngles, 0.2f).SetDelay(timer).SetEase(Ease.Linear).OnComplete(CompleteMove);
        }

        PosX = target.PosX;
        PosY = target.PosY;
    }

    void Attack()
    {
        // 상대방이 포가 아니면 공격자를 쳐다보게 한다.
        if (SType != SoldierType.포)
        {
            Target.Player.transform.LookAt(transform);
        }
        anim.Play("Attack");

        if (SType != SoldierType.차)
        {
            if (MyGun != null)
            {
                MyGun.SendMessage("Play", true);
            }
        }
    }

    public void TargetDamage()
    {
        if (SType == SoldierType.포 || SType == SoldierType.차)
        {
            MyGun.GetComponent<GunFire>().ShootBullet(Target.transform, 1f);
        }
        else
        {
            if (Target.Player != null) Target.Player.SendMessage("Damage");
        }
    }

    public void Damage()
    {
        anim.Play("Damage");
        if (DamageAudio != null) DamageAudio.Play();
        Blood.Play();
    }

    public void Death(string name)
    {
        Blood.Play();
        if (DeadAudio != null) DeadAudio.Play();
        anim.Play(name);
    }

    void StartMove()
    {
        anim.Play("Walk");
    }

    void CompleteMove()
    {
        anim.Play("Idle");
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		Target.Type = SType;
		Target.Team = MyTeam;
		Target.Player = this;
		Target = null;

        GameManager.Instance.ChangeTurn(); // 이동이 완료되면 턴을 바꾼다.
        
    }

    void CompleteAttack()
    {
        anim.Play("Idle");

        if (SType != SoldierType.포 && SType != SoldierType.차)
        {
            Target.Player.SendMessage("Death", "Dead");
        }

        if (MyGun != null)
        {
            MyGun.SendMessage("Play", false);
        }
    }

    public void Explosion()
    {
        if (SType == SoldierType.포)
        {
            Vector3 pos = Target.Player.transform.position;

            Target.Player.SendMessage("Death", "Dead");
            Target.Player.transform.DOJump(pos, 1f, 1, 1f);

            GameManager.Instance.Explosion.transform.position = Target.transform.position;
            GameManager.Instance.Explosion.SetActive(true);
        }
    }
}
