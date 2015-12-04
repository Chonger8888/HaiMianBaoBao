#include "MMLog.h"
#include "LoadingScene.h"


CCScene* MMlog::LogScene()
{
	CCScene* scene = CCScene::create();

	CCLayer* layer = MMlog::create();
	scene->addChild(layer);

	return scene;
}


void MMlog::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite* mmlog = CCSprite::create("Image/Loading/mmlog.jpg");
	mmlog->setPosition(ccp(s.width*0.5,s.height*0.5));
	addChild(mmlog,1000);

	CCActionInterval* delay = CCDelayTime::create(1.5);
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(MMlog::GoLoadingScene));

	mmlog->runAction(CCSequence::create(delay,func ,NULL));
}

void MMlog::GoLoadingScene()
{
	CCScene* loadScene = Loading::scene(CANDY_SCENCE_DOWNLOAD);
	CCDirector::sharedDirector()->replaceScene(loadScene);
}

