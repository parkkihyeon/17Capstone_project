using UnityEngine;
using System.Collections;
using DG.Tweening;

public class GunFire : MonoBehaviour
{
    GameObject newBullet;
    public GameObject FireEff, Bullet;

    // 뭔가를 쏘는 병사들의 처리 루틴 (상,마,차,포 4개의 프리펩에 적용돼 있다)
    // 왕,사,졸은 1칸 이내에서 공격하기 때문에 따로 총알 등을 발사하지 않는다.
    public void ShootBullet(Transform target, float timer)
    {
        newBullet = Instantiate(Bullet, Bullet.transform.position, Bullet.transform.rotation) as GameObject;
        newBullet.SetActive(true);
        Soldier temp = GetComponentInParent<Soldier>();

        if (temp.SType == SoldierType.포)
        {
            newBullet.transform.DOJump(target.position, 0.6f, 1, timer).SetEase(Ease.Linear).OnComplete(CompleteBullet);
            newBullet.transform.DOLookAt(target.position, 1f).SetEase(Ease.Linear);
        }
        else if (temp.SType == SoldierType.차)
        {
            Vector3 pos = target.position;
            pos.y = Bullet.transform.position.y;
            float dist = Vector3.Distance(pos, newBullet.transform.position) / 15f;
            newBullet.transform.DOMove(pos, dist).SetEase(Ease.Linear).OnComplete(CompleteBullet);
        }
    }

    void CompleteBullet() // '포'나 '차'의 총알이나 대포가 목표지점에 도달했을때 호출된다.
    {
        Soldier temp = GetComponentInParent<Soldier>();

        if (temp.SType == SoldierType.포)
        {
            temp.Explosion(); // 대포알이 목표지점에 도착했을때 폭발 파티클을 보여준다.
        }
        if (temp.SType == SoldierType.차)
        {
            temp.Target.Player.SendMessage("Death", "StunDeath"); // 차는 저격총이므로 상대방이 회전하면서 죽는 애니를 하도록 처리한다.
        }
        Destroy(newBullet); // 총알을 파괴한다.
    }

    public void Play(bool isShow)
	{
        if (FireEff != null) FireEff.SetActive(isShow);
    }
}
