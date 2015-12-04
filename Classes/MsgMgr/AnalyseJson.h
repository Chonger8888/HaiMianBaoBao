#ifndef ANALYSE_JSON__H
#define ANALYSE_JSON__H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define JSON_STRING_LEN		1024*50

typedef enum
{
	//RECODING_MSG_ACTIONID_8, 			//退出时间											"1328",

	//RECODING_MSG_ACTIONID_9, 			// 	进图Loading									  "2000",
	//RECODING_MSG_ACTIONID_10, 			// 	大地图到达									   "2001",
	//RECODING_MSG_ACTIONID_11, 			// 	关卡ID										  "2002",

	//RECODING_MSG_ACTIONID_12, 			// 	关卡Loading									  "2003",
	//RECODING_MSG_ACTIONID_13, 			// 	关卡到达			2004						"2004",
	//RECODING_MSG_ACTIONID_14, 			// 	弹出关卡1_UI									"2005",
	//RECODING_MSG_ACTIONID_15, 			// 	关闭关卡1_UI									"2006",
	//RECODING_MSG_ACTIONID_16, 			// 	点击关卡1_"Play"								"2007",
	//RECODING_MSG_ACTIONID_17, 			// 	到达关卡1_游戏中  2008							 "2008",
	//RECODING_MSG_ACTIONID_18, 			// 	完成关卡1_新手引导								"2009",
	//RECODING_MSG_ACTIONID_19, 			// 	关卡1_过关  2010								"2010",
	//RECODING_MSG_ACTIONID_20, 			// 	弹出关卡1_下一关UI								 "2011",
	//RECODING_MSG_ACTIONID_21, 			// 	点击关卡1_下一关按钮							   "2012",

	//RECODING_MSG_ACTIONID_23, 			// 	第几次闯关									   "2014",
	//RECODING_MSG_ACTIONID_24, 			// 	道具类型										"2015",
	//RECODING_MSG_ACTIONID_25, 			// 	使用时剩余生命									 "2016",
	//RECODING_MSG_ACTIONID_26, 			// 	使用时剩余步数									 "2017",
	//RECODING_MSG_ACTIONID_28, 			// 	使用时间										"2019",

	//RECODING_MSG_ACTIONID_29, 			// 	定单号								 "2021"
	//RECODING_MSG_ACTIONID_30, 			// 	流水号								  "2022"
	//RECODING_MSG_ACTIONID_31, 			// 	购买物品							 "2023"
	//RECODING_MSG_ACTIONID_32, 			// 	购买金额							 "2024"
	//RECODING_MSG_ACTIONID_33, 			// 	购买时间							 "2025"
	//RECODING_MSG_ACTIONID_34, 			// 	支付方式							 "2026"
	//RECODING_MSG_ACTIONID_35, 			// 	是否结算							 "2027"
	//RECODING_MSG_ACTIONID_36, 			// 	UID									 "2028"
	//RECODING_MSG_ACTIONID_38, 			// 	剩余生命							 "2030"
	//RECODING_MSG_ACTIONID_39, 			// 	剩余步数							 "2031"
	//RECODING_MSG_ACTIONID_41, 			// 	点击微米图标						   "2033"
	//RECODING_MSG_ACTIONID_42, 			// 	点击反馈图标						   "2034"
	//RECODING_MSG_ACTIONID_43, 			// 	点击公告图标						   "2035"
	//RECODING_MSG_ACTIONID_44, 			// 	点击游戏外帮助						  "2036"
	//RECODING_MSG_ACTIONID_45, 			// 	点击游戏内帮助						  "2037"
	//RECODING_MSG_ACTIONID_46,			// 	返回地图loading						 "2038"
	//RECODING_MSG_ACTIONID_47,			// 	到达大地图							"2039"
	//RECODING_MSG_ACTIONID_48,			// 	移动头像							 "2040"

	//// 1.2版本
	//RECODING_MSG_ACTIONID_49,			// 	出现过场动画		                                  "2041"	
	//RECODING_MSG_ACTIONID_50,			// 	剧情动画下一步①									  "2042"
	//RECODING_MSG_ACTIONID_51,			// 	剧情动画跳过①										  "2043"
	//RECODING_MSG_ACTIONID_52,			// 	剧情动画下一步②									  "2044"
	//RECODING_MSG_ACTIONID_53,			// 	剧情动画跳过②										  "2045"
	//RECODING_MSG_ACTIONID_54,			// 	剧情动画下一步③									  "2046"
	//RECODING_MSG_ACTIONID_55,			// 	剧情动画跳过③										   "2047"

	//RECODING_MSG_ACTIONID_56,			// 	进第一关Loading										  "2048"

	//RECODING_MSG_ACTIONID_57,			// 	第一关到达											 "2049"  
	//RECODING_MSG_ACTIONID_58,			// 	出现新手指引											"2050"

	//RECODING_MSG_ACTIONID_59,			// 	第一关第一步跳过									  "2051"
	//RECODING_MSG_ACTIONID_60,			// 	第一关第二步跳过									  "2052"
	//RECODING_MSG_ACTIONID_61,			// 	第一关第三步我知道了									"2053"
	//RECODING_MSG_ACTIONID_62,			// 	第一关关卡完成										  "2054"
	//RECODING_MSG_ACTIONID_63,			// 	弹出第一关奖励道具界面								   "2055"
	//RECODING_MSG_ACTIONID_64,			// 	第一关道具领取										   "2056"
	//RECODING_MSG_ACTIONID_65,			// 	弹出第一关胜利UI									   "2057"
	//RECODING_MSG_ACTIONID_66,			// 	返回地图的Loading									 "2058"
	//RECODING_MSG_ACTIONID_67,			// 	大地图到达											 "2059"1111111111

	//RECODING_MSG_ACTIONID_68,			// 	播放行走动画											"2060"
	//RECODING_MSG_ACTIONID_69,			// 	弹出第二关关卡介绍									 "2061"
	//RECODING_MSG_ACTIONID_70,			// 	第二关开始游戏按钮									 "2062"
	//RECODING_MSG_ACTIONID_71,			// 	第二关关闭按钮										   "2063"
	//RECODING_MSG_ACTIONID_72,			// 	进第二关Loading										  "2064"
	//RECODING_MSG_ACTIONID_73,			// 	第二关到达											 "2065"
	//RECODING_MSG_ACTIONID_74,			// 	第二关完成											 "2066"
	//RECODING_MSG_ACTIONID_75,			// 	弹出第二关胜利UI									   "2067"
	//RECODING_MSG_ACTIONID_76,			// 	返回地图的Loading									 "2068"
	//RECODING_MSG_ACTIONID_77,			// 	大地图到达											 "2069"11111
	//RECODING_MSG_ACTIONID_78,			// 	播放行走动画											"2070"
	//RECODING_MSG_ACTIONID_79,			// 	弹出第三关关卡介绍									 "2071"
	//RECODING_MSG_ACTIONID_80,			// 	第三关开始游戏按钮									 "2072"
	//RECODING_MSG_ACTIONID_81,			// 	第三关关闭按钮										  "2073"
	//RECODING_MSG_ACTIONID_82,			// 	进第二关Loading										  "2074"
	//RECODING_MSG_ACTIONID_83,			// 	第三关到达											 "2075"
	//RECODING_MSG_ACTIONID_84,			// 	出现新手指引											"2076"
	//RECODING_MSG_ACTIONID_85,			// 	第三关第一步跳过									  "2077"
	//RECODING_MSG_ACTIONID_86,			// 	第三关第二步跳过									  "2078"
	//RECODING_MSG_ACTIONID_87,			// 	第三关第三步我知道了									"2079"
	//RECODING_MSG_ACTIONID_88,			// 	第三关关卡完成										   "2080"
	//RECODING_MSG_ACTIONID_89,			// 	弹出第三关奖励道具界面								   "2081"
	//RECODING_MSG_ACTIONID_90,			// 	第三关道具领取										   "2082"
	//RECODING_MSG_ACTIONID_91,			// 	弹出第五关奖励道具界面								   "2083"
	//RECODING_MSG_ACTIONID_92,			// 	第五关道具领取										   "2084"
	//RECODING_MSG_ACTIONID_4001,			// 	4001	出现登录的Loading
	//RECODING_MSG_ACTIONID_4002,			// 	4002	出现"拼命加载中"文字	
	//RECODING_MSG_ACTIONID_4003,			// 	4003	出现"加载关卡数据"
	//RECODING_MSG_ACTIONID_4004,			// 	4004	进入封面
	//RECODING_MSG_ACTIONID_4005,			// 	4005	点击开始游戏
	//RECODING_MSG_ACTIONID_4006,			// 	4006	进入大地图
	//RECODING_MSG_ACTIONID_4007,			// 	4007	点击各个界面的炫耀
	//RECODING_MSG_ACTIONID_1319,			// 	1319	登录
	//RECODING_MSG_ACTIONID_4008,			// 	4008	重玩
	//RECODING_MSG_ACTIONID_4009,			// 	4009	购买消耗统计

	//RECODING_MSG_ACTIONID_4010,			// 	4010	点击VIP购买
	//RECODING_MSG_ACTIONID_4011,			// 	4011	糖果之旅解锁 o o
	//RECODING_MSG_ACTIONID_4012,			// 	4012	糖果之旅任务完成
	//RECODING_MSG_ACTIONID_4013,			// 	1313	商城购买
	//RECODING_MSG_ACTIONID_4014,			// 	4014	日常任务完成领取宝石
	//RECODING_MSG_ACTIONID_4015,			// 	4015	好友上限扩充
	//RECODING_MSG_ACTIONID_4016,			// 	4016	购买统计  进入ＳＤＫ界面

	//// 3.0.0
	//RECODING_MSG_ACTIONID_4017,			// 	4017	礼包领取
	//RECODING_MSG_ACTIONID_4018,			// 	4018	ＶＩＰ奖　领取	

	RECODING_MSG_ACTIONID_1, 			//玩家每闯一关要进行记录							"1321",
	RECODING_MSG_ACTIONID_2, 			//同一关卡进行多次更新计数							"1322",
	RECODING_MSG_ACTIONID_3, 			//如有使用道具进行标记								"1323",
	RECODING_MSG_ACTIONID_4, 			//是否退出时生命为零								"1324",
	RECODING_MSG_ACTIONID_5, 			//是否同一关超过3次没过退出							"1325",
	RECODING_MSG_ACTIONID_6, 			//是否第一关没过									"1326",
	RECODING_MSG_ACTIONID_7, 			//是否没有符合条件符合没回头						"1327",
	RECODING_MSG_ACTIONID_22, 			// 	关卡ID											"2013",
	RECODING_MSG_ACTIONID_27, 			// 	是否过关										"2018",
	RECODING_MSG_ACTIONID_37, 			// 	关卡ID											"2029",
	RECODING_MSG_ACTIONID_40, 			// 	点击+5继续										"2032",
	//mini版本新增记录点
	RECODING_MSG_ACTIONID_1002,			//到达开始游戏										"1002",
	RECODING_MSG_ACTIONID_1003,			//点击开始按钮										"1003",
	RECODING_MSG_ACTIONID_1004,			//进入游戏界面										"1004",
	RECODING_MSG_ACTIONID_1005,			//点击关卡											"1005",
	RECODING_MSG_ACTIONID_1006,			//进入关卡loading									"1006",
	RECODING_MSG_ACTIONID_1007,			//进入关卡内										"1007",

	RECODING_MSG_NUM	  	

}RecordingMsgType;			
							
