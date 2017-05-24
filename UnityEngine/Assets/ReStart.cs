using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ReStart : MonoBehaviour {

	public Button OkButton;
	public Button CanCelButton;
	public Dropdown position;
	public Dropdown other_position;
	public GameObject PopUp;

	public int charim;
	public int other;

	List<string> Mycharim = new List<string> (){ "마상마상", "마상상마", "상마마상", "상마상마" };

	public void position_index(int index){

		charim = index;
	}

	public void other_position_index(int index){
		other = index;
	}

	void Start () {
		PopulateList();
	}

	public void PopulateList(){
		position.AddOptions (Mycharim);
		other_position.AddOptions (Mycharim);
	}

	public void ReStartGame(){
		Debug.Log ("game restart");
		GameManager.Instance.MyCharim = charim;
		GameManager.Instance.OtherCharim = other;
		GameManager.Instance.IsGameOver = false;
		GameManager.Instance.DontTouch = false;
		GameManager.Instance.StartGame = false;
		GameManager.Instance.SetStartGame (0);
	}

}
