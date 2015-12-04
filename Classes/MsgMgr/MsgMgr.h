#ifndef MSG_MGR__H
#define MSG_MGR__H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


enum
{
	HTTP_NETEVENT_LOGON = 0,
	HTTP_NETENENT_LEVELSCORE = 1,
	HTTP_NETENENT_GETFRIENDINFO = 3,
	HTTP_NETENENT_ALLACCEPTHANDSEL = 4,	//全部接受别人赠送的生命及道具
	HTTP_NETENENT_INVITEFRIEND = 5,    // 邀请好友
	HTTP_NETENENT_FILTERNOFRIEND = 6,	//过滤邀请第三方好友信息
	HTTP_NETENENT_FEEDBACKINFO = 8,    //记录用户反馈信息
	HTTP_NETENENT_GETNOFRIENDINFO = 83,	// 获得非好友详细信息   通过第三方调用 
	HTTP_NETENENT_GETLIFEPRICE = 300,	//获取生命基本属性信息
	HTTP_NETENENT_BUYLIFE = 301,	//购买生命
	HTTP_NETENENT_HANDSELLIFE = 302,	//赠送生命
	HTTP_NETENENT_GETHANDSELLIFE = 303, //获得赠送生命的消息
	HTTP_NETENENT_ACCEPTLIFE = 304,	//读取用户生命消息
	HTTP_NETENENT_CONSUMELIFE = 305, //消耗生命
	HTTP_NETENENT_REMOVESYSLIFE = 306,	//删除系统赠送生命
	HTTP_NETENENT_ADDSYSLIFE = 307,	//添加系统赠送生命
	HTTP_NETENENT_GETPROPINFO = 400,	//获取游戏道具属性信息
	HTTP_NETENENT_BUYPROP = 401,	//购买道具
	HTTP_NETENENT_HANDSELPROP = 402,	//赠送道具
	HTTP_NETENENT_GETHANDSELPROP = 403,	//获得赠送道具的消息
	HTTP_NETENENT_ACCEPTPROP = 404,	//读取赠送用户道具消息
	HTTP_NETENENT_CLAIMPROP = 405,	//索要道具
	HTTP_NETENENT_GETCLAIMEDPROP = 406,		//获得索要道具的消息
	HTTP_NETENENT_ACCEPTCLAIMEPROP = 407,	//读取索要用户道具消息
	HTTP_NETENENT_CONSUMEPROP = 408,	//消耗道具
	HTTP_NETENENT_GETUSERPROP = 409,	//通过用户ID和道具ID获取用户道具信息
	HTTP_NETENENT_GETCHATRECORD = 410,	//通过用户ID获取用户道具历史消息
	HTTP_NETENENT_REFUSECLAIMEDPROP = 411,			//拒绝用户索要道具消息
	HTTP_NETENTNT_GETNOTICEMSG = 700,			// 获取公告消息
	HTTP_NETENTNT_SYSTEMGIVEPROP = 412,		//系统赠送道具
	HTTP_NETENTNT_GEMBUYLIFE = 309,
	HTTP_NETENTNT_INVITEFRIENDMSG = 1303,	// 获取添加好友消息
	HTTP_NETENTNT_GETMYALLMESSAGE = 312,	// 获得我的消息
	HTTP_NETENTNT_SEACHFRIENDRESULT = 1306, //搜索好友结果
	HTTP_NETENTNT_GEMBUYVIP = 16,			//vip 购买
	HTTP_NETENTNT_BUYFRIENDLIMIT = 1308,		// 购买好友
	HTTP_NETENTNT_GETFRIENDLIST = 1300,		// 获得好友列表
	HTTP_NETENTNT_UNLOCKMAINTASK = 1703,	// 解锁主线任务
	HTTP_NETENTNT_GETMYWORLDRANKED = 23,	// 获得我的世界排名
};

class  ResponseMgr:public CCObject
{
	public:
		//connect url
		void msgForConnectUrl(CCHttpClient *sender, CCHttpResponse *response);

