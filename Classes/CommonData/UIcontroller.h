/********************************************************************
������:		2014/10/09  12:26	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\candy.crush.3.0.2.mini\Classes\CommonData\UIcontroller.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/10/09  12:26	

Ŀ  ��:		UI�����࣬���ڿ������н���UI���ɺ�����������ģʽ
*********************************************************************/
#ifndef _UI_CONTROLLER_H_
#define _UI_CONTROLLER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define CREATE_UI(__TYPE__) \
	static __TYPE__* create() \
{ \
		__TYPE__ *pRet = new __TYPE__(); \
		if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		UIController::getInstance()->setCurUI(pRet);\
		return pRet; \
	} \
		else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}


class UIController : public CCObject
{
public:
	static UIController* getInstance()
	{
		if (m_Instance == NULL)
		{
			m_Instance = new UIController;
			m_Instance->init();
		}

		return m_Instance;
	}

	static void purge()
	{
		CC_SAFE_DELETE(m_Instance);
	}

	//�볡����
	void PlayActionInView(UIWidget* ActionObj, CCObject* select = NULL, SEL_CallFunc func = NULL);
	void PlayActionInView(CCNode* ActionObj, CCObject* select = NULL, SEL_CallFunc func = NULL);

	//�볡����
	void PlayActionOutView(UIWidget* ActionObj, CCObject* select = NULL, SEL_CallFunc func = NULL);
	void PlayActionOutView(CCNode* ActionObj, CCObject* select = NULL, SEL_CallFunc func = NULL);

	void removeCurUI();
	void setCurUI(UIWidget* widget);

private:
	bool init();
	void OutViewCallback();

private:
	UIController();

	static UIController*		m_Instance;
	UIWidget*		m_pCurUI;
	CCSize			m_winSize;

	CCObject*		m_pOutViewSelect;
	SEL_CallFunc	m_OutViewfunc;
};


#endif