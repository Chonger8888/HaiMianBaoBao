package org.weme.candy.service;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;
import org.weme.candy.activity.c_game_candy;
import org.weme.candy.comm.c_weme_http_candy;
import org.weme.candy.data.bean.c_constant_bean;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.ActivityManager.RunningTaskInfo;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.text.TextUtils;
import android.widget.RemoteViews;
/**
 * 好友赠送生命和添加好友消息后台服务推送
 * @author ivan
 * @since 2014-04-19
 */
public class c_service_push_message extends Service {
	private static CandyHandler candyHandler;
	static Notification notification;
	static NotificationManager mNotificationManager;
	private static String userId;
	int stop_time=300000;
	static Boolean cancelFlag=false;
	 Intent intent = null;

	public static void setCancelFlag(Boolean cancelFlag) {
		c_service_push_message.cancelFlag = cancelFlag;
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();
		candyHandler = new CandyHandler();
	}

	@Override
	public void onDestroy() {
		if (mNotificationManager!=null&&cancelFlag) {
			mNotificationManager.cancelAll();
		}
		candyHandler.removeCallbacks(runnable);
		super.onDestroy();
	}
	@Override
	public void onStart(Intent intent, int startId) {
		
	}
	Runnable runnable =new Runnable() {
		@Override
		public void run() {
			candyHandler.sendEmptyMessage(0);
		}
	};
	int run_flag = 0;
	private void initNotifi(int num,String user_names,int nid){
      
	}
	

	public void access_message(){
	
	}
	
	class CandyHandler extends Handler{
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			if (msg.what==0) {
				access_message();
			}
		}
		
	}
	
	/**
	 * 判断activity是否在运行
	 * @param mContext
	 * @param activityClassName
	 * @return
	 */
	public boolean isActivityRunning(Context mContext,String activityClassName){  
	    ActivityManager activityManager = (ActivityManager) mContext.getSystemService(Context.ACTIVITY_SERVICE);  
	    List<RunningTaskInfo> info = activityManager.getRunningTasks(1);
	    if(info != null && info.size() > 0){  
	        ComponentName component = info.get(0).topActivity; 
	        if(activityClassName.equals(component.getClassName())){  
	            return true;  
	           }  
	        }  
	    return false;  
	}  
	
	/**
	 * 判断app程序是否在运行
	 * @param context
	 * @return
	 */
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
    String message_nike ,nikes;
    int lift_num =0,msg_num=0;
	private void msg_life_message(String json){
		if (json.contains("\"status\":-1,\"id\":0")) {
			return;
		}else{
		StringBuffer nikes = new StringBuffer();
	    StringBuffer message_nike = new StringBuffer();
        try {
			JSONObject jo = new JSONObject(json);
			JSONObject content = (JSONObject) jo.get("content");
			JSONObject life = (JSONObject) content.get("handsel_life_message");
			JSONArray jsonArray = (JSONArray) life.get("handsel_life_message_info");
			JSONObject msg = (JSONObject) content.get("apply_user_message");
			JSONArray msgArray = (JSONArray) msg.get("apply_user_message_info");
			lift_num = Integer.parseInt(life.getString("handsel_life_message_count"));
			msg_num = Integer.parseInt(msg.getString("apply_user_message_count"));
			for (int i = 0; i < jsonArray.length(); i++) {
				 JSONObject o = (JSONObject) jsonArray.get(i);
				 nikes.append(o.getString("nickname"));
				 if (i!=jsonArray.length()-1) {
					 nikes.append("、");
				 }
			}
			for (int j = 0;j < msgArray.length(); j++) {
				 JSONObject o = (JSONObject) msgArray.get(j);
				 message_nike.append(o.getString("nickname"));
				 if (j!=msgArray.length()-1) {
					 message_nike.append("、");
				 }
			}
			this.message_nike = message_nike.toString();
			this.nikes = nikes.toString();
		} catch (Exception e) {
			e.printStackTrace();
		}
	  }
	}
	
	public static void cancelFlag(){
		if (mNotificationManager!=null) {
			mNotificationManager.cancelAll();
		}
	}
	
	public void pushToPreference(int new_push_number,String str_key){
	}
	public boolean isServiceRunning(Context mContext, String className) {
		boolean isRunning = false;
		ActivityManager activityManager = (ActivityManager) mContext
				.getSystemService(Context.ACTIVITY_SERVICE);
		List<ActivityManager.RunningServiceInfo> serviceList = activityManager
				.getRunningServices(200);
		if (!(serviceList.size() > 0)) {
			return false;
		}
		for (int i = 0; i < serviceList.size(); i++) {
			if (serviceList.get(i).service.getClassName().equals(className) == true) {
				isRunning = true;
				break;
			}
		}
		return isRunning;
	}
	
}