enum
{
	SEX_BOY = 0,
	SEX_GIRL = 1,
};

typedef struct
{
	int netStatus;
	int netid;
	int updataStatus;
	string title;
	string update_info;
	string app_name;
}UpdataGameInfo;

// 用户基础信息
typedef struct
{
	int		id;				// 用户标识
	int		gender;			// 性别 0男 1女 －1未设置
	int		skill_one_num;  // 罐子能量
	int		all_skill;		// 罐子上限
	int		jar_replay_time;	//神灯恢复时间
	int		jar_price;			//神灯总价格
	int		jar_hour_reduce;	//神灯单次扣除价格
	int		gemNum;				//　宝石数量
	int		candyNum;			// 糖币果数
	int		Chitchat;
	int		avatar_upd_times;	// 第一次修改资料
	int		isFirstModify;
	int		isFirstLogin;
	int		isVip;			// 0 非Vip  1 一周vip   2 一月vip   3 永久vip
	int		vipLength;		
	int		friendLack;
	int		isNotice;		// 0 没有公告 1有公告
	int		failNum;		// 最大关卡失败次数
	int		today_has_receice;		//是否已经领取VIP礼包 0未领取 1领取
	int		myWorldRanked;	//　我的世界排名

	int		MaxSignInDay;		//　应签到天数　　　　
	int		practicalSignInDay; //　当前可签到天
	int     hasSignInDay;		//　实际已签
	int		IsRetroactive;		//　是否可补签
	int		RetroactiveCardNum; //　补签卡数量
	int		RetroactiveCatdPrice; //补签卡价格
	int		today_Roulette_num;	//每日转盘剩余次数
	int		Roulette_UseCandy;	//转盘需要的糖果币数量
	int		isBuySuperGift;		//是否购买过超级礼包
	int		isUsePropToday;		//今天是否点击过道具
	int		SuperGiftId;		//超级礼包ID
	int		openkkSdk;			//KKsdk是否开启
	int		isNewUser;			//是否为新用户

	string	qq;
	string  idx;
	string  version;
	string  packpag;
	string	updataver;
	string  channel;
	string	headPicUrl;		// 头像Url
	string	nickName;		// 昵称
}UserBaseInfoStr;

