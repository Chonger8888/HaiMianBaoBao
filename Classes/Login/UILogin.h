
#ifndef LOGIN_SCENE__H
#define LOGIN_SCENE__H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum
{
	LOGINUI_BTN_TAG_PLAYGAME,
	LOGINUI_BTN_TAG_AUTHORP,
};

class UILogin: public CCLayer
{
public:
	CREATE_FUNC(UILogin);

public:

	static CCScene* scene(void);

	~UILogin();

public:
	virtual bool init(void); 
	
public:
	void ButtonCallBack(CCObject *pSender);

private:
	void StarEffect1Play(void);
	void StarEffect2Play(void);
	void StarEffect3Play(void);

	void LoginEffectPlay(void);
	void AuthornMoveCallback(void);
	void PlayLoginAction(UILayer* layer);
	CCFiniteTimeAction* getSpriteAction(void);
	CCActionInterval * getRepeatForeverAction(void* object, int movedist, float delay);



};


#endif
