#include "UILogin.h"
#include "SimpleAudioEngine.h"
#include "CommonMacro.h"
#include "../CppCallJava/CppCallJava.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MainMap/MainMapScene.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../Loading/LoadingScene.h"
#include "../PlayGame/CandyParticle.h"
#include "../CommonData/CommonData.h"

#define CANDY_LOGIN_LAYOUT_FILE "Image/LoginUi/LoginUi_1.ExportJson"

#define CANDY_LOGIN_IMG_LOGINBG		"Image/LoginUi/login_play_bg.jpg"
#define CANDY_LOGIN_BTN_PLAYGAMEN	"Image/LoginUi/login_guest_play_btn_normal.png"
#define CANDY_LOGIN_BTN_PLAYGAMEP	"Image/LoginUi/login_guest_play_btn_pressed.png"
#define CANDY_LOGIN_BTN_AUTHORN		"Image/LoginUi/login_play_authorN.png"
#define CANDY_LOGIN_BTN_AUTHORP		"Image/LoginUi/login_play_authorP.png"

using namespace CocosDenshion;
CCScene* UILogin::scene(void)
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		CCLayer *layer;
		layer = UILogin::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);

	} while (0);

	return scene;
}

UILogin::~UILogin()
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");
	plogin->stopAllActions();
	layer->removeWidget( plogin );

	CCTextureCache::sharedTextureCache()->removeTextureForKey(CANDY_IMG_LOGIN_LOGINUI1);  
	CCTextureCache::sharedTextureCache()->removeTextureForKey(CANDY_IMG_LOGIN_LOGINUI2); 

// 	if ( SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() )
// 		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
#endif
}
  
bool UILogin::init(void)
{
	if(!CCLayer::init())
	{
		return false;
	}

	CommonData::getSoundEffectStateEx();
	CommonData::getBackgroundStateEx();

	UILayer* layer = UILayer::create();
	layer->setTag(1000);
	this->addChild( layer);

	CCSize nSceneSize = CCDirector::sharedDirector()->getWinSizeInPixels();
	UIImageView* pLoginBg = UIImageView::create();
	pLoginBg->setTexture( CANDY_LOGIN_IMG_LOGINBG );
	pLoginBg->setAnchorPoint( ccp( 0.0f, 0.0f ));
	pLoginBg->setVisible( true );
	pLoginBg->setScaleX( nSceneSize.width / TARGET_SCREEN_WIDTH );
	pLoginBg->setScaleY( nSceneSize.height / TARGET_SCREEN_HEIGHT );
	pLoginBg->setPosition(ccp(0, 0));
	layer->addWidget( pLoginBg );


#ifdef CANDY_STATISITICAL_DATA
	//新用户记录点
	if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
	{
		AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1002);
	}
#endif

	if ( CommonData::getBackgroundState() )
	{
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Music/MapBgm.mp3");
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/MapBgm.mp3", true);
	}

#ifdef CANDY_STATISITICAL_DATA
	//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4004);
#endif
	
	//CandyParticle::initCandyParicleForXml();
	//CommonData::getStorePath();

	//获取转盘概率
	MsgMgr::sendRoulettePercentReq();

	PlayLoginAction( layer );


	return true;
}

