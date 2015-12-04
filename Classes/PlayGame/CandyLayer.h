#ifndef CANDY_MAP__H
#define CANDY_MAP__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CandyCell;

/*
CandyLayer  ÓÎÏ·ÖÐÌÇ¹û²ã
*/

class CandyLayer : public CCLayer
{
	public:
   		CREATE_FUNC(CandyLayer);
		
	public:
		virtual bool init(void); 
		virtual void onEnter(void);
		virtual void onExit(void);
		
	public:
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	public:
		CCNode* getCandyParent(void);
		void addToCandyParent(CandyCell *candy);
		CCClippingNode * getClipper(void);
		CCSpriteBatchNode* getCandyElementBatchNode(void);

		void addToCandyElementBatchNode(CandyCell *candy);
		void addToCandyBarrierTopBatchNode(CCNode *node, int order =0);
		void addToCandyBarrierBottomBatchNode(CCNode *node, int order =0);
		
	public:
		void runResortCandyLightning(CCNode* sender, void* data);
		void runResortCandyFade(CCNode* sender, void* data);
		void runFadeAction(CCNode *node, bool inFlag, float delay);
		void runResortCandyAction(void);
		void resortCandyStart(void);
		void resortCandyEnd(void);
		void resortCandyLightningCallBack(CCNode* sender);
		void resortCandyFadeOutCallback(void);
		void resortCandyFadeInCallback(void);

	public:
		void layerActionCallback(void);
		
	private:
		CandyIndex 	firstTouchCandy;
		CandyIndex 	secondTouchCandy;
		bool 			moveableStates;

	private:
		CCClippingNode *clipper;
		CCSpriteBatchNode *candyElementBatchNode;
		CCSpriteBatchNode *candyBarrierTopBatchNode;
		CCSpriteBatchNode *candyBarrierBottomBatchNode;
};

#endif