// 用户生命信息
typedef struct
{
	int		lifeCountDown;	// 生命倒计时时间
	int		flag;
	int		lifeNum;		// 生命个数
	int		first_consums;	// 首次消耗生命
	string	price;			// 价格
}UserLifeInfoStr;

// 用户道具信息
typedef struct
{
	int		id;				// 道具标识
	int		num;			// 道具数量
	int		priceType;		//　货币类型　1宝　２糖果　3 all
	string	candyprice;		//　糖果币价格
	string	price;			// 价格
	string	name;			// 道具名称
}UserPropInfoStr;

// 用户VIP信息
typedef struct
{
	int		id;				
	std::string 	price;			
}UserVipInfoStr;

// 礼包信息
typedef struct
{
	int		id;				
	int 	price;		
	int		type;
	int		pop_pack;
}UserPackInfoStr;

// 关卡解锁信息
typedef struct
{
	int		level;				//解锁关卡	
	int 	needStar;			//解锁需要的星星数
	int		unlocked;			//是否已经解锁	0未解锁 1已解锁
}UserUnlockLevelInfo;

// 用户关卡信息
typedef struct UserStageInfo
{

public:
	int		level;			// 关卡数
	int		score;			// 关卡分数
	int		starnum;
	
public:	
	bool operator < (struct UserStageInfo b){return level < b.level;};
	bool operator > (struct UserStageInfo b){return level > b.level;};	
		
}UserStageInfoStr;

