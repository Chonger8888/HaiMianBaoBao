#include "CandyGuideLayer.h"
#include "CandyManager.h"
#include "../MsgMgr/AnalyseJson.h"

/************************/
/* 新手指导			   */
/***********************/
USING_NS_CC;

#define GUIDE_CONTENT_BG_IMG				"Image/CandyGame/Teach/Font/teachContentBg.png"
#define GUIDE_FONT_STRING_XML				"Image/CandyGame/Teach/Font/strings.xml"
#define GUIDE_FONT_STRING_FONT			"Image/CandyGame/Teach/Font/font.fnt"
#define GUIDE_GUIDE_MAN_IMG				"Image/CandyGame/Teach/teacher.png"
#define GUIDE_GUIDE_FINGER_IMG			"Image/CandyGame/Teach/teachFinger.png"
#define ISEE_BUTTON_NORMAL_IMG			"Image/CandyGame/Teach/Font/ISeeNorm.png"
#define ISEE_BUTTON_SELECT_IMG			"Image/CandyGame/Teach/Font/ISeeSelected.png"

#define SKIP_BUTTON_NORMAL_IMG			"Image/CandyGame/Teach/Font/SkipNorm.png"
#define SKIP_BUTTON_SELECT_IMG			"Image/CandyGame/Teach/Font/SkipSelected.png"

#define GUIDE_FADE_IN_TIME					0.5f
#define GUIDE_FADE_OUT_TIME				0.5f

#define GUIDE_EXAMPLE_TAG					220
#define SKIP_EXAMPLE_TAG					221

bool CandyGuideLayer::init(void)
{
	if ( !CCLayer::init() )
		{
			return false;
		}
	
	currentStep = 0;
	isGuiding = false;
	isDisplaying = false;
	moveableStates = false;
	guideSprite = NULL;
	guideMan = NULL;
	guideFont = NULL;
	guideFinger = NULL;
	guideTaech = NULL;
	return true;
}

void CandyGuideLayer::onEnter(void)
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, GUIDE_LAYER_PRIORITY, true);
	scheduleUpdate();
	
	initGuideData();
	createDisplayGuide();


#ifdef CANDY_STATISITICAL_DATA
	/*if ( 0 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_58 );
	else if ( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_84 );*/
	
#endif
}

void CandyGuideLayer::onExit(void)
{
	unscheduleUpdate();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
		
bool CandyGuideLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_SHOW_TARGET)
		{
			CandyManager::getInstance()->resultMgr->unDisplayTargetTips();
			return false;
		}

	if(getShowExample())
		return true;
		

	if (( 3 == CandyManager::currentLevel && 2 == currentStep ) // 第三关第二步
		|| ( 4 == CandyManager::currentLevel && 1 == currentStep )// 第四关第一步
		|| ( 1 == CandyManager::currentLevel && 2 == currentStep ))// 第1关第二步
	{
		setGuiding(false);
		return false; 
	}

	moveableStates = false;
	if(CandyManager::getInstance()->shareMgr->getCandyIdle())
		{
			if( CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), firstTouchCandy) )
				{
					if(firstTouchCandy.x == guideData.targetIndex[currentStep][0].x && firstTouchCandy.y == guideData.targetIndex[currentStep][0].y)
						{
							moveableStates = true;
							secondTargetCandy = guideData.targetIndex[currentStep][1];
							CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->setScale(1.2f);
						}
					else if(firstTouchCandy.x == guideData.targetIndex[currentStep][1].x && firstTouchCandy.y == guideData.targetIndex[currentStep][1].y)
						{
							moveableStates = true;
							secondTargetCandy = guideData.targetIndex[currentStep][0];
							CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->setScale(1.2f);
						}
				}
		}
	
	return true;
}


void CandyGuideLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!moveableStates)
		return;
	
	bool ret = CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), secondTouchCandy) ;

	if(secondTouchCandy.x == secondTargetCandy.x && secondTouchCandy.y == secondTargetCandy.y)
		{
			CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->setScale(1.0f);
			CandyManager::getInstance()->moveMgr->moveCandy(firstTouchCandy, secondTouchCandy, CHANGE_MODE_BY_USER);

			moveableStates = false;
			CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->setScale(1.0f);
			
			finishCurrentStep();
		}
}

void CandyGuideLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(moveableStates)
		CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->setScale(1.0f);
}

void CandyGuideLayer::update(float time)
{
	if(CandyManager::getInstance()->candyLayer->numberOfRunningActions())
		return;
	
	if(!CandyManager::getInstance()->resultMgr->getGameRunning() )
		return;
	
	if(isGuiding)
		{
			if(CandyManager::getInstance()->shareMgr->getCandyIdle())
				{
					doDisplayGuide();
				}
		}
}

