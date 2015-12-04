#include "CppCallJava.h"
#include "../Loading/LoadingScene.h"
#include "../CommonData/CommonData.h"
#include "../PlayGame/CandyManager.h"
#ifndef WIN32
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

// unipropid2 :vac支付vacCode，第三方支付customCode，支付金额（单位元），宝石数量
///*const char* cmccpropid,const char* vacCode,const char* customCode, char* price, char* gemnum,*/
void CppCallJava::toBuyProp(int buytype, int num, int preciousid)
{
	return;
	//kkpay版本支付
#if defined( KK_PAY_VERSION)
	if (AnalyseJson::logOnMsg.baseInfo.openkkSdk == 0)
	{
		return;
	}
	char* ret = NULL;
	char* unicomdata = NULL;
	char* cmccdata = NULL;
	char* alipaydata = NULL;

	char* userid = const_cast<char*>(CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.id )->getCString());
	char* propAccount = "";	//价格（分）
	char* orderdesc = "0";
	char* paycode = "";
	char* propid = const_cast<char*>(CCString::createWithFormat("%d", CommonData::m_buytype )->getCString());
	char* points = const_cast<char*>(CCString::createWithFormat("%d", CommonData::getMaxLevel() )->getCString());
	char* lifes = const_cast<char*>(CCString::createWithFormat("%d", AnalyseJson::logOnMsg.lifeInfo.lifeNum)->getCString());
	
	switch( buytype )
	{
	case CANDY_BUYGEM_NUM_50:
		{
			//mini版本生命购买
			propAccount = "500";
			paycode = CMCC_MINI_PROP_5LIFE;
		}
		break;
	case CANDY_BUYGEM_NUM_60:
		{ 
			//mini版本新增,判断5个道具的计费点
			propAccount = "500";
			if (CommonData::m_buytype == CANDY_PROP_OUT_COLORFULL)
			{
				paycode = CMCC_MINI_PROP_COLORFULL;
			}
			else if (CommonData::m_buytype == CANDY_PROP_OUT_BOMBNEW)
			{
				paycode = CMCC_MINI_PROP_BOMBNEW;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_RESORT)
			{
				paycode = CMCC_MINI_PROP_RESORT;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_SWAP)
			{
				paycode = CMCC_MINI_PROP_SWAP;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_HAMMER)
			{
				paycode = CMCC_MINI_PROP_HAMER;
			}
		}
		break;
	case CANDY_BUY_GIFTBIG_NUM_8:
		{
			//大礼包
			propAccount = "1000";
			paycode = CMCC_BUY_GIFTBIG_8_ID;
		}
		break;
	case CANDY_BUYGEM_NUM_80:
		{
			//加5步
			propAccount = "500";
			paycode = CMCC_MINI_PROP_STEP5;
		}
		break;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)|| defined ( CANDY_VERSIONS_FOR_SINGLE )

	CommonData::m_buyState = false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;

	CommonData::m_buyGemState = false;
	CommonData::m_buyState = false;
	if(	JniHelper::getStaticMethodInfo(
		methodInfo, 
		"org/weme/candy/util/CppCallJava", 
		"kkPay", 
		"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
		))
	{
		CCLog("CppCallJava::kkPay" );

		const char* pUserid = CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.id )->getCString();
		jstring  l_stringuseid = methodInfo.env->NewStringUTF( pUserid ); 
		jstring  l_propAccount = methodInfo.env->NewStringUTF( propAccount ); 
		jstring  l_orderdesc = methodInfo.env->NewStringUTF( orderdesc ); 
		jstring  l_paycode = methodInfo.env->NewStringUTF( paycode ); 
		jstring  l_propid = methodInfo.env->NewStringUTF( propid ); 
		jstring  l_points = methodInfo.env->NewStringUTF( points ); 
		jstring  l_lifes = methodInfo.env->NewStringUTF( lifes ); 

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
			l_stringuseid,
			l_propAccount,
			l_orderdesc,
			l_paycode,
			l_propid,
			l_points,
			l_lifes
			);
		methodInfo.env->DeleteLocalRef(l_stringuseid); 
		methodInfo.env->DeleteLocalRef(l_propAccount); 
		methodInfo.env->DeleteLocalRef(l_orderdesc); 
		methodInfo.env->DeleteLocalRef(l_propid); 
		methodInfo.env->DeleteLocalRef(l_paycode); 
		methodInfo.env->DeleteLocalRef(l_points); 
		methodInfo.env->DeleteLocalRef(l_lifes); 
		methodInfo.env->DeleteLocalRef(methodInfo.classID);    

		CCLog("jni:org/weme/candy/util/CppCallJava--kkPay");
	}
	else
	{
#ifdef ANDROIDHELPER_USE_CCLOG
		CCLog("jni:org/weme/candy/util/CppCallJava--kkPay is not exist.");
#endif
	}
	
