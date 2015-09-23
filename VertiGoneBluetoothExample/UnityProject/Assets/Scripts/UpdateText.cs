using UnityEngine;
using System.Collections;
using UnityEngine.UI;
/*
 * This class provides an example for how to use the blewrapper class
 * Author: Justin Vrana, 5-22-15
 */
public class UpdateText : MonoBehaviour {
	public Text statusText;
	
	// Update is called once per frame
	void Update () {
		statusText.text = "Bluetooth Status: " + BleWrapper.getBleStatus ();
	}
}