void UILogin::ButtonCallBack(CCObject *pSender)
{
	UIButton* pBtn = (UIButton*) pSender;
	int tag = pBtn->getTag();

	if ( LOGINUI_BTN_TAG_PLAYGAME == tag )
	{
#ifdef CANDY_STATISITICAL_DATA
		//新用户记录点
		if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
		{
			AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1003);
		}
#endif

		Loading::scenceType = CANDY_SCENCE_MAIN_MAP;
		CCScene *pScene = NULL;
		pScene =MainMap::scene( false );
		CCTransitionCrossFade* reScene = CCTransitionCrossFade::create(0.2f, pScene);
		CCDirector::sharedDirector()->replaceScene( reScene );
	}
	else if ( LOGINUI_BTN_TAG_AUTHORP == tag )
	{
		UILayer* layer = (UILayer*)this->getChildByTag(1000);
		Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");

		if ( plogin )
		{
			UIImageView* ContentBg = dynamic_cast<UIImageView*>(plogin->getChildByName("ContentBg"));
			UIButton* pBtnPlay = dynamic_cast<UIButton*>(plogin->getChildByName("BtnPlay"));
			UIButton* pBtnAuthorn = dynamic_cast<UIButton*>(plogin->getChildByName("BtnAuthorn"));
			ContentBg->setVisible( false );
			pBtnPlay->setVisible( false );
			pBtnAuthorn->setVisible( false );
			pBtnAuthorn->setTouchEnabled( false );

			CCSize nSceneSize = CCDirector::sharedDirector()->getWinSize();
			UIPanel* pProducer = (UIPanel*)plogin->getChildByName("PanelProducer");
			UIPanel* pShowProducer = (UIPanel*)plogin->getChildByName("ProducerTable");

			pProducer->setVisible( true );
			pProducer->setTouchEnable( true );

			pShowProducer->setPosition( ccp(0, -nSceneSize.height) );
			pShowProducer->runAction( CCSequence::create(
				CCMoveTo::create(10.0f, ccp(0, nSceneSize.height - 756)),
				CCDelayTime::create( 1.0f ),
				CCCallFunc::create(this, callfunc_selector(UILogin::AuthornMoveCallback)),
				NULL));
		}
	}

}


void UILogin::PlayLoginAction( UILayer* layer )
{
	return;
	CCSize nSceneSize = CCDirector::sharedDirector()->getWinSize();
	Layout* plogin =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile( CANDY_LOGIN_LAYOUT_FILE ));
	plogin->setName( "loginimg" );
	layer->addWidget( plogin );

	UIImageView* pContentBg = dynamic_cast<UIImageView*>(plogin->getChildByName("ContentBg"));;
	pContentBg->setScale( (nSceneSize.height/1280.f > nSceneSize.width/720.f)?nSceneSize.width/720.f:nSceneSize.height/1280.f );
	pContentBg->setPosition( ccp(nSceneSize.width/2, nSceneSize.height * 0.65f) );

	UIImageView* pImage1 = dynamic_cast<UIImageView*>(plogin->getChildByName("loginfigure1"));
	UIImageView* pImage2 = dynamic_cast<UIImageView*>(plogin->getChildByName("loginfigure2"));
	UIImageView* pImage3 = dynamic_cast<UIImageView*>(plogin->getChildByName("loginfigure4"));
	UIImageView* pImage4 = dynamic_cast<UIImageView*>(plogin->getChildByName("loginfigure3"));
	UIImageView* pImage5 = dynamic_cast<UIImageView*>(plogin->getChildByName("loginfigure5"));
	UIImageView* ploginbgaction = dynamic_cast<UIImageView*>(plogin->getChildByName("loginbgaction"));
	UIImageView* plogintitle = dynamic_cast<UIImageView*>(plogin->getChildByName("logintitle"));


// 	pos = pParticle3->getParent()->convertToWorldSpace(pParticle3->getPosition());
// 	CandyParticle::displayCandyParticle(CANDY_LOGIN_FLASH_EFFECT, pos, this);

