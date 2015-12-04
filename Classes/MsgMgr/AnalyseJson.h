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
	//RECODING_MSG_ACTIONID_8, 			//�˳�ʱ��											"1328",

	//RECODING_MSG_ACTIONID_9, 			// 	��ͼLoading									  "2000",
	//RECODING_MSG_ACTIONID_10, 			// 	���ͼ����									   "2001",
	//RECODING_MSG_ACTIONID_11, 			// 	�ؿ�ID										  "2002",

	//RECODING_MSG_ACTIONID_12, 			// 	�ؿ�Loading									  "2003",
	//RECODING_MSG_ACTIONID_13, 			// 	�ؿ�����			2004						"2004",
	//RECODING_MSG_ACTIONID_14, 			// 	�����ؿ�1_UI									"2005",
	//RECODING_MSG_ACTIONID_15, 			// 	�رչؿ�1_UI									"2006",
	//RECODING_MSG_ACTIONID_16, 			// 	����ؿ�1_"Play"								"2007",
	//RECODING_MSG_ACTIONID_17, 			// 	����ؿ�1_��Ϸ��  2008							 "2008",
	//RECODING_MSG_ACTIONID_18, 			// 	��ɹؿ�1_��������								"2009",
	//RECODING_MSG_ACTIONID_19, 			// 	�ؿ�1_����  2010								"2010",
	//RECODING_MSG_ACTIONID_20, 			// 	�����ؿ�1_��һ��UI								 "2011",
	//RECODING_MSG_ACTIONID_21, 			// 	����ؿ�1_��һ�ذ�ť							   "2012",

	//RECODING_MSG_ACTIONID_23, 			// 	�ڼ��δ���									   "2014",
	//RECODING_MSG_ACTIONID_24, 			// 	��������										"2015",
	//RECODING_MSG_ACTIONID_25, 			// 	ʹ��ʱʣ������									 "2016",
	//RECODING_MSG_ACTIONID_26, 			// 	ʹ��ʱʣ�ಽ��									 "2017",
	//RECODING_MSG_ACTIONID_28, 			// 	ʹ��ʱ��										"2019",

	//RECODING_MSG_ACTIONID_29, 			// 	������								 "2021"
	//RECODING_MSG_ACTIONID_30, 			// 	��ˮ��								  "2022"
	//RECODING_MSG_ACTIONID_31, 			// 	������Ʒ							 "2023"
	//RECODING_MSG_ACTIONID_32, 			// 	������							 "2024"
	//RECODING_MSG_ACTIONID_33, 			// 	����ʱ��							 "2025"
	//RECODING_MSG_ACTIONID_34, 			// 	֧����ʽ							 "2026"
	//RECODING_MSG_ACTIONID_35, 			// 	�Ƿ����							 "2027"
	//RECODING_MSG_ACTIONID_36, 			// 	UID									 "2028"
	//RECODING_MSG_ACTIONID_38, 			// 	ʣ������							 "2030"
	//RECODING_MSG_ACTIONID_39, 			// 	ʣ�ಽ��							 "2031"
	//RECODING_MSG_ACTIONID_41, 			// 	���΢��ͼ��						   "2033"
	//RECODING_MSG_ACTIONID_42, 			// 	�������ͼ��						   "2034"
	//RECODING_MSG_ACTIONID_43, 			// 	�������ͼ��						   "2035"
	//RECODING_MSG_ACTIONID_44, 			// 	�����Ϸ�����						  "2036"
	//RECODING_MSG_ACTIONID_45, 			// 	�����Ϸ�ڰ���						  "2037"
	//RECODING_MSG_ACTIONID_46,			// 	���ص�ͼloading						 "2038"
	//RECODING_MSG_ACTIONID_47,			// 	������ͼ							"2039"
	//RECODING_MSG_ACTIONID_48,			// 	�ƶ�ͷ��							 "2040"

	//// 1.2�汾
	//RECODING_MSG_ACTIONID_49,			// 	���ֹ�������		                                  "2041"	
	//RECODING_MSG_ACTIONID_50,			// 	���鶯����һ����									  "2042"
	//RECODING_MSG_ACTIONID_51,			// 	���鶯��������										  "2043"
	//RECODING_MSG_ACTIONID_52,			// 	���鶯����һ����									  "2044"
	//RECODING_MSG_ACTIONID_53,			// 	���鶯��������										  "2045"
	//RECODING_MSG_ACTIONID_54,			// 	���鶯����һ����									  "2046"
	//RECODING_MSG_ACTIONID_55,			// 	���鶯��������										   "2047"

	//RECODING_MSG_ACTIONID_56,			// 	����һ��Loading										  "2048"

	//RECODING_MSG_ACTIONID_57,			// 	��һ�ص���											 "2049"  
	//RECODING_MSG_ACTIONID_58,			// 	��������ָ��											"2050"

	//RECODING_MSG_ACTIONID_59,			// 	��һ�ص�һ������									  "2051"
	//RECODING_MSG_ACTIONID_60,			// 	��һ�صڶ�������									  "2052"
	//RECODING_MSG_ACTIONID_61,			// 	��һ�ص�������֪����									"2053"
	//RECODING_MSG_ACTIONID_62,			// 	��һ�عؿ����										  "2054"
	//RECODING_MSG_ACTIONID_63,			// 	������һ�ؽ������߽���								   "2055"
	//RECODING_MSG_ACTIONID_64,			// 	��һ�ص�����ȡ										   "2056"
	//RECODING_MSG_ACTIONID_65,			// 	������һ��ʤ��UI									   "2057"
	//RECODING_MSG_ACTIONID_66,			// 	���ص�ͼ��Loading									 "2058"
	//RECODING_MSG_ACTIONID_67,			// 	���ͼ����											 "2059"1111111111

	//RECODING_MSG_ACTIONID_68,			// 	�������߶���											"2060"
	//RECODING_MSG_ACTIONID_69,			// 	�����ڶ��عؿ�����									 "2061"
	//RECODING_MSG_ACTIONID_70,			// 	�ڶ��ؿ�ʼ��Ϸ��ť									 "2062"
	//RECODING_MSG_ACTIONID_71,			// 	�ڶ��عرհ�ť										   "2063"
	//RECODING_MSG_ACTIONID_72,			// 	���ڶ���Loading										  "2064"
	//RECODING_MSG_ACTIONID_73,			// 	�ڶ��ص���											 "2065"
	//RECODING_MSG_ACTIONID_74,			// 	�ڶ������											 "2066"
	//RECODING_MSG_ACTIONID_75,			// 	�����ڶ���ʤ��UI									   "2067"
	//RECODING_MSG_ACTIONID_76,			// 	���ص�ͼ��Loading									 "2068"
	//RECODING_MSG_ACTIONID_77,			// 	���ͼ����											 "2069"11111
	//RECODING_MSG_ACTIONID_78,			// 	�������߶���											"2070"
	//RECODING_MSG_ACTIONID_79,			// 	���������عؿ�����									 "2071"
	//RECODING_MSG_ACTIONID_80,			// 	�����ؿ�ʼ��Ϸ��ť									 "2072"
	//RECODING_MSG_ACTIONID_81,			// 	�����عرհ�ť										  "2073"
	//RECODING_MSG_ACTIONID_82,			// 	���ڶ���Loading										  "2074"
	//RECODING_MSG_ACTIONID_83,			// 	�����ص���											 "2075"
	//RECODING_MSG_ACTIONID_84,			// 	��������ָ��											"2076"
	//RECODING_MSG_ACTIONID_85,			// 	�����ص�һ������									  "2077"
	//RECODING_MSG_ACTIONID_86,			// 	�����صڶ�������									  "2078"
	//RECODING_MSG_ACTIONID_87,			// 	�����ص�������֪����									"2079"
	//RECODING_MSG_ACTIONID_88,			// 	�����عؿ����										   "2080"
	//RECODING_MSG_ACTIONID_89,			// 	���������ؽ������߽���								   "2081"
	//RECODING_MSG_ACTIONID_90,			// 	�����ص�����ȡ										   "2082"
	//RECODING_MSG_ACTIONID_91,			// 	��������ؽ������߽���								   "2083"
	//RECODING_MSG_ACTIONID_92,			// 	����ص�����ȡ										   "2084"
	//RECODING_MSG_ACTIONID_4001,			// 	4001	���ֵ�¼��Loading
	//RECODING_MSG_ACTIONID_4002,			// 	4002	����"ƴ��������"����	
	//RECODING_MSG_ACTIONID_4003,			// 	4003	����"���عؿ�����"
	//RECODING_MSG_ACTIONID_4004,			// 	4004	�������
	//RECODING_MSG_ACTIONID_4005,			// 	4005	�����ʼ��Ϸ
	//RECODING_MSG_ACTIONID_4006,			// 	4006	������ͼ
	//RECODING_MSG_ACTIONID_4007,			// 	4007	��������������ҫ
	//RECODING_MSG_ACTIONID_1319,			// 	1319	��¼
	//RECODING_MSG_ACTIONID_4008,			// 	4008	����
	//RECODING_MSG_ACTIONID_4009,			// 	4009	��������ͳ��

	//RECODING_MSG_ACTIONID_4010,			// 	4010	���VIP����
	//RECODING_MSG_ACTIONID_4011,			// 	4011	�ǹ�֮�ý��� o o
	//RECODING_MSG_ACTIONID_4012,			// 	4012	�ǹ�֮���������
	//RECODING_MSG_ACTIONID_4013,			// 	1313	�̳ǹ���
	//RECODING_MSG_ACTIONID_4014,			// 	4014	�ճ����������ȡ��ʯ
	//RECODING_MSG_ACTIONID_4015,			// 	4015	������������
	//RECODING_MSG_ACTIONID_4016,			// 	4016	����ͳ��  ����ӣģ˽���

	//// 3.0.0
	//RECODING_MSG_ACTIONID_4017,			// 	4017	�����ȡ
	//RECODING_MSG_ACTIONID_4018,			// 	4018	�֣ɣн�����ȡ	

	RECODING_MSG_ACTIONID_1, 			//���ÿ��һ��Ҫ���м�¼							"1321",
	RECODING_MSG_ACTIONID_2, 			//ͬһ�ؿ����ж�θ��¼���							"1322",
	RECODING_MSG_ACTIONID_3, 			//����ʹ�õ��߽��б��								"1323",
	RECODING_MSG_ACTIONID_4, 			//�Ƿ��˳�ʱ����Ϊ��								"1324",
	RECODING_MSG_ACTIONID_5, 			//�Ƿ�ͬһ�س���3��û���˳�							"1325",
	RECODING_MSG_ACTIONID_6, 			//�Ƿ��һ��û��									"1326",
	RECODING_MSG_ACTIONID_7, 			//�Ƿ�û�з�����������û��ͷ						"1327",
	RECODING_MSG_ACTIONID_22, 			// 	�ؿ�ID											"2013",
	RECODING_MSG_ACTIONID_27, 			// 	�Ƿ����										"2018",
	RECODING_MSG_ACTIONID_37, 			// 	�ؿ�ID											"2029",
	RECODING_MSG_ACTIONID_40, 			// 	���+5����										"2032",
	//mini�汾������¼��
	RECODING_MSG_ACTIONID_1002,			//���￪ʼ��Ϸ										"1002",
	RECODING_MSG_ACTIONID_1003,			//�����ʼ��ť										"1003",
	RECODING_MSG_ACTIONID_1004,			//������Ϸ����										"1004",
	RECODING_MSG_ACTIONID_1005,			//����ؿ�											"1005",
	RECODING_MSG_ACTIONID_1006,			//����ؿ�loading									"1006",
	RECODING_MSG_ACTIONID_1007,			//����ؿ���										"1007",

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

