#include "AnalyseJson.h"
#include "Json.h"
#include "../CommonData/CommonData.h"
#include "../MsgMgr/MsgMgr.h"

#include "../CppCallJava/CppCallJava.h"


// Recording divide sign
#define		CANDY_RECORDING_DIVIDE_SIGN		"^"

//　Recording data
static char* RecordingMsgId[RECODING_MSG_NUM] = 
{
	//(char*)"1321",
	//(char*)"1322",
	//(char*)"1323",
	//(char*)"1324",
	//(char*)"1325",
	//(char*)"1326",
	//(char*)"1327",
	//(char*)"1328",
	//
	//(char*)"2000",
	//(char*)"2001",
	//(char*)"2002",
	//(char*)"2003",
	//(char*)"2004",
	//(char*)"2005",
	//(char*)"2006",
	//(char*)"2007",
	//(char*)"2008",
	//(char*)"2009",
	//(char*)"2010",
	//(char*)"2011",
	//(char*)"2012",
	//(char*)"2013",
	//(char*)"2014",
	//(char*)"2015",
	//(char*)"2016",
	//(char*)"2017",
	//(char*)"2018",
	//(char*)"2019",

	//(char*)"2021",
	//(char*)"2022",
	//(char*)"2023",
	//(char*)"2024",
	//(char*)"2025",
	//(char*)"2026",
	//(char*)"2027",
	//(char*)"2028",
	//(char*)"2029",
	//(char*)"2030",
	//(char*)"2031",
	//(char*)"2032",
	//(char*)"2033",
	//(char*)"2034",
	//(char*)"2035",
	//(char*)"2036",
	//(char*)"2037",
	//(char*)"2038",
	//(char*)"2039",
	//(char*)"2040",

	//// 1.2版本
	//(char*)"2041",
	//(char*)"2042",
	//(char*)"2043",
	//(char*)"2044",
	//(char*)"2045",
	//(char*)"2046",
	//(char*)"2047",
	//(char*)"2048",
	//(char*)"2049",
	//(char*)"2050",
	//(char*)"2051",
	//(char*)"2052",
	//(char*)"2053",
	//(char*)"2054",
	//(char*)"2055",
	//(char*)"2056",
	//(char*)"2057",
	//(char*)"2058",
	//(char*)"2059",
	//(char*)"2060",
	//(char*)"2061",
	//(char*)"2062",
	//(char*)"2063",
	//(char*)"2064",
	//(char*)"2065",
	//(char*)"2066",
	//(char*)"2067",
	//(char*)"2068",
	//(char*)"2069",
	//(char*)"2070",
	//(char*)"2071",
	//(char*)"2072",
	//(char*)"2073",
	//(char*)"2074",
	//(char*)"2075",
	//(char*)"2076",
	//(char*)"2077",
	//(char*)"2078",
	//(char*)"2079",
	//(char*)"2080",
	//(char*)"2081",
	//(char*)"2082",
	//(char*)"2083",
	//(char*)"2084",
	//(char*)"4001",
	//(char*)"4002",
	//(char*)"4003",
	//(char*)"4004",
	//(char*)"4005",
	//(char*)"4006",
	//(char*)"4007",
	//(char*)"1319",
	//(char*)"4008",
	//(char*)"4009",
	//(char*)"4010",
	//(char*)"4011",
	//(char*)"4012",
	//(char*)"1313",
	//(char*)"4014",
	//(char*)"4015",
	//(char*)"4016",
	//(char*)"4017",
	//(char*)"4018"

		"1321",	//mini版本记录点
		"1322",
		"1323",
		"1324",
		"1325",
		"1326",
		"1327",
		"2013",
		"2018",
		"2029",
		"2032",
		"1002",
		"1003",
		"1004",
		"1005",
		"1006",
		"1007"
};


char 	AnalyseJson::jsonString[JSON_STRING_LEN] = {0};
char	AnalyseJson::CandPicPath[512] = {0};

UpdataGameInfo			AnalyseJson::updataData = {0};
UserLogOnSr 			AnalyseJson::logOnMsg = {0};
UserLevelScoreStr		AnalyseJson::levelScoreMsg = {0};
UserFriendStr			AnalyseJson::worldFriendInfoMsg = {0};
UserFriendStr			AnalyseJson::friendInfoMsg = {0};
UserNoFriendStr			AnalyseJson::nofriendInfoMsg = {0};
UserLifePriceStr 		AnalyseJson::lifePriceMsg = {0};
UserBuyLifeStr			AnalyseJson::buyLifeMsg  = {0};
UserHandselLifeStr		AnalyseJson::handselLifeMsg  = {0};
UserGetHandselMsgStr	AnalyseJson::getHandselMsg  = {0};
UserNoFriendStr			AnalyseJson::InviteFriendMsgList  = {0};
UserNoFriendStr			AnalyseJson::SeachFriendList  = {0};
UserAcceptLifeStr		AnalyseJson::acceptLifeMsg  = {0};
UserConsumeLifeStr		AnalyseJson::consumeLifeMsg = {0};
UserRemoveSysLifeStr	AnalyseJson::removeSysLifeMsg = {0};
UserAddSysLifeStr		AnalyseJson::addSysLifeMsg = {0};
UserPropsInfoStr		AnalyseJson::propInfoMsg = {0};
UserBuyPropInfoStr		AnalyseJson::buyPropInfo = {0};
UserHandselPropStr		AnalyseJson::handselPropInfo = {0};
UserGetHandselPropStr	AnalyseJson::handselPropMsg = {0};
UserAcceptPropStr		AnalyseJson::acceptPropMsg = {0};
UserClaimPropStr		AnalyseJson::claimPropMsg = {0};
UserGetClaimedPropStr	AnalyseJson::getClaimedPropMsg = {0};
UserAcceptClaimedPropStr AnalyseJson::acceptClaimedPropMsg = {0};
UserConsumePropStr		AnalyseJson::consumePropStr = {0};
UserGetUserPropStr		AnalyseJson::getUserPropStr = {0};
UserPropRecordStr		AnalyseJson::propRecordStr = {0};
UserRefuseClaimPropStr	AnalyseJson::refuseClaimPropStr = {0};
UserAllAcceptHandselStr	AnalyseJson::allAcceptHandsel = {0};
UserFilterFriendStr		AnalyseJson::filterFriend = {0};
UserNoticeStr			AnalyseJson::noticeStr = {0};
UserGameState			AnalyseJson::gamestate = {0};
SystemGivePropStr		AnalyseJson::giveProp = {0};
UserEnergyUseTime		AnalyseJson::energyUsetime = {0};
MagicLampInfo			AnalyseJson::magicLampInfo = {0};
SystemHeadUrlStr		AnalyseJson::SysHeadUrl = {0};
UserSingleLevelResultStr		AnalyseJson::SingleLevelResultStr = {0}; 
SystemTask				AnalyseJson::taskTable = {0};
FunctionUnLockLevel		AnalyseJson::unLockConfig = {0};
SignInConfigStr			AnalyseJson::signInConfigStr = {0};

std::string AnalyseJson::myDevice = "";
std::string AnalyseJson::myUserId = "";
std::string AnalyseJson::Recordingdata = "";
std::string AnalyseJson::MyCurrVersion = "";
std::string AnalyseJson::MyCurrchannel = "";
std::vector<RouleteRatio>	AnalyseJson::RouleteRatioVec;
void AnalyseJson::SaveDeviceAndUid(char* device, char* uid, char* version, char* channel)
{
	myDevice = device;
	myUserId = uid;
	MyCurrVersion = version;
	MyCurrchannel = channel;
}

void AnalyseJson::SavePlatfromData( string idx, string channel, string version, string packpagname, string updataver )
{
	AnalyseJson::logOnMsg.baseInfo.idx = idx;
	AnalyseJson::logOnMsg.baseInfo.channel = channel;
	AnalyseJson::logOnMsg.baseInfo.version = version;																								
	AnalyseJson::logOnMsg.baseInfo.packpag = packpagname;																							
	AnalyseJson::logOnMsg.baseInfo.updataver = updataver;																							
}																																					
																																					
void AnalyseJson::setRecordHeadMsg(RecordingMsgType type )																							
{																																					
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)																										
	SaveDeviceAndUid( "5152546216", "35", CANDY_CURRENT_VERSIONS ,"00000" );																		
#endif																																				
	Recordingdata.clear();																															
	Recordingdata.append( (char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.id)->getCString() );								
	Recordingdata.append( CANDY_RECORDING_DIVIDE_SIGN );																							
	Recordingdata.append( RecordingMsgId[type] );																									
	Recordingdata.append( CANDY_RECORDING_DIVIDE_SIGN );																							
	Recordingdata.append( AnalyseJson::logOnMsg.baseInfo.idx.c_str() );																				
}																																					

void AnalyseJson::setRecordMsgAppend(const  char* string)
{
	Recordingdata.append( CANDY_RECORDING_DIVIDE_SIGN );
	if(string)
		Recordingdata.append( string );
}
	
void AnalyseJson::setRecordingMsg(RecordingMsgType type, const char* string1,const char *string2, 
							const char *string3,const char *string4,const char *string5)
{
#ifdef CANDY_STATISITICAL_DATA

	if(type <0 || type>=RECODING_MSG_NUM)
		return ;
	setRecordHeadMsg(type);
	setRecordMsgAppend(string1);
	setRecordMsgAppend(string2);
	setRecordMsgAppend(string3);
	setRecordMsgAppend(string4);
	setRecordMsgAppend(string5);
	//CppCallJava::patchTracker( Recordingdata.c_str() );
#endif
}

