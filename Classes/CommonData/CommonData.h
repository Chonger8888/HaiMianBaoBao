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
	GameGift_Level1 = 1300,		// ���ִ����
	GameGift_Level2,			// ���״����
	GameGift_Level3,			// �߶˴����
	GameGift_Level4,	//�����
	GameGift_Level5,	//���ذ�
	GameGift_Level6,	//���ǰ�

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
	CANDY_PROP_COMPOSE_1 = 39,  //�ۿ۵���

	CANDY_PROP_SUPERGIFT = 100,	//���������

	CANDY_PROP_NUM,
}CandyPropType;


typedef enum
{
	CANDY_PROP_UNLACK_MAINTASK = 1000,		// �����������񡪡�����1000
	CANDY_PROP_FRIEND_LIMIT = 1001,			// ��������+5��������1001
	CANDY_PROP_VIP			= 1002,			// vip���򡪡�����1002
	CANDY_PROP_LIFE			= 1003,			// ����������������1003
	CANDY_PROP_HEAD			= 1004,			// ����ͷ�񡪡�����1004
	CANDY_PROP_GUANZI		= 1005,			// ���ӡ�������1005
	CANDY_PROP_RETROACTIVE  = 1006,			// ��ǩ��------1006

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
	Super_gift = 1333,		//�°泬���Żݰ�
	Super_life = 1336,		//����������
	Success_Pass = 1339,	//ֱ��ͨ��
	UnLock_Level = 1342,	//�����ؿ�
	Exit_Gift = 1345,		//�˳����
	Zhadan_Gift = 1348,		//ը�����
	Zhizun_Gift = 1351,		//�������

};

class CandyCell;
class CommonData
{
	public:
		static std::string getStorePath(void);		// ��ô洢·��
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
		static int m_buytype;			// 0 ��ʯ����  1 ���� ����  ����ID
		static int m_gamemode;
		static bool m_isBuyLife;	
		static bool m_buyState;
		static bool m_buyGemState;
		static bool m_isLoadedMapRes;
		static bool m_isLoadedGameRes;
		static bool m_ModifiedHeadPhoto;
		static bool m_ResortByProp;
		static bool m_resetPropState;
		static bool m_isEnterNext;		//�Ƿ��Ѿ�������һ�ؽ���/��Խ���ѽ���
		static bool m_isEnterGame;		//�Ƿ������Ϸ
		static int  m_levelFailNum[MAX_LEVEL];		//ÿ���ؿ���ʧ�ܴ���
		static int  m_GiftIDBuyNow;		//���ڿ���������ID
		static ToastDisplay*	m_pToast;	// ����ʾ

// 		static bool		m_isLoading;	// ����Loading
// 		static Loading*	m_pLoading;		// Loading Layer

		// ����ؿ����������
		static int	m_lastLevelStarNum;

		//��ǰ���еĴ�ؿ�����Ĭ��ֵ-1,ֻҪ���й���Ϸ����ֵ�͵��������Ĵ�ؿ���
		static int m_pageViewNum;
		static int m_curLevelRewardNum;

		static bool m_isShowChoujiang;		//���عؿ�ҳ��ʱ�Ƿ���ʾ�齱
		static bool m_isShowBuyLife;		//���عؿ�ҳ��ʱ�Ƿ���ʾ��������
		static bool m_isPlayNewUserAction;	//�Ƿ񲥷Ź����û�����ָ��
		static bool m_isShowSuperGiftInGame;//����Ϸ�����Ƿ񵯳��������������
		static int  m_BuyAdd5From;			//����+5���ߵ�·����0�̳ǣ�1ʧ�ܽ��棩

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
		static std::string& GetString(std::string strKey);	// ��ȡXML��ֵ

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


		//��xml�ļ���ȡ��Ϸ����
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


		// ��������ʾ
		// isLocalStrΪtrue����toastΪstring key��ʹ�ñ��ػ��ִ�
		static void	SetToast(std::string toast, bool isLocalStr = true);

		// ����Loading
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
