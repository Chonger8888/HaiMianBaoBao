#ifndef CANDY_MANAGER__H
#define CANDY_MANAGER__H

#include "cocos2d.h"
#include "CandyCommon.h"

#include "CandyCell.h"
#include "CandyDispel.h"
#include "CandyCorrectMap.h"
#include "CandyCombination.h"
#include "CandyLayer.h"
#include "CandyScore.h"
#include "CandySpecialManager.h"
#include "CandyMapData.h"
#include "CandyBgGrid.h"
#include "CandyMove.h"
#include "CandyPlace.h"
#include "CandyEffectLayer.h"
#include "CandyJelly.h"
#include "CandyCream.h"
#include "CandyLock.h"
#include "CandyIngredients.h"
#include "CandyLicorices.h"
#include "CandyChocolate.h"
#include "CandyExplosions.h"
#include "CandyUiLayer.h"
#include "CandyShare.h"
#include "CandyResult.h"
#include "CandyNewPortal.h"
#include "CandyMusic.h"
#include "CandyGuideLayer.h"
#include "CandyStageIntro.h"
#include "CandyParticle.h"
#include "../CommonData/CommonData.h"

USING_NS_CC;


typedef enum
{
	CANDY_MODE_NORMAL,		// 普通模式
	CANDY_MODE_JELLY,		// 消除果冻模式/冰块模式
	CANDY_MODE_INGREDIENT,	// 运送模式
	CANDY_MODE_TIMING,		// 计时模式
	CANDY_MODE_COLLECT,		// 收集特定糖果/组合模式
	CANDY_MODE_NUM
}CandyGameMode;


typedef struct
{
	int				targetNum;
	int				currentNum;
	CandyCollectType 	type;
}CandyCollectItem;


#define PERCENT_ARRAY_NUM 6
typedef struct 
{ 
	int m_array[ PERCENT_ARRAY_NUM ]; 
}MapArray;

class CandyManager
{
	private:
		CandyManager(); 
		~CandyManager();
		static CandyManager * instance; 
		
	public: 
		static CandyManager * getInstance(void);
		static void purgeInstance(void);

	public:
		void startCandyGame(void);
		
	public:
		void updateStates(float time);

	public:
		void setCurrentLayer(CCLayer*layer);
		CCLayer* getCurrentLayer(void);

	public:
		//游戏中糖果层
		CandyLayer			*candyLayer;
		//游戏中UI层
		CandyUiLayer			*uiLayer;
		//游戏中特效层
		CandyEffectLayer		*effectLayer;
		//新手指引
		CandyGuideLayer		*guideLayer;
		//检测地图各种情况：比如无糖果可以消除
		CandyCorrectMap 		*correctMapMgr;
		//糖果消除逻辑
		CandyDispel 			*dispelMgr;
		//糖果组合逻辑
		CandyCombination 		*combinationMgr;
		//分数
		CandyScore 			*scoreMgr;
		//特殊糖果爆炸
		CandySpecialManager 	*specialMgr;
		//地图数据
		CandyMapData 		*mapDataMgr;
		//背景格子
		CandyBgGrid 			*bgGridMgr;
		//糖果点击移动
		CandyMove			*moveMgr;
		//糖果位置更新
		CandyPlace			*placeMgr;
		//冰块
		CandyJelly			*jellyMgr;
		//奶油障碍物
		CandyCream			*creamMgr;
		//锁
		CandyLock			*lockMgr;
		//运输模式的果实
		CandyIngredients      	*ingredientsMgr;
		//甘草障碍物
		CandyLicorices			*licoricesMgr;
		//巧克力
		CandyChocolate		*chocolateMgr;
		//定时炸弹
		CandyExplosions		*explosionMgr;
		//公共接口
		CandyShare			*shareMgr;
		//游戏状态
		CandyResult			*resultMgr;
		//新传送门
		CandyNewPortal		*newPortal;
		//音乐
		CandyMusic			*musicMgr;
			
	public:
		static int currentLevel;
		static int numberOfColours;

		static float timeLimit;
		static int energyNum;
		static bool explosionBomb;
		static CandyGameMode gameMode;
		static CandyCollectItem collectCandy[COLLECT_MAX_TYPE_NUM];
		static bool usePropFlag;
		static bool m_isPropBuying;
	public:
		static int randomSeed;
		static int modifyPercent;
		static int modifyRed;
		static int modifyBlue;
		static int modifyGreen;
		static int modifyYellow;
		static int modifyOrange;
		static int modifyPurple;




		static std::map<int,MapArray> candyPercent;
		static std::vector<int> failLevelsNum;
		static int multiplePercent;

	private:
		CCLayer *currentLayer;
};

#endif
