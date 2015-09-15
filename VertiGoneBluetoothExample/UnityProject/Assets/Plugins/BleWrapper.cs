using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
/*
 * This class provides access to the bluetooth plugin methods and static values
 * Author: Justin Vrana, 5-22-15
 */

public class BleWrapper : MonoBehaviour {
	public static string packageName = "com.vertigone.plugin";
	public static AndroidJavaClass sensorValuesJC = new AndroidJavaClass(packageName + ".SensorValues"); 
	public static AndroidJavaClass gameActivityJC = new AndroidJavaClass(packageName + ".GameActivity"); 
	public static AndroidJavaClass vertiGoneHelperJC = new AndroidJavaClass(packageName + ".VertiGoneHelper");
	public static AndroidJavaClass statusJC = new AndroidJavaClass(packageName + ".Status");

	#if !DEBUGMODE && UNITY_ANDROID
	public static string getBleStatus()
	{
		string bleStatus = statusJC.GetStatic<string>("CurrentBluetoothStatus"); 
		return bleStatus;
	}

	public static string getVertiGoneStatus()
	{
		string vStatus = statusJC.GetStatic<string>("CurrentVertiGoneStatus"); 
		return vStatus;
	}

	public static Vector3 getQuatData() 
	{
		float quatw = sensorValuesJC.GetStatic<float> ("quat_w");
		float quatx = sensorValuesJC.GetStatic<float> ("quat_x");
		float quaty = sensorValuesJC.GetStatic<float> ("quat_y");
		float quatz = sensorValuesJC.GetStatic<float> ("quat_z");
		Quaternion quat = new Quaternion (quatx, quaty, quatz, quatw);
		return quat
	}


	#endif
}
