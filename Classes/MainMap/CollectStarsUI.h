/********************************************************************
������:		2014/10/20  21:07	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\candy.crush.clean.3.0.2\Classes\MainMap\CollectStarsUI.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/10/20  21:07	

Ŀ  ��:		�й������ռ����佱��
*********************************************************************/

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum StarRewardType
{
	STAR_SILVER_REWARD,
	STAR_GOLD_REWARD,
};


class CollectData
{
public:
	CollectData();
	bool isComplete();	//�Ƿ��ռ���45����
	bool isPassLvl();	//�Ƿ�ͨ�ص�ǰҳ��
	bool isReceive();	//�Ƿ���ȡ��
	int getPercent();	//��ǰ����
	int getCurPageNum();//��ǰҳ��
	int getMaxLvl();	//��ǰҳ������ؿ�

protected:
	void initData(const int pageNum);
	void refreshData();
public:
	int		m_curCollectNum;
	int		m_percernt;
	int		m_curPageNum;
	int		m_maxLvl;
	bool	m_isReceive;
	bool	m_isComplete;
	bool	m_isCompleteSilver;
	bool	m_ispass;
	StarRewardType		m_receiveType;

};

/************************************************************************/
/* 
ҳ���������ռ����������ʾ
*/
/************************************************************************/
class CollectStarsLayer : public Layout, public CollectData
{
public:
	static CollectStarsLayer* create(const int pageNum);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void CollectProgress();
	void initLayout();
	void ShowRewardCallback(CCObject* sender);
	void refreshRewardIco();
	void removeLayout(CCObject* sender);
	CCActionInterval* createBoxAction();
private:
	Layout*			m_layout;
	UIImageView*	m_silverBox;
	UIImageView*	m_goldBox;
	UIPanel*		m_starPanel;
};

/************************************************************************/
/* 
������Ϣ����
*/
/************************************************************************/
class StarRewardUI : public Layout
{
public:
	CREATE_FUNC(StarRewardUI);
	virtual bool init();
	virtual void onEnter();
	void ShowSilverRewards();
	void ShowGoldRewards();

	void getRewardCB(CCObject* sender);
	void colseCallback(CCObject* sender);
	void setData(CollectData* data){m_data = data;}
	void remove();

private:
	Layout*				m_layout;
	StarRewardType		m_rewardType;
	UIWidget*			m_silverTitle;
	UIWidget*			m_silverIco;
	UIWidget*			m_GoldTitle;
	UIWidget*			m_GoldIco;
	UIButton*			m_getBtn;
	UIButton*			m_colseBtn;
	UILabel*			m_tipsField;
	CollectData*		m_data;			
};
