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
	HTTP_NETENENT_ALLACCEPTHANDSEL = 4,	//ȫ�����ܱ������͵�����������
	HTTP_NETENENT_INVITEFRIEND = 5,    // �������
	HTTP_NETENENT_FILTERNOFRIEND = 6,	//�������������������Ϣ
	HTTP_NETENENT_FEEDBACKINFO = 8,    //��¼�û�������Ϣ
	HTTP_NETENENT_GETNOFRIENDINFO = 83,	// ��÷Ǻ�����ϸ��Ϣ   ͨ������������ 
	HTTP_NETENENT_GETLIFEPRICE = 300,	//��ȡ��������������Ϣ
	HTTP_NETENENT_BUYLIFE = 301,	//��������
	HTTP_NETENENT_HANDSELLIFE = 302,	//��������
	HTTP_NETENENT_GETHANDSELLIFE = 303, //���������������Ϣ
	HTTP_NETENENT_ACCEPTLIFE = 304,	//��ȡ�û�������Ϣ
	HTTP_NETENENT_CONSUMELIFE = 305, //��������
	HTTP_NETENENT_REMOVESYSLIFE = 306,	//ɾ��ϵͳ��������
	HTTP_NETENENT_ADDSYSLIFE = 307,	//���ϵͳ��������
	HTTP_NETENENT_GETPROPINFO = 400,	//��ȡ��Ϸ����������Ϣ
	HTTP_NETENENT_BUYPROP = 401,	//�������
	HTTP_NETENENT_HANDSELPROP = 402,	//���͵���
	HTTP_NETENENT_GETHANDSELPROP = 403,	//������͵��ߵ���Ϣ
	HTTP_NETENENT_ACCEPTPROP = 404,	//��ȡ�����û�������Ϣ
	HTTP_NETENENT_CLAIMPROP = 405,	//��Ҫ����
	HTTP_NETENENT_GETCLAIMEDPROP = 406,		//�����Ҫ���ߵ���Ϣ
	HTTP_NETENENT_ACCEPTCLAIMEPROP = 407,	//��ȡ��Ҫ�û�������Ϣ
	HTTP_NETENENT_CONSUMEPROP = 408,	//���ĵ���
	HTTP_NETENENT_GETUSERPROP = 409,	//ͨ���û�ID�͵���ID��ȡ�û�������Ϣ
	HTTP_NETENENT_GETCHATRECORD = 410,	//ͨ���û�ID��ȡ�û�������ʷ��Ϣ
	HTTP_NETENENT_REFUSECLAIMEDPROP = 411,			//�ܾ��û���Ҫ������Ϣ
	HTTP_NETENTNT_GETNOTICEMSG = 700,			// ��ȡ������Ϣ
	HTTP_NETENTNT_SYSTEMGIVEPROP = 412,		//ϵͳ���͵���
	HTTP_NETENTNT_GEMBUYLIFE = 309,
	HTTP_NETENTNT_INVITEFRIENDMSG = 1303,	// ��ȡ��Ӻ�����Ϣ
	HTTP_NETENTNT_GETMYALLMESSAGE = 312,	// ����ҵ���Ϣ
	HTTP_NETENTNT_SEACHFRIENDRESULT = 1306, //�������ѽ��
	HTTP_NETENTNT_GEMBUYVIP = 16,			//vip ����
	HTTP_NETENTNT_BUYFRIENDLIMIT = 1308,		// �������
	HTTP_NETENTNT_GETFRIENDLIST = 1300,		// ��ú����б�
	HTTP_NETENTNT_UNLOCKMAINTASK = 1703,	// ������������
	HTTP_NETENTNT_GETMYWORLDRANKED = 23,	// ����ҵ���������
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

		void msgForGetLifePrice(CCHttpClient *sender, CCHttpResponse *response);//��������۸�
		void msgForBuyLife(CCHttpClient *sender, CCHttpResponse *response);//��������
		void msgForHandselLife(CCHttpClient *sender, CCHttpResponse *response); // ������
		void msgForGetHandselLife(CCHttpClient *sender, CCHttpResponse *response); //�����͵�����
		void msgForAcceptLife(CCHttpClient *sender, CCHttpResponse *response);//�Ӱ����͵�����
		void msgForConsumeLife(CCHttpClient *sender, CCHttpResponse *response);// ��������
		void msgForRemoveSysLife(CCHttpClient *sender, CCHttpResponse *response);
		void msgForAddSysLife(CCHttpClient *sender, CCHttpResponse *response);
		void msgForGetPropInfo(CCHttpClient *sender, CCHttpResponse *response);// ��õ�����Ϣ
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
		//������ٴ�������
		void msgForEnergyUseNum(CCHttpClient *sender, CCHttpResponse *response);
		//���
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

		//�����ؿ�
		void msgForUnlockLevel(CCHttpClient *sender, CCHttpResponse *response);

		// ǩ�����
		void msgForSignIn(CCHttpClient *sender, CCHttpResponse *response);
		void msgForBuyRetroactive(CCHttpClient *sender, CCHttpResponse *response);

		//ת�̽�����ȡ
		void msgForRouletteReward(CCHttpClient *sender, CCHttpResponse *response);

		//������߳ɹ���ʾ
		void BuySuccessTips();
		void FuncAfterTips(CCNode* node);

	public:
		static bool analyseResponse(CCHttpResponse *response);
		void msgForRoulettePercent( CCHttpClient *sender, CCHttpResponse *response );
		//		static void msgFor3PartyGetNoFriendInfo();

		//�ռ����ǽ�����ȡ���ݻص�
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
		static void sendHandselLifeMsg(int myId, int friendId);//����������
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

		// �������
		static void sendgetMyAllMsgForGuest(int userid, int page = 1, int limit = 60);
		static void sendgetInviteFriendMsgForGuest(int userId, int page = 1, int limit = 40);
		static void sendAcceptAddFriendForGuestMsg(int myId, int friendId);
		static void sendDelFriendForGuestMsg(int myId, int friendId);
		static void sendBuyFriendlimitForMsg(int myId);

		static void sendNoAcceptAddFriendForGuestMsg(int myId, int friendId);
		static void sendCleanAddFriendForGuestMsg(int myId);
		static void sendSeachFriendForGuestMsg(int userId, char*condition, int page = 1, int limit = 40);
		static void sendGetSingleLevelResult(int userid, int level, int page = 1, int limit = 100);

		//���͵�ǰ��������
		static void sendEnergyNumMsg(int myid,int num);
		static void sendEnergyUseNumMsg(int userId);
		//
		static void sendMagicLampTimeRequest(int userId);
		static void sendUseMagicLampTimeRequest(int userId);


		// Gem buy
		static void sendGemBuyVip(int myid, int vipLevel,int vipStone);
		static void sendGemBuyLife(int myid, int lifenum);
		static void sendGemBuyProp(int myid, int propid, int propnum, int candyType = 1);// ʹ�û��ң�1����ʯ��2���ǹ��ң�����Ĭ��Ϊ1
		static void sendGemBuySkill(int myid);
		static void sendUpdateGem(int myid, int buytype);
		static void sendGetSingleLevelResultInMap(int userid, int level, int page = 1, int limit = 100);
		//���
		static void sendGemBuyPackage(int myid, int packageid);


		static void sendRewardVip(int myid);

		// task
		static void sendGetSystemTask(int myid);
		static void sendSubmitTask(int myid, int taskid, int num);
		static void sendGetRewardTask(int myid, int taskid, int starnum);
		static void sendUnLockTask(int myid, int taskid);

		//��world ranked
		static void sendGetWorldRanked(int myid);
		
		//���ؿ�ʧ��
		static void sendLevelFail(int myid, int level);

		//��ǩ�����
		static void sendSignInMsg( int myid ,int isreple= 0); //����ǩ����Ϣ
		static void sendBuyRetroactiveMsg(int myid);	//������ǩ����

		//�����ؿ�
		static void sendUnlockLevel(int myid,int gemnum,int level);

		//ת����ȡ����
		static void sendRouletteReward(int myid,int wupin_id);
		static void sendRoulettePercentReq();

		//��ȡ�ռ����ǽ���
		static void sendReceiveCollectReward(int userid,int maxLvl,int receiveType);

		

private:
		static ResponseMgr responseMgr;

};


#endif
