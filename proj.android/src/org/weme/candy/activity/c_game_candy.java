package org.weme.candy.activity;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.lang.ref.WeakReference;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.weme.candy.comm.c_app_define;
import org.weme.candy.helper.c_comm_helper;
import org.weme.candy.helper.c_progress_circle;
import org.weme.candy.service.c_service_push_message;
import org.weme.candy.util.CandyPay;
import org.weme.candy.util.CppCallJava;
import org.weme.candy.util.JavaCallCpp;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;

import com.umeng.analytics.game.UMGameAgent;

/**
 * 游戏界面
 * org.weme.happyboom.mini
 * @author wind
 * @since 2013-11-20
 */
public class c_game_candy extends Cocos2dxActivity {
	public static c_game_candy instance;
	private c_progress_circle c_progress_circle;
	public static String userId , deviceId;
	public static CandyHandler candyHandler;
	private Intent life_service_intent , messageIntent;
	public static boolean chat_activity=false;
	static PackageInfo pki;
	
	String mPaycode;
	String mOrderId;
	int mPricepoint;
	int mNum;
	
	private static Context context;
	private static final String APPID = "300008951795";
	private static final String APPKEY = "E941930DB5CDFC97C8A5C5E85F559BDA";
	 
	public Handler m_myhandler = new Handler(){
		@Override		
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			switch(msg.what){
			case 0:
				CandyPay.ShowPrompt();
				break;

			default:				
				break;
			}
			
			
			
		}
};
		
	private static String signature , versionName;
	
	static {
		System.loadLibrary("cocos2dcpp");
	}
    static int oncreateCount=0;
    
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,  WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		super.onCreate(savedInstanceState);
		UMGameAgent.init(this);
		instance = this;
		context = c_game_candy.this;
		deviceId = "0000000";
		candyHandler = new CandyHandler(instance);
		init_handler();
		
		//SDK初始化(易接)
		SDKinit();
		
	}
	
	public static void jniDoPay( String paycode, String orderId, int pricepoint, int num ){
		c_game_candy.instance.doPay( paycode,orderId,pricepoint, num);
	}
	

	
	private void doPay( String paycode, String orderId, int pricepoint, int num){
		mPaycode = paycode;
		mOrderId = orderId;
		mPricepoint = pricepoint;
		mNum = num;
		
		// test
		buySuccess();
		//m_myhandler.sendEmptyMessage( 9 );
	}
	
	private void buySuccess(){
//		money 本次消费的金额(非负数) 
//		item 购买物品的ID(不能为空) 
//		number 购买物品数量(非负数) 
//		price 每个物品等值虚拟币的价格(非负数) 
//		source 支付渠道 (见上表)
//		1	Google Play
//		2	支付宝
//		3	网银
//		4	财付通
//		5	移动通信
//		6	联通通信
//		7	电信通信
//		8	paypal
		// 友盟付费统计
		UMGameAgent.pay((mPricepoint)/100, mPaycode, 1, 0, 5);
		
		CandyPay.Prompt("购买成功");
		CandyPay.PaySuccess("0");
	}
	
	private void buyFailed(){
		CandyPay.Prompt("购买失败");
		CandyPay.PayFailed();
	}
	
	public void game_exit(){
		
	}
	
	private void init_handler(){
		c_progress_circle = new c_progress_circle(instance);
		// 获取电话服务
		 pki = c_game_candy.this.getMyPackageInfo(instance);
		// 获取渠道号和版本号
		if (pki != null) {
			signature = c_app_define.define_android_app_market_signature;
			versionName = pki.versionName;
		}
		messageIntent = new Intent(this, c_service_push_message.class);
	}

	@Override
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		return glSurfaceView;
	}


	public static String getUserID(){
				
		return "0000";

	}
	/**
	 * 注销
	 */
	public static void logout() {
		if (instance != null) {
		}
	}

	/**
	 * 校验lua文件
	 */
	public static void verifyLuas(final String userId, final String deviceId,final int luaindex) {
		new AsyncTask<Void, Void, String>() {
			@Override
			protected String doInBackground(Void... params) {
				AssetManager assetManager = instance.getAssets();
				StringBuilder stringBuilder = new StringBuilder();
				for (int i = (luaindex > 20?luaindex-20:1); i <= (luaindex < 185?luaindex+40:225); i++) {
//				for (int i = 1; i <=225; i++) {
					String content = null;
					InputStream inputStream = null;
					ByteArrayOutputStream byteArrayOutputStream = null;
					try {
						inputStream = assetManager.open("lua/level" + i + ".lua");
						byteArrayOutputStream = new ByteArrayOutputStream();
						byte[] buffer = new byte[1024];
						int readBytes = -1;
						while ((readBytes = inputStream.read(buffer)) != -1) {
							byteArrayOutputStream.write(buffer, 0, readBytes);
						}
						content = i+ "=" ;
					} catch (Exception e) {
						e.printStackTrace();
					} finally {
						if (inputStream != null) {
							try {
								inputStream.close();
							} catch (Exception e2) {
								e2.printStackTrace();
							}
						}
						if (byteArrayOutputStream != null) {
							try {
								byteArrayOutputStream.close();
							} catch (Exception e2) {
								e2.printStackTrace();
							}
						}
					}
					stringBuilder.append(TextUtils.isEmpty(content) ? ""
							: content);
				}
				return stringBuilder.toString().substring(0,
						stringBuilder.toString().lastIndexOf("|"));
			}

			@Override
			protected void onPostExecute(String result) {
			}
		}.execute();
	}

	
	public static void toBuyProp(String userId, String cmccpayCode,
			String unipayCode,String alipayCode, int num) {}

	public static class CandyHandler extends Handler {
		WeakReference<c_game_candy> candy = null;
		public CandyHandler(c_game_candy object) {
			candy = new WeakReference<c_game_candy>(object);
		}
		@Override
		public void handleMessage(Message msg) {
			if (msg==null||"".equals(msg)) {
				Toast.makeText(instance, "超时处理.", Toast.LENGTH_SHORT).show();
				candy.get().c_progress_circle.dismiss();
				return;
			}
		}
	}
	@Override
	protected void onResume() {
		super.onResume();
		UMGameAgent.onResume(this);
		
		if (c_progress_circle!=null) {
			c_progress_circle.dismiss();
		}
		Thread resumeThread = new Thread(new Runnable() {
			@Override
			public void run() {
				if (installFlag!=0) {
					if (installFlag++>8) {
						installFlag = -2;
			            JavaCallCpp.userNoInstallFile();
					}else if (installFlag>5&&installFlag<7) {
						installFlag = -2;
					}
				}
				return;
			}
		});
		resumeThread.start();
		resumeThread.interrupt();
		pushToPreference(0,"push_message");
		pushToPreference(0,"push_life");
		chat_activity=false;
	}
	
	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		super.onRestoreInstanceState(savedInstanceState);
		chat_activity=false;
	}

	@Override
	protected void onPause() {
		super.onPause();
		UMGameAgent.onPause(this);
		from_service_life();
	}
	


	/**
	 * 当用户退出游戏界面的时候，启动消息推送service
	 */
	private void from_service_life() {
		if (!chat_activity) {
			android.content.ContentResolver cv = this.getContentResolver();
			String strTimeFormat = android.provider.Settings.System.getString(
					cv, android.provider.Settings.System.TIME_12_24);
			SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");
			Date curDate = new Date(System.currentTimeMillis());// 获取当前时间
			String str = formatter.format(curDate);
			String[] dates = str.split(":");
			GregorianCalendar ca = new GregorianCalendar();
			if (strTimeFormat != null) {
				if (strTimeFormat.equals("24")) {
					if (Integer.parseInt(dates[0]) >= 8
							&& Integer.parseInt(dates[0]) < 23) {
						if (null!=messageIntent) {
							c_game_candy.this.startService(messageIntent);
						}
						push_life_flag();
					}
				} else if (strTimeFormat.equals("12")) {
					if ((Integer.parseInt(dates[0]) >= 8 && ca
							.get(GregorianCalendar.AM_PM) == 0)
							|| (Integer.parseInt(dates[0]) < 11 && ca
									.get(GregorianCalendar.AM_PM) == 1)) {
						if (null!=messageIntent) {
							c_game_candy.this.startService(messageIntent);
						}
						push_life_flag();
					}
				}
			} else {
				if (Integer.parseInt(dates[0]) >= 8
						&& Integer.parseInt(dates[0]) < 23) {
					if (null!=messageIntent) {
						c_game_candy.this.startService(messageIntent);
					}
					push_life_flag();
				}
			}
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		
		//SDK已经退出，此处可处理游戏的退出代码
		android.os.Process.killProcess(android.os.Process.myPid());
	}


	/**
	 * 获取生命值判断是否要进行推送
	 */
	public void push_life_flag() {
	}
    
	/**
	 * @author leaf
	 */
	public static c_game_candy getintance() {
		return instance;
	}

	/**
	 * @param orderid
	 *            订单编号
	 */
	public void toUnipay(String orderid) {}

	private PackageInfo getMyPackageInfo(Context context) {
		PackageInfo packageInfo = null;
		try {
			packageInfo = context.getPackageManager().getPackageInfo(
					context.getPackageName(), 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return packageInfo;
	}

	/**
	 * 用来判断服务是否运行.
	 * 
	 * @param context
	 * @param className 判断的服务名字
	 * @return true 在运行 false 不在运行
	 */
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

	public static void lifeToPreference(String new_life_number){
	}
	

	/**
	 * 把消息推送的次数保存到本地
	 * @param new_push_number 
	 * @param str_key 保存的键
	 */
	public static void pushToPreference(int new_push_number,String str_key){
	}


	
	private static SimpleDateFormat simpleDateFormat;
	
	/**
	 * 调用统计点
	 * @param register 0为登陆 1为注册
	 * @param user_Id 
	 */
	public static void registerOrLoginTrack(int register , String user_Id){
		simpleDateFormat = new SimpleDateFormat("yyyyMMddHHmmss");
		StringBuilder stringBuilder = new StringBuilder();
		if(register == 1){
			//注册是调用
			stringBuilder.append(user_Id+"^1312^"+deviceId+"^"+user_Id+"^^^|");
			stringBuilder.append(user_Id+"^1313^"+deviceId+"^"+deviceId+"^^^|");
			stringBuilder.append(user_Id+"^1314^"+deviceId+"^"+signature+"^^^|");
			stringBuilder.append(user_Id+"^1315^"+deviceId+"^"+versionName+"^^^|");
			stringBuilder.append(user_Id+"^1316^"+deviceId+"^"+simpleDateFormat.format(new Date(System.currentTimeMillis()))+"^^^");
		}else{
			//每次登陆的时候
			stringBuilder.append(user_Id+"^1317^"+deviceId+"^"+c_comm_helper.getNetType(instance)+"^^^|");
			stringBuilder.append(user_Id+"^1318^"+deviceId+"^"+simpleDateFormat.format(new Date(System.currentTimeMillis()))+"^^^|");
			stringBuilder.append(user_Id+"^1319^"+deviceId+"^"+c_comm_helper.getInetAddress(instance)+"^"+signature+"^"+versionName+"^|");
			stringBuilder.append(user_Id+"^1320^"+deviceId+"^"+Build.MANUFACTURER+Build.MODEL+"^^^");
		}
			CppCallJava.patchTracker(stringBuilder.toString());
	}
	
	int installFlag=0;
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode==8989) {
			installFlag = 8;
			return;
		}
		super.onActivityResult(requestCode, resultCode, data);
	}
	
	
	/**
	 * 移动MM sdk 相关函数
	 */
	
	//移动MM初始化函数
	private void SDKinit(){
		//初始化无回调调用方法
//		Log.e("/////1111", "1111");
//		SFCommonSDKInterface.onInit(this);		
//		Log.e("/////2222", "2222");
//		SFNativeAdapter.init(this, new SFActionCallback() {
//			
//			@Override
//			public void callback(Runnable run) {
//				runOnGLThread(run);
//				Log.e("/////3333", "3333");
//			}
//		});
	}
	
	public static long lastBuyTime;
	
	//购买订单
	public static void BuyProduct( final String paycodeIdx, String Userdata, int num) {
		if(System.currentTimeMillis() - lastBuyTime >= 0){
			try {
//				SFCommonSDKInterface.pay(instance, paycodeIdx, new SFIPayResultListener() {
//					@Override
//					public void onCanceled(String arg0) {
//						//取消购买
//						instance.buyFailed();
//					}
//					@Override
//					public void onFailed(String arg0) {
//						//购买失败
//						instance.buyFailed();
//					}
//					@Override
//					public void onSuccess(String arg0) {
//						//购买成功
//						instance.buySuccess();
//					}
//					});
			} catch (Exception e) {
				e.printStackTrace();
			}
		}else{
			instance.runOnUiThread(new Runnable() {
				@Override
				public void run() {
				}
			});
		}
	}
	
	public void dismissProgressDialog() {
		// TODO Auto-generated method stub
	}
	
	
	
	
	
}
