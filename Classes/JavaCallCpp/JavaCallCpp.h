#ifndef WIN32
	#ifndef _Included_JavaCallCpp
	#define _Included_JavaCallCpp
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"

		#ifdef __cplusplus
		extern "C" {
		#endif

/*
 * Class:     JavaCallCpp
 * Method:    SetLogonResult
 * Signature: (IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
 
JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_GetUserInfo
  (JNIEnv *, jclass, jint,  jstring);

		#ifdef __cplusplus
		}
		#endif
		
	#endif
	
#endif
