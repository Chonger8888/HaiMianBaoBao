/********************************************************************
创建于:		2014/11/25  11:49	
文件名: 	E:\cocos2d-x-2.2.0\projects\MMnewVersion\Classes\Loading\MMLog.h 
作  者:		彭志宏(alex)
修改于：	2014/11/25  11:49	

目  的:		加载MMlog
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