typedef struct PreciousConfInfo
{
	int		preciousid;
	int		preciousnum;
	string	preciousprice;
	string	preciousname;
}PreciousInfoStr;

// 用户消息
typedef struct
{
	int		num;			// 消息个数
}UserMsgInfoStr;

// 过滤后的IDX
typedef struct
{
	string idx;
}UserFilterIdxStr;


typedef struct 
{
	int						state;
	string					noticeDate;
	string					noticeData;
}UserNoticeStr;

// 用户获得道具相关消息
typedef struct
{
	int		handselId;		// 赠送的ID
	int		friendId;		// 好友ID
	int		gender;			// 好友性别
	string	headPicUrl;		// 好友头像URL
	string	nickName;		// 好友昵称
	int		diff_time;
	int		lifeId;			// 生命ID
	string	lifePrice;		// 生命价格
	int		lifeNum;		// 生命个数
	string	lifeName;		// 生命名称
}UserGetHandselMsg;


// 
typedef struct
{
	int			id;
	string		idx;
	int			gender;
	int			flag;//　是否赠送生命
	int			level;
	int			isvip;
	unsigned int click_timestamp;	
	unsigned int cur_timestamp;	
	unsigned int countdown_timestamp;	
	string		headPicUr;
	string		nickName;
}UserFriendInfoStr;

