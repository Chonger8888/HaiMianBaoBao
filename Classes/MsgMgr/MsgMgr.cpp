#include "MsgMgr.h"
#include "UrlMgr.h"
#include "AnalyseJson.h"

#include "../MsgMgr/MsgMgr.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../Loading/LoadingScene.h"
#include "../PlayGame/CandyManager.h"
#include "../CppCallJava/CppCallJava.h"

ResponseMgr MsgMgr::responseMgr;

void MsgMgr::sendMsg(char *url, SEL_HttpResponse pSelector,void *userData)
{
	return;
#ifndef CANDY_VERSIONS_FOR_SINGLE
	CCLog( "MsgMgr==>sendMsg  url:%s",  url);
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(&responseMgr, pSelector);
	request->setUserData(userData);
	CCHttpClient::getInstance()->setTimeoutForConnect(30);
	CCHttpClient::getInstance()->setTimeoutForRead(30);
	CCHttpClient::getInstance()->send(request);
	request->release();
#endif
}

void MsgMgr::SendSoundOutLogin( const char* idx, const char* channel )
{
	sendMsg( UrlMgr::getSoundOutLoginUrl( idx, channel ),
		httpresponse_selector( ResponseMgr::msgForSoundOutLogin ));
}

void MsgMgr::sendRegeditUser(const char* idx, const char* channel1, const char* channel2, const char* version)
{
	sendMsg( UrlMgr::getRegeditUser( idx, channel1 ,channel2, version),
		httpresponse_selector( ResponseMgr::msgForRegetdit ));
}


void MsgMgr::sendLogOnMsg(const char *idx)
{
	sendMsg(UrlMgr::getLogOnUrl(idx, AnalyseJson::logOnMsg.baseInfo.version.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str()),
		httpresponse_selector(ResponseMgr::msgForLogOn));
}

void MsgMgr::sendLevelScoreMsg(int userId,  int level,  int score, int candynum)
{
	sendMsg(UrlMgr::getLevelScoreUrl(userId,   level,   score, candynum),
		httpresponse_selector(ResponseMgr::msgForLevelScore));
}

void MsgMgr::sendGetFriendInfoMsg(void)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	sendMsg((char *)"http://www.weme-game.com/1.0.0/dispatch.php?v_class=0&v_cmd=3&idx=59f51fd6937412b7e56ded1ea2470c25&friend_idx=7e7e69ea3384874304911625ac34321c|b337e84de8752b27eda3a12363109e80|54229abfcfa5649e7003b83dd4755294|2838023a778dfaecdc212708f721b788|f3f27a324736617f20abbf2ffd806f6d|996a7fa078cc36c46d02f9af3bef918b|f0e52b27a7a5d6a1a87373dffa53dbe5|9cc138f8dc04cbf16240daa92d8d50e2|b2f627fff19fda463cb386442eac2b3d|274ad4786c3abca69fa097b85867d9a4|ff4d5fbbafdf976cfdc032e3bde78de5|389bc7bb1e1c2a5e7e147703232a88f6|9ab0d88431732957a618d4a469a0d4c3|912d2b1c7b2826caf99687388d2e8f7c|1579779b98ce9edb98dd85606f2c119d|1728efbda81692282ba642aafd57be3a|959a557f5f6beb411fd954f3f34b21c3|d09bf41544a3365a46c9077ebb5e35c3|3fe78a8acf5fda99de95303940a2420c|d8700cbd38cc9f30cecb34f0c195b137|69421f032498c97020180038fddb8e24|c32d9bf27a3da7ec8163957080c8628e",
		httpresponse_selector(ResponseMgr::msgForGetFriendInfo));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Loading::m_loading->HttpGetFriendListAsyn();
#endif
}

void MsgMgr::sendGetFriendForGuestMsg(int userId, int page, int limit)
{
	sendMsg(UrlMgr::getGetFriendInfoUrl(userId, page, limit),
		httpresponse_selector(ResponseMgr::msgForGetFriendInfoForGuest) );
}
void MsgMgr::sendGetWorldFriendForGuestMsg()
{
	sendMsg(UrlMgr::getGetWorldFriendInfoUrl(),
		httpresponse_selector(ResponseMgr::msgForGetWorldFriendInfoForGuest) );
}
void MsgMgr::sendGetNoFriendForGuestMsg(int userId, int page, int limit)
{
	sendMsg(UrlMgr::getGetNoFriendInfoUrl(userId, page, limit),
		httpresponse_selector(ResponseMgr::msgForGetNoFriendInfoForGuest) );
}

void MsgMgr::sendInvateFriendForGuestMsg(int myId, int invateId)
{
	sendMsg( UrlMgr::getInviteFriendForGuestUrl(myId, invateId), NULL);
}

void MsgMgr::sendGetLifePriceMsg(void)
{
	sendMsg(UrlMgr::getGetLifePriceUrl(),httpresponse_selector(ResponseMgr::msgForGetLifePrice));
}

void MsgMgr::sendBuyLifeMsg(int userId, int lifeNum, int lifePrice)
{
	sendMsg(UrlMgr::getBuyLifeUrl( userId,  lifeNum,  lifePrice),
		httpresponse_selector(ResponseMgr::msgForBuyLife));
}

void MsgMgr::sendHandselLifeMsg(int myId, int friendId)
{
	sendMsg(UrlMgr::getHandselLifeUrl(myId, friendId),
		httpresponse_selector(ResponseMgr::msgForHandselLife));
}


void MsgMgr::sendAcceptLifeMsg(int myId, int givenId, int friendId)
{
	sendMsg(UrlMgr::getAcceptLifeUrl(myId, givenId, friendId),
		httpresponse_selector(ResponseMgr::msgForAcceptLife));
}

void MsgMgr::sendConsumeLifeMsg(int myId, int num)
{
	sendMsg(UrlMgr::getConsumeLifeUrl( myId,  num),
		httpresponse_selector(ResponseMgr::msgForConsumeLife));
}
void MsgMgr::sendConnectMsg(int myId)
{
	sendMsg(UrlMgr::getConnectUrl( myId ),
		httpresponse_selector(ResponseMgr::msgForConnectUrl));
}

void MsgMgr::sendRemoveSysLifeMsg(int myId)
{
	sendMsg(UrlMgr::getRemoveSysLifeUrl( myId ),
		httpresponse_selector(ResponseMgr::msgForRemoveSysLife));
}

void MsgMgr::sendAddSysLifeMsg(int myId)
{
	sendMsg(UrlMgr::getAddSysLifeUrl(myId),
		httpresponse_selector(ResponseMgr::msgForAddSysLife));
}

void MsgMgr::sendGetPropInfoMsg(int propId)
{
	sendMsg(UrlMgr::getGetPropInfoUrl(propId),
		httpresponse_selector(ResponseMgr::msgForGetPropInfo));
}

