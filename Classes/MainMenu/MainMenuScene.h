
#ifndef MAIN_MENU_SCENE__H
#define MAIN_MENU_SCENE__H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CommonMacro.h"

USING_NS_CC;
using namespace cocos2d::extension;


class MainMenu: public CCLayer, public CCEditBoxDelegate
{
	public:
   		CREATE_FUNC(MainMenu);
		
	public:
    		static CCScene* scene(void);
			
	public:
		virtual bool init(void); 

	public:
		virtual void keyBackClicked();

	public:
		virtual void editBoxEditingDidBegin(CCEditBox* editBox);
		virtual void editBoxEditingDidEnd(CCEditBox* editBox);
		virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
		virtual void editBoxReturn(CCEditBox* editBox);

	public:
		void playButtonCallBack(CCObject *pSender);
	#if 0	
	public:
		virtual void onEnter(void);
		virtual void onExit(void);

	public:
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
#endif
};


#endif
