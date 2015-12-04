#include "CommonData.h"
#include "../PlayGame/CandyManager.h"
#include "CppCallJava/CppCallJava.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../MsgMgr/HeadDownMgr.h"

#include "../CandyPay/CandyPay.h"
unsigned long long  CommonData::propUseState = 0;
int CommonData::usingPropState[CANDY_PROP_NUM] = {0};
int CommonData::m_levelFailNum[MAX_LEVEL] = {0};
int CommonData::m_GiftIDBuyNow = 0;
int CommonData::remainStep = 0;
int CommonData::currentPropType = 0;

CandyCell* CommonData::currentCandy = NULL;
int CommonData::newSpecial = CANDY_SPECIAL_NORMAL;
CandyIndex CommonData::propSelectedIndex = {-1,-1};

bool CommonData::m_isSoundEffect = true;
bool CommonData::m_isMusic = true;
bool CommonData::m_isPlayGame = false;
bool CommonData::m_isBuyLife = false;
bool CommonData::m_buyState = false;
bool CommonData::m_buyGemState = false;
int CommonData::m_gamemode = 0;
cocos2d::CCDictionary*	CommonData::m_pStrings = NULL;	//	
int CommonData::m_buytype = 0;
int CommonData::m_buyMutipropNum = 0;
bool CommonData::m_isLoadedMapRes = false;
bool CommonData::m_isLoadedGameRes = false;
int  CommonData::m_maxResortLevelNum = 0;
int  CommonData::m_LastLifeNum = 0;
int  CommonData::m_curBuyPropid = 2;
bool CommonData::m_ModifiedHeadPhoto = false;
int  CommonData::m_doubleScore = 1;
bool  CommonData::m_isSwap = false;
bool  CommonData::m_ResortByProp = false;
bool  CommonData::m_resetPropState = true;
bool  CommonData::m_isEnterNext = false;
bool  CommonData::m_isEnterGame = true;
ToastDisplay*	CommonData::m_pToast = NULL;
int	CommonData::m_lastLevelStarNum = 0;
int CommonData::m_pageViewNum = -1;
int CommonData::m_curLevelRewardNum = 0;
int CommonData::m_BuyAdd5From = 0;
int CommonData::m_successPassFailed = 0;
int CommonData::m_buyAdd5Failed = 0;
int CommonData::m_successPass = 0;
int CommonData::m_superGift = 0;
int CommonData::m_isExitGame = 0;
int CommonData::m_isBuyExitGift = 0;
int CommonData::m_unLockAllLevel = 0;
int CommonData::m_isFirstEnterGame = 0;
int CommonData::m_nextStage = 0;
int CommonData::m_mapLayerBuyFinish = 0;




bool CommonData::m_isShowChoujiang = false;
bool CommonData::m_isShowBuyLife = false;
bool CommonData::m_isPlayNewUserAction = false;
bool CommonData::m_isShowSuperGiftInGame = false;

// bool		 CommonData::m_isLoading = false;
// Loading*	 CommonData::m_pLoading = NULL;	

const char* unlockAllLvl = "unlock all lvl";


int CommonData::getPropPrice(CandyPropType type)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return 0;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return 0;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		int price = 0;
		if(iter->id == type)
		{
			price = atoi( iter->price.c_str() );
			return price;
		}
	}
	return 0;
}
int CommonData::getPropPriceForCandy(CandyPropType type)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return 0;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return 0;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		int price = 0;
		if(iter->id == type)
		{
			price = atoi( iter->candyprice.c_str() );
			return price;
		}
	}
	return 0;
}
int CommonData::getPropNum(CandyPropType type)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return 0;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return 0;
	
	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		if((*iter).id == type)
			return (*iter).num;
	}
	return 0;
}

int CommonData::getPropPriceForBuyType(CandyPropType type)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return 0;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return 0;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		if((*iter).id == type)
		{
			//　糖果币价格
			if ( (2 == (*iter).priceType ||3 == (*iter).priceType)&& AnalyseJson::logOnMsg.baseInfo.candyNum >= atoi((*iter).candyprice.c_str()))
				return atoi((*iter).candyprice.c_str());
			//　宝石价格
			else
				return atoi((*iter).price.c_str());
		}
	}
	return 0;
}

int CommonData::getPropBuyMoneyType(CandyPropType type)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return 0;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return 0;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		if((*iter).id == type)
		{
			//　糖果币价格
			if ( (2 == (*iter).priceType ||3 == (*iter).priceType)&& AnalyseJson::logOnMsg.baseInfo.candyNum >= atoi((*iter).candyprice.c_str()))
				return 2;
			//　宝石价格
			else
				return 1;
		}
	}
	return 1;
}

void CommonData::setPropNum(CandyPropType type, int num)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return ;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
	{
		if((*iter).id == type)
		{
			iter->num = iter->num + num;
			break;
		}
	}
	return ;
}

void CommonData::changePropNum(CandyPropType type, int var)
{
	if(type <CANDY_PROP_OUT_STEP3 || type >= CANDY_PROP_NUM )
		return ;

	if(AnalyseJson::logOnMsg.propInfo.size()==0)
		return ;

	list<UserPropInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.propInfo.begin();	iter!=AnalyseJson::logOnMsg.propInfo.end(); iter++)
		{
			if((*iter).id == type)
				(*iter).num += var;
		}

}

void CommonData::resetPropUseState(void)
{
	propUseState = 0;
	remainStep = 0;
	memset(&usingPropState[0], 0, sizeof(CandyPropStates)*CANDY_PROP_NUM);
}

bool CommonData::getPropUseState(CandyPropType type)
{
	if(type <0 || type >= CANDY_PROP_NUM )
		return false;
	unsigned long long tem = 1;
	
	bool flag = (propUseState>>type)&tem;
	return flag;
}

void CommonData::setPropUseState(CandyPropType type, bool state)
{

	if(type <0 || type >= CANDY_PROP_NUM )
		return ;
	unsigned long long tem = 1;
	if(state)
		propUseState |= (tem<<type);
	else
		propUseState &= (~(tem<<type));
}

bool CommonData::updateActiveProps(void)
{	
	for(int i=0; i<CANDY_PROP_NUM; i++)
		if(usingPropState[i] == CANDY_PROP_ACTIVE)
			{
				updateActiveProp(i);
				return true;
			}
	return false;
}

