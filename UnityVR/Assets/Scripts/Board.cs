using UnityEngine;
using System.Collections;

public class Board : MonoBehaviour
{
    public int PosX, PosY; // 위치값
    public SoldierType Type = SoldierType.NONE; // 병사가 없는 곳은 NONE이 디폴트지만, 병사가 위치하면 마,상,사,왕,졸,차,포 중에 하나를 갖는다.
    public SolTeam Team = SolTeam.RED; // 레드팀인가 블루팀인가를 나타낸다.
    public Soldier Player; // 실제 병사를 가리킬 오브젝트

    public void SetPosition(int x, int y) // 위치값 설정 함수
    {
        PosX = x;
        PosY = y;
    }
}
