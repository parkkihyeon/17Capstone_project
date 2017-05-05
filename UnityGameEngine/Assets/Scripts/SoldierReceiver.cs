using UnityEngine;
using System.Collections;

public class SoldierReceiver : MonoBehaviour
{
    // 이 함수는 메카님 애니메이션의 이벤트 설정에서 호출된다. 코딩 상으로는 호출되지 않는다.
    // 이 함수가 호출되는 부분을 보고 싶으면 Player_로 시작하는 프리펩을 하이어라키에 생성하고 선택한 후, CTRL+6을 누르면 볼 수 있다.
    public void Attack()
	{
        GetComponentInParent<Soldier>().TargetDamage();
    }

    // 총알 파티클에서 충돌 신호가 들어온 경우
    void OnParticleCollision(GameObject other)
    {
        GetComponentInParent<Soldier>().Damage();
    }

    public void Death()
    {
        transform.parent.gameObject.SetActive(false);
    }

    public void PlaySound()
    {
        GetComponent<AudioSource>().Play();

        if (GetComponentInParent<Soldier>().SType == SoldierType.차)
        {
            GetComponentInChildren<GunFire>().Play(true);
        }
    }
}