void MsgMgr::sendBuyPropMsg(int userId, int propId)
{
	sendMsg(UrlMgr::getBuyPropUrl( userId ),
		httpresponse_selector(ResponseMgr::msgForBuyProp), (void*)propId);
}

void MsgMgr::sendMagicLampTimeRequest(int userId)
{
	sendMsg(UrlMgr::getMagicLampTimeUrl( userId ),
		httpresponse_selector(ResponseMgr::msgForMagicLampTime));
}
void MsgMgr::sendUseMagicLampTimeRequest(int userId)
{
	sendMsg(UrlMgr::getUseMagicLampUrl( userId ),
		httpresponse_selector(ResponseMgr::msgForUseMagicLamp));
}

void MsgMgr::sendEnergyNumMsg(int userId, int num)
{
	sendMsg(UrlMgr::getEnergyNumUrl( userId ,num),NULL);
}

//请求使用能量罐次数
void MsgMgr::sendEnergyUseNumMsg(int userId)
{
	sendMsg(UrlMgr::getEnergyUseNumUrl( userId),
		httpresponse_selector(ResponseMgr::msgForEnergyUseNum));

}

void MsgMgr::sendHandselPropMsg(int myId, int friendId, int propId, int propPrice, int propNum)
{
	sendMsg(UrlMgr::getHandselPropUrl( myId, friendId,  propId,  propPrice,  propNum),
		httpresponse_selector(ResponseMgr::msgForHandselProp));
}

void MsgMgr::sendGetHandselPropMsg(int userId)
{
	sendMsg(UrlMgr::getGetHandselPropUrl( userId),
		httpresponse_selector(ResponseMgr::msgForGetHandselProp));
}

void MsgMgr::sendAcceptPropMsg(int myId, int friendId, int givenId)
{
	sendMsg(UrlMgr::getAcceptPropUrl( myId, friendId, givenId),
		httpresponse_selector(ResponseMgr::msgForAcceptProp));
}

void MsgMgr::sendClaimPropMsg(int myId, int friendId, int propId, int propPrice, int propNum)
{
	sendMsg(UrlMgr::getClaimPropUrl( myId,  friendId,  propId,  propPrice,  propNum),
		httpresponse_selector(ResponseMgr::msgForClaimProp));
}

void MsgMgr::sendGetClaimedPropMsg(int userId)
{
	sendMsg(UrlMgr::getGetClaimedPropUrl( userId),
		httpresponse_selector(ResponseMgr::msgForGetClaimedProp));
}

void MsgMgr::sendAcceptClaimedPropMsg(int myId, int friendId,int claimedId)
{
	sendMsg(UrlMgr::getAcceptClaimedPropUrl(myId, friendId, claimedId),
		httpresponse_selector(ResponseMgr::msgForAcceptClaimedProp));
}

void MsgMgr::sendRefuseClaimedPropMsg(int myId, int friendId,int claimedId)
{
	sendMsg(UrlMgr::getRefuseClaimedPropUrl(myId, friendId, claimedId),
		httpresponse_selector(ResponseMgr::msgForRefuseClaimedProp));
}

void MsgMgr::sendInviteFirendMsg(char* myIdx, char* friendidx)
{
	sendMsg(UrlMgr::getInviteFriendUrl(myIdx, friendidx),
		httpresponse_selector(ResponseMgr::msgForInviteFirendMsg));	
}

void MsgMgr::sendInvateFirendMsg(int myIdx, int friendidx)
{
	sendMsg(UrlMgr::getInviteFriendForUrl(myIdx, friendidx),NULL);//12

}

void MsgMgr::sendFilterNoFriend(char* myIdx, char* nofriendidx)
{
	CCLog( "MsgMgr==>sendFilterNoFriend" );
	sendMsg(UrlMgr::getFilterNoFriendUrl(myIdx, nofriendidx),
		httpresponse_selector(ResponseMgr::msgForFilterNoFriend));
}

void MsgMgr::sendAllAcceptUserHandsel( int myId)
{
	sendMsg( UrlMgr::getAllAcceptUserHandselUrl( myId ),
		httpresponse_selector(ResponseMgr::msgForAllAcceptUserHandsel));
}

void MsgMgr::send3PartyGetNoFriendInfoMsg(char* friendidx)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	sendMsg(UrlMgr::getNoFriendInfoUrl( friendidx ),
		httpresponse_selector(ResponseMgr::msgFor3PartyGetNoFriendInfo));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//CppCallJava::loadNoCandyUserInfo( friendidx );
#endif
}

void MsgMgr::sendConsumePropMsg(int userId, int propId, int propNum)
{
	sendMsg(UrlMgr::getConsumePropUrl( userId,  propId,  propNum),
		httpresponse_selector(ResponseMgr::msgForConsumeProp));
}

void MsgMgr::sendGetUserPropMsg(int userId, int propId)
{
	sendMsg(UrlMgr::getGetUserPropUrl( userId,  propId),
		httpresponse_selector(ResponseMgr::msgForGetUserProp));
}

void MsgMgr::sendGetChatRecordMsg(int userId )
{
	sendMsg(UrlMgr::getGetChatRecordUrl( userId ),
		httpresponse_selector(ResponseMgr::msgForGetChatRecord));
}

void MsgMgr::sendGetNoticeData(void)
{
	sendMsg(UrlMgr::getNoticeDataUrl(),
		httpresponse_selector(ResponseMgr::msgForNoticeDataMsg));
}


void MsgMgr::sendGetChitchatSt(void)
{
	sendMsg(UrlMgr::getChitchatStUrl(),
		httpresponse_selector(ResponseMgr::msgForGetChitchatMsg));
}

void MsgMgr::sendGetGameState(int myid, int state)
{
	sendMsg(UrlMgr::getGameStateUrl(myid, state),
		httpresponse_selector(ResponseMgr::msgForGetGameStateMsg));
}

void MsgMgr::sendFeedbackMsg(int myId,std::string info)
{
	sendMsg( UrlMgr::getFeedbackInfoUrl(myId, info.c_str()),
		NULL);
}

void MsgMgr::sendSystemGiveProp(int myid, int propid)
{
	sendMsg( UrlMgr::getSystemGiveProp(myid, propid),
		httpresponse_selector(ResponseMgr::msgForSystemGivePropMsg));
}

void MsgMgr::sendMyInformation(int myid, int qq, int sex, char* nickname)
{
	sendMsg( UrlMgr::getMyInformationUrl(myid, qq, sex, nickname),NULL);
}

void MsgMgr::sendGetSystemHeadUrl(void)
{
	sendMsg( UrlMgr::getSystemHeadUrl(),
		httpresponse_selector(ResponseMgr::msgForGetSystemHeadUrlMsg));
}

void MsgMgr::sendGemBuyVip(int myid, int vipLevel, int vipStone)
{
	sendMsg( UrlMgr::getGemBuyVipUrl(myid, vipLevel,vipStone),
		httpresponse_selector(ResponseMgr::msgForGemBuyVip),(void*)vipLevel);
}