void CommonData::updateActiveProp(int propType)
{
	if(usingPropState[propType] != CANDY_PROP_ACTIVE)
		return ;
	
	CandyCell* pCandy = NULL;
	if ( 1 )
	{
		pCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( propSelectedIndex );
	}
	else
	{
		pCandy = CandyCell::getRandomNormalCandy();
	}
	switch(propType)
		{
			case CANDY_PROP_OUT_STEP3:
				remainStep = 3;
				break;
				
			case CANDY_PROP_OUT_STRIP:
				currentCandy = pCandy;
				newSpecial = rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL; 
				break;
				
			case CANDY_PROP_OUT_BOMB:
				currentCandy = pCandy;
				newSpecial = CANDY_SPECIAL_BOMB;
				break;
			case CANDY_PROP_OUT_BOMBNEW:
				currentCandy = pCandy;
				newSpecial = CANDY_SPECIAL_BOMB;
				break;
			case CANDY_PROP_OUT_COLORFULL:
				currentCandy = pCandy;
				newSpecial = CANDY_SPECIAL_COLORFULL;
				break;

			case CANDY_PROP_OUT_DOUBLE:
				CommonData::m_doubleScore = 2;
				break;

			case CANDY_PROP_IN_SWAP:

				//CommonData::m_isSwap = true;
				break;

			case CANDY_PROP_IN_STEP5:
				remainStep = 5;
				break;
				
			case CANDY_PROP_IN_STRIP:
				newSpecial = CANDY_SPECIAL_HORIZONTAL;
				break;
				
			case CANDY_PROP_IN_BOMB:
				newSpecial = CANDY_SPECIAL_BOMB;
				break;
		}
	currentPropType = propType;

	usingPropState[propType] = CANDY_PROP_EFFECTING;

	if(currentPropType == CANDY_PROP_IN_SWAP)
	{
		CommonData::updateEffectingPropCb();
	}
	else
	{
		CandyManager::getInstance()->effectLayer->displayUsingPropEffect(propType);
	}
}

bool CommonData::updateEffectingProps(void)
{
	for(int i=0; i<CANDY_PROP_NUM; i++)
		if(usingPropState[i] == CANDY_PROP_EFFECTING)
			{
				return true;
			}
	return false;
}

void CommonData::updateEffectingPropCb(void)
{
	if(currentPropType<CANDY_PROP_OUT_STEP3 || currentPropType>=CANDY_PROP_NUM)
		return;

	if(usingPropState[currentPropType] == CANDY_PROP_EFFECTING)
		usingPropState[currentPropType] = CANDY_PROP_ACTIVING;
}

bool CommonData::updateActivingProps(void)
{
	for(int i=0; i<CANDY_PROP_NUM; i++)
		if(usingPropState[i] == CANDY_PROP_ACTIVING)
			{
				updateActivingProp(i);
				return true;
			}
	return false;
}

void CommonData::updateActivingProp(int propType)
{
	if(usingPropState[propType] != CANDY_PROP_ACTIVING)
		return ;
	
	bool doneState = false;
	switch(propType)
		{
			case CANDY_PROP_OUT_STEP3:
			case CANDY_PROP_IN_STEP5:
				{
					CandyMove::moveLimit++;
					if(--remainStep <=0)
						doneState = true;
				}
				break;
			case CANDY_PROP_IN_RESORT:
				{
					CommonData::m_ResortByProp = true;
					CandyManager::getInstance()->candyLayer->runResortCandyAction();
					doneState = true;
				}
				break;

			case CANDY_PROP_OUT_STRIP:
			case CANDY_PROP_OUT_BOMB:
			case CANDY_PROP_OUT_BOMBNEW:
			case CANDY_PROP_OUT_COLORFULL:
				{
					if(currentCandy)
					{
						currentCandy->changeCandySpecial((CandySpecial)newSpecial, true);
					}
					doneState = true;
				}
				break;
				
			case CANDY_PROP_IN_STRIP:
				{
					if(!CandyManager::getInstance()->specialMgr->stripeDispelCandyDelay(CommonData::propSelectedIndex, 0))
						CandyManager::getInstance()->specialMgr->runSpecialHorizontal(CommonData::propSelectedIndex, 
							CANDY_COLOR_ORANGE, true);
					
					doneState = true;
				}
				break;
				
			case CANDY_PROP_IN_BOMB:
				{
 					CandyManager::getInstance()->specialMgr->runSpecialBomb(CommonData::propSelectedIndex, 
 							(CandyColor)(rand()%CANDY_COLOR_NORMAL_NUM), false);
					doneState = true;
				}
				break;
			case CANDY_PROP_IN_HAMMER:
				{
					CandyManager::getInstance()->dispelMgr->specialDispelCandyByProp(CommonData::propSelectedIndex,true);
					doneState = true;
				}
				break;
			default:
				doneState = true;
				break;
		}

	if(doneState)
	{
		usingPropState[propType]  = CANDY_PROP_UNACTIVE;
		if(propType == CANDY_PROP_IN_STEP5 || propType == CANDY_PROP_IN_STRIP ||propType == CANDY_PROP_IN_BOMB || propType == CANDY_PROP_IN_RESORT || propType == CANDY_PROP_IN_SWAP
		|| propType == CANDY_PROP_IN_HAMMER || propType == CANDY_PROP_OUT_COLORFULL || propType == CANDY_PROP_OUT_BOMBNEW
		)
		{
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
			CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(true);
		}
	}
}

