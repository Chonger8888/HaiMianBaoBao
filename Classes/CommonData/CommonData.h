#ifndef COMMON_DATA__H
#define COMMON_DATA__H

#include "cocos2d.h"
#include "../CommonMacro.h"
#include "../PlayGame/CandyCommon.h"
#include "../MsgMgr/AnalyseJson.h"
#include "ToastDisplay.h"

USING_NS_CC;


#define MAX_LEVEL 225

extern const char* unlockAllLvl;

typedef enum
{
	GameVip_Level1 = 1111,
	GameVip_Level2,
	GameVip_Level3,

	GameVip_LevelNum
}GameVip;

typedef enum
{
	GameGift_Level1 = 1300,		// 新手大礼包
	GameGift_Level2,			// 进阶大礼包
	GameGift_Level3,			// 高端大礼包
	GameGift_Level4,	//畅玩包
	GameGift_Level5,	//闯关包
	GameGift_Level6,	//冲星包

	GameGift_LevelNum
}GameGift;

typedef enum
{
	CANDY_PROP_OUT_STEP3=2,
	CANDY_PROP_OUT_STRIP,
	CANDY_PROP_OUT_BOMB,
	CANDY_PROP_IN_STEP5,
	CANDY_PROP_IN_STRIP,
	CANDY_PROP_IN_BOMB,
	CANDY_PROP_IN_GUANZI,

	CANDY_PROP_OUT_HEAD = 32,

	CANDY_PROP_OUT_DOUBLE = 33,
	CANDY_PROP_OUT_COLORFULL = 34,
	CANDY_PROP_OUT_BOMBNEW = 35,
	CANDY_PROP_IN_RESORT = 36,
	CANDY_PROP_IN_SWAP = 37,
	CANDY_PROP_IN_HAMMER = 38,
	CANDY_PROP_COMPOSE_1 = 39,  //折扣道具

	CANDY_PROP_SUPERGIFT = 100,	//超级大礼包

	CANDY_PROP_NUM,
}CandyPropType;


typedef enum
{
	CANDY_PROP_UNLACK_MAINTASK = 1000,		// 解锁主线任务————1000
	CANDY_PROP_FRIEND_LIMIT = 1001,			// 好友上限+5————1001
	CANDY_PROP_VIP			= 1002,			// vip购买————1002
	CANDY_PROP_LIFE			= 1003,			// 购买生命————1003
	CANDY_PROP_HEAD			= 1004,			// 扩充头像————1004
	CANDY_PROP_GUANZI		= 1005,			// 罐子————1005
	CANDY_PROP_RETROACTIVE  = 1006,			// 补签卡------1006

}CandySpecialProp;

typedef enum
{
	CANDY_PROP_UNACTIVE = 0,
	CANDY_PROP_ACTIVE,
	CANDY_PROP_EFFECTING,
	CANDY_PROP_ACTIVING,
}CandyPropStates;

typedef enum
{
	CANDY_BUYTYPE_OUT_GEM,
	CANDY_BUYTYPE_OUT_STEP2,
	CANDY_BUYTYPE_OUT_STRIP,
	CANDY_BUYTYPE_OUT_BOMB,
	CANDY_BUYTYPE_IN_STEP5,
	CANDY_BUYTYPE_IN_STRIP,
	CANDY_BUYTYPE_IN_BOMB,
	CANDY_BUYTYPE_IN_GUANZI,
}CandyBuyType;

enum PROP_NAME
{
	Super_gift = 1333,		//新版超级优惠包
	Super_life = 1336,		//超级生命包
	Success_Pass = 1339,	//直接通关
	UnLock_Level = 1342,	//解锁关卡
	Exit_Gift = 1345,		//退出礼包
	Zhadan_Gift = 1348,		//炸弹礼包
	Zhizun_Gift = 1351,		//至尊礼包

};

