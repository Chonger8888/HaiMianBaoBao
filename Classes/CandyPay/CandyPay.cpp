#include "CandyPay.h"
#include "CommonData/CommonData.h"
#include "NetWork.h"
#include "Json.h"
#ifndef WIN32
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif
#include "PlayGame/CandyParticle.h"
#include "Loading/LoadingScene.h"
#include "PlayGame/CandyManager.h"
#include "MainMap/MainMapUiLayer.h"

#define MAX_RETRY_TIMES   3

char* paycodeList[][2]=
{
	{"生命",			"0"},			//6
	{"刷新",			"3"},			//6
	{"糖果锤",			"5"},			//6
	{"互换",			"4"},			//6
	{"彩糖炸弹",		"6"},			//6
	{"包装炸弹",		"7"},			//6
	{"加五步",			"1"},			//6
	{"新手礼包",		"8"},			//6
	{"进阶礼包",		"8"},			//6
	{"高端礼包",		"8"},			//6
	{"至尊大礼包",		"9"},			//20
	{"直接通关",		"2"},			//10
	{"解锁全关卡",		"0"},			//20
	{"优惠礼包",		"10"},			//10
};

// 计费金额
int payPoint[] = 
{
	600,//800,
	600,//400,
	600,//400,
	600,//400,
	600,//600,
	600,//400,
	600,//800,
	2000,//2900,
	600,//2900,
	600,//2900,
	2000,//2900,
	1000,//1000,
	2000,//1000,
	1000,//1000
};

void PayHelper::BuySuccessTips(Tipstype tips )
{
	if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType)
	{
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	}

	char* path = "Image/MainMapUi/ImgBuyPromtp.png";
	if (tips == RECEIVE_TIPS)
	{
		path = "Image/MainMapUi/ImgReceivePromtp.png";
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* BuyPrompt = CCSprite::create(path);
	BuyPrompt->setPosition( ccp(size.width/2,size.height*0.6));
	CCNode* node = CCDirector::sharedDirector()->getRunningScene();
	node->addChild( BuyPrompt,0,1000);

	//CCPoint pos = pBtn->getParent()->convertToWorldSpace(pBtn->getPosition());
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(size.width/2,size.height*0.6), node);

	CCActionInterval * spawn = CCSpawn::create(
		CCMoveTo::create(1.0f, ccp(size.width/2,size.height*0.6 + 150)),
		CCFadeOut::create(1.0f),
		NULL);

	BuyPrompt->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		spawn,
		CCCallFuncN::create(NULL, callfuncN_selector(PayHelper::FuncAfterTips)),
		NULL));
}

void PayHelper::FuncAfterTips( CCNode* node )
{
	if (!node)
	{
		return;
	}
	node->removeFromParentAndCleanup(true);
}

void PayHelper::AndroidPrompt( std::string text )
{
	std::string funcName = "Prompt";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;

	bool isExist = JniHelper::getStaticMethodInfo(
		methodInfo, 
		"org/weme/candy/util/CandyPay", 
		funcName.c_str(), 
		"(Ljava/lang/String;)V"
		);
	if(isExist)	
	{
		jstring  j_Tips = methodInfo.env->NewStringUTF( text.c_str() ); 

		methodInfo.env->CallStaticVoidMethod(
			methodInfo.classID, 
			methodInfo.methodID,
			j_Tips
			);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);    
		CCLog("-------CppCallJava:: call %s success",funcName.c_str() );
		return;
	}
	CCLog("---------jni:call func %s failed------",funcName.c_str());
#endif
}

void PayHelper::AndroidPrompt_Net( std::string text )
{
	std::string funcName = "Prompt_Net";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;

	bool isExist = JniHelper::getStaticMethodInfo(
		methodInfo, 
		"org/weme/candy/util/CandyPay", 
		funcName.c_str(), 
		"(Ljava/lang/String;)V"
		);
	if(isExist)	
	{
		jstring  j_Tips = methodInfo.env->NewStringUTF( text.c_str() ); 

		methodInfo.env->CallStaticObjectMethod(
			methodInfo.classID, 
			methodInfo.methodID,
			j_Tips
			);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);    
		CCLog("-------CppCallJava:: call %s success",funcName.c_str() );
		return;
	}
	CCLog("---------jni:call func %s failed------",funcName.c_str());
#endif
}

//---------------------------
CandyPay::CandyPay()
{
	m_isBuygift = false;
	m_isFinished = true;
	m_BuyPropId = -1;
	m_retryTimes = 0;

	m_RetryNode = CCNode::create();
	CCNode* scene = CCDirector::sharedDirector()->getRunningScene();
	if (scene)
	{
		scene->addChild(m_RetryNode);
	}
}