typedef struct 
{
	int id;
	int gender;
	int result;
	int isvip;
	string nickname;
	string headPicUr;
	unsigned int click_timestamp;	
}UserSingleLevelStr;

typedef struct
{
	int			id;
	string		idx;
	int			gender;
	string		headPicUr;
	string		nickName;
	string		adate;
	int			isfriend;
	bool		isSelect;
	bool		isInvite;
}UserNoFriendInfoStr;

typedef struct
{
	string		idx;
}UserNoFriendIdxStr;

typedef struct
{
	int			userId;
	int			propId;
	int			proNum;
	string		propPrice;
}UserBuyPropBaseInfoStr;

typedef struct
{
	int			myId;
	int			friendId;
	int			propId;
	int			propNum;
	string		propPrice;
}UserHandselPropBaseStr;

typedef struct
{
	int		handselId;		
	int		friendId;		
	int		gender;			
	string	headPicUrl;		
	string	nickName;
	int		diffTime;
	int		propId;		
	string	propPrice;		
	int		propNum;
	string	propName;
}UserGetHandselPropMsg;

typedef struct
{
	int				acceptId;
	int				friendId;
	int				gender;
	string			headPicUrl;
	string			nickName;
	int				diff_time;
	int				propId;
	int				propNum;
	string			propName;
	string			propPrice;
}UserGetClaimedPropMsg;

typedef struct
{
	int				id;
	int				userId;
	int				type;
	int				flag;  // 0 - 3 类型
	int				gender;
	string			headPicUrl;
	string			nickName;
	int				propId;
	string			propName;
	int				propNum;
	string			propPrice;
	string			timeStar;
	string			timeEnd;
}UserPropRecordMsg;

typedef struct  
{
	int RewardId;			//奖品ID
	int RewardRatio;		//奖品概率
	std::string RewardName;	//奖品名称
}RouleteRatio;

// 过关奖励糖果币公式配置
typedef struct  
{
	float growth_factor;
	float growth_value;
	float one_star;
	float two_star;
	float third_star;
}SystemRewardLevelCandyConfig;

//星星收集数据
typedef struct  
{
	int		level;
	int		receive;	//0代表白银礼箱，1代表黄金礼箱
}CollectStarStruct;

typedef struct
{
	UserBaseInfoStr		baseInfo;
	UserLifeInfoStr		lifeInfo;
	SystemRewardLevelCandyConfig	rewardCandyConfig;//过关时奖励糖果公式配置
	list<UserPropInfoStr> 	propInfo;
	list<UserStageInfoStr> 	stageInfo;
	list<PreciousInfoStr>	preciousConfig;
	list<UserPropInfoStr>	specialProp;
	list<UserVipInfoStr>	vipConfig;
	list<UserPackInfoStr>	packInfo;
	list<UserUnlockLevelInfo>	unlockInfo;
	list<CollectStarStruct>	collectInfo;

}UserLogOnSr;

typedef struct
{
	int						myId;
	int						friendNum;
	int						friendMaxNum;
	string					myIdx;
	string					friendIdx;
	list<UserFriendInfoStr> 	friendInfo;
	list<UserNoFriendIdxStr>	nofriend_idx;
}UserFriendStr;

typedef struct 
{
	int level;
	list<UserSingleLevelStr> 	friendInfo;
}UserSingleLevelResultStr;

typedef struct  
{
	int							myid;
	string						myIdx;
	string						inviteidx;
	list<UserFilterIdxStr>		FilterIdx;
}UserFilterFriendStr;

