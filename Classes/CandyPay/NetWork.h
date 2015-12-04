/********************************************************************
创建于:		2014/10/24  14:27	
文件名: 	E:\cocos2d-x-2.2.0\projects\candy.mini.3.0.3.newMM\Classes\CandyPay\NetWork.h 
作  者:		彭志宏(alex)
修改于：	2014/10/24  14:27	

目  的:		http网络通信层
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
	@功能：请求网络,需要传入全网址
	@参数：1.url; 网址
		   2.target；完成请求后执行回调函数的对象
		   3.fun；完成请求后执行的回调函数
		   4.isLoading;是否显示等待界面
	@返回：无
	*/
	void HttpRequestWithUrl(std::string url,CCObject*target,SEL_CallFuncND fun,bool isLoading = false);

	/**
	@功能：请求网络，省略全网址
	@参数：1.target；完成请求后执行回调函数的对象
		   2.fun；完成请求后执行的回调函数
		   3.isLoading;是否显示等待界面
	@返回：无
	*/
	void HttpRequestEllipsisUrl(CCObject*target,SEL_CallFuncND fun,bool isLoading = false);
	/**
	@功能：拼接url
	@参数：
	@返回：
	*/
	void CombineUrl(char* key, char* val, bool isEnd = false);
		
	/**
	@功能：安卓提示
	@参数：text；需要提示的文字字符串
	@返回：无
	*/
	void Promt(const char *text);

	/**
	@功能：取得当前的请求网址
	@参数：无
	@返回：当前网址字符串
	*/
	std::string GetRequestUrl()
	{
		m_FullUrl = getUrlHead() + m_CurRulK_VArr;
		return  m_FullUrl;
	}
	
	/**
	@功能：清空url的键值
	@参数：无
	@返回：无
	*/
	void clearKeyVal();

private:
	/**
	@功能：增加一条请求记录，插入到记录列表中
	@参数：1.target；执行回调的对象
		   2.fun；回调函数
		   3.tag；该记录的key值，用于查询
	@返回：
	*/
	void addCallbackFun(CCObject*target,SEL_CallFuncND fun,const char * tag);
	
	/**
	@功能：收到了网络返回值后执行的函数
	@参数：1.psender；执行回调函数的对象
			2.data；返回的网络数据
	@返回：
	*/
	void HttpResponseFinished(CCNode*psender,void *data);
	/**
	@功能：初始化url
	@参数：无
	@返回：std::string
	*/
	std::string  getUrlHead();

	/**
	@功能：创建等待的loading界面
	@参数：无
	@返回：无
	*/
	void createWaitingLayer();

	/**
	@功能：移除等待界面
	@参数：无
	@返回：无
	*/
	void removeWaitingLayer();

	/**
	@功能：释放掉当前所有网络请求的回调
	@参数：无
	@返回：无
	*/
	void releaseCallArr();
	
	/**
	@功能：为每个请求生成一个随机的key值，以当前系统时间为参考值
	@参数：无
	@返回：key; 生成的key值
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
在请求网络过程中的等待界面；默认不加载
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