void MsgMgr::sendGemBuyLife(int myid, int lifenum)
{
	sendMsg( UrlMgr::getGemBuyLifeUrl(myid, lifenum),
		httpresponse_selector(ResponseMgr::msgForGemBuyLife));
}

void MsgMgr::sendGemBuyProp(int myid, int propid, int propnum, int candyType)
{
	CCLog("buy prop 2222 propid = %d, propnum = %d, candyType = %d",propid,propnum,candyType);
	sendMsg( UrlMgr::getGemBuyPropUrl(myid, propid, propnum, candyType),
		httpresponse_selector(ResponseMgr::msgForGemBuyProp), (void*)propid);
}

void MsgMgr::sendGemBuySkill(int myid)
{
	sendMsg( UrlMgr::getGemBuySkillUrl(myid),
		httpresponse_selector(ResponseMgr::msgForGemBuySkill));
}

void MsgMgr::sendGemBuyPackage(int myid, int packageid)
{
	sendMsg( UrlMgr::getGemBuyPackageUrl(myid,packageid),
		httpresponse_selector(ResponseMgr::msgForGemBuyPackage), (void*)packageid);
}

void MsgMgr::sendRewardVip(int myid)
{
	sendMsg( UrlMgr::getVipRewardUrl(myid),
		httpresponse_selector(ResponseMgr::msgForRewardVip));
}
void MsgMgr::sendUnlockLevel(int myid,int gemnum,int level)
{
	sendMsg( UrlMgr::getUnlockLevelUrl(myid,gemnum,level),
		httpresponse_selector(ResponseMgr::msgForUnlockLevel),(void *)level);
}
void MsgMgr::sendUpdateGem(int myid, int buytype)
{
	sendMsg( UrlMgr::getUpdateGemUrl(myid),
		httpresponse_selector(ResponseMgr::msgForUpdateGem), (void*)buytype);
}

void MsgMgr::sendLevelFail(int myid, int level)
{
	sendMsg( UrlMgr::getSendLevelFailUrl(myid,level),NULL);
}

// 获得赠送生命消息  消息已并到　sendgetMyAllMsgForGuest
void MsgMgr::sendGetHandselLifeMsg(int userId, int page, int limit)
{
	sendMsg(UrlMgr::getGetHandselLifeMsgUrl(userId, page, limit),
		httpresponse_selector(ResponseMgr::msgForGetHandselLife));
}

//　获得邀请好友消息　　消息已并到　 sendgetMyAllMsgForGuest
void MsgMgr::sendgetInviteFriendMsgForGuest(int userId, int page, int limit)
{
	sendMsg( UrlMgr::getgetInviteFriendMsgUrlForGuest(userId, page, limit ),
		httpresponse_selector(ResponseMgr::msgGetInviteFriendMsgForGuest));
}


void MsgMgr::sendgetMyAllMsgForGuest( int userid, int page /*= 1*/, int limit /*= 60*/ )
{
	sendMsg( UrlMgr::getMyAllMsgUrlForGuest(userid, page, limit ),
		httpresponse_selector(ResponseMgr::msgGetMyAllMsgForGuest));
}


//　同意添加好友
void MsgMgr::sendAcceptAddFriendForGuestMsg(int myId, int friendId)
{
	sendMsg( UrlMgr::getAcceptAddFriendForGuestUrl(myId, friendId),
		httpresponse_selector(ResponseMgr::msgAcceptAddFriendMsgForGuest));
}

//　删除好友
void MsgMgr::sendDelFriendForGuestMsg(int myId, int friendId)
{
	sendMsg( UrlMgr::getDelFriendForGuestUrl(myId, friendId),
		NULL);
}

//　拒绝添加好友
void MsgMgr::sendNoAcceptAddFriendForGuestMsg(int myId, int friendId)
{
	sendMsg( UrlMgr::getNoAcceptAddFriendForGuestUrl(myId, friendId),NULL);
}

//　（一键清除）
void MsgMgr::sendCleanAddFriendForGuestMsg(int myId )
{
	sendMsg( UrlMgr::getCleanAddFriendForGuestUrl(myId),NULL);
}

// 搜索好友
void MsgMgr::sendSeachFriendForGuestMsg(int userId, char*condition, int page , int limit)
{
	sendMsg( UrlMgr::getSeachFriendForGuestUrl(userId, condition ,page, limit),
		httpresponse_selector(ResponseMgr::msgSeachFriendForGuest));
}

void MsgMgr::sendGetSingleLevelResult(int userid, int level, int page, int limit)
{
	sendMsg( UrlMgr::getSingleLevelReultUrl(userid, level, page, limit),
		httpresponse_selector(ResponseMgr::msgSingleLevelResultForGuest)) ;
}
void MsgMgr::sendGetSingleLevelResultInMap(int userid, int level, int page, int limit)
{
	sendMsg( UrlMgr::getSingleLevelReultUrl(userid, level, page, limit),
		httpresponse_selector(ResponseMgr::msgSingleLevelResultForGuestInMap)) ;
}

void MsgMgr::sendRegeditChatUser( const char* nickname, const char* idx, const char* packpag )
{
	sendMsg( UrlMgr::getRegeditChatUserUrl(nickname, idx, packpag),NULL) ;
}

void MsgMgr::sendUpdataGameMsg( int ver )
{
	sendMsg( UrlMgr::getUpdataGameUrl(ver),
		httpresponse_selector(ResponseMgr::msgUpdataGameMsg)) ;
}

void MsgMgr::sendGetSystemTask( int myid )
{
	sendMsg( UrlMgr::getGetSystemTaskUrl(myid),
		httpresponse_selector(ResponseMgr::msgForGetSystemTask)) ;
}

void MsgMgr::sendSubmitTask( int myid, int taskid, int num )
{

	sendMsg( UrlMgr::getSubmitTaskUrl(myid, taskid, num),
		httpresponse_selector(ResponseMgr::msgForSubmitTask)) ;
}

void MsgMgr::sendGetRewardTask( int myid, int taskid, int starnum )
{
	sendMsg( UrlMgr::getGetRewardTaskUrl(myid, taskid, starnum),
		httpresponse_selector(ResponseMgr::msgForGetRewardTask)) ;
}

// 解锁任务
void MsgMgr::sendUnLockTask( int myid, int taskid )
{
	sendMsg( UrlMgr::getUnllockTaskUrl(myid, taskid),
		httpresponse_selector(ResponseMgr::msgForUnLockTaskMsg)) ;
}

void MsgMgr::sendBuyFriendlimitForMsg( int myId )
{
	sendMsg( UrlMgr::getBuyFriendLimitUrl( myId ),
		httpresponse_selector(ResponseMgr::msgForBuyFriendLimit)) ;
}

