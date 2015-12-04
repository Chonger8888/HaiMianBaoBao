#ifndef WIN32

#include "cocos2d.h"
#include "JavaCallCpp.h"
#include "../Loading/LoadingScene.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../CommonData/CommonData.h"
USING_NS_CC;

extern "C"
{
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

	JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_GetUserInfo
		(JNIEnv *env, jclass thiz, jint status,  jstring jsonData)
	{
#if 1
		char *u = jstringTostring(env, jsonData);

		if(AnalyseJson::setUserFriendInfoMsg(u))
		{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			MsgMgr::sendLogOnMsg( (char *)AnalyseJson::friendInfoMsg.myIdx.c_str() );
			CCLog( " Java_org_weme_candy_util_JavaCallCpp_GetUserInfo  Myidx [%s]", AnalyseJson::friendInfoMsg.myIdx.c_str());
#endif
		}
		else
		{

		}
		free(u);
#endif
	}

	JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_passNoCandyUserInfo
		(JNIEnv *env, jclass thiz, jstring jsonData)
	{
		char *u = jstringTostring(env, jsonData);

		if(AnalyseJson::setForNoFriendInfoMsg(u))
		{
			MainMapUiLayer::m_mainmapuilayer->setAsynFlag( true );
		}
		else
		{

		}
		free(u);
	}

	//　java调用　登录入口
	JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_passIDs
		(JNIEnv *env, jclass thiz,jstring  devicesId, jstring userId, jstring versionname, jstring channel)   
	{
		char *pDevices = jstringTostring(env, devicesId);
		char *pUser = jstringTostring(env, userId);
		char *pverName = jstringTostring(env, versionname);
		char *pchannel = jstringTostring(env, channel);

		CCLog( "Java_org_weme_candy_util_passIDs  userId[%s] versionname[%s] devicesId[%s] channel[%s]",pUser ,pverName ,pDevices ,pchannel);

		if ( strlen(pDevices) && strlen(pUser) && strlen(pverName) && strlen(pchannel) )
		{
			AnalyseJson::SaveDeviceAndUid( pDevices, pUser ,pverName, pchannel);

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//	Loading::m_loading->initMainMapRes();
#endif
		}

		free( pDevices );
		free( pUser );
		free( pverName );
		free( pchannel );
	}


	// will remove
#include "../PlayGame/CandyManager.h"
#include "../MainMap/MainMapScene.h"
#if defined( DEMO_FOR_MOBILE)|| defined(DEMO_FOR_GUEST)
	JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_passCMCCPayResult
		(JNIEnv *env, jclass thiz,jstring  result, jstring  propid )
	{
		char *pResult = jstringTostring(env, result);
		char *pPropID = jstringTostring(env, propid);
		int nResult = atoi( pResult );

		UIButton *pBuyButton = dynamic_cast<UIButton*>(CommonWidgt::PropWidgetLayout->PropInfoLayout->getChildByName("prop_butbuy"));
		pBuyButton->setTouchEnabled(true);

		CCLog("Java_org_weme_candy_util_JavaCallCpp_passCMCCPayResult nResult[%d] prid[%s] gamestate[%d]", nResult, pPropID, CandyManager::getInstance()->resultMgr->gamestate);
		 // 0:失败  1：成功   2：返回
		if (0 == nResult || 2 == nResult)
			return;

		if ( 0 == strcmp( pPropID, MOBILE_PROP1_ID ) )
		{
			CommonData::m_isBuyLife = true;
		}
		else if((0 == strcmp( pPropID, MOBILE_PROP2_ID ))||(0 == strcmp( pPropID, MOBILE_PROP3_ID ))||(0 == strcmp( pPropID, MOBILE_PROP4_ID )))
		{
			MsgMgr::sendBuyPropMsg(AnalyseJson::logOnMsg.baseInfo.id, CommonWidgt::PropWidgetLayout->propid );
			CommonData::m_buyState = true;
		}
		else if((0 == strcmp( pPropID, MOBILE_PROP5_ID ))||(0 == strcmp( pPropID, MOBILE_PROP6_ID ))||(0 == strcmp( pPropID, MOBILE_PROP7_ID )))
		{

			if((0 == strcmp( pPropID, MOBILE_PROP5_ID )) && GAME_STATE_FAIL == CandyManager::getInstance()->resultMgr->gamestate)
			{
				CCLog( " Java_org_weme_candy_util_JavaCallCpp_passCMCCPayResult  useProp 5");

				list<UserPropInfoStr >::iterator iter;
				for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
				{
					if(iter->id == 5)
						iter->num += 1;
				}
				CandyManager::getInstance()->resultMgr->gamestate = GAME_STATE_SUCCEE;
				MsgMgr::sendConsumePropMsg(AnalyseJson::logOnMsg.baseInfo.id, 5, 1);
				CandyManager::getInstance()->uiLayer->useProp(5);
			}
			else
			{
				//在这里向服务器更新道具信息
				MsgMgr::sendBuyPropMsg(AnalyseJson::logOnMsg.baseInfo.id, CommonWidgt::PropWidgetLayout->propid );
			}

			CommonData::m_buyState = true;
			CandyManager::getInstance()->uiLayer->QuitPropWidget();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
		}
		else if((0 == strcmp( pPropID, MOBILE_PROP8_ID ))||(0 == strcmp( pPropID, MOBILE_PROP9_ID ))||(0 == strcmp( pPropID, MOBILE_PROP10_ID )))
		{
			//MsgMgr::sendBuyPropMsg(AnalyseJson::logOnMsg.baseInfo.id, CommonWidgt::PropWidgetLayout->propid );
			CommonData::m_buyState = true;
		}
		free( pResult );
		free( pPropID );
	}


JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_passBuyResult(JNIEnv *env, jclass thiz,jstring  result, jstring  propid )
	{
		CCLog("JAVA CALL C begin");
		char *pResult = jstringTostring(env, result);
		char *pPropID = jstringTostring(env, propid);
		int nResult = atoi( pResult );

		if ( CommonWidgt::PropWidgetLayout && CommonWidgt::PropWidgetLayout->PropInfoLayout)
		{
			UIButton *pBuyButton = dynamic_cast<UIButton*>(CommonWidgt::PropWidgetLayout->PropInfoLayout->getChildByName("prop_butbuy"));
			pBuyButton->setTouchEnabled(true);

		}

		CCLog("Java_org_weme_candy_util_JavaCallCpp_passBuyResult nResult[%d] pPropID[%s] Buytype[%d]", nResult, pPropID, CommonData::m_buytype);
		// 0:失败  1：成功   2：返回
		if (0 == nResult || 2 == nResult )
		{
			CommonData::m_buyMutipropNum = 0;

			if(CANDY_PROP_IN_STEP5 == CommonData::m_buytype && GAME_STATE_FAIL == CandyManager::getInstance()->resultMgr->gamestate)
			{
				CCLog("buy step5 failed call setCurrentResult()");
				CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_LOST_EFFECT);
			}
			return;
		}
				
			
		if( (0 == strcmp( pPropID, CMCC_MINI_PROP_5LIFE ))||(0 == strcmp( pPropID, CMCC_MINI_PROP_RESORT ))||(0 == strcmp( pPropID, CMCC_MINI_PROP_HAMER ))||
			(0 == strcmp( pPropID, CMCC_MINI_PROP_SWAP ))||(0 == strcmp( pPropID, CMCC_MINI_PROP_COLORFULL ))||(0 == strcmp( pPropID, CMCC_MINI_PROP_BOMBNEW ))||
			(0 == strcmp( pPropID, CMCC_MINI_PROP_STEP5 ))||(0 == strcmp( pPropID, CMCC_BUY_GIFTBIG_8_ID ))||(0 == strcmp( pPropID, CMCC_BUY_GIFTBIG_28_ID ))||
			(0 == strcmp( pPropID, UNICOM_BUYGEM_3_TO_30_ID ))||(0 == strcmp( pPropID, UNICOM_BUYGEM_5_TO_50_ID ))||
			(0 == strcmp( pPropID, UNICOM_BUYGEM_8_TO_80_ID ))||(0 == strcmp( pPropID, UNICOM_BUYGEM_10_TO_100_ID ))||(0 == strcmp( pPropID, UNICOM_BUYGEM_20_TO_200_ID ))||
			(0 == strcmp( pPropID, UNICOM_BUYGEM_30_TO_320_ID ))||(0 == strcmp( pPropID, ALIPAY_BUYGEM_588_ID ))||(0 == strcmp( pPropID, ALIPAY_BUYGEM_1288_ID ))||
			(0 == strcmp( pPropID, ALIPAY_BUYGEM_2588_ID ))	||(0 == strcmp( pPropID, CMCC_BUY_GIFTBIG_8_ID ))	|| (0 == strcmp( pPropID, CMCC_BUY_GIFTBIG_18_ID ))||
			(0 == strcmp( pPropID, CMCC_BUY_GIFTBIG_28_ID ))||(0 == strcmp( pPropID, UNICOM_BUY_GIFTBIG_8_ID ))	|| (0 == strcmp( pPropID, UNICOM_BUY_GIFTBIG_18_ID ))||
			(0 == strcmp( pPropID, UNICOM_BUY_GIFTBIG_28_ID )))
		{
			if (0 == CommonData::m_buytype) CommonData::m_buyGemState= true;
			//	CommonData::m_isBuyLife = true;

			CCLog("Java_org_weme_candy_util_JavaCallCpp_passBuyResult %d",CommonData::m_buytype);
			MsgMgr::sendUpdateGem( AnalyseJson::logOnMsg.baseInfo.id ,CommonData::m_buytype);
		}
		else if(0 == strcmp( pPropID, CMCC_MINI_PROP_SUPERGIFT ))
		{
			//超级大礼包购买成功处理
			//从网络读取道具数量,之后更新显示
			CCLog("libao huidiao");
			MsgMgr::sendGemBuyPackage(AnalyseJson::logOnMsg.baseInfo.id,AnalyseJson::logOnMsg.baseInfo.SuperGiftId);
		}

		free( pResult );
		free( pPropID );
	}

	JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_getCMCCInfo
		(JNIEnv *env, jclass thiz)
	{
		char* cmccdata = (char*)CCString::createWithFormat("%s %s",APPID_FORCMCC, APPKEY_FORCMCC )->getCString();
		static jstring  jstr_cmccdata = env->NewStringUTF(cmccdata); 
		CCLog( " Java_org_weme_candy_util_getCMCCInfo  cmccdata [%s]", cmccdata);

		return jstr_cmccdata;
	}

	JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_getUnipayInfo
		(JNIEnv *env, jclass thiz)
	{
		char* unicomdata = (char*)CCString::createWithFormat("%s %s %s",APPID_FORUNICOM, APPKEY_FORUNICPCODE, APPKEY_FORUNICPID)->getCString();
		static jstring  jstr_unicomdata = env->NewStringUTF(unicomdata); 
		CCLog( " Java_org_weme_candy_util_getCMCCInfo  cmccdata [%s]", unicomdata);

		return jstr_unicomdata;
	}
