using UnityEngine;
using System.Collections;
using UnityEngine.UI;
/*
 * This class provides an example for how to use the blewrapper class
 * Author: Justin Vrana, 5-22-15
 */
public class UpdateText : MonoBehaviour {
	public Text statusText;
	public Text gyrox;
	public Text gyroy;
	public Text gyroz;
	public Text accelx;
	public Text accely;
	public Text accelz;
	public Vector3 gyro = new Vector3(0f,0f,0f);
	public Vector3 acceleration = new Vector3(0f,0f,0f);
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		statusText.text = "Bluetooth Status: " + BleWrapper.getBleStatus ();

		gyro = BleWrapper.getGyroData ();
		gyrox.text = "Gyroscope X: " + gyro.x.ToString ();
		gyroy.text = "Gyroscope Y: " + gyro.y.ToString ();
		gyroz.text = "Gyroscope Z: " + gyro.z.ToString ();

		acceleration = BleWrapper.getAccelData ();
		accelx.text = "Acceleration X: " + acceleration.x.ToString ();
		accely.text = "Acceleration Y: " + acceleration.y.ToString ();
		accelz.text = "Acceleration Z: " + acceleration.z.ToString ();
	}
}