bool CommonData::updatePropData(void)
{
	if(updateActiveProps())
		return true;

	if(updateEffectingProps())
		return true;

	if(updateActivingProps())
		return true;
	
	for(int i=0; i<CANDY_PROP_NUM; i++)
		{
			if(getPropUseState((CandyPropType)i))
				{
					switch(i)
						{
							case CANDY_PROP_OUT_STEP3:
								{
									usingPropState[CANDY_PROP_OUT_STEP3] = CANDY_PROP_ACTIVE;
									changePropNum((CandyPropType)i, -1);
								}
								break;

							case CANDY_PROP_OUT_BOMB:
								{
									usingPropState[CANDY_PROP_OUT_BOMB] = CANDY_PROP_ACTIVE;
									changePropNum((CandyPropType)i, -1);
								}
								break;
							case CANDY_PROP_OUT_BOMBNEW:
								{
									usingPropState[CANDY_PROP_OUT_BOMBNEW] = CANDY_PROP_ACTIVE;
									//changePropNum((CandyPropType)i, -1);
								}
								break;

							case CANDY_PROP_OUT_STRIP:
								{
									usingPropState[CANDY_PROP_OUT_STRIP] = CANDY_PROP_ACTIVE;
									changePropNum((CandyPropType)i, -1);
								}
								break;
							case CANDY_PROP_OUT_COLORFULL:
								{
									usingPropState[CANDY_PROP_OUT_COLORFULL] = CANDY_PROP_ACTIVE;
									//changePropNum((CandyPropType)i, -1);
								}
								break;
							case CANDY_PROP_OUT_DOUBLE:
								{
									usingPropState[CANDY_PROP_OUT_DOUBLE] = CANDY_PROP_ACTIVE;
									changePropNum((CandyPropType)i, -1);
								}
								break;
							case CANDY_PROP_IN_STEP5:
								{
									usingPropState[CANDY_PROP_IN_STEP5] = CANDY_PROP_ACTIVE;
									updatePropData();
								}
								break;

							case CANDY_PROP_IN_RESORT:
								{
									usingPropState[CANDY_PROP_IN_RESORT] = CANDY_PROP_ACTIVE;
									//updatePropData();
								}
								break;
							case CANDY_PROP_IN_SWAP:
								{
									usingPropState[CANDY_PROP_IN_SWAP] = CANDY_PROP_ACTIVE;
									//updatePropData();
								}
								break;
							case CANDY_PROP_IN_HAMMER:
								{
									usingPropState[CANDY_PROP_IN_HAMMER] = CANDY_PROP_ACTIVE;
									//updatePropData();
								}
								break;


							case CANDY_PROP_IN_STRIP:
							case CANDY_PROP_IN_BOMB:
								{
									usingPropState[i] = CANDY_PROP_ACTIVE;
									updateActiveProp(i);
								}
								break;
						}

					setPropUseState((CandyPropType)i, false);

					//单机修改
					CommonData::setPropInfoById(i);
					//MsgMgr::sendConsumePropMsg(AnalyseJson::logOnMsg.baseInfo.id, i, 1);
					//单机修改
#ifdef CANDY_STATISITICAL_DATA
					sendUsePropStatistics(i);
#endif
					//if(i != CANDY_PROP_IN_STRIP )//避免道具爆炸后糖果短时间不掉落
					return true;
				}
		}
	return false;
}
std::string CommonData::getReward(void)
{
	std::string tem;
	tem =  "Image/MainMapUi/Prop/prop36.png";
	if ( CommonData::getMaxLevel() == 0  && CandyManager::currentLevel == 1 )
	{
		tem = "Image/MainMapUi/Prop/prop36.png";
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3 )
	{
		tem = "Image/MainMapUi/Prop/prop37.png";
	}
	else if(CommonData::getMaxLevel() == 4 && CandyManager::currentLevel == 5 )
	{
		tem = "Image/MainMapUi/Prop/prop38.png";
	}
	return tem;
}


int CommonData::getMaxLevel(void)
{
	int levelSize = AnalyseJson::logOnMsg.stageInfo.size();
	if (0 >= levelSize)
		return  0;
	UserStageInfoStr lastLevel  = AnalyseJson::logOnMsg.stageInfo.back();
	return levelSize>lastLevel.level?levelSize:lastLevel.level;
}

int CommonData::getLevelScore(int level)
{
	int i=1;

	if(AnalyseJson::logOnMsg.stageInfo.size()==0)
		return 0;
	
	list<UserStageInfoStr >::iterator listIter = AnalyseJson::logOnMsg.stageInfo.begin();
	
	while (i++<level )
	    {
		 if(++listIter == AnalyseJson::logOnMsg.stageInfo.end())
		 	return 0;
	    }
	UserStageInfoStr v = *listIter;
	return v.score;
}


int CommonData::countLevelrewardCandy( int level, int starnum )
{
	// 首次胜利：FLOOR(关卡等级^成长系数*成长值+星级增量，10）

	int nRewardNum = pow( level , AnalyseJson::logOnMsg.rewardCandyConfig.growth_factor )  * AnalyseJson::logOnMsg.rewardCandyConfig.growth_value;
	float nStarRewardNum = 0;

	if ( 1 == starnum)
		nStarRewardNum = AnalyseJson::logOnMsg.rewardCandyConfig.one_star;
	else if ( 2 == starnum)
		nStarRewardNum = AnalyseJson::logOnMsg.rewardCandyConfig.two_star;
	else if ( 3 == starnum)
		nStarRewardNum = AnalyseJson::logOnMsg.rewardCandyConfig.third_star;

	// 去掉尾数
	nRewardNum = (nRewardNum + nStarRewardNum)/10.0f;
	nRewardNum = nRewardNum* 10;

	// 二次胜利或以往关卡：相应关卡首次胜利结算的10% 
	nRewardNum = ( CommonData::getMaxLevel() < level)? nRewardNum : nRewardNum * 0.1f;

	// 时间模式双倍糖果币
	nRewardNum = ( CANDY_MODE_TIMING == CandyManager::gameMode )? nRewardNum*2  : nRewardNum;

	return nRewardNum;
}

int CommonData::getStarForLevelAndScore( int level, int score)
{
	int nStarNum = 0;

	int ntemp = 0;
	if (score > CandyMapData::getTargetScore(level, 1) )
		ntemp++;
	if (score > CandyMapData::getTargetScore(level, 2) )
		ntemp++;
	if (score > CandyMapData::getTargetScore(level, 3) )
		ntemp++;

	nStarNum = ntemp;

	return nStarNum;
}

void CommonData::sendLevelScore( int level, int score )
{
	// 计算当前的奖励
	int curGetStarNum = getStarForLevelAndScore( level, score );
	CommonData::m_curLevelRewardNum = CommonData::countLevelrewardCandy( level, curGetStarNum);
	AnalyseJson::logOnMsg.baseInfo.candyNum += CommonData::m_curLevelRewardNum;

	// 添加到关卡 一定要在没有关卡成绩时候
	addlevelScore( level, score);

	// 计算星星数
	getStarForLevel( level );


	//单机修改
	CommonData::setLevelScore(level,score);
	CommonData::setCandyNum();
	//MsgMgr::sendLevelScoreMsg(AnalyseJson::logOnMsg.baseInfo.id, level,score, curGetStarNum);
	//单机修改

}

void CommonData::updateLevelScore(void)
{
	if(getLevelScore(AnalyseJson::levelScoreMsg.level) ==0 )
		{
			UserStageInfoStr stageInfoStr;
			stageInfoStr.level = AnalyseJson::levelScoreMsg.level;
			stageInfoStr.score = AnalyseJson::levelScoreMsg.score;
			AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);
			AnalyseJson::logOnMsg.stageInfo.sort();
		}
	else
		{
			int i=1;
			list<UserStageInfoStr >::iterator listIter = AnalyseJson::logOnMsg.stageInfo.begin();
			
			while (i++<AnalyseJson::levelScoreMsg.level )
			    {
				 if(++listIter == AnalyseJson::logOnMsg.stageInfo.end())
				 	return;
			    }
			
			listIter->score = AnalyseJson::levelScoreMsg.score;
	}
	
}


