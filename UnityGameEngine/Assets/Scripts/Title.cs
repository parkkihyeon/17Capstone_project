using UnityEngine;
using System.Collections;
using DG.Tweening;

public class Title : MonoBehaviour
{
	void Start()
	{
        GetComponent<AudioSource>().Play();
        transform.DOLocalMoveX(-40f, 0.5f).SetEase(Ease.OutBack).SetDelay(0.5f);
        transform.DOLocalMoveX(-2184f, 0.5f).SetEase(Ease.OutBack).SetDelay(2.5f).OnComplete(Complete);
    }
    
    void Complete()
    {
        GetComponentInParent<StartGame>().ShowStartButton();
    }
}
