package org.weme.candy.comm;

import org.weme.candy.data.bean.c_constant_bean;

public class c_logout {
	public static void log(String what, String content){
		if(c_constant_bean.LOG_SWITCH)
			System.out.println("=========="+what+"=========="+content);
	}
}