bool AnalyseJson::setSoundOutMsg( void )
{
	bool ret = false;

	std::string nidx;
	int nflag = 0;
	Json* root	= Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* idx = Json_getItem(content, "idx");
		if(!idx|| idx->type!=Json_String)
			break;
		nidx = idx->valuestring;

		Json* flag = Json_getItem(content, "flag");
		if(!flag|| flag->type!=Json_Number)
			break;
		nflag = flag->valueint;
		AnalyseJson::logOnMsg.baseInfo.isNewUser = flag->valueint;
		// 判断新老用户　: 0老用户　1:新用户　
		if ( nidx == AnalyseJson::logOnMsg.baseInfo.idx )
		{
			//　老用户登录
			if ( 0 == nflag)
			{
				MsgMgr::sendLogOnMsg( AnalyseJson::logOnMsg.baseInfo.idx.c_str() );
			}
			//　新用户注册
			else if ( 1 == nflag )
			{
				//CppCallJava::sendRegeditOrLogin( 1 , AnalyseJson::logOnMsg.baseInfo.id);

				MsgMgr::sendRegeditUser( 
					AnalyseJson::logOnMsg.baseInfo.idx.c_str(), 
					AnalyseJson::logOnMsg.baseInfo.channel.c_str(), 
					AnalyseJson::logOnMsg.baseInfo.channel.c_str(), 
					AnalyseJson::logOnMsg.baseInfo.version.c_str() );

				// 新用户　设置背音乐可播放
				CommonData::setBackgroundState(true);
				CommonData::setSoundEffectState(true);
			}
		}

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setRegeditMsg( void )
{
	bool ret = false;

	std::string nidx;
	int nflag = 0;
	Json* root	= Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* idx = Json_getItem(content, "idx");
		if(!idx|| idx->type!=Json_String)
			break;
		nidx = idx->valuestring;

		Json* userid = Json_getItem(content, "userid");
		if(!userid|| userid->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.baseInfo.id = userid->valueint;

		Json* flag = Json_getItem(content, "flag");
		if(!flag|| flag->type!=Json_Number)
			break;
		nflag = flag->valueint;

		Json* chat_status = Json_getItem(content, "chat_status");
		if(!chat_status|| chat_status->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.baseInfo.Chitchat = chat_status->valueint;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
		AnalyseJson::logOnMsg.baseInfo.Chitchat = 0;
#endif

		//　新注册用户登录
		if ( nidx == AnalyseJson::logOnMsg.baseInfo.idx /*&& 0 == nflag*/ )
		{
			//CppCallJava::getChitNickName();
			MsgMgr::sendLogOnMsg( AnalyseJson::logOnMsg.baseInfo.idx.c_str() );
		}


		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setLogOnMsg(void)
{
	unsigned long file_size = 0;

  	unsigned char *tmp = NULL;
	tmp = CCFileUtils::sharedFileUtils()->getFileData("jsonContent.txt","rb",&file_size);
 
  	if(file_size <=0 || file_size >= JSON_STRING_LEN)
  		return false;
  
  	memcpy(&AnalyseJson::jsonString[0], &(tmp[0]), file_size);
  	AnalyseJson::jsonString[file_size] = '\0';


	bool ret = false;
	Json* root	= Json_create(jsonString);
	CCLog("AnalyseJson::setLogOnMsg %s",jsonString );
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo = Json_getItem(content, "base_info");
		if(!baseInfo|| baseInfo->type!=Json_Object)
			break;

		Json* userid 	= Json_getItem(baseInfo, "userid");
		if(!userid || userid->type!=Json_Number)
			break;
		logOnMsg.baseInfo.id = userid->valueint;

		Json* gender = Json_getItem(baseInfo, "gender");
		if(!gender || gender->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gender= gender->valueint;

		//kksdk
		Json* kksdkOpen = Json_getItem(baseInfo,"open_kk_sdk");
		if (!kksdkOpen || kksdkOpen->type != Json_Number)
		{
			break;
		}
		logOnMsg.baseInfo.openkkSdk = kksdkOpen->valueint;

		//这个在客户端处理，服务器去掉该字段
		logOnMsg.baseInfo.isUsePropToday = 0;

		Json* hasBuySuperPacks = Json_getItem(baseInfo, "has_buy_super_packs");
		if(!hasBuySuperPacks || hasBuySuperPacks->type!=Json_Number)
			break;
		logOnMsg.baseInfo.isBuySuperGift= hasBuySuperPacks->valueint;

		Json* superPackId = Json_getItem(baseInfo, "super_pack_id");
		if(!superPackId || superPackId->type!=Json_Number)
			break;
		logOnMsg.baseInfo.SuperGiftId = superPackId->valueint;


 		Json* qq = Json_getItem(baseInfo, "qq");
 		if(!qq || qq->type!=Json_String)
 			break;
 		logOnMsg.baseInfo.qq= qq->valuestring;

		Json* avatar_upd_times = Json_getItem(baseInfo, "avatar_upd_times");
		if(!avatar_upd_times || avatar_upd_times->type!=Json_Number)
			break;
		logOnMsg.baseInfo.avatar_upd_times= avatar_upd_times->valueint;

		Json* headPicUrl = Json_getItem(baseInfo, "avatar_url");
		if(!headPicUrl || headPicUrl->type!=Json_String)
			break;
		logOnMsg.baseInfo.headPicUrl= headPicUrl->valuestring;

		Json* nickName = Json_getItem(baseInfo, "nickname");
		if(!nickName || nickName->type!=Json_String)
			break;
		logOnMsg.baseInfo.nickName= nickName->valuestring;

		Json* first_login = Json_getItem(baseInfo, "first_login");
		if(!first_login || first_login->type!=Json_Number)
			break;
		logOnMsg.baseInfo.isFirstLogin= first_login->valueint;

		Json* today_lave_turntable_num = Json_getItem(baseInfo, "today_lave_turntable_num");
		if(!today_lave_turntable_num || today_lave_turntable_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.today_Roulette_num= today_lave_turntable_num->valueint;

		Json* turntable_use_candy = Json_getItem(baseInfo, "turntable_use_candy");
		if(!turntable_use_candy || turntable_use_candy->type!=Json_Number)
			break;
		logOnMsg.baseInfo.Roulette_UseCandy= turntable_use_candy->valueint;

		Json* candy_currency = Json_getItem(baseInfo, "candy_currency");
		if(!candy_currency || candy_currency->type!=Json_Number)
			break;
		logOnMsg.baseInfo.candyNum= candy_currency->valueint;

		Json* is_vip = Json_getItem(baseInfo, "is_vip");
		if(!is_vip || is_vip->type!=Json_Number)
			break;
		logOnMsg.baseInfo.isVip= is_vip->valueint;

		Json* vipLen = Json_getItem(baseInfo, "vip_length");
		if(!vipLen || vipLen->type!=Json_Number)
			break;
		logOnMsg.baseInfo.vipLength= vipLen->valueint;

		Json* new_bullentin = Json_getItem(baseInfo, "new_bullentin");
		if(!new_bullentin || new_bullentin->type!=Json_Number)
			break;
		logOnMsg.baseInfo.isNotice= new_bullentin->valueint;

		Json* fail_num = Json_getItem(baseInfo, "fail_num");
		if(!fail_num || fail_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.failNum= fail_num->valueint;

		Json* today_has_receice = Json_getItem(baseInfo, "today_has_receice");
		if(!today_has_receice || today_has_receice->type!=Json_Number)
			break;
		logOnMsg.baseInfo.today_has_receice = today_has_receice->valueint;

		Json* pack_id = Json_getItem(baseInfo, "pack_id");
		if(!pack_id || pack_id->type!=Json_Number)
			break;

 		CommonData::m_GiftIDBuyNow = 4;

		//　签到相关
		Json* registration_card_num = Json_getItem(baseInfo, "registration_card_num");
		if(!registration_card_num || registration_card_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.RetroactiveCardNum= registration_card_num->valueint;

		Json* num_day = Json_getItem(baseInfo, "num_day");
		if(!num_day || num_day->type!=Json_Number)
			break;
		logOnMsg.baseInfo.MaxSignInDay= num_day->valueint;

		Json* should_sign_day = Json_getItem(baseInfo, "should_sign_day");
		if(!should_sign_day || should_sign_day->type!=Json_Number)
			break;
		logOnMsg.baseInfo.practicalSignInDay = should_sign_day->valueint;

		Json* has_sign_day = Json_getItem(baseInfo, "has_sign_day");
		if(!has_sign_day || has_sign_day->type!=Json_Number)
			break;
		logOnMsg.baseInfo.hasSignInDay = has_sign_day->valueint;

		Json* is_reple = Json_getItem(baseInfo, "is_reple");
		if(!is_reple || is_reple->type!=Json_Number)
			break;
		logOnMsg.baseInfo.IsRetroactive = is_reple->valueint;



		Json* lifeInfo = Json_getItem(content, "life_info");
		if(!lifeInfo|| lifeInfo->type!=Json_Object)
			break;

		Json* lifeCountDown 	= Json_getItem(lifeInfo, "life_countdown");
		if(!lifeCountDown || lifeCountDown->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeCountDown= lifeCountDown->valueint;

		Json* life_price 	= Json_getItem(lifeInfo, "life_price");
		if(!life_price || life_price->type!=Json_String)
			break;
		logOnMsg.lifeInfo.price= life_price->valuestring;

		Json* lifeNum 	= Json_getItem(lifeInfo, "life_number");
		if(!lifeNum || lifeNum->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum= lifeNum->valueint;
		if ( 0 > logOnMsg.lifeInfo.lifeNum)
		{
			logOnMsg.lifeInfo.lifeNum = 0;
		}

		Json* propsInfo = Json_getItem(content, "stage_property_info");
		if(!propsInfo|| propsInfo->type!=Json_Array)
			break;

		int i;
		logOnMsg.propInfo.clear();
		for(i =0; i<Json_getSize(propsInfo); i++)
		{
			UserPropInfoStr propInfoStr;

			Json* propInfo = Json_getItemAt(propsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			propInfoStr.id = propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			propInfoStr.num = propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			propInfoStr.name= propName->valuestring;

			Json* price  = Json_getItem(propInfo, "product_price");
			if(!price || price->type!=Json_String)
				break;
			propInfoStr.price = price->valuestring;

			Json* candy_price  = Json_getItem(propInfo, "candy_price");
			if(!candy_price || candy_price->type!=Json_String)
				break;
			propInfoStr.candyprice= candy_price->valuestring;

			Json* currency  = Json_getItem(propInfo, "currency_type");
			if(!currency || currency->type!=Json_Number)
				break;
			propInfoStr.priceType= currency->valueint;


			logOnMsg.propInfo.push_back(propInfoStr);
		}

		if(i <Json_getSize(propsInfo))
			break;

		Json* stagesInfo = Json_getItem(content, "fraction_info");
		if(!stagesInfo|| stagesInfo->type!=Json_Array)
			break;

		logOnMsg.stageInfo.clear();

		int MaxLevel = 0;
		if(Json_getSize(stagesInfo) > 0)
		{
			Json* stageInfo = Json_getItemAt(stagesInfo, Json_getSize(stagesInfo)-1);
			Json* level  = Json_getItem(stageInfo, "game_level");
			if(!level   || level  ->type!=Json_Number)
				break;
			MaxLevel = 225;//level->valueint;
		}

		int j;
		for(i =0, j = 0; i<MaxLevel; i++)
		//for(i =0; i<Json_getSize(stagesInfo); i++)
		{
			UserStageInfoStr stageInfoStr;

			Json* stageInfo = Json_getItemAt(stagesInfo, j);
			if(!stageInfo|| stageInfo->type!=Json_Object)
				break;

			Json* level  = Json_getItem(stageInfo, "game_level");
			if(!level   || level  ->type!=Json_Number)
				break;
			if ( i+1 == level->valueint)
				stageInfoStr.level= level->valueint;
			else 
			{
				stageInfoStr.level = i+1;
				stageInfoStr.score = 0;
				logOnMsg.stageInfo.push_back(stageInfoStr);
				continue;
			}


			Json* score  = Json_getItem(stageInfo, "number");
			if(!score   || score  ->type!=Json_Number)
				break;
			stageInfoStr.score= score->valueint;

			j++;
			logOnMsg.stageInfo.push_back(stageInfoStr);
		}
		logOnMsg.stageInfo.sort();
#if 0
		list<UserStageInfoStr >::iterator start1 = logOnMsg.stageInfo.begin();
		while (start1 != logOnMsg.stageInfo.end())
		{
			UserStageInfoStr v = *start1++;
			CCLog("level %d, score1 %d,score2 %d",v.level, v.score,CommonData::getLevelScore(v.level));
		}
#endif	
		CommonData::m_levelFailNum[CommonData::getMaxLevel() + 1] = logOnMsg.baseInfo.failNum;


		if(i <Json_getSize(stagesInfo))
			break;

		// 过关奖励糖果币配置
		Json* pass_level_add_candy_info = Json_getItem(content, "pass_level_add_candy_info");
		if(!pass_level_add_candy_info|| pass_level_add_candy_info->type!=Json_Object)
			break;

		Json* growth_factor = Json_getItem(pass_level_add_candy_info, "growth_factor");
		if(!growth_factor || growth_factor->type!=Json_Number)
			break;
		logOnMsg.rewardCandyConfig.growth_factor = growth_factor->valuefloat;

		Json* growth_value = Json_getItem(pass_level_add_candy_info, "growth_value");
		if(!growth_value || growth_value->type!=Json_Number)
			break;
		logOnMsg.rewardCandyConfig.growth_value = growth_value->valuefloat;

		Json* one_star = Json_getItem(pass_level_add_candy_info, "one_star");
		if(!one_star || one_star->type!=Json_Number)
			break;
		logOnMsg.rewardCandyConfig.one_star = one_star->valuefloat;

		Json* two_star = Json_getItem(pass_level_add_candy_info, "two_star");
		if(!two_star || two_star->type!=Json_Number)
			break;
		logOnMsg.rewardCandyConfig.two_star = two_star->valuefloat;

		Json* third_star = Json_getItem(pass_level_add_candy_info, "third_star");
		if(!third_star || third_star->type!=Json_Number)
			break;
		logOnMsg.rewardCandyConfig.third_star = third_star->valuefloat;


		// 宝石
		Json* precious_stone_info = Json_getItem(content, "precious_stone_info");
		if(!precious_stone_info|| precious_stone_info->type!=Json_Object)
			break;

		Json* precious_stone_number = Json_getItem(precious_stone_info, "precious_stone_number");
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum= precious_stone_number->valueint;


		Json* cmcc_precious_stone_conf_info = Json_getItem(content, "cmcc_precious_stone_conf_info");
		if(!cmcc_precious_stone_conf_info|| cmcc_precious_stone_conf_info->type!=Json_Array)
			break;

		logOnMsg.preciousConfig.clear();
		for(i =0; i<Json_getSize(cmcc_precious_stone_conf_info); i++)
		{
			PreciousInfoStr preciousConfigStr;

			Json* preciousInfo = Json_getItemAt(cmcc_precious_stone_conf_info, i);
			if(!preciousInfo|| preciousInfo->type!=Json_Object)
				break;

			Json* preciousId  = Json_getItem(preciousInfo, "precious_stone_id");
			if(!preciousId || preciousId->type!=Json_Number)
				break;
			preciousConfigStr.preciousid = preciousId->valueint;


			Json* preciousName  = Json_getItem(preciousInfo, "precious_stone_name");
			if(!preciousName || preciousName->type!=Json_String)
				break;
			preciousConfigStr.preciousname= preciousName->valuestring;

			Json* preciousprice  = Json_getItem(preciousInfo, "precious_stone_price");
			if(!preciousprice || preciousprice->type!=Json_String)
				break;
			preciousConfigStr.preciousprice = preciousprice->valuestring;

			Json* preciousNum  = Json_getItem(preciousInfo, "precious_stone");
			if(!preciousNum || preciousNum->type!=Json_Number)
				break;
			preciousConfigStr.preciousnum = preciousNum->valueint;

			logOnMsg.preciousConfig.push_back(preciousConfigStr);
		}

		if(i <Json_getSize(cmcc_precious_stone_conf_info))
			break;


		//vip信息
		Json* vip_config = Json_getItem(content, "vip_config");
		if(!vip_config|| vip_config->type!=Json_Array)
			break;

		logOnMsg.vipConfig.clear();
		for(i =0; i<Json_getSize(vip_config); i++)
		{
			UserVipInfoStr userVipStr;

			Json* vipInfo = Json_getItemAt(vip_config, i);
			if(!vipInfo|| vipInfo->type!=Json_Object)
				break;

			Json* product_id  = Json_getItem(vipInfo, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			userVipStr.id = product_id->valueint;


			Json* precious_stone_price  = Json_getItem(vipInfo, "precious_stone_price");
			if(!precious_stone_price || precious_stone_price->type!=Json_String)
				break;
			userVipStr.price = precious_stone_price->valuestring;

			logOnMsg.vipConfig.push_back(userVipStr);
		}

		if(i <Json_getSize(vip_config))
			break;

		//礼包信息
		Json* packs_info = Json_getItem(content, "packs_info");
		if(!packs_info|| packs_info->type!=Json_Array)
			break;

		logOnMsg.packInfo.clear();
		for(i =0; i<Json_getSize(packs_info); i++)
		{
			UserPackInfoStr userPackStr;

			Json* packs_item = Json_getItemAt(packs_info, i);
			if(!packs_item|| packs_item->type!=Json_Object)
				break;

			Json* id  = Json_getItem(packs_item, "id");
			if(!id || id->type!=Json_Number)
				break;
			userPackStr.id = id->valueint;


			Json* discount_price  = Json_getItem(packs_item, "discount_price");
			if(!discount_price || discount_price->type!=Json_Number)
				break;
			userPackStr.price = discount_price->valueint;

			Json* p_type  = Json_getItem(packs_item, "type");
			if(!p_type || p_type->type!=Json_Number)
				break;
			userPackStr.type = p_type->valueint;


			Json* pop_pack  = Json_getItem(packs_item, "pop_pack");
			if(!pop_pack || pop_pack->type!=Json_Number)
				break;
			userPackStr.pop_pack = pop_pack->valueint;
			if(userPackStr.pop_pack == 1)
			{
				CommonData::m_GiftIDBuyNow = 4;
			}


			logOnMsg.packInfo.push_back(userPackStr);
		}

		if(i <Json_getSize(packs_info))
			break;


		//解锁关卡
		Json* unlock_star_data = Json_getItem(content, "unlock_star_data");
		if(!unlock_star_data|| unlock_star_data->type!=Json_Array)
			break;

		logOnMsg.unlockInfo.clear();
		for(i =0; i<Json_getSize(unlock_star_data); i++)
		{
			UserUnlockLevelInfo userUnlockLevel;

			Json* unlockLevel_item = Json_getItemAt(unlock_star_data, i);
			if(!unlockLevel_item|| unlockLevel_item->type!=Json_Object)
				break;

			Json* level  = Json_getItem(unlockLevel_item, "level");
			if(!level || level->type!=Json_Number)
				break;
			userUnlockLevel.level = level->valueint;

			Json* unlock_star  = Json_getItem(unlockLevel_item, "unlock_star");
			if(!unlock_star || unlock_star->type!=Json_Number)
				break;
			userUnlockLevel.needStar = unlock_star->valueint;

			Json* unlocked  = Json_getItem(unlockLevel_item, "unlocked");
			if(!unlocked || unlocked->type!=Json_Number)
				break;
			userUnlockLevel.unlocked = unlocked->valueint;

			logOnMsg.unlockInfo.push_back(userUnlockLevel);
		}

		if(i <Json_getSize(unlock_star_data))
			break;

		// 特殊道具
// 		Json* special_product = Json_getItem(content, "special_product");
// 		if(!special_product|| special_product->type!=Json_Array)
// 			break;
// 
// 		logOnMsg.specialProp.clear();
// 		for(i =0; i<Json_getSize(special_product); i++)
// 		{
// 			UserPropInfoStr propInfoStr;
// 
// 			Json* propInfo = Json_getItemAt(special_product, i);
// 			if(!propInfo|| propInfo->type!=Json_Object)
// 				break;
// 
// 			Json* propId  = Json_getItem(propInfo, "product_id");
// 			if(!propId || propId->type!=Json_Number)
// 				break;
// 			propInfoStr.id = propId->valueint;
// 
// 			Json* propName  = Json_getItem(propInfo, "product_name");
// 			if(!propName || propName->type!=Json_String)
// 				break;
// 			propInfoStr.name= propName->valuestring;
// 
// 			Json* price  = Json_getItem(propInfo, "precious_stone_price");
// 			if(!price || price->type!=Json_String)
// 				break;
// 			propInfoStr.price= price->valuestring;
// 
// 			logOnMsg.specialProp.push_back(propInfoStr);
// 		}
// 
// 		if(i <Json_getSize(special_product))
// 			break;

		//　系统签到配置
		Json* registration = Json_getItem(content, "registration");
		if(!registration|| registration->type!=Json_Array)
			break;

		signInConfigStr.signInConfig.clear();
		for(i =0; i<Json_getSize(registration); i++)
		{
			SystemSignInConfig SigInInfoStr;

			Json* registrationItem = Json_getItemAt(registration, i);
			if(!registrationItem|| registrationItem->type!=Json_Object)
				break;

			Json* name  = Json_getItem(registrationItem, "sign_day");
			if(!name || name->type!=Json_Number)
				break;
			SigInInfoStr.SignInDay = name->valueint;


			Json* combin = Json_getItem(registrationItem, "combin");
			if(!combin|| combin->type!=Json_Array)
				break;


			SigInInfoStr.signReward.clear();
			for ( int j = 0; j<Json_getSize( combin ); j++)
			{
				SignReward signRewardStr;

				Json* combinItem = Json_getItemAt(combin, j);
				if(!combinItem|| combinItem->type!=Json_Object)
					break;

				Json* type  = Json_getItem(combinItem, "type");
				if(!type || type->type!=Json_Number)
					break;
				signRewardStr.proptype = type->valueint;

				Json* num  = Json_getItem(combinItem, "num");
				if(!num || num->type!=Json_Number)
					break;
				signRewardStr.propnum= num->valueint;

				SigInInfoStr.signReward.push_back(signRewardStr);

			}

			signInConfigStr.signInConfig.push_back(SigInInfoStr);
		}

		if(i <Json_getSize(registration))
			break;


		// 功能解锁配置
		Json* config = Json_getItem(content, "config");
		if(!config|| config->type!=Json_Object)
			break;


		Json* friend_points = Json_getItem(config, "friend_points");
		if(!friend_points|| friend_points->type!=Json_Number)
			break;
		unLockConfig.friendFun = friend_points->valueint;

		Json* star_points = Json_getItem(config, "star_points");
		if(!star_points|| star_points->type!=Json_Number)
			break;
		unLockConfig.starTask = star_points->valueint;

		Json* main_task_points = Json_getItem(config, "main_task_points");
		if(!main_task_points|| main_task_points->type!=Json_Number)
			break;
		unLockConfig.mainTask = main_task_points->valueint;

		Json* daily_task_points = Json_getItem(config, "daily_task_points");
		if(!daily_task_points|| daily_task_points->type!=Json_Number)
			break;
		unLockConfig.dailyTask = daily_task_points->valueint;

		Json* jar_replay_time = Json_getItem(config, "jar_replay_time");
		if(!jar_replay_time || jar_replay_time->type!=Json_Number)
			break;
		logOnMsg.baseInfo.jar_replay_time= jar_replay_time->valueint;

		Json* jar_price = Json_getItem(config, "jar_price");
		if(!jar_price || jar_price->type!=Json_Number)
			break;
		logOnMsg.baseInfo.jar_price= jar_price->valueint;

		Json* jar_hour_reduce = Json_getItem(config, "jar_hour_reduce");
		if(!jar_hour_reduce || jar_hour_reduce->type!=Json_Number)
			break;
		logOnMsg.baseInfo.jar_hour_reduce= jar_hour_reduce->valueint;

		Json* sign_card_price = Json_getItem(config, "sign_card_price");
		if(!sign_card_price || sign_card_price->type!=Json_Number)
			break;
		logOnMsg.baseInfo.RetroactiveCatdPrice= sign_card_price->valueint;

		//星星收集数据
		Json* has_get_packs_level = Json_getItem(content,"has_get_packs_level");
		if (!has_get_packs_level || has_get_packs_level->type != Json_Array)
		{
			break;
		}

		logOnMsg.collectInfo.clear();
		for ( int j = 0; j<Json_getSize( has_get_packs_level ); j++)
		{
			CollectStarStruct CollectRewardStr;

			Json* collectItem = Json_getItemAt(has_get_packs_level, j);
			if(!collectItem|| collectItem->type!=Json_Object)
				break;

			Json* type  = Json_getItem(collectItem, "type");
			if(!type || type->type!=Json_Number)
				break;
			CollectRewardStr.receive = type->valueint;

			Json* num  = Json_getItem(collectItem, "level");
			if(!num || num->type!=Json_Number)
				break;
			CollectRewardStr.level= num->valueint;

			logOnMsg.collectInfo.push_back(CollectRewardStr);

		}
		ret = true;
	}while(0);




// 调整关卡数据
#if defined (TEST_FOR_MOBILE)
	for (int i = AnalyseJson::logOnMsg.stageInfo.size()+1; i <= 14; i++)
	{
		UserStageInfoStr stageInfoStr;

		stageInfoStr.level = i;
		stageInfoStr.score = 0;
		AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);
	}
#endif

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setLevelScoreMsg(void)
{
	CCLog("AnalyseJson setLevelScoreMsg");
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		levelScoreMsg.userId = userId->valueint;

		Json* level 	= Json_getItem(content, "game_level");
		if(!level|| level->type!=Json_Number)
			break;
		levelScoreMsg.level= level->valueint;

		Json* score 	= Json_getItem(content, "number");
		if(!score|| score->type!=Json_Number)
			break;
		levelScoreMsg.score= score->valueint;
		CommonData::updateLevelScore();
		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setNoFriendInfoMsg(char *jsonData)
{

	CCLog("AnalyseJson setNoFriendInfoMsg %s",jsonData);
	bool ret = false;
	Json* root = Json_create( jsonData );
	do 
	{
		if (!root || root->type != Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* myId 	= Json_getItem(root, "id");
		if(!myId || myId->type!=Json_Number)
			break;
		nofriendInfoMsg.myId = myId->valueint;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		int i;
		nofriendInfoMsg.nofriend.clear();
		for(i =0; i<Json_getSize(content); i++)
		{
			UserNoFriendInfoStr nofriendInfoStr;

			Json* nofriendInfo = Json_getItemAt(content, i);
			if(!nofriendInfo|| nofriendInfo->type!=Json_Object)
				break;

			Json* idx  = Json_getItem(nofriendInfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			nofriendInfoStr.idx= idx->valuestring;

			Json* gender  = Json_getItem(nofriendInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			nofriendInfoStr.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(nofriendInfo, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			nofriendInfoStr.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(nofriendInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			nofriendInfoStr.nickName= nickName->valuestring;

			nofriendInfoMsg.nofriend.push_back(nofriendInfoStr);

		}
		if(i <Json_getSize(content))
			break;

		ret = true;
	} while (0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setUserFriendInfoMsg(char *jsonData)
{
	CCLog("AnalyseJson setUserFriendInfoMsg %s",jsonData);
	bool ret = false;
	Json* root = Json_create(jsonData);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo 	= Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(baseInfo, "id");
		if(!myId || myId->type!=Json_Number)
			break;
		friendInfoMsg.myId= myId->valueint;

		Json* myIdx 	= Json_getItem(baseInfo, "idx");
		if(!myIdx || myIdx->type!=Json_String)
			break;
		friendInfoMsg.myIdx= myIdx->valuestring;

		// 已删除
		// 			Json* friendIdx 	= Json_getItem(baseInfo, "friend_idx");
		// 			if(!friendIdx || friendIdx->type!=Json_String)
		// 				break;
		// 			friendInfoMsg.friendIdx= friendIdx->valuestring;

		// 好友
		Json* friendsInfo 	= Json_getItem(content, "friend_info");
		if(!friendsInfo || friendsInfo->type!=Json_Array)
			break;

		int i;
		friendInfoMsg.friendInfo.clear();
		for(i =0; i<Json_getSize(friendsInfo); i++)
		{
			UserFriendInfoStr friendInfoStr;

			Json* friendInfo = Json_getItemAt(friendsInfo, i);
			if(!friendInfo|| friendInfo->type!=Json_Object)
				break;

			Json* id  = Json_getItem(friendInfo, "id");
			if(!id || id->type!=Json_Number)
				break;
			friendInfoStr.id= id->valueint;

			Json* idx  = Json_getItem(friendInfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			friendInfoStr.idx= idx->valuestring;

			Json* gender  = Json_getItem(friendInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			friendInfoStr.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(friendInfo, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			friendInfoStr.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(friendInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			friendInfoStr.nickName= nickName->valuestring;

			Json* flag  = Json_getItem(friendInfo, "flag");
			if(!flag || flag->type!=Json_Number)
				break;
			friendInfoStr.flag= flag->valueint;

			friendInfoMsg.friendInfo.push_back(friendInfoStr);

		}

		if(i <Json_getSize(friendsInfo))
			break;

		// 非好友
		Json* nofriendsInfo 	= Json_getItem(content, "nofriend_info");
		if(!nofriendsInfo || nofriendsInfo->type!=Json_Array)
			break;

		int j;
		friendInfoMsg.nofriend_idx.clear();
		for(j =0; j<Json_getSize(nofriendsInfo); j++)
		{
			UserNoFriendIdxStr nofriendInfoStr;

			Json* nofriendInfo = Json_getItemAt(nofriendsInfo, j);
			if(!nofriendInfo|| nofriendInfo->type!=Json_Object)
				break;

			Json* idx  = Json_getItem(nofriendInfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			nofriendInfoStr.idx= idx->valuestring;

			friendInfoMsg.nofriend_idx.push_back(nofriendInfoStr);
		}

		if(j <Json_getSize(nofriendsInfo))
			break;

		ret = true;
	}while(0);
	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setWorldFriendInfoForGuestMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Array)
			break;

		int i =0;
		worldFriendInfoMsg.friendInfo.clear();
		for(i = 0; i<Json_getSize(content); i++)
		{
			UserFriendInfoStr friendInfoStr;

			Json* friendInfo = Json_getItemAt(content, i);
			if(!friendInfo|| friendInfo->type!=Json_Object)
				break;

			Json* id  = Json_getItem(friendInfo, "id");
			if(!id || id->type!=Json_Number)
				break;
			friendInfoStr.id= id->valueint;

			Json* gender  = Json_getItem(friendInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			friendInfoStr.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(friendInfo, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			friendInfoStr.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(friendInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			friendInfoStr.nickName= nickName->valuestring;

			Json* game_level  = Json_getItem(friendInfo, "max_level");
			if(!game_level || game_level->type!=Json_Number)
				break;
			friendInfoStr.level= game_level->valueint;


			worldFriendInfoMsg.friendInfo.push_back(friendInfoStr);
		}

		if(i <Json_getSize(content))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setFriendInfoForGuestMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		// 当前好友个数
		Json* friend_nums 	= Json_getItem(content, "friend_nums");
		if(!friend_nums || friend_nums->type!=Json_Number)
			break;
		friendInfoMsg.friendNum = friend_nums->valueint;


		// 最大好友个数配置
		Json* limit_friend_nums 	= Json_getItem(content, "limit_friend_nums");
		if(!limit_friend_nums || limit_friend_nums->type!=Json_Number)
			break;
		friendInfoMsg.friendMaxNum = limit_friend_nums->valueint;

		// 好友
		Json* friendsInfo 	= Json_getItem(content, "friend_info");
		if(!friendsInfo || friendsInfo->type!=Json_Array)
			break;

		int i;
		friendInfoMsg.friendInfo.clear();
		for(i =0; i<Json_getSize(friendsInfo); i++)
		{
			UserFriendInfoStr friendInfoStr;

			Json* friendInfo = Json_getItemAt(friendsInfo, i);
			if(!friendInfo|| friendInfo->type!=Json_Object)
				break;

			Json* id  = Json_getItem(friendInfo, "userid");
			if(!id || id->type!=Json_Number)
				break;
			friendInfoStr.id= id->valueint;

			Json* is_vip  = Json_getItem(friendInfo, "is_vip");
			if(!is_vip || is_vip->type!=Json_Number)
				break;
			friendInfoStr.isvip= is_vip->valueint;

			Json* idx  = Json_getItem(friendInfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			friendInfoStr.idx= idx->valuestring;

			Json* gender  = Json_getItem(friendInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			friendInfoStr.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(friendInfo, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			friendInfoStr.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(friendInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			friendInfoStr.nickName= nickName->valuestring;

			Json* game_level  = Json_getItem(friendInfo, "game_level");
			if(!game_level || game_level->type!=Json_Number)
				break;
			friendInfoStr.level= game_level->valueint;

			Json* click_timestamp  = Json_getItem(friendInfo, "click_timestamp");
			if(!click_timestamp || click_timestamp->type!=Json_Number)
				break;
			friendInfoStr.click_timestamp= click_timestamp->valueint;

			Json* cur_timestamp  = Json_getItem(friendInfo, "cur_timestamp");
			if(!cur_timestamp || cur_timestamp->type!=Json_Number)
				break;
			friendInfoStr.cur_timestamp= cur_timestamp->valueint;

			Json* countdown_timestamp  = Json_getItem(friendInfo, "countdown_timestamp");
			if(!countdown_timestamp || countdown_timestamp->type!=Json_Number)
				break;
			friendInfoStr.countdown_timestamp= countdown_timestamp->valueint;

			// 			Json* flag  = Json_getItem(friendInfo, "flag");
			// 			if(!flag || flag->type!=Json_Number)
			// 				break;
			friendInfoStr.flag= 0;//flag->valueint;

			friendInfoMsg.friendInfo.push_back(friendInfoStr);
		}

		if(i <Json_getSize(friendsInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}
bool AnalyseJson::setNoFriendInfoForGuestMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		// 非好友
		Json* nofriendsInfo 	= Json_getItem(content, "recommand_user_info");
		if(!nofriendsInfo || nofriendsInfo->type!=Json_Array)
			break;

		int i;
		nofriendInfoMsg.nofriend.clear();
		for(i =0; i<Json_getSize(nofriendsInfo); i++)
		{
			UserNoFriendInfoStr NofriendInfo;

			Json* nofriend = Json_getItemAt(nofriendsInfo, i);
			if(!nofriend|| nofriend->type!=Json_Object)
				break;

			Json* id  = Json_getItem(nofriend, "userid");
			if(!id || id->type!=Json_Number)
				break;
			NofriendInfo.id= id->valueint;

			Json* idx  = Json_getItem(nofriend, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			NofriendInfo.idx= idx->valuestring;

			Json* gender  = Json_getItem(nofriend, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			NofriendInfo.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(nofriend, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			NofriendInfo.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(nofriend, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			NofriendInfo.nickName= nickName->valuestring;

			NofriendInfo.isInvite = false;
			NofriendInfo.isSelect = false;
	
			nofriendInfoMsg.nofriend.push_back(NofriendInfo);

		}

		if(i <Json_getSize(nofriendsInfo))
			break;

		ret = true;
	}while(0);
	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setGetLifePriceMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* lifeId 	= Json_getItem(content, "product_id");
		if(!lifeId || lifeId->type!=Json_Number)
			break;
		lifePriceMsg.lifeId = lifeId->valueint;

		Json* price 	= Json_getItem(content, "product_price");
		if(!price || price->type!=Json_String)
			break;
		lifePriceMsg.price= price->valuestring;

		Json* name 	= Json_getItem(content, "product_name");
		if(!name || name->type!=Json_String)
			break;
		lifePriceMsg.name= name->valuestring;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setBuyLifeMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		buyLifeMsg.userId= userId->valueint;

		Json* buyNum  = Json_getItem(content, "buy_life_number");
		if(!buyNum || buyNum->type!=Json_Number)
			break;
		buyLifeMsg.buyNum= buyNum->valueint;

		Json* price 	= Json_getItem(content, "buy_life_price");
		if(!price || price->type!=Json_String)
			break;
		buyLifeMsg.price= price->valuestring;

		Json* totalLife  = Json_getItem(content, "life_number");
		if(!totalLife || totalLife->type!=Json_Number)
			break;
		buyLifeMsg.totalLife= totalLife->valueint;
		CCLog("AnalyseJson::setBuyLifeMsg   butT%d  buyN%d  T%d", AnalyseJson::buyLifeMsg.totalLife, AnalyseJson::buyLifeMsg.buyNum, AnalyseJson::logOnMsg.lifeInfo.lifeNum );


		Json* flag 	= Json_getItem(content, "flag");
		if(!flag || flag->type!=Json_Number)
			break;
		buyLifeMsg.flag= flag->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setHandselLifeMsg(void)
{
	bool ret = false;
	int tempfriend = 0;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* friendId = Json_getItem(content, "userid_friend");
		if(!friendId || friendId->type!=Json_Number)
			break;
		tempfriend= friendId->valueint;

		std::list<UserFriendInfoStr>::iterator p = AnalyseJson::friendInfoMsg.friendInfo.begin();

		for (int i = 0; i< (int)AnalyseJson::friendInfoMsg.friendInfo.size(); i++)
		{
			if (p->id == tempfriend)
			{
				break;
			}
			p++;
		}

		Json* click_timestamp  = Json_getItem(content, "click_timestamp");
		if(!click_timestamp || click_timestamp->type!=Json_Number)
			break;
		p->click_timestamp= click_timestamp->valueint;

		Json* cur_timestamp  = Json_getItem(content, "cur_timestamp");
		if(!cur_timestamp || cur_timestamp->type!=Json_Number)
			break;
		p->cur_timestamp= cur_timestamp->valueint;

		Json* countdown_timestamp  = Json_getItem(content, "countdown_timestamp");
		if(!countdown_timestamp || countdown_timestamp->type!=Json_Number)
			break;
		p->countdown_timestamp= countdown_timestamp->valueint;


		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setGetHandselMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId = Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		getHandselMsg.myId= myId->valueint;

		Json* limit_heard_num = Json_getItem(baseInfo, "limit_heard_num");
		if(!limit_heard_num || limit_heard_num->type!=Json_Number)
			break;
		getHandselMsg.heardLimit = limit_heard_num->valueint;


		Json* handselMsgInfo = Json_getItem(content, "handsel_life_message_info");
		if(!handselMsgInfo|| handselMsgInfo->type!=Json_Array)
			break;

		int i;
		getHandselMsg.handselMsg.clear();
		for(i =0; i<Json_getSize(handselMsgInfo); i++)
		{
			UserGetHandselMsg handselMsg;

			Json* handselInfo = Json_getItemAt(handselMsgInfo, i);
			if(!handselInfo|| handselInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(handselInfo, "id");//product_id
			if(!handselId || handselId->type!=Json_Number)
				break;
			handselMsg.handselId= handselId->valueint;

			Json* friendId  = Json_getItem(handselInfo, "userid");
			if(!friendId || friendId->type!=Json_Number)
				break;
			handselMsg.friendId= friendId->valueint;

			Json* gender  = Json_getItem(handselInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			handselMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(handselInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			handselMsg.headPicUrl= headPicUrl->valuestring;

			Json* nickName  = Json_getItem(handselInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			handselMsg.nickName= nickName->valuestring;

			Json* diff_time  = Json_getItem(handselInfo, "diff_time");
			if(!diff_time || diff_time->type!=Json_Number)
				break;
			handselMsg.diff_time= diff_time->valueint;

			Json* lifeId  = Json_getItem(handselInfo, "product_id");
			if(!lifeId || lifeId->type!=Json_Number)				
				break;
			handselMsg.lifeId= lifeId->valueint;

			Json* lifePrice  = Json_getItem(handselInfo, "product_price");
			if(!lifePrice || lifePrice->type!=Json_String)			// 价格字符数据
				break;
			handselMsg.lifePrice= lifePrice->valuestring;

			Json* lifeNum  = Json_getItem(handselInfo, "product_number");
			if(!lifeNum || lifeNum->type!=Json_Number)
				break;
			handselMsg.lifeNum= lifeNum->valueint;

			Json* lifeName  = Json_getItem(handselInfo, "product_name");
			if(!lifeName || lifeName->type!=Json_String)
				break;
			handselMsg.lifeName= lifeName->valuestring;

			getHandselMsg.handselMsg.push_back(handselMsg);
		}

		if(i <Json_getSize(handselMsgInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setAcceptLifeMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* handselId 	= Json_getItem(content, "id");
		if(!handselId || handselId->type!=Json_Number)
			break;
		acceptLifeMsg.handselId= handselId->valueint;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		acceptLifeMsg.userId= userId->valueint;

		Json* totalLife 	= Json_getItem(content, "candy_currency");
		if(!totalLife || totalLife->type!=Json_Number)
			break;
		//acceptLifeMsg.totalLife= totalLife->valueint;
		logOnMsg.baseInfo.candyNum = totalLife->valueint;

// 		Json* flag 	= Json_getItem(content, "flag");
// 		if(!flag || flag->type!=Json_Number)
// 			break;
// 		acceptLifeMsg.flag= flag->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setConsumeLifeMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		consumeLifeMsg.userId= userId->valueint;

		Json* consumeNum = Json_getItem(content, "life_consume_number");
		if(!consumeNum || consumeNum->type!=Json_Number)
			break;
		consumeLifeMsg.consumeNum= consumeNum->valueint;

		Json* totalLife = Json_getItem(content, "life_number");
		if(!totalLife || totalLife->type!=Json_Number)
			break;
		consumeLifeMsg.totalLife= totalLife->valueint;

		Json* flag = Json_getItem(content, "flag");
		if(!flag || flag->type!=Json_Number)
			break;
		consumeLifeMsg.flag= flag->valueint;

		Json* lifeCountDown = Json_getItem(content, "life_countdown");
		if(!lifeCountDown || lifeCountDown->type!=Json_Number)
			break;
		consumeLifeMsg.lifeCountDown= lifeCountDown->valueint;

		Json* first_consume = Json_getItem(content, "first_consume");
		if(!first_consume || first_consume->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.lifeInfo.first_consums = first_consume->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setRemoveSysLifeMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		removeSysLifeMsg.userId= userId->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setAddSysLifeMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		addSysLifeMsg.userId= userId->valueint;

		Json* totalLife 	= Json_getItem(content, "life_number");
		if(!totalLife || totalLife->type!=Json_Number)
			break;
		addSysLifeMsg.totalLife= totalLife->valueint;
		CCLog("ResponseMgr::setAddSysLifeMsg  addT[%d] T[%d]",AnalyseJson::addSysLifeMsg.totalLife, AnalyseJson::logOnMsg.lifeInfo.lifeNum);


		Json* flag 	= Json_getItem(content, "flag");
		if(!flag || flag->type!=Json_Number)
			break;
		addSysLifeMsg.flag= flag->valueint;

		Json* lifeCountDown 	= Json_getItem(content, "life_countdown");
		if(!lifeCountDown || lifeCountDown->type!=Json_Number)
			break;
		addSysLifeMsg.lifeCountDown= lifeCountDown->valueint;
		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setGetPropInfoMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* id 	= Json_getItem(content, "product_id");
		if(!id || id->type!=Json_Number)
			break;
		propInfoMsg.id= id->valueint;

		Json* price 	= Json_getItem(content, "product_price");
		if(!price || price->type!=Json_String)
			break;
		propInfoMsg.price= price->valuestring;

		Json* name 	= Json_getItem(content, "product_name");
		if(!name || name->type!=Json_String)
			break;
		propInfoMsg.name= name->valuestring;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;

}

bool AnalyseJson::setBuyPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;


		// get life info
		Json* lifeInfo  = Json_getItem(content, "life");
		if(!lifeInfo || lifeInfo->type!=Json_Object)
			break;

		Json* life_countdown 	= Json_getItem(lifeInfo, "life_countdown");
		if(!life_countdown || life_countdown->type!=Json_Number)
			break;
		buyPropInfo.lifeInfo.lifeCountDown= life_countdown->valueint;

		Json* life_number 	= Json_getItem(lifeInfo, "life_number");
		if(!life_number || life_number->type!=Json_Number)
			break;
		buyPropInfo.lifeInfo.lifeNum= life_number->valueint;

		// get goods info
		Json* stagePropsInfo = Json_getItem(content, "goods");
		if(!stagePropsInfo|| stagePropsInfo->type!=Json_Array)
			break;

		int i;
		buyPropInfo.stagePropInfo.clear();
		for(i =0; i<Json_getSize(stagePropsInfo); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stagePropsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			buyPropInfo.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stagePropsInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setHandselPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(baseInfo, "usreid_myself");
		if(!myId || myId->type!=Json_Number)
			break;
		handselPropInfo.baseInfo.myId= myId->valueint;

		Json* friendId 	= Json_getItem(baseInfo, "userid_friend");
		if(!friendId || friendId->type!=Json_Number)
			break;
		handselPropInfo.baseInfo.friendId= friendId->valueint;

		Json* propId 	= Json_getItem(baseInfo, "product_id");
		if(!propId || propId->type!=Json_Number)
			break;
		handselPropInfo.baseInfo.propId= propId->valueint;

		Json* proNum = Json_getItem(baseInfo, "product_number");
		if(!proNum || proNum->type!=Json_Number)
			break;
		handselPropInfo.baseInfo.propNum= proNum->valueint;


		Json* propPrice = Json_getItem(baseInfo, "product_price");
		if(!propPrice || propPrice->type!=Json_String)
			break;
		handselPropInfo.baseInfo.propPrice= propPrice->valuestring;


		Json* stagePropsInfo = Json_getItem(content, "game_stage_property_info");
		if(!stagePropsInfo|| stagePropsInfo->type!=Json_Array)
			break;

		int i;
		handselPropInfo.stagePropInfo.clear();
		for(i =0; i<Json_getSize(stagePropsInfo); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stagePropsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			handselPropInfo.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stagePropsInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;

}

bool AnalyseJson::setGetHandselPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(baseInfo, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		handselPropMsg.userId= userId->valueint;


		Json* handselStageProps = Json_getItem(content, "handsel_game_stage_property_message_info");
		if(!handselStageProps|| handselStageProps->type!=Json_Array)
			break;

		int i;
		handselPropMsg.handselStageProp.clear();
		for(i =0; i<Json_getSize(handselStageProps); i++)
		{
			UserGetHandselPropMsg handselPropInfo;

			Json* propInfo = Json_getItemAt(handselStageProps, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(propInfo, "id");
			if(!handselId || handselId->type!=Json_Number)
				break;
			handselPropInfo.handselId= handselId->valueint;

			Json* friendId  = Json_getItem(propInfo, "userid");
			if(!friendId || friendId->type!=Json_Number)
				break;
			handselPropInfo.friendId= friendId->valueint;

			Json* gender  = Json_getItem(propInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			handselPropInfo.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(propInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			handselPropInfo.headPicUrl= headPicUrl->valuestring;

			Json* nickName  = Json_getItem(propInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			handselPropInfo.nickName= nickName->valuestring;

			Json* diffTime  = Json_getItem(propInfo, "diff_time");
			if(!diffTime || diffTime->type!=Json_Number)
				break;
			handselPropInfo.diffTime= diffTime->valueint;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			handselPropInfo.propId= propId->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			handselPropInfo.propName= propName->valuestring;

			Json* propPrice  = Json_getItem(propInfo, "product_price");
			if(!propPrice || propPrice->type!=Json_String)
				break;
			handselPropInfo.propPrice= propName->valuestring;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			handselPropInfo.propNum= propNum->valueint;

			handselPropMsg.handselStageProp.push_back(handselPropInfo);
		}

		if(i <Json_getSize(handselStageProps))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;

}

bool AnalyseJson::setAcceptPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* acceptId 	= Json_getItem(baseInfo, "id");
		if(!acceptId || acceptId->type!=Json_Number)
			break;
		acceptPropMsg.acceptId= acceptId->valueint;

		Json* userId 	= Json_getItem(baseInfo, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		acceptPropMsg.userId= userId->valueint;


		Json* stageProps = Json_getItem(content, "game_stage_property_info");
		if(!stageProps|| stageProps->type!=Json_Array)
			break;

		int i;
		acceptPropMsg.stagePropInfo.clear();
		for(i =0; i<Json_getSize(stageProps); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stageProps, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			acceptPropMsg.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stageProps))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setClaimPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(content, "userid_myself");
		if(!myId || myId->type!=Json_Number)
			break;
		claimPropMsg.myId = myId->valueint;

		Json* friendId 	= Json_getItem(content, "userid_friend");
		if(!friendId || friendId->type!=Json_Number)
			break;
		claimPropMsg.friendId= friendId->valueint;

		Json* propId 	= Json_getItem(content, "product_id");
		if(!propId || propId->type!=Json_Number)
			break;
		claimPropMsg.propId= propId->valueint;

		Json* propNum 	= Json_getItem(content, "product_number");
		if(!propNum || propNum->type!=Json_Number)
			break;
		claimPropMsg.propNum= propNum->valueint;

		Json* propPrice 	= Json_getItem(content, "product_price");
		if(!propPrice || propPrice->type!=Json_String)
			break;
		claimPropMsg.propPrice= propPrice->valuestring;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson:: setRefuseClaimedProp(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do 
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* base_info = Json_getItem(content, "base_info");
		if(!base_info || base_info->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(base_info, "id");
		if(!myId || myId->type!=Json_Number)
			break;
		refuseClaimPropStr.myId = myId->valueint;

		Json* friendId 	= Json_getItem(base_info, "userid");
		if(!friendId || friendId->type!=Json_Number)
			break;
		refuseClaimPropStr.friendId= friendId->valueint;

		Json* propId 	= Json_getItem(base_info, "userid_other");
		if(!propId || propId->type!=Json_Number)
			break;
		refuseClaimPropStr.propId= propId->valueint;

		ret = true;
	} while (0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setAllAcceptHandselMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* base_info = Json_getItem(content, "base_info");
		if(!base_info || base_info->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(base_info, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		allAcceptHandsel.myId= userId->valueint;

		// 生命信息解析
		Json* life_info = Json_getItem(content, "life_info");
		if(!life_info || life_info->type!=Json_Object)
			break;

		Json* life_number 	= Json_getItem(life_info, "life_number");
		if(!life_number || life_number->type!=Json_Number)
			break;
		allAcceptHandsel.myLifeInfo.lifeNum = life_number->valueint;

		Json* life_flag 	= Json_getItem(life_info, "flag");
		if(!life_flag || life_flag->type!=Json_Number)
			break;
		allAcceptHandsel.myLifeInfo.flag = life_flag->valueint;

		Json* life_countdown 	= Json_getItem(life_info, "life_countdown");
		if(!life_countdown || life_countdown->type!=Json_Number)
			break;
		allAcceptHandsel.myLifeInfo.lifeCountDown = life_countdown->valueint;

		//道具数据解析
		Json* stageProps = Json_getItem(content, "game_stage_property_info");
		if(!stageProps|| stageProps->type!=Json_Array)
			break;

		int i;
		allAcceptHandsel.stagePropInfo.clear();
		for(i =0; i<Json_getSize(stageProps); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stageProps, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			allAcceptHandsel.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stageProps))
			break;

		ret = true;

	}while( 0 );

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForFilterNoFriend(void)
{
	CCLog("AnalyseJson==>setForFilterNoFriend %s", jsonString);
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* owner_idx 	= Json_getItem(content, "owner_idx");
		if(!owner_idx || owner_idx->type!=Json_String)
			break;
		filterFriend.myIdx= owner_idx->valuestring;

		Json* invite_friend_idxs 	= Json_getItem(content, "invite_friend_idxs");
		if(!invite_friend_idxs || invite_friend_idxs->type!=Json_String)
			break;
		filterFriend.inviteidx= invite_friend_idxs->valuestring;

		//过滤后的IDX
		Json* filter_freind_idx_array = Json_getItem(content, "filter_freind_idx_array");
		if(!filter_freind_idx_array|| filter_freind_idx_array->type!=Json_Array)
			break;

		int i;
		filterFriend.FilterIdx.clear();
		for(i =0; i<Json_getSize(filter_freind_idx_array); i++)
		{
			UserFilterIdxStr filteridx;

			Json* FilterIdx = Json_getItemAt(filter_freind_idx_array, i);
			if(!FilterIdx|| FilterIdx->type!=Json_Object)
				break;

			Json* idx  = Json_getItem(FilterIdx, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			filteridx.idx = idx->valuestring;

			filterFriend.FilterIdx.push_back(filteridx);
		}

		if(i <Json_getSize(filter_freind_idx_array))
			break;

		ret = true;
	}while(0);
	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForNoFriendInfoMsg(char *jsonData)
{
	bool ret = false;
	Json* root = NULL;


	if ( NULL != jsonData)
		root = Json_create(jsonData);
	else
		root = Json_create(jsonString);

	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Array)
			break;

		int i;
		nofriendInfoMsg.nofriend.clear();
		for(i =0; i<Json_getSize(content); i++)
		{
			UserNoFriendInfoStr filterinfo;

			Json* Filterinfo = Json_getItemAt(content, i);
			if(!Filterinfo|| Filterinfo->type!=Json_Object)
				break;

			Json* idx  = Json_getItem(Filterinfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			filterinfo.idx = idx->valuestring;

			Json* gender  = Json_getItem(Filterinfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			filterinfo.gender = gender->valueint;

			Json* avatar_url  = Json_getItem(Filterinfo, "avatar_url");
			if(!avatar_url || avatar_url->type!=Json_String)
				break;
			filterinfo.headPicUr = avatar_url->valuestring;

			Json* nickname  = Json_getItem(Filterinfo, "nickname");
			if(!nickname || nickname->type!=Json_String)
				break;
			filterinfo.nickName = nickname->valuestring;

			filterinfo.isInvite = false;
			filterinfo.isSelect = false;
			nofriendInfoMsg.nofriend.push_back(filterinfo);
		}
		if(i <Json_getSize(content))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForInviteFriendMsg(void)
{
	bool ret = false;


	return ret;
}

bool AnalyseJson::setGetClaimedPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		getClaimedPropMsg.myId= myId->valueint;

		Json* getClaimedProps = Json_getItem(content, "obtain_game_stage_property_message_info");
		if(!getClaimedProps|| getClaimedProps->type!=Json_Array)
			break;

		int i;
		getClaimedPropMsg.msg.clear();
		for(i =0; i<Json_getSize(getClaimedProps); i++)
		{
			UserGetClaimedPropMsg getClaimedProp;

			Json* claimedProp = Json_getItemAt(getClaimedProps, i);
			if(!claimedProp|| claimedProp->type!=Json_Object)
				break;

			Json* acceptId  = Json_getItem(claimedProp, "id");
			if(!acceptId || acceptId->type!=Json_Number)
				break;
			getClaimedProp.acceptId= acceptId->valueint;

			Json* friendId  = Json_getItem(claimedProp, "userid");
			if(!friendId || friendId->type!=Json_Number)
				break;
			getClaimedProp.friendId= friendId->valueint;

			Json* gender  = Json_getItem(claimedProp, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			getClaimedProp.gender= gender->valueint;


			Json* headPicUrl  = Json_getItem(claimedProp, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			getClaimedProp.headPicUrl= headPicUrl->valuestring;

			Json* nickName  = Json_getItem(claimedProp, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			getClaimedProp.nickName= nickName->valuestring;

			Json* diff_time  = Json_getItem(claimedProp, "diff_time");
			if(!diff_time || diff_time->type!=Json_Number)
				break;
			getClaimedProp.diff_time= diff_time->valueint;

			Json* propId  = Json_getItem(claimedProp, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			getClaimedProp.propId= propId->valueint;

			Json* propName  = Json_getItem(claimedProp, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			getClaimedProp.propName= propName->valuestring;

			Json* propPrice  = Json_getItem(claimedProp, "product_price");
			if(!propPrice || propPrice->type!=Json_String)
				break;
			getClaimedProp.propPrice= propName->valuestring;

			Json* propNum  = Json_getItem(claimedProp, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			getClaimedProp.propNum= propNum->valueint;

			getClaimedPropMsg.msg.push_back(getClaimedProp);
		}

		if(i <Json_getSize(getClaimedProps))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setAcceptClaimedPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* claimedPropId 	= Json_getItem(baseInfo, "id");
		if(!claimedPropId || claimedPropId->type!=Json_Number)
			break;
		acceptClaimedPropMsg.claimedPropId= claimedPropId->valueint;

		Json* stagePropsInfo = Json_getItem(content, "game_stage_property_info");
		if(!stagePropsInfo|| stagePropsInfo->type!=Json_Array)
			break;
		int i;
		for(i =0; i<Json_getSize(stagePropsInfo); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stagePropsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			acceptClaimedPropMsg.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stagePropsInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;

}

bool AnalyseJson::setConsumePropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId 	= Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		consumePropStr.myId= myId->valueint;

		Json* propId 	= Json_getItem(baseInfo, "product_id");
		if(!propId || propId->type!=Json_Number)
			break;
		consumePropStr.propId= propId->valueint;

		Json* propName 	= Json_getItem(baseInfo, "product_name");
		if(!propName || propName->type!=Json_String)
			break;
		consumePropStr.propName= propName->valuestring;

		Json* stagePropsInfo = Json_getItem(content, "game_stage_property_info");
		if(!stagePropsInfo|| stagePropsInfo->type!=Json_Array)
			break;

		int i;
		consumePropStr.stagePropInfo.clear();
		for(i =0; i<Json_getSize(stagePropsInfo); i++)
		{
			UserPropInfoStr stagePropInfo;

			Json* propInfo = Json_getItemAt(stagePropsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			stagePropInfo.id= propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			if(!propNum || propNum->type!=Json_Number)
				break;
			stagePropInfo.num= propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			if(!propName || propName->type!=Json_String)
				break;
			stagePropInfo.name= propName->valuestring;

			consumePropStr.stagePropInfo.push_back(stagePropInfo);
		}

		if(i <Json_getSize(stagePropsInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setGetUserPropMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(content, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		getUserPropStr.userId= userId->valueint;

		Json* propId 	= Json_getItem(content, "product_id");
		if(!propId || propId->type!=Json_Number)
			break;
		getUserPropStr.propId= propId->valueint;

		Json* propNum 	= Json_getItem(content, "product_number");
		if(!propNum || propNum->type!=Json_Number)
			break;
		getUserPropStr.propNum= propNum->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setEnergyUseNum(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* price 	= Json_getItem(content, "product_price");
		if(!price || price->type!=Json_String)
			break;
		std::string tem(price->valuestring);
		energyUsetime.usetime = tem;

		Json* gemprice 	= Json_getItem(content, "product_precious_stone_price");
		if(!gemprice || gemprice->type!=Json_Number)
			break;
		energyUsetime.gemprice = gemprice->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setMagicLampTime(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* replay_time 	= Json_getItem(content, "replay_time");
		if(!replay_time || replay_time->type!=Json_Number)
			break;
		magicLampInfo.magicLampTime = replay_time->valueint;

		Json* has_jar 	= Json_getItem(content, "has_jar");
		if(!has_jar || has_jar->type!=Json_Number)
			break;
		magicLampInfo.hasMagicLamp = has_jar->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setUseMagicLamp(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* replay_time 	= Json_getItem(content, "replay_time");
		if(!replay_time || replay_time->type!=Json_Number)
			break;
		magicLampInfo.magicLampTime = replay_time->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setGetPropRecordMsg(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo  = Json_getItem(content, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* userId 	= Json_getItem(baseInfo, "userid");
		if(!userId || userId->type!=Json_Number)
			break;
		propRecordStr.userId= userId->valueint;

		Json* chatRecords = Json_getItem(content, "game_stage_property_info");
		if(!chatRecords|| chatRecords->type!=Json_Array)
			break;

		int i;
		propRecordStr.propRecord.clear();
		for(i =0; i<Json_getSize(chatRecords); i++)
		{
			UserPropRecordMsg propRecordMsg;

			Json* chatRecord = Json_getItemAt(chatRecords, i);
			if(!chatRecord|| chatRecord->type!=Json_Object)
				break;

			Json* id  = Json_getItem(chatRecord, "id");
			if(!id || id->type!=Json_Number)
				break;
			propRecordMsg.id= id->valueint;

			Json* userId  = Json_getItem(chatRecord, "userid");
			if(!userId || userId->type!=Json_Number)
				break;
			propRecordMsg.userId= userId->valueint;

			Json* type  = Json_getItem(chatRecord, "type");
			if(!type || type->type!=Json_Number)
				break;
			propRecordMsg.type= type->valueint;

			Json* flag  = Json_getItem(chatRecord, "flag");
			if(!flag|| flag->type!=Json_Number)
				break;
			propRecordMsg.flag= flag->valueint;

			Json* gender  = Json_getItem(chatRecord, "gender");
			if(!gender|| gender->type!=Json_Number)
				break;
			propRecordMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(chatRecord, "avatar_url");
			if(!headPicUrl|| headPicUrl->type!=Json_String)
				break;
			propRecordMsg.headPicUrl= headPicUrl->valuestring;

			Json* nickName  = Json_getItem(chatRecord, "nickname");
			if(!nickName|| nickName->type!=Json_String)
				break;
			propRecordMsg.nickName= nickName->valuestring;

			Json* propId  = Json_getItem(chatRecord, "product_id");
			if(!propId|| propId->type!=Json_Number)
				break;
			propRecordMsg.propId= propId->valueint;

			Json* propName  = Json_getItem(chatRecord, "product_name");
			if(!propName|| propName->type!=Json_String)
				break;
			propRecordMsg.propName= propName->valuestring;

			Json* propNum  = Json_getItem(chatRecord, "product_number");
			if(!propNum|| propNum->type!=Json_Number)
				break;
			propRecordMsg.propNum= propNum->valueint;

			Json* propPrice  = Json_getItem(chatRecord, "product_price");
			if(!propPrice|| propPrice->type!=Json_String)
				break;
			propRecordMsg.propPrice= propPrice->valuestring;

			Json* timeStar  = Json_getItem(chatRecord, "time_start");
			if(!timeStar|| timeStar->type!=Json_String)
				break;
			propRecordMsg.timeStar= timeStar->valuestring;

			Json* timeEnd  = Json_getItem(chatRecord, "time_end");
			if(!timeEnd|| timeEnd->type!=Json_String)
				break;
			propRecordMsg.timeEnd= timeEnd->valuestring;

			propRecordStr.propRecord.push_back(propRecordMsg);
		}

		if(i <Json_getSize(chatRecords))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForNoticeData(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
		{
			noticeStr.state = status->valueint;
			return true;
		}
		noticeStr.state = status->valueint;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* noticeData  = Json_getItem(content, "adate");
		if(!noticeData || noticeData->type!=Json_String)
			break;
		noticeStr.noticeData = noticeData->valuestring;

		Json* noticeDate  = Json_getItem(content, "content");
		if(!noticeDate || noticeDate->type!=Json_String)
			break;
		noticeStr.noticeDate = noticeDate->valuestring;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForChitchat(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* Chitchatstatus  = Json_getItem(content, "status");
		if(!Chitchatstatus || Chitchatstatus->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.baseInfo.Chitchat = Chitchatstatus->valueint;

#if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM )

		AnalyseJson::logOnMsg.baseInfo.Chitchat = 0;
#endif

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setGameState(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* pGamestate  = Json_getItem(content, "status");
		if(!pGamestate || pGamestate->type!=Json_Number)
			break;
		gamestate.isGameState = pGamestate->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setSystemGiveProp(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* propsInfo = Json_getItem(content, "game_stage_property_info");
		if(!propsInfo|| propsInfo->type!=Json_Array)
			break;

		int i = 0;
		int nSize = logOnMsg.propInfo.size();
		std::list<UserPropInfoStr>::iterator iter = logOnMsg.propInfo.begin();
		std::list<UserPropInfoStr>::iterator iterEnd = logOnMsg.propInfo.end();

		for(i =0; i<Json_getSize(propsInfo); i++)
		{
			Json* propInfo = Json_getItemAt(propsInfo, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			if(!propId || propId->type!=Json_Number)
				break;
			iter = logOnMsg.propInfo.begin();
			for(;iter != iterEnd; ++iter)
			{
				if(iter->id == propId->valueint)
				{
					Json* propNum  = Json_getItem(propInfo, "product_number");
					if(!propNum || propNum->type!=Json_Number)
						break;
					iter->num = propNum->valueint;

					break;
				}
			}
		}
		if(i <Json_getSize(propsInfo))
			break;


		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setSystemHeadUrl(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;
		SysHeadUrl.status = status->valueint;

		Json* content = Json_getItem(root, "content");
		if(!content|| content->type!=Json_Array)
			break;

		int i;
		SysHeadUrl.headUrl.clear();
		for(i =0; i<Json_getSize(content); i++)
		{
			std::string Url;

			Json* item = Json_getItemAt(content, i);
			if(!item|| item->type!=Json_Object)
				break;

			Json* url  = Json_getItem(item, "url");
			if( url->type != Json_String)
				break;
			Url = url->valuestring;

			SysHeadUrl.headUrl.push_back(Url);
		}

		if(i <Json_getSize(content))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}



bool AnalyseJson::setForGemBuyLife(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* life_number  = Json_getItem(content, "life_number");
		if(!life_number || life_number->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum = life_number->valueint;

		Json* precious_stone_number  = Json_getItem(content, "precious_stone_number");
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum= precious_stone_number->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForGemBuyProp(void)
{
	CCLog("jsonString = %s",jsonString);
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		CCLog("jsonString 111111111",jsonString);
		if(!root || root->type!=Json_Object)
			break;
		CCLog("jsonString 2222222",jsonString);

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		CCLog("jsonString 3333333333",jsonString);

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Array)
			break;
		CCLog("jsonString 44444444444",jsonString);

		logOnMsg.propInfo.clear();
		for(int i =0; i<Json_getSize(content); i++)
		{
			UserPropInfoStr propInfoStr;

			Json* propInfo = Json_getItemAt(content, i);
			if(!propInfo|| propInfo->type!=Json_Object)
				break;

			Json* propId  = Json_getItem(propInfo, "product_id");
			CCLog("jsonString product_id = %d",propId);
			if(!propId || propId->type!=Json_Number)
				break;
			propInfoStr.id = propId->valueint;

			Json* propNum  = Json_getItem(propInfo, "product_number");
			CCLog("jsonString propNum = %d",propNum->valueint);

			if(!propNum || propNum->type!=Json_Number)
				break;
			propInfoStr.num = propNum->valueint;

			Json* propName  = Json_getItem(propInfo, "product_name");
			CCLog("jsonString propName = %s",propName);

			if(!propName || propName->type!=Json_String)
				break;
			propInfoStr.name= propName->valuestring;

			Json* price  = Json_getItem(propInfo, "product_price");
			CCLog("jsonString price = %s",price);

			if(!price || price->type!=Json_String)
				break;
			propInfoStr.price= price->valuestring;

			Json* candy_price  = Json_getItem(propInfo, "candy_price");
			CCLog("jsonString candy_price = %d",candy_price);

			if(!candy_price || candy_price->type!=Json_String)
				break;
			propInfoStr.candyprice= candy_price->valuestring;

			Json* currency  = Json_getItem(propInfo, "currency_type");
			CCLog("jsonString currency = %d",currency);

			if(!currency || currency->type!=Json_Number)
				break;
			propInfoStr.priceType= currency->valueint;


			logOnMsg.propInfo.push_back(propInfoStr);
		}

		
		CCLog("jsonString 6666666666",jsonString);
		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForGemBuyVip(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* returnInfo  = Json_getItem(content, "return_info");
		if(!returnInfo || returnInfo->type!=Json_Object)
			break;

		Json* vipLength  = Json_getItem(returnInfo, "vip_length");
		if(!vipLength || vipLength->type!=Json_Number)
			break;
		logOnMsg.baseInfo.vipLength= vipLength->valueint;

		Json* viplevel = Json_getItem(returnInfo, "vip_level");
		if(!viplevel || viplevel->type!=Json_Number)
			break;
		logOnMsg.baseInfo.isVip= viplevel->valueint;

		Json* precious_stone_number = Json_getItem(returnInfo, "precious_stone_number");
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum= precious_stone_number->valueint;


		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForGemBuySkill(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* cur_stone_num  = Json_getItem(content, "cur_stone_num");
		if(!cur_stone_num || cur_stone_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum= cur_stone_num->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}
bool AnalyseJson::setForGemBuyPackage(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content 	= Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* user_info = Json_getItem(content, "user_info");
		if(!user_info || user_info->type!=Json_Object)
			break;

		Json* cur_life = Json_getItem(user_info, "cur_life");
		if(!cur_life || cur_life->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum = cur_life->valueint;

		Json* cur_gem = Json_getItem(user_info, "cur_gem");
		if(!cur_gem || cur_gem->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum = cur_gem->valueint;


		Json* game_stage_property_info = Json_getItem(content, "game_stage_property_info");
		if(!game_stage_property_info || game_stage_property_info->type!=Json_Array)
			break;
		int i = 0;
		for(i =0; i<Json_getSize(game_stage_property_info); i++)
		{
			Json* packs_item = Json_getItemAt(game_stage_property_info, i);
			if(!packs_item|| packs_item->type!=Json_Object)
				break;

			Json* product_id  = Json_getItem(packs_item, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			int productId = product_id->valueint;

			Json* product_number  = Json_getItem(packs_item, "product_number");
			if(!product_number || product_number->type!=Json_Number)
				break;
			int productNumber = product_number->valueint;


			std::list<UserPropInfoStr>::iterator iter = logOnMsg.propInfo.begin();
			std::list<UserPropInfoStr>::iterator iterend = logOnMsg.propInfo.end();
			for(; iter != iterend ;++iter)
			{
				if(productId == iter->id)
				{
					iter->num = productNumber;
					break;
				}
			}
		}

		if(i <Json_getSize(game_stage_property_info))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}
bool AnalyseJson::setForUpdateGemNum(void)
{
	CCLog("56555555");
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		
		Json* precious_stone_number  = Json_getItem(content, "precious_stone_number");

		CCLog("precious_stone_number = %d",precious_stone_number->valueint);
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum= precious_stone_number->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}


bool AnalyseJson::setForRewardVip(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* return_info = Json_getItem(content, "return_info");
		if(!return_info || return_info->type!=Json_Object)
			break;

		Json* life_num  = Json_getItem(return_info, "life_num");
		if(!life_num || life_num->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum= life_num->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForMyAllMsgG(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* friend_message = Json_getItem(content, "friend_message");
		if(!friend_message|| friend_message->type!=Json_Object)
			break;

		Json* apply_user_info = Json_getItem(friend_message, "apply_user_info");
		if(!apply_user_info|| apply_user_info->type!=Json_Array)
			break;

		int i;
		InviteFriendMsgList.nofriend.clear();
		for(i =0; i<Json_getSize(apply_user_info); i++)
		{
			UserNoFriendInfoStr userMsg;

			Json* msgInfo = Json_getItemAt(apply_user_info, i);
			if(!msgInfo|| msgInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(msgInfo, "userid");//product_id
			if(!handselId || handselId->type!=Json_Number)
				break;
			userMsg.id= handselId->valueint;

			Json* friendId  = Json_getItem(msgInfo, "adate");
			if(!friendId || friendId->type!=Json_String)
				break;
			userMsg.adate= friendId->valuestring;

			Json* gender  = Json_getItem(msgInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			userMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(msgInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			userMsg.headPicUr = headPicUrl->valuestring;

			Json* nickName  = Json_getItem(msgInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			userMsg.nickName= nickName->valuestring;

			InviteFriendMsgList.nofriend.push_back(userMsg);
		}

		if(i <Json_getSize(apply_user_info))
			break;

		Json* life_message = Json_getItem(content, "life_message");
		if(!life_message || life_message->type!=Json_Object)
			break;

		Json* baseInfo = Json_getItem(life_message, "base_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId = Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		getHandselMsg.myId= myId->valueint;
		InviteFriendMsgList.myId= myId->valueint;

		Json* limit_heard_num = Json_getItem(baseInfo, "limit_heard_num");
		if(!limit_heard_num || limit_heard_num->type!=Json_Number)
			break;
		getHandselMsg.heardLimit = limit_heard_num->valueint;

		Json* handselMsgInfo = Json_getItem(life_message, "handsel_life_message_info");
		if(!handselMsgInfo|| handselMsgInfo->type!=Json_Array)
			break;

		getHandselMsg.handselMsg.clear();
		for(i =0; i<Json_getSize(handselMsgInfo); i++)
		{
			UserGetHandselMsg handselMsg;

			Json* handselInfo = Json_getItemAt(handselMsgInfo, i);
			if(!handselInfo|| handselInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(handselInfo, "id");//product_id
			if(!handselId || handselId->type!=Json_Number)
				break;
			handselMsg.handselId= handselId->valueint;

			Json* friendId  = Json_getItem(handselInfo, "userid");
			if(!friendId || friendId->type!=Json_Number)
				break;
			handselMsg.friendId= friendId->valueint;

			Json* gender  = Json_getItem(handselInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			handselMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(handselInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			handselMsg.headPicUrl= headPicUrl->valuestring;

			Json* nickName  = Json_getItem(handselInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			handselMsg.nickName= nickName->valuestring;

			Json* diff_time  = Json_getItem(handselInfo, "diff_time");
			if(!diff_time || diff_time->type!=Json_Number)
				break;
			handselMsg.diff_time= diff_time->valueint;

			Json* lifeId  = Json_getItem(handselInfo, "product_id");
			if(!lifeId || lifeId->type!=Json_Number)				
				break;
			handselMsg.lifeId= lifeId->valueint;

			Json* lifePrice  = Json_getItem(handselInfo, "product_price");
			if(!lifePrice || lifePrice->type!=Json_String)			// 价格字符数据
				break;
			handselMsg.lifePrice= lifePrice->valuestring;

			Json* lifeNum  = Json_getItem(handselInfo, "product_number");
			if(!lifeNum || lifeNum->type!=Json_Number)
				break;
			handselMsg.lifeNum= lifeNum->valueint;

			Json* lifeName  = Json_getItem(handselInfo, "product_name");
			if(!lifeName || lifeName->type!=Json_String)
				break;
			handselMsg.lifeName= lifeName->valuestring;

			getHandselMsg.handselMsg.push_back(handselMsg);
		}

		if(i <Json_getSize(handselMsgInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForInviteFriendMsgG(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo = Json_getItem(content, "args_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId = Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		InviteFriendMsgList.myId= myId->valueint;

		Json* apply_user_info = Json_getItem(content, "apply_user_info");
		if(!apply_user_info|| apply_user_info->type!=Json_Array)
			break;

		int i;
		InviteFriendMsgList.nofriend.clear();
		for(i =0; i<Json_getSize(apply_user_info); i++)
		{
			UserNoFriendInfoStr userMsg;

			Json* msgInfo = Json_getItemAt(apply_user_info, i);
			if(!msgInfo|| msgInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(msgInfo, "userid");//product_id
			if(!handselId || handselId->type!=Json_Number)
				break;
			userMsg.id= handselId->valueint;

			Json* friendId  = Json_getItem(msgInfo, "adate");
			if(!friendId || friendId->type!=Json_String)
				break;
			userMsg.adate= friendId->valuestring;

			Json* gender  = Json_getItem(msgInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			userMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(msgInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			userMsg.headPicUr = headPicUrl->valuestring;

			Json* nickName  = Json_getItem(msgInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			userMsg.nickName= nickName->valuestring;

			InviteFriendMsgList.nofriend.push_back(userMsg);
		}

		if(i <Json_getSize(apply_user_info))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForSeachFriendMsgG(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* baseInfo = Json_getItem(content, "args_info");
		if(!baseInfo || baseInfo->type!=Json_Object)
			break;

		Json* myId = Json_getItem(baseInfo, "userid");
		if(!myId || myId->type!=Json_Number)
			break;
		InviteFriendMsgList.myId= myId->valueint;

		Json* user_info = Json_getItem(content, "user_info");
		if(!user_info|| user_info->type!=Json_Array)
			break;

		int i;
		SeachFriendList.nofriend.clear();
		for(i =0; i<Json_getSize(user_info); i++)
		{
			UserNoFriendInfoStr userMsg;

			Json* msgInfo = Json_getItemAt(user_info, i);
			if(!msgInfo|| msgInfo->type!=Json_Object)
				break;

			Json* handselId  = Json_getItem(msgInfo, "userid");//product_id
			if(!handselId || handselId->type!=Json_Number)
				break;
			userMsg.id= handselId->valueint;

			Json* friendId  = Json_getItem(msgInfo, "adate");
			if(!friendId || friendId->type!=Json_String)
				break;
			userMsg.adate= friendId->valuestring;

			Json* gender  = Json_getItem(msgInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			userMsg.gender= gender->valueint;

			Json* headPicUrl  = Json_getItem(msgInfo, "avatar_url");
			if(!headPicUrl || headPicUrl->type!=Json_String)
				break;
			userMsg.headPicUr = headPicUrl->valuestring;

			Json* nickName  = Json_getItem(msgInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			userMsg.nickName= nickName->valuestring;

			Json* is_friend  = Json_getItem(msgInfo, "is_friend");
			if(!is_friend || is_friend->type!=Json_Number)
				break;
			userMsg.isfriend= nickName->valueint;

			SeachFriendList.nofriend.push_back(userMsg);
		}

		if(i <Json_getSize(user_info))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setAcceptAddFriendMsgG(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		// 好友
		Json* friendsInfo 	= Json_getItem(content, "friend_info");
		if(!friendsInfo || friendsInfo->type!=Json_Array)
			break;

		int i;
		for(i =0; i<Json_getSize(friendsInfo); i++)
		{
			UserFriendInfoStr friendInfoStr;

			Json* friendInfo = Json_getItemAt(friendsInfo, i);
			if(!friendInfo|| friendInfo->type!=Json_Object)
				break;

			Json* id  = Json_getItem(friendInfo, "userid");
			if(!id || id->type!=Json_Number)
				break;
			friendInfoStr.id= id->valueint;

			Json* idx  = Json_getItem(friendInfo, "idx");
			if(!idx || idx->type!=Json_String)
				break;
			friendInfoStr.idx= idx->valuestring;

			Json* gender  = Json_getItem(friendInfo, "gender");
			if(!gender || gender->type!=Json_Number)
				break;
			friendInfoStr.gender= gender->valueint;

			Json* headPicUr  = Json_getItem(friendInfo, "avatar_url");
			if(!headPicUr || headPicUr->type!=Json_String)
				break;
			friendInfoStr.headPicUr= headPicUr->valuestring;

			Json* nickName  = Json_getItem(friendInfo, "nickname");
			if(!nickName || nickName->type!=Json_String)
				break;
			friendInfoStr.nickName= nickName->valuestring;

			Json* game_level  = Json_getItem(friendInfo, "game_level");
			if(!game_level || game_level->type!=Json_Number)
				break;
			friendInfoStr.level= game_level->valueint;

			Json* click_timestamp  = Json_getItem(friendInfo, "click_timestamp");
			if(!click_timestamp || click_timestamp->type!=Json_Number)
				break;
			friendInfoStr.click_timestamp= click_timestamp->valueint;

			Json* cur_timestamp  = Json_getItem(friendInfo, "cur_timestamp");
			if(!cur_timestamp || cur_timestamp->type!=Json_Number)
				break;
			friendInfoStr.cur_timestamp= cur_timestamp->valueint;

			Json* countdown_timestamp  = Json_getItem(friendInfo, "countdown_timestamp");
			if(!countdown_timestamp || countdown_timestamp->type!=Json_Number)
				break;
			friendInfoStr.countdown_timestamp= countdown_timestamp->valueint;

			friendInfoStr.flag= 0;

			friendInfoMsg.friendInfo.push_back(friendInfoStr);

		}

		if(i <Json_getSize(friendsInfo))
			break;

		ret = true;
	}while(0);
	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForGetSinglelevelResult(void)
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* LevelInfo = Json_getItem(content, "game_level_info");
		if(!LevelInfo|| LevelInfo->type!=Json_Array)
			break;

		int i;
		AnalyseJson::SingleLevelResultStr.friendInfo.clear();
		for( i = 0; i<Json_getSize(LevelInfo); i++)
		{
			UserSingleLevelStr itemLevel;

			Json* ItemInfo = Json_getItemAt(LevelInfo, i);
			if(!ItemInfo|| ItemInfo->type!=Json_Object)
				break;

			Json* userid  = Json_getItem(ItemInfo, "userid");
			if(!userid || userid->type!=Json_Number)
				break;
			itemLevel.id = userid->valueint;

			Json* number  = Json_getItem(ItemInfo, "number");
			if(!number || number->type!=Json_Number)
				break;
			itemLevel.result = number->valueint;

			if (itemLevel.id == AnalyseJson::logOnMsg.baseInfo.id)
			{
				itemLevel.isvip = AnalyseJson::logOnMsg.baseInfo.isVip;
				itemLevel.nickname = AnalyseJson::logOnMsg.baseInfo.nickName;
				itemLevel.gender = AnalyseJson::logOnMsg.baseInfo.gender;
				itemLevel.headPicUr = AnalyseJson::logOnMsg.baseInfo.headPicUrl;
				itemLevel.click_timestamp = 1;

				AnalyseJson::SingleLevelResultStr.friendInfo.push_back( itemLevel );

			}
			else
			{
				std::list<UserFriendInfoStr>::iterator p = AnalyseJson::friendInfoMsg.friendInfo.begin();
				for (int j = 0; j <(int) AnalyseJson::friendInfoMsg.friendInfo.size(); j++, p++)
				{
					if ( itemLevel.id == p->id )
					{
						itemLevel.isvip = p->isvip;
						itemLevel.nickname = p->nickName;
						itemLevel.gender = p->gender;
						itemLevel.headPicUr = p->headPicUr;
						itemLevel.click_timestamp = p->click_timestamp;

						AnalyseJson::SingleLevelResultStr.friendInfo.push_back( itemLevel );
						break;
					}
	
				}
			}

		}

		if(i <Json_getSize(LevelInfo))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}



void AnalyseJson::cleanData(void)
{
	return;
	memset(&logOnMsg, 0, sizeof(logOnMsg));
	memset(&levelScoreMsg, 0, sizeof(levelScoreMsg));
	memset(&friendInfoMsg, 0, sizeof(friendInfoMsg));
	memset(&nofriendInfoMsg, 0, sizeof(nofriendInfoMsg));
	memset(&lifePriceMsg, 0, sizeof(lifePriceMsg));
	memset(&buyLifeMsg, 0, sizeof(buyLifeMsg));
	memset(&handselLifeMsg, 0, sizeof(handselLifeMsg));
	memset(&getHandselMsg, 0, sizeof(getHandselMsg));
	memset(&acceptLifeMsg, 0, sizeof(acceptLifeMsg));
	memset(&consumeLifeMsg, 0, sizeof(consumeLifeMsg));
	memset(&removeSysLifeMsg, 0, sizeof(removeSysLifeMsg));
	memset(&addSysLifeMsg, 0, sizeof(addSysLifeMsg));
	memset(&propInfoMsg, 0, sizeof(propInfoMsg));
	memset(&buyPropInfo, 0, sizeof(buyPropInfo));
	memset(&handselPropInfo, 0, sizeof(handselPropInfo));
	memset(&handselPropMsg, 0, sizeof(handselPropMsg));
	memset(&acceptPropMsg, 0, sizeof(acceptPropMsg));
	memset(&claimPropMsg, 0, sizeof(claimPropMsg));
	memset(&getClaimedPropMsg, 0, sizeof(getClaimedPropMsg));
	memset(&acceptClaimedPropMsg, 0, sizeof(acceptClaimedPropMsg));
	memset(&consumePropStr, 0, sizeof(consumePropStr));
	memset(&getUserPropStr, 0, sizeof(getUserPropStr));
	memset(&propRecordStr, 0, sizeof(propRecordStr));
	memset(&refuseClaimPropStr, 0, sizeof(refuseClaimPropStr));
	memset(&allAcceptHandsel, 0, sizeof(allAcceptHandsel));
	memset(&filterFriend, 0, sizeof(filterFriend));
}

void AnalyseJson::getCandPicPath(void)
{
	std::string path = CommonData::getStorePath();
	sprintf(CandPicPath, "%s/", path.c_str());
	int a;
	a =1;
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 	char* temp =  CppCallJava::getCandyPicDir();
// 	if ( strlen(temp) != 0 )
// 	{
// 		strcpy( CandPicPath, temp);
// 		strcat( CandPicPath, (char *)"\/");
// 		CCLog( "AnalyseJson getCandPicPath path: [%s]", CandPicPath);
// 	}
// 	free(temp);
// #elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// 	sprintf(CandPicPath, "%s", "Image/wemepci/");
// #endif
}

bool AnalyseJson::setUpdataGameMsg( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		int nstatus = 0, nid = 0;
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;
		AnalyseJson::updataData.netStatus = status->valueint;

		Json* id 	= Json_getItem(root, "id");
		if(!id || id->type!=Json_Number )
			break;
		AnalyseJson::updataData.netid = id->valueint;
		
		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* title = Json_getItem(content, "title");
		if(!title || title->type!=Json_String)
			break;
		AnalyseJson::updataData.title = title->valuestring;

		Json* update_info = Json_getItem(content, "update_info");
		if(!update_info || update_info->type!=Json_String)
			break;
		AnalyseJson::updataData.update_info = update_info->valuestring;

		Json* app_name = Json_getItem(content, "app_name");
		if(!app_name || app_name->type!=Json_String)
			break;
		AnalyseJson::updataData.app_name = app_name->valuestring;

		Json* updatastatus = Json_getItem(content, "status");
		if(!updatastatus || updatastatus->type!=Json_Number)
			break;
		AnalyseJson::updataData.updataStatus = updatastatus->valueint;

		ret = true;
	}while(0);

	return ret;
}

bool AnalyseJson::setGetSystemTask( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number || status->valueint != 0)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* star = Json_getItem(content, "star");
		if(!star|| star->type!=Json_Array)
			break;

		int i;
		// 星星任务
		AnalyseJson::taskTable.startTask.clear();
		for( i = 0; i<Json_getSize(star); i++)
		{
			SystemStarStarTask item;

			Json* ItemInfo = Json_getItemAt(star, i);
			if(!ItemInfo|| ItemInfo->type!=Json_Object)
				break;

			Json* task_id  = Json_getItem(ItemInfo, "task_id");
			if(!task_id || task_id->type!=Json_Number)
				break;
			item.taskid = task_id->valueint;

			Json* type  = Json_getItem(ItemInfo, "type");
			if(!type || type->type!=Json_Number)
				break;
			item.type = type->valueint;

			Json* claim  = Json_getItem(ItemInfo, "claim");
			if(!claim || claim->type!=Json_Number)
				break;
			item.maxnum = claim->valueint;

			Json* product_id  = Json_getItem(ItemInfo, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			item.propid = product_id->valueint;

			Json* product_num  = Json_getItem(ItemInfo, "product_num");
			if(!product_num || product_num->type!=Json_Number)
				break;
			item.propnum = product_num->valueint;

			Json* total_star_consume = Json_getItem(content, "total_star_consume");
			if(!total_star_consume|| total_star_consume->type!=Json_Number)
				break;
			item.consumenum = total_star_consume->valueint;

			AnalyseJson::taskTable.startTask.push_back( item );
		}

		if(i <Json_getSize(star))
			break;


		Json* main = Json_getItem(content, "main");
		if(!star|| star->type!=Json_Array)
			break;

		// 主线任务 
		AnalyseJson::taskTable.mainTask.clear();
		for( i = 0; i<Json_getSize(main); i++)
		{
			SystemMainTask item;

			Json* ItemInfo = Json_getItemAt(main, i);
			if(!ItemInfo|| ItemInfo->type!=Json_Object)
				break;

			Json* task_id  = Json_getItem(ItemInfo, "task_id");
			if(!task_id || task_id->type!=Json_Number)
				break;
			item.taskid = task_id->valueint;

			Json* status  = Json_getItem(ItemInfo, "status");
			if(!status || status->type!=Json_Number)
				break;
			item.status = status->valueint;

			Json* claim  = Json_getItem(ItemInfo, "claim");
			if(!claim || claim->type!=Json_Number)
				break;
			item.targer = claim->valueint;

			Json* product_id  = Json_getItem(ItemInfo, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			item.propid = product_id->valueint;

			Json* product_num  = Json_getItem(ItemInfo, "product_num");
			if(!product_num || product_num->type!=Json_Number)
				break;
			item.propnum = product_num->valueint;

			Json* locked = Json_getItem(ItemInfo, "locked");
			if(!locked|| locked->type!=Json_Number)
				break;
			item.lockstate = locked->valueint;

			Json* lock_store = Json_getItem(ItemInfo, "lock_store");
			if(!lock_store|| lock_store->type!=Json_Number)
				break;
			item.lockConsumeGem = lock_store->valueint;

			Json* title = Json_getItem(ItemInfo, "title");
			if(!title|| title->type!=Json_String)
				break;
			item.title = title->valuestring;

			Json* extra = Json_getItem(ItemInfo, "extra");
			if(!extra|| extra->type!=Json_String)
				break;
			item.explain = extra->valuestring;

			AnalyseJson::taskTable.mainTask.push_back( item );
		}

		if(i <Json_getSize(main))
			break;


		Json* daily = Json_getItem(content, "daily");
		if(!star|| star->type!=Json_Array)
			break;

		// 日常任务 
		AnalyseJson::taskTable.dailyTask.clear();
		for( i = 0; i<Json_getSize(daily); i++)
		{
			SystemDailyTask item;

			Json* ItemInfo = Json_getItemAt(daily, i);
			if(!ItemInfo|| ItemInfo->type!=Json_Object)
				break;

			Json* task_id  = Json_getItem(ItemInfo, "task_id");
			if(!task_id || task_id->type!=Json_Number)
				break;
			item.taskid = task_id->valueint;

			Json* status  = Json_getItem(ItemInfo, "status");
			if(!status || status->type!=Json_Number)
				break;
			item.status = status->valueint;

			Json* claim_id  = Json_getItem(ItemInfo, "claim_id");
			if(!claim_id || claim_id->type!=Json_Number)
				break;
			item.claimid = claim_id->valueint;

			Json* claim  = Json_getItem(ItemInfo, "claim");
			if(!claim || claim->type!=Json_Number)
				break;
			item.targer = claim->valueint;

			Json* daily_type  = Json_getItem(ItemInfo, "daily_type");
			if(!daily_type || daily_type->type!=Json_Number)
				break;
			item.type = daily_type->valueint;

			Json* complete  = Json_getItem(ItemInfo, "complete");
			if(!complete || complete->type!=Json_Number)
				break;
			item.complete = complete->valueint;

			if ( 2 == item.type ) item.complete = 0;

			Json* product_num  = Json_getItem(ItemInfo, "product_num");
			if(!product_num || product_num->type!=Json_Number)
				break;
			item.gemnum = product_num->valueint;

			Json* locked = Json_getItem(ItemInfo, "locked");
			if(!locked|| locked->type!=Json_Number)
				break;
			item.lockstate = locked->valueint;

			Json* long_time = Json_getItem(ItemInfo, "long_time");
			if(!long_time|| long_time->type!=Json_Number)
				break;
			item.time = long_time->valueint;

			Json* title = Json_getItem(ItemInfo, "title");
			if(!title|| title->type!=Json_String)
				break;
			item.title = title->valuestring;

			Json* extra = Json_getItem(ItemInfo, "extra");
			if(!extra|| extra->type!=Json_String)
				break;
			item.explain = extra->valuestring;

			Json* vip_task = Json_getItem(ItemInfo, "vip_task");
			if(!vip_task|| vip_task->type!=Json_Number)
				break;
			item.isVipTask = vip_task->valueint;

			AnalyseJson::taskTable.dailyTask.push_back( item );
		}

		if(i <Json_getSize(daily))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setSubmitTask( void )
{
	bool ret = false;
	return ret;

}

bool AnalyseJson::setGetRewardTask( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		// 1 星星任务  2 主线任务  3 日常任务
		Json* task_type = Json_getItem(content, "task_type");
		if(!task_type|| task_type->type!=Json_Number)
			break;

		// 只有星星任务才会有下一组
		if (1 == task_type->valueint )
		{
			// 解析下一组任务
			AnalyseJson::taskTable.startTask.clear();
			SystemStarStarTask item;

			Json* total_star_consume = Json_getItem(content, "total_star_consume");
			if(!total_star_consume|| total_star_consume->type!=Json_Number)
				break;
			item.consumenum = total_star_consume->valueint;

			Json* star = Json_getItem(content, "next_task_info");
			if(!star|| star->type!=Json_Object)
				break;


			Json* task_id  = Json_getItem(star, "task_id");
			if(!task_id || task_id->type!=Json_Number)
				break;
			item.taskid = task_id->valueint;

			Json* type  = Json_getItem(star, "type");
			if(!type || type->type!=Json_Number)
				break;
			item.type = type->valueint;

			Json* claim  = Json_getItem(star, "claim");
			if(!claim || claim->type!=Json_Number)
				break;
			item.maxnum = claim->valueint;

			Json* product_id  = Json_getItem(star, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			item.propid = product_id->valueint;

			Json* product_num  = Json_getItem(star, "product_num");
			if(!product_num || product_num->type!=Json_Number)
				break;
			item.propnum = product_num->valueint;


			AnalyseJson::taskTable.startTask.push_back( item );
		}
		
		
		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setUnLockTaskMsg( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* content1 = Json_getItem(content, "content");
		if(!content1 || content1->type!=Json_Object)
			break;

		Json* precious_stone_number = Json_getItem(content1, "precious_stone_number");
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.baseInfo.gemNum = precious_stone_number->valueint;


		// 解析下一组主线任务
		SystemMainTask item;

		Json* ItemInfo =Json_getItem(content, "next_task_info");
		if(!ItemInfo|| ItemInfo->type!=Json_Object)
			break;

		Json* task_id  = Json_getItem(ItemInfo, "task_id");
		if(!task_id || task_id->type!=Json_Number)
			break;
		item.taskid = task_id->valueint;

		Json* status  = Json_getItem(ItemInfo, "status");
		if(!status || status->type!=Json_Number)
			break;
		item.status = status->valueint;

		Json* claim  = Json_getItem(ItemInfo, "claim");
		if(!claim || claim->type!=Json_Number)
			break;
		item.targer = claim->valueint;

		Json* product_id  = Json_getItem(ItemInfo, "product_id");
		if(!product_id || product_id->type!=Json_Number)
			break;
		item.propid = product_id->valueint;

		Json* product_num  = Json_getItem(ItemInfo, "product_num");
		if(!product_num || product_num->type!=Json_Number)
			break;
		item.propnum = product_num->valueint;

		Json* locked = Json_getItem(ItemInfo, "locked");
		if(!locked|| locked->type!=Json_Number)
			break;
		item.lockstate = locked->valueint;

		Json* lock_store = Json_getItem(ItemInfo, "lock_store");
		if(!lock_store|| lock_store->type!=Json_Number)
			break;
		item.lockConsumeGem = lock_store->valueint;

		Json* title = Json_getItem(ItemInfo, "title");
		if(!title|| title->type!=Json_String)
			break;
		item.title = title->valuestring;

		Json* extra = Json_getItem(ItemInfo, "extra");
		if(!extra|| extra->type!=Json_String)
			break;
		item.explain = extra->valuestring;

		AnalyseJson::taskTable.mainTask.push_back( item );

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForBuyFriendLimitMsg( void )
{
	bool ret = false;

	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* limit_heard_num = Json_getItem(content, "limit_friend_num");
		if(!limit_heard_num|| limit_heard_num->type!=Json_Number)
			break;
		friendInfoMsg.friendMaxNum = limit_heard_num->valueint;

		Json* stone_num = Json_getItem(content, "stone_num");
		if(!stone_num|| stone_num->type!=Json_Number)
			break;
		AnalyseJson::logOnMsg.baseInfo.gemNum = stone_num->valueint;

		ret = true;
	}while(0);
	return ret;
}

bool AnalyseJson::setWorldRankedMsg( void )
{
	bool ret = false;

	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* return_info = Json_getItem(content, "return_info");
		if(!return_info || return_info->type!=Json_Object)
			break;

		Json* world_ranking = Json_getItem(return_info, "world_ranking");
		if(!world_ranking|| world_ranking->type!=Json_Number)
			break;
		logOnMsg.baseInfo.myWorldRanked = world_ranking->valueint;

		ret = true;
	}while(0);
	return ret;
}

bool AnalyseJson::setForSignIn( void )
{
	bool ret = false;

	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* return_info = Json_getItem(content, "return_info");
		if(!return_info || return_info->type!=Json_Object)
			break;

		Json* has_sign_day = Json_getItem(return_info, "has_sign_day");
		if(!has_sign_day|| has_sign_day->type!=Json_Number)
			break;
		logOnMsg.baseInfo.hasSignInDay = has_sign_day->valueint;

		Json* registration_card_num = Json_getItem(return_info, "registration_card_num");
		if(!registration_card_num|| registration_card_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.RetroactiveCardNum = registration_card_num->valueint;


		Json* candy_currency = Json_getItem(return_info, "candy_currency");
		if(!candy_currency|| candy_currency->type!=Json_Number)
			break;
		logOnMsg.baseInfo.candyNum = candy_currency->valueint;


		Json* cur_gem = Json_getItem(return_info, "cur_gem");
		if(!cur_gem|| cur_gem->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum = cur_gem->valueint;

		Json* cur_life = Json_getItem(return_info, "cur_life");
		if(!cur_life|| cur_life->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum = cur_life->valueint;


		ret = true;
	}while(0);
	return ret;
}

bool AnalyseJson::setForBuyRetroactive( void )
{
	bool ret = false;

	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "status");
		if(!status || status->type!=Json_Number )
			break;

		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* return_info = Json_getItem(content, "return_info");
		if(!return_info || return_info->type!=Json_Object)
			break;

		Json* precious_stone_number = Json_getItem(return_info, "precious_stone_number");
		if(!precious_stone_number|| precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum = precious_stone_number->valueint;

		Json* sign_card_num = Json_getItem(return_info, "sign_card_num");
		if(!sign_card_num|| sign_card_num->type!=Json_Number)
			break;
		logOnMsg.baseInfo.RetroactiveCardNum = sign_card_num->valueint;

		ret = true;
	}while(0);
	return ret;
}

bool AnalyseJson::setForUnlockLevel( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;


		Json* content = Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* return_info = Json_getItem(content, "return_info");
		if(!return_info || return_info->type!=Json_Object)
			break;

		Json* precious_stone_number  = Json_getItem(return_info, "precious_stone_number");
		if(!precious_stone_number || precious_stone_number->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum = precious_stone_number->valueint;

		Json* game_level  = Json_getItem(return_info, "game_level");
		if(!game_level || game_level->type!=Json_Number)
			break;
		int level = game_level->valueint;

		std::list<UserUnlockLevelInfo>::iterator p = logOnMsg.unlockInfo.begin();
		std::list<UserUnlockLevelInfo>::iterator pEnd = logOnMsg.unlockInfo.end();
		for(;p != pEnd; ++p)
		{
			if(level == p->level)
				break;
		}
		if(p == pEnd)
		{
			break;
		}

		Json* unlocked  = Json_getItem(return_info, "unlocked");
		if(!unlocked || unlocked->type!=Json_Number)
			break;
		p->unlocked = unlocked->valueint;

		ret = true;
	}while(0);

	Json_dispose(root);

	return ret;
}

bool AnalyseJson::setForRouletteReward( void )
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content 	= Json_getItem(root, "content");
		if(!content || content->type!=Json_Object)
			break;

		Json* cur_life = Json_getItem(content, "cur_life");
		if(!cur_life || cur_life->type!=Json_Number)
			break;
		logOnMsg.lifeInfo.lifeNum = cur_life->valueint;

		Json* cur_gem = Json_getItem(content, "cur_gem");
		if(!cur_gem || cur_gem->type!=Json_Number)
			break;
		logOnMsg.baseInfo.gemNum = cur_gem->valueint;

		Json* candy_currency = Json_getItem(content, "candy_currency");
		if(!candy_currency || candy_currency->type!=Json_Number)
			break;
		logOnMsg.baseInfo.candyNum = candy_currency->valueint;

		Json* product_info = Json_getItem(content, "product_info");
		if(!product_info || product_info->type!=Json_Array)
			break;

		int i = 0;
		for(i =0; i<Json_getSize(product_info); i++)
		{
			Json* products_item = Json_getItemAt(product_info, i);
			if(!products_item|| products_item->type!=Json_Object)
				break;

			Json* product_id  = Json_getItem(products_item, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			int productId = product_id->valueint;

			Json* product_number  = Json_getItem(products_item, "product_number");
			if(!product_number || product_number->type!=Json_Number)
				break;
			int productNumber = product_number->valueint;

			std::list<UserPropInfoStr>::iterator iter = logOnMsg.propInfo.begin();
			std::list<UserPropInfoStr>::iterator iterend = logOnMsg.propInfo.end();
			for(; iter != iterend ;++iter)
			{
				if(productId == iter->id)
				{
					iter->num = productNumber;
					break;
				}
			}
		}

		if(i <Json_getSize(product_info))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return ret;
}

bool AnalyseJson::setForRoulettePercent( void )
{
	unsigned long file_size = 0;

	unsigned char *tmp = NULL;
	tmp = CCFileUtils::sharedFileUtils()->getFileData("jsonRoulette.txt","rb",&file_size);

	if(file_size <=0 || file_size >= JSON_STRING_LEN)
		return false;

	memcpy(&AnalyseJson::jsonString[0], &(tmp[0]), file_size);
	AnalyseJson::jsonString[file_size] = '\0';


	bool ret = false;
	Json* root	= Json_create(jsonString);
	do
	{
	  	if(!root || root->type!=Json_Object)
	  		break;
	  
	  	Json* status 	= Json_getItem(root, "id");
	  	if(!status || status->type!=Json_Number)
	  		break;
	  
	  	Json* content 	= Json_getItem(root, "content");
	  	if(!content || content->type!=Json_Array)
	  		break;
	  
	 	int i = 0;
	 	for(i =0; i<Json_getSize(content); i++)
	 	{
			RouleteRatio rr;
	 		Json* products_item = Json_getItemAt(content, i);
	 		if(!products_item|| products_item->type!=Json_Object)
	 			break;
	 
	 		Json* product_id  = Json_getItem(products_item, "p_id");
	 		if(!product_id || product_id->type!=Json_Number)
	 			break;
	 		rr.RewardId = product_id->valueint;
	 
	 		Json* rewardname  = Json_getItem(products_item, "name");
	 		if(!rewardname || rewardname->type!=Json_String)
	 			break;
	 		rr.RewardName = rewardname->valuestring;

			Json* rewardRatio = Json_getItem(products_item, "chance");
			if (!rewardRatio || rewardRatio->type != Json_Number)
				break;
			rr.RewardRatio = rewardRatio->valueint;
	 
	 		AnalyseJson::RouleteRatioVec.push_back(rr);
	 	}
	 
	 	if(i <Json_getSize(content))
	 		break;
	 
	 	ret = true;
	}while(0);
	 
	Json_dispose(root);
	return true;
}

bool AnalyseJson::setForCollectStarReward()
{
	bool ret = false;
	Json* root = Json_create(jsonString);
	do
	{
		if(!root || root->type!=Json_Object)
			break;

		Json* status 	= Json_getItem(root, "id");
		if(!status || status->type!=Json_Number)
			break;

		Json* content 	= Json_getItem(root, "content");
		if(!content || content->type!= Json_Object)
			break;

		Json* cur_life = Json_getItem(content, "cur_life");
		if (!cur_life || cur_life->type != Json_Number)
			break;
		AnalyseJson::logOnMsg.lifeInfo.lifeNum = cur_life->valueint;

		Json* property_info = Json_getItem(content, "property_info");
		if (!property_info || property_info->type != Json_Array)
		{
			break;
		}

		AnalyseJson::logOnMsg.propInfo.clear();
		int i = 0;
		for( i = 0; i<Json_getSize(property_info); i++)
		{
			UserPropInfoStr propInfo;
			Json* products_item = Json_getItemAt(property_info, i);
			if(!products_item|| products_item->type!=Json_Object)
				break;

			Json* product_id  = Json_getItem(products_item, "product_id");
			if(!product_id || product_id->type!=Json_Number)
				break;
			propInfo.id = product_id->valueint;

			Json* product_name  = Json_getItem(products_item, "product_name");
			if(!product_name || product_name->type!=Json_String)
				break;
			propInfo.name = product_name->valuestring;

			Json* product_number = Json_getItem(products_item, "product_number");
			if (!product_number || product_number->type != Json_Number)
				break;
			propInfo.num = product_number->valueint;

			AnalyseJson::logOnMsg.propInfo.push_back(propInfo);
		}

		if(i <Json_getSize(content))
			break;

		ret = true;
	}while(0);

	Json_dispose(root);
	return true;
}
