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
	CANDY_MODE_NORMAL,		// ��ͨģʽ
	CANDY_MODE_JELLY,		// ��������ģʽ/����ģʽ
	CANDY_MODE_INGREDIENT,	// ����ģʽ
	CANDY_MODE_TIMING,		// ��ʱģʽ
	CANDY_MODE_COLLECT,		// �ռ��ض��ǹ�/���ģʽ
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
		//��Ϸ���ǹ���
		CandyLayer			*candyLayer;
		//��Ϸ��UI��
		CandyUiLayer			*uiLayer;
		//��Ϸ����Ч��
		CandyEffectLayer		*effectLayer;
		//����ָ��
		CandyGuideLayer		*guideLayer;
		//����ͼ����������������ǹ���������
		CandyCorrectMap 		*correctMapMgr;
		//�ǹ������߼�
		CandyDispel 			*dispelMgr;
		//�ǹ�����߼�
		CandyCombination 		*combinationMgr;
		//����
		CandyScore 			*scoreMgr;
		//�����ǹ���ը
		CandySpecialManager 	*specialMgr;
		//��ͼ����
		CandyMapData 		*mapDataMgr;
		//��������
		CandyBgGrid 			*bgGridMgr;
		//�ǹ�����ƶ�
		CandyMove			*moveMgr;
		//�ǹ�λ�ø���
		CandyPlace			*placeMgr;
		//����
		CandyJelly			*jellyMgr;
		//�����ϰ���
		CandyCream			*creamMgr;
		//��
		CandyLock			*lockMgr;
		//����ģʽ�Ĺ�ʵ
		CandyIngredients      	*ingredientsMgr;
		//�ʲ��ϰ���
		CandyLicorices			*licoricesMgr;
		//�ɿ���
		CandyChocolate		*chocolateMgr;
		//��ʱը��
		CandyExplosions		*explosionMgr;
		//�����ӿ�
		CandyShare			*shareMgr;
		//��Ϸ״̬
		CandyResult			*resultMgr;
		//�´�����
		CandyNewPortal		*newPortal;
		//����
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
