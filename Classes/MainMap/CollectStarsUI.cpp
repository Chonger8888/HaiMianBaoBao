#include "CollectStarsUI.h"
#include "CommonData/CommonData.h"
#include "MsgMgr/MsgMgr.h"
#include "CandyPay/CandyPay.h"
#include "MainMap/MainMapUiLayer.h"

#ifndef MAX_GROUP
#define MAX_GROUP 15
#endif

const char* receiveCollectMsg = "reveive collect stars rewards";

CollectStarsLayer* CollectStarsLayer::create( const int pageNum )
{
	CollectStarsLayer* layer = new CollectStarsLayer;
	if (layer && layer->init())
	{
		layer->m_curPageNum = pageNum;
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool CollectStarsLayer::init()
{
	if (!Layout::init())
	{
		return false;
	}

	
	return true;
}

void CollectStarsLayer::onEnter()
{
	Layout::onEnter();

	//先初始化数据
	initData(m_curPageNum);

	//如果有过领取记录，那么不显示界面
	if (m_isReceive)
	{
		return;
	}

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(CollectStarsLayer::removeLayout),receiveCollectMsg,NULL);

	initLayout();
	CollectProgress();
	refreshRewardIco();
}

void CollectStarsLayer::onExit()
{
	Layout::onExit();
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
		
}

void CollectStarsLayer::initLayout()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_layout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("Image/MainMapUi/Tools/CandyCollectStarsUI.ExportJson"));
	addChild(m_layout);

	UIPanel* panel = dynamic_cast<UIPanel*>(m_layout->getChildByName("Panel"));
	panel->setPosition(ccp(winSize.width*0.5,winSize.height*0.23));

	m_silverBox = dynamic_cast<UIImageView*>(m_layout->getChildByName("silverBox"));
	m_goldBox = dynamic_cast<UIImageView*>(m_layout->getChildByName("goldBox"));
	m_starPanel = dynamic_cast<UIPanel*>(m_layout->getChildByName("StarPanel"));

	UIImageView* caihong = dynamic_cast<UIImageView*>(m_layout->getChildByName("caihong"));
	caihong->addReleaseEvent(this,coco_releaseselector(CollectStarsLayer::ShowRewardCallback));
	caihong->setTouchEnabled(true);

	m_silverBox->setVisible(false);
	m_goldBox->setVisible(false);
	
	for (int i = 0; i < 3; ++i)
	{
		UIPanel* starPanel = dynamic_cast<UIPanel*>(m_layout->getChildByName(CCString::createWithFormat(
			"Star%d",i+1)->getCString()));
		UIImageView* star = UIImageView::create();
		star->loadTexture(CCString::createWithFormat("Image/MainMapUi/m_pic_star%d.png",i+1)->getCString());
		starPanel->addChild(star);
	}

}

void CollectStarsLayer::ShowRewardCallback(CCObject* sender)
{
	StarRewardUI* rewardLayout = StarRewardUI::create();
	rewardLayout->setData(this);
	addChild(rewardLayout);
}

void CollectStarsLayer::CollectProgress()
{
	UILoadingBar* bar = dynamic_cast<UILoadingBar*>(m_layout->getChildByName("loadingBar"));
	bar->setPercent(m_percernt);

	std::string tips = CCString::createWithFormat("%d/%d",m_curCollectNum,45)->getCString();
	UILabelAtlas* progressTips = dynamic_cast<UILabelAtlas*>(m_layout->getChildByName("progressLabel"));
	progressTips->setStringValue(tips.c_str());
}

void CollectStarsLayer::refreshRewardIco()
{
	//先判断是否通关页面所有关卡
	if (!m_isCompleteSilver)
	{
		//星星
		m_silverBox->setVisible(false);
		m_goldBox->setVisible(false);
		m_starPanel->setVisible(true);
		return;
	}

	//没有收集到45颗星星
	if (!m_isComplete)
	{
		//白银礼箱
		m_silverBox->setVisible(true);
		m_silverBox->runAction(createBoxAction());
		m_goldBox->setVisible(false);
		m_starPanel->setVisible(false);
		return;
	}

	//收集满了45颗
	//黄金礼箱
	m_silverBox->setVisible(false);
	m_goldBox->setVisible(true);
	m_goldBox->runAction(createBoxAction());
	m_starPanel->setVisible(false);

	
}

