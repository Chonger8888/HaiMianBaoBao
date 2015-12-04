#include "ClippingTouchLayer.h"
#include "CommonData\CommonData.h"
#include "MainMapUiLayer.h"

const char* ShowOrHideLayer = "show or hide layer";

void ClippingAreaTouchableLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,callfuncO_selector(ClippingAreaTouchableLayer::noticeCallback),
		ShowOrHideLayer,
		NULL);

	createTouchableArea();

	//物理键不可用
	MainMapUiLayer::m_mainmapuilayer->setKeypadEnabled(false);
}

void ClippingAreaTouchableLayer::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);

	//物理键恢复可用
	MainMapUiLayer::m_mainmapuilayer->setKeypadEnabled(true);
}

bool ClippingAreaTouchableLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	for (int i = 0; i < m_RectVec.size(); ++i)
	{
		if (containsTouchLocation(pTouch,m_RectVec.at(i)))
		{
			CCLog("touch area %d",i);
			return false;
		}
	}
	return true;
}

void ClippingAreaTouchableLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void ClippingAreaTouchableLayer::addTouchArea( const TouchArea& area )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//屏幕适配
	TouchArea fixArea = area;
	fixArea.centerPos = FixPoint(fixArea.centerPos);

	m_AreaVec.push_back(fixArea);
}

bool ClippingAreaTouchableLayer::containsTouchLocation( CCTouch* pTouch ,const CCRect& rect )
{
	bool b = rect.containsPoint(convertTouchToNodeSpace(pTouch));
	return b;
}

void ClippingAreaTouchableLayer::createTouchableArea()
{
	CCClippingNode* bigClipper = CCClippingNode::create();

	CCLayerColor* bgLayer = CCLayerColor::create(ccc4(0,0,0,150));
	bigClipper->addChild(bgLayer);

	CCDrawNode *shape = getShape();

	bigClipper->setStencil(shape);
	bigClipper->setInverted(true);//反向
	addChild(bigClipper);
}

CCDrawNode* ClippingAreaTouchableLayer::getShape()
{
	CCDrawNode *shape = CCDrawNode::create();
	ccColor4F green = {0, 1, 0, 1};

	//画出镂空框
	for (int i = 0; i < m_AreaVec.size(); i++)
	{
		TouchArea area = m_AreaVec.at(i);
		shape->drawSegment(area.centerPos,area.centerPos,area.radius,green);
		CCRect	rect = CCRectMake(
			area.centerPos.x - area.radius,
			area.centerPos.y - area.radius,
			area.radius * 2 ,
			area.radius * 2);
		m_RectVec.push_back(rect);
	}

	return shape;
}

void ClippingAreaTouchableLayer::noticeCallback( CCObject* sender )
{
	setVisible(!isVisible());
	if (isVisible())
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-128,this);
	}
	else
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(1280,this);
	}
}

//---------------------
void PointerFinger::addFinger( CCNode* node,const CCPoint& pos )
{
	CCSprite* finger = CCSprite::create("Image/CandyGame/Teach/teachFinger.png");

	CCPoint fixPos = FixPoint(pos);
	CCPoint movePos = ccp(fixPos.x + 30,fixPos.y - 30);
	finger->setPosition(movePos);
	finger->setAnchorPoint(ccp(0,1));
	node->addChild(finger);

	CCActionInterval* moveTo = CCMoveTo::create(0.2,fixPos);
	CCActionInterval* moveBack = CCMoveTo::create(0.5,movePos);
	CCActionInterval* seqAction = CCSequence::create(moveTo,moveBack,NULL);
	finger->runAction(CCRepeatForever::create(seqAction));
}

cocos2d::CCPoint PointerFinger::FixPoint( const CCPoint& pos )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint fixpos = pos;
	fixpos.x *= (winSize.width/720); 
	fixpos.y *= (winSize.height/1280); 
	return fixpos;
}
