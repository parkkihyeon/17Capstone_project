using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControllTouch : MonoBehaviour {

	public void SetDontTouch(){
		GameManager.Instance.DontTouch = true;
	}

	public void SetTouchAble(){
		GameManager.Instance.DontTouch = false;
	}
}