CCActionInterval* CollectStarsLayer::createBoxAction()
{
	CCActionInterval* moveBy1 = CCMoveBy::create(0.1,ccp(0,40));
	CCActionInterval* easeMove1 = CCEaseElastic::create(moveBy1,0.3);
	CCActionInterval* moveBack1 = CCMoveBy::create(0.1,ccp(0,-40));
	CCActionInterval* moveBy2 = CCMoveBy::create(0.1,ccp(0,25));
	CCActionInterval* easeMove2 = CCEaseElastic::create(moveBy2,0.3);
	CCActionInterval* moveBack2 = CCMoveBy::create(0.1,ccp(0,-25));
	CCActionInterval* delay = CCDelayTime::create(0.5);

	CCActionInterval* seq1 = CCSequence::create(easeMove1,moveBack1,easeMove2,moveBack2,delay,NULL);
	CCActionInterval* repeatAction = CCRepeatForever::create(seq1);

	return repeatAction;
}

void CollectStarsLayer::removeLayout( CCObject* sender )
{
	refreshData();
	removeFromParentAndCleanup(true);
}



//---------------------------------
bool StarRewardUI::init()
{
	if (!Layout::init())
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_layout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("Image/MainMapUi/Tools/CandyStarsRewardUI.ExportJson"));
	m_layout->setTouchEnabled(true);

	UIImageView* bg = dynamic_cast<UIImageView*>(m_layout->getChildByName("StarRewardBg"));
	bg->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
	addChild(m_layout);

	UIButton* exitBtn = dynamic_cast<UIButton*>(m_layout->getChildByName("Exitbtn"));
	exitBtn->setTouchEnabled(true);
	exitBtn->addReleaseEvent(this,coco_releaseselector(StarRewardUI::colseCallback));
	exitBtn->isEffects(true);

	m_tipsField = dynamic_cast<UILabel*>(m_layout->getChildByName("LabelTips"));

	m_silverTitle = m_layout->getChildByName("LabelTitleSilver");
	m_silverIco = m_layout->getChildByName("silverBox");
	m_GoldTitle = m_layout->getChildByName("LabelTitleGold");
	m_GoldIco = m_layout->getChildByName("goldBox");
	m_getBtn = dynamic_cast<UIButton*>(m_layout->getChildByName("GetRewardBtn"));
	m_colseBtn = dynamic_cast<UIButton*>(m_layout->getChildByName("CloseBtn"));

	m_silverTitle->setVisible(false);
	m_silverIco->setVisible(false);
	m_GoldTitle->setVisible(false);
	m_GoldIco->setVisible(false);
	m_getBtn->setVisible(false);
	m_colseBtn->setVisible(false);

	return true;
}

void StarRewardUI::onEnter()
{
	Layout::onEnter();

	if (!m_data->isComplete())
	{
		ShowSilverRewards();
	}
	else
	{
		ShowGoldRewards();
	}
}

void StarRewardUI::ShowSilverRewards()
{
	m_silverTitle->setVisible(true);
	m_silverIco->setVisible(true);

	

	std::string descStr = CommonData::GetString("silverRewardDesc");
	UILabel* rewardDesc = dynamic_cast<UITextArea*>(m_layout->getChildByName("TextArea_Rewards"));
	rewardDesc->setText(descStr.c_str());
	rewardDesc->setFontSize(28);

	//是否通关
	if (m_data->m_isCompleteSilver)
	{
		m_getBtn->setTag(0);
		m_getBtn->setVisible(true);
		m_getBtn->setTouchEnabled(true);
		m_getBtn->addReleaseEvent(this,coco_releaseselector(StarRewardUI::getRewardCB));
		m_getBtn->isEffects(true);

		std::string tipsStr = CommonData::GetString("goldRewardTips");
		m_tipsField->setText(tipsStr.c_str());
	}
	else
	{
		m_colseBtn->setVisible(true);
		m_colseBtn->setTouchEnabled(true);
		m_colseBtn->addReleaseEvent(this,coco_releaseselector(StarRewardUI::colseCallback));
		m_colseBtn->isEffects(true);

		std::string tipsStr = CommonData::GetString("silverRewardTips");
		m_tipsField->setText(tipsStr.c_str());
	}
}