//	CCPoint pos = plogin->convertToWorldSpace(pParticle1->getPosition());
// 	CCNode* node = CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(0, 0));
// 	node->setZOrder( 1000 );
// 	pImage1->getRenderer()->addChild( node );
// 	pos = plogin->convertToWorldSpace(pParticle2->getPosition());
// 	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(pos.x, pos.y), this);
// 	pos = plogin->convertToWorldSpace(pParticle3->getPosition());
// 	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(pos.x, pos.y), this);

	pImage1->setScale( 0.1f );
	pImage2->setScale( 0.1f );
	pImage3->setScale( 0.1f );
	pImage4->setScale( 0.1f );
	pImage5->setScale( 0.1f );
	ploginbgaction->setScale( 0.1f );
	plogintitle->setScale( 0.01f );
	plogintitle->setPosition(ccp(0,plogintitle->getPosition().y));
	pImage1->runAction( CCSequence::create(
		getSpriteAction(),
		NULL));

	pImage2->runAction( CCSequence::create(
		CCDelayTime::create( 0.33f ),
		getSpriteAction(),
		NULL));

	pImage3->runAction( CCSequence::create(
		CCDelayTime::create( 0.33f ),
		getSpriteAction(),
		NULL));


	CCActionInterval*  actionScale = CCScaleTo::create(0.13f, 1.0f);
	CCActionInterval * fadeout = CCFadeIn::create(0.13f); 
	CCFiniteTimeAction * reveseseq = CCSpawn::create(actionScale,fadeout,NULL);

	ploginbgaction->runAction( CCSequence::create(
		CCDelayTime::create( 0.4f ),
		reveseseq,
		NULL));


	pImage4->runAction( CCSequence::create(
		CCDelayTime::create( 0.5f ),
		getSpriteAction(),
		NULL));

	pImage5->runAction( CCSequence::create(
		CCDelayTime::create( 0.5f ),
		getSpriteAction(),
		NULL));


	actionScale = CCScaleTo::create(0.08f, 0.94f);
	fadeout = CCFadeIn::create(0.08f); 
	reveseseq = CCSpawn::create(actionScale,fadeout,NULL);

	plogintitle->runAction( CCSequence::create(
		CCDelayTime::create( 1.0f ),
		reveseseq,
		CCScaleTo::create(0.08f, 1.02f),
		CCScaleTo::create(0.08f, 1.0f),
		CCCallFunc::create(this, callfunc_selector(UILogin::LoginEffectPlay)),
		NULL));
	
	pImage1->runAction( getRepeatForeverAction(pImage1, 10, 0.5f) );
	pImage2->runAction( getRepeatForeverAction(pImage2, 10, 0.8f) );
	pImage3->runAction( getRepeatForeverAction(pImage3, 10, 0.7f) );
	pImage4->runAction( getRepeatForeverAction(pImage4, 10, 0.2f) );
	pImage5->runAction( getRepeatForeverAction(pImage5, 10, 0.3f) );

	UIButton* pBtnPlay = dynamic_cast<UIButton*>(plogin->getChildByName("BtnPlay"));
	pBtnPlay->setTag( LOGINUI_BTN_TAG_PLAYGAME);
	pBtnPlay->isEffects( true, 1.2f );
	pBtnPlay->addReleaseEvent(this, coco_releaseselector(UILogin::ButtonCallBack));

	UIButton* pBtnAuthorn = dynamic_cast<UIButton*>(plogin->getChildByName("BtnAuthorn"));
	pBtnAuthorn->setTag( LOGINUI_BTN_TAG_AUTHORP);
	pBtnAuthorn->isEffects( true, 1.2f );
	pBtnAuthorn->setPosition( ccp(46, nSceneSize.height - 50));
	pBtnAuthorn->addReleaseEvent(this, coco_releaseselector(UILogin::ButtonCallBack));
	pBtnAuthorn->setTouchEnabled(false);


}


CCFiniteTimeAction* UILogin::getSpriteAction( void )
{
	CCActionInterval*  actionScale = CCScaleTo::create(0.17f, 0.94f);
	CCActionInterval * fadeout = CCFadeIn::create(0.17f); 
	CCFiniteTimeAction * reveseseq = CCSpawn::create(actionScale,fadeout,NULL);
	CCActionInterval*  actionScale1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval * easeSineOut = CCEaseSineOut::create(actionScale1);
	CCActionInterval * delaytime = CCDelayTime::create( 0.33f );

	//　顺序执行
	CCFiniteTimeAction* seq = CCSequence::create(
		reveseseq,
		easeSineOut,
		delaytime,
		NULL);

	return seq;
}

