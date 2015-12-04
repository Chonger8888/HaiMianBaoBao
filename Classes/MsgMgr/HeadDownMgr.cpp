#include "HeadDownMgr.h"
#include "cocos2d.h"

#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../Loading/LoadingScene.h"
#include "../CommonData/CommonData.h"
USING_NS_CC;

#define PIC_NAME_FREFIX		"weme_candy_user"

HeadDownMgr* HeadDownMgr::s_headpic = NULL;

HeadDownMgr::HeadDownMgr()
{     
	CCLog("HeadDownMgr::HeadDownMgr");
	//m_headurllist.clear();
	m_curdownIdx.clear();

}

HeadDownMgr::~HeadDownMgr()
{
	//CCHttpClient::getInstance()->destroyInstance();
}

HeadDownMgr* HeadDownMgr::Instance()
{
	if ( !s_headpic )
	{
		s_headpic = new HeadDownMgr();
	}

	return s_headpic;
}	

void HeadDownMgr::Destroy()
{
	if ( s_headpic )
	{
		s_headpic->m_headurllist.clear();
		delete s_headpic;
		s_headpic = NULL;
	}
}
   
void HeadDownMgr::addHeadUrlToList(int userid, std::string url, int pictype)
{
	if (CommonData::headIsExist( url ))
		return;

	char UrlName[128]= {0};
	HeadDownMgr::getHeadNameForUrl(url, UrlName);

	HeadUrlNode node;
	node.m_pictype = pictype;
	node.m_url = url;
	node.m_userid = userid;
	node.m_picname = (char *)CCString::createWithFormat( "%s.png", UrlName )->getCString();
	node.m_isDown = false;
	    
	m_headurllist.push_back( node );
}

void HeadDownMgr::setResponseCallback( CCObject* pTarget, My_HttpResponse pSelector )
{
	_Target = pTarget;
	_pSelector = pSelector;
}

void HeadDownMgr::startDownLoadPic()
{
	if ( !m_headurllist.empty() )
	{
		HttpDownloadHead();
	}
}

bool HeadDownMgr::isDownOver(void)
{
	if ( m_headurllist.empty() )
		return true;
	else
		return false;
}

// the method remove!
void HeadDownMgr::GetHeadUrlList()
{
	HeadUrlNode node;
	std::list<UserFriendInfoStr>::iterator p;

	char UrlName[128]= {0};
	HeadDownMgr::getHeadNameForUrl(AnalyseJson::logOnMsg.baseInfo.headPicUrl, UrlName);

	int len = 0;
	node.m_url = AnalyseJson::logOnMsg.baseInfo.headPicUrl;
	node.m_picname = (char *)CCString::createWithFormat( "%s.png", UrlName )->getCString();
	node.m_isDown = false;

	m_headurllist.push_back( node );

	len = AnalyseJson::friendInfoMsg.friendInfo.size();
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		char UrlName[128]= {0};
		HeadDownMgr::getHeadNameForUrl(p->headPicUr, UrlName);

		node.m_url = p->headPicUr;
		node.m_picname = (char *)CCString::createWithFormat( "%s.png", UrlName )->getCString();
		node.m_isDown = false;
		
		m_headurllist.push_back( node );
	}

	AnalyseJson::getCandPicPath();

	CCLog("HeadDownMgr::GetHeadUrlList %d, path:%s", m_headurllist.size(), AnalyseJson::CandPicPath);
}

void HeadDownMgr::HttpDownloadHead(void)
{
	int nPicType = 0;
	int MaxHeadLen = m_headurllist.size();
	int CulIdx = 0;
	std::list<HeadUrlNode>::iterator p;
	p = m_headurllist.begin();

	while(1)
	{
		char UrlName[128]= {0};
		HeadDownMgr::getHeadNameForUrl(p->m_url, UrlName);
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, p->m_picname.c_str())->getCString();
		FILE* sdCardImg=  fopen(headPath, "rb");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		char *headPath= (char *)CCString::createWithFormat("Image/wemepci/%s", p->m_picname.c_str())->getCString();
		FILE* sdCardImg=  fopen(headPath, "rb");
#endif
		
		CCLog( "File :%s  index:%d, URL:%s ", headPath ,CulIdx, p->m_url.c_str());
		if ( sdCardImg )
		{
			CCLog( "HttpDownloadHead file exist" );

			fclose(sdCardImg);
			sdCardImg= NULL;
			nPicType = p->m_pictype;
			CulIdx++;

			m_headurllist.erase( p );
			if( m_headurllist.empty() )
				break;
			else
			{
				p = m_headurllist.begin();	
				continue;
			}
		}

		CCLog( "HttpDownloadHead  index:%d FileURL:%s",  CulIdx, p->m_url.c_str());
		m_curdownIdx = p->m_picname;
		CCHttpRequest* request = new CCHttpRequest();
		request->setUrl( p->m_url.c_str() );
		request->setRequestType(CCHttpRequest::kHttpGet);
		request->setResponseCallback(this, httpresponse_selector(HeadDownMgr::SaveFriendHead));
		request->setUserData( (void*) p->m_userid );
		CCHttpClient::getInstance()->send(request);
		request->release();
		break;
	}

	if ( m_headurllist.empty() )
	{
		m_headurllist.clear();
		CCLog( "HttpDownloadHead Over" );

		if (PIC_TYPE_MYHEAD == nPicType)
		{
			//Loading::m_loading->HttpGetHeadImgAsyn();
		}
	}
}