void CandyGuideLayer::initGuideData(void)
{
#ifndef WIN32 // Eason
	if(CommonData::getMaxLevel() >= CandyManager::currentLevel
		&& CandyManager::currentLevel != 7)
	{
		setGuiding(false);
		return;
	}
	

#endif

	memset(&guideData, 0, sizeof(guideData));
	switch(CandyManager::currentLevel)
		{
			case 1:
				{
					guideData.totalSteps = 3;

					guideData.highLightNum[0] = 4;

					guideData.highLightArea[0][0] = cIndex(6,2);
					guideData.highLightArea[0][1] = cIndex(7,2);
					guideData.highLightArea[0][2] = cIndex(7,3);
					guideData.highLightArea[0][3] = cIndex(7,4);

					guideData.targetIndex[0][0] 	= cIndex(6,2);
					guideData.targetIndex[0][1] 	= cIndex(7,2);


					guideData.highLightNum[1] = 5;

					guideData.highLightArea[1][0] = cIndex(6,2);
					guideData.highLightArea[1][1] = cIndex(6,3);
					guideData.highLightArea[1][2] = cIndex(6,4);
					guideData.highLightArea[1][3] = cIndex(6,5);
					guideData.highLightArea[1][4] = cIndex(7,3);
				
					guideData.targetIndex[1][0] 	= cIndex(6,3);
					guideData.targetIndex[1][1] 	= cIndex(7,3);

					setGuiding(true);
					
				}
				break;
#if 0
			case 2:
				{
					guideData.totalSteps = 4;
					guideData.highLightNum[0] = 5;
					guideData.highLightNum[1] = 4;
					guideData.highLightNum[2] = 5;
					guideData.highLightNum[3] = 4;
					
					guideData.highLightArea[0][0] = cIndex(6,0);
					guideData.highLightArea[0][1] = cIndex(6,1);
					guideData.highLightArea[0][2] = cIndex(6,2);
					guideData.highLightArea[0][3] = cIndex(5,2);
					guideData.highLightArea[0][4] = cIndex(6,3);
						
					guideData.highLightArea[1][0] = cIndex(6,3);
					guideData.highLightArea[1][1] = cIndex(6,4);
					guideData.highLightArea[1][2] = cIndex(7,4);
					guideData.highLightArea[1][3] = cIndex(6,5);
					
					guideData.highLightArea[2][0] = cIndex(7,3);
					guideData.highLightArea[2][1] = cIndex(7,4);
					guideData.highLightArea[2][2] = cIndex(7,5);
					guideData.highLightArea[2][3] = cIndex(7,6);
					guideData.highLightArea[2][4] = cIndex(8,5);

					guideData.highLightArea[3][0] = cIndex(6,4);
					guideData.highLightArea[3][1] = cIndex(7,4);
					guideData.highLightArea[3][2] = cIndex(7,5);
					guideData.highLightArea[3][3] = cIndex(7,6);
					
					guideData.targetIndex[0][0] 	= cIndex(5,2);
					guideData.targetIndex[0][1] 	= cIndex(6,2);

					guideData.targetIndex[1][0] 	= cIndex(6,4);
					guideData.targetIndex[1][1] 	= cIndex(7,4);

					guideData.targetIndex[2][0] 	= cIndex(7,5);
					guideData.targetIndex[2][1] 	= cIndex(8,5);

					guideData.targetIndex[3][0] 	= cIndex(6,4);
					guideData.targetIndex[3][1] 	= cIndex(7,4);
					setGuiding(true);
				}
				break;
#endif
			case 3:
				{
					guideData.totalSteps = 3;
				
					// teachFont0301
					guideData.highLightNum[0] = 6;

					guideData.highLightArea[0][0] = cIndex(5,2);
					guideData.highLightArea[0][1] = cIndex(3,3);
					guideData.highLightArea[0][2] = cIndex(4,3);
					guideData.highLightArea[0][3] = cIndex(5,3);
					guideData.highLightArea[0][4] = cIndex(6,3);
					guideData.highLightArea[0][5] = cIndex(5,4);

					guideData.targetIndex[0][0] 	= cIndex(5,3);
					guideData.targetIndex[0][1] 	= cIndex(6,3);
					
					//交换特殊糖果会有惊喜哦
					guideData.highLightNum[1] = 2;

					guideData.highLightArea[1][0] = cIndex(4,4);
					guideData.highLightArea[1][1] = cIndex(5,4);

					guideData.targetIndex[1][0] 	= cIndex(4,4);
					guideData.targetIndex[1][1] 	= cIndex(5,4);


					CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(4,2));
					candy1->changeCandySpecial(CANDY_SPECIAL_HORIZONTAL,false);

					setGuiding(true);
				}
				break;
#if 0
			case 4:
				{
					guideData.totalSteps = 2;
					guideData.highLightNum[0] = 2;
				
					guideData.highLightArea[0][0] = cIndex(4,3);
					guideData.highLightArea[0][1] = cIndex(4,4);
					
					guideData.targetIndex[0][0] 	= cIndex(4,3);
					guideData.targetIndex[0][1] 	= cIndex(4,4);

					setGuiding(true);

					CandyCell::CreateNewCandySpecial(guideData.targetIndex[0][0], CANDY_SPECIAL_BOMB);
					CandyCell::CreateNewCandySpecial(guideData.targetIndex[0][1], CANDY_SPECIAL_VERTICAL);
#if 0
					CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(guideData.targetIndex[0][0]);
					CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(guideData.targetIndex[0][1]);

					if(candy1 && candy2)
					{
						candy1->changeCandySpecial(CANDY_SPECIAL_BOMB,false);
						candy2->changeCandySpecial(CANDY_SPECIAL_VERTICAL,false);
					}
					else
					{
						candy1 = CandyCell::create(guideData.targetIndex[0][0], CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_BOMB);
						candy2 = CandyCell::create(guideData.targetIndex[0][1], CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_VERTICAL);
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(guideData.targetIndex[0][0], candy1);
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(guideData.targetIndex[0][1], candy2);
						CandyManager::getInstance()->candyLayer->addToCandyParent(candy1);
						CandyManager::getInstance()->candyLayer->addToCandyParent(candy2);
					}
#endif
				}
				
				break;
#endif
#if 0
			case 5:

				{
					guideData.totalSteps = 2;
					guideData.highLightNum[0] = 6;
					guideData.highLightNum[1] = 2;
				
					guideData.highLightArea[0][0] = cIndex(4,3);
					guideData.highLightArea[0][1] = cIndex(4,4);
					guideData.highLightArea[0][2] = cIndex(4,5);
					guideData.highLightArea[0][3] = cIndex(3,5);
					guideData.highLightArea[0][4] = cIndex(4,6);
					guideData.highLightArea[0][5] = cIndex(4,7);
					
					guideData.highLightArea[1][0] = cIndex(4,6);
					guideData.highLightArea[1][1] = cIndex(4,7);
					

					guideData.targetIndex[0][0] 	= cIndex(3,5);
					guideData.targetIndex[0][1] 	= cIndex(4,5);

					guideData.targetIndex[1][0] 	= cIndex(4,6);
					guideData.targetIndex[1][1] 	= cIndex(4,7);

					setGuiding(true);
				}
				break;
#endif
			case 7:
				{

					CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(4,4));
					candy1->changeCandySpecial(CANDY_SPECIAL_HORIZONTAL,false);

					CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(4,5));
					candy2->changeCandySpecial(CANDY_SPECIAL_VERTICAL,false);

#if 0
					CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(4,4));
					CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(4,5));

					if(candy1 && candy2)
					{
						candy1->changeCandySpecial(CANDY_SPECIAL_HORIZONTAL,false);
						candy2->changeCandySpecial(CANDY_SPECIAL_VERTICAL,false);
					}
					else
					{
						candy1 = CandyCell::create(cIndex(4,4), CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_HORIZONTAL);
						candy2 = CandyCell::create(cIndex(4,5), CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_VERTICAL);
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(4,4), candy1);
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(4,5), candy2);
						CandyManager::getInstance()->candyLayer->addToCandyParent(candy1);
						CandyManager::getInstance()->candyLayer->addToCandyParent(candy2);
					}
#endif
					setGuiding(false);
				}
				break;
			default:
				{
					if(getShowExample())
						setGuiding(true);
					else
						setGuiding(false);
				}
				break;
		}
}


void CandyGuideLayer::setGuiding(bool states)
{
	isGuiding = states;
	CandyManager::getInstance()->correctMapMgr->setDisplayCandyDispelTipsFlag(isGuiding?false:true);
	
	if(!isGuiding)
		this->removeFromParent();
}

