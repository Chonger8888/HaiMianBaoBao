#ifndef CANDY_MOVE__H
#define CANDY_MOVE__H

#include "cocos2d.h"
#include "CandyCommon.h"

//　移动糖果

USING_NS_CC;

typedef enum
{
	CHANGE_MODE_BY_USER,			//用户普通交换
	CHANGE_MODE_BY_SYS,			//系统交换
	CHANGE_MODE_BY_ANYWAY,		//特殊模式下，任意更换
}CandyChangeMode;

class CandyMove
{
	public:
		CandyMove();
		~CandyMove();
	public:
		void moveCandy(CandyIndex first, CandyIndex second, CandyChangeMode mode);
		void updateCandyMove(void);

	public:
		void moveDone(void);
		
	private:
		bool moveFlag;
		CandyIndex firstMove;
		CandyIndex secondMove;
		CandyChangeMode moveMode;

	private:
		int warningMoveNum;
		
	public:
		static int moveLimit;
};

#endif