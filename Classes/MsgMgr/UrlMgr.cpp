#include "UrlMgr.h"

#include "CommonMacro.h"
#include "AnalyseJson.h"

#define WEME_PHP_URL				"http://weme.wemepi.com/1.0.0/dispatch.php?"

char UrlMgr::urlString[URL_STRING_LEN] = {0};

void UrlMgr::initUrlString(void)
{
	memset(&urlString[0], 0, URL_STRING_LEN);
	sprintf(urlString, CANDY_PHP_ADD, CANDY_CURRENT_VERSIONS);
}

void UrlMgr::updateUrlString(const char *type, const char *value, bool isFinish)
{
	memcpy(&urlString[strlen(urlString)], (char *)type, strlen(type));
	urlString[strlen(urlString)] = '=';
	memcpy(&urlString[strlen(urlString)], (char *)value, strlen(value));
	urlString[strlen(urlString)] = isFinish?'\0':'&';
}

char* UrlMgr::getConnectUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","19");
	updateUrlString("user_id",CCString::createWithFormat("%s",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getSoundOutLoginUrl(const char* idx, const char* channel )
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","13");
	updateUrlString("idx",CCString::createWithFormat("%s",idx)->getCString());
	updateUrlString("e_market_signature",CCString::createWithFormat("%s",channel)->getCString(),true);
	return urlString;
}

char* UrlMgr::getRegeditUser( const char* idx, const char* channel1, const char* channel2, const char* version )
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","7");
	updateUrlString("idx",CCString::createWithFormat("%s",idx)->getCString());
	updateUrlString("e_market_signature",CCString::createWithFormat("%s",channel1)->getCString());
	updateUrlString("channel",CCString::createWithFormat("%s",channel2)->getCString());
	updateUrlString("version",CCString::createWithFormat("%s",version)->getCString(),true);
	return urlString;
}


char* UrlMgr::getLogOnUrl(const char *idx, const char* version, const char* channel)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","0");
	updateUrlString("idx",idx);
	updateUrlString("version",version);
	updateUrlString("channel",channel, true);
	return urlString;
}

char* UrlMgr::getLevelScoreUrl(int userId,  int level,  int score, int candynum)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","1");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("game_level",CCString::createWithFormat("%d",level)->getCString());
	updateUrlString("number",CCString::createWithFormat("%d",score)->getCString());
	updateUrlString("candynum",CCString::createWithFormat("%d",candynum)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetLifePriceUrl(void)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","300",true);
	return urlString;
}

char* UrlMgr::getBuyLifeUrl(int userId, int lifeNum, int lifePrice)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","301");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("buy_life_number",CCString::createWithFormat("%d",lifeNum)->getCString());
	updateUrlString("buy_life_price",CCString::createWithFormat("%d",lifePrice)->getCString(),true);
	return urlString;
}


// char* UrlMgr::getGiveFriendLifeUrlForGuest(int userid, int friendid)
// {
// 	initUrlString();
// 	updateUrlString("v_class","300");
// 	updateUrlString("v_cmd","302");
// 	updateUrlString("userid_myself",CCString::createWithFormat("%d",userid)->getCString());
// 	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendid)->getCString(),true);
// 	return urlString;
// }

char* UrlMgr::getHandselLifeUrl(int myId, int friendId)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","302");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getAcceptLifeUrl(int myId, int givenId, int friendId)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","304");
	updateUrlString("id",CCString::createWithFormat("%d",givenId)->getCString());
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_other",CCString::createWithFormat("%d",friendId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getConsumeLifeUrl(int myId, int num)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","305");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("life_consume_number",CCString::createWithFormat("%d",num)->getCString(),true);
	return urlString;
}

