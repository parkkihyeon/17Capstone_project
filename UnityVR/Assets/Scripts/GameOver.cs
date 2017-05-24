using UnityEngine;
using System.Collections;
using DG.Tweening;

public class GameOver : MonoBehaviour
{
	public void QuitGame()
	{

		GameManager.Instance.exit ();

		//Application.Quit ();

		// save any game data here
		#if UNITY_EDITOR
		// Application.Quit() does not work in the editor so
		// UnityEditor.EditorApplication.isPlaying need to be set to false to end the game
		UnityEditor.EditorApplication.isPlaying = false;
		#else
		Application.Quit();
		#endif

	}
}
