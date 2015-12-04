#ifndef WIN32
#include "org_weme_candy_util_CandyPay.h"
#include "..\CandyPay\CandyPay.h"

char* jstringTostring(JNIEnv* env, jstring jstr) 
{ 
	char* rtn = NULL;
	if(!jstr)
		return NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{ 
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	} 
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_CandyPay_PaySuccess( JNIEnv * env, jclass, jstring j_str)
{
	//从服务器更新道具
	char* str = jstringTostring(env,j_str);

	CandyPay::getInstance()->UpdateProp(str);
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_CandyPay_PayFailed( JNIEnv *env, jclass )
{
	CandyPay::getInstance()->CandyPayFailed();
}
#endif

