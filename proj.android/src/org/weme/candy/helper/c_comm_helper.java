package org.weme.candy.helper;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.util.Enumeration;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.text.format.Formatter;

public class c_comm_helper {
	
	/**
	 * 获取网络类型，可能返回"WIFI"或者"GPRS"
	 * <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
	 * @param context
	 * @return
	 */
	public static String getNetType(Context context){
		String netType = "unknown";
		NetworkInfo networkInfo = ((ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE)).getActiveNetworkInfo();
		if(networkInfo != null && networkInfo.isConnected()){
			if(networkInfo.getType() == ConnectivityManager.TYPE_WIFI)
				netType = "WIFI";
			else if(networkInfo.getType() == ConnectivityManager.TYPE_MOBILE)
				netType = "GPRS";
		}
		return netType;
	}
	
	
	/**
	 * 获取正在使用的网卡的IP，需要如下权限:
	 * <uses-permission android:name="android.permission.INTERNET"/>
	 * <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
	 * <uses-permission android:name="android.permission.ACCESS_WIFI_STATE"/>
	 * @param context
	 * @return
	 */
	public static String getInetAddress(Context context){
		String ip = "";
		try{
			NetworkInfo networkInfo = ((ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE)).getActiveNetworkInfo();
			if(networkInfo != null && networkInfo.isConnected()){
				if(networkInfo.getType() == ConnectivityManager.TYPE_WIFI){
					WifiManager wifiManager = (WifiManager)context.getSystemService(Context.WIFI_SERVICE);
					if(wifiManager != null){
						WifiInfo wifiInfo = wifiManager.getConnectionInfo();
						if(wifiInfo != null)
							ip = Formatter.formatIpAddress(wifiInfo.getIpAddress());
					}
				}else{
					Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();
					if(networkInterfaces != null){
						while(networkInterfaces.hasMoreElements()){
							NetworkInterface networkInterface = networkInterfaces.nextElement();
							if(networkInterface.isUp() && !networkInterface.isLoopback() && !networkInterface.isPointToPoint() && !networkInterface.isVirtual()){
								Enumeration<InetAddress>inetAddresses = networkInterface.getInetAddresses();
								if(inetAddresses != null){
									while(inetAddresses.hasMoreElements()){
										InetAddress inetAddress = inetAddresses.nextElement();
										if(!inetAddress.getHostAddress().contains("::"))
											ip = inetAddress.getHostAddress();
									}
								}
							}
						}
					}
				}
			}
		}catch(Exception e){
			e.printStackTrace();
		}
		return ip;	
	}
}