void MsgMgr::sendGetWorldRanked( int myid )
{
	sendMsg( UrlMgr::getWorldRankedUrl( myid ),
		httpresponse_selector(ResponseMgr::msgForGetWorldRankedMsg)) ;
}

//发送签到消息
void MsgMgr::sendSignInMsg( int myid ,int isreple)
{
	sendMsg( UrlMgr::getSignInMsg( myid ,isreple),
		httpresponse_selector(ResponseMgr::msgForSignIn)) ;
}

//发送购买补签卡
void MsgMgr::sendBuyRetroactiveMsg( int myid )
{
	sendMsg( UrlMgr::getBuyRetroactiveMsg( myid ),
		httpresponse_selector(ResponseMgr::msgForBuyRetroactive)) ;
}

void MsgMgr::sendRouletteReward( int myid,int wupin_id )
{
	sendMsg( UrlMgr::getRouletteRewardUrl(myid,wupin_id),
		httpresponse_selector(ResponseMgr::msgForRouletteReward));
}

void MsgMgr::sendRoulettePercentReq()
{
	sendMsg( UrlMgr::getRoulettePercentUrl(),
		httpresponse_selector(ResponseMgr::msgForRoulettePercent));
}

void MsgMgr::sendReceiveCollectReward( int userid,int maxLvl,int receiveType )
{
	sendMsg( UrlMgr::getReceiveStarsRewardUrl(userid,maxLvl,receiveType),
		httpresponse_selector(ResponseMgr::msgForReceiveStarsRewards));
}

bool ResponseMgr::analyseResponse(CCHttpResponse *response)
{
	if (!response)
		return false;

	if (!response->isSucceed()) 
	{
//  		if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
//  		{
//  			if(CandyManager::getInstance()->resultMgr->getResultLayer() != NULL)
//  			{
//  				CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGET_NET);
//  			}
//  		}
//  		else if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
//  		{
//   			if (MainMapUiLayer::m_mainmapuilayer)
//   			{
//   				MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_REMINDNETWORK);
//   			}
//  		}

		CCLog("response failed:error buffer: %s", response->getErrorBuffer());
		return false;
	}

	std::vector<char> *buffer = response->getResponseData();
	int bufferSize = buffer->size();
	if(bufferSize <=0 || bufferSize >= JSON_STRING_LEN)
		return false;

	memcpy(&AnalyseJson::jsonString[0], &((*buffer)[0]), bufferSize);
	AnalyseJson::jsonString[bufferSize] = '\0';
	
	//CCLog( "ResponseMgr::analyseResponse %s", AnalyseJson::jsonString);
	return true;
}

void ResponseMgr::msgForLogOn(CCHttpClient *sender, CCHttpResponse *response)
{
	bool ret = false;
	CCLog( "ResponseMgr::msgForLogOn");
	do
	{
		if(!analyseResponse(response))
			return;

		if(!AnalyseJson::setLogOnMsg())
			return;

		ret = true;
	}while(0);

#if defined(DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)

	if ( !CommonData::isFirstInstall() )
	{
		CommonData::setBackgroundState( true );
		CommonData::setSoundEffectState( true );
	}
	Loading::m_loading->HttpGetHeadImgAsyn();
#else
	Loading::m_loading->HttpGetMyInfoAsyn( ret );
#endif
	CCLog( "ResponseMgr::msgForLogOn  nRet = [ %d ]", ret );
}

void ResponseMgr::msgForLevelScore(CCHttpClient *sender, CCHttpResponse *response)
{
// 	int code = response->getResponseCode();
// 	switch(code)
// 	{
// 	case 200:
// 		CCLog("success");
// 		break;
// 	default:
// 		CCUserDefault::sharedUserDefault()->setIntegerForKey("level", num);
// 
// 		break;
// 	}

	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setLevelScoreMsg())
		return;


}

void ResponseMgr::msgForGetFriendInfo(CCHttpClient *sender, CCHttpResponse *response)
{
	bool nRet = response->isSucceed();

	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setUserFriendInfoMsg(AnalyseJson::jsonString))
		return;


	//MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETLIFEPRICE );
	Loading::m_loading->HttpGetFriendListAsyn( nRet );
}


void ResponseMgr::msgForGetFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setFriendInfoForGuestMsg())
		return;

	//　download head ico
	std::list<UserFriendInfoStr>::iterator p;
	int len = 0;
	len = AnalyseJson::friendInfoMsg.friendInfo.size();
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		CCLog("MainMapUiLayer::init ==> ID:%d  IDX:%s",p->id, p->idx.c_str() );
		HeadDownMgr::Instance()->addHeadUrlToList(
			p->id,
			p->headPicUr,
			PIC_TYPE_FRIEND );
	}
	HeadDownMgr::Instance()->startDownLoadPic();


 	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GETFRIENDLIST );
}

void ResponseMgr::msgForGetWorldFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setWorldFriendInfoForGuestMsg())
		return;

	//　download head ico
	int len = AnalyseJson::worldFriendInfoMsg.friendInfo.size();
	std::list<UserFriendInfoStr>::iterator p = AnalyseJson::worldFriendInfoMsg.friendInfo.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		HeadDownMgr::Instance()->addHeadUrlToList(
			p->id,
			p->headPicUr,
			PIC_TYPE_FRIEND );
	}
	HeadDownMgr::Instance()->startDownLoadPic();
}

void ResponseMgr::msgForGetNoFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setNoFriendInfoForGuestMsg())
		return;

	//　download head ico
	std::list<UserNoFriendInfoStr>::iterator p;
	int len = 0;
	len = AnalyseJson::nofriendInfoMsg.nofriend.size();
	p = AnalyseJson::nofriendInfoMsg.nofriend.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		CCLog("MainMapUiLayer::init ==> ID:%d  IDX:%s",p->id, p->idx.c_str() );
		HeadDownMgr::Instance()->addHeadUrlToList(
			p->id,
			p->headPicUr,
			PIC_TYPE_NOFRIEND );
	}
	HeadDownMgr::Instance()->startDownLoadPic();

	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
	{
		if (MainMapUiLayer::m_mainmapuilayer->noFriendListLayout)
		{
			MainMapUiLayer::m_mainmapuilayer->addNofriendtoList();
		}
	}

}

void ResponseMgr::msgForGetLifePrice(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetLifePriceMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETLIFEPRICE );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetLifePriceAsyn();
}

void ResponseMgr::msgForBuyLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setBuyLifeMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_BUYLIFE );
	//MainMapUiLayer::m_mainmapuilayer->HttpBuyLifeAsyn();
}

void ResponseMgr::msgForHandselLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setHandselLifeMsg())
		return;
}

void ResponseMgr::msgForGetHandselLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetHandselMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETHANDSELLIFE );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetHandselLifeAsyn();
}

void ResponseMgr::msgForAcceptLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setAcceptLifeMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_ACCEPTLIFE );
	//MainMapUiLayer::m_mainmapuilayer->HttpAcceptLife();
}


