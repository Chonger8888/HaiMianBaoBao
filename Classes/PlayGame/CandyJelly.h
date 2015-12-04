#ifndef CANDY_JELLY__H
#define CANDY_JELLY__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyJelly
{
	public:
		CandyJelly();
		~CandyJelly();

	public:
		void createCandyJellys(void);
		bool removeCandyJellyOne(CandyIndex index, bool displayScore = false);

	public:
		int getCandyJellyRemainNum(void);
		int getCandyJellyTotalNum(void);
		
	private:
		void addCandyJelly(CandyIndex index, int jellyLayerNum);
		int getCandyJellyLayerNum(CandyIndex index);

	private:
		int jellyTotalNum;
		
	private:
		CCSprite* jellyInMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
};

#endif