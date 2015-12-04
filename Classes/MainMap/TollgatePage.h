/********************************************************************
创建于:		2014/10/08  11:49	
文件名: 	E:\cocos2d-x-2.2.0\projects\candy.crush.3.0.2.mini\Classes\MainMap\TollgatePage.h 
作  者:		彭志宏(alex)
修改于：	2014/10/08  11:49	

目  的:		编写一个翻页页面，所有关卡放入页面中
*********************************************************************/

#ifndef _NEW_MAIN_SCENE_H_
#define _NEW_MAIN_SCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainMap/MainMapUiLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

/************************************************************************/       
/*
*继承UIPageview类
*1.创建接口，设置是否显示遮罩效果
*2.重写函数，提高滑动翻页灵敏度
*/
/************************************************************************/


class MainMapPageView : public UIPageView
{
public:
	
	MainMapPageView();
	CREATE_FUNC(MainMapPageView);

	/**
	@功能：设置是否有遮罩
	@参数：有遮罩效果传入true，反之传入false
	*/
	void SetClipping(bool b);

	/**
	@功能：重写基类函数，提高滑动灵敏度
	@参数：参照基类
	*/
	virtual void handleReleaseLogic(const CCPoint &touchPoint);

};


/************************************************************************/
/* 
*翻页共同属性类
*/
/************************************************************************/
class TollgateDelagate
{
public:
	/**
	@功能：设置页码，起始数字0
	@参数：int类型，传入页码数字
	*/
	void SetPageNum(int num){curPageNum = num;}

	/**
	@功能：获取页码
	@返回：int，页码数字
	*/
	int GetPageNum(){return curPageNum;}
	

	void setMainMapUi(MainMapUiLayer* uilayer){ mainMapUi = uilayer;}
	MainMapUiLayer* getMainMapUi(){return mainMapUi;}

protected:
	int curPageNum;
	MainMapUiLayer*		mainMapUi;
};

/************************************************************************/
/*
*关卡选择页面的一个页面层，继承UILayer。在该层上添加一个重写后的MainMapPageView的
*翻页层。翻页（起始页面序号为0）：
*1.默认页面：在没有指定跳转到某个页面时，默认跳到玩家当前最大解锁关卡所对应的页面
*2.指定页面：直接跳转到翻页层的对应页面
*/
/************************************************************************/
class TollgateSelectLayer : public UILayer, public TollgateDelagate
{
public:
	TollgateSelectLayer();

	/** 
	@功能：获取翻页层实例的接口
	@参数：int；指定要跳转页面的序号，不指定则默认-1
	@返回：实例对应的类名
	*/
	static TollgateSelectLayer* create(int toPageNum = -1);

	virtual bool init();
	virtual void onEnter();

	/**
	@功能：创建翻页层
	@参数：int；跳到指定页面；如果传入<0的值，则跳转到玩家解锁的最大关卡所对应的页面
	*/
	void CreatePageView(int pageNum);

	/**
	@功能：翻页后的回调，用来更新翻页进度
	@参数：略..
	*/
	void TurnpageCallback(CCObject* sender, PageViewEventType eventType);

	/**
	@功能：翻到序号为idx的页面
	@参数：int；页面序号
	*/
	void TurnToPage(int idx);

	/**
	@功能：设置将要跳转页面的序号
	@参数：int；页面序号
	*/
	void setToPage(int pageNum){m_ToPageNum = pageNum;}

	/**
	@功能：延迟创建翻页层，由于加载场景用到了场景切换过渡特效，影响了Pageview创建，故延迟创建pageview
	*/
	void DelayCreate();

	/**
	@功能：初始化显示翻页进度
	*/
	void ShowProgress();

	/**
	@功能：更新翻页进度
	*/
	void RefreshProgress();

	static void ShowYijieUserId(CCNode* node);
private:
	MainMapPageView*	m_pageView;
	
	int					m_ToPageNum;

};

