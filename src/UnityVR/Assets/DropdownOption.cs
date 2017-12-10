using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class DropdownOption : MonoBehaviour {

	List<string> charim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };

	public Dropdown myCharim;
	//public Dropdown Other;
	public Dropdown gameOver;
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

	void Start () {
		PopulateList();
	}

	public void PopulateList(){
		Debug.Log ("test");
		myCharim.AddOptions (charim);
		//Other.AddOptions (othercharim);
		gameOver.AddOptions (charim);
		//GameOver_other.AddOptions (Mycharim);
	}

}