void ResponseMgr::msgForConsumeLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setConsumeLifeMsg())
		return;

	if(AnalyseJson::consumeLifeMsg.totalLife >AnalyseJson::logOnMsg.lifeInfo.lifeNum)
		AnalyseJson::logOnMsg.lifeInfo.lifeNum= AnalyseJson::consumeLifeMsg.totalLife;

	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_CONSUMELIFE );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetConsumeLifeAsyn();

}
void ResponseMgr::msgForConnectUrl(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;
}

void ResponseMgr::msgForRemoveSysLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setRemoveSysLifeMsg())
		return;
}

void ResponseMgr::msgForAddSysLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setAddSysLifeMsg())
		return;

	//AnalyseJson::addSysLifeMsg;
	CCLog(" ResponseMgr::msgForAddSysLife  addSysLifeMsg.totalLife[%d] logOnMsg.lifeInfo.lifeNum[%d]",AnalyseJson::addSysLifeMsg.totalLife, AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	AnalyseJson::logOnMsg.lifeInfo.lifeCountDown = AnalyseJson::addSysLifeMsg.lifeCountDown;
	AnalyseJson::logOnMsg.lifeInfo.lifeNum = AnalyseJson::addSysLifeMsg.totalLife;
	if ( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		if(MainMapUiLayer::m_mainmapuilayer)
		{
			MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_ADDSYSLIFE );

		}
	}
}

void ResponseMgr::msgForGetPropInfo(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetPropInfoMsg())
		return;
}

void ResponseMgr::msgForBuyProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!response)
		return;

	bool ret = false;
	do
	{
		if(!analyseResponse(response))
			break;

		if(!AnalyseJson::setBuyPropMsg())
			break;

		ret = true;
	}while(0);

	int propId = (int)response->getHttpRequest()->getUserData();
	CandyStageIntro::buyPropCallBack(propId);

}

void ResponseMgr::msgForHandselProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setHandselPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_HANDSELPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpHandselPropAsyn();
}

void ResponseMgr::msgForGetHandselProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetHandselPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETHANDSELPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetHandselPropAsyn();
}

void ResponseMgr::msgForAcceptProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setAcceptPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_ACCEPTPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpAcceptPropAsyn();
}

void ResponseMgr::msgForClaimProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setClaimPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_CLAIMPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpClaimPropAsyn();
}

void ResponseMgr::msgForGetClaimedProp(CCHttpClient *sender, CCHttpResponse *response)
{
	bool nRet = response->isSucceed();
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetClaimedPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETCLAIMEDPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetClaimedPropAsyn( nRet );
}

void ResponseMgr::msgForAcceptClaimedProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setAcceptClaimedPropMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_ACCEPTCLAIMEPROP );
	//MainMapUiLayer::m_mainmapuilayer->HttpClaimedPropAcceptAsyn();
}

void ResponseMgr::msgForRefuseClaimedProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setRefuseClaimedProp())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_REFUSECLAIMEDPROP );

}

void ResponseMgr::msgForAllAcceptUserHandsel(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setAllAcceptHandselMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_ALLACCEPTHANDSEL );
}

void ResponseMgr::msgForFilterNoFriend(CCHttpClient *sender, CCHttpResponse *response)
{
	CCLog( "ResponseMgr==>msgForFilterNoFriend" );
	if(!analyseResponse(response))
		return;

	if (!AnalyseJson::setForFilterNoFriend())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_FILTERNOFRIEND );

}

void ResponseMgr::msgForConsumeProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setConsumePropMsg())
		return;

	list<UserPropInfoStr >::iterator newPropIter;
	list<UserPropInfoStr >::iterator currentPropIter;
	for(newPropIter= AnalyseJson::consumePropStr.stagePropInfo.begin();	newPropIter!=AnalyseJson::consumePropStr.stagePropInfo.end(); newPropIter++)
	{
		for(currentPropIter= AnalyseJson::logOnMsg.propInfo.begin();	currentPropIter!=AnalyseJson::logOnMsg.propInfo.end(); currentPropIter++)
		{
			if((*currentPropIter).id == (*newPropIter).id)
				(*currentPropIter).num =  (*newPropIter).num;
		}
	}
}

void ResponseMgr::msgForGetUserProp(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetUserPropMsg())
		return;
}

void ResponseMgr::msgForGetChatRecord(CCHttpClient *sender, CCHttpResponse *response)
{
	bool nRet = response->isSucceed();
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setGetPropRecordMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETCHATRECORD );
	//MainMapUiLayer::m_mainmapuilayer->HttpGetChatRecordAsyn();
}

void ResponseMgr::msgFor3PartyGetNoFriendInfo(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setForNoFriendInfoMsg())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETNOFRIENDINFO );
}

void ResponseMgr::msgForInviteFirendMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if(!analyseResponse(response))
		return;

	if(!AnalyseJson::setForInviteFriendMsg())
		return;
}

void ResponseMgr::msgForNoticeDataMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForNoticeData())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GETNOTICEMSG );
}


void ResponseMgr::msgForGetChitchatMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForChitchat())
		return;

	//　to Java_org_weme_candy_util_JavaCallCpp_passIDs
	//CppCallJava::initChat(AnalyseJson::logOnMsg.baseInfo.id, AnalyseJson::logOnMsg.baseInfo.Chitchat, AnalyseJson::logOnMsg.baseInfo.nickName.c_str() );
}

void ResponseMgr::msgForGetGameStateMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setGameState())
		return;
}

void ResponseMgr::msgForSystemGivePropMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setSystemGiveProp())
		return;

}

void ResponseMgr::msgForMagicLampTime(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setMagicLampTime())
		return;

	CandyManager::getInstance()->uiLayer->showMagicLamp();

}

void ResponseMgr::msgForUseMagicLamp(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;
	if (!AnalyseJson::setUseMagicLamp())
		return;

	CandyManager::getInstance()->uiLayer->showMagicLamp();
}

void ResponseMgr::msgForEnergyUseNum(CCHttpClient *sender, CCHttpResponse *response)
{
 	//CandyManager::getInstance()->uiLayer->energyJarButton->setTouchEnable(true);
 
 	if (!analyseResponse(response))
 		return;
 
 	if (!AnalyseJson::setEnergyUseNum())
 		return;
 
 	//以后做成回调
 	CandyManager::getInstance()->uiLayer->showPropBuy(CANDY_PROP_IN_GUANZI);
}

void ResponseMgr::msgForGetSystemHeadUrlMsg(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setSystemHeadUrl())
		return;

	CCLog("ResponseMgr::msgForGetSystemHeadUrlMsg");
	int len = AnalyseJson::SysHeadUrl.headUrl.size();
	std::list<std::string>::iterator p = AnalyseJson::SysHeadUrl.headUrl.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		HeadDownMgr::Instance()->addHeadUrlToList(
			0,
			p->c_str(),
			PIC_TYPE_SYSTEM );
	}
	HeadDownMgr::Instance()->startDownLoadPic();
	CCLog("ResponseMgr::msgForGetSystemHeadUrlMsg2");
}