class CandyCell;
class CommonData
{
	public:
		static std::string getStorePath(void);		// 获得存储路径
		static int getPropNum(CandyPropType type);
		static void setPropNum(CandyPropType type, int num);
		static void changePropNum(CandyPropType type, int var);
		static int getPropPriceForBuyType(CandyPropType type);
		static int getPropBuyMoneyType(CandyPropType type);
	public:
		static void resetPropUseState(void);
		static bool getPropUseState(CandyPropType type);
		static void setPropUseState(CandyPropType type, bool state);

	public:
		static bool updateActiveProps(void);
		static void updateActiveProp(int propType);
		static bool updateEffectingProps(void);
		static void updateEffectingPropCb(void);
		static bool updateActivingProps(void);
		static void updateActivingProp(int propType);
		static bool updatePropData(void);
		
	private:
		static unsigned long long propUseState;
		static int usingPropState[CANDY_PROP_NUM];
		static int remainStep;
		static int newSpecial;

	public:
		static int currentPropType;
		static CandyCell* currentCandy;
		static CandyIndex propSelectedIndex;
		static int m_doubleScore;
		static bool m_isSwap;
			
	public:
		static CCDictionary*	m_pStrings;	//	

		static int m_curBuyPropid;
		static int  m_LastLifeNum;
		static int m_buyMutipropNum;
		static int  m_maxResortLevelNum;
		static int m_buytype;			// 0 宝石类型  1 生命 其他  道具ID
		static int m_gamemode;
		static bool m_isBuyLife;	
		static bool m_buyState;
		static bool m_buyGemState;
		static bool m_isLoadedMapRes;
		static bool m_isLoadedGameRes;
		static bool m_ModifiedHeadPhoto;
		static bool m_ResortByProp;
		static bool m_resetPropState;
		static bool m_isEnterNext;		//是否已经进入下一关界面/超越好友界面
		static bool m_isEnterGame;		//是否进入游戏
		static int  m_levelFailNum[MAX_LEVEL];		//每个关卡的失败次数
		static int  m_GiftIDBuyNow;		//现在可以买的礼包ID
		static ToastDisplay*	m_pToast;	// 弱提示

// 		static bool		m_isLoading;	// 正在Loading
// 		static Loading*	m_pLoading;		// Loading Layer

		// 进入关卡存放星星数
		static int	m_lastLevelStarNum;

		//当前进行的大关卡数，默认值-1,只要进行过游戏，该值就等于最近玩的大关卡数
		static int m_pageViewNum;
		static int m_curLevelRewardNum;

		static bool m_isShowChoujiang;		//返回关卡页面时是否显示抽奖
		static bool m_isShowBuyLife;		//返回关卡页面时是否显示生命购买
		static bool m_isPlayNewUserAction;	//是否播放过新用户动画指引
		static bool m_isShowSuperGiftInGame;//在游戏里面是否弹出过超级礼包界面
		static int  m_BuyAdd5From;			//购买+5道具的路径（0商城，1失败界面）

		static int  m_successPassFailed;
		static int  m_buyAdd5Failed;
		static int  m_successPass;
		static int  m_superGift;
		static int  m_isExitGame;
		static int  m_isBuyExitGift;
		static int  m_unLockAllLevel;
		static int  m_isFirstEnterGame;
		static int  m_nextStage;
		static int m_mapLayerBuyFinish;


	private:
		static bool m_isSoundEffect;
		static bool m_isMusic;
		static bool m_isPlayGame;
	public:
		static int getMaxLevel(void);
		static int getLevelScore(int level);
		static int getStarForLevelAndScore( int level, int score);

		static int countLevelrewardCandy( int level, int starnum );
		static void sendLevelScore(int level, int score);
		static void updateLevelScore(void);
		static void addlevelScore(int level , int score);

	public:
		static bool isFirstInstall(void);
		static int getEnergyNum(void);
		static void setEnergyNum(int energy);

		static void getSoundEffectStateEx(void);
		static bool getSoundEffectState(void);
		static void setSoundEffectState(bool state);

		static void getBackgroundStateEx(void);
		static bool getBackgroundState(void);
		static void setBackgroundState(bool state);
		
