#include "CandyRoulette.h"
#include "CandyManager.h"
/************************/
/* ×ªÅÌUI			   */
/***********************/
#define CANDY_ROULETTE_LAYOUT_FILE		"Image/CandyGame/CandyGameRoulette/CandyRoulette.json"
#define ROULETTE_MOVE_LEN					800
#define ROULETTE_MOVE_TIME				1.5f

CandyRouletteLayout::CandyRouletteLayout()
{
	rouletteLayout = NULL;
}

Layout* CandyRouletteLayout::getRouletteLayout(void)
{
	if(!rouletteLayout)
		{
			rouletteLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDY_ROULETTE_LAYOUT_FILE));
			rouletteLayout->retain();

			rouletteStart = dynamic_cast<UIButton*>(rouletteLayout->getChildByName("StartRoulete"));
			rouletteStart->addReleaseEvent(this, coco_releaseselector(CandyRouletteLayout::rouletteButtonCallback));
			
			rouletteBg = dynamic_cast<UIImageView*>(rouletteLayout->getChildByName("RouletteBg"));
			rouletteNum = dynamic_cast<UIImageView*>(rouletteLayout->getChildByName("RouletteNum"));
			rouletteType = dynamic_cast<UIImageView*>(rouletteLayout->getChildByName("RouletteType"));

			roulettePos = rouletteBg->getPosition();
			rouletteBg->setPosition(ccp(roulettePos.x, roulettePos.y + ROULETTE_MOVE_LEN));
			rouletteBg->runAction(CCEaseElasticOut::create(CCMoveBy::create(ROULETTE_MOVE_TIME,ccp(0,-ROULETTE_MOVE_LEN))));
		}
	rouletteStart->setTouchEnable(true);
	rouletteStart->isEffects(true);
	return rouletteLayout;
}

void CandyRouletteLayout::releaseRouletteLayout(void)
{
	CC_SAFE_RELEASE_NULL(rouletteLayout);
}

void CandyRouletteLayout::rouletteButtonCallback(CCObject *pSender)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	CommonData::setButtonTouchEnable( pSender, false);
	//rouletteStart->setVisible(false);
	rouletteInCallback();
}

int CandyRouletteLayout::adjustRouletteProbability(void)
{
	int resultNum =1;
	
	int randNum = rand()%100;
	if(rouletteSpecialtype == 0)//colorful
		{
			if(randNum<30)
				{
					resultNum =1;
				}
			else if(randNum<60)
				{
					resultNum =2;
				}
			else if(randNum<80)
				{
					resultNum =3;
				}
			else
				{
					resultNum =4;
				}
		}
	else if(rouletteSpecialtype == 1)//bomb
		{
			if(randNum<30)
				{
					resultNum =1;
				}
			else if(randNum<50)
				{
					resultNum =2;
				}
			else if(randNum<70)
				{
					resultNum =3;
				}
			else if(randNum<90)
				{
					resultNum =4;
				}
			else
				{
					resultNum =5;
				}
		}
	else if(rouletteSpecialtype == 2)//strip
		{
			if(randNum<20)
				{
					resultNum =1;
				}
			else if(randNum<35)
				{
					resultNum =2;
				}
			else if(randNum<50)
				{
					resultNum =3;
				}
			else if(randNum<65)
				{
					resultNum =4;
				}
			if(randNum<75)
				{
					resultNum =5;
				}
			else if(randNum<85)
				{
					resultNum =6;
				}
			else if(randNum<95)
				{
					resultNum =7;
				}
			else
				{
					resultNum =8;
				}
		}
	return  (8-resultNum) *45 + 5 + rand()%35;
}

void CandyRouletteLayout::rouletteInCallback(void)
{
	int randNum = rand()%360;
	if(randNum%120 < 5)
		randNum +=5;
	else if(randNum%120 > (120-5))
		randNum -=5;
	
	rouletteTypeRotate = 360*11+randNum;
	rouletteSpecialtype = 2 -((int)rouletteTypeRotate%360)/120;

	rouletteNumRotate = 360 *5+adjustRouletteProbability();
	rouletteSpecialNum = 8 - ((int)rouletteNumRotate%360)/45;
	
	CCActionInterval*  rouletteNumAction = CCRotateBy::create(5, rouletteNumRotate);
	CCActionInterval*  rouletteTypeAction = CCRotateBy::create(7, rouletteTypeRotate);
	
	CCActionInterval*  rouletteNumEase = CCEaseInOut::create(rouletteNumAction, 3.0f);
	CCActionInterval*  rouletteTypeEase = CCEaseInOut::create(rouletteTypeAction, 3.0f);

	rouletteNum->runAction(rouletteNumEase);
	rouletteType->runAction(CCSequence::create(
								rouletteTypeEase,
								CCCallFunc::create(this, callfunc_selector(CandyRouletteLayout::rotateDoneCallback)),
								NULL));

	rouletteType->runAction(CCSequence::create(CCDelayTime::create(0.5f),
											CCCallFunc::create(this, callfunc_selector(CandyRouletteLayout::rotateMusicCallback)),
											NULL));
	
}

void CandyRouletteLayout::rotateMusicCallback(void)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_ROULETTE_IN);
}

void CandyRouletteLayout::rotateDoneCallback(void)
{
	rouletteBg->runAction(CCSequence::create(
										CCEaseElasticIn::create(CCMoveBy::create(ROULETTE_MOVE_TIME,ccp(0,ROULETTE_MOVE_LEN))),
										CCCallFunc::create(NULL, callfunc_selector(CandyRouletteLayout::rouletteOutCallback)),
										NULL
									));
}
void CandyRouletteLayout::rouletteOutCallback(void)
{
	CandyManager::getInstance()->resultMgr->getResultLayer()->getUILayer()->removeWidget(CandyRoulette::getLayout());
	CandyManager::getInstance()->resultMgr->removeResultLayer();
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	CandyRoulette::startRunRoulette();
	CandyRoulette::releaseLayout();
	CandyManager::getInstance()->uiLayer->resetEnergyJarPercentage();
}



CandyRouletteLayout* CandyRoulette::layout = NULL;
Layout* CandyRoulette::getLayout(void)
{
	if(!layout)
		{
			layout = new CandyRouletteLayout();
		}
	return layout->getRouletteLayout();
}

void CandyRoulette::releaseLayout(void)
{
	if(layout)
		{
			layout->releaseRouletteLayout();
			CC_SAFE_DELETE(layout);
		}
}

void CandyRoulette::startRunRoulette(void)
{
	if(layout)
		{
			CandySpecial special;
			switch(layout->rouletteSpecialtype)
				{
					case 0:
						special = CANDY_SPECIAL_COLORFULL;
						break;

					case 1:
						special = CANDY_SPECIAL_BOMB;
						break;

					case 2:
						special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;
						break;
				}
			for(int i=0; i<layout->rouletteSpecialNum; i++)
			{
				if(layout->rouletteSpecialtype == 2)
					special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;

				CandyCell *candy = CandyCell::getRandomNormalCandy();
				if(candy)
					candy->runCandyChangeSpecialDelay(special, 0.5f*(i+1));
			}
									
		}
}
