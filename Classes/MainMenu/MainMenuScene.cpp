#include "MainMenuScene.h"
#include "../Loading/LoadingScene.h"
#include "../MainMap/MainMapScene.h"
#include "../PlayGame/PlayGameScene.h"

CCScene* MainMenu::scene(void)
{
	CCScene * scene = NULL;
	do
		{
			scene = CCScene::create();
			CC_BREAK_IF(! scene);

			CCLayer *layer;
			layer = MainMenu::create();
			CC_BREAK_IF(! layer);
			scene->addChild(layer);
		} while (0);

	return scene;
}

bool MainMenu::init(void)
{
	if ( !CCLayer::init() )
		{
			return false;
		}
	setKeypadEnabled(true);
	CCLayerColor *bgColor = CCLayerColor::create(ccc4(255,255,255,255));
	addChild(bgColor);
	MainMap::playMapBgm();
	UILayer *uiLayer = UILayer::create();
	addChild(uiLayer);

	Layout *layout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("CandyLogOn/CandyLogOn.json"));
	uiLayer->addWidget((layout));

	UIButton *starGameButton= dynamic_cast<UIButton*>(layout->getChildByName("PlayButton"));
	starGameButton->setTouchEnable(true);
	starGameButton->addReleaseEvent(this, coco_releaseselector(MainMenu::playButtonCallBack));

	CCActionInterval*  actionScale1 = CCScaleTo::create(0.5f, 1.2f, 1.0f);
	CCActionInterval*  actionScale2 = CCScaleTo::create(0.2f, 1.2f, 1.1f);
	CCActionInterval*  actionScale3 = CCScaleTo::create(0.3f, 1.0f, 1.1f);

	starGameButton->runAction( CCRepeatForever::create(
		CCSequence::create(
		actionScale1,
		actionScale2,
		actionScale3,
		actionScale2,
		NULL)));
	
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;
	float offsetY = 0;//(fixedScreenHeight - 960.0f)*0.5;
	layout->setPosition(ccp(0,offsetY));
#if 1
	UIImageView *userNameImg = dynamic_cast<UIImageView*>(layout->getChildByName("UserName"));
	CCPoint userNameImglPos = userNameImg->getPosition();

	UIImageView *passWordImg = dynamic_cast<UIImageView*>(layout->getChildByName("PassWord"));
	CCPoint passWordImgPos = passWordImg->getPosition();
			

	CCSize editBoxSize = CCSizeMake(280, 50);
	CCEditBox* m_pEditName;
	m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("green_edit.png"));
	m_pEditName->setAnchorPoint(ccp(0.0,0.5));
	m_pEditName->setPosition(ccp(userNameImglPos.x +270, userNameImglPos.y+offsetY +633));
	m_pEditName->setFontSize(20);
	m_pEditName->setFontColor(ccBLACK);
	m_pEditName->setDelegate(this);
	m_pEditName->setText("WeMeCandy");
	addChild(m_pEditName);

	CCEditBox* m_pEditPassword;
	m_pEditPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("green_edit.png"));
	m_pEditPassword->setAnchorPoint(ccp(0.0,0.5));
	m_pEditPassword->setPosition(ccp(passWordImgPos.x +270, passWordImgPos.y+offsetY+635));
	m_pEditPassword->setFontSize(20);
	m_pEditPassword->setFontColor(ccBLACK);
	m_pEditPassword->setDelegate(this);
	m_pEditPassword->setText("SimpleHappyShare");
	addChild(m_pEditPassword);
#endif	
	//m_pEditName->setPlaceHolder("");
	//m_pEditName->setPlaceholderFontColor(ccWHITE);
	//m_pEditName->setMaxLength(8);
	//m_pEditName->setReturnType(kKeyboardReturnTypeDone);

	CCLog("Cocos ---> MainMenu scene");
	return true;
}

void MainMenu::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void MainMenu::editBoxEditingDidBegin(CCEditBox* editBox)
{
	
}

 void MainMenu::editBoxEditingDidEnd(CCEditBox* editBox)
{

}

void MainMenu::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
	
}


 void MainMenu::editBoxReturn(CCEditBox* editBox)
{

}

void MainMenu::playButtonCallBack(CCObject *pSender)
{
	Loading::replaceScence(CANDY_SCENCE_MAIN_MAP);
}
#if 0	
void MainMenu::onEnter(void)
{
	CCLayer::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	
}

void MainMenu::onExit(void)
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool MainMenu::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}

void MainMenu::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MainMenu::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}
#endif