bool CandyGuideLayer::getGuiding(void)
{
	return isGuiding;
}

bool CandyGuideLayer::getShowExample(void)
{
	bool ret = false;
// 	switch(CandyManager::currentLevel)
// 	{
// 	case 5:
// 	case 9:
// 	case 16:
// 	case 31:
// 	case 46:
// 	case 61:
// 	case 76:
// 	case 91:
// 	case 136:
// 	case 181:
// 		ret= true;
// 		break;
// 	}
	return ret;
}

void CandyGuideLayer::finishCurrentStep(void)
{
	unDisplayGuide();
	if(++currentStep >= guideData.totalSteps)
		{
			setGuiding(false);
	#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_18, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());
	#endif
		}
}

void CandyGuideLayer::createDisplayGuide(void)
{
	guideUiLayer = UILayer::create();
	guideUiLayer->setTouchPriority(GUIDE_LAYER_PRIORITY);
	addChild(guideUiLayer,1);
	
	unDisplayGuide();

}

void CandyGuideLayer::doDisplayGuide(void)
{
	if(isDisplaying)
		return;
	
	isDisplaying = true;

	if(!getShowExample())
		if( !CandyManager::getInstance()->dispelMgr->getDispelStateByChangeCandy(
			guideData.targetIndex[currentStep][0], guideData.targetIndex[currentStep][1]))
			{

			#ifndef WIN32  //Eason
				if (( 1 == CandyManager::currentLevel && 0 == currentStep )
					||( 1 == CandyManager::currentLevel && 1 == currentStep )
					||( 3 == CandyManager::currentLevel && 0 == currentStep )
					||( 3 == CandyManager::currentLevel && 1 == currentStep ))
				{
					CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(guideData.targetIndex[currentStep][0]);
					CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(guideData.targetIndex[currentStep][1]);
					// 判断交换两点是否为可组合消除模式
					if(!CandyManager::getInstance()->combinationMgr->checkCandyCombination(candy1, candy2))
					{
						setGuiding(false);
						return;
					}
				}
			#endif		
			}
	
	updateGuideSprite();
	updateGuideFont();
	updateGuideMan();
	updateGuideFinger();
	updateGuideExample();
	
	guideSprite->setOpacity(0);
	guideSprite->runAction(CCFadeIn::create(GUIDE_FADE_IN_TIME));
}

void CandyGuideLayer::unDisplayGuide(void)
{
	isDisplaying = false;
	
	if(guideSprite)
		{
			guideSprite->runAction(CCFadeOut::create(GUIDE_FADE_OUT_TIME));
			guideFinger->stopAllActions();
		}
		
	
}

void CandyGuideLayer::updateGuideSprite(void)
{
	if(guideSprite)
		{
			guideSprite->removeFromParent();
			guideSprite = NULL;
		}
	
	guideSprite = createGuideSprite();
	guideSprite->setCascadeOpacityEnabled(true);
	guideSprite->setAnchorPoint(ccp(0,0));
	addChild(guideSprite);
}

//　设置指引人物位置
void CandyGuideLayer::updateGuideMan(void)
{
	// 新手静态老师
	guideMan = CCSprite::create(GUIDE_GUIDE_MAN_IMG);
	//guideSprite->addChild(guideMan,2);
	guideMan->setFlipX(true);
	guideMan->setPosition(ccp(600,150));

	// 新手动态态老师
// 	guideTaech= CCArmature::create("xszy");
// 	guideTaech->getAnimation()->play("xszy1");
// 	guideTaech->setPosition(ccp(600,150));
// 	guideTaech->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyGuideLayer::StartAnimationEvent));

	//guideSprite->addChild(guideTaech);

	if(getShowExample())
		{
			guideMan->setPosition(ccp(600,400));
			guideMan->setFlipX(true);
		}
	else
		{
			CCPoint fontPos = guideFont->getPosition();
			CCPoint fontAnchor = guideFont->getAnchorPoint();
			float fixedScreenHeight = CandyShare::getFixedScreenHeight();
			guideMan->setAnchorPoint(fontAnchor);
			guideMan->setPosition(ccp(fontPos.x, fontPos.y-250));

			if((CandyManager::currentLevel == 3 && currentStep == 2))
				guideMan->setFlipX( fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT? true:true );

			// Create i see button
			if((CandyManager::currentLevel == 1 && currentStep == 2)
				||(CandyManager::currentLevel == 3 && currentStep == 2))
			{
				createISeeButton();
			}
//  			else
// 			{
// 				//　Create skip button
//  				createSkipButton();
// 			}
			
		}
	

	
}

void CandyGuideLayer::updateGuideFont(void)
{	
	createGuideFont();
	setGuideFontPos();
}

void CandyGuideLayer::updateGuideFinger(void)
{
	if(getShowExample() || (CandyManager::currentLevel == 3 &&  currentStep == 2) 
		|| (CandyManager::currentLevel == 4 &&  currentStep == 1)
		|| ( 1 == CandyManager::currentLevel && 2 == currentStep ))
		return;
	
	guideFinger = CCSprite::create(GUIDE_GUIDE_FINGER_IMG);
	guideSprite->addChild(guideFinger,2);

	CCPoint pos1 = CandyManager::getInstance()->shareMgr->getPosByIndex(guideData.targetIndex[currentStep][0]);
	CCPoint pos2 = CandyManager::getInstance()->shareMgr->getPosByIndex(guideData.targetIndex[currentStep][1]);
	CCPoint offsetPos = ccpSub(pos2,pos1);
	CCActionInterval* moveBy = CCMoveBy::create(0.65f, offsetPos);
	CCActionInterval* moveBack = ((CCActionInterval*)moveBy->copy()->autorelease())->reverse();
	CCRepeatForever* move = CCRepeatForever::create(CCSequence::create(
															CCCallFuncN::create(guideFinger, callfuncN_selector(CandyGuideLayer::displayGuideFingerEffect)),
															moveBy,
															moveBack,
															NULL));

	guideFinger->setAnchorPoint(ccp(0.15f,1.0f));
	guideFinger->setPosition(pos1);
	guideFinger->runAction(move);
	guideFinger->setCascadeOpacityEnabled(true);
}

void CandyGuideLayer::updateGuideExample(void)
{
	switch(CandyManager::currentLevel)
		{
			case 5:
				createGuideExample5();
				break;
			case 9:
				createGuideExample9();
				break;
			case 16:
				createGuideExample16();// mode 2
				break;
			case 31:
				createGuideExample31();
				break;
// 			case 46:
// 				createGuideExample46();
// 				break;
			case 61:
				createGuideExample61();
				break;
			case 76:
				createGuideExample76();
				break;
			case 91:
				createGuideExample91();
				break;
			case 136:
				createGuideExample136();
				break;
			case 181:
				createGuideExample181();
				break;
		}
}

