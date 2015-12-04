#ifndef CANDY_TARGET__H
#define CANDY_TARGET__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

#define TARGET_NODE_LABEL_TAG		720

typedef enum
{
	LOSE_TARGET_NOT_YET,
	LOSE_TARGET_EXPLOSION,
	LOSE_TARGET_NO_MOVE,
	LOSE_TARGET_NO_TIME,
}LoseTargetType;



class CandyTarget:public CCObject
{
	public:
		CandyTarget();
		~CandyTarget();

	public:
		bool getReachingTarget(void);
		LoseTargetType getLosingTarget(void);

	public:
		void runTargetTipsAction(void);
		void targetTipsActionCallback(void);

	private:
		void createTargetNode(CCNode *parent);
		void runTargetNodeAction(void);
		void targetNodeActionCallback(CCNode* sender);
		
	public:
		static CCSprite *targetBg;

	private:
		CCPoint targetNodePos[3];
		CCNode *targetNode[3];
		int targetNodeNum ;
};

#endif
