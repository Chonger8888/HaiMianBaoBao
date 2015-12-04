#ifndef CANDY_SHARE__H
#define CANDY_SHARE__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

class CandyShare:CCObject
{
	public:
		CandyShare();
		~CandyShare();

	public:
		void updateCandyShare(void);
		
	public:
		void initPos(void);
		int getOffsetXForMakeCenter(void);
		int getOffsetYForMakeCenter(void);

	public:
		//判断两个格子是否相邻
		bool isTwoIndexNeighbour( CandyIndex first, CandyIndex second );

	public:
		//糖果是否处于稳定静止状态
		bool getCandyIdle(void);
		bool getAllCandyStopAction(bool ingoreBombing=true);

	public:
		static float getFixedScreenHeight(void);
			
	public:
		CCPoint getPosByIndex(CandyIndex index);
		bool getIndexByPos(CCPoint point, CandyIndex &index);
	
	public:
		bool getLayerIncludeCandy(CandyCell *candy);

	public:
		void updateCollectNum(CandyCollectType type);
		void collectCandy(CandyCell *candy, CandyComType comType = CANDY_COM_NUM);
		void collectCandyActive(CandyCell *candy, CandyCollectType comType);
		void callfuncCollectCandy(CCNode* sender, void* data);

	public:
		CandyColor getCandyRandomColor(void);
		CandyColor getCandyRandomColorByLua(void);
	public:
		CCActionInterval * getEffectBezierAction(CCPoint originPos, CCPoint targetPos);
		
	public:
		static void changeColor(CandyColor color, ccColor4F& ret);

	public:
		CCPoint leftUpPos;
		CCPoint leftDonwPos;
		CCPoint rightUpPos;
		CCPoint rightDonwPos;


	private:
		int newRandSeed;
		int currentRandSeed;

};

#endif