#endif
	return;
	
	 

#else
	//cmcc支付
	char* ret = NULL;
	char* unicomdata = NULL;
	char* cmccdata = NULL;
	char* alipaydata = NULL;
	CCLog("get baseinfo 111");
	char *comdata = (char*)CCString::createWithFormat("%d %d %d", CommonData::m_buytype, CommonData::getMaxLevel(), AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();
	CCLog("get baseinfo 222 buytype = %d",buytype);
	switch( buytype )
	{
	case CANDY_BUYGEM_NUM_10:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_1_TO_10_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_1_TO_10_ID, UNICOM_OTHE_BUYGEM_1_TO_10_ID, "1","10", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_20:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_2_TO_20_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_2_TO_20_ID, UNICOM_OTHE_BUYGEM_2_TO_20_ID, "2","20", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_30:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_3_TO_30_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_3_TO_30_ID, UNICOM_OTHE_BUYGEM_3_TO_30_ID, "3","30", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_50:
		{
			//mini版本生命购买
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_MINI_PROP_5LIFE, comdata )->getCString();
			//unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_5_TO_50_ID, UNICOM_OTHE_BUYGEM_5_TO_50_ID, "5","50", comdata )->getCString();
			unicomdata = "0";
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_60:
		{ 
			//mini版本新增,判断5个道具的计费点
			char* jifeidian = "";
			if (CommonData::m_buytype == CANDY_PROP_OUT_COLORFULL)
			{
				jifeidian = CMCC_MINI_PROP_COLORFULL;
			}
			else if (CommonData::m_buytype == CANDY_PROP_OUT_BOMBNEW)
			{
				jifeidian = CMCC_MINI_PROP_BOMBNEW;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_RESORT)
			{
				jifeidian = CMCC_MINI_PROP_RESORT;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_SWAP)
			{
				jifeidian = CMCC_MINI_PROP_SWAP;
			}
			else if (CommonData::m_buytype == CANDY_PROP_IN_HAMMER)
			{
				jifeidian = CMCC_MINI_PROP_HAMER;
			}

			cmccdata = (char*)CCString::createWithFormat("%s %s",jifeidian, comdata )->getCString();
			//unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_5_TO_50_ID, UNICOM_OTHE_BUYGEM_5_TO_50_ID, "5","50", comdata )->getCString();
			unicomdata = (char*)"0";
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_80:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_MINI_PROP_STEP5, comdata )->getCString();
			unicomdata = "0";
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_100:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_10_TO_100_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_10_TO_100_ID, UNICOM_OTHE_BUYGEM_10_TO_100_ID, "10","100", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_200:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_20_TO_200_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_20_TO_200_ID, UNICOM_OTHE_BUYGEM_20_TO_200_ID, "20","200", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_320:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUYGEM_30_TO_320_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUYGEM_30_TO_320_ID, UNICOM_OTHE_BUYGEM_30_TO_320_ID, "30","320", comdata )->getCString();
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUYGEM_NUM_588:
		{
			cmccdata = (char*)"0";
			unicomdata = (char*)"0";
			alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_588_ID, "1", "50","588", comdata )->getCString();
		}
		break;

	case CANDY_BUYGEM_NUM_1288:
		{
			cmccdata = (char*)"0";
			unicomdata = (char*)"0";
			alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_1288_ID, "1", "100","1288", comdata )->getCString();
		}
		break;

	case CANDY_BUYGEM_NUM_2588:
		{
			cmccdata = (char*)"0";
			unicomdata = (char*)"0";
			alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_2588_ID, "1", "200","2588", comdata )->getCString();
		}
		break;

		// 礼包
	case CANDY_BUY_GIFTBIG_NUM_8:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUY_GIFTBIG_8_ID, comdata )->getCString();
			unicomdata = (char*)CCString::createWithFormat("%s %s %s %s %s",UNICOM_BUY_GIFTBIG_8_ID, "1", "8", CommonData::GetString("app_giftbig1_str").c_str(), comdata )->getCString();
			alipaydata = (char*)"0";
			CCLog("-------buy gift @C++ -------");
		}
		break;

	case CANDY_BUY_GIFTBIG_NUM_18:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUY_GIFTBIG_18_ID, comdata )->getCString();
			unicomdata = "0";
			alipaydata = (char*)"0";
		}
		break;

	case CANDY_BUY_GIFTBIG_NUM_28:
		{
			cmccdata = (char*)CCString::createWithFormat("%s %s",CMCC_BUY_GIFTBIG_28_ID, comdata )->getCString();
			unicomdata = "0";
			alipaydata = (char*)"0";
		}
		break;
	}
	CCLog("CppCallJava::toBuyProp==> unicomdata[%s] cmccdata[%s] num[%d] prop[%d]", unicomdata,cmccdata, num, CommonData::m_buytype );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)|| defined ( CANDY_VERSIONS_FOR_SINGLE )

	CommonData::m_buyState = false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;

	CommonData::m_buyGemState = false;
	CommonData::m_buyState = false;
	if(	JniHelper::getStaticMethodInfo(
		methodInfo, 
		"org/weme/candy/util/CppCallJava", 
		"toBuyProp", 
		"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"
		))
	{
		CCLog("CppCallJava::toBuyProp" );

		const char* pUserid = CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.id )->getCString();
		jstring  l_stringcmccpid = methodInfo.env->NewStringUTF(cmccdata); 
		jstring  l_stringuseid = methodInfo.env->NewStringUTF( pUserid ); 
		jstring  l_stringundata = methodInfo.env->NewStringUTF(unicomdata ); 
		jstring  l_stringalipaydata = methodInfo.env->NewStringUTF(alipaydata ); 
		jint  l_stringnum = num;

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
			l_stringuseid,
			l_stringcmccpid,
			l_stringundata,
			l_stringalipaydata,
			l_stringnum
			);
		methodInfo.env->DeleteLocalRef(l_stringuseid); 
		methodInfo.env->DeleteLocalRef(l_stringcmccpid); 
		methodInfo.env->DeleteLocalRef(l_stringundata); 
		methodInfo.env->DeleteLocalRef(l_stringalipaydata); 
		methodInfo.env->DeleteLocalRef(methodInfo.classID);    

		CCLog("jni:org/weme/candy/util/CppCallJava--toBuyProp");
	}
	else
	{
#ifdef ANDROIDHELPER_USE_CCLOG
		CCLog("jni:org/weme/candy/util/CppCallJava--toBuyProp is not exist.");
#endif
	}
