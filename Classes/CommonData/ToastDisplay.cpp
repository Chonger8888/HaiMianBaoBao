#include "ToastDisplay.h"

USING_NS_CC;
USING_NS_CC_EXT;

ToastDisplay::ToastDisplay()
{
	m_isShowing = false;
	m_pLayerBG = NULL;
	m_pLabTips = NULL;
}

ToastDisplay::~ToastDisplay()
{
	m_pLayerBG->release();
}

void ToastDisplay::onEnter()
{
	cocos2d::CCLayer::onEnter();

	if (m_pLayerBG)
		return;

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	m_pLayerBG = CCLayerColor::create( ccc4( 53, 47, 36, 100 ) );
	m_pLayerBG->setAnchorPoint( ccp( 0.5f, 0.5f ) );
	m_pLayerBG->setPosition( s.width / 2, TIPS_BG_OFFSET_Y );
	addChild( m_pLayerBG );

	m_pLabTips = cocos2d::CCLabelTTF::create();
	m_pLabTips->setAnchorPoint( ccp( 0.5f, 0.5f ) );
	m_pLabTips->setFontSize( 25 );
	//m_pLabTips->setFontName( "Marker Felt" );
	m_pLabTips->setColor( ccc3( 255, 255, 255 ) );
	m_pLayerBG->addChild( m_pLabTips );
}

// �����ı�
void ToastDisplay::SetTips(std::string tips)
{
	if (!m_isShowing)
	{
		CCDirector::sharedDirector()->getRunningScene()->addChild( this );
		m_isShowing = true;
	}

	RefreshTips( tips );
}

// ˢ����ʾ��Ϣ
void ToastDisplay::RefreshTips(std::string tips)
{
	// ������ʾ��Ϣ
	m_pLabTips->setString( tips.c_str() );
	CCSize strsize = m_pLabTips->getContentSize();

	// ���ñ�����
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pLayerBG->setPosition( ccp( winSize.width / 2 - strsize.width / 2 - TIPS_BG_OFFSET_W, winSize.height / 8 + strsize.height  ) );
	m_pLayerBG->setContentSize( CCSizeMake( (strsize.width + (TIPS_BG_OFFSET_W * 2)),  (strsize.height + (TIPS_BG_OFFSET_H * 2) )) );

	// ������ʾ��Ϣ����
	m_pLabTips->setPosition( ccp( m_pLayerBG->getContentSize().width / 2, m_pLayerBG->getContentSize().height / 2 ) );

	// ��ʱ����ʼ����
	this->unschedule( schedule_selector( ToastDisplay::HideForTimeout ) );
	this->scheduleOnce( schedule_selector( ToastDisplay::HideForTimeout ), TIPS_SHOW_TIME );

	// ����Ч����ʼ��Ч
	m_pLayerBG->stopAllActions();
	CCActionInterval*  action1 = CCFadeOut::create( TIPS_SHOW_TIME - TIPS_SHOW_FADE );
	m_pLayerBG->runAction( action1 );
	m_pLabTips->stopAllActions();
	CCActionInterval*  action2 = (CCActionInterval*) action1->copy();
	m_pLabTips->runAction( action2 );
}

// ��ʾʱ�䵽
void ToastDisplay::HideForTimeout(float dt)
{
	m_isShowing = false;
	CCDirector::sharedDirector()->getRunningScene()->removeChild( this, false );
}
