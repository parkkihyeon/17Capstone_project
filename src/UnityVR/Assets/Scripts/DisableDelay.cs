using UnityEngine;
using System.Collections;

public class DisableDelay : MonoBehaviour
{
    public float Delay = 1f;

	void OnEnable()
	{
        Invoke("Hide", Delay); // 오브젝트가 활성화 되면 Delay초 이후에 비활성화시킨다.
	}

    void Hide()
	{
        gameObject.SetActive(false);
	}
}
