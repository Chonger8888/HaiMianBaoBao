#ifndef CANDY_LOCK__H
#define CANDY_LOCK__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyLockCell:public CCSprite
{
	public:
		static CandyLockCell* create(CandyIndex index);

	private:
		CandyIndex index;
		
};

class CandyLock
{
	public:
		CandyLock();
		~CandyLock();

	public:
		void createLocksWithMapData(void);
		void addCandyLockCell(CandyIndex index);
		void removeCandyLockCell(CandyIndex index);
		CandyLockCell* getLockCell(CandyIndex index);

	public:
		CandyLockCell* lockInMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
};

#endif