using UnityEngine;
using System.Collections;
using DG.Tweening;

public class GameOver : MonoBehaviour
{
    public void QuitGame() // 게임 종료 팝업이 떴을때 "예"를 선택하면 호출된다.
    {
        Application.Quit();
    }
}
