using UnityEngine;
using System.Collections;
using UnityEngine.UI;
/*
 * This class provides an example for how to use the blewrapper class
 * Author: Justin Vrana, 5-22-15
 */
public class UpdateText : MonoBehaviour {
	public Text statusText;
	public Text quatx;
	public Text quaty;
	public Text quatz;
	public Text quatw;
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		statusText.text = "Bluetooth Status: " + BleWrapper.getBleStatus ();

		Quaternion quat = BleWrapper.getQuatData ();
		quatx.text = "Quaternion X: " + quat.x.ToString ();
		quaty.text = "Quaternion Y: " + quat.y.ToString ();
		quatz.text = "Quaternion Z: " + quat.z.ToString ();
		quatw.text = "Quaternion W: " + quat.w.ToString ();
	}
}
