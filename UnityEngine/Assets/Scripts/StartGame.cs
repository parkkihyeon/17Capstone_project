using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using DG.Tweening;

public class StartGame : MonoBehaviour
{
    public GameObject StartButton;
    public Dropdown dropdown0;
    public Dropdown dropdown1;

    public void ShowStartButton()
    {
        StartButton.SetActive(true);
        StartButton.transform.DOScale(1f, 0.5f).SetEase(Ease.OutElastic);
        dropdown0.transform.gameObject.SetActive(true);
        //dropdown1.transform.gameObject.SetActive(true);
    }

    public void ClickedStart()
    {

        //GameManager.Instance.NickName = StartButton.GetComponentInChildren<InputField>().text;

        StartButton.transform.parent.gameObject.SetActive(false);
        dropdown0.transform.gameObject.SetActive(false);
        //dropdown1.transform.gameObject.SetActive(false);
		ConnectServer.Instance.Execute();
		GameManager.Instance.SetStartGame (0);
    }
}