CandyPay::~CandyPay()
{

}


void CandyPay::RequestCandyOrder(int propId)
{
// 	//不要支付
// 	return;
	if(propId == CANDY_PROP_LIFE && Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
	{
		UIButton *gameLifeBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("lifebtn"));
		gameLifeBut->setTouchEnable(true);
	}
	else if( (propId == GameGift_Level1 || propId == GameGift_Level2 ||propId == GameGift_Level3) && Loading::scenceType == CANDY_SCENCE_MAIN_MAP )
	{
		UIButton* pgameGiftBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameGift")); 
		if ( pgameGiftBut )
		{
			pgameGiftBut->setTouchEnabled( true );

			if(CommonData::m_GiftIDBuyNow == 0)
			{
				pgameGiftBut->setTouchEnabled( false );
			}
		}
	}

// 	if (!m_isFinished)
// 	{
// 		std::string tips = CommonData::GetString("isPaying");
// 		AndroidPrompt(tips);
// 		CCLog("%s",tips.c_str());
// 		return;
// 	}

	m_isFinished = true;
	AddNewTime();

	bool isClickable = IsTimeFree(2);
	if (!isClickable)
	{
		std::string Tooquick = CommonData::GetString("ClickTooQuick");
		AndroidPrompt(Tooquick);
		CCLog("%s",Tooquick.c_str());
		m_isFinished = true;
		return;
	}

	m_isBuygift = false;

	int uid = 8888888;
	int maxlvl = CommonData::getMaxLevel();
	int life = AnalyseJson::logOnMsg.lifeInfo.lifeNum;
	m_BuyPropId = propId;
	
	switch (propId)
	{
	case CANDY_PROP_LIFE:
		//生命
		m_buyPricePoint = payPoint[0];
		m_curPaycode = paycodeList[0][1];
		break;
	case CANDY_PROP_OUT_COLORFULL:
		//彩塘
		m_buyPricePoint = payPoint[4];
		m_curPaycode = paycodeList[4][1];
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		//炸弹唐
		m_buyPricePoint = payPoint[5];
		m_curPaycode = paycodeList[5][1];
		break;
	case CANDY_PROP_IN_RESORT:
		//重排
		m_buyPricePoint = payPoint[1];
		m_curPaycode = paycodeList[1][1];
		break;
	case CANDY_PROP_IN_SWAP:
		//交换
		m_buyPricePoint = payPoint[3];
		m_curPaycode = paycodeList[3][1];
		break;
	case CANDY_PROP_IN_HAMMER:
		//锤子
		m_buyPricePoint = payPoint[2];
		m_curPaycode = paycodeList[2][1];
		break;
	case CANDY_PROP_IN_STEP5:
		//加五步
		m_buyPricePoint = payPoint[6];
		m_curPaycode = paycodeList[6][1];
		break;
	case GameGift_Level1:
		m_isBuygift = true;

		//新手大礼包
		m_buyPricePoint = payPoint[7];
		m_curPaycode = paycodeList[7][1];
		break;
	case GameGift_Level2:
		m_isBuygift = true;

		//进阶大礼包
		m_buyPricePoint = payPoint[8];
		m_curPaycode = paycodeList[8][1];
		break;
	case GameGift_Level3:
		m_isBuygift = true;

		//高端大礼包
		m_buyPricePoint = payPoint[9];
		m_curPaycode = paycodeList[9][1];
		break;
	case Super_gift:
		//限时优惠包
		m_buyPricePoint = payPoint[10];
		m_curPaycode = paycodeList[10][1];
		break;
	case Super_life:
		//超级生命包
		m_buyPricePoint = payPoint[11];
		m_curPaycode = paycodeList[11][1];
		break;
	case Success_Pass:
		m_buyPricePoint = payPoint[11];
		m_curPaycode = paycodeList[11][1];
		break;
	case UnLock_Level:
		m_buyPricePoint = payPoint[12];
		m_curPaycode = paycodeList[12][1];
		break;
	case Exit_Gift:
		m_buyPricePoint = payPoint[13];
		m_curPaycode = paycodeList[13][1];
		break;
	case Zhadan_Gift:
		m_buyPricePoint = payPoint[11];
		m_curPaycode = paycodeList[11][1];
		break;
	case Zhizun_Gift:
		m_buyPricePoint = payPoint[11];
		m_curPaycode = paycodeList[11][1];
		break;
	default:
		m_buyPricePoint = payPoint[0];
		m_curPaycode = paycodeList[0][1];
		break;
	}
	//存储订单号
	CandyPay::getInstance()->setOrderId((char*)CCString::createWithFormat("%d",000)->getCString());

#ifdef WIN32
	/****** win32测试 *******/
//	UpdateProp((char*)m_orderId.c_str());
	/****** win32测试 *******/
#endif // WIN32

	//彈出发送短信界面
	ShowSDKBuyGUI();

	return;


	HttpNetWork::getInstance()->clearKeyVal();
	HttpNetWork::getInstance()->CombineUrl("v_class", "1");
	HttpNetWork::getInstance()->CombineUrl("v_cmd", "0");
	HttpNetWork::getInstance()->CombineUrl("idx",(char*)CCString::createWithFormat("%s",AnalyseJson::logOnMsg.baseInfo.idx.c_str())->getCString());	
	HttpNetWork::getInstance()->CombineUrl("userid",(char*)CCString::createWithFormat("%d",uid)->getCString());	
	HttpNetWork::getInstance()->CombineUrl("points",(char*)CCString::createWithFormat("%d",maxlvl)->getCString());	
	HttpNetWork::getInstance()->CombineUrl("popId",(char*)CCString::createWithFormat("%d",propId)->getCString());	
	HttpNetWork::getInstance()->CombineUrl("item",(char*)CCString::createWithFormat("%s",m_curPaycode.c_str())->getCString());	
	HttpNetWork::getInstance()->CombineUrl("channel",(char*)CCString::createWithFormat("%d",5)->getCString());	
	HttpNetWork::getInstance()->CombineUrl("num",(char*)CCString::createWithFormat("%d",1)->getCString(),true);	
	HttpNetWork::getInstance()->HttpRequestEllipsisUrl(this, callfuncND_selector(CandyPay::CandyOrderCallback),true);
}

