#ifndef __Candy_Roulette_Story__H
#define __Candy_Roulette_Story__H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CandyRouletteStory:public CCLayer
{
public:
	CandyRouletteStory();
	virtual ~CandyRouletteStory();
public:
	static CCScene* scene(void);
	CREATE_FUNC(CandyRouletteStory);
	virtual bool init();
public:
	virtual void onEnter(void);
	virtual void onEnterTransitionDidFinish(void);
	virtual void onExitTransitionDidStart(void);
	virtual void onExit(void);
public:
	CCActionInterval* getAppearAction();

public:
	void StartTheStory();
	void candyAppearCb();
	void Image2Appear();
	void Image2RoleAppear();
	void Image3Appear();
	void Image3RoleAppear();
	void Image3End();
	void ButtonCallBack(CCObject *pSender);
public:
	UILayer *m_RouletteStoryLayer;
	Layout  *m_pLayout;

	UIImageView *m_pImage1;
	UIImageView *m_pImage1_dialogue1;
	UIImageView *m_pImage1_dialogue2;
	UIImageView *m_pImage1_role1;
	UIImageView *m_pImage1_role2;
	UIImageView *m_pImage1_candy;

	UIImageView *m_pImage2;
	UIImageView *m_pImage2_dialogue;
	UIImageView *m_pImage2_paopao;
	UIImageView *m_pImage2_role1;
	UIImageView *m_pImage2_role2;

	UIImageView *m_pImage3;
	UIImageView *m_pImage3_dialogue;
	UIImageView *m_pImage3_role1;
	UIImageView *m_pImage3_role2;
	UIButton	*m_pImage3_button;

};
#endif