void StarRewardUI::ShowGoldRewards()
{
	m_GoldTitle->setVisible(true);
	m_GoldIco->setVisible(true);

	std::string tipsStr = CommonData::GetString("goldRewardTips");
	m_tipsField->setText(tipsStr.c_str());

	std::string descStr = CommonData::GetString("goldRewardDesc");
	UILabel* rewardDesc = dynamic_cast<UITextArea*>(m_layout->getChildByName("TextArea_Rewards"));
	rewardDesc->setText(descStr.c_str());
	rewardDesc->setFontSize(28);
	//是否收集满45颗
	m_getBtn->setTag(1);
	m_getBtn->setVisible(true);
	m_getBtn->setTouchEnabled(true);
	m_getBtn->addReleaseEvent(this,coco_releaseselector(StarRewardUI::getRewardCB));
	m_getBtn->isEffects(true);
}

void StarRewardUI::colseCallback( CCObject* sender )
{
	removeFromParentAndCleanup(true);
}

void StarRewardUI::getRewardCB( CCObject* sender )
{
	UIButton* btn = (UIButton*)sender;
	int tag = btn->getTag();

	//发送网络数据
	MsgMgr::sendReceiveCollectReward(AnalyseJson::logOnMsg.baseInfo.id,m_data->getMaxLvl(),tag);

	CCUserDefault::sharedUserDefault()->setIntegerForKey("getRewardLevel",m_data->getMaxLvl());

	if(tag == 0)
	{
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 5;
		CommonData::setLifeInfo();

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		CommonData::changePropNum(CANDY_PROP_IN_RESORT,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);
	}
	else if(tag == 1)
	{
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 5;
		CommonData::setLifeInfo();

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		CommonData::changePropNum(CANDY_PROP_IN_RESORT,3);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,3);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,3);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);
	}
	MainMapUiLayer::m_mainmapuilayer->refreshLifeUI();



	CandyPay::getInstance()->BuySuccessTips(RECEIVE_TIPS);

	removeFromParentAndCleanup(true);

	CCNotificationCenter::sharedNotificationCenter()->postNotification(receiveCollectMsg,NULL);

}

//-------------------------

void CollectData::initData(const int pageNum)
{
	m_isComplete = false;
	m_isCompleteSilver = false;
	m_ispass = false;
	m_isReceive = false;
	m_receiveType = STAR_SILVER_REWARD;

	//循环取得当前页面的关卡星星数
	const int allStars = 45;
	int startLvl = pageNum * MAX_GROUP + 1;
	int endLvl = (pageNum + 1) * MAX_GROUP;

	m_maxLvl = endLvl;

	m_curCollectNum = 0;
	for (int i = startLvl; i <= endLvl; ++i)
	{
		m_curCollectNum += CommonData::getStarForLevel(i);
	}
	if (m_curCollectNum >= 35)
	{
		m_isCompleteSilver = true;
	}
	if (m_curCollectNum >= allStars)
	{
		m_isComplete = true;
		m_receiveType = STAR_GOLD_REWARD;
	}
	if (CommonData::getMaxLevel() >= endLvl)
	{
		m_ispass = true;
	}

	//收集进度
	m_percernt = m_curCollectNum*1.0f/allStars * 100;	

	//本页面最大的关卡
	int maxLvl = (m_curPageNum + 1) * MAX_GROUP;

	int getRewardLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("getRewardLevel",0);
	if(maxLvl <= getRewardLevel)
	{
		m_isReceive = true;
	}

	//本页面领取奖励情况,遍历容器，如果存在本页面领取记录，那么
//  	list<CollectStarStruct>::iterator it = AnalyseJson::logOnMsg.collectInfo.begin();
//  	for (it; it != AnalyseJson::logOnMsg.collectInfo.end(); it++)
//  	{
//  		CollectStarStruct data = *it;
//  		if (data.level == maxLvl)
//  		{
//  			m_isReceive = true;
//  			break;
//  		}
//  	}
}

bool CollectData::isComplete()
{
	return m_isComplete;
}

bool CollectData::isPassLvl()
{
	return m_ispass;
}

int CollectData::getPercent()
{
	return m_percernt;
}

int CollectData::getCurPageNum()
{
	return m_curPageNum;
}

bool CollectData::isReceive()
{
	return m_isReceive;
}

int CollectData::getMaxLvl()
{
	return m_maxLvl;
}

void CollectData::refreshData()
{
	CollectStarStruct newStruct;
	newStruct.level = m_maxLvl;
	newStruct.receive = m_receiveType;
	AnalyseJson::logOnMsg.collectInfo.push_back(newStruct);
}

CollectData::CollectData()
{
	CCLOG("");
}

