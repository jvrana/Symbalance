using UnityEngine;
using System.Collections;

public class RotateCamera : MonoBehaviour {
	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 or = BleWrapper.getOrientation ();
		Quaternion rotation = Quaternion.Euler (or.y, or.x, -or.z);
		Quaternion current = transform.localRotation;
		transform.rotation = rotation;
	}
}