#endif
#endif
	
	
#ifdef CANDY_STATISITICAL_DATA
	//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4016, CCString::createWithFormat("%d", CommonData::m_buytype)->getCString() );
#endif


}
 void CppCallJava::BuyProduct( int productId )
 {
	 int uid = AnalyseJson::logOnMsg.baseInfo.id;
	 std::string funcName = "BuyProduct";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 JniMethodInfo methodInfo;

	 CommonData::m_buyGemState = false;
	 CommonData::m_buyState = false;
	 
	 bool isExist = JniHelper::getStaticMethodInfo(
		 methodInfo, 
		 "org/weme/candy/util/CppCallJava", 
		 funcName.c_str(), 
		 "(II)V"
		 );
	 if(isExist)	
	 {
		 methodInfo.env->CallStaticVoidMethod(
			 methodInfo.classID, 
			 methodInfo.methodID,
			 uid,
			 productId
			 );
		
		 methodInfo.env->DeleteLocalRef(methodInfo.classID);    
		 CCLog("CppCallJava:: %s success",funcName.c_str() );
		 return;
	 }
	CCLog("---------jni:call func %s failed------",funcName.c_str());
#endif
 }

 long CppCallJava::getUserId( void )
 {
	 long Uid = 0;
	 std::string funcName = "getUserId";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 JniMethodInfo methodInfo;

	 CommonData::m_buyGemState = false;
	 CommonData::m_buyState = false;

	 bool isExist = JniHelper::getStaticMethodInfo(
		 methodInfo, 
		 "org/weme/candy/util/CppCallJava", 
		 funcName.c_str(), 
		 "()J"
		 );
	 jlong id;
	 if(isExist)	
	 {
		id = methodInfo.env->CallStaticLongMethod(
			 methodInfo.classID, 
			 methodInfo.methodID
			 );
		Uid = id;
		methodInfo.env->DeleteLocalRef(methodInfo.classID);    
		CCLog("CppCallJava:: %s success",funcName.c_str() );
	 }
	 else
	 {
		 CCLog("---------jni:call func %s failed------",funcName.c_str());
	 }
#endif
	 CCLog("^^^^^^^^^^^^^^^^ uid = %ld",Uid);
	 return Uid;
 }


