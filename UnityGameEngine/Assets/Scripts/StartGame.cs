using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using DG.Tweening;

public class StartGame : MonoBehaviour
{
    public GameObject StartButton;

    public void ShowStartButton()
    {
        StartButton.SetActive(true);
        StartButton.transform.DOScale(1f, 0.5f).SetEase(Ease.OutElastic);
    }

    public void ClickedStart()
    {
        if (StartButton.GetComponentInChildren<InputField>().text.Length <= 0)
        {
            GameManager.Instance.Popup("닉네임을 입력하세요.");
            return;
        }
        GameManager.Instance.NickName = StartButton.GetComponentInChildren<InputField>().text;

        StartButton.transform.parent.gameObject.SetActive(false);
        ConnectServer.Instance.Execute();
    }
}