CCActionInterval * UILogin::getRepeatForeverAction( void* object, int movedist, float delay )
{
	UIImageView* pMoveImg = (UIImageView*)object;

	CCActionInterval * move = CCMoveTo::create(1, ccp(pMoveImg->getPosition().x, pMoveImg->getPosition().y - movedist));
	CCActionInterval * move1 = CCMoveTo::create(1, ccp(pMoveImg->getPosition().x, pMoveImg->getPosition().y));
	CCActionInterval * delaytime = CCDelayTime::create( delay );
	CCFiniteTimeAction* seq = CCSequence::create(delaytime, move,move1,NULL);
	CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
	return repeatForever;
}

void UILogin::AuthornMoveCallback( void )
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");

	if ( plogin )
	{
		CCSize nSceneSize = CCDirector::sharedDirector()->getWinSize();
		UIPanel* pProducer = (UIPanel*)plogin->getChildByName("PanelProducer");
		UIPanel* pShowProducer = (UIPanel*)plogin->getChildByName("ProducerTable");
		
		pProducer->setVisible( false );
		pProducer->setTouchEnable( false );

		UIImageView* ContentBg = dynamic_cast<UIImageView*>(plogin->getChildByName("ContentBg"));
		ContentBg->setVisible( true );

		UIButton* pBtnPlay = dynamic_cast<UIButton*>(plogin->getChildByName("BtnPlay"));
		UIButton* pBtnAuthorn = dynamic_cast<UIButton*>(plogin->getChildByName("BtnAuthorn"));
		pBtnPlay->setVisible( true );
		pBtnAuthorn->setVisible( false );
		pBtnAuthorn->setTouchEnabled( false);
	}
}

void UILogin::LoginEffectPlay( void )
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");

	if ( plogin )
	{
		UIImageView* plogintitle = dynamic_cast<UIImageView*>(plogin->getChildByName("logintitle"));
		CCPoint pos = plogintitle->getParent()->convertToWorldSpace(plogintitle->getPosition());
		CandyParticle::displayCandyParticle(CANDY_LOGIN_BOOMFLY_EFF, ccp(pos.x, pos.y + 150), this);

		runAction( CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(UILogin::StarEffect1Play)),
			CCDelayTime::create(1.0f),
			CCCallFunc::create(this, callfunc_selector(UILogin::StarEffect2Play)),
			CCDelayTime::create(2.2f),
			CCCallFunc::create(this, callfunc_selector(UILogin::StarEffect3Play)),
			NULL
			));
	}
}

void UILogin::StarEffect1Play( void )
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");
	UIImageView* pParticle1 = dynamic_cast<UIImageView*>(plogin->getChildByName("Particle1"));
	CCPoint pos = pParticle1->getParent()->convertToWorldSpace(pParticle1->getPosition());

	pos = pParticle1->getParent()->convertToWorldSpace(pParticle1->getPosition());
	CandyParticle::displayCandyParticle(CANDY_LOGIN_FLASH_EFFECT, pos, this);
}

void UILogin::StarEffect2Play( void )
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");
	UIImageView* pParticle2 = dynamic_cast<UIImageView*>(plogin->getChildByName("Particle2"));

	CCPoint pos = pParticle2->getParent()->convertToWorldSpace(pParticle2->getPosition());
	CandyParticle::displayCandyParticle(CANDY_LOGIN_FLASH_EFFECT, pos, this);
}

void UILogin::StarEffect3Play( void )
{
	UILayer* layer = (UILayer*)this->getChildByTag(1000);
	Layout* plogin = (Layout*)layer->getWidgetByName("loginimg");
	UIImageView* pParticle3 = dynamic_cast<UIImageView*>(plogin->getChildByName("Particle3"));

	CCPoint pos = pParticle3->getParent()->convertToWorldSpace(pParticle3->getPosition());
	CandyParticle::displayCandyParticle(CANDY_LOGIN_FLASH_EFFECT, pos, this);
}

