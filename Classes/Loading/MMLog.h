/********************************************************************
������:		2014/11/25  11:49	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\MMnewVersion\Classes\Loading\MMLog.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/11/25  11:49	

Ŀ  ��:		����MMlog
*********************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MMlog : public CCLayer
{
public:
	CREATE_FUNC(MMlog);

	static CCScene* LogScene();

	virtual void onEnter();

	void GoLoadingScene();
};