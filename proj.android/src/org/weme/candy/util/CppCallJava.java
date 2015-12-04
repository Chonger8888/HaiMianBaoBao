package org.weme.candy.util;

import java.io.File;
import java.util.HashMap;

import org.weme.candy.activity.c_game_candy;
import org.weme.candy.comm.c_application;
import org.weme.candy.comm.c_logout;
import org.weme.candy.comm.c_weme_http_candy;
import org.weme.candy.data.bean.c_constant_bean;

import android.R.integer;
import android.content.Intent;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.provider.Settings;
import android.util.Log;
import android.widget.Toast;

public class CppCallJava{

	/**
	 * 获得用户ID
	 */
	public static String getuserID(){
		return c_game_candy.getUserID();
	}
	
	/**
	 * KKPay
	 * @param userId 用户ID
	 * @param orderAccount 道具总额（分）
	 * @param orderDesc 道具ID
	 * @param popId 
	 * @param points
	 * @param lifes
	 */
	public static void kkPay(String userId, String orderAccount, String orderDesc, String payCode, String popId, String points, String lifes){
	}

	
	/**
	 * 注销
	 */
	public static void logout(){
		c_game_candy.logout();
	}
	
	/**
	 * 获取candy数据保存路径
	 * @return 例如：/mnt/sdcard/candy/
	 */
	public static String getCandyPicDir(){
		if(Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
			File candyFolder = new File(Environment.getExternalStorageDirectory().toString()+"/candy/.nomedia/");
			if(!candyFolder.exists())
				candyFolder.mkdirs();
			File candyNoFriendFoledr = new File(candyFolder.toString()+"/noFriend");
			if(!candyNoFriendFoledr.exists())
				candyNoFriendFoledr.mkdir();
			return candyFolder.toString();
		}else
			return "";
	}
	
	/**
	 * 统计
	 * @param info 封装后的字符串
	 */
	public static void patchTracker(String info){
		if(info != null && info.length() != 0){
			final HashMap<String, Object> map = new HashMap<String, Object>();
			map.put("batch_tracker", info);
			new Thread(new Runnable() {
				@Override
				public void run() {
				}
			}).start();
		}
	}
	
	/**
	 * 支付接口
	 * @param cmccpayCode  移动道具ID
	 * @param unipayCode 联通道具字符串，里面包含，vac支付vacCode，第三方支付customCode，支付金额（单位元），宝石数量
	 * @param num 数量
	 */

	public static void toBuyProp(String userId,String cmccpayCode, String unipayCode,String alipayCode,int num){
		Log.e("---------buy gift @JAVA------0------","");
	
		c_game_candy.toBuyProp(userId,cmccpayCode,unipayCode,alipayCode,num);
		Log.e("---------buy gift @JAVA------1------","");
	}
	
	
	/**
	 * 进入聊天界面
	 * @author leaf
	 */
	public static boolean enter_chat_window(){
		return false;
	}
	
	/**
	 * 获取未读消息数
	 * @return
	 */
	public static int get_message_no_read_nums(){
		return 0;
	}
	
	/**
	 * 更新用户信息
	 * @param userid 用户id
	 * @param nickname 昵称
	 * @param pic_for_user_avatar 头像地址
	 * @param gender 性别
	 * @return
	 */
	public static void update_user_info(String userid,String nickname,String pic_for_user_avatar,String gender){}
	

	
	/**
	 * 分享调用
	 */
	public static void sharetoqzone(String url){}
	
	/**
	 * 本地保存用户生命值
	 * @param new_life_number
	 */
	public static void lifeToPreference(int new_life_number){
		c_game_candy.lifeToPreference(new_life_number+"");
	}
	
	/**
	 * 获取基本信息，渠道号 idx等
	 * @return
	 */
	public static String getPlatfromInfo(){
		return "";
	};
	/**
	 * 关卡验证
	 * @param userId
	 * @param luaindex
	 */
    public static void verifyLuas(int userId , int luaindex){
    };

   /**
    * zhuohua初始化登陆
    * @param nickname 用户昵称
    * @param userId 用户id
    * @param zhLogin 是否开启聊天服务器
    */
    public static void zhuohua_init(String nickname , int userId , int zhLogin){
    }
    /**
     * 统计点
     * @param register 0为登陆 1为注册
     * @param userId
     */
    public static void registerOrLoginTrack(int register , int userId){
    	c_game_candy.registerOrLoginTrack(register , userId+"");
    }
    /**
     * 第一次注册后调用，通知zhuohua服务器修改用户nickname
     * @param deviceId 用户唯一标示
     * @param nickname 用户的昵称
     */
    public static void set_zhuohua_nickname(String deviceId,String nickname){}
    /**
     * 用户修改资料时调用设置头像
     */
    public static void set_user_head_image(){
    }
    /**
     * 用户确认修改资料后上传头像
     */
    public static void upload_head_image(){
    }
    
    /**
     * 版本更新
     */
    public static void app_update(){
    }
    /**
     * 删除本地用户的头像
     */
    public static void delete_user_image(){
    };
    /**
     * 易接获取用户ID
     */
    public static long getUserId()
    {
    	return 0;
    };
    
}