// �û�������Ϣ
typedef struct
{
	int		id;				// �û���ʶ
	int		gender;			// �Ա� 0�� 1Ů ��1δ����
	int		skill_one_num;  // ��������
	int		all_skill;		// ��������
	int		jar_replay_time;	//��ƻָ�ʱ��
	int		jar_price;			//����ܼ۸�
	int		jar_hour_reduce;	//��Ƶ��ο۳��۸�
	int		gemNum;				//����ʯ����
	int		candyNum;			// �Ǳҹ���
	int		Chitchat;
	int		avatar_upd_times;	// ��һ���޸�����
	int		isFirstModify;
	int		isFirstLogin;
	int		isVip;			// 0 ��Vip  1 һ��vip   2 һ��vip   3 ����vip
	int		vipLength;		
	int		friendLack;
	int		isNotice;		// 0 û�й��� 1�й���
	int		failNum;		// ���ؿ�ʧ�ܴ���
	int		today_has_receice;		//�Ƿ��Ѿ���ȡVIP��� 0δ��ȡ 1��ȡ
	int		myWorldRanked;	//���ҵ���������

	int		MaxSignInDay;		//��Ӧǩ��������������
	int		practicalSignInDay; //����ǰ��ǩ����
	int     hasSignInDay;		//��ʵ����ǩ
	int		IsRetroactive;		//���Ƿ�ɲ�ǩ
	int		RetroactiveCardNum; //����ǩ������
	int		RetroactiveCatdPrice; //��ǩ���۸�
	int		today_Roulette_num;	//ÿ��ת��ʣ�����
	int		Roulette_UseCandy;	//ת����Ҫ���ǹ�������
	int		isBuySuperGift;		//�Ƿ�����������
	int		isUsePropToday;		//�����Ƿ���������
	int		SuperGiftId;		//�������ID
	int		openkkSdk;			//KKsdk�Ƿ���
	int		isNewUser;			//�Ƿ�Ϊ���û�

	string	qq;
	string  idx;
	string  version;
	string  packpag;
	string	updataver;
	string  channel;
	string	headPicUrl;		// ͷ��Url
	string	nickName;		// �ǳ�
}UserBaseInfoStr;