void CommonData::addlevelScore(int level, int score)
{
	if(getLevelScore( level ) ==0 )
	{
		UserStageInfoStr stageInfoStr;
		stageInfoStr.level = level;
		stageInfoStr.score = score;
		AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);
		AnalyseJson::logOnMsg.stageInfo.sort();
	}
	else
	{
		int i=1;
		list<UserStageInfoStr >::iterator listIter = AnalyseJson::logOnMsg.stageInfo.begin();

		while (i++<level )
		{
			if(++listIter == AnalyseJson::logOnMsg.stageInfo.end())
				return;
		}

		listIter->score = score;
	}

}

int CommonData::getEnergyNum(void)
{
	/*return CCUserDefault::sharedUserDefault()->getIntegerForKey("CandyEnergy");*/
	return AnalyseJson::logOnMsg.baseInfo.skill_one_num;
}

void CommonData::setEnergyNum(int energy)
{
	AnalyseJson::logOnMsg.baseInfo.skill_one_num = energy;
}


bool CommonData::isFirstInstall( void )
{
	bool ret = false;

	ret = CCUserDefault::sharedUserDefault()->getBoolForKey("CandyInstallFrist");
	if ( !ret )
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("CandyInstallFrist", true);
	}
	return ret;
}


void CommonData::getSoundEffectStateEx(void)
{
	m_isSoundEffect = CCUserDefault::sharedUserDefault()->getBoolForKey("SoundEffectState");
}

bool CommonData::getSoundEffectState(void)
{
	return m_isSoundEffect;
}

bool CommonData::getBackgroundState(void)
{
	return m_isMusic;
}

void CommonData::setSoundEffectState(bool state)
{
	m_isSoundEffect = state;
	CCUserDefault::sharedUserDefault()->setBoolForKey("SoundEffectState", m_isSoundEffect);
}

void CommonData::getBackgroundStateEx(void)
{
	m_isMusic = CCUserDefault::sharedUserDefault()->getBoolForKey("BackgroundState");
}

void CommonData::setBackgroundState(bool state)
{
	m_isMusic = state;
	CCUserDefault::sharedUserDefault()->setBoolForKey("BackgroundState", m_isMusic);
}

void CommonData::setPlayGame(bool state)
{
	m_isPlayGame = state;
}

bool CommonData::getPlayGame(void)
{
	return m_isPlayGame;
}

bool CommonData::consumeGameLife(void)
{
	if(CandyManager::currentLevel >=1 && CandyManager::currentLevel <=5)
		return true;
	
	if(AnalyseJson::logOnMsg.lifeInfo.lifeNum >0)
		{
			AnalyseJson::logOnMsg.lifeInfo.lifeNum = AnalyseJson::logOnMsg.lifeInfo.lifeNum -1;
			//单机修改
			CommonData::setLifeInfo();
			//MsgMgr::sendConsumeLifeMsg(AnalyseJson::logOnMsg.baseInfo.id, 1);
			//单机修改
			return true;
		}
	else
		{
			return false;
		}
}

bool CommonData::sendEnergyNum(void)
{
	MsgMgr::sendEnergyNumMsg(AnalyseJson::logOnMsg.baseInfo.id, CandyManager::energyNum);
	return true;
}

#ifdef CANDY_STATISITICAL_DATA

int CommonData::levelFaildCount[226] ={0};
int CommonData::lastFailedLevel = 0;

void CommonData::updateLevelFaildCount(void)
{
	if(lastFailedLevel != CandyManager::currentLevel)
		{
			if(levelFaildCount[lastFailedLevel] <3)
				levelFaildCount[lastFailedLevel] = 0;
			lastFailedLevel = 0;
		}
}

void CommonData::addLevelFaildCount(void)
{
	lastFailedLevel = CandyManager::currentLevel;
	levelFaildCount[lastFailedLevel]++;
}

void CommonData::sendLevelFaildCount(bool isSend)
{
	for(int i=0; i<226; i++)
	{
		if(levelFaildCount[i]>=3)
		{
			if(isSend)
				{
					AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_5, CCString::createWithFormat("%d",i)->getCString(),
							CCString::createWithFormat("%d",levelFaildCount[i])->getCString());
				}
			else
				{
					AnalyseJson::setRecordHeadMsg(RECODING_MSG_ACTIONID_5);
					AnalyseJson::setRecordMsgAppend((char*)CCString::createWithFormat("%d",i)->getCString());
					AnalyseJson::setRecordMsgAppend(CCString::createWithFormat("%d",levelFaildCount[i])->getCString());
				}			
		}
	}
}


void CommonData::sendExitStatistics(void)
{
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4, (char*)CCString::createWithFormat("%d",AnalyseJson::logOnMsg.lifeInfo.lifeNum)->getCString());
	if ( 0 == AnalyseJson::logOnMsg.stageInfo.size())
	{
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_6, (char*)CCString::createWithFormat("%d",1)->getCString());
	}
	if ( CommonData::getPlayGame() )
	{
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_7, (char*)CCString::createWithFormat("%d",1)->getCString());
	}

	CommonData::sendLevelFaildCount();
}

void CommonData::sendUsePropStatistics(int propId)
{
	CandyManager::usePropFlag = true;
	
	AnalyseJson::setRecordingMsg(	RECODING_MSG_ACTIONID_22, 
								CCString::createWithFormat("%d",propId)->getCString(),
								CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString(),
								CCString::createWithFormat("%d",levelFaildCount[CandyManager::currentLevel]+1)->getCString(),
								CCString::createWithFormat("%d",AnalyseJson::logOnMsg.lifeInfo.lifeNum)->getCString(),
								CCString::createWithFormat("%d",CandyManager::getInstance()->moveMgr->moveLimit)->getCString()
							);
}

void CommonData::sendActiveExitGameStatistics(void)
{
	AnalyseJson::setRecordingMsg(	RECODING_MSG_ACTIONID_37, 
								CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString(),
								CCString::createWithFormat("%d",AnalyseJson::logOnMsg.lifeInfo.lifeNum)->getCString(),
								CCString::createWithFormat("%d",CandyManager::getInstance()->moveMgr->moveLimit)->getCString()
								);
}

void CommonData::sendUseMoreFiveStepStatistics(void)
{
	AnalyseJson::setRecordingMsg(	RECODING_MSG_ACTIONID_40, 
								CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString()
								);
}
#endif	