void HeadDownMgr::SaveFriendHead(CCHttpClient *sender, CCHttpResponse *response)
{
	if ( m_headurllist.empty() )
		return;

	int nPicType = 0;
	char UrlName[128]= {0};
	HeadDownMgr::getHeadNameForUrl( response->getHttpRequest()->getUrl(), UrlName);
	CCLog("HeadDownMgr::SaveFriendHead  save name:%s", UrlName);

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//char *headPath= (char *)CCString::createWithFormat("%s%s.png",AnalyseJson::CandPicPath, UrlName/*m_curdownIdx.c_str()*/)->getCString();
	char *headPath= (char *)CCString::createWithFormat("%s%s.png",AnalyseJson::CandPicPath, UrlName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	char *headPath= (char *)CCString::createWithFormat("%s%s.png", AnalyseJson::CandPicPath, UrlName)->getCString();
#endif

	FILE* sdCardImg=  fopen(headPath, "wb+");//

	std::string url = response->getHttpRequest()->getUrl();
	int userid = (int)response->getHttpRequest()->getUserData();

	std::list<HeadUrlNode>::iterator p;
	p = m_headurllist.begin();
	nPicType = p->m_pictype;

	if ( sdCardImg )
	{
		CCLog("HttpResponse  /sdcard/weme/ Oper susser");

		// 存储头像
		std::vector<char> *buffer = response->getResponseData();
		int filelen = sizeof( char )*buffer->size();
		char *httpbuf = (char *)malloc( filelen );
		memset(httpbuf, 0,  filelen);

		for (unsigned int i = 0; i < buffer->size(); i++)
		{
			httpbuf[i] = (*buffer)[i];
		}

		int m = sizeof( char ) * strlen( httpbuf );
		int n = fwrite(httpbuf, filelen, 1, sdCardImg );
		fclose(sdCardImg);
		free( httpbuf );



		// 将已下载userid的节点删除
		for ( int i = 0; i <(int) m_headurllist.size(); i++, p++ )
		{
			if ( userid == p->m_userid)
			{
				nPicType = p->m_pictype;
				m_headurllist.erase( p );

				if( m_headurllist.empty() )	break;
				else p = m_headurllist.begin();
			}
			
 		}

		if (!m_headurllist.empty())
		{
			HttpDownloadHead();
		}
		else
		{
			m_headurllist.clear();
			m_curdownIdx.clear();
			CCLog( "HttpDownloadHead Over" );
			if (PIC_TYPE_MYHEAD == nPicType)
			{
				//Loading::m_loading->HttpGetHeadImgAsyn();
			}			
		}
	}
	else
	{
		CCLog("HttpResponse  /sdcard/weme/ Not exiter  head:%s", headPath);
		if (PIC_TYPE_MYHEAD == nPicType)
		{
			//Loading::m_loading->HttpGetHeadImgAsyn();
		}
	}
}

void HeadDownMgr::getHeadNameForUrl(std::string url,char* name)
{
	if ( !url.size() )
	{
		name = NULL;
		return;
	}
	std::string ntemp;
	int ntail2 = url.rfind( "/95/95" );		//图片有特殊的处理 如  56351451dsfasdf155.png/95/95 
	if ( -1 != ntail2 )
		ntemp.assign(url, 0, url.length() - strlen("/95/95") -1 );
	else
		ntemp.assign(url, 0, url.length() );


	int ntail = ntemp.rfind('.');
	int nhead = ntemp.rfind('/');
	char *HeadURl = (char *)CCString::createWithFormat("%s",ntemp.c_str())->getCString();

	strncpy(name, HeadURl+nhead+1, ntail - nhead - 1);
}