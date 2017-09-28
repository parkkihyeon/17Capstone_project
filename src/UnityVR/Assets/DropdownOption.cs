using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class DropdownOption : MonoBehaviour {

	//List<string> ChoHan = new List<string> (){"임시", "초", "한"};
	//List<string> othercharim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };
	List<string> Mycharim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };

	public Dropdown My;
	//public Dropdown Other;
	public Dropdown GameOver;
	//public Dropdown GameOver_other;

	//public Text selectedName;

	public void My_Index(int index){
		//ConnectServer.Instance.Charim = index;
		GameManager.Instance.MyCharim = index;
	}
	//public void Other_Index(int index){
		//ConnectServer.Instance.Charim = index;
	//	GameManager.Instance.MyCharim = index;
	//}

	public void GameOver_Index(int index){
		GameManager.Instance.MyCharim = index;
	}

	//public void GameOver_Other_Index(int index){
	//	GameManager.Instance.MyCharim = index;
	//}

	void Start () {
		PopulateList();
	}

	public void PopulateList(){
		Debug.Log ("test");
		My.AddOptions (Mycharim);
		//Other.AddOptions (othercharim);
		GameOver.AddOptions (Mycharim);
		//GameOver_other.AddOptions (Mycharim);
	}

}
