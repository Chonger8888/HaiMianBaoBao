#ifndef CANDY_GUIDE_LAYER__H
#define CANDY_GUIDE_LAYER__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;

#define CANDY_GUIDE_MAX_STEP	4

typedef struct
{
	int 			totalSteps;
	int			highLightNum[CANDY_GUIDE_MAX_STEP];
	CandyIndex	highLightArea[CANDY_GUIDE_MAX_STEP][6];
	CandyIndex	targetIndex[CANDY_GUIDE_MAX_STEP][2];
}CandyGuideStr;

class CandyGuideLayer: public CCLayer
{
	public:
   		CREATE_FUNC(CandyGuideLayer);

	public:
		virtual bool init(void); 
		virtual void onEnter(void);
		virtual void onExit(void);
		
	public:
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	public:
		virtual void update(float time);

	public:
		bool getGuiding(void);
		
	private:
		void initGuideData(void);
		void setGuiding(bool states);
		bool getShowExample(void);
		void finishCurrentStep(void);
		
	private:
		void createDisplayGuide(void);
		void doDisplayGuide(void);
		void unDisplayGuide(void);

	private:
		void updateGuideSprite(void);
		void updateGuideMan(void);
		void updateGuideFont(void);
		void updateGuideFinger(void);
		void updateGuideExample(void);
		
	private:
		CCSprite* createGuideFont(void);
		void setGuideFontPos(void);
		void setTeacherPos(void);
			
	private:
		CCSprite* createGuideSprite(void);
		CCDrawNode* createHighLightArea(void);
		CCDrawNode* createStepAndTargetHighLightArea(bool showStep, bool showTarget);

	private:
		void createGuideExample5(void)  ;
		void createGuideExample9(void);
		void createGuideExample16(void) ;
		void createGuideExample31(void) ;
		void createGuideExample46(void) ;
		void createGuideExample61(void) ;
		void createGuideExample76(void) ;
		void createGuideExample91(void) ;
		void createGuideExample136(void);
		void createGuideExample181(void);

	private:
		void displayGuideFingerEffect(CCNode* sender);

	private:
		void exampleCompleteCallBack(CCNode* sender);
		void createISeeButton(void);
		void ISeeButtonCallback(CCObject* pSender);

		void createSkipButton(void);
		void SkipButtonCallback(CCObject* pSender);

		void StartAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
public:	
		int 	currentStep;
private:
		bool isGuiding;
		CandyGuideStr guideData;

	private:
		bool isDisplaying;
		UILayer* guideUiLayer;
		CCSprite* guideSprite;
		CCSprite* guideFont;
		CCSprite* guideMan;
		CCSprite* guideFinger;

		CCArmature*		guideTaech;
	private:
		CandyIndex 	firstTouchCandy;
		CandyIndex 	secondTouchCandy;
		CandyIndex	secondTargetCandy;
		bool 		moveableStates;

};

#endif