CCSprite* CandyGuideLayer::createGuideFont(void)
{
	guideFont = CCSprite::create(GUIDE_CONTENT_BG_IMG);
	guideFont->setScale( 2.0f );
	//guideSprite->addChild(guideFont,2);

	CCDictionary *strings = CCDictionary::createWithContentsOfFile(GUIDE_FONT_STRING_XML);
  	char *fontString;
	

	if(CandyManager::currentLevel ==1 && currentStep == 0)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0101"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==1 && currentStep == 1)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0102"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==1 && currentStep == 2)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0103"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==3 && currentStep == 0)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0301"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==3 && currentStep == 1)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0302"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==3 && currentStep == 2)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0303"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==2 && currentStep == 0)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0201"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==2 && currentStep == 1)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0202"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==2 && currentStep == 2)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0201"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==2 && currentStep == 3)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0202"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==4 && currentStep == 0)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0401"))->m_sString.c_str();
	else if(CandyManager::currentLevel ==4 && currentStep == 1)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont0402"))->m_sString.c_str();
// 	else if(CandyManager::currentLevel ==5 && currentStep == 0)
// 		fontString = (char *)((CCString*)strings->objectForKey("teachFont0501"))->m_sString.c_str();
// 	else if(CandyManager::currentLevel ==5 && currentStep == 1)
// 		fontString = (char *)((CCString*)strings->objectForKey("teachFont0502"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 5)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont06"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 16)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont16"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 31)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont31"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 46)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont46"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 61)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont61"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 76)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont76"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 91)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont91"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 136)
		fontString = (char *)((CCString*)strings->objectForKey("teachFont136"))->m_sString.c_str();
	else if(CandyManager::currentLevel == 181 || CandyManager::currentLevel == 9 )
		fontString = (char *)((CCString*)strings->objectForKey("teachFont181"))->m_sString.c_str();
	else
		fontString = (char *)((CCString*)strings->objectForKey("teachFontdefined"))->m_sString.c_str();
	
	CCLabelTTF* pFont = CCLabelTTF::create();
	//pFont->setFontName( "黑体" );
	pFont->setColor( ccc3(255,255,255) );
	pFont->setFontSize( 30 );
	pFont->setScale( 1.0f );
	pFont->setString( (const char*)fontString );
	pFont->setDimensions(CCSizeMake(250, 300));
	pFont->setHorizontalAlignment( kCCTextAlignmentCenter );
	pFont->setVerticalAlignment( kCCVerticalTextAlignmentCenter );
	//guideFont->addChild(pFont);
	guideSprite->addChild(pFont,2);
	CCRect contentRect = guideFont->getTextureRect();
	pFont->setPosition(ccp(300,380));

	guideFont->setCascadeOpacityEnabled(true);


	// 这里是目标哦
	if( ( 1 == CandyManager::currentLevel && 2 == currentStep ) /*|| ( 3 == CandyManager::currentLevel && 2 == currentStep )*/)
	{
		fontString = (char *)((CCString*)strings->objectForKey("teachthistarget"))->m_sString.c_str();

		CCLabelTTF* pTargetPrompt = CCLabelTTF::create();
		//pTargetPrompt->setFontName( "黑体" );
		pTargetPrompt->setColor( ccc3(255, 255, 255) );
		pTargetPrompt->setFontSize( 25 );
		pTargetPrompt->setString( (const char*)fontString );
		pTargetPrompt->setPosition( ccp(0, 50) );
		pTargetPrompt->setHorizontalAlignment( kCCTextAlignmentLeft );
		guideSprite->addChild(pTargetPrompt);

		CCPoint nTargetPoint = CandyManager::getInstance()->uiLayer->getTargetNumLabelPos();
		CCPoint nStepNumPoint = CandyManager::getInstance()->uiLayer->getStepNumLabelPos();

		float fixedScreenHeight = CandyShare::getFixedScreenHeight();

		if (( 3 == CandyManager::currentLevel && 2 == currentStep ) )
			pTargetPrompt->setPosition( ccpAdd(nStepNumPoint, ccp(0, fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?45:45) ) );
		else if ( ( 1 == CandyManager::currentLevel && 2 == currentStep ) )
			pTargetPrompt->setPosition( ccpAdd(nTargetPoint, ccp(0, fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?-45:45) ) );
			
	}

	return guideFont;
}

void CandyGuideLayer::setGuideFontPos(void)
{
	CCPoint pos = ccp(0,0);
	//guideFont->setFlipX( false );
	switch(CandyManager::currentLevel)
		{
			case 1:
				{
					if(currentStep == 2)
					{
						float fixedScreenHeight = CandyShare::getFixedScreenHeight();
						CCPoint nTargetPoint = CandyManager::getInstance()->uiLayer->getTargetNumLabelPos();


						pos = fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?(ccpAdd( nTargetPoint, ccp(-350, 0) )):(CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(7, 6)));
					}
					else
					{
						pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(3, 2));
					}
				}
				break;
// 			case 2:
// 				{
// 					pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(3, 4));
// 				}
// 				
// 				break;
				
			case 3:
				{
					if(currentStep == 0)
						{
							pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(2, 1));
						}
					else if(currentStep == 1)
						{
							pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(2, 1));
						}
					else if(currentStep == 2)
					{
						//pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4, 6));
						float fixedScreenHeight = CandyShare::getFixedScreenHeight();
						pos = fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?(CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(6, 7))):(CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(3, 6)));
					}
						
				}
				break;
				
			case 4:
				{
					pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(2, 1));
				}
				break;

// 			case 5:
// 				{
// 					if(currentStep == 0)
// 						{
// 							pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(1, 1));
// 						}
// 					else if(currentStep == 1)
// 						{
// 							pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(2, 3));
// 						}
// 						
// 				}
// 				break;
			case 9:
				{
					pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4, 0));
					guideFont->setAnchorPoint(ccp(0.5f,0.0f));
				}
				break;

			default:
					{
						CCPoint candyPos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,0));
						pos = ccp(candyPos.x, candyPos.y+36);
						guideFont->setAnchorPoint(ccp(0.5f,1.0f));
					}
				break;
				
		}
	
	guideFont->setPosition(pos);
}