#endif

#if defined( DEMO_FOR_GUEST)

	JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_homeKeyPressed
		(JNIEnv *env, jclass thiz)
	{
		CCLog( "Java_org_weme_candy_util_JavaCallCpp_homeKeyPressed" );
		
		std::string nSendData;
		
		AnalyseJson::setRecordHeadMsg(RECODING_MSG_ACTIONID_4);
		AnalyseJson::setRecordMsgAppend((char*)CCString::createWithFormat("%d",AnalyseJson::logOnMsg.lifeInfo.lifeNum)->getCString());
		nSendData.append( (char*)AnalyseJson::Recordingdata.c_str() );
		
		if ( 0 == AnalyseJson::logOnMsg.stageInfo.size())
		{
			nSendData.append( "|" );
			AnalyseJson::setRecordHeadMsg(RECODING_MSG_ACTIONID_6);
			AnalyseJson::setRecordMsgAppend((char*)CCString::createWithFormat("%d",1)->getCString());
			nSendData.append( (char*)AnalyseJson::Recordingdata.c_str() );
		}
		if ( CommonData::getPlayGame() )
		{
			nSendData.append( "|" );
			AnalyseJson::setRecordHeadMsg(RECODING_MSG_ACTIONID_7);
			AnalyseJson::setRecordMsgAppend((char*)CCString::createWithFormat("%d",1)->getCString());
			nSendData.append( (char*)AnalyseJson::Recordingdata.c_str() );
		}
		nSendData.append( "|" );
#ifdef CANDY_STATISITICAL_DATA
		CommonData::sendLevelFaildCount(false);
#endif
		nSendData.append( (char*)AnalyseJson::Recordingdata.c_str() );

		CCLog( "Java_org_weme_candy_util_JavaCallCpp_homeKeyPressed, jstr_data[%s] ", (char*)nSendData.c_str() );
		static jstring  jstr_data = env->NewStringUTF( (char*)nSendData.c_str() ); 
		return jstr_data;
	}

