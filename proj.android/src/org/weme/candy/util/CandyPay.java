package org.weme.candy.util;

import org.weme.candy.activity.c_game_candy;

import android.R.integer;
import android.widget.Toast;

public class CandyPay {
	private static String msgText = null;
	
	public static native void PaySuccess(String tradeId);
	
	public static native void PayFailed();
	
	/**
     * MM购买接口
     */
    public static void BuyProduct( String paycode, String orderId, int pricepoint, int num)
    {
    	// 易接计费点
    	//c_game_candy.BuyProduct(paycode,orderId,num);
    	
    	c_game_candy.BuyProduct(paycode,"0",0);
    	
    	// 聚乐网络单机计费点
    	//c_game_candy.jniDoPay( paycode,orderId,pricepoint,num );
    	
    	//易接计费，传入计费点索引
    	
    }
	
	/**
     * 安卓提示
     */
    public static void Prompt(String text){
    	msgText = text;
    	android.os.Message msg = c_game_candy.instance.m_myhandler.obtainMessage();
		msg.what=0;
		c_game_candy.instance.m_myhandler.sendMessage(msg);
    }
    
    /**
	 *
	 * @param text
	 */
	public static void ShowPrompt(){
		Toast toast=Toast.makeText(c_game_candy.instance, msgText, Toast.LENGTH_LONG);
		toast.show();
    }
    
	/**
     * 安卓提示
     */
    public static void Prompt_Net(String text){
    	msgText = text;
    	android.os.Message msg = c_game_candy.instance.m_myhandler.obtainMessage();
		msg.what=0;
		c_game_candy.instance.m_myhandler.sendMessage(msg);
		
		
    }
    
    
    
}