CCSprite* CandyGuideLayer::createGuideSprite(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	CCLayerColor* grayLayer = CCLayerColor::create(ccc4(0,0,0,200),size.width, size.height);
	grayLayer->setPosition(ccp(0,0));
	
	 CCDrawNode* highLightNode = NULL;
	 
	 if (( 3 == CandyManager::currentLevel && 2 == currentStep ) || ( 4 == CandyManager::currentLevel && 1 == currentStep ))
		highLightNode = createStepAndTargetHighLightArea(true, false);
	 else if ( ( 1 == CandyManager::currentLevel && 2 == currentStep ) )
		 highLightNode = createStepAndTargetHighLightArea(false, true);
	 else
		highLightNode = createHighLightArea();	
	  	
	 ccBlendFunc blendFunc;
#if 0
	 blendFunc.src = GL_ONE;
	 blendFunc.dst = GL_ZERO;
	 maskSp->setBlendFunc(blendFunc);
#endif

	blendFunc.src = GL_ONE;//GL_ONE_MINUS_DST_ALPHA;
	blendFunc.dst = GL_ZERO;    // maskSprite不可见
	highLightNode->setBlendFunc(blendFunc);

	CCRenderTexture* texture = CCRenderTexture::create(size.width, size.height);
	texture->begin();
	grayLayer->visit();
	highLightNode->visit();
	texture->end();
	
	CCSprite* ret = CCSprite::createWithTexture(texture->getSprite()->getTexture());
	ret->setFlipY(true);
	 return ret;
}


CCDrawNode* CandyGuideLayer::createStepAndTargetHighLightArea(bool showStep, bool showTarget)
{
	int nStepNumH = 60 , nStepW = 170;
	int nTargetAreH = 380, nTargetAreW = 88;
	//int nTargetAreH = 325, nTargetAreW = 70;
	CCDrawNode *draw = CCDrawNode::create();

	if ( showTarget )
	{
		CCPoint nTargetPoint = CandyManager::getInstance()->uiLayer->getTargetNumLabelPos();
		float fixedScreenHeight = CandyShare::getFixedScreenHeight();

		float nOffset = fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?35:0;
		CCPoint TargetareaPoint[4] = 
		{
			ccp(nTargetPoint.x - nOffset - nTargetAreH/2 ,  nTargetPoint.y - nTargetAreW/2 ), 
			ccp(nTargetPoint.x - nOffset - nTargetAreH/2 ,  nTargetPoint.y + nTargetAreW/2 ), 
			ccp(nTargetPoint.x - nOffset + nTargetAreH/2 ,  nTargetPoint.y + nTargetAreW/2 ), 
			ccp(nTargetPoint.x - nOffset + nTargetAreH/2 ,  nTargetPoint.y - nTargetAreW/2 ), 
		};
		draw->drawPolygon(TargetareaPoint, 4, ccc4f(0,0,0,0), 0, ccc4f(0,0,0,0));
	}

	if ( showStep )
	{
		CCPoint nStepNumPoint = CandyManager::getInstance()->uiLayer->getStepNumLabelPos();
		CCPoint StepareaPoint[4] = 
		{
			ccp(nStepNumPoint.x - nStepW/2 ,  nStepNumPoint.y - nStepNumH/2 ),
			ccp(nStepNumPoint.x - nStepW/2 ,  nStepNumPoint.y + nStepNumH/2 ),
			ccp(nStepNumPoint.x + nStepW/2 ,  nStepNumPoint.y + nStepNumH/2 ),
			ccp(nStepNumPoint.x + nStepW/2 ,  nStepNumPoint.y - nStepNumH/2 ),
		};
		draw->drawPolygon(StepareaPoint, 4, ccc4f(0,0,0,0), 0, ccc4f(0,0,0,0));
	}

	return draw;
}

CCDrawNode* CandyGuideLayer::createHighLightArea(void)
{
	CCDrawNode *draw = CCDrawNode::create();

	for(int i=0; i<guideData.highLightNum[currentStep]; i++)
		{
			CandyIndex index = guideData.highLightArea[currentStep][i];
			CCPoint candyPos = CandyManager::getInstance()->shareMgr->getPosByIndex(guideData.highLightArea[currentStep][i]);
			CCPoint areaPoint[4] = 
				{
					ccp(candyPos.x - (CANDY_CELL_WIDTH>>1 ),  candyPos.y + (CANDY_CELL_HEIGHT>>1 )),
					ccp(candyPos.x + (CANDY_CELL_WIDTH>>1 ),  candyPos.y + (CANDY_CELL_HEIGHT>>1 )),
					ccp(candyPos.x + (CANDY_CELL_WIDTH>>1 ),  candyPos.y - (CANDY_CELL_HEIGHT>>1 )),
					ccp(candyPos.x - (CANDY_CELL_WIDTH>>1 ),  candyPos.y - (CANDY_CELL_HEIGHT>>1 )),
				};
			draw->drawPolygon(areaPoint, 4, ccc4f(0,0,0,0), 0, ccc4f(0,0,0,0));
		}
		
	return draw;
}

void CandyGuideLayer::createGuideExample5(void)
{
	CCSprite *exampleSprite = (CCSprite *)guideSprite->getChildByTag(GUIDE_EXAMPLE_TAG);
	if(exampleSprite)
		return;
		
	exampleSprite = CCSprite::create();
	exampleSprite->setCascadeOpacityEnabled(true);
	guideSprite->addChild(exampleSprite,0,GUIDE_EXAMPLE_TAG);
	
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
		
	CCSprite* jelly1 = CCSprite::createWithSpriteFrameName( "jelly1.png");
	CCSprite* jelly2 = CCSprite::createWithSpriteFrameName( "jelly1.png");
	CCSprite* jelly3 = CCSprite::createWithSpriteFrameName( "jelly1.png");
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyGreenNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyGreenNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyGreenNormal.png");
	CCSprite*candy4 = CCSprite::createWithSpriteFrameName( "CandyBlueNormal.png");

	jelly1->setScale(scale);
	jelly2->setScale(scale);
	jelly3->setScale(scale);
	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	candy4->setScale(scale);
	
	exampleSprite->addChild(jelly1,3);
	exampleSprite->addChild(jelly2,3);
	exampleSprite->addChild(jelly3,3);
	exampleSprite->addChild(candy1,3);
	exampleSprite->addChild(candy2,3);
	exampleSprite->addChild(candy3,3);
	exampleSprite->addChild(candy4,3);

	jelly1->setPosition(ccp(pos.x - offset, pos.y));
	jelly2->setPosition(ccp(pos.x, pos.y));
	jelly3->setPosition(ccp(pos.x + offset, pos.y));
	candy1->setPosition(ccp(pos.x- offset, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y));
	candy3->setPosition(ccp(pos.x+ offset, pos.y+ offset));
	candy4->setPosition(ccp(pos.x+ offset, pos.y));

	candy3->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ offset, pos.y)),
										NULL));
	candy4->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ offset, pos.y+ offset)),
										NULL));

	CCAction *delayFade = CCSequence::create(CCDelayTime::create(1.0f),
										CCFadeOut::create(0.5f),
										NULL);
	
	jelly1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	jelly2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	jelly3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));


	exampleSprite->runAction(CCSequence::create(CCDelayTime::create(1.5f),
											CCFadeOut::create(0.5f),
											CCCallFuncN::create(this, callfuncN_selector(CandyGuideLayer::exampleCompleteCallBack)),
											NULL));
}