char* UrlMgr::getRemoveSysLifeUrl(int myId)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","306");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getAddSysLifeUrl(int myId)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","307");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetPropInfoUrl(int propId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","400");
	updateUrlString("product_id",CCString::createWithFormat("%d",propId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getBuyPropUrl(int userId )
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","308");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getMagicLampTimeUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","1000");
	updateUrlString("v_cmd","1007");
	updateUrlString("user_id",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getUseMagicLampUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","1000");
	updateUrlString("v_cmd","1005");
	updateUrlString("user_id",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getEnergyNumUrl(int userId,int num )
{
	initUrlString();
	updateUrlString("v_class","1000");
	updateUrlString("v_cmd","1000");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("skill_one_num",CCString::createWithFormat("%d",num)->getCString(),true);
	return urlString;
}
char* UrlMgr::getEnergyUseNumUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","1000");
	updateUrlString("v_cmd","1002");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}


char* UrlMgr::getHandselPropUrl(int myId, int friendId, int propId, int propPrice, int propNum)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","402");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propId)->getCString());
	updateUrlString("product_price",CCString::createWithFormat("%d",propPrice)->getCString());
	updateUrlString("product_number",CCString::createWithFormat("%d",propNum)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetHandselPropUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","403");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getAcceptPropUrl(int myId, int friendId,int givenId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","404");
	updateUrlString("id",CCString::createWithFormat("%d",givenId)->getCString());
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_other",CCString::createWithFormat("%d",friendId)->getCString(), true);
	return urlString;
}

char* UrlMgr::getClaimPropUrl(int myId, int friendId, int propId, int propPrice, int propNum)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","405");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propId)->getCString());
	updateUrlString("product_price",CCString::createWithFormat("%d",propPrice)->getCString());
	updateUrlString("product_number",CCString::createWithFormat("%d",propNum)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetClaimedPropUrl(int userId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","406");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
	
}

char* UrlMgr::getAcceptClaimedPropUrl(int myId, int friendId, int claimedId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","407");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_other",CCString::createWithFormat("%d",friendId)->getCString());
	updateUrlString("id",CCString::createWithFormat("%d",claimedId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getRefuseClaimedPropUrl(int myId, int friendId, int claimedId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","411");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_other",CCString::createWithFormat("%d",friendId)->getCString());
	updateUrlString("id",CCString::createWithFormat("%d",claimedId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getInviteFriendUrl(char* myIdx, char* nofriendidx)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","5");
	updateUrlString("owner_idx",CCString::createWithFormat("%s",myIdx)->getCString());
	updateUrlString("invite_friend_idxs",CCString::createWithFormat("%s",nofriendidx)->getCString(), true);
	return urlString;

}

char* UrlMgr::getInviteFriendForUrl(int myIdx, int nofriendidx)
{
	initUrlString();
	updateUrlString("v_class","1300");
	updateUrlString("v_cmd","1302");
	updateUrlString("owner_idx",CCString::createWithFormat("%d",myIdx)->getCString());
	updateUrlString("invite_friend_idxs",CCString::createWithFormat("%d",nofriendidx)->getCString(), true);
	return urlString;

}

char* UrlMgr::getAllAcceptUserHandselUrl(int myId)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","4");
	updateUrlString("userid",CCString::createWithFormat("%d",myId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getNoFriendInfoUrl(char* friendidx)
{
	//initUrlString();
	memset(&urlString[0], 0, URL_STRING_LEN);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sprintf(urlString, CANDY_PHP_ADD,  CANDY_CURRENT_VERSIONS );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	sprintf(urlString, CANDY_PHP_ADD, CANDY_CURRENT_VERSIONS);
#endif

	updateUrlString("v_class","0");
	updateUrlString("v_cmd","83");
	updateUrlString("nofriend_idx",CCString::createWithFormat("%s",friendidx)->getCString(),true);
	return urlString;
}

char* UrlMgr::getFilterNoFriendUrl(char* myIdx, char* nofriendidx)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","6");
	updateUrlString("owner_idx",CCString::createWithFormat("%s",myIdx)->getCString());
	updateUrlString("invite_friend_idxs",CCString::createWithFormat("%s",nofriendidx)->getCString(), true);
	return urlString;
}


char* UrlMgr::getConsumePropUrl(int userId, int propId, int propNum)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","408");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propId)->getCString());
	updateUrlString("product_number",CCString::createWithFormat("%d",propNum)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetUserPropUrl(int userId, int propId)
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","409");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getGetChatRecordUrl(int userId )
{
	initUrlString();
	updateUrlString("v_class","400");
	updateUrlString("v_cmd","410");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(),true);
	return urlString;
}

char* UrlMgr::getFeedbackInfoUrl(int userId, const char* info)
{
	initUrlString();
	updateUrlString("v_class","0");
	updateUrlString("v_cmd","8");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("bug_info",CCString::createWithFormat("%s",info)->getCString(),true);
	return urlString;
}

char* UrlMgr::getNoticeDataUrl(void)
{
	initUrlString();
	updateUrlString("v_class", "700");
	updateUrlString("v_cmd", "200", true);
	return urlString;
}

char* UrlMgr::getChitchatStUrl(void)
{
	initUrlString();
	updateUrlString("v_class", "3");
	updateUrlString("v_cmd", "200", true);
	return urlString;
}

char* UrlMgr::getGameStateUrl(int myid, int status)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "9");
	updateUrlString("userid",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("status",CCString::createWithFormat("%d",status)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getSystemGiveProp(int myid, int propid)
{
	initUrlString();
	updateUrlString("v_class", "400");
	updateUrlString("v_cmd", "412");
	updateUrlString("userid",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propid)->getCString());
	updateUrlString("product_number",CCString::createWithFormat("%d",1)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getMyInformationUrl(int myid, int qq, int sex, char* nickname)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "10");
	updateUrlString("userid",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("qq",CCString::createWithFormat("%d",qq)->getCString());
	updateUrlString("gender",CCString::createWithFormat("%d",sex)->getCString());
	updateUrlString("nickname",CCString::createWithFormat("%s",nickname)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getSystemHeadUrl(void)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "11",true);
	return urlString;
}

char* UrlMgr::getGemBuyVipUrl(int userid, int vipLevel,int vipStone)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "16");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());
	updateUrlString("vip_level",CCString::createWithFormat("%d",vipLevel)->getCString());	
	updateUrlString("vip_stone",CCString::createWithFormat("%d",vipStone)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getGemBuyLifeUrl(int userid, int lifenum)
{
	initUrlString();
	updateUrlString("v_class", "300");
	updateUrlString("v_cmd", "309");
	updateUrlString("userid",CCString::createWithFormat("%d",userid)->getCString());
	updateUrlString("buy_life_number",CCString::createWithFormat("%d",lifenum)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getGemBuyPropUrl(int userid, int propid, int propnum, int candyType)
{
	initUrlString();
	updateUrlString("v_class", "400");
	updateUrlString("v_cmd", "413");
	updateUrlString("userid",CCString::createWithFormat("%d",userid)->getCString());
	updateUrlString("product_id",CCString::createWithFormat("%d",propid)->getCString());
	updateUrlString("product_number",CCString::createWithFormat("%d",propnum)->getCString());	
	updateUrlString("currency_type",CCString::createWithFormat("%d",candyType)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getGemBuySkillUrl(int userid)
{
	initUrlString();
	updateUrlString("v_class", "1000");
	updateUrlString("v_cmd", "1006");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString(),true);	
	return urlString;
}
char* UrlMgr::getGemBuyPackageUrl(int userid,int packid)
{
	initUrlString();
	updateUrlString("v_class", "400");
	updateUrlString("v_cmd", "415");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("pack_id",CCString::createWithFormat("%d",packid)->getCString(),true);	
	return urlString;
}
char* UrlMgr::getVipRewardUrl(int userid)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "22");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString(),true);	
	return urlString;
}
char* UrlMgr::getUnlockLevelUrl(int userid,int gemnum,int level)
{
	initUrlString();
	updateUrlString("v_class", "800");
	updateUrlString("v_cmd", "500");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("num",CCString::createWithFormat("%d",gemnum)->getCString());	
	updateUrlString("game_level",CCString::createWithFormat("%d",level)->getCString(),true);	
	return urlString;
}
char * UrlMgr::getUpdateGemUrl(int userid)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "12");
	updateUrlString("userid",CCString::createWithFormat("%d",userid)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getSendLevelFailUrl(int userid,int level)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "20");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("game_level",CCString::createWithFormat("%d",level)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getGetFriendInfoUrl(int userId, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1300");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString(),true);
	return urlString;
}
char * UrlMgr::getGetWorldFriendInfoUrl()
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "27",true);
	return urlString;
}
char * UrlMgr::getGetNoFriendInfoUrl(int userId, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1301");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString(),true);
	return urlString;
}

char * UrlMgr::getInviteFriendForGuestUrl(int myid, int invateid)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1302");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",invateid)->getCString(),true);
	return urlString;
}

//http://guest.candy.weme-game.com/2.0.1.guest/dispatch.php?v_class=1300&v_cmd=1303&userid=54457&page=1&limit=40
char *UrlMgr::getgetInviteFriendMsgUrlForGuest(int userId, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1303");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString(),true);
	return urlString;
}

char *UrlMgr::getMyAllMsgUrlForGuest(int userId, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "300");
	updateUrlString("v_cmd", "312");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString(), true);
	return urlString;
}