void CommonData::setButtonTouchEnable(CCObject *pSender, bool states)
{
	if(!pSender)
		return;
	UIButton *button = dynamic_cast<UIButton*>(pSender);
	button->setTouchEnable(states);
}

void CommonData::setButtonTouchEnableBySchedule(CCObject *pSender, bool states)
{
	if(!pSender)
		return;
	UIButton *button = dynamic_cast<UIButton*>(pSender);
	button->setTouchEnable(states);
}


std::string& CommonData::GetString(std::string strKey)
{
	if ( NULL == m_pStrings)
	{
		m_pStrings = CCDictionary::createWithContentsOfFileThreadSafe( "Image/strings.xml" );
	}
	return ((CCString*) m_pStrings->objectForKey( strKey ))->m_sString;
}

void CommonData::ReleaseXml(void)
{
	if ( m_pStrings )
	{
		m_pStrings->release();
		m_pStrings = NULL;
	}
}

int CommonData::getFriendNumInLevel(int level)
{
	int num = 0;
	std::list<UserFriendInfoStr>::iterator iter = AnalyseJson::friendInfoMsg.friendInfo.begin();
	std::list<UserFriendInfoStr>::iterator iterEnd= AnalyseJson::friendInfoMsg.friendInfo.end();
	for(;iter!=iterEnd;++iter)
	{
		if(iter->level == level)
		{
			num++;
		}
	}
	return num;
}

CANDY_BUYGEM_NUM_TYPE CommonData::getGuanziMoney()
{
	int leftHour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
	int totoalHour =   CommonData::getHourForSever(AnalyseJson::logOnMsg.baseInfo.jar_replay_time);

	int passHour = totoalHour - (leftHour+1);
	int tem = AnalyseJson::logOnMsg.baseInfo.jar_price - passHour*AnalyseJson::logOnMsg.baseInfo.jar_hour_reduce;

	if(tem <= 10)
	{
		return CANDY_BUYGEM_NUM_10;
	}
	else if(tem>10 && tem<=20)
	{
		return CANDY_BUYGEM_NUM_20;
	}
	else if(tem>20 && tem<=30)
	{
		return CANDY_BUYGEM_NUM_30;
	}
	else if(tem>30 && tem<=50)
	{
		return CANDY_BUYGEM_NUM_50;
	}
	else if(tem>50 && tem<=80)
	{
		return CANDY_BUYGEM_NUM_80;
	}
	else if(tem>80 && tem<=100)
	{
		return CANDY_BUYGEM_NUM_100;
	}
	else if(tem>100 && tem<=200)
	{
		return CANDY_BUYGEM_NUM_200;
	}
	else if(tem>200 && tem<=320)
	{
		return CANDY_BUYGEM_NUM_320;
	}
	else if(tem>320 && tem<=588)
	{
		return CANDY_BUYGEM_NUM_588;
	}
	else if(tem>588 && tem<=1288)
	{
		return CANDY_BUYGEM_NUM_1288;
	}
	else if(tem>1288 && tem<=2588)
	{
		return CANDY_BUYGEM_NUM_2588;
	}

	return CANDY_BUYGEM_NUM_2588;
}

void CommonData::CutOutScene(void)
{	
	//　截屏
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
	CCRenderTexture *screen = CCRenderTexture::create(size.width, size.height);  
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();  
	screen->begin();  
	scene->visit();//将当前的整个scene绘出来  
	screen->end();  
	//screen->setClearColor( ccc4FFromccc3B(ccc3(255,255,255)) );
	screen->saveToFile("MyCurScene.png", kCCImageFormatPNG);
}

void CommonData::restoreLevelInfo(void)
{
	if(CommonData::m_maxResortLevelNum < 1)
	{
		CommonData::m_maxResortLevelNum++;
		int value =  CandyManager::getInstance()->scoreMgr->getCurrentScore();
		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("level%d",CandyManager::currentLevel)->getCString(),value);
	}

}

std::string CommonData::getCurrentHeadPath(std::string url)
{
	std::string tem;
	const char* headname = CCString::createWithFormat("%s%d.png", AnalyseJson::CandPicPath,AnalyseJson::logOnMsg.baseInfo.id)->getCString();
	if(CCFileUtils::sharedFileUtils()->isFileExist(headname))
	{
		tem =  headname;
	}
	else
	{
		tem = getHeadPathForUrl( url );
		
	}
	return tem;
}

std::string CommonData::getHeadPathForUrl( std::string url )
{
	std::string nHeadPath;
	char UrlName[128]= {0};

	CCFileUtils *sharedFileUtils = CCFileUtils::sharedFileUtils();

	//取URL最后图片名字字段，到URLName
	HeadDownMgr::getHeadNameForUrl(url, UrlName);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char *HeadName = (char *)CCString::createWithFormat("%s.png",UrlName)->getCString();
	char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, HeadName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	char *headPath= (char *)CCString::createWithFormat("%s%s.png",AnalyseJson::CandPicPath, UrlName)->getCString();
#endif

	if (!sharedFileUtils->isFileExist(headPath))
		headPath= (char *)CCString::createWithFormat( CANDY_DEFAULT_HEADPATH )->getCString();

	nHeadPath = headPath;
	return nHeadPath;
}

bool CommonData::headIsExist( std::string url )
{
	std::string nHeadPath;
	char UrlName[128]= {0};

	CCFileUtils *sharedFileUtils = CCFileUtils::sharedFileUtils();

	HeadDownMgr::getHeadNameForUrl(url, UrlName);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char *HeadName = (char *)CCString::createWithFormat("%s.png",UrlName)->getCString();
	char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, HeadName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	char *headPath= (char *)CCString::createWithFormat("%s/%s.png", AnalyseJson::CandPicPath, UrlName)->getCString();
#endif

	if (!sharedFileUtils->isFileExist(headPath))
		return false;
	else
		return true;
}

void CommonData::submitTaskNum( void )
{
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for( ; item!= AnalyseJson::taskTable.dailyTask.end(); item++)
	{
		if ( 1 == item->type && item->complete<item->targer )
		{
			MsgMgr::sendSubmitTask(AnalyseJson::logOnMsg.baseInfo.id, item->taskid, item->complete );
		}
	}
}

void CommonData::changeLevelTaskStarNum(int level )
{
	if ( AnalyseJson::unLockConfig.dailyTask > CommonData::getMaxLevel() )
		return;

	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for (; item!=AnalyseJson::taskTable.dailyTask.end(); ++item )
	{
		if( 2 == item->type && item->claimid == level )
		{
			item->complete++;
		}
	}
}