void CandyGuideLayer::createGuideExample16(void)
{
	CCSprite *exampleSprite = (CCSprite *)guideSprite->getChildByTag(GUIDE_EXAMPLE_TAG);
	if(exampleSprite)
		return;

	exampleSprite = CCSprite::create();
	exampleSprite->setCascadeOpacityEnabled(true);
	guideSprite->addChild(exampleSprite,0,GUIDE_EXAMPLE_TAG);
	
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,3));
	
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite* cherry = CCSprite::createWithSpriteFrameName( "chesnut0.png");
	CCSprite* drop = CCSprite::createWithSpriteFrameName( "dropIngredientFlag.png");

	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	cherry->setScale(scale);
	drop->setScale(scale);

	exampleSprite->addChild(candy1,3);
	exampleSprite->addChild(candy2,3);
	exampleSprite->addChild(candy3,3);
	exampleSprite->addChild(cherry,3);
	exampleSprite->addChild(drop,3);

	
	candy1->setPosition(ccp(pos.x, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y - offset));
	candy3->setPosition(ccp(pos.x, pos.y- 3*offset));
	cherry->setPosition(ccp(pos.x, pos.y- 2*offset));
	drop->setPosition(ccp(pos.x, pos.y- 4*offset));

	candy3->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x, pos.y- 2*offset)),
										NULL));
	cherry->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x, pos.y- 3*offset)),
										NULL));

	CCAction *delayFade = CCSequence::create(CCDelayTime::create(1.0f),
										CCFadeOut::create(0.5f),
										NULL);
	
	candy1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	cherry->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));


	exampleSprite->runAction(CCSequence::create(CCDelayTime::create(1.5f),
											CCFadeOut::create(0.5f),
											CCCallFuncN::create(this, callfuncN_selector(CandyGuideLayer::exampleCompleteCallBack)),
											NULL));

}

