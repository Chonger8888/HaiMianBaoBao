#include "UIcontroller.h"

UIController* UIController::m_Instance = NULL;
UIController::UIController()
{

}

bool UIController::init()
{
	m_winSize = CCDirector::sharedDirector()->getWinSize();

	return true;
}

void UIController::PlayActionInView( UIWidget* ActionObj, CCObject* select, SEL_CallFunc func )
{
	//设置初始位置
	ActionObj->setPosition(ccp(m_winSize.width * 0.5, m_winSize.height * 1.55));

	CCPoint ToPos = ccp(0, -m_winSize.height * 0.55);

	CCActionInterval* move_in = CCMoveBy::create(0.7f, ToPos);
	CCActionInterval* move_ease = CCEaseElasticInOut::create((CCActionInterval*)move_in,0.9f );
	CCCallFunc* cb_func = CCCallFunc::create(select, func);

	ActionObj->runAction(CCSequence::create(move_ease, cb_func, NULL));
}

void UIController::PlayActionInView( CCNode* ActionObj, CCObject* select, SEL_CallFunc func )
{
	//设置初始位置
	ActionObj->setPosition(ccp(m_winSize.width * 0.5, m_winSize.height * 1.55));

	//移动距离为一个屏幕高度
	CCPoint ToPos = ccp(0, -m_winSize.height );

	CCActionInterval* move_in = CCMoveBy::create(0.7f, ToPos);
	CCActionInterval* move_ease = CCEaseElasticInOut::create((CCActionInterval*)move_in,0.9f );
	CCCallFunc* cb_func = CCCallFunc::create(select, func);

	ActionObj->runAction(CCSequence::create(move_ease, cb_func, NULL));
}

void UIController::PlayActionOutView( UIWidget* ActionObj, CCObject* select, SEL_CallFunc func )
{
	m_pOutViewSelect = select;
	m_OutViewfunc = func;

	//移动距离为一个屏幕高度
	CCPoint ToPos = ccp(0, m_winSize.height );

	CCActionInterval* move_in = CCMoveBy::create(0.7f, ToPos);
	CCActionInterval* move_ease = CCEaseElasticInOut::create((CCActionInterval*)move_in,0.9f );
	CCCallFunc* cb_func = CCCallFunc::create(this, callfunc_selector(UIController::OutViewCallback));

	ActionObj->runAction(CCSequence::create(move_ease, cb_func, NULL));
}

void UIController::PlayActionOutView( CCNode* ActionObj, CCObject* select, SEL_CallFunc func )
{
	m_pOutViewSelect = select;
	m_OutViewfunc = func;

	//移动距离为一个屏幕高度
	CCPoint ToPos = ccp(0, m_winSize.height );

	CCActionInterval* move_in = CCMoveBy::create(0.7f, ToPos);
	CCActionInterval* move_ease = CCEaseElasticInOut::create((CCActionInterval*)move_in,0.9f );
	CCCallFunc* cb_func = CCCallFunc::create(this, callfunc_selector(UIController::OutViewCallback));

	ActionObj->runAction(CCSequence::create(move_ease, cb_func, NULL));
}

void UIController::OutViewCallback()
{
	removeCurUI();
	if (m_pOutViewSelect && m_OutViewfunc)
	{
		(m_pOutViewSelect->*m_OutViewfunc)();
	}
}

void UIController::removeCurUI()
{
	if (m_pCurUI)
	{
		m_pCurUI->removeFromParentAndCleanup(true);
		m_pCurUI = NULL;
	}
}

void UIController::setCurUI( UIWidget* widget )
{
	m_pCurUI = widget;
}