void CommonData::initLevelTaskStarNum(void)
{
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for (; item!=AnalyseJson::taskTable.dailyTask.end(); ++item )
	{
		if( item->type == 2 )
		{
			item->complete = 0;
		}
	}
}

CCActionInterval* CommonData::getMoveAction( int state, CCPoint pos )
{
	CCActionInterval* move = NULL;
	CCActionInterval* move_ease_inout2 = NULL;

	if( 1 == state )
	{
		move = CCMoveTo::create(0.7f, pos);
		move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );
	}
	else if( 2 == state )
	{
		move = CCMoveTo::create(0.8f, pos);
		move_ease_inout2 = CCEaseElasticOut::create((CCActionInterval*)move,0.8f );
	}
	return move_ease_inout2;
}

void CommonData::getMyMessage( void )
{
	if ( AnalyseJson::unLockConfig.friendFun <= getMaxLevel() )
	{
	// 获得消息数据
		MsgMgr::sendgetMyAllMsgForGuest( AnalyseJson::logOnMsg.baseInfo.id );
	}
}

CCActionInterval* CommonData::getAfloatAction()
{
	CCPointArray *array = CCPointArray::create(10);

	array->addControlPoint(ccp(0, 0));
	array->addControlPoint(ccp(-30,25));
	array->addControlPoint(ccp(-60,0));
	array->addControlPoint(ccp(-30,-20));
	array->addControlPoint(ccp(30,25));
	array->addControlPoint(ccp(60,0));
	array->addControlPoint(ccp(30,-20));
	array->addControlPoint(ccp(0,0));
	CCCardinalSplineBy *action = CCCardinalSplineBy::create(5.5f, array, 0);

	return action;
}



int CommonData::getHourForSever(unsigned int time)
{
	return time / ( 60 *60 );
}

int CommonData::getMinuteForSever(int hour, unsigned int time)
{
	return (time - hour*60*60) / 60;
}

int CommonData::getSecoudForSever(int hour, int min, unsigned int time)
{
	return time - hour* 60*60 - min *60;
}

void CommonData::sendGemConsumeStatistics(int type, int curlevel /*= 0*/, int levelmode /*= 0*/, int level_data /*= 0*/ )
{
#ifdef CANDY_STATISITICAL_DATA
	char pConsumeType[5] = {0};
	char pLifeNum[5] = {0};
	char pLevel[5] = {0};
	char pLevelMode[5] = {0};
	char pLevelData[5] = {0};

	sprintf(pConsumeType, "%d", type);
	sprintf(pLifeNum, "%d", AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	sprintf(pLevel, "%d", curlevel);
	sprintf(pLevelMode, "%d", levelmode);
	sprintf(pLevelData, "%d", level_data);

	// 4009 消耗类型 生命个数 关卡 关卡模式 步数/时间
	//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4009, pConsumeType, pLifeNum, pLevel,pLevelMode, pLevelData);
#endif
}

void CommonData::CutSceneForGl()
{
	int nSavedBufferWidth = (int)720;
	int nSavedBufferHeight = (int)1280;
	GLubyte *pTempData = NULL;
	GLubyte *pBuffer = NULL;

	do 
	{

		CC_BREAK_IF(! (pBuffer = new GLubyte[nSavedBufferWidth * nSavedBufferHeight * 4]));

		if(! (pTempData = new GLubyte[nSavedBufferWidth * nSavedBufferHeight * 4]))
		{
			delete[] pBuffer;
			pBuffer = NULL;
			break;
		}
		glPixelStorei(GL_PACK_ALIGNMENT, 1);

		glReadPixels(0,0,nSavedBufferWidth,nSavedBufferHeight,GL_RGBA,GL_UNSIGNED_BYTE, pTempData);

		for (int i = 0; i < nSavedBufferHeight; ++i)
		{
			memcpy(&pBuffer[i * nSavedBufferWidth * 4], 
				&pTempData[(nSavedBufferHeight - i - 1) * nSavedBufferWidth * 4], 
				nSavedBufferWidth * 4);
		}

	} while (0);

}

// 检测该道具是否有购买过的标志
bool CommonData::checkGoodsBuyFlag( int goodsid )
{
	return false;

	bool ret = false;
	const char* pStrGoods = CCString::createWithFormat("CandyGoods%d", goodsid )->getCString();

	ret = CCUserDefault::sharedUserDefault()->getBoolForKey( pStrGoods );
	if ( !ret )
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey( pStrGoods , true);
	}

	return ret;
}

// 检测该道具是否有足够的宝石
bool CommonData::checkGoodsPriceEnough( int goodsid )
{
	bool ret = false;
	int nPrice = findGoodsPrice( goodsid );

	ret = (nPrice <= AnalyseJson::logOnMsg.baseInfo.gemNum)? true:false;
	return ret;
}


int CommonData::findGoodsPrice( int goodsid )
{
	if ( CANDY_PROP_IN_GUANZI == goodsid )
	{
		int leftHour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
		int totoalHour =   CommonData::getHourForSever(AnalyseJson::logOnMsg.baseInfo.jar_replay_time);

		int passHour = totoalHour - (leftHour+1);
		int tem = AnalyseJson::logOnMsg.baseInfo.jar_price - passHour*AnalyseJson::logOnMsg.baseInfo.jar_hour_reduce;
		return tem;
	}
	else
	{
		std::list<UserPropInfoStr>::iterator item = AnalyseJson::logOnMsg.propInfo.begin();
		for(; item != AnalyseJson::logOnMsg.propInfo.end(); item++)
		{
			if(goodsid == item->id)
				return atoi( item->price.c_str() );
		}
	}

	return 0;
}