void ResponseMgr::msgForGemBuyVip(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForGemBuyVip())
		return;

	CommonData::sendGemConsumeStatistics( CANDY_PROP_VIP, CommonData::getMaxLevel() );
	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GEMBUYVIP );
	}
}

void ResponseMgr::msgForGemBuyLife(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForGemBuyLife())
		return;

	CommonData::sendGemConsumeStatistics( CANDY_PROP_LIFE, CommonData::getMaxLevel() );
	CommonData::m_isBuyLife = true;
	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GEMBUYLIFE );
}

void ResponseMgr::msgForGemBuyProp(CCHttpClient *sender, CCHttpResponse *response)
{
	CCLog("111111112222222222");
	if (!analyseResponse(response))
		return;
	CCLog("1111111133333333333");
	if (!AnalyseJson::setForGemBuyProp())
		return;
	CCLog("11111111444444444444");

	int propId = (int)response->getHttpRequest()->getUserData();
	if(propId != CANDY_PROP_OUT_HEAD)
	{
		CommonData::m_curBuyPropid = propId;
		CandyStageIntro::buyPropCallBack(propId);
	}
	CCLog("ResponseMgr::msgForGemBuyProp propId[%d] scenceType[%d]", propId, Loading::scenceType );

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		CCLog("11111111555555555555");

		//MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
		if(propId != CANDY_PROP_OUT_HEAD)
		{
			CommonData::sendGemConsumeStatistics( propId,  CandyManager::currentLevel );
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
			MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
			
			//MainMapUiLayer::m_mainmapuilayer->updataShopGemAndCandNum();
		}
		else if(propId == CANDY_PROP_OUT_HEAD)
		{
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
			MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
			CommonData::sendGemConsumeStatistics( CANDY_PROP_HEAD, CommonData::getMaxLevel() );
			MainMapUiLayer::m_mainmapuilayer->uploadInfo();
		}
	}
	else if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType)
	{
		CCLog("11111111666666666666");

		CommonData::sendGemConsumeStatistics( propId, CandyManager::currentLevel, CommonData::m_gamemode, (3 == CommonData::m_gamemode)?CandyManager::timeLimit:CandyMove::moveLimit  );
		if(CANDY_PROP_IN_STEP5 == propId && GAME_STATE_FAIL == CandyManager::getInstance()->resultMgr->gamestate)
		{
			BuySuccessTips();
			CandyManager::getInstance()->resultMgr->gamestate = GAME_STATE_SUCCEE;
			CandyManager::getInstance()->uiLayer->useProp(CANDY_PROP_IN_STEP5);
			
		}
		else if(CANDY_PROP_IN_RESORT == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget_dis();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget_dis();
			BuySuccessTips();	
			//CandyManager::getInstance()->uiLayer->useProp(CANDY_PROP_IN_RESORT);
		}
		else if(CANDY_PROP_IN_SWAP == propId)
		{
			CCLog("11111111777777777777");
			CandyManager::getInstance()->uiLayer->QuitPropWidget_dis();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget_dis();
			BuySuccessTips();	
			//CandyManager::getInstance()->uiLayer->candyUsePropStart(CANDY_PROP_IN_SWAP);
		}
		else if(CANDY_PROP_OUT_COLORFULL == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget_dis();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget_dis();
			BuySuccessTips();	
			//CandyManager::getInstance()->uiLayer->candyUsePropStart(CANDY_PROP_OUT_COLORFULL);
		}
		else if(CANDY_PROP_OUT_BOMBNEW == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget_dis();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget_dis();
			BuySuccessTips();	
			//CandyManager::getInstance()->uiLayer->candyUsePropStart(CANDY_PROP_OUT_BOMBNEW);
		}
		else if(CANDY_PROP_IN_HAMMER == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget_dis();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget_dis();
			BuySuccessTips();	
			//CandyManager::getInstance()->uiLayer->candyUsePropStart(CANDY_PROP_IN_HAMMER);
		}

		//增加5步
		else if(CANDY_PROP_IN_STEP5 == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
			BuySuccessTips();	
		}

		else if(CANDY_PROP_IN_GUANZI == propId)
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
			CommonData::m_buyState = true;
		}
		else if(CANDY_PROP_COMPOSE_1 == propId)
		{
			for(int type = 33; type <= 35; ++type)
			{
				CommonData::setPropNum((CandyPropType)type,1);
				int propNum = CommonData::getPropNum((CandyPropType)type);
				if(propNum > 0)
				{
					CommonData::setPropUseState((CandyPropType)type, true);
				}
			}
			Layout *pLayout = CandyManager::getInstance()->resultMgr->getResultLayer()->getDiscountGoodsLayout();
			pLayout->setTouchEnable(false);
			pLayout->removeFromParent();
			CommonData::m_resetPropState = false;
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NEXT_STAGE);
		}
		else
		{
			CandyManager::getInstance()->uiLayer->QuitPropWidget();
			CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
		}
	}
}

void ResponseMgr::msgForGemBuySkill(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForGemBuySkill())
		return;

	CCLog("msgForUpdateGem ");

	CandyManager::getInstance()->uiLayer->QuitPropWidget();
	CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
	CommonData::sendGemConsumeStatistics( CANDY_PROP_GUANZI, CandyManager::currentLevel, CommonData::m_gamemode, (3 == CommonData::m_gamemode)?CandyManager::timeLimit:CandyMove::moveLimit );

	CommonData::m_buyState = true;
}

void ResponseMgr::msgForGemBuyPackage(CCHttpClient *sender, CCHttpResponse *response)
{
	CCLog("libao jieguo 11111");
	if (!analyseResponse(response))
		return;
	CCLog("libao jieguo 22222");

	if (!AnalyseJson::setForGemBuyPackage())
		return;
	CCLog("libao jieguo 33333");

	// 发送记录点数据
	int nPackageID = (int)response->getHttpRequest()->getUserData();

	switch(nPackageID)
	{
	case 1:
		CommonData::sendGemConsumeStatistics( GameGift_Level4,  CandyManager::currentLevel );
		break;
	case 2:
		CommonData::sendGemConsumeStatistics( GameGift_Level5,  CandyManager::currentLevel );
		break;
	case 3:
		CommonData::sendGemConsumeStatistics( GameGift_Level6,  CandyManager::currentLevel );
		break;
	case 4:
		CommonData::sendGemConsumeStatistics( GameGift_Level1,  CandyManager::currentLevel );
		break;
	case 5:
		CommonData::sendGemConsumeStatistics( GameGift_Level2,  CandyManager::currentLevel );
		break;
	case 6:
		CommonData::sendGemConsumeStatistics( GameGift_Level4,  CandyManager::currentLevel );
		break;
	}

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		if(CommonData::m_GiftIDBuyNow < 6 && CommonData::m_GiftIDBuyNow >= 4)
		{
			CommonData::m_GiftIDBuyNow += 1;
		}
		else if(CommonData::m_GiftIDBuyNow == 6)
		{
			UIButton* m_gameGiftBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameGift")); 

			m_gameGiftBut->setVisible(false);
			m_gameGiftBut->setTouchEnable( false );

			CommonData::m_GiftIDBuyNow = 0;
		}

		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
		MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
	}
	else if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
	{
		CommonWidgt::m_SuperGiftWidget->GameGiftExit(NULL);
		AnalyseJson::logOnMsg.baseInfo.isBuySuperGift = 1;	//改变状态礼包是否购买状态
		//成功提示
		BuySuccessTips();
	}
}

