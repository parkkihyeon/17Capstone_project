using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class DropdownOption : MonoBehaviour {

	//List<string> ChoHan = new List<string> (){"임시", "초", "한"};
	List<string> charim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };

	public Dropdown myDrop;
	//public Dropdown otherDrop;

	public Dropdown gameover_My;
	//public Dropdown gameover_Other;

	//public Text selectedName;

	public void My_Index(int index){
		//ConnectServer.Instance.Charim = index;
		GameManager.Instance.MyCharim = index;
	}
	//public void Other_Index(int index){
	//	GameManager.Instance.OtherCharim = index;
	//}

	public void GameOver_My_Index(int index){
		GameManager.Instance.MyCharim = index;
	}

	//public void GameOver_Other_Index(int index){
	//	GameManager.Instance.OtherCharim = index;
	//}

		
	void Start () {
		PopulateList();
	}

	public void PopulateList(){
		myDrop.AddOptions (charim);
		//otherDrop.AddOptions (charim);
		gameover_My.AddOptions (charim);
		//gameover_Other.AddOptions (charim);
	}

}
