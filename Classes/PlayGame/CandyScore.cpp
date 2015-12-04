#include "CandyScore.h"
#include "CandyManager.h"

USING_NS_CC;

#define CANDY_SCORE_LABEL_IMG		"LabelNum/Score"
#define CANDY_SCORE_LABEL_WIDTH	28
#define CANDY_SCORE_LABEL_HEIGHT	34

int CandyScore::starScoreNum[3] = {0};


// totalscore 222 ·ÀÖ¹´Ü¸Ä
CandyScore::CandyScore():comboNumber(0),totalScore(DIFFERENCE_DATA),totalScoreLabel(NULL),candyBaseScore(50),accumulateFlag(false),accumulateScore(0)
{
	
}

CandyScore::~CandyScore()
{
}

void CandyScore::updateCandyScore(void)
{
	if(!CandyManager::getInstance()->shareMgr->getCandyIdle())
		return;

	if(comboNumber > 0)
		{
			if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_PLAYING)
				{
					CandyManager::getInstance()->musicMgr->playPraiseEffect(comboNumber);
					CandyManager::getInstance()->uiLayer->showComboPraise(comboNumber);
				}
			comboNumber = 0;
			
		}
}

void CandyScore::updateStarScoreProgressBar(void)
{
	if(CandyScore::starScoreNum[0] == 0 || CandyScore::starScoreNum[1]== 0 || CandyScore::starScoreNum[2]== 0 )
		return;

	CandyManager::getInstance()->uiLayer->setScoreStarPercentage(100.0f * (totalScore - DIFFERENCE_DATA)  /CandyScore::starScoreNum[2]);
}

int CandyScore::getComboNumber(void)
{
	return comboNumber;
}


void CandyScore::increaseComboNumber(void)
{
	CandyManager::getInstance()->musicMgr->playComboEffect(comboNumber);

	++comboNumber;
}


void CandyScore::displayCandyScore(int score, CCPoint pos, CandyColor color)
{
	int scoreLabelImg;//0~6
	
	if(color>=CANDY_COLOR_RED && color<=CANDY_COLOR_PURPLE)
		{
			scoreLabelImg = (int)color;
		}
	else if(color == CANDY_COLOR_CHERRY || color == CANDY_COLOR_CHESNUT)
		{
			scoreLabelImg = 6;
		}
	else
		{
			scoreLabelImg = rand() % 7;
		}
#if 1
	  // Upper Label
	int fontFileNum = color <CANDY_COLOR_NORMAL_NUM?color:CANDY_COLOR_BLUE;
	if(CommonData::m_doubleScore == 2)
	{
		fontFileNum = 6;
	}
	CCLabelBMFont *socreLabel = CCLabelBMFont::create(CCString::createWithFormat("%d",score)->getCString(), 
		CCString::createWithFormat("fonts/Score%d/font.fnt",fontFileNum)->getCString() );

	
#else	
	CCLabelAtlas* socreLabel = CCLabelAtlas::create(CCString::createWithFormat("%d",score)->getCString(), 
							CCString::createWithFormat("%s%d.png",CANDY_SCORE_LABEL_IMG, scoreLabelImg)->getCString(), 
							CANDY_SCORE_LABEL_WIDTH, CANDY_SCORE_LABEL_HEIGHT, '0');
#endif
  	socreLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	socreLabel->setPosition(pos);
	socreLabel->setScale(0.5f);
	CandyManager::getInstance()->candyLayer->addChild(socreLabel, SCORE_ORDER );
	CCFiniteTimeAction*  action1 =CCSequence::create(
										CCScaleTo::create(0.2f, 1.0f),
										CCMoveBy::create(1.0f,ccp(0,25)),
										CCCallFuncN::create(NULL, callfuncN_selector(CandyScore::displayCandyScoreCallBack)),
						 				NULL);
	CCFiniteTimeAction*  action2 =CCSequence::create(
										CCDelayTime::create(1.0f),
										CCFadeOut::create(0.2f),
						 				NULL);
	socreLabel->runAction(action1);
	socreLabel->runAction(action2);
	

	
	int fontGap = -8;
	int numTem = 10;
	int numCount = 1;
	while(score >= numTem)
		{
			
			CCSprite* fontChild = (CCSprite*)socreLabel->getChildByTag(numCount);
			if(fontChild)
				{
					float fontChildPosX = fontChild->getPositionX();
					fontChild->setPositionX(fontChildPosX + fontGap * numCount);
				}
			numCount++;
			numTem*=10;
		}
#if 0
	ccColor3B fontColor;
    	switch(color)
    	{
    		case CANDY_COLOR_RED:
			fontColor = ccRED;
			break;

		case CANDY_COLOR_BLUE:
			fontColor = ccBLUE;
			break;

		case CANDY_COLOR_GREEN:
			fontColor = ccGREEN;
			break;

		case CANDY_COLOR_YELLOW:
			fontColor = ccYELLOW;
			break;

		case CANDY_COLOR_ORANGE:
			fontColor = ccORANGE;
			break;

		case CANDY_COLOR_PURPLE:
			fontColor = ccMAGENTA;
			break;

		default:
			fontColor = ccWHITE;
			break;
    	}
	socreLabel->setColor(fontColor);

	#endif
}

void CandyScore::displayCandyScoreCallBack(CCNode* sender)
{
	sender->removeFromParent();
}

int CandyScore::getCurrentScore(void)
{
	return totalScore - DIFFERENCE_DATA;
}

void CandyScore::addCandyScore(int score, CCPoint pos , CandyColor color)
{
	if(score <= 0)
		return;

	score = score * CommonData::m_doubleScore;
	if(accumulateFlag)
		{
			accumulateScore += score;
			return;
		}
	
	totalScore += score;
	displayCandyScore(score, pos, color);
	updateStarScoreProgressBar();

	for(int i=0; i<3; i++)
		{
			if((totalScore - DIFFERENCE_DATA) >= CandyScore::starScoreNum[i] && (totalScore - DIFFERENCE_DATA) -score <  CandyScore::starScoreNum[i])
				{
					CandyManager::getInstance()->uiLayer->displayStarPercentEffect(i);
					CandyManager::getInstance()->uiLayer->setScoreGrayStarVisible(i, false);
				}
		}
}

void CandyScore::setAccumulateScoreFlag(bool state, bool display)
{
	accumulateFlag = state;
	if(accumulateFlag == false  && display == true)
		{
			addCandyScore(accumulateScore, CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4)));
			accumulateScore = 0;
		}
}