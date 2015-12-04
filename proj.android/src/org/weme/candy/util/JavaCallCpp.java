package org.weme.candy.util;
public class JavaCallCpp {
	
	/**
	 * 传递设备码和用户ID
	 * @param devicesId
	 * @param userId
	 * @param versionName
	 */
	public static native void passIDs(String devicesId, String userId, String versionName ,String signature);
	
	/**
	 * 用户点击Home键
	 */
	public static native String homeKeyPressed();
	
	
	public static native String getNickName();
	
	/**
	 * 传递移动支付结果
	 * @param result true为成功，false为失败
	 * @param payCode 商品ID
	 */
	public static native void passCMCCPayResult(String result, String payCode); 
	
	/**
	 * 传递支付结果
	 * @param result 0为失败，1为成功，2为返回 
	 * @param payCode 商品ID
	 */
	public static native void passBuyResult(String result,String payCode);
	
	/**
	 * 获取支付信息
	 * @return
	 */
	public static native String getCMCCInfo();
	
	/**
	 * 获取Unipay初始化信息
	 * 获取的字符串包含几个参数。1:appid  2:cpCode  3:cpid 
	 * @return
	 */
	public static native String getUnipayInfo();
	
	/**
	 * 从支付界面回到游戏
	 */
	public static native void backToCandy();
	
	/**
	 * 显示消息对话框
	 */
	public static native void showMessageView();
	
	/**
	 *获取alipay初始化信息
	 * 获取的字符串包含几个参数。1:DEFAULT_PARTNER  2:DEFAULT_SELLER  3:PRIVATE 4:PUBLIC  
	 * @return
	 */
	public static native String getalipayInfo();
	
	/**
	 * 用户设置头像之后 通知底层修改头像
	 * @param is_ok 0代表修改头像，1为开放按钮
	 */
	public static native void showHeadImage(int is_ok);
	
	/**
	 * 图片上传完，通知底层
	 * @param flag 0是成功 1是失败
	 */
	public static native void uploadFlag(int flag);
	
	/**
	 * 用户不安装的时候回调底层，继续程序运行
	 */
	public static native void userNoInstallFile();
	
	/**
	 * 其他支付转到支付宝支付
	 * @param buyPrice 购买的单价
	 * @return
	 */
	public static native String otherpayToAlipay(int buyPrice);
	
	/**
	 * @param flag 分享结果1为成功，0为失败
	 */
	public static native void shareFlag(int flag);
}