typedef struct
{
	int							myId;
	list<UserNoFriendInfoStr>	nofriend;
}UserNoFriendStr;

typedef struct
{
	int		userId;
	int		level;
	int		score;
}UserLevelScoreStr;

typedef struct
{
	int		lifeId;
	string	price;
	string	name;
}UserLifePriceStr;

typedef struct
{
	int		userId;
	int		buyNum;
	string	price;
	int		totalLife;
	int		flag;
}UserBuyLifeStr;

typedef struct
{
	int		myId;
	int		friendId;
}UserHandselLifeStr;

typedef struct
{
	int						myId;
	int						heardLimit;
	list<UserGetHandselMsg> 	handselMsg;
}UserGetHandselMsgStr;

typedef struct
{
	int			handselId;
	int			userId;
	int			totalLife;
	int			flag;
}UserAcceptLifeStr;

typedef struct
{
	int			userId;
	int			consumeNum;
	int			totalLife;
	int			flag;
	int			lifeCountDown;
}UserConsumeLifeStr;

typedef struct
{
	int			userId;
}UserRemoveSysLifeStr;

typedef struct
{
	int			userId;
	int			totalLife;
	int			flag;
	int			lifeCountDown;
}UserAddSysLifeStr;

typedef struct
{
	int		id;				
	string	price;			
	string	name;
}UserPropsInfoStr;

typedef struct
{
	UserLifeInfoStr 			lifeInfo;
	list<UserPropInfoStr> 		stagePropInfo;
}UserBuyPropInfoStr;

typedef struct
{
	UserHandselPropBaseStr	baseInfo;
	list<UserPropInfoStr> 		stagePropInfo;
}UserHandselPropStr;

typedef struct
{
	int					 		userId;
	list<UserGetHandselPropMsg> 	handselStageProp;
}UserGetHandselPropStr;

typedef struct
{
	int						acceptId;
	int						userId;
	list<UserPropInfoStr> 		stagePropInfo;
}UserAcceptPropStr;

typedef struct
{
	int				myId;
	int				friendId;
	int				propId;
	string			propPrice;
	int				propNum;
}UserClaimPropStr;

typedef struct
{
	int				propId;
	int				myId;
	int				friendId;
}UserRefuseClaimPropStr;


typedef struct  
{
	int							myId;
	UserLifeInfoStr				myLifeInfo;
	list<UserPropInfoStr>			stagePropInfo;
}UserAllAcceptHandselStr;

typedef struct
{
	int							myId;
	list<UserGetClaimedPropMsg> 	msg;
}UserGetClaimedPropStr;

typedef struct
{
	int						claimedPropId;
	list<UserPropInfoStr> 		stagePropInfo;
}UserAcceptClaimedPropStr;

typedef struct
{		
	int						myId;
	int						propId;
	string					propName;
	list<UserPropInfoStr> 		stagePropInfo;
}UserConsumePropStr;

typedef struct
{
	int						userId;
	int						propId;
	int						propNum;
}UserGetUserPropStr;

typedef struct
{
	int						userId;
	list<UserPropRecordMsg> 	propRecord;
}UserPropRecordStr;

typedef struct
{							
	int					isGameState;
}UserGameState;

typedef struct 
{
	int			myid;
	UserPropInfoStr giveProp;
}SystemGivePropStr;

typedef struct
{
	int				gemprice;
	std::string		usetime;
}UserEnergyUseTime;

typedef struct
{
	int				hasMagicLamp;			//是否有神灯	
	int				magicLampTime;			//神灯恢复剩余时间
}MagicLampInfo;

typedef struct
{
	int status;
	list<std::string>	headUrl;
}SystemHeadUrlStr;

typedef struct  
{
	int taskid;
	int maxnum;
	int type;
	int propid;
	int propnum;
	int consumenum;
	string taskname; 
}SystemStarStarTask;

