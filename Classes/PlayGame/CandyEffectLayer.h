#ifndef CANDY_EFFECT_LAYER__H
#define  CANDY_EFFECT_LAYER__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;

typedef enum
{
	CANDY_STRIPE_LEFT,
	CANDY_STRIPE_RIGHT,
	CANDY_STRIPE_UP,
	CANDY_STRIPE_DOWN
}CandyStripeDirection;

class CandyCell;

class CandyEffectLayer: public CCLayer
{
	public:
		CREATE_FUNC(CandyEffectLayer);
		~CandyEffectLayer();
		
	public:
		virtual bool init(void);
		virtual void onEnter(void);
		virtual void onExit(void);

	public:
		void displayEnergyJarEffect(void);
		void undisplayEnergyJarEffect(void);
		
	public:
		void displayExplosionBombEffect(CandyIndex index,CandyColor color);
		
	public:
		void displayExchangeCandyEffect(CandyIndex index);
		
	public:
		void displaySingleNormalDispelEffect(CandyIndex index);
		
	public:
		void displayBombDispelEffect(CandyIndex index);
		void displayHorizonDispelEffect(CandyIndex index, CandyColor color);
		void displayVerticalDispelEffect(CandyIndex index,CandyColor color);
		void displayCololfulDispelEffect(CandyIndex index);
		void displayCololfulMainEffect(CandyIndex index);
		void displayCololfulSubEffect(CandyIndex index);

	public:
		void displayColorEmit(CandyIndex index);
		void displayColorFire(CandyIndex origin, CandyIndex target, float delayTime);
		void displayColorFireDelayCb(CCNode* sender, void* data);
		void displayColorTarget(CandyIndex index, float delayTime);
		void displayColorTargetDelayCb(CCNode* sender, void* data);
	
	public:
		void displayComBBEffect(CandyIndex index, CCCallFuncN *cb);
		void displayComSSEffect(CandyIndex index,CandyColor colorH,CandyColor colorV);
		void displayComCCEffect(CCCallFuncN *cb);
		
	public:
		void displayComBSEffect1(CandyIndex index, CCCallFuncN *cb);

	public:
		void displayChangeStripleEffect(CandyIndex index);

	public:
		void displayRouleteeMakeColor(CandyIndex index);
		void displayRouleteeMakeBomb(CandyIndex index);
		void displayRouleteeMakeStrip(CandyIndex index);
		
	public:
		void displayBreakLicorices(CandyIndex index);
		void displayBreakCream(CandyIndex index);
		void displayBreakJelly(CandyIndex index, int jellyNum=1);
		void displayBreakLock(CandyIndex index);
		void displayBreakChocolate(CandyIndex index);

	public:
		void displayUsingPropEffect(int type);
		void displayUsingPropEffectCb0(CCNode* sender);
		void displayUsingPropEffectCb1(CCNode* sender);
		void displayUsingPropEffectCb2(CCNode* sender);
		void displayUsingPropEffectCb2_Hammer(CCNode* sender);

	public:
		void displayPropButtonEffect(void);
		void undisplayPropButtonEffect(void);
		void displayPropSelectCellEffect(int type);

	public:
		void displayHighLightFront(CCNode* sender);
		void displayStageClearTips(void);
		void displayStageClearTipsExtra(void);
		void displayStageClearEffect(CCNode* sender, void* data);
		void displayStageFailedTips(void);
		void displayStageFailedEffect(void);

	public:
		void displayCountDown(float time);
		void displayNumLabelChange(CCLabelAtlas *label);

	public:
		void displayUseStepChangeStripe(CandyIndex index);

	public:
		void displayTargetIconEffect(void);

	public:
		void displayStarLightEffect(CCNode *node);
		void displayStarLightEffectCallBack(CCNode *node);
		
	public:
		void displayEffectCallBack(CCNode* sender);

	public:
		void delayCallBack(float delay,CCCallFuncND *cb);

		void displayPropLightEffect(void);

		void animationEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
		void displayStageClearTipsExtraPre(void);
		void displayStageFailedTipsPre(void);
		void displayStageFailedCallback(void);

		//被选中的糖果加上框
		void AddWinForSelectCandy(CCPoint idxPos);
		void RemoveWinFromSelectCandy();
private:
		CCSprite *effectNode[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];

	private:
		int useStepCount;
		static CCSprite* m_SelectWin;
		
};

#endif
