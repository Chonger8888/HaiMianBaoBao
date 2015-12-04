#ifndef HEAD_DOWN_MGR_H
#define HEAD_DOWN_MGR_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define CANDY_DEFAULT_HEADPATH		"Image/MainMapUi/user_defaulthead.png"
typedef enum
{
	PIC_TYPE_MYHEAD = 1,
	PIC_TYPE_FRIEND,
	PIC_TYPE_SYSTEM,
	PIC_TYPE_NOFRIEND,
}PicTypeStr;

// Í·ÏñURL½Úµã
typedef struct HeadUrlNode_t
{
	bool			m_isDown;
	int				m_pictype;
	int				m_userid;
	std::string		m_url;
	std::string		m_picname;
}HeadUrlNode;

typedef struct RecordHeadUrl_t
{
	int				m_id;
	std::string		m_picname;
}RecordHeadUrl;

typedef void (CCObject::*My_HttpResponse)(void);
#define httpHeaddown_Asyn(_SELECTOR) (My_HttpResponse)(&_SELECTOR)

class HeadDownMgr:public CCObject
{
public:

	static HeadDownMgr*	Instance();
	static void			Destroy();

public:
	HeadDownMgr();
	~HeadDownMgr();

	void addHeadUrlToList(int userid, std::string url, int pictype);
	void setResponseCallback( CCObject* pTarget, My_HttpResponse pSelector );
	void startDownLoadPic(void);
	bool isDownOver(void);

	void GetHeadPic(void);

	static void getHeadNameForUrl(std::string url,char* name);
protected:

private:
	void GetHeadUrlList(void);
	void HttpDownloadHead(void);
	void SaveFriendHead(CCHttpClient *sender, CCHttpResponse *response);

public:
	std::string					m_curdownIdx;
	std::list<HeadUrlNode>		m_headurllist;

public:
	static HeadDownMgr* s_headpic;

protected:
	CCObject* _Target;
	My_HttpResponse _pSelector;
	
};


#endif