void ResponseMgr::msgForRewardVip(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForRewardVip())
		return;

	// 发送记录点数据
	int nVipID = (int)response->getHttpRequest()->getUserData();

	switch( nVipID )
	{
	case 1:
		CommonData::sendGemConsumeStatistics( GameVip_Level1,  CandyManager::currentLevel );
		break;
	case 2:
		CommonData::sendGemConsumeStatistics( GameVip_Level2,  CandyManager::currentLevel );
		break;
	case 3:
		CommonData::sendGemConsumeStatistics( GameVip_Level3,  CandyManager::currentLevel );
		break;
	}

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
	}
}

void ResponseMgr::msgForUpdateGem(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForUpdateGemNum())
		return;

	int propId = (int)response->getHttpRequest()->getUserData();
	CCLog("ResponseMgr::msgForUpdateGem1  buytype[%d]", propId);

	// 购买宝石
	if ( 0 == propId )
	{

	}
	// 购买生命
	else if ( CANDY_PROP_LIFE == propId )
	{
		MsgMgr::sendGemBuyLife( AnalyseJson::logOnMsg.baseInfo.id ,MOBILE_GOURD_LIFENUM);
		CommonData::m_buytype = 0;
	}
	//　解锁主线任务
	else if ( CANDY_PROP_UNLACK_MAINTASK == propId )
	{
		CCLog("ResponseMgr::msgForUpdateGem1  buytype[%d]　taskid[%d]", propId, AnalyseJson::taskTable.buytaskid );
		MsgMgr::sendUnLockTask (AnalyseJson::logOnMsg.baseInfo.id, AnalyseJson::taskTable.buytaskid );

	}
	//　购买好友上限
	else if ( CANDY_PROP_FRIEND_LIMIT == propId )
	{
		MsgMgr::sendBuyFriendlimitForMsg( AnalyseJson::logOnMsg.baseInfo.id );
		CommonData::m_buytype = 0;
	}
	//　购买补签卡
	else if ( CANDY_PROP_RETROACTIVE == propId )
	{
		MsgMgr::sendBuyRetroactiveMsg( AnalyseJson::logOnMsg.baseInfo.id );
		CommonData::m_buytype = 0;
	}
	else if(CANDY_PROP_IN_GUANZI == propId)
	{
		CCLog("ResponseMgr::msgForUpdateGem1  buytype Skill");
		MsgMgr::sendGemBuySkill( AnalyseJson::logOnMsg.baseInfo.id );
		CommonData::m_buytype = 0;
	}
	else if(CANDY_PROP_OUT_HEAD == propId)
	{
		MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_OUT_HEAD, 1);
		CommonData::m_buytype = 0;
	}
	else if(
		(CANDY_PROP_OUT_STEP3 <= propId && CANDY_PROP_IN_BOMB >= propId ) ||
		(CANDY_PROP_OUT_DOUBLE <= propId && CANDY_PROP_COMPOSE_1 >= propId )
		)
	{
		CCLog("ResponseMgr::msgForUpdateGem1  buytype prop");
		CommonData::m_buytype = 0;
		if(CommonData::m_buyMutipropNum != 0)
		{
			CCLog("buy prop 1111 propid = %d",propId);
			MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, propId, CommonData::m_buyMutipropNum);
			CommonData::m_buyMutipropNum = 0;
		}
		else
		{
			CCLog("buy prop 2222 propid = %d",propId);
			MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, propId, 1);
		}
	}
	else if( GameVip_Level1 <= propId && GameVip_Level3 >= propId )
	{
		CommonData::m_buytype = 0;
		int vipLevel = 0;
		int vipStone = 0;
		switch(propId)
		{
		case GameVip_Level1:
			vipLevel = 1;
			vipStone = 50;
			break;
		case GameVip_Level2:
			vipLevel = 2;
			vipStone = 80;
			break;
		case GameVip_Level3:
			vipLevel = 3;
			vipStone = 100;
			break;
		}
		CCLog("vipLevel is %d,vipStone is %d",vipLevel,vipStone);
		MsgMgr::sendGemBuyVip( AnalyseJson::logOnMsg.baseInfo.id,vipLevel,vipStone);
	}
	else if( GameGift_Level1 <= propId && GameGift_Level6 >= propId )
	{
		int currentId = 0;
		switch(propId)
		{
		case GameGift_Level1:
			currentId = 4;
			break;
		case GameGift_Level2:
			currentId = 5;
			break;
		case GameGift_Level3:
			currentId = 6;
			break;
		case GameGift_Level4:
			currentId = 1;
			break;
		case GameGift_Level5:
			currentId = 2;
			break;
		case GameGift_Level6:
			currentId = 3;
			break;
		}
		MsgMgr::sendGemBuyPackage( AnalyseJson::logOnMsg.baseInfo.id,currentId);
		CommonData::m_buytype = 0;
	}
}

void ResponseMgr::msgGetMyAllMsgForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForMyAllMsgG())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType && CommonData::getMaxLevel() >= AnalyseJson::unLockConfig.friendFun )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GETMYALLMESSAGE );
}

void ResponseMgr::msgGetInviteFriendMsgForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForInviteFriendMsgG())
		return;

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_INVITEFRIENDMSG );
}

void ResponseMgr::msgSeachFriendForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForSeachFriendMsgG())
		return;

	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_SEACHFRIENDRESULT );
}

void ResponseMgr::msgAcceptAddFriendMsgForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setAcceptAddFriendMsgG())
		return;
}

