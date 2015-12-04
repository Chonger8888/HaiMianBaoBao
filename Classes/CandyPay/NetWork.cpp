#include "NetWork.h"
#include "cocos-ext.h"
#include "CommonMacro.h"
using namespace cocos2d;
using namespace extension;



HttpNetWork::HttpNetWork()
	:m_loadingLayer(NULL)
	,m_RequestrnNm(0)
{ 
	m_pCallbackArr=CCArray::create();
	m_pCallbackArr->retain();

	srand(time(NULL));
}

HttpNetWork::~HttpNetWork()
{
	m_pCallbackArr->release();
}

void HttpNetWork::addCallbackFun(CCObject*target,SEL_CallFuncND fun,const char * tag)
{
	CallbackFuc*fuc = new CallbackFuc;
	fuc->setTarget(target,fun);
	fuc->autorelease();
	m_callbackDic.setObject(fuc,tag);
	//m_pCallbackArr->addObject(fuc);
}

void HttpNetWork::HttpRequestWithUrl(std::string curl,CCObject*target,SEL_CallFuncND fun,bool isLoading/* =false */)
{  
	if (isLoading)
	{
		createWaitingLayer();
	}

	CCHttpRequest* request = new CCHttpRequest();//
	m_FullUrl.clear();
	m_FullUrl = curl;
	request->setUrl(m_FullUrl.c_str());
	CCLog("%s",m_FullUrl.c_str());
	request->setRequestType(CCHttpRequest::kHttpGet);

	std::string key = createRandKey();
	addCallbackFun(target,fun,key.c_str());
	request->setResponseCallback(this,callfuncND_selector(HttpNetWork::HttpResponseFinished));
	request->setTag(key.c_str());
	CCHttpClient::getInstance()->setTimeoutForConnect(30);
	CCHttpClient::getInstance()->setTimeoutForRead(100);
	CCHttpClient::getInstance()->send(request);

	request->release();
}

void HttpNetWork::HttpRequestEllipsisUrl( CCObject*target,SEL_CallFuncND fun,bool isLoading /*= false*/ )
{
	if (isLoading)
	{
		createWaitingLayer();
	}

	CCHttpRequest* request = new CCHttpRequest();
	m_FullUrl.clear();
	m_FullUrl = m_CurRulK_VArr;
	request->setUrl(m_FullUrl.c_str());
	CCLog("%s",m_FullUrl.c_str());
	request->setRequestType(CCHttpRequest::kHttpGet);

	std::string key = createRandKey();
	addCallbackFun(target,fun,key.c_str());
	request->setResponseCallback(this,callfuncND_selector(HttpNetWork::HttpResponseFinished));
	request->setTag(key.c_str());
	CCHttpClient::getInstance()->setTimeoutForConnect(30);
	CCHttpClient::getInstance()->setTimeoutForRead(100);
	CCHttpClient::getInstance()->send(request);
	request->release();
}

void HttpNetWork::HttpResponseFinished(CCNode*psender,void *data)
{   
	removeWaitingLayer();
	
	extension::CCHttpResponse *response = (extension::CCHttpResponse*)data;
	bool b = response->isSucceed();
	const char *tag = response->getHttpRequest()->getTag();

	std::vector<char> *buffer = response->getResponseData();
	std::string s_data;
	if (!buffer->empty())
	{
		for (unsigned int i = 0; i < buffer->size(); i++)
		{   
			s_data.push_back((*buffer)[i]);
		}
	}

	if (!b)
	{
		CCLOG("connect failed");
		CCLOG("%s",s_data.c_str());
		CallbackFuc *pfunc=dynamic_cast<CallbackFuc *>(m_callbackDic.objectForKey(tag));
		if (!pfunc)
		{
			return;
		}
	
		const char * errodata = "error";
		pfunc->CallbackActive(psender,(void*)errodata);

		m_callbackDic.removeObjectForKey(tag);
		return;

	}
	
	void* v_data = (void*)s_data.c_str();

	cocos2d::CCPrettyPrinter vister;
	m_callbackDic.acceptVisitor(vister);
	CCLog("m_Classdic:%s",vister.getResult().c_str());

	CallbackFuc *pfunc = dynamic_cast<CallbackFuc *>(m_callbackDic.objectForKey(tag));
	if (!pfunc)
	{
		return;
	}
	
	pfunc->CallbackActive(psender,v_data);
	m_callbackDic.removeObjectForKey(tag);
	//m_pCallbackArr->removeObjectAtIndex(0);
}

void HttpNetWork::createWaitingLayer()
{   
	m_RequestrnNm++;
	if (!m_loadingLayer)
	{
		m_loadingLayer= WaitingLayer::create();
     	CCDirector::sharedDirector()->getRunningScene()->addChild(m_loadingLayer,5);
	}
}

void HttpNetWork::removeWaitingLayer()
{  
	--m_RequestrnNm;
	if (m_RequestrnNm < 0)
	{
		m_RequestrnNm = 0;
	}
   if (m_loadingLayer && m_RequestrnNm ==0)
   {
	   CCDirector::sharedDirector()->getRunningScene()->removeChild(m_loadingLayer);
	   m_loadingLayer = NULL;
   }
   
}

void HttpNetWork::releaseCallArr()
{
	 //m_pCallbackArr->removeAllObjects();
	m_callbackDic.removeAllObjects();
}

void HttpNetWork::Promt( const char *text )
{

}

std::string HttpNetWork::getUrlHead()
{
	std::string urlhead = CCString::createWithFormat(CANDY_PHP_ADD, CANDY_CURRENT_VERSIONS)->getCString();
	return urlhead;
}

void HttpNetWork::CombineUrl( char* key, char* val, bool isEnd /*= false*/ )
{
	std::string newKV = CCString::createWithFormat("%s=%s",key,val)->getCString();
	m_CurRulK_VArr += newKV;

	if (!isEnd)
	{
		m_CurRulK_VArr += "&";
	}
	else
	{
		m_CurRulK_VArr = getUrlHead() + m_CurRulK_VArr;
	}
}

void HttpNetWork::clearKeyVal()
{
	m_CurRulK_VArr.clear();
}

std::string HttpNetWork::createRandKey()
{
	time_t p;
	time(&p);

	int randNum = rand()%999999;
	std::string Randkey = CCString::createWithFormat("%d_%ld",randNum,(long)p)->getCString();

	return Randkey;
}





//------------------------
void WaitingLayer::onEnter()
{    
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-140,true);
	CCSprite *pSpritewait=CCSprite::create("Image/Loading/loading.png");
	CCSize s=getContentSize();
	pSpritewait->setPosition(ccp(s.width/2,s.height/2));
	pSpritewait->runAction(CCRepeatForever::create(CCRotateBy::create(0.8,360)));
	addChild(pSpritewait);
}
void WaitingLayer::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool WaitingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

bool WaitingLayer::init()
{
	return CCLayerColor::initWithColor(ccc4(0,0,0,200));
}



HttpNetWork*HttpNetWork::m_pintance=NULL;