typedef struct
{
	int taskid;				// 任务ID
	int targer;				// 任务目标
	int propid;				// 奖励道具ID
	int propnum;			// 奖励数
	int lockstate;			// 0 已解  1 未解
	int lockConsumeGem;		// 解锁需消耗宝石数
	int status;				// 领取状态  0未领取  1已领取
	std::string title;		// 任务标题	
	std::string explain;	// 任务说明	
}SystemMainTask;

typedef struct
{
	int taskid;				// 任务ID
	int targer;				// 任务目标
	int gemnum;				// 奖励宝石数
	int lockstate;			// 0 已解  1 未解	2非VIP任务
	int status;				// 领取状态  0未领取  1已领取
	int	type;				// 任务类型 1 糖果收集类  2关卡达成星星类
	int	claimid;			// 关卡数/糖果id
	int complete;			// 当前完成数
	int isVipTask;			// 0 非Vip任务  1 VIP任务
	unsigned int time;		// 任务倒计时 
	std::string title;		// 任务标题	
	std::string explain;	// 任务说明	
}SystemDailyTask;

typedef struct 
{
	int curstarnum;
	int taskstatus;
	int buytaskid;
	list<SystemStarStarTask> startTask;
	list<SystemMainTask>	mainTask;
	list<SystemDailyTask>	dailyTask;
}SystemTask;

typedef struct  
{
	int		starTask;
	int		mainTask;
	int		dailyTask;
	int		friendFun;
}FunctionUnLockLevel;

typedef struct  
{
	int		propnum;
	int		proptype;//1:糖果币；2:宝石；3:生命
}SignReward;

typedef struct 
{
	int SignInDay;			//　签到天标签
	std::list<SignReward> signReward;	//　签到天奖励信息
}SystemSignInConfig;

typedef struct 
{
	int idx;
	std::list<SystemSignInConfig> signInConfig;
}SignInConfigStr;


class AnalyseJson
{
	public:
		static bool setUpdataGameMsg(void);
		static bool setSoundOutMsg(void);
		static bool setRegeditMsg(void);
		static bool setLogOnMsg(void);
		static bool setLevelScoreMsg(void);
		static bool setUserFriendInfoMsg(char *jsonData);
		static bool setNoFriendInfoMsg(char *jsonData);
		static bool setFriendInfoForGuestMsg(void);
		static bool setWorldFriendInfoForGuestMsg(void);
		static bool setNoFriendInfoForGuestMsg(void);
		static bool setGetLifePriceMsg(void);
		static bool setBuyLifeMsg(void);
		static bool setHandselLifeMsg(void);
		static bool setGetHandselMsg(void);
		static bool setAcceptLifeMsg(void);
		static bool setConsumeLifeMsg(void);
		static bool setRemoveSysLifeMsg(void);
		static bool setAddSysLifeMsg(void);
		static bool setGetPropInfoMsg(void);
		static bool setBuyPropMsg(void);
		static bool setHandselPropMsg(void);
		static bool setGetHandselPropMsg(void);
		static bool setAcceptPropMsg(void);
		static bool setClaimPropMsg(void);
		static bool setGetClaimedPropMsg(void);
		static bool setAcceptClaimedPropMsg(void);
		static bool setConsumePropMsg(void);
		static bool setGetUserPropMsg(void);
		static bool setGetPropRecordMsg(void);
		static bool setRefuseClaimedProp(void);
		static bool setAllAcceptHandselMsg(void);
		static bool setForFilterNoFriend(void);
		static bool setForNoFriendInfoMsg(char *jsonData = NULL);
		static bool setForInviteFriendMsg(void);
		static bool setFeedbackInfo(void);
		static bool setForNoticeData(void);
		static bool setForChitchat(void);
		static bool setGameState(void);
		static bool setSystemGiveProp(void);
		static bool setSystemHeadUrl(void);

		// buy gem
		static bool setForGemBuyVip(void);
		static bool setForGemBuyProp(void);
		static bool setForGemBuyLife(void);
		static bool setForGemBuySkill(void);
		static bool setForGemBuyPackage(void);
		static bool setForUpdateGemNum(void);

