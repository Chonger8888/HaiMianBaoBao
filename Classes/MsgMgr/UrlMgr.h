#ifndef URL_MGR__H
#define URL_MGR__H

#include "cocos2d.h"
 USING_NS_CC;

#define URL_STRING_LEN			1024*3

class UrlMgr
{
	private:
		static void initUrlString(void);
		static void updateUrlString(const char *type, const char *value, bool isFinish = false);
		
	public:
		static char *getConnectUrl(int userId);
		static char *getUpdataGameUrl(int ver);
		static char *getSoundOutLoginUrl(const char* idx, const char* channel);
		static char *getRegeditUser(const char* idx, const char* channel1, const char* channel2, const char* version);
		static char *getLogOnUrl(const char *idx, const char* version, const char* channel);
		static char *getLevelScoreUrl(int userId,  int level,  int score, int candynum);
		static char *getGetLifePriceUrl(void);
		static char *getBuyLifeUrl(int userId, int lifeNum, int lifePrice);
		static char *getHandselLifeUrl(int myId, int friendId);
		static char *getGetHandselLifeMsgUrl(int userId, int page, int limit);
		static char *getAcceptLifeUrl(int myId, int givenId, int friendId);
		static char *getConsumeLifeUrl(int myId, int num);
		static char *getRemoveSysLifeUrl(int myId);
		static char *getAddSysLifeUrl(int myId);
		static char *getGetPropInfoUrl(int propId); 
		static char *getBuyPropUrl(int userId);
		static char *getMagicLampTimeUrl(int userId);
		static char *getUseMagicLampUrl(int userId);
		static char *getEnergyNumUrl(int userId,int num);
		static char *getEnergyUseNumUrl(int userId);
		static char *getHandselPropUrl(int myId, int friendId, int propId, int propPrice, int propNum);
		static char *getGetHandselPropUrl(int userId);
		static char *getAcceptPropUrl(int myId, int friendId, int givenId);
		static char *getClaimPropUrl(int myId, int friendId, int propId, int propPrice, int propNum);
		static char *getGetClaimedPropUrl(int userId);
		static char *getAcceptClaimedPropUrl(int myId, int friendId, int claimedId);
		static char *getConsumePropUrl(int userId, int propId, int propNum);
		static char *getGetUserPropUrl(int userId, int propId);
		static char *getGetChatRecordUrl(int userId );
		static char *getRefuseClaimedPropUrl(int myId, int friendId, int claimedId);
		static char *getAllAcceptUserHandselUrl(int myId);
		static char *getNoFriendInfoUrl(char* friendidx);
		static char *getFilterNoFriendUrl(char* myIdx, char* nofriendidx);
		static char *getInviteFriendUrl(char* myIdx, char* nofriendidx);
		static char *getInviteFriendForUrl(int myIdx, int nofriendidx);
		static char *getFeedbackInfoUrl(int userId, const char* info);
		static char *getNoticeDataUrl(void);
		static char *getChitchatStUrl(void);
		static char *getGameStateUrl(int myid, int state);
		static char *getSystemGiveProp(int myid, int propid);
		static char *getMyInformationUrl(int myid, int qq, int sex, char* nickname);
		static char *getSystemHeadUrl(void);
		static char *getGetFriendInfoUrl(int userId, int page, int limit);
		static char *getGetWorldFriendInfoUrl();
		static char *getGetNoFriendInfoUrl(int userId, int page, int limit);
		static char *getInviteFriendForGuestUrl(int myid, int invateid);
		static char *getGemBuyVipUrl(int userid, int vipLevel,int vipStone);
		static char *getGemBuyLifeUrl(int userid, int lifenum);
		static char *getGemBuyPropUrl(int userid, int propid, int propnum, int candyType);
		static char *getGemBuySkillUrl(int userid);
		static char *getGemBuyPackageUrl(int userid,int packid);
		static char *getUpdateGemUrl(int userid);

		static char *getMyAllMsgUrlForGuest(int userId, int page, int limit);
		static char *getgetInviteFriendMsgUrlForGuest(int userId, int page, int limit);
		static char *getAcceptAddFriendForGuestUrl(int myId, int friendId);
		static char *getDelFriendForGuestUrl(int myId, int friendId);
		static char *getBuyFriendLimitUrl(int myid);
		static char *getNoAcceptAddFriendForGuestUrl(int myId,int friendId);
		static char *getCleanAddFriendForGuestUrl(int myId, int type = 1);
		static char *getSeachFriendForGuestUrl(int userId, char*condition, int page, int limit);


		static char *getSingleLevelReultUrl(int userid, int level, int page, int limit);
		static char *getRegeditChatUserUrl( const char* nickname, const char* idx, const char* packpag);

		// task
		static char *getGetSystemTaskUrl(int myid);
		static char *getSubmitTaskUrl(int myid, int tasktape, int num);
		static char *getGetRewardTaskUrl(int myid, int taskid, int starnum);
		static char *getUnllockTaskUrl(int myid, int taskid);

		//
		static char * getSendLevelFailUrl(int userid,int level);

		static char *getWorldRankedUrl(int userid);
		static char* getVipRewardUrl(int userid);
		static char* getUnlockLevelUrl(int userid,int gemnum,int level);

		//　签到相关
		static char* getSignInMsg(int userid, int isreple);
		static char* getBuyRetroactiveMsg(int userid);

		static char* getRouletteRewardUrl(int userid,int wupin_id);
		static char* getRoulettePercentUrl();	//转盘概率

		static char* getReceiveStarsRewardUrl(int userid,int maxLvl,int receiveType);
		

private:
		static char urlString[URL_STRING_LEN];
};

#endif
