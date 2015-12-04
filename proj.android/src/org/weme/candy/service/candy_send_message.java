package org.weme.candy.service;

import java.util.List;

import org.weme.candy.activity.c_game_candy;

import android.app.ActivityManager;
import android.app.Service;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;

/**
 *  用户点击push进入界面的时候，通知底层显示消息框
 * @author ivan
 * @since 2014-05-06
 */
public class candy_send_message extends Service {
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();
	}

	@Override
	public void onStart(Intent intent, int startId) {
		Intent activityintent = new Intent(this, c_game_candy.class);
		//activityintent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		activityintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//		activityintent.putExtra("message", "0");
		this.startActivity(activityintent);
//		Intent mIntent = new Intent("update_service_data");  
//        mIntent.putExtra("type", "update");  
//        sendBroadcast(mIntent); 
		super.onStart(intent, startId);
	}

	public boolean isAppInForeground(Context context) {  
		boolean istrue = false;
	    ActivityManager activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);  
	    List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();  
	    for (RunningAppProcessInfo appProcess : appProcesses) {  
	        if (appProcess.processName.equals(context.getPackageName())) {
	            //return appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND;
	        	istrue=true;
	        }  
	    }  
	    return istrue;  
	}  
	
}
