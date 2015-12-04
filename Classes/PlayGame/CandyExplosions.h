#ifndef CANDY_EXPLOSIONS__H
#define CANDY_EXPLOSIONS__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

 // 定时炸弹管理
class CandyCell;


class CandyExplosions
{
	public:
		CandyExplosions();
		~CandyExplosions();
		
	public:
		void updateExplosions(void);
		
	public:
		bool isNeedToCreateNewExplosion(void);
		CandyCell* createExplosion(CandyIndex index);
		void createExplosionsWithMapData(void);

	public:
		void decreaseExplosionsTime(void);
		void decreaseExplosionsSpawn(void);

	public:
		void addExplosionsAnimation(CCNode*node, bool offsetFlag = false);
		
	public:
		CandyCell* getExplosionsCandy(void);
		bool isReadyToExplode(void);
	
	public:
		void setCandyExplosionTime(CandyCell *candy, int time);
	
	private:
		int getCurrentExplosionsNum(void);

	public:
		int currentExplosionSpawn;

		
	public:
		static int explosionMax;
		static int explosionTurns;
		static int explosionSpawn;
};


#endif
