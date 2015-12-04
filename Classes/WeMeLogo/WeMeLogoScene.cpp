#include "WeMeLogoScene.h"
#include "../MainMenu/MainMenuScene.h"
#include "../Loading/LoadingScene.h"
CCScene* WeMeLogo::scene(void)
{
	CCScene * scene = NULL;
	do
		{
			scene = CCScene::create();
			CC_BREAK_IF(! scene);

			CCLayer *layer;
			layer = WeMeLogo::create();
			CC_BREAK_IF(! layer);
			scene->addChild(layer);
		} while (0);

	return scene;
}

bool WeMeLogo::init(void)
{
	if ( !CCLayer::init() )
		{
			return false;
		}
	
	CCLayerColor *bgColor = CCLayerColor::create(ccc4(255,255,255,255));
	addChild(bgColor);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *logo = CCSprite::create("WeMeLogo.png");
	logo->setScale(0.7f);
	logo->setPosition( ccp(size.width / 2, size.height/2) );
	this->addChild(logo);
	
	scheduleOnce(schedule_selector(WeMeLogo::goMainMenu), 2);
	
	
	return true;
}

void WeMeLogo::goMainMenu(float dt)
{
	//CCScene *pScene = MainMenu::scene();
	CCScene *pScene = Loading::scene(CANDY_SCENCE_MAIN_MAP);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

