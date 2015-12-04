/********************************************************************
������:		2014/10/24  14:27	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\candy.mini.3.0.3.newMM\Classes\CandyPay\NetWork.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/10/24  14:27	

Ŀ  ��:		http����ͨ�Ų�
*********************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "cocos2d.h"

using namespace cocos2d;

class CallbackFuc:public CCObject
{
public:
	void setTarget(CCObject*target,SEL_CallFuncND fun)
	{
		m_targetObj = target;
		m_func=fun;
	}
	void CallbackActive(CCNode*psnder,void*data)
	{   
		CCLOG("target:%d,func:%d",m_targetObj,m_func);
		if (m_func)
		{
			(m_targetObj->*m_func)(psnder,data);
		}
	}
private:
	CCObject *			m_targetObj;
	SEL_CallFuncND		m_func;
};

class HttpNetWork:public CCObject
{
public:
	~HttpNetWork();
	static HttpNetWork* getInstance()
	{
		if (!m_pintance)
		{
			m_pintance=new HttpNetWork;
			return m_pintance;
		}
		return m_pintance;
	}
	void Destory()
	{
		delete m_pintance;
		m_pintance=NULL;
	}

	/**
	@���ܣ���������,��Ҫ����ȫ��ַ
	@������1.url; ��ַ
		   2.target����������ִ�лص������Ķ���
		   3.fun����������ִ�еĻص�����
		   4.isLoading;�Ƿ���ʾ�ȴ�����
	@���أ���
	*/
	void HttpRequestWithUrl(std::string url,CCObject*target,SEL_CallFuncND fun,bool isLoading = false);

	/**
	@���ܣ��������磬ʡ��ȫ��ַ
	@������1.target����������ִ�лص������Ķ���
		   2.fun����������ִ�еĻص�����
		   3.isLoading;�Ƿ���ʾ�ȴ�����
	@���أ���
	*/
	void HttpRequestEllipsisUrl(CCObject*target,SEL_CallFuncND fun,bool isLoading = false);
	/**
	@���ܣ�ƴ��url
	@������
	@���أ�
	*/
	void CombineUrl(char* key, char* val, bool isEnd = false);
		
	/**
	@���ܣ���׿��ʾ
	@������text����Ҫ��ʾ�������ַ���
	@���أ���
	*/
	void Promt(const char *text);

	/**
	@���ܣ�ȡ�õ�ǰ��������ַ
	@��������
	@���أ���ǰ��ַ�ַ���
	*/
	std::string GetRequestUrl()
	{
		m_FullUrl = getUrlHead() + m_CurRulK_VArr;
		return  m_FullUrl;
	}
	
	/**
	@���ܣ����url�ļ�ֵ
	@��������
	@���أ���
	*/
	void clearKeyVal();

private:
	/**
	@���ܣ�����һ�������¼�����뵽��¼�б���
	@������1.target��ִ�лص��Ķ���
		   2.fun���ص�����
		   3.tag���ü�¼��keyֵ�����ڲ�ѯ
	@���أ�
	*/
	void addCallbackFun(CCObject*target,SEL_CallFuncND fun,const char * tag);
	
	/**
	@���ܣ��յ������緵��ֵ��ִ�еĺ���
	@������1.psender��ִ�лص������Ķ���
			2.data�����ص���������
	@���أ�
	*/
	void HttpResponseFinished(CCNode*psender,void *data);
	/**
	@���ܣ���ʼ��url
	@��������
	@���أ�std::string
	*/
	std::string  getUrlHead();

	/**
	@���ܣ������ȴ���loading����
	@��������
	@���أ���
	*/
	void createWaitingLayer();

	/**
	@���ܣ��Ƴ��ȴ�����
	@��������
	@���أ���
	*/
	void removeWaitingLayer();

	/**
	@���ܣ��ͷŵ���ǰ������������Ļص�
	@��������
	@���أ���
	*/
	void releaseCallArr();
	
	/**
	@���ܣ�Ϊÿ����������һ�������keyֵ���Ե�ǰϵͳʱ��Ϊ�ο�ֵ
	@��������
	@���أ�key; ���ɵ�keyֵ
	*/
	std::string createRandKey();

private:
	HttpNetWork();
	static HttpNetWork*	m_pintance;

	CCLayer *			m_loadingLayer;
	CCArray *			m_pCallbackArr;
	CCDictionary		m_callbackDic;
	std::string			m_CurRulK_VArr;
	std::string			m_FullUrl;
	
	int					m_RequestrnNm;

};

/************************************************************************/
/* 
��������������еĵȴ����棻Ĭ�ϲ�����
*/
/************************************************************************/

class WaitingLayer:public CCLayerColor
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){};
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){};
	CREATE_FUNC(WaitingLayer)
};

#endif