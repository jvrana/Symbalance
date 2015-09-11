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

	public static Vector3 getGyroData() 
	{
		float gyrox = sensorValuesJC.GetStatic<float> ("gyro_x");
		float gyroy = sensorValuesJC.GetStatic<float> ("gyro_y");
		float gyroz = sensorValuesJC.GetStatic<float> ("gyro_z");
		Vector3 gyro = new Vector3 (gyrox, gyroy, gyroz);
		return gyro;
	}

	public static Vector3 getAccelData() 
	{
		float accelx = sensorValuesJC.GetStatic<float> ("acceleration_x");
		float accely = sensorValuesJC.GetStatic<float> ("acceleration_y");
		float accelz = sensorValuesJC.GetStatic<float> ("acceleration_z");
		Vector3 accel = new Vector3 (accelx, accely, accelz);
		return accel;
	}
	#endif
}
