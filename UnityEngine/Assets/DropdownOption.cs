using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class DropdownOption : MonoBehaviour {

	//List<string> ChoHan = new List<string> (){"임시", "초", "한"};
	List<string> Mycharim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };

	public Dropdown dropdown0;
	public Dropdown GameOver;

	//public Text selectedName;

	public void Dropdown0_Index(int index){
		//ConnectServer.Instance.Charim = index;
			GameManager.Instance.MyCharim = index;
	}

	public void GameOver_Index(int index){
		GameManager.Instance.MyCharim = index;
	}
		
	void Start () {
		PopulateList();
	}

	public void PopulateList(){
		dropdown0.AddOptions (Mycharim);
		GameOver.AddOptions (Mycharim);
	}

}