void ResponseMgr::msgSingleLevelResultForGuest(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!response->isSucceed()) 
	{
		if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
		{
			if(CandyManager::getInstance()->resultMgr->getResultLayer() != NULL)
			{
				CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGET_NET);
			}
		}
	}
 	if (!analyseResponse(response))
 	{
 		return;
 	}
	if (!AnalyseJson::setForGetSinglelevelResult())
	{
		return;
	}
	if(CommonData::m_isEnterNext == false)
	{
		CommonData::m_isEnterNext = true;
		if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
		{
			AnalyseJson::SingleLevelResultStr.friendInfo.sort(Cmpare2());

			int tempScore = CandyManager::getInstance()->scoreMgr->getCurrentScore();

			std::list<UserSingleLevelStr>::iterator iter = AnalyseJson::SingleLevelResultStr.friendInfo.begin();
			std::list<UserSingleLevelStr>::iterator iterbegin = AnalyseJson::SingleLevelResultStr.friendInfo.begin();
			std::list<UserSingleLevelStr>::iterator iterend   = AnalyseJson::SingleLevelResultStr.friendInfo.end();
			for(;iterbegin!=iterend; ++iterbegin)
			{
				if(iterbegin->id == AnalyseJson::logOnMsg.baseInfo.id)
				{
					if(iterbegin->result < tempScore)
					{
						iterbegin->result = tempScore;
					}
					break;
				}
				if(iterbegin->result > tempScore)
				{
					++iter;
				}
			}
			//获取超越的好友的信息
			if(iter != iterbegin)
			{
				UserSingleLevelStr *exceedPlayer = &(*iter);
				AnalyseJson::SingleLevelResultStr.friendInfo.sort(Cmpare2());

				CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGE_GAME_RESORTRANK,true,(void*)exceedPlayer);
			}
			else
			{
				CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_WIN);
			}
		}
	}
}

void ResponseMgr::msgSingleLevelResultForGuestInMap(CCHttpClient *sender, CCHttpResponse *response)
{
	if (!analyseResponse(response))
		return;

	if (!AnalyseJson::setForGetSinglelevelResult())
		return;

	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
	{
		AnalyseJson::SingleLevelResultStr.friendInfo.sort(Cmpare2());
		if(CandyStageIntro::layout)
		{
			CandyStageIntro::layout->AddFriendToRank();
		}
	}
	else if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
	{
		AnalyseJson::SingleLevelResultStr.friendInfo.sort(Cmpare2());
		if(CandyStageIntro::layout)
		{
			CandyStageIntro::layout->AddFriendToRank();
		}
	}
}

void ResponseMgr::msgForSoundOutLogin( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setSoundOutMsg())
		return;
}

void ResponseMgr::msgForRegetdit( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setRegeditMsg())
		return;
}

void ResponseMgr::msgUpdataGameMsg( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
	{
		return;
	}

	if ( !AnalyseJson::setUpdataGameMsg())
	{
		MsgMgr::SendSoundOutLogin( AnalyseJson::logOnMsg.baseInfo.idx.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str() );
		return;
	}

	if ( 0 == AnalyseJson::updataData.netStatus && 200 == AnalyseJson::updataData.netid )
	{
		// 强制更新
		if ( 1 == AnalyseJson::updataData.updataStatus)
		{
		}
		else
		{
			CCLog( "ResponseMgr::msgUpdataGameMsg 0 200" );
			Loading::m_loading->showWidget( LOGINUI_WIDGET_TYPE_UPDATA );
		}
	}
	else
	{
		CCLog( "ResponseMgr::msgUpdataGameMsg - 1" );
		MsgMgr::SendSoundOutLogin( AnalyseJson::logOnMsg.baseInfo.idx.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str() );
	}
}

void ResponseMgr::msgForGetSystemTask( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setGetSystemTask())
		return;
}

void ResponseMgr::msgForSubmitTask( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setSubmitTask())
		return;
}

void ResponseMgr::msgForGetRewardTask( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setGetRewardTask())
		return;
}

void ResponseMgr::msgForUnLockTaskMsg( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setUnLockTaskMsg())
		return;
	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_UNLOCKMAINTASK );

}

void ResponseMgr::msgForBuyFriendLimit( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForBuyFriendLimitMsg())
		return;
#ifdef CANDY_STATISITICAL_DATA
	//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4015, CCString::createWithFormat("%d", AnalyseJson::friendInfoMsg.friendInfo.size())->getCString(), CCString::createWithFormat("%d", AnalyseJson::friendInfoMsg.friendMaxNum)->getCString());
#endif
	CommonData::sendGemConsumeStatistics( CANDY_PROP_FRIEND_LIMIT , CommonData::getMaxLevel());
	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_BUYFRIENDLIMIT );
}

void ResponseMgr::msgForGetWorldRankedMsg( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setWorldRankedMsg())
		return;

	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
		MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENTNT_GETMYWORLDRANKED );
}

void ResponseMgr::msgForSignIn( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForSignIn())
		return;
}

void ResponseMgr::msgForBuyRetroactive( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForBuyRetroactive())
		return;
}

void ResponseMgr::msgForUnlockLevel( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForUnlockLevel())
		return;

	int level = (int)response->getHttpRequest()->getUserData();

	if( CANDY_SCENCE_MAIN_MAP == Loading::scenceType )
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

		UIImageView* pImg = dynamic_cast<UIImageView*>(MainMap::m_mainmap->getBigMapUILayer()->getWidgetByTag(2000 + level));

		CCPoint position = pImg->getPosition();
		CandyParticle::displayCandyParticle(CANDY_UNLOCKLEVEL_EFFECT, position,MainMap::m_mainmap->getBigMapUILayer());
		pImg->removeFromParent();
	}
}

void ResponseMgr::msgForRouletteReward( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForRouletteReward())
		return;

}

void ResponseMgr::BuySuccessTips()
{
	if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType)
	{
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* BuyPrompt = CCSprite::create("Image/MainMapUi/ImgBuyPromtp.png");
	BuyPrompt->setPosition( ccp(size.width/2,size.height*0.6));
	CCNode* node = CCDirector::sharedDirector()->getRunningScene();
	node->addChild( BuyPrompt,0,1000);

	//CCPoint pos = pBtn->getParent()->convertToWorldSpace(pBtn->getPosition());
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(size.width/2,size.height*0.6), node);

	CCActionInterval * spawn = CCSpawn::create(
		CCMoveTo::create(1.0f, ccp(size.width/2,size.height*0.6 + 150)),
		CCFadeOut::create(1.0f),
		NULL);

	BuyPrompt->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		spawn,
		CCCallFuncN::create(this, callfuncN_selector(ResponseMgr::FuncAfterTips)),
		NULL));
}

void ResponseMgr::FuncAfterTips( CCNode* node )
{
	if (!node)
	{
		return;
	}
	node->removeFromParentAndCleanup(true);
}

void ResponseMgr::msgForRoulettePercent( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	if ( !AnalyseJson::setForRoulettePercent())
		return;
}

void ResponseMgr::msgForReceiveStarsRewards( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!analyseResponse(response))
		return;

	//数据解析
	if ( !AnalyseJson::setForCollectStarReward())
		return;

	//发送更新界面消息
	CCNotificationCenter::sharedNotificationCenter()->postNotification(receiveCollectMsg,NULL);
}