/************************************************************************/
/*
翻页层中的页面，继承UIImageView 和 TollgateDelagate
*/
/************************************************************************/
class TollgaePage : public UIImageView, public TollgateDelagate
{
public:
	CREATE_FUNC(TollgaePage);

	virtual bool init();
	virtual void onEnter();
	virtual bool onTouchBegan(const CCPoint &touchPoint);
	virtual void onTouchEnded(const CCPoint &touchPoint);

	/**
	@功能：播放动作
	@参数：无
	@返回：无
	*/
	void RunAction();

	/**
	@功能：刷新页面的缩放和旋转；页面离屏幕中线的距离dis，dis越大，缩放越小，旋转角度越大
	@参数：无
	@返回：无
	*/
	void UpdateScale();

	/**
	@功能：显示“完美通关”标示
	@参数：无
	@返回：无
	*/
	void ShowPerfectTips();

	/**
	@功能：显示当前页面包含的关卡数
	@参数：无
	@返回：无
	*/
	void ShowLvlRange();

	/**
	@功能：判断是否完美通关，即该页面的所有关卡所得星星数量是否>=45
	@参数：无
	@返回：bool; 总星星数>=45返回true，反之返回false
	*/
	bool isPerfectPass();

private:
	CCPoint		m_beginPoint;
	CCSize		m_winSize;
};


/************************************************************************/
/*小关卡选择层                                                                      */
/************************************************************************/
class SelectLevelLayer : public UILayer,public TollgateDelagate
{
public:
	CREATE_FUNC(SelectLevelLayer);
	virtual void onEnter();

	/**
	@功能：显示15个关卡
	@参数：无
	@返回：无
	*/
	void ShowLvls();

	/**
	@功能：显示当前星星收集进度
	@参数：无
	@返回：无
	*/
	void ShowCollectProgress();


};

/************************************************************************/
/* 
每个页面中，小关卡图标，点击后进入对应关卡游戏
*/
/************************************************************************/
class LevelBtn : public UIImageView
{
public:
	LevelBtn();

	/**
	@功能：创建实例
	@参数：int；关卡序号，起始为序号1
	@返回：LevelBtn；LevelBtn类名；
	*/
	static LevelBtn* create(int lvl);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	/**
	@功能：点击图片的回调事件
	@参数：
	@返回：
	*/
	void ClickCallback(CCObject* snder,TouchEventType eventType);

	/**
	@功能：设置关卡序号
	@参数：int；关卡序号
	@返回：无
	*/
	void SetLevel(int level){m_CurLevel = level;}

	/**
	@功能：未通关的关卡，显示枷锁图标
	@参数：无
	@返回：无
	*/
	void setLockIco();

	/**
	@功能；判断是否加锁
	@参数：无
	@返回：bool；未通关返回true，否则返回false
	*/
	bool isLock();

	/**
	@功能：已通关的关卡，显示其获得星星数
	@参数：无
	@返回：无
	*/
	void ShowStar();

	/**
	@功能：为每个关卡显示关卡序号的数字标签
	@参数：无
	@返回：无
	*/
	void ShowAtlas();

	/**
	@功能：监听到进入第一关卡的消息，进入游戏的第一关卡
	@参数：CCObject;发送消息的对象
	@返回：无
	*/
	void GotoGameLevelOne(CCObject* sender);

	//解锁所有关卡
	void UnlockAllLvl(CCObject*obj);
private:
	UIButton*		m_button;
	int				m_CurLevel;
	CCSprite*		m_lock;
};

/************************************************************************/
/* 
背景层，加上灰色
*/
/************************************************************************/


class BackGroudLayer : public CCLayer
{
public:
	CREATE_FUNC(BackGroudLayer);
	virtual bool init();
	virtual void onEnter();

	void UpdateVector(float dt);

private:
	CCPoint	m_gradientPos;
	CCNode* m_VecNode;
};




#endif