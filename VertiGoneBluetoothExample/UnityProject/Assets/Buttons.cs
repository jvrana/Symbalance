using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Buttons : MonoBehaviour {
	public Text status;
	public Vector3 orientation;
	void OnGUI () {
		// Make a background box
		GUI.Box(new Rect(10,10,150,90), "Symbalance Menu");
		GUI.Box(new Rect(180,10,400,90), "BLE Status");
	}
}