//http://guest.candy.weme-game.com/2.0.1.guest/dispatch.php?v_class=300&v_cmd=303&userid=2&page=1&limit=40
char* UrlMgr::getGetHandselLifeMsgUrl(int userId, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class","300");
	updateUrlString("v_cmd","303");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString(),true);
	return urlString;
}

//http://guest.candy.weme-game.com/2.0.1.guest/dispatch.php?v_class=1300&v_cmd=1304&userid_myself=54457&userid_friend=44238
char *UrlMgr::getAcceptAddFriendForGuestUrl(int myId, int friendId)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1304");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString(),true);
	return urlString;
}

char *UrlMgr::getDelFriendForGuestUrl(int myId, int friendId)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1307");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString(),true);
	return urlString;
}

//http://guest.candy.weme-game.com/2.0.1.guest/dispatch.php?v_class=1300&v_cmd=1305&userid_myself=54457&userid_friend=44238
char *UrlMgr::getNoAcceptAddFriendForGuestUrl(int myId, int friendId)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1305");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("userid_friend",CCString::createWithFormat("%d",friendId)->getCString(),true);
	return urlString;
}

char *UrlMgr::getCleanAddFriendForGuestUrl(int myId, int type)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1305");
	updateUrlString("userid_myself",CCString::createWithFormat("%d",myId)->getCString());
	updateUrlString("batch_delete",CCString::createWithFormat("%d",type)->getCString(),true);
	return urlString;
}

