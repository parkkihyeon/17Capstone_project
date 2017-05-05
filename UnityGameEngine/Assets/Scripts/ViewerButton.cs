using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;

public class ViewerButton : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    // 우측 상단의 장기알 버튼이 눌려있는 상태인지 나타낸다.
    // 이 값이 true이면 병사들 머리 위에 장기알을 보여준다.
    public static bool isClick = false;

    public void OnPointerDown(PointerEventData eventData)
    {
        isClick = true;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        isClick = false;
    }
}