		static void setPlayGame(bool state);
		static bool getPlayGame(void);

		static bool consumeGameLife(void);
		static std::string& GetString(std::string strKey);	// 获取XML键值

		static void ReleaseXml(void);
		static std::string getReward(void);

		static std::string getHeadPathForUrl(std::string url);
		static bool headIsExist(std::string url);

		static void getMyMessage();

		static int getHourForSever(unsigned int time);
		static int getMinuteForSever(int hour, unsigned int time);
		static int getSecoudForSever(int hour, int min, unsigned int time);
		static int getCurrentPackage();

		static CCActionInterval* getScaleEaseInAction();
		static CCActionInterval* getScaleEaseOutAction(CCObject* obj, SEL_CallFunc func);

#ifdef CANDY_STATISITICAL_DATA
	public:
		static int levelFaildCount[226];
		static int lastFailedLevel;
		static void updateLevelFaildCount(void);
		static void addLevelFaildCount(void);
		static void sendLevelFaildCount(bool isSend = true);
		static void sendExitStatistics(void);
		static void sendLoadingStateStatistics(bool scucess);//scucess->false = loading, true = gaming
		static void sendUsePropStatistics(int propId);
		static void sendActiveExitGameStatistics(void);
		static void sendUseMoreFiveStepStatistics(void);
		static void sendGemConsumeStatistics(int type, int curlevel = 0, int levelmode = 0, int level_data = 0);
		static void CutOutScene();
		static void CutSceneForGl();
		static CANDY_BUYGEM_NUM_TYPE getGuanziMoney();
#endif

	public:
		static void setButtonTouchEnable(CCObject *pSender, bool states);
		static bool sendEnergyNum(void);

		static bool CmpareFriend(const UserFriendInfoStr st1, const UserFriendInfoStr st2); 
		static int getFriendNumInLevel(int level);
		static void restoreLevelInfo(void);
		static std::string getCurrentHeadPath(std::string url);
		static int getPropPrice(CandyPropType type);
		static int getPropPriceForCandy(CandyPropType type);

		static void submitTaskNum(void);
		static void changeLevelTaskStarNum(int level);
		static void initLevelTaskStarNum(void);
		static CCActionInterval* getAfloatAction(void);

		static bool checkGoodsBuyFlag(int goodsid);
		static bool checkGoodsPriceEnough(int goodid);
		static int	findGoodsPrice(int goodsid);
		static void directBuyGoods(int goodsid);

		static CCActionInterval* getMoveAction(int state, CCPoint pos);
		static void setButtonTouchEnableBySchedule(CCObject *pSender, bool states);
		static int getPayIDByPrice(int price);
		static int getPayIDByGemNum( int gemnum );
		static int isUnlockedLevel(int level);


		//从xml文件读取游戏数据
		static void initConfigInfo();
		static void getLifeInfo();
		static void setLifeInfo();

		static void getCandyNum();
		static void setCandyNum();

		static void getPropInfo();
		static void getPropInfoById(int propId);
		static void setPropInfoById(int propId);

		static void setLevelScore(int level,int score);
		static void getLevelScore();

		static void gamePay( int type );


		// 设置弱提示
		// isLocalStr为true，则toast为string key，使用本地化字串
		static void	SetToast(std::string toast, bool isLocalStr = true);

		// 设置Loading
		void	SetLoading(bool bLoading);

		static void setLastStarNumForLevel(int level);
		static int getLastStarNumForLevel();
		static int getStarForLevel(int level);

		void DelayCallBuyPropfunc();
		static void unLockAllTheLevel();
};

class Cmpare  
{  
public:  
	bool operator()(const UserFriendInfoStr st1,const UserFriendInfoStr  st2) const
	{  
		return st1.level > st2.level;     
	}
};

class Cmpare2
{  
public:  
	bool operator()(const UserSingleLevelStr st1,const UserSingleLevelStr  st2) const
	{  
		return st1.result > st2.result;     
	}
};

#endif
