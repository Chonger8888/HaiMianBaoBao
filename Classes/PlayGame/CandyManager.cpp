#include "CandyManager.h"
#include "CommonData/CommonWidgt.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../Loading/LoadingScene.h"
USING_NS_CC;


CandyGameMode CandyManager::gameMode = (CandyGameMode)0;
CandyCollectItem CandyManager::collectCandy[COLLECT_MAX_TYPE_NUM] = {0};
float CandyManager::timeLimit = 0;
int CandyManager::numberOfColours  = 6;
int CandyManager::currentLevel = 1;
int CandyManager::energyNum = 0;
bool CandyManager::usePropFlag = false;
bool CandyManager::explosionBomb =false;
bool CandyManager::m_isPropBuying = false;


int CandyManager::randomSeed = 0;
int CandyManager::modifyPercent = 0;
int CandyManager::modifyRed = 0;
int CandyManager::modifyBlue = 0;
int CandyManager::modifyGreen = 0;
int CandyManager::modifyYellow = 0;
int CandyManager::modifyOrange = 0;
int CandyManager::modifyPurple = 0;

int CandyManager::multiplePercent = 0;
std::vector<int> CandyManager::failLevelsNum;
std::map<int,MapArray> CandyManager::candyPercent;


CandyManager * CandyManager::instance = NULL;
CandyManager::CandyManager()
{
	CCAssert(  Loading::scenceType == CANDY_SCENCE_PLAY_GAME, "CandyManager Loading::scenceType == CANDY_SCENCE_PLAY_GAME");
#ifdef CANDY_STATISITICAL_DATA
	CommonData::updateLevelFaildCount();
#endif
	explosionBomb =false;
	usePropFlag = false;
	
	candyLayer 		= 	CandyLayer::create();
	candyLayer->retain();

	uiLayer			=	 CandyUiLayer::create();
	uiLayer->retain();

	effectLayer		=	CandyEffectLayer::create();
	effectLayer->retain();

	guideLayer		=	CandyGuideLayer::create();
	guideLayer->retain();
		
	mapDataMgr 			= 	new CandyMapData();
	dispelMgr			= 	new CandyDispel();
	correctMapMgr 		= 	new CandyCorrectMap();
	combinationMgr		= 	new CandyCombination();
	scoreMgr 			= 	new CandyScore();
	specialMgr 			= 	new CandySpecialManager();
	bgGridMgr			= 	new CandyBgGrid();
	moveMgr				=	new CandyMove();
	placeMgr			=	new CandyPlace();
	jellyMgr			=	new CandyJelly();
	creamMgr			= 	new CandyCream();
	lockMgr				=	new CandyLock();
	ingredientsMgr  	= 	new CandyIngredients();
	licoricesMgr		=	new CandyLicorices();
	chocolateMgr		=	new CandyChocolate();
	explosionMgr		=	new CandyExplosions();
	shareMgr			=	new CandyShare();
	resultMgr			=	new CandyResult();
	newPortal			=	new CandyNewPortal();
	musicMgr			=  	new CandyMusic();

	energyNum 			= 	CommonData::getEnergyNum();

}
	
CandyManager::~CandyManager()

{				
#ifdef CANDY_STATISITICAL_DATA
	if(resultMgr->getCurrentResult() == CANDY_RESULT_LOSE)
		CommonData::addLevelFaildCount();
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_3, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString(),usePropFlag?"1":"0");

	if(usePropFlag)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_27, resultMgr->getCurrentResult() == CANDY_RESULT_LOSE?"0":"1");