void CandyPay::CandyOrderCallback( CCNode* sender, void* data )
{
#ifdef WIN32
	//CandyPayFailed();
	//return;
#endif

	char* net_data = (char*)data;
	// {"status":0,"id":0,"description":"","content":{"orderid":290578}}
	int order = 0;

	//限额
	int pay_status = 0;
	int pay_id = 0;

	//解析数据
	Json* root = Json_create(net_data);
	bool ret = true;
	do 
	{
		if(!root || root->type!=Json_Object)
		{
			ret = false;
			break;
		}

		Json* status = Json_getItem(root, "status");
		if (!status || status->type != Json_Number)
		{
			ret = false;
			break;
		}
		pay_status = status->valueint;

		Json* id = Json_getItem(root, "id");
		if (!id || id->type != Json_Number)
		{
			ret = false;
			break;
		}
		pay_id = id->valueint;

		Json* content = Json_getItem(root,"content");
		if (!content || content->type != Json_Object)
		{
			ret = false;
			break;
		}

		Json* orderid = Json_getItem(content, "orderid");
		if (!orderid || orderid->type != Json_Number)
		{
			ret = false;
			break;
		}
		order = orderid->valueint;

	} while (0);
	
	Json_dispose(root);
	if (!ret)
	{
		std::string text = CommonData::GetString("app_prompt_neterror");
		AndroidPrompt_Net(text);
		m_isFinished = true;
		CCLog("------------analyse data error");
		return;
	}

	//是否达到了限额
// 	if (pay_id < 0 && pay_status < 0 )
// 	{
// 		AndroidPrompt(CommonData::GetString("payMax"));
// 		return;
// 	}
		
	//存储订单号
	CandyPay::getInstance()->setOrderId((char*)CCString::createWithFormat("%d",order)->getCString());

#ifdef WIN32
	/****** win32测试 *******/
	UpdateProp((char*)m_orderId.c_str());
	/****** win32测试 *******/
#endif // WIN32
	
	//彈出发送短信界面
	ShowSDKBuyGUI();
}

void CandyPay::setOrderId( char* str )
{
	m_orderId = str;
}

void CandyPay::ShowSDKBuyGUI()
{
	JniCallFunc((char*)m_curPaycode.c_str(),(char*)m_orderId.c_str(), m_buyPricePoint);
}

