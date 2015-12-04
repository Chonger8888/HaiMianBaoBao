#ifndef __Candy__Roulette__H
#define __Candy__Roulette__H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../UIMgr/Singleton_t.h"
#include "../CommonData/Counter.h"


USING_NS_CC;
using namespace cocos2d::extension;

typedef enum
{
	Anim_Roulette_Audience01 = 0,
	Anim_Roulette_Audience02,
	Anim_Roulette_Audience03,
	Anim_Roulette_Audience04,
	Anim_Roulette_Audience05,
	Anim_Roulette_Count,
}RouletteTypeAnim;



class CandyRouletteLayer:public UILayer,public TSingleton<CandyRouletteLayer>
{
public:
	CandyRouletteLayer();
	virtual ~CandyRouletteLayer();

public:
	virtual bool init();

protected:
	void initArmature(void);
	void initAnimation(void);

protected:
	void StartBtnCallBack(CCObject *pSender);
	void RouletteInCallback(void);
	void RotateMusicCallback(void);
	void RotateDoneCallback(void);
	void RouletteOutCallback();
	void animationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
	void IndiaAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
	void StartAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
	int  AdjustRouletteProbability(void);
	void startRunRoulette(void);

protected:
	void RouletteFall(void);
	void RouletteLightUp(void);
	void AudienceCheer(void);
	void RabbitFall(void);
	void RabbitAction1(void);
	void RabbitAction2(void);
	void PlayStick(void);
	void LightAtTheEnd(void);
	void SpecialEffectCb();
	void IndiaRabbitAction1(void);
protected:
	Layout			*m_pRouletteLayout;
	UIButton		*m_pRouletteStartBtn; 
	UIImageView		*m_pRouletteBgImg;
	UIImageView		*m_pRouletteNumImg;
	UIImageView		*m_pRouletteTypeImg;

	CCNode			*m_pAudiences;
// 	CCArmature		*m_pRabbitAnim01;
//	CCArmature		*m_pRabbitAnim02;
	CCSprite		*m_pStick;
	CCSprite		*m_pLight0;
	CCSprite		*m_pLight1;
	CCSprite		*m_pLight2;
	CCSprite		*m_pLight3;
	Counter			*m_pCounter;
	//¬÷≈Ã–¬»ÀŒÔ
	CCArmature		*m_pIndiaRabbitAnim;
	CCArmature		*m_pStart;


	UINodeContainer *m_pContain;
	UINodeContainer *m_pLight;
protected:
	float	m_nRouletteNumRotate;
	float	m_nRouletteTypeRotate;
	int		m_nRouletteSpecialNum;
	int		m_nRouletteSpecialtype;
	bool	m_bPressed;
};
#endif