		static bool setForMyAllMsgG(void);
		static bool setForInviteFriendMsgG(void);
		static bool setForSeachFriendMsgG(void);
		static bool setForBuyFriendLimitMsg(void);

		static bool setAcceptAddFriendMsgG(void);
		static bool setForGetSinglelevelResult(void);

		static void setRecordHeadMsg( RecordingMsgType type);
		static void setRecordMsgAppend(const  char* string);
		static void setRecordingMsg(RecordingMsgType type, const char* string1=NULL,const char *string2=NULL, 
							const char *string3=NULL,const char *string4=NULL,const char *string5=NULL);


		static void getCandPicPath(void);

		static void cleanData(void);
		static void SaveDeviceAndUid(char* device, char* uid, char* version,char* channel);	
		static void SavePlatfromData(string idx, string channel, string version, string packpagname, string updataver);
		static bool setEnergyUseNum(void);
		static bool setMagicLampTime(void);
		static bool setUseMagicLamp(void);

		// task
		static bool setGetSystemTask(void);
		static bool setSubmitTask(void);
		static bool setGetRewardTask(void);
		static bool setUnLockTaskMsg(void);

		static bool setWorldRankedMsg(void);

		static bool setForRewardVip(void);

		//　signIn
		static bool setForSignIn(void);
		static bool setForBuyRetroactive(void);

		static bool setForUnlockLevel(void);
		static bool setForRouletteReward(void);

		static bool setForRoulettePercent(void);

		//收集星星
		static bool setForCollectStarReward();

		
	public:
		static UpdataGameInfo	updataData;
		static UserLogOnSr 		logOnMsg;
		static SystemTask		taskTable;
		static UserLevelScoreStr		levelScoreMsg;
		static UserFriendStr		worldFriendInfoMsg;
		static UserFriendStr		friendInfoMsg;
		static UserNoFriendStr		nofriendInfoMsg;
		static UserLifePriceStr		lifePriceMsg;
		static UserBuyLifeStr		buyLifeMsg;
		static UserHandselLifeStr	handselLifeMsg;
		static UserGetHandselMsgStr getHandselMsg;
		static UserNoFriendStr		InviteFriendMsgList;
		static UserNoFriendStr		SeachFriendList;
		static UserAcceptLifeStr		acceptLifeMsg;
		static UserConsumeLifeStr	consumeLifeMsg;
		static UserRemoveSysLifeStr	removeSysLifeMsg;
		static UserAddSysLifeStr	addSysLifeMsg;

		static UserPropsInfoStr		propInfoMsg;
		static UserBuyPropInfoStr	buyPropInfo;
		static UserHandselPropStr	handselPropInfo;
		static UserGetHandselPropStr handselPropMsg;
		static UserAcceptPropStr	acceptPropMsg;
		static UserClaimPropStr		claimPropMsg;	
		static UserGetClaimedPropStr getClaimedPropMsg;
		static UserAcceptClaimedPropStr acceptClaimedPropMsg;
		static UserConsumePropStr	consumePropStr;
		static UserGetUserPropStr	getUserPropStr;
		static UserPropRecordStr 	propRecordStr;
		static UserRefuseClaimPropStr refuseClaimPropStr;
		static UserAllAcceptHandselStr	allAcceptHandsel;
		static UserFilterFriendStr	filterFriend;
		static UserNoticeStr	noticeStr;
		static UserGameState gamestate;
		static SystemGivePropStr giveProp;
		static UserEnergyUseTime energyUsetime;
		static MagicLampInfo magicLampInfo;
		static SystemHeadUrlStr SysHeadUrl;
		static UserSingleLevelResultStr SingleLevelResultStr;
		static FunctionUnLockLevel	unLockConfig;
		static SignInConfigStr signInConfigStr;

	public:
		static char jsonString[JSON_STRING_LEN];

		static char CandPicPath[512];
		static std::string Recordingdata;
		static std::string myDevice;
		static std::string myUserId;
		static std::string MyCurrVersion;
		static std::string MyCurrchannel;
		static std::vector<RouleteRatio>	RouleteRatioVec;
};

#endif