void CandyPay::UpdateProp(char* tradeid,bool isWait)
{

	//m_tradeId = tradeid;
#ifdef WIN32

	//WIN32测试
	//HttpNetWork::getInstance()->HttpRequestWithUrl("www.FACEBOOK.com",this, callfuncND_selector(CandyPay::UpdatePropCallback),isWait);
	UpdatePropCallbackSingle();

#else
// 	HttpNetWork::getInstance()->clearKeyVal();
// 	HttpNetWork::getInstance()->CombineUrl("v_class", "1");
// 	HttpNetWork::getInstance()->CombineUrl("v_cmd", "2");
// 	HttpNetWork::getInstance()->CombineUrl("orderid",(char*)m_orderId.c_str());	
// 	HttpNetWork::getInstance()->CombineUrl("tradeid",tradeid,true);	
// 	HttpNetWork::getInstance()->HttpRequestEllipsisUrl(this, callfuncND_selector(CandyPay::UpdatePropCallback),isWait);

	UpdatePropCallbackSingle();

#endif
	
	//存储当前URL，用于重试
	m_CurUpdateUrl = HttpNetWork::getInstance()->GetRequestUrl();
}
void CandyPay::UpdatePropCallbackSingle()
{

	CCLog("CandyPay::UpdatePropCallbackSingle m_BuyPropId= %d",m_BuyPropId);
	switch (m_BuyPropId)
	{
	case CANDY_PROP_LIFE:
		//生命
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 5;
		CommonData::setLifeInfo();
		break;
	case CANDY_PROP_OUT_COLORFULL:
		//彩塘
		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		//炸弹唐
		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);
		break;
	case CANDY_PROP_IN_RESORT:
		//重排
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);
		break;
	case CANDY_PROP_IN_SWAP:
		//交换
		CommonData::changePropNum(CANDY_PROP_IN_SWAP,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);
		break;
	case CANDY_PROP_IN_HAMMER:
		//锤子
		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);
		break;
	case CANDY_PROP_IN_STEP5:
		//加五步
		CommonData::changePropNum(CANDY_PROP_IN_STEP5,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_STEP5);
		break;
	case GameGift_Level1:
		// 新手礼包
// 		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
// 		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);
// 
// 		CommonData::changePropNum(CANDY_PROP_IN_SWAP,2);
// 		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);
// 
// 		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,2);
// 		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,3);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,2);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,2);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		break;
	case GameGift_Level2:
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);


		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		break;
	case GameGift_Level3:
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);


		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);
		break;
	case Super_life:
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 30;
		CommonData::setLifeInfo();
		//超级生命包
		break;
	case Super_gift:
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);

		break;
	case Exit_Gift:
		CommonData::m_isBuyExitGift = 1;
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 10;
		CommonData::setLifeInfo();

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,10);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);
		break;
	case Zhadan_Gift:
		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,5);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,5);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);
		break;
	case Zhizun_Gift:
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);

		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);

		CommonData::changePropNum(CANDY_PROP_IN_SWAP,2);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);

		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);

		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,3);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);
	default:
		break;
	}
	//播放成功提示
	//BuySuccessTips();

	//更新道具
	if(Loading::scenceType == CANDY_SCENCE_MAIN_MAP)
	{
		//MainMapUiLayer::m_mainmapuilayer->refreshLifeUI();
		//MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
		CommonData::m_mapLayerBuyFinish = 1;
		
		if (m_BuyPropId == UnLock_Level)
		{
			CommonData::m_unLockAllLevel = 1;
		}
		else
		{
			CommonData::m_isPlayNewUserAction = true;

			if(CommonData::m_GiftIDBuyNow >= 6)
			{
				UIButton* m_gameGiftBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameGift")); 

				m_gameGiftBut->setVisible(false);
				m_gameGiftBut->setTouchEnable( false );
			}
		}
	}
	else if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
	{
		if(m_BuyPropId != Success_Pass && m_BuyPropId != Super_gift)
		{
			list<UserPropInfoStr>::iterator it = AnalyseJson::logOnMsg.propInfo.begin();
			for (it; it != AnalyseJson::logOnMsg.propInfo.end(); ++it)
			{
				int propid = (*it).id;
				CandyStageIntro::buyPropCallBack(propid);
			}

// 			UIWidget* widget = CandyManager::getInstance()->uiLayer->getShopLayout();
// 			CandyManager::getInstance()->uiLayer->QuitPropWidget((Layout*)widget);
		}


		if (m_BuyPropId == CANDY_PROP_IN_STEP5)
		{
			CandyManager::getInstance()->uiLayer->useProp(CANDY_PROP_IN_STEP5);
		}
		else if (m_BuyPropId == Super_life)
		{
			//CandyManager::getInstance()->resultMgr->getResultLayer()->gameLosePlayAgainCallBack(NULL);
		}
		else if(m_BuyPropId == Super_gift)
		{
			CommonData::m_superGift = 1;
			//改变购买超级大礼包状态
			CCUserDefault::sharedUserDefault()->setIntegerForKey("superGift",1);
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);		//游戏状态要设置成进行中
		}
		else if(m_BuyPropId == Success_Pass)
		{
			CommonData::m_successPass = 1;
		}
		else if(m_BuyPropId == Zhadan_Gift || m_BuyPropId == Zhizun_Gift)
		{
			CommonData::m_nextStage = 1;
		}
		else
		{
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);		//游戏状态要设置成进行中
		}
	}


	//是否是购买礼包
	if (m_isBuygift)
	{
		CommonData::m_GiftIDBuyNow += 1;
		if (CommonData::m_GiftIDBuyNow > 6)
		{
			CommonData::m_GiftIDBuyNow = 0;
		}
	}	
	CCLog("CandyPay::UpdatePropCallbackSingle end");

	m_isFinished = true;
}