#endif
	CommonData::setEnergyNum(energyNum);

	CC_SAFE_DELETE(dispelMgr);
	CC_SAFE_DELETE(correctMapMgr);
	CC_SAFE_DELETE(combinationMgr);
	CC_SAFE_DELETE(scoreMgr);
	CC_SAFE_DELETE(specialMgr);
	CC_SAFE_DELETE(mapDataMgr);
	CC_SAFE_DELETE(bgGridMgr);
	CC_SAFE_DELETE(moveMgr);
	CC_SAFE_DELETE(placeMgr);
	CC_SAFE_DELETE(jellyMgr);
	CC_SAFE_DELETE(creamMgr);
	CC_SAFE_DELETE(lockMgr);
	CC_SAFE_DELETE(ingredientsMgr);
	CC_SAFE_DELETE(licoricesMgr);
	CC_SAFE_DELETE(chocolateMgr);
	CC_SAFE_DELETE(explosionMgr);
	CC_SAFE_DELETE(shareMgr);
	CC_SAFE_DELETE(resultMgr);
	CC_SAFE_DELETE(newPortal);
	CC_SAFE_DELETE(musicMgr);

	candyLayer->removeFromParentAndCleanup(true);
	effectLayer->removeFromParentAndCleanup(true);
	guideLayer->removeFromParentAndCleanup(true);
	uiLayer->removeFromParentAndCleanup(true);

	candyLayer->release();
	effectLayer->release();
	guideLayer->release();
	uiLayer->release();

	CommonWidgt::releaseWidgt();


}

CandyManager * CandyManager::getInstance(void)
 {
	if (CandyManager::instance == NULL) 
	    CandyManager::instance = new CandyManager();
	return CandyManager::instance; 
}

void CandyManager::purgeInstance(void)
{
	CC_SAFE_DELETE(CandyManager::instance);
}

void CandyManager::startCandyGame(void)
{
	if(CommonData::getMaxLevel() >= 3)
	{
		MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 1);
	}

	//初始位置
	shareMgr->initPos();

	getCurrentLayer()->addChild(candyLayer, CANDY_LAYER_ORDER);
	getCurrentLayer()->addChild(uiLayer, UI_LAYER_ORDER);
	getCurrentLayer()->addChild(effectLayer, EFFECT_LAYER_ORDER);

	resultMgr->initCandyResult();
	//创建新传送门LOGO
	newPortal->createNewPortalsLogo();
		
	//板栗樱桃
	ingredientsMgr->createIngredientsWithMapData();
	ingredientsMgr->createExitWithMapData();

	//炸弹 甘草糖 巧克力 果冻锁链传送门奶油
	explosionMgr->createExplosionsWithMapData();
	licoricesMgr->createLicoricesWithMapData();	
	chocolateMgr->createChocolatesWithMapData();
	jellyMgr->createCandyJellys();
	lockMgr->createLocksWithMapData();
	placeMgr->createPortalsLogos();
	creamMgr->createCreamsWithMapData();
	//糖果
	
	/*随机种子 
	for(int i=1; i<10; i++)
		{
			srand(i);
			rand();
		}*/
//	if(CandyManager::randomSeed)
//		srand(CandyManager::randomSeed);
	
	correctMapMgr->createCandyWithMapData(numberOfColours);

	getCurrentLayer()->addChild(guideLayer,GUIDE_LAYER_ORDER);
	//播放背景音乐
	musicMgr->playBgm();
}

extern bool crazyMode;
void CandyManager::updateStates(float time)
{	
	musicMgr->updateCandyMusic();
	resultMgr->updateCandyResult(time);
	moveMgr->updateCandyMove();

	if( (!CommonData::m_isSwap || !crazyMode) && resultMgr->getCurrentResult()<=CANDY_RESULT_USE_STEPS)
	{
		placeMgr->updateCandyPlace();
		dispelMgr->updateCandyDispel();
	}

	specialMgr->updateActivedSpecial(time);
	ingredientsMgr->updateIngredients();
	combinationMgr->updateCandyCombination();
	chocolateMgr->updateCandyChocolate();
	correctMapMgr->updateCandyCorrectMap();

	shareMgr->updateCandyShare();
	scoreMgr->updateCandyScore();

	if(gameMode == CANDY_MODE_TIMING && resultMgr->getGameRunning())
	{
		if(timeLimit  >10.0f &&  timeLimit - time<10.0f)
		{
			musicMgr->playMusic(CANDY_EFFECT_TIME_ALARM);
			CandyManager::getInstance()->uiLayer->displayMoveWarning();
		}
		timeLimit  = timeLimit - time;
	}	
}

void CandyManager::setCurrentLayer(CCLayer* layer)
{
	currentLayer = layer;
}

CCLayer* CandyManager::getCurrentLayer(void)
{
	return currentLayer;
}