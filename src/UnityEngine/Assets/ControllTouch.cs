using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class controllTouch : MonoBehaviour {

	public void setDontTouch(){
		GameManager.Instance.DontTouch = true;
	}

	public void setTouchAble(){
		GameManager.Instance.DontTouch = false;
	}
}
