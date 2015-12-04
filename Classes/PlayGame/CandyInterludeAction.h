#ifndef _CANDY_INTERLUDE_ACTION_H_
#define _CANDY_INTERLUDE_ACTION_H_


#include "cocos2d.h"
#include "cocos-ext.h"
#include "../UIMgr/Singleton_t.h"

USING_NS_CC;
USING_NS_CC_EXT;


typedef enum
{
	Anim_Interlude_People1_Audience01 = 1100,
	Anim_Interlude_People1_Audience02,
	Anim_Interlude_People1_Audience03,
	Anim_Interlude_People1_Audience04,
	Anim_Interlude_People2_Audience01,
	Anim_Interlude_People2_Audience02,
	Anim_Interlude_Skip_But,
	Anim_Interlude_Next_But,
	Anim_Roulette_Count,
}RouletteTypeAnim;

enum
{
	RunAction_interlude_FunCb_Cloud1,
	RunAction_interlude_FunCb_Cloud2,
	RunAction_interlude_FunCb_Sun
};

class CandyInterlude:public CCLayer
{
public:
	CandyInterlude();
	~CandyInterlude();

public:
	virtual bool init();
public:
	virtual void onEnter(void);
	virtual void onExit(void);
	CREATE_FUNC(CandyInterlude);
	/**
     * Default constructor
	 */
public:
	static CCScene* scene(void);

protected:
	void RunActionFunND(CCNode* sender, void* data);
	void GloabActionStop(void);
	void GloabActionExit(void);
	void onmovementEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
	void onmovementEvent2(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);

	void InterludeButCallBack(CCObject *pSender);
public:
	UILayer* m_Interludelayer;
	Layout* m_pInterludeLayer;
	bool m_isLoop;
	int m_countnextNum;

};

#endif