void CommonData::directBuyGoods( int goodsid )
{
	int nPrice = findGoodsPrice( goodsid );
	int nPriceCandy = CommonData::getPropPriceForBuyType( (CandyPropType)goodsid );
	int nPriceMoneyType = CommonData::getPropBuyMoneyType( (CandyPropType)goodsid );

	if ((((2 == nPriceMoneyType || 3 == nPriceMoneyType )&& nPriceCandy > AnalyseJson::logOnMsg.baseInfo.candyNum) && nPrice > AnalyseJson::logOnMsg.baseInfo.gemNum )||
		((1 == nPriceMoneyType || 3 == nPriceMoneyType )&&(nPrice > AnalyseJson::logOnMsg.baseInfo.gemNum)))
	{
		int nBuyType = 0;
		switch ( goodsid )
		{
			case CANDY_PROP_OUT_DOUBLE:
			case CANDY_PROP_OUT_COLORFULL:
			case CANDY_PROP_OUT_BOMBNEW:
				nBuyType = CANDY_BUYGEM_NUM_50;
				break;
			case CANDY_PROP_IN_RESORT:
			case CANDY_PROP_IN_SWAP:
			case CANDY_PROP_IN_HAMMER:
				nBuyType = CANDY_BUYGEM_NUM_80;
				break;
			case CANDY_PROP_IN_GUANZI:
				nBuyType = CommonData::getGuanziMoney();
				break;

		}
		CCLog(" CommonData::directBuyGoods goods[%d] buyType[]%d", goodsid, nBuyType);

		CommonData::m_buytype = goodsid;
		CommonData::m_buyMutipropNum = 0;
		CppCallJava::toBuyProp(nBuyType, 1 );
	}
	else
	{
		//糖果比购买
		if ( 2 == nPriceMoneyType )
			MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, goodsid, 1, 2);
		else
		{
			if(goodsid == CANDY_PROP_IN_GUANZI)
			{
				MsgMgr::sendGemBuySkill( AnalyseJson::logOnMsg.baseInfo.id );
			}
			else
			{
				MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, goodsid, 1);
			}
		}
	}
}

int CommonData::getCurrentPackage()
{
	list<UserPackInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.packInfo.begin();	iter!=AnalyseJson::logOnMsg.packInfo.end(); iter++)
	{
		if(iter->pop_pack == 1)
		{
			return iter->id;
		}
	}
	return 0;
}

void CommonData::SetToast( std::string toast, bool isLocalStr /*= true*/ )
{
	if (!m_pToast)
	{
		m_pToast = new ToastDisplay();
	}

	// 使用本地字串
	if (isLocalStr)
	{
		std::string strLocalStr = GetString( toast );
		m_pToast->SetTips( strLocalStr );
	}
	// 直接显示字串
	else
	{
		m_pToast->SetTips( toast );
	}
}

// void CommonData::SetLoading( bool bLoading )
// {
// 	if (m_isLoading == bLoading)
// 		return ;
// 	m_isLoading = bLoading;
// 
// 	if (m_isLoading)
// 	{
// 		if (!m_pLoading)
// 		{
// 			m_pLoading = new Loading();
// 		}
// 
// 		m_pLoading->SetShow( m_isLoading );
// 	}
// 	else
// 	{
// 		if (m_pLoading)
// 		{
// 			m_pLoading->SetShow( m_isLoading );
// 		}
// 	}
// }

int CommonData::getPayIDByPrice( int price )
{
	int payId = 0;
	switch(price)
	{
	case 1:
		payId = CANDY_BUYGEM_NUM_10;
		break;
	case 2:
		payId = CANDY_BUYGEM_NUM_20;
		break;
	case 3:
		payId = CANDY_BUYGEM_NUM_30;
		break;
	case 5:
		payId = CANDY_BUYGEM_NUM_50;
		break;
	case 8:
		payId = CANDY_BUYGEM_NUM_80;
		break;
	case 10:
		payId = CANDY_BUYGEM_NUM_100;
		break;
	case 20:
		payId = CANDY_BUYGEM_NUM_200;
		break;
	case 30:
		payId = CANDY_BUYGEM_NUM_320;
		break;
	case 50:
		payId = CANDY_BUYGEM_NUM_588;
		break;
	case 100:
		payId = CANDY_BUYGEM_NUM_1288;
		break;
	case 200:
		payId = CANDY_BUYGEM_NUM_2588;
		break;
	default:
		payId = CANDY_BUYGEM_NUM_2588;
		break;
	}
	return payId;
}

int CommonData::isUnlockedLevel( int level )
{
	list<UserUnlockLevelInfo>::iterator iter;
	for(iter= AnalyseJson::logOnMsg.unlockInfo.begin();	iter!=AnalyseJson::logOnMsg.unlockInfo.end(); iter++)
	{
		if(iter->level == level)
		{
			return iter->unlocked;
		}
	}
	return -1;
}

int CommonData::getStarForLevel( int level )
{
	int nStarNum = 0;
	std::list<UserStageInfoStr>::iterator item = AnalyseJson::logOnMsg.stageInfo.begin();
	for (; item!=AnalyseJson::logOnMsg.stageInfo.end(); item++)
	{
		if ( level == item->level )
		{
			int ntemp = 0;
			if (item->score > CandyMapData::getTargetScore(level, 1) )
				ntemp++;
			if (item->score > CandyMapData::getTargetScore(level, 2) )
				ntemp++;
			if (item->score > CandyMapData::getTargetScore(level, 3) )
				ntemp++;

			nStarNum = item->starnum = ntemp;
			break;
		}
	}

	return nStarNum;
}

void CommonData::setLastStarNumForLevel( int level )
{
	m_lastLevelStarNum = getStarForLevel( level );
}

int CommonData::getLastStarNumForLevel()
{
	return m_lastLevelStarNum;
}

CCActionInterval* CommonData::getScaleEaseInAction()
{
	CCActionInterval* scaleTo = CCScaleTo::create(0.15,1.0f);
	CCActionInterval* ease1 = CCEaseElastic::create(scaleTo,0.15);
	CCActionInterval* scaleBack = CCScaleTo::create(0.05,0.95f);
	CCActionInterval* ease2 = CCEaseElastic::create(scaleBack,0.05);

	CCSequence* seq = CCSequence::create(ease1,ease2,ease1,NULL);
	CCActionInterval* ease = CCEaseElastic::create(seq, 0.2);

	return ease;
}

CCActionInterval* CommonData::getScaleEaseOutAction(CCObject* obj, SEL_CallFunc func)
{
	CCActionInterval* scaleTo = CCScaleTo::create(0.1f,0.1f);
	CCCallFunc*	f = CCCallFunc::create(obj,func);
	CCSequence* seq = CCSequence::create(scaleTo,f,NULL);
	return seq;
}



int CommonData::getPayIDByGemNum( int gemnum )
{
	int payId = 0;
	switch(gemnum)
	{
	case 10:
		payId = CANDY_BUYGEM_NUM_10;
		break;
	case 20:
		payId = CANDY_BUYGEM_NUM_20;
		break;
	case 30:
		payId = CANDY_BUYGEM_NUM_30;
		break;
	case 50:
		payId = CANDY_BUYGEM_NUM_50;
		break;
	case 80:
		payId = CANDY_BUYGEM_NUM_80;
		break;
	case 100:
		payId = CANDY_BUYGEM_NUM_100;
		break;
	case 200:
		payId = CANDY_BUYGEM_NUM_200;
		break;
	case 320:
		payId = CANDY_BUYGEM_NUM_320;
		break;
	case 588:
		payId = CANDY_BUYGEM_NUM_588;
		break;
	case 1288:
		payId = CANDY_BUYGEM_NUM_1288;
		break;
	case 2588:
		payId = CANDY_BUYGEM_NUM_2588;
		break;
	default:
		payId = CANDY_BUYGEM_NUM_2588;
		break;
	}
	return payId;
}