void CandyGuideLayer::createGuideExample31(void)
{
	CCSprite *exampleSprite = (CCSprite *)guideSprite->getChildByTag(GUIDE_EXAMPLE_TAG);
	if(exampleSprite)
		return;

	exampleSprite = CCSprite::create();
	exampleSprite->setCascadeOpacityEnabled(true);
	guideSprite->addChild(exampleSprite,0,GUIDE_EXAMPLE_TAG);
	
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
					
	CCSprite* cream1 = CCSprite::createWithSpriteFrameName( "cream1.png");
	CCSprite* cream2 = CCSprite::createWithSpriteFrameName( "cream1.png");
	CCSprite* cream3 = CCSprite::createWithSpriteFrameName( "cream1.png");
	CCSprite* cream4 = CCSprite::createWithSpriteFrameName( "cream1.png");
	
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy4 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");

	cream1->setScale(scale);
	cream2->setScale(scale);
	cream3->setScale(scale);
	cream4->setScale(scale);
	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	candy4->setScale(scale);

	exampleSprite->addChild(cream1,3);
	exampleSprite->addChild(cream2,3);
	exampleSprite->addChild(cream3,3);
	exampleSprite->addChild(cream4,3);
	exampleSprite->addChild(candy1,3);
	exampleSprite->addChild(candy2,3);
	exampleSprite->addChild(candy3,3);
	exampleSprite->addChild(candy4,3);

	cream1->setPosition(ccp(pos.x-2*offset, pos.y));
	cream2->setPosition(ccp(pos.x-offset, pos.y+offset));
	cream3->setPosition(ccp(pos.x, pos.y+offset));
	cream4->setPosition(ccp(pos.x+offset, pos.y+offset));
	candy1->setPosition(ccp(pos.x- offset, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y));
	candy3->setPosition(ccp(pos.x+ offset, pos.y));
	candy4->setPosition(ccp(pos.x+ 2*offset, pos.y));

	candy3->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ 2*offset, pos.y)),
										NULL));
	candy4->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ offset, pos.y)),
										NULL));

	CCAction *delayFade = CCSequence::create(CCDelayTime::create(1.0f),
										CCFadeOut::create(0.5f),
										NULL);

	cream1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	cream2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	cream3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	cream4->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	//candy3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy4->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));


	exampleSprite->runAction(CCSequence::create(CCDelayTime::create(1.5f),
											CCFadeOut::create(0.5f),
											CCCallFuncN::create(this, callfuncN_selector(CandyGuideLayer::exampleCompleteCallBack)),
											NULL));
}
void CandyGuideLayer::createGuideExample9(void)
{	
	CCSprite *exampleSprite = (CCSprite *)guideSprite->getChildByTag(GUIDE_EXAMPLE_TAG);
	if(exampleSprite)
		return;

	exampleSprite = CCSprite::create();
	exampleSprite->setCascadeOpacityEnabled(true);
	guideSprite->addChild(exampleSprite,0,GUIDE_EXAMPLE_TAG);

	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;

	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	pos.x = pos.x - offset*0.5f;
	pos.y = pos.y + offset*0.5f;

	CCSprite* pBottombg = CCSprite::createWithSpriteFrameName("NewUi2/bottom2.png");
	pBottombg->setPosition(ccp(pos.x- offset + 170, pos.y + 150));
	exampleSprite->addChild( pBottombg );

	CCSprite* pTargetLabel = CCSprite::createWithSpriteFrameName( "TargetLabel.png");
	pTargetLabel->setPosition( ccp(47+10,40));
	pBottombg->addChild( pTargetLabel );

	CCSprite* pBottomcandy = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png"); 
	pBottomcandy->setPosition( ccp(114+10,40));
	pBottombg->addChild( pBottomcandy );

	CCLabelAtlas* pTargetNumLabe = CCLabelAtlas::create("4" , "Image/CandyGame/CandyGameUi/NumLabel/TargetNumLabe.png", 24, 28, '0');
	pTargetNumLabe->setPosition( ccp(180+10,30) );
	pBottombg->addChild( pTargetNumLabe );

	CCSprite* pTick = CCSprite::createWithSpriteFrameName( "Others/Tick.png"); 
	pTick->setPosition( ccp(180+10,40));
	pTick->setOpacity( 0 );
	pBottombg->addChild( pTick );

	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyBlueNormal.png");
	CCSprite*candy4 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");

	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	candy4->setScale(scale);

	candy1->setPosition(ccp(pos.x- offset, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y));
	candy3->setPosition(ccp(pos.x+ offset, pos.y));
	candy4->setPosition(ccp(pos.x+ 2*offset, pos.y));

	exampleSprite->addChild(candy1,3);
	exampleSprite->addChild(candy2,3);
	exampleSprite->addChild(candy3,3);
	exampleSprite->addChild(candy4,3);

	candy3->runAction(CCSequence::create(CCDelayTime::create(0.5f),
		CCMoveTo::create(0.5f,ccp(pos.x+ 2*offset, pos.y)),
		NULL));
	candy4->runAction(CCSequence::create(CCDelayTime::create(0.5f),
		CCMoveTo::create(0.5f,ccp(pos.x+ offset, pos.y)),
		NULL));

	pTargetNumLabe->runAction(CCSequence::create(CCDelayTime::create(0.5f),
		CCDelayTime::create(1.1f),
		CCFadeOut::create(0.5),
		NULL));

	pTick->runAction(CCSequence::create(CCDelayTime::create(0.5f),
		CCDelayTime::create(1.6f),
		CCFadeIn::create(0.5),
		NULL));

	CCAction *delayFade1 = CCSequence::create(CCDelayTime::create(1.0f),
		CCFadeOut::create(0.5f),
		NULL);

	CCAction *delayFade2 = CCSequence::create(CCDelayTime::create(4.0f),
		CCFadeOut::create(0.5f),
		NULL);

	candy1->runAction((CCFiniteTimeAction*)(delayFade1->copy()->autorelease()));
	candy2->runAction((CCFiniteTimeAction*)(delayFade1->copy()->autorelease()));
	candy3->runAction((CCFiniteTimeAction*)(delayFade1->copy()->autorelease()));
	candy4->runAction((CCFiniteTimeAction*)(delayFade1->copy()->autorelease()));
	pBottomcandy->runAction((CCFiniteTimeAction*)(delayFade2->copy()->autorelease()));
	pTargetLabel->runAction((CCFiniteTimeAction*)(delayFade2->copy()->autorelease()));
	pTick->runAction((CCFiniteTimeAction*)(delayFade2->copy()->autorelease()));

	exampleSprite->runAction(CCSequence::create(CCDelayTime::create(4.0f),
		CCFadeOut::create(0.5f),
		CCCallFuncN::create(this, callfuncN_selector(CandyGuideLayer::exampleCompleteCallBack)),
		NULL));

	createISeeButton();
}
void CandyGuideLayer::createGuideExample46(void)
{
	CCSprite *exampleSprite = (CCSprite *)guideSprite->getChildByTag(GUIDE_EXAMPLE_TAG);
	if(exampleSprite)
		return;

	exampleSprite = CCSprite::create();
	exampleSprite->setCascadeOpacityEnabled(true);
	guideSprite->addChild(exampleSprite,0,GUIDE_EXAMPLE_TAG);
	
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	pos.x = pos.x - offset*0.5f;
	pos.y = pos.y + offset*0.5f;
	
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyRedNormal.png");
	CCSprite*candy4 = CCSprite::createWithSpriteFrameName( "CandyYellowNormal.png");
	CCSprite* lock = CCSprite::createWithSpriteFrameName( "lock.png");
	
	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	candy4->setScale(scale);
	lock->setScale(scale);

	exampleSprite->addChild(candy1,3);
	exampleSprite->addChild(candy2,3);
	exampleSprite->addChild(candy3,3);
	exampleSprite->addChild(candy4,3);
	exampleSprite->addChild(lock,3);

	candy1->setPosition(ccp(pos.x- offset, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y));
	candy3->setPosition(ccp(pos.x+ offset, pos.y));
	candy4->setPosition(ccp(pos.x+ 2*offset, pos.y));
	lock->setPosition(ccp(pos.x, pos.y));

	candy3->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ 2*offset, pos.y)),
										NULL));
	candy4->runAction(CCSequence::create(CCDelayTime::create(0.5f),
										CCMoveTo::create(0.5f,ccp(pos.x+ offset, pos.y)),
										NULL));

	CCAction *delayFade = CCSequence::create(CCDelayTime::create(1.0f),
										CCFadeOut::create(0.5f),
										NULL);

	candy1->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	//candy2->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	//candy3->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	candy4->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));
	lock->runAction((CCFiniteTimeAction*)(delayFade->copy()->autorelease()));


	exampleSprite->runAction(CCSequence::create(CCDelayTime::create(1.5f),
											CCFadeOut::create(0.5f),
											CCCallFuncN::create(this, callfuncN_selector(CandyGuideLayer::exampleCompleteCallBack)),
											NULL));
}

void CandyGuideLayer::createGuideExample61(void)
{
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	pos.x = pos.x - offset*0.5f;
	pos.y = pos.y + offset*0.5f;
	
	CCSprite* jelly1 = CCSprite::createWithSpriteFrameName( "jelly1.png");
	CCSprite* jelly2 = CCSprite::createWithSpriteFrameName( "jelly2.png");
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyPurpleNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyPurpleNormal.png");
	CCSprite*candy3 = CCSprite::createWithSpriteFrameName( "CandyOrangeNormal.png");
	CCSprite*candy4 = CCSprite::createWithSpriteFrameName( "CandyPurpleNormal.png");

	jelly1->setScale(scale);
	jelly2->setScale(scale);
	candy1->setScale(scale);
	candy2->setScale(scale);
	candy3->setScale(scale);
	candy4->setScale(scale);

	guideSprite->addChild(jelly1,3);
	guideSprite->addChild(jelly2,3);
	guideSprite->addChild(candy1,3);
	guideSprite->addChild(candy2,3);
	guideSprite->addChild(candy3,3);
	guideSprite->addChild(candy4,3);

	jelly1->setPosition(ccp(pos.x , pos.y));
	jelly2->setPosition(ccp(pos.x+offset, pos.y));
	candy1->setPosition(ccp(pos.x- offset, pos.y));
	candy2->setPosition(ccp(pos.x, pos.y));
	candy3->setPosition(ccp(pos.x+ offset, pos.y));
	candy4->setPosition(ccp(pos.x+ 2*offset, pos.y));
	createISeeButton();
}

void CandyGuideLayer::createGuideExample76(void)
{
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	pos.y = pos.y + offset*0.5f;
	
	CCSprite* chocolate1 = CCSprite::createWithSpriteFrameName( "chocolate7.png");
	CCSprite* chocolate2 = CCSprite::createWithSpriteFrameName( "chocolate7.png");
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyPurpleNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyOrangeNormal.png");

	chocolate1->setScale(scale);
	chocolate2->setScale(scale);
	candy1->setScale(scale);
	candy2->setScale(scale);
	
	guideSprite->addChild(candy1,3);
	guideSprite->addChild(candy2,3);
	guideSprite->addChild(chocolate1,3);
	guideSprite->addChild(chocolate2,3);


	chocolate2->setScale(0.8f);
	chocolate2->setRotation(45.0f);
	
	candy1->setPosition(ccp(pos.x, pos.y));
	candy2->setPosition(ccp(pos.x + offset, pos.y));
	chocolate1->setPosition(ccp(pos.x- offset, pos.y));
	chocolate2->setPosition(ccp(pos.x, pos.y));
	createISeeButton();
}