// �û�������Ϣ
typedef struct
{
	int		lifeCountDown;	// ��������ʱʱ��
	int		flag;
	int		lifeNum;		// ��������
	int		first_consums;	// �״���������
	string	price;			// �۸�
}UserLifeInfoStr;

// �û�������Ϣ
typedef struct
{
	int		id;				// ���߱�ʶ
	int		num;			// ��������
	int		priceType;		//���������͡�1�������ǹ���3 all
	string	candyprice;		//���ǹ��Ҽ۸�
	string	price;			// �۸�
	string	name;			// ��������
}UserPropInfoStr;

// �û�VIP��Ϣ
typedef struct
{
	int		id;				
	std::string 	price;			
}UserVipInfoStr;

// �����Ϣ
typedef struct
{
	int		id;				
	int 	price;		
	int		type;
	int		pop_pack;
}UserPackInfoStr;

// �ؿ�������Ϣ
typedef struct
{
	int		level;				//�����ؿ�	
	int 	needStar;			//������Ҫ��������
	int		unlocked;			//�Ƿ��Ѿ�����	0δ���� 1�ѽ���
}UserUnlockLevelInfo;

// �û��ؿ���Ϣ
typedef struct UserStageInfo
{

public:
	int		level;			// �ؿ���
	int		score;			// �ؿ�����
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

// �û���Ϣ
typedef struct
{
	int		num;			// ��Ϣ����
}UserMsgInfoStr;

// ���˺��IDX
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

// �û���õ��������Ϣ
typedef struct
{
	int		handselId;		// ���͵�ID
	int		friendId;		// ����ID
	int		gender;			// �����Ա�
	string	headPicUrl;		// ����ͷ��URL
	string	nickName;		// �����ǳ�
	int		diff_time;
	int		lifeId;			// ����ID
	string	lifePrice;		// �����۸�
	int		lifeNum;		// ��������
	string	lifeName;		// ��������
}UserGetHandselMsg;


// 
typedef struct
{
	int			id;
	string		idx;
	int			gender;
	int			flag;//���Ƿ���������
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
	int				flag;  // 0 - 3 ����
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
	int RewardId;			//��ƷID
	int RewardRatio;		//��Ʒ����
	std::string RewardName;	//��Ʒ����
}RouleteRatio;

// ���ؽ����ǹ��ҹ�ʽ����
typedef struct  
{
	float growth_factor;
	float growth_value;
	float one_star;
	float two_star;
	float third_star;
}SystemRewardLevelCandyConfig;

//�����ռ�����
typedef struct  
{
	int		level;
	int		receive;	//0����������䣬1����ƽ�����
}CollectStarStruct;

typedef struct
{
	UserBaseInfoStr		baseInfo;
	UserLifeInfoStr		lifeInfo;
	SystemRewardLevelCandyConfig	rewardCandyConfig;//����ʱ�����ǹ���ʽ����
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
	int				hasMagicLamp;			//�Ƿ������	
	int				magicLampTime;			//��ƻָ�ʣ��ʱ��
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
	int taskid;				// ����ID
	int targer;				// ����Ŀ��
	int propid;				// ��������ID
	int propnum;			// ������
	int lockstate;			// 0 �ѽ�  1 δ��
	int lockConsumeGem;		// ���������ı�ʯ��
	int status;				// ��ȡ״̬  0δ��ȡ  1����ȡ
	std::string title;		// �������	
	std::string explain;	// ����˵��	
}SystemMainTask;

typedef struct
{
	int taskid;				// ����ID
	int targer;				// ����Ŀ��
	int gemnum;				// ������ʯ��
	int lockstate;			// 0 �ѽ�  1 δ��	2��VIP����
	int status;				// ��ȡ״̬  0δ��ȡ  1����ȡ
	int	type;				// �������� 1 �ǹ��ռ���  2�ؿ����������
	int	claimid;			// �ؿ���/�ǹ�id
	int complete;			// ��ǰ�����
	int isVipTask;			// 0 ��Vip����  1 VIP����
	unsigned int time;		// ���񵹼�ʱ 
	std::string title;		// �������	
	std::string explain;	// ����˵��	
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
	int		proptype;//1:�ǹ��ң�2:��ʯ��3:����
}SignReward;

typedef struct 
{
	int SignInDay;			//��ǩ�����ǩ
	std::list<SignReward> signReward;	//��ǩ���콱����Ϣ
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

		//��signIn
		static bool setForSignIn(void);
		static bool setForBuyRetroactive(void);

		static bool setForUnlockLevel(void);
		static bool setForRouletteReward(void);

		static bool setForRoulettePercent(void);

		//�ռ�����
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