#endif

JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_getNickName(JNIEnv *env, jclass thiz)
{
	CCLog( "Java_org_weme_candy_util_JavaCallCpp_GetNickName start" );
	const char* nickName =  AnalyseJson::logOnMsg.baseInfo.nickName.c_str();
	static jstring  jstr_nickname = env->NewStringUTF(nickName); 
	CCLog( "Java_org_weme_candy_util_JavaCallCpp_GetNickName nickName %s", nickName);
	return jstr_nickname;
	
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_NoticeMessage(JNIEnv *env, jclass thiz)
{
	CCLog( "Java_org_weme_candy_util_JavaCallCpp_NoticeMessage" );
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_showMessageView(JNIEnv *env, jclass thiz)
{
	CCLog( "Java_org_weme_candy_util_JavaCallCpp_showMessageView" );
	
// 	if ( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
// 	{
// 	//	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_MESSAGE_LIST );
// 	}
}

JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_getalipayInfo
	(JNIEnv *env, jclass thiz)
{
	char* alipaydata = (char*)CCString::createWithFormat("%s %s %s %s" ,ALIPAY_DEFAULT_PARTNER, ALIPAY_DEFAULT_SELLER,ALIPAY_PRIVATE, ALIPAY_PUBLIC)->getCString();
	static jstring  jstr_alipaydata = env->NewStringUTF(alipaydata); 
	CCLog( " Java_org_weme_candy_util_getalipayInfo  cmccdata [%s]", alipaydata);

	return jstr_alipaydata;
}


JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_showHeadImage(JNIEnv *env, jclass thiz, jint  result )
{
	int result_int = result;
 	if(MainMapUiLayer::m_mainmapuilayer->changeinfoLayout)
 	{
		if(result_int == 0)
		{
			CommonData::m_ModifiedHeadPhoto = true;
			MainMapUiLayer::m_mainmapuilayer->schedule(schedule_selector(MainMapUiLayer::updateHead), 3.0f);
		}
		UIImageView *pHead = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->changeinfoLayout->getChildByName("selectheadico_1"));

		if(pHead)
		{
			pHead->setTouchEnabled(true);
		}
 	}
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_shareFlag(JNIEnv *env, jclass thiz, jint  result )
{
	int result_int = result;
	if(CandyManager::getInstance()->resultMgr->getResultLayer()->gemeResortRankLayout)
	{
		UIButton *pBtn = dynamic_cast<UIButton*>(CandyManager::getInstance()->resultMgr->getResultLayer()->gemeResortRankLayout->getChildByName("share_button"));
		if(pBtn)
		{
			if(result_int == 0)
			{
				pBtn->setTouchEnable(true);
			}
			else
			{
				CandyManager::getInstance()->resultMgr->getResultLayer()->TurnToGameWinLayoutByJava();
			}
		}
	}
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_uploadFlag(JNIEnv *env, jclass thiz, jint result )
{
	CCLog("Java_org_weme_candy_util_JavaCallCpp_uploadFlag start");
	int result_int = result;
	if(result_int == 0)
	{
		CCLog("result:%d",result_int);
		if(MainMapUiLayer::m_mainmapuilayer)
		{
			CCLog("m_mainmapuilayer start");
			MainMapUiLayer::m_mainmapuilayer->m_isShowMessage = true;
		}
	}
	CCLog("Java_org_weme_candy_util_JavaCallCpp_uploadFlag end");
}

JNIEXPORT void JNICALL Java_org_weme_candy_util_JavaCallCpp_userNoInstallFile(JNIEnv *env, jclass thiz )
{
	CCLog("Java_org_weme_candy_util_JavaCallCpp_userNoInstallFile start");
	MsgMgr::SendSoundOutLogin( AnalyseJson::logOnMsg.baseInfo.idx.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str() );
}

JNIEXPORT jstring JNICALL Java_org_weme_candy_util_JavaCallCpp_otherpayToAlipay(JNIEnv *env, jclass thiz, jint result )
{
	CCLog("Java_org_weme_candy_util_JavaCallCpp_otherpayToAlipay");
	char* alipaydata = NULL;
	char *comdata = (char*)CCString::createWithFormat("%d %d %d", CommonData::m_buytype, CommonData::getMaxLevel(), AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();
	switch( result )
	{
	case CANDY_BUYGEM_NUM_10:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_10_ID, "1", "1","10", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_20:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_20_ID, "1", "2","20", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_30:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_30_ID, "1", "3","30", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_50:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_50_ID, "1", "5","50", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_80:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_80_ID, "1", "8","80", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_100:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_100_ID, "1", "10","100", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_200:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_200_ID, "1", "20","200", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_320:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_320_ID, "1", "32","320", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_588:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_588_ID, "1", "50","588", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_1288:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_1288_ID, "1", "100","1288", comdata )->getCString();
		break;
	case CANDY_BUYGEM_NUM_2588:
		alipaydata = (char*)CCString::createWithFormat("%s %s %s %s %s",ALIPAY_BUYGEM_2588_ID, "1", "200","2588", comdata )->getCString();
		break;
	}
	CCLog("Java_org_weme_candy_util_JavaCallCpp_otherpayToAlipay paycode[%s]", alipaydata );

	//static jstring  jstr_alipaydata = env->NewStringUTF(alipaydata); 

	return env->NewStringUTF(alipaydata);
}

}
#endif
