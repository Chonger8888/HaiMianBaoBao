#include "CandyTarget.h"
#include "CandyManager.h"
#include "../MsgMgr/MsgMgr.h"

/************************/
/* 关卡目标提示UI        */
/***********************/
USING_NS_CC;

#define TARGET_BG_IMG					"Image/CandyGame/Others/CandyTipsBg.png"
#define TARGET_INFO_IMG				"Image/CandyGame/Others/CandyTarget"

CCSprite* CandyTarget::targetBg = NULL;

CandyTarget::CandyTarget():targetNodeNum(0)
{
	
}

CandyTarget::~CandyTarget()
{
	
}

bool CandyTarget::getReachingTarget(void)
{
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
					{
						if(CandyManager::getInstance()->moveMgr->moveLimit <= 0)
							if(CandyManager::getInstance()->scoreMgr->getCurrentScore() >= CandyScore::starScoreNum[0])
								return true;
					}
				break;

			case CANDY_MODE_JELLY:
					{
						if(CandyManager::getInstance()->jellyMgr->getCandyJellyRemainNum() <= 0)
							return true;
					}
				break;

			case CANDY_MODE_INGREDIENT:
					{
						if(CandyManager::getInstance()->ingredientsMgr->numDropDoneCherry >= CandyIngredients::numCherry
							&& CandyManager::getInstance()->ingredientsMgr->numDropDoneChesnut>= CandyIngredients::numChesnut)
								return true;
					}
				break;

			case CANDY_MODE_TIMING:
					{
						if(CandyManager::timeLimit < 0)
							if(CandyManager::getInstance()->scoreMgr->getCurrentScore() >= CandyScore::starScoreNum[0])
								return true;
					}
				break;

			case CANDY_MODE_COLLECT:
					{
						CCLog("<<-----");
						for(int i =0; i<COLLECT_MAX_TYPE_NUM; i++)
						{
							if(CandyManager::collectCandy[i].currentNum != 0)
							{
								CCLog("collectCandy[%d] = %d",i,CandyManager::collectCandy[i].currentNum);
								return false;
							}
						}
						CCLog("----->>");
						return true;
					}
				break;
		}
	return false;
}

LoseTargetType CandyTarget::getLosingTarget(void)
{
	if(CandyManager::getInstance()->explosionMgr->isReadyToExplode() )
		return LOSE_TARGET_EXPLOSION;
	
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
			case CANDY_MODE_JELLY:
			case CANDY_MODE_INGREDIENT:
			case CANDY_MODE_COLLECT:
				if(CandyManager::getInstance()->moveMgr->moveLimit <= 0)
					return LOSE_TARGET_NO_MOVE;
				break;

			case CANDY_MODE_TIMING:
				if(CandyManager::timeLimit < 0)
					return LOSE_TARGET_NO_TIME;
				break;
		}
	return LOSE_TARGET_NOT_YET;
}


void CandyTarget::runTargetTipsAction(void)
{
	targetBg = CCSprite::create(TARGET_BG_IMG);
	CandyManager::getInstance()->uiLayer->addChild(targetBg,102);
	createTargetNode(targetBg);

	float fixedScreenHeight = CandyShare::getFixedScreenHeight();
	targetBg->setPosition(ccp(360.0f, fixedScreenHeight+400.0));
	targetBg->runAction(CCSequence::create(
							CCDelayTime::create(0.5f),
							CCEaseBackOut::create(CCMoveTo::create(0.5f,ccp(360.0f, fixedScreenHeight*0.5f))),
							CCCallFunc::create(this, callfunc_selector(CandyTarget::runTargetNodeAction)), 
							CCDelayTime::create(2.0f),
							CCEaseBackIn::create(CCMoveTo::create(0.5f,ccp(360.0f, fixedScreenHeight+400.0))),
							CCCallFunc::create(this, callfunc_selector(CandyTarget::targetTipsActionCallback)), 
							NULL
						)
					);
}


void CandyTarget::targetTipsActionCallback(void)
{
	if(CandyTarget::targetBg)
		{
			CandyTarget::targetBg->removeFromParent();
			CandyTarget::targetBg= NULL;
		}
	//CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_USE_PROP);
}

void CandyTarget::createTargetNode(CCNode *parent)
{
	for(int i=0; i<3; i++)
	{
		targetNode[i]= CandyManager::getInstance()->uiLayer->getTargetIconNode(i+1);
		if(targetNode[i])
		{
			targetNodePos[i] = ccpSub(targetNode[i]->getPosition(), 
				ccp(0,CandyShare::getFixedScreenHeight()*0.5f - parent->getContentSize().height *0.5f)) ;
			targetNodeNum++;
		}
	}

	const int offsetX = 260; //图片从400像素开始
	const int nodeY = 110;
	int gapX = (TARGET_SCREEN_WIDTH - offsetX)/targetNodeNum;
	int exsitNum = 0;
	for(int i=0; i<3; i++)
	{
		if(targetNode[i])
		{
			targetNode[i]->setPosition(ccp(offsetX + gapX*(0.4f+exsitNum), nodeY));
			targetBg->addChild(targetNode[i]);
			exsitNum++;
		}
	}
	CCSprite *pImg = NULL;
	switch(CandyManager::gameMode)
	{
	case CANDY_MODE_NORMAL:
		pImg = CCSprite::create("Image/CandyGame/Others/targetTip1.png");
		pImg->setPosition(ccp(440,180));
		targetBg->addChild(pImg);
		break;

	case CANDY_MODE_JELLY:
		pImg = CCSprite::create("Image/CandyGame/Others/targetTip2.png");
		pImg->setPosition(ccp(440,190));
		targetBg->addChild(pImg);
		break;

	case CANDY_MODE_INGREDIENT:
		pImg = CCSprite::create("Image/CandyGame/Others/targetTip4.png");
		pImg->setPosition(ccp(440,190));
		targetBg->addChild(pImg);
		break;

	case CANDY_MODE_COLLECT:
		pImg = CCSprite::create("Image/CandyGame/Others/targetTip3.png");
		pImg->setPosition(ccp(440,180));
		targetBg->addChild(pImg);
		break;
	}

}

void CandyTarget::runTargetNodeAction(void)
{
	for(int i=0; i<3; i++)
	{
		if(targetNode[i])
		{
			targetNode[i]->runAction(CCSequence::create
				(CCDelayTime::create(0.3f*i + 1.0f),
				CCSpawn::create(CCMoveTo::create(0.5f, targetNodePos[i]), CCScaleTo::create(0.5f,0.3f),CCFadeOut::create(0.6f), NULL),
				CCCallFuncN::create(this, callfuncN_selector(CandyTarget::targetNodeActionCallback)),
				NULL));

			CCLabelAtlas *targetNodeChild = (CCLabelAtlas *)targetNode[i]->getChildByTag(TARGET_NODE_LABEL_TAG);
			if(targetNodeChild)
			{
				targetNodeChild->runAction(CCSequence::create
					(CCDelayTime::create(0.3f*i + 1.0f),
					CCFadeOut::create(0.6f),
					NULL));
			}
		}
	}
}

void CandyTarget::targetNodeActionCallback(CCNode* sender)
{
	if(targetNode[targetNodeNum-1] == sender)
		{
				CCPoint pos = ccpAdd(sender->getPosition(), ccp(0,CandyShare::getFixedScreenHeight()*0.5f - 110)) ;
			CandyManager::getInstance()->effectLayer->displayTargetIconEffect();
		}
}