#include <sys/stat.h>
std::string CommonData::getStorePath( void )
{
	//获取FileUtiles对象
	CCFileUtils *fileUtile=CCFileUtils::sharedFileUtils();
	std::string pathToSave;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	pathToSave = fileUtile->getWritablePath();
	pathToSave +="Candy";
	//打开该路径
	FILE* pDir =  fopen(pathToSave.c_str(), "wb+");

	if (! pDir)
	{
		//创建该路径
		mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}

#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

	//pathToSave =  CppCallJava::getCandyPicDir();

#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	pathToSave = fileUtile->getWritablePath();
	pathToSave +="Candy";
	if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(pathToSave.c_str(), 0);
	}

#endif
	CCLog("CommonData::getStorePathpathToSave= %s",pathToSave.c_str());
	return  pathToSave;
}

void CommonData::DelayCallBuyPropfunc()
{
	CppCallJava::BuyProduct(0);
}



void CommonData::initConfigInfo()
{
	getLifeInfo();
	getCandyNum();
	getPropInfo();
	getLevelScore();
}
void CommonData::getLifeInfo()
{
	AnalyseJson::logOnMsg.lifeInfo.lifeNum = 555;//CCUserDefault::sharedUserDefault()->getIntegerForKey("lifeNum",10);
}
void CommonData::setLifeInfo()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("lifeNum",AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	CCUserDefault::sharedUserDefault()->flush();
}

void CommonData::getCandyNum()
{
	AnalyseJson::logOnMsg.baseInfo.candyNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("candyNum",0);
}
void CommonData::setCandyNum()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("candyNum",AnalyseJson::logOnMsg.baseInfo.candyNum);
	CCUserDefault::sharedUserDefault()->flush();
}


void CommonData::getPropInfo()
{
	getPropInfoById(5);
	getPropInfoById(34);
	getPropInfoById(35);
	getPropInfoById(36);
	getPropInfoById(37);
	getPropInfoById(38);
}


void CommonData::getPropInfoById(int propId)
{
	std::list<UserPropInfoStr>::iterator iterBegin = AnalyseJson::logOnMsg.propInfo.begin();
	std::list<UserPropInfoStr>::iterator iterEnd = AnalyseJson::logOnMsg.propInfo.end();
	for(;iterBegin != iterEnd;++iterBegin)
	{
		if(iterBegin->id == propId)
		{
			iterBegin->num = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("propInfoNum%d",propId)->getCString(),0);
			break;
		}
	}
}
void CommonData::setPropInfoById(int propId)
{
	std::list<UserPropInfoStr>::iterator iterBegin = AnalyseJson::logOnMsg.propInfo.begin();
	std::list<UserPropInfoStr>::iterator iterEnd = AnalyseJson::logOnMsg.propInfo.end();
	for(;iterBegin != iterEnd;++iterBegin)
	{
		if(iterBegin->id == propId)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("propInfoNum%d",propId)->getCString(),iterBegin->num);
			break;
		}
	}
	CCUserDefault::sharedUserDefault()->flush();
}

void CommonData::setLevelScore( int level,int score )
{
	std::list<UserStageInfoStr >::iterator iterBegin = AnalyseJson::logOnMsg.stageInfo.begin();
	std::list<UserStageInfoStr >::iterator iterEnd = AnalyseJson::logOnMsg.stageInfo.end();

	int maxLevelSize = AnalyseJson::logOnMsg.stageInfo.size();

	for(;iterBegin!=iterEnd;++iterBegin)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("levelScore%d",iterBegin->level)->getCString(),iterBegin->score);
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxLevel",maxLevelSize);

	CCUserDefault::sharedUserDefault()->flush();
}


void CommonData::getLevelScore()
{
	AnalyseJson::logOnMsg.stageInfo.clear();
	int MaxLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxLevel",0);
	for(int level =1; level <= MaxLevel; level++)
	{
		UserStageInfoStr stageInfoStr;

		stageInfoStr.level = level;
		stageInfoStr.score = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("levelScore%d",level)->getCString(),0);
		AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);
	}
	AnalyseJson::logOnMsg.stageInfo.sort();
}


void CommonData::unLockAllTheLevel()
{
	for (int i = AnalyseJson::logOnMsg.stageInfo.size()+1; i <= 90; i++)
	{
		UserStageInfoStr stageInfoStr;

		stageInfoStr.level = i;
		stageInfoStr.score = 100;
		stageInfoStr.starnum = 0;
		AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);

		CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("levelScore%d",stageInfoStr.level)->getCString(),stageInfoStr.score);

	}

	CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxLevel",90);

	CCUserDefault::sharedUserDefault()->flush();
}

void CommonData::gamePay( int type )
{
	//不要支付
	//return;
	switch (type)
	{
	case CANDY_PROP_LIFE:
		//生命
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_LIFE);
		break;
	case CANDY_PROP_OUT_COLORFULL:
		//彩塘
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_OUT_COLORFULL);
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		//炸弹唐
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_OUT_BOMBNEW);
		break;
	case CANDY_PROP_IN_RESORT:
		//重排
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_RESORT);
		break;
	case CANDY_PROP_IN_SWAP:
		//交换
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_SWAP);
		break;
	case CANDY_PROP_IN_HAMMER:
		//锤子
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_HAMMER);
		break;
	case CANDY_PROP_IN_STEP5:
		//加五步
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_STEP5);
		break;
	case GameGift_Level1:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level1);
		break;
	case GameGift_Level2:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level2);
		break;
	case GameGift_Level3:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level3);
		break;
	case Super_gift:
		//限时优惠包
		CandyPay::getInstance()->RequestCandyOrder(Super_gift);
		break;
	case Success_Pass:
		CandyPay::getInstance()->RequestCandyOrder(Success_Pass);
		break;
	case UnLock_Level:
		CandyPay::getInstance()->RequestCandyOrder(UnLock_Level);
		break;
	case Exit_Gift:
		CandyPay::getInstance()->RequestCandyOrder(Exit_Gift);
		break;
	case Zhadan_Gift:
		CandyPay::getInstance()->RequestCandyOrder(Zhadan_Gift);
		break;
	case Zhizun_Gift:
		CandyPay::getInstance()->RequestCandyOrder(Zhizun_Gift);
		break;
	default:
		break;
	}
}