void CandyPay::UpdatePropCallback( CCNode* sender, void* data )
{
	
}

void CandyPay::JniCallFunc(  char* paycode,char* orderId,int pricepoint,int buyNum )
{
	//要调用的java函数名称
	std::string funcName = "BuyProduct";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;

	bool isExist = JniHelper::getStaticMethodInfo(
		methodInfo, 
		"org/weme/candy/util/CandyPay", 
		funcName.c_str(), 
		"(Ljava/lang/String;Ljava/lang/String;II)V"
		);
	if(isExist)	
	{
		jstring  l_paycode = methodInfo.env->NewStringUTF( paycode ); 
		jstring  l_orderId = methodInfo.env->NewStringUTF( orderId ); 

		methodInfo.env->CallStaticVoidMethod(
			methodInfo.classID, 
			methodInfo.methodID,
			l_paycode,
			l_orderId,
			pricepoint,
			buyNum);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);    
		methodInfo.env->DeleteLocalRef(l_paycode);      
		methodInfo.env->DeleteLocalRef(l_orderId);      
		CCLog("-------CppCallJava:: call %s success",funcName.c_str() );
		return;
	}
	CCLog("---------jni:call func %s failed------",funcName.c_str());
#else
	CandyPay::getInstance()->UpdateProp("0");

#endif

}


void CandyPay::CandyPayFailed()
{
	m_isFinished = true;

	if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType )
	{
	//加五步购买失败要特殊处理
		if (m_BuyPropId == CANDY_PROP_IN_STEP5 || m_BuyPropId == Success_Pass || m_BuyPropId == Zhadan_Gift || m_BuyPropId == Zhizun_Gift )
		{
			if(m_BuyPropId == CANDY_PROP_IN_STEP5)
			{
				//如果是在商城购买的加五步，购买失败后不弹出过关失败界面
				if (CommonData::m_BuyAdd5From == 1)
				{
					CommonData::m_buyAdd5Failed = 1;
				}
			}
			else if(m_BuyPropId == Success_Pass)
			{
				CommonData::m_successPassFailed = 1;
			}
			else if( m_BuyPropId == Zhadan_Gift || m_BuyPropId == Zhizun_Gift )
			{
				CommonData::m_nextStage = 1;
			}
		}
	}
	else if(CANDY_SCENCE_MAIN_MAP == Loading::scenceType)
	{
		if (m_BuyPropId == Exit_Gift)
		{
			CommonData::m_isExitGame = 1;
		}
		if (m_BuyPropId == GameGift_Level1)
		{
			if (!CommonData::m_isPlayNewUserAction && CommonData::getMaxLevel() < 1)
			{
				CommonData::m_isFirstEnterGame = 1;
			}
		}
	}
}

void CandyPay::RetryUpdate()
{
	if (m_retryTimes >= MAX_RETRY_TIMES)
	{
		m_retryTimes = 0;
		m_isFinished = true;
		AndroidPrompt(CommonData::GetString("RetryFailed"));
		CCLog("%s",CommonData::GetString("RetryFailed").c_str());
		return;
	}

	m_retryTimes++;

	//网络状况时快时慢，所以至少每隔5秒才重试一次
	CCActionInterval* delay = CCDelayTime::create(5);
	CCCallFunc*		  func = CCCallFunc::create(this,callfunc_selector(CandyPay::RetryFunc));
	CCSequence*		  seqAction = CCSequence::create(func,delay,NULL);
	m_RetryNode->runAction(seqAction);
}

void CandyPay::RetryFunc()
{
	//重试
	std::string Tips = CCString::createWithFormat("%s(%d)",CommonData::GetString("RetryUpdatePay").c_str(),m_retryTimes)->getCString();
	AndroidPrompt(Tips);
	CCLog("%s",Tips.c_str());

	UpdateProp((char*)m_tradeId.c_str(),false);
}