		void msgForSoundOutLogin(CCHttpClient *sender, CCHttpResponse *response);
		void msgForRegetdit(CCHttpClient *sender, CCHttpResponse *response);
		void msgForLogOn(CCHttpClient *sender, CCHttpResponse *response);
		void msgForLevelScore(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetFriendInfo(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetWorldFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetNoFriendInfoForGuest(CCHttpClient *sender, CCHttpResponse *response);

		void msgForGetLifePrice(CCHttpClient *sender, CCHttpResponse *response);//获得生命价格
		void msgForBuyLife(CCHttpClient *sender, CCHttpResponse *response);//购买生命
		void msgForHandselLife(CCHttpClient *sender, CCHttpResponse *response); // 送生命
		void msgForGetHandselLife(CCHttpClient *sender, CCHttpResponse *response); //别人送的生命
		void msgForAcceptLife(CCHttpClient *sender, CCHttpResponse *response);//接爱获送的生命
		void msgForConsumeLife(CCHttpClient *sender, CCHttpResponse *response);// 消耗生命
		void msgForRemoveSysLife(CCHttpClient *sender, CCHttpResponse *response);
		void msgForAddSysLife(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetPropInfo(CCHttpClient *sender, CCHttpResponse *response);// 获得道具信息
		void msgForBuyProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForHandselProp(CCHttpClient *sender, CCHttpResponse *response);//402
		void msgForGetHandselProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForAcceptProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForClaimProp(CCHttpClient *sender, CCHttpResponse *response);//405
		void msgForGetClaimedProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForAcceptClaimedProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForConsumeProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetUserProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetChatRecord(CCHttpClient *sender, CCHttpResponse *response);
		void msgForRefuseClaimedProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForAllAcceptUserHandsel(CCHttpClient *sender, CCHttpResponse *response);
		void msgForFilterNoFriend(CCHttpClient *sender, CCHttpResponse *response);
		void msgFor3PartyGetNoFriendInfo(CCHttpClient *sender, CCHttpResponse *response);
		void msgForInviteFirendMsg(CCHttpClient *sender, CCHttpResponse *response);
		void msgForNoticeDataMsg(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetChitchatMsg(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetGameStateMsg(CCHttpClient *sender, CCHttpResponse *response);
		void msgForSystemGivePropMsg(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetSystemHeadUrlMsg(CCHttpClient *sender, CCHttpResponse *response);
		//购买多少次能量罐
		void msgForEnergyUseNum(CCHttpClient *sender, CCHttpResponse *response);
		//神灯
		void msgForMagicLampTime(CCHttpClient *sender, CCHttpResponse *response);
		void msgForUseMagicLamp(CCHttpClient *sender, CCHttpResponse *response);

		void msgForGemBuyVip(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGemBuyLife(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGemBuyProp(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGemBuySkill(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGemBuyPackage(CCHttpClient *sender, CCHttpResponse *response);
		void msgForUpdateGem(CCHttpClient *sender, CCHttpResponse *response);

		void msgGetMyAllMsgForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgGetInviteFriendMsgForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgSeachFriendForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgAcceptAddFriendMsgForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgForBuyFriendLimit(CCHttpClient *sender, CCHttpResponse *response);
		void msgSingleLevelResultForGuest(CCHttpClient *sender, CCHttpResponse *response);
		void msgSingleLevelResultForGuestInMap(CCHttpClient *sender, CCHttpResponse *response);

		void msgUpdataGameMsg(CCHttpClient *sender, CCHttpResponse *response);

		// task
		void msgForGetSystemTask(CCHttpClient *sender, CCHttpResponse *response);
		void msgForSubmitTask(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetRewardTask(CCHttpClient *sender, CCHttpResponse *response);
		void msgForUnLockTaskMsg(CCHttpClient *sender, CCHttpResponse *response);

		void msgForGetWorldRankedMsg(CCHttpClient *sender, CCHttpResponse *response);
 
		void msgForRewardVip(CCHttpClient *sender, CCHttpResponse *response);

		//解锁关卡
		void msgForUnlockLevel(CCHttpClient *sender, CCHttpResponse *response);

		// 签到相关
		void msgForSignIn(CCHttpClient *sender, CCHttpResponse *response);
		void msgForBuyRetroactive(CCHttpClient *sender, CCHttpResponse *response);

		//转盘奖励领取
		void msgForRouletteReward(CCHttpClient *sender, CCHttpResponse *response);

		//购买道具成功提示
		void BuySuccessTips();
		void FuncAfterTips(CCNode* node);

	public:
		static bool analyseResponse(CCHttpResponse *response);
		void msgForRoulettePercent( CCHttpClient *sender, CCHttpResponse *response );
		//		static void msgFor3PartyGetNoFriendInfo();

		//收集星星奖励领取数据回调
		void msgForReceiveStarsRewards(CCHttpClient *sender, CCHttpResponse *response);
};

class MsgMgr:public CCObject
{
	public:
		static void sendMsg(char *url, SEL_HttpResponse pSelector, void *userData=NULL);
		
	public:
		static void sendUpdataGameMsg(int ver);
		static void sendRegeditChatUser(const char* nickname, const char* idx, const char* packpag);
		static void SendSoundOutLogin(const char* idx, const char* channel);
		static void sendRegeditUser(const char* idx, const char* channel1, const char* channel2, const char* version);
		static void sendLogOnMsg(const char *idx);
		static void sendLevelScoreMsg(int userId,  int level,  int score, int candynum);
		static void sendGetFriendInfoMsg(void);
		static void sendGetFriendForGuestMsg(int userId, int page = 1, int limit = 1000);
		static void sendGetWorldFriendForGuestMsg();
		static void sendGetNoFriendForGuestMsg(int userId, int page = 1, int limit = 20);
		static void sendInvateFriendForGuestMsg(int myId, int invateId);
		static void sendGetLifePriceMsg(void);
		static void sendBuyLifeMsg(int userId, int lifeNum, int lifePrice);
		static void sendHandselLifeMsg(int myId, int friendId);//　赠送生命
		static void sendGetHandselLifeMsg(int userId, int page = 1, int limit = 40);
		static void sendAcceptLifeMsg(int myId, int givenId, int friendId);
		static void sendConsumeLifeMsg(int myId, int num);
		static void sendConnectMsg(int myId);
		static void sendRemoveSysLifeMsg(int myId);
		static void sendAddSysLifeMsg(int myId);
		static void sendFeedbackMsg(int myId,std::string info);

		static void sendGetPropInfoMsg(int propId);
		static void sendBuyPropMsg(int userId, int propId);	
		static void sendHandselPropMsg(int myId, int friendId, int propId, int propPrice, int propNum);	//400
		static void sendGetHandselPropMsg(int userId);
		static void sendAcceptPropMsg(int myId, int friendId, int givenId);//404
		static void sendClaimPropMsg(int myId, int friendId, int propId, int propPrice, int propNum);//405
		static void sendGetClaimedPropMsg(int userId);//406
		static void sendAcceptClaimedPropMsg(int myId, int friendId,int claimedId);//407
		static void sendConsumePropMsg(int userId, int propId, int propNum);
		static void sendGetUserPropMsg(int userId, int propId);
		static void sendGetChatRecordMsg(int userId );
		static void sendRefuseClaimedPropMsg(int myId, int friendId,int claimedId);// 411
		static void sendAllAcceptUserHandsel( int myId);
		static void sendFilterNoFriend(char* myIdx, char* nofriendidx);
		static void send3PartyGetNoFriendInfoMsg(char* friendidx);
		static void sendInviteFirendMsg(char* myIdx, char* friendidx);
		static void sendInvateFirendMsg(int myIdx, int friendidx);
		static void sendGetNoticeData(void);
		static void sendGetChitchatSt(void);
		static void sendGetGameState(int myid, int state);
		static void sendSystemGiveProp(int myid, int propid);
		static void sendMyInformation(int myid, int qq, int sex, char* nickname);
		static void sendGetSystemHeadUrl(void);

		// 好友相关
		static void sendgetMyAllMsgForGuest(int userid, int page = 1, int limit = 60);
		static void sendgetInviteFriendMsgForGuest(int userId, int page = 1, int limit = 40);
		static void sendAcceptAddFriendForGuestMsg(int myId, int friendId);
		static void sendDelFriendForGuestMsg(int myId, int friendId);
		static void sendBuyFriendlimitForMsg(int myId);

		static void sendNoAcceptAddFriendForGuestMsg(int myId, int friendId);
		static void sendCleanAddFriendForGuestMsg(int myId);
		static void sendSeachFriendForGuestMsg(int userId, char*condition, int page = 1, int limit = 40);
		static void sendGetSingleLevelResult(int userid, int level, int page = 1, int limit = 100);

		//发送当前罐子能量
		static void sendEnergyNumMsg(int myid,int num);
		static void sendEnergyUseNumMsg(int userId);
		//
		static void sendMagicLampTimeRequest(int userId);
		static void sendUseMagicLampTimeRequest(int userId);


		// Gem buy
		static void sendGemBuyVip(int myid, int vipLevel,int vipStone);
		static void sendGemBuyLife(int myid, int lifenum);
		static void sendGemBuyProp(int myid, int propid, int propnum, int candyType = 1);// 使用货币（1：宝石，2：糖果币）不传默认为1
		static void sendGemBuySkill(int myid);
		static void sendUpdateGem(int myid, int buytype);
		static void sendGetSingleLevelResultInMap(int userid, int level, int page = 1, int limit = 100);
		//礼包
		static void sendGemBuyPackage(int myid, int packageid);


		static void sendRewardVip(int myid);

		// task
		static void sendGetSystemTask(int myid);
		static void sendSubmitTask(int myid, int taskid, int num);
		static void sendGetRewardTask(int myid, int taskid, int starnum);
		static void sendUnLockTask(int myid, int taskid);

		//　world ranked
		static void sendGetWorldRanked(int myid);
		
		//　关卡失败
		static void sendLevelFail(int myid, int level);

		//　签到相关
		static void sendSignInMsg( int myid ,int isreple= 0); //发送签到消息
		static void sendBuyRetroactiveMsg(int myid);	//　购买签到卡

		//解锁关卡
		static void sendUnlockLevel(int myid,int gemnum,int level);

		//转盘领取奖励
		static void sendRouletteReward(int myid,int wupin_id);
		static void sendRoulettePercentReq();

		//领取收集星星奖励
		static void sendReceiveCollectReward(int userid,int maxLvl,int receiveType);

		

private:
		static ResponseMgr responseMgr;

};


#endif