//http://guest.candy.weme-game.com/2.0.1.guest/dispatch.php?v_class=1300&v_cmd=1306&userid=54457&page=1&limit=40&condition=52954
char *UrlMgr::getSeachFriendForGuestUrl(int userId, char*condition, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1306");
	updateUrlString("userid",CCString::createWithFormat("%d",userId)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString());
	updateUrlString("condition",CCString::createWithFormat("%s",condition)->getCString(),true);
	return urlString;
}

char* UrlMgr::getSingleLevelReultUrl(int userid, int level, int page, int limit)
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "15");
	updateUrlString("userid",CCString::createWithFormat("%d",userid)->getCString());
	updateUrlString("game_level",CCString::createWithFormat("%d",level)->getCString());
	updateUrlString("page",CCString::createWithFormat("%d",page)->getCString());
	updateUrlString("limit",CCString::createWithFormat("%d",limit)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getRegeditChatUserUrl( const char* nickname, const char* idx, const char* packpag )
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "15");
	updateUrlString("idx",CCString::createWithFormat("%s",nickname)->getCString());
	updateUrlString("device_uuid",CCString::createWithFormat("%s",idx)->getCString());
	updateUrlString("group_app_package_name",CCString::createWithFormat("%s",packpag)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getUpdataGameUrl( int ver )
{
	initUrlString();
	updateUrlString("v_class", "4");
	updateUrlString("v_cmd", "200");
	updateUrlString("ver",CCString::createWithFormat("%d",ver)->getCString(),true);
	return urlString;
}

char * UrlMgr::getGetSystemTaskUrl( int myid )
{
	initUrlString();
	updateUrlString("v_class", "1700");
	updateUrlString("v_cmd", "1700");
	updateUrlString("user_id",CCString::createWithFormat("%d",myid)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getSubmitTaskUrl( int myid, int tasktape, int num )
{
	initUrlString();
	updateUrlString("v_class", "1700");
	updateUrlString("v_cmd", "1701");
	updateUrlString("user_id",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("type",CCString::createWithFormat("%d",tasktape)->getCString());
	updateUrlString("num",CCString::createWithFormat("%d",num)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getGetRewardTaskUrl( int myid, int taskid, int starnum)
{
	initUrlString();
	updateUrlString("v_class", "1700");
	updateUrlString("v_cmd", "1702");
	updateUrlString("user_id",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("task_id",CCString::createWithFormat("%d",taskid)->getCString());
	updateUrlString("star_num",CCString::createWithFormat("%d",starnum)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getUnllockTaskUrl( int myid, int taskid )
{
	initUrlString();
	updateUrlString("v_class", "1700");
	updateUrlString("v_cmd", "1703");
	updateUrlString("user_id",CCString::createWithFormat("%d",myid)->getCString());
	updateUrlString("task_id",CCString::createWithFormat("%d",taskid)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getBuyFriendLimitUrl( int myid )
{
	initUrlString();
	updateUrlString("v_class", "1300");
	updateUrlString("v_cmd", "1308");
	updateUrlString("user_id",CCString::createWithFormat("%d",myid)->getCString(),true);	
	return urlString;
}

char * UrlMgr::getWorldRankedUrl( int userid )
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "23");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getSignInMsg( int userid ,int isreple )
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "24");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("is_reple",CCString::createWithFormat("%d",isreple)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getBuyRetroactiveMsg( int userid )
{
	initUrlString();
	updateUrlString("v_class", "0");
	updateUrlString("v_cmd", "25");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getRouletteRewardUrl( int userid,int wupin_id )
{
	initUrlString();
	updateUrlString("v_class", "1000");
	updateUrlString("v_cmd", "1008");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("p_id",CCString::createWithFormat("%d",wupin_id)->getCString(),true);	
	return urlString;
}

char* UrlMgr::getRoulettePercentUrl()
{
	initUrlString();
	updateUrlString("v_class", "1000");
	updateUrlString("v_cmd", "1009",true);
	return urlString;
}

char* UrlMgr::getReceiveStarsRewardUrl( int userid,int maxLvl,int receiveType )
{
	initUrlString();
	updateUrlString("v_class", "800");
	updateUrlString("v_cmd", "600");
	updateUrlString("user_id",CCString::createWithFormat("%d",userid)->getCString());	
	updateUrlString("level",CCString::createWithFormat("%d",maxLvl)->getCString());	
	updateUrlString("type",CCString::createWithFormat("%d",receiveType)->getCString(),true);	

	return urlString;
}