void CandyGuideLayer::createGuideExample91(void)
{
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	
	CCSprite* PortalEntrance = CCSprite::createWithSpriteFrameName( "PortalEntrance1.png");
	CCSprite* PortalExit = CCSprite::createWithSpriteFrameName( "PortalExit1.png");
	CCSprite*candy1 = CCSprite::createWithSpriteFrameName( "CandyBlueNormal.png");
	CCSprite*candy2 = CCSprite::createWithSpriteFrameName( "CandyBlueNormal.png");

	PortalEntrance->setScale(scale*1.3f);
	PortalExit->setScale(scale*1.3f);
	candy1->setScale(scale);
	candy2->setScale(scale);
	
	guideSprite->addChild(candy1,3);
	guideSprite->addChild(candy2,3);
	guideSprite->addChild(PortalEntrance,3);
	guideSprite->addChild(PortalExit,3);

	
	candy1->setPosition(ccp(pos.x-offset, pos.y-0.5*offset));
	candy2->setPosition(ccp(pos.x + offset, pos.y));
	PortalEntrance->setPosition(ccp(pos.x-offset, pos.y-offset));
	PortalExit->setPosition(ccp(pos.x+ offset, pos.y+0.5*offset));
	createISeeButton();
	
}

void CandyGuideLayer::createGuideExample136(void)
{
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	
	CandyCell* candy = CandyCell::create(cIndex(4,5), CANDY_COLOR_RED, CANDY_SPECIAL_EXPLOSION);
	candy->setScale(scale);
	
	guideSprite->addChild(candy,3);

	
	candy->setPosition(pos);
	CandyManager::getInstance()->explosionMgr->setCandyExplosionTime(candy,15);
	createISeeButton();
}

void CandyGuideLayer::createGuideExample181(void)
{
	const float scale = 1.3f;
	const float offset = scale * CANDY_CELL_WIDTH;
	
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(4,4));
	pos.y = pos.y + offset*0.5f;
	
	CCSprite* targetGuide = CCSprite::create("Image/CandyGame/Teach/targetTeach.png");
	guideSprite->addChild(targetGuide,3);
	targetGuide->setPosition(pos);
	createISeeButton();
}

void CandyGuideLayer::displayGuideFingerEffect(CCNode* sender)
{
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_GUIDE_FINGER, ccp(12,120), sender);
}

void CandyGuideLayer::exampleCompleteCallBack(CCNode* sender)
{
	sender->removeFromParent();
	updateGuideExample();
	createISeeButton();
}

void CandyGuideLayer::createISeeButton(void)
{
	if(guideSprite->getChildByTag(SKIP_EXAMPLE_TAG))
		return;

	
	CCMenuItemImage *skipItem = CCMenuItemImage::create(
                                        ISEE_BUTTON_NORMAL_IMG,
                                       	ISEE_BUTTON_SELECT_IMG,
                                        this,
                                        menu_selector(CandyGuideLayer::ISeeButtonCallback));

	UIButton* pSkipTtem =  UIButton::create();
	pSkipTtem->setTextures(ISEE_BUTTON_NORMAL_IMG, ISEE_BUTTON_SELECT_IMG, ISEE_BUTTON_SELECT_IMG);
	pSkipTtem->setTouchEnabled( true );
	pSkipTtem->addReleaseEvent(this, coco_releaseselector(CandyGuideLayer::ISeeButtonCallback));
	pSkipTtem->isEffects( true );

	CCPoint pos = ccp(360,340);
	switch(CandyManager::currentLevel)
	{

	case 1:
	case 3:
		{
			if ( 2 == currentStep )
				pos =ccp(360,640);
		}
		break;
			case 6:
				pos = ccp(360,340);
				break;
			case 16:
				pos = ccp(590,220);
				break;
			case 31:
				pos = ccp(360,340);
				break;
// 			case 46:
// 				break;
		}
	
	skipItem->setPosition(pos);

	pSkipTtem->setPosition(pos);
	UILayer* pLayer = UILayer::create();
	guideSprite->addChild( pLayer );
	pLayer->addWidget( pSkipTtem );
	

	CCMenu* pMenu = CCMenu::create(skipItem, NULL);
	pMenu->setPosition(CCPointZero);
	//guideSprite->addChild(pMenu,0,SKIP_EXAMPLE_TAG);	
}

void CandyGuideLayer::ISeeButtonCallback(CCObject* pSender)
{
#ifdef CANDY_STATISITICAL_DATA
	/*if(CandyManager::currentLevel == 1 && currentStep == 2)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_61 );
	else if(CandyManager::currentLevel == 3 && currentStep == 2)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_87 );*/
#endif
	setGuiding(false);

}

void CandyGuideLayer::createSkipButton(void)
{
	if(guideSprite->getChildByTag(SKIP_EXAMPLE_TAG))
		return;


	CCMenuItemImage *skipItem = CCMenuItemImage::create(
		SKIP_BUTTON_NORMAL_IMG,
		SKIP_BUTTON_SELECT_IMG,
		this,
		menu_selector(CandyGuideLayer::SkipButtonCallback));

	CCPoint pos = ccp(360,340);
	skipItem->setPosition(pos);

	CCMenu* pMenu = CCMenu::create(skipItem, NULL);
	pMenu->setPosition(CCPointZero);
	pMenu->setScale(1.20f );
	guideSprite->addChild(pMenu,0,SKIP_EXAMPLE_TAG);

}

void CandyGuideLayer::SkipButtonCallback(CCObject* pSender)
{
#ifdef CANDY_STATISITICAL_DATA
	/*if(CandyManager::currentLevel == 1 && currentStep == 0)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_59 );
	else if(CandyManager::currentLevel == 1 && currentStep == 1)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_60 );

	else if(CandyManager::currentLevel == 3 && currentStep == 0)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_85 );
	else if(CandyManager::currentLevel == 3 && currentStep == 1)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_86 );*/
#endif
	setGuiding(false);
	//finishCurrentStep();
}

void CandyGuideLayer::setTeacherPos( void )
{

}

void CandyGuideLayer::StartAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string nid = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if(nid.compare("xszy1") == 0)
		{
			guideTaech->getAnimation()->play("xszy2");
		}
	}
}
