/********************************************************************
������:		2014/10/08  11:49	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\candy.crush.3.0.2.mini\Classes\MainMap\TollgatePage.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/10/08  11:49	

Ŀ  ��:		��дһ����ҳҳ�棬���йؿ�����ҳ����
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
*�̳�UIPageview��
*1.�����ӿڣ������Ƿ���ʾ����Ч��
*2.��д��������߻�����ҳ������
*/
/************************************************************************/


class MainMapPageView : public UIPageView
{
public:
	
	MainMapPageView();
	CREATE_FUNC(MainMapPageView);

	/**
	@���ܣ������Ƿ�������
	@������������Ч������true����֮����false
	*/
	void SetClipping(bool b);

	/**
	@���ܣ���д���ຯ������߻���������
	@���������ջ���
	*/
	virtual void handleReleaseLogic(const CCPoint &touchPoint);

};


/************************************************************************/
/* 
*��ҳ��ͬ������
*/
/************************************************************************/
class TollgateDelagate
{
public:
	/**
	@���ܣ�����ҳ�룬��ʼ����0
	@������int���ͣ�����ҳ������
	*/
	void SetPageNum(int num){curPageNum = num;}

	/**
	@���ܣ���ȡҳ��
	@���أ�int��ҳ������
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
*�ؿ�ѡ��ҳ���һ��ҳ��㣬�̳�UILayer���ڸò������һ����д���MainMapPageView��
*��ҳ�㡣��ҳ����ʼҳ�����Ϊ0����
*1.Ĭ��ҳ�棺��û��ָ����ת��ĳ��ҳ��ʱ��Ĭ��������ҵ�ǰ�������ؿ�����Ӧ��ҳ��
*2.ָ��ҳ�棺ֱ����ת����ҳ��Ķ�Ӧҳ��
*/
/************************************************************************/
class TollgateSelectLayer : public UILayer, public TollgateDelagate
{
public:
	TollgateSelectLayer();

	/** 
	@���ܣ���ȡ��ҳ��ʵ���Ľӿ�
	@������int��ָ��Ҫ��תҳ�����ţ���ָ����Ĭ��-1
	@���أ�ʵ����Ӧ������
	*/
	static TollgateSelectLayer* create(int toPageNum = -1);

	virtual bool init();
	virtual void onEnter();

	/**
	@���ܣ�������ҳ��
	@������int������ָ��ҳ�棻�������<0��ֵ������ת����ҽ��������ؿ�����Ӧ��ҳ��
	*/
	void CreatePageView(int pageNum);

	/**
	@���ܣ���ҳ��Ļص����������·�ҳ����
	@��������..
	*/
	void TurnpageCallback(CCObject* sender, PageViewEventType eventType);

	/**
	@���ܣ��������Ϊidx��ҳ��
	@������int��ҳ�����
	*/
	void TurnToPage(int idx);

	/**
	@���ܣ����ý�Ҫ��תҳ������
	@������int��ҳ�����
	*/
	void setToPage(int pageNum){m_ToPageNum = pageNum;}

	/**
	@���ܣ��ӳٴ�����ҳ�㣬���ڼ��س����õ��˳����л�������Ч��Ӱ����Pageview���������ӳٴ���pageview
	*/
	void DelayCreate();

	/**
	@���ܣ���ʼ����ʾ��ҳ����
	*/
	void ShowProgress();

	/**
	@���ܣ����·�ҳ����
	*/
	void RefreshProgress();

	static void ShowYijieUserId(CCNode* node);
private:
	MainMapPageView*	m_pageView;
	
	int					m_ToPageNum;

};

/************************************************************************/
/*
��ҳ���е�ҳ�棬�̳�UIImageView �� TollgateDelagate
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
	@���ܣ����Ŷ���
	@��������
	@���أ���
	*/
	void RunAction();

	/**
	@���ܣ�ˢ��ҳ������ź���ת��ҳ������Ļ���ߵľ���dis��disԽ������ԽС����ת�Ƕ�Խ��
	@��������
	@���أ���
	*/
	void UpdateScale();

	/**
	@���ܣ���ʾ������ͨ�ء���ʾ
	@��������
	@���أ���
	*/
	void ShowPerfectTips();

	/**
	@���ܣ���ʾ��ǰҳ������Ĺؿ���
	@��������
	@���أ���
	*/
	void ShowLvlRange();

	/**
	@���ܣ��ж��Ƿ�����ͨ�أ�����ҳ������йؿ��������������Ƿ�>=45
	@��������
	@���أ�bool; ��������>=45����true����֮����false
	*/
	bool isPerfectPass();

private:
	CCPoint		m_beginPoint;
	CCSize		m_winSize;
};


/************************************************************************/
/*С�ؿ�ѡ���                                                                      */
/************************************************************************/
class SelectLevelLayer : public UILayer,public TollgateDelagate
{
public:
	CREATE_FUNC(SelectLevelLayer);
	virtual void onEnter();

	/**
	@���ܣ���ʾ15���ؿ�
	@��������
	@���أ���
	*/
	void ShowLvls();

	/**
	@���ܣ���ʾ��ǰ�����ռ�����
	@��������
	@���أ���
	*/
	void ShowCollectProgress();


};

/************************************************************************/
/* 
ÿ��ҳ���У�С�ؿ�ͼ�꣬���������Ӧ�ؿ���Ϸ
*/
/************************************************************************/
class LevelBtn : public UIImageView
{
public:
	LevelBtn();

	/**
	@���ܣ�����ʵ��
	@������int���ؿ���ţ���ʼΪ���1
	@���أ�LevelBtn��LevelBtn������
	*/
	static LevelBtn* create(int lvl);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	/**
	@���ܣ����ͼƬ�Ļص��¼�
	@������
	@���أ�
	*/
	void ClickCallback(CCObject* snder,TouchEventType eventType);

	/**
	@���ܣ����ùؿ����
	@������int���ؿ����
	@���أ���
	*/
	void SetLevel(int level){m_CurLevel = level;}

	/**
	@���ܣ�δͨ�صĹؿ�����ʾ����ͼ��
	@��������
	@���أ���
	*/
	void setLockIco();

	/**
	@���ܣ��ж��Ƿ����
	@��������
	@���أ�bool��δͨ�ط���true�����򷵻�false
	*/
	bool isLock();

	/**
	@���ܣ���ͨ�صĹؿ�����ʾ����������
	@��������
	@���أ���
	*/
	void ShowStar();

	/**
	@���ܣ�Ϊÿ���ؿ���ʾ�ؿ���ŵ����ֱ�ǩ
	@��������
	@���أ���
	*/
	void ShowAtlas();

	/**
	@���ܣ������������һ�ؿ�����Ϣ��������Ϸ�ĵ�һ�ؿ�
	@������CCObject;������Ϣ�Ķ���
	@���أ���
	*/
	void GotoGameLevelOne(CCObject* sender);

	//�������йؿ�
	void UnlockAllLvl(CCObject*obj);
private:
	UIButton*		m_button;
	int				m_CurLevel;
	CCSprite*		m_lock;
};

/************************************************************************/
/* 
�����㣬���ϻ�ɫ
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