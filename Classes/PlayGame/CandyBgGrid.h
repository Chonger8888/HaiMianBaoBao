#ifndef CANDY_BG_GRID__H
#define CANDY_BG_GRID__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyBgGrid
{
	public:
		CandyBgGrid();
		~CandyBgGrid();

	public:
		void createBgGrid(void);
		void createGridsVisit(float offsetX =0, float offsetY = 0);
		void removeBgGrid(void);
		
	private:
		unsigned int getCrossGridData(CandyIndex index);
		
		bool getCrossGridIndex(CandyIndex &index);
		
		void createNormalGridCellVisit(CandyIndex index);

		//边缘格子分四个小格子，左上、左下、右上、右下
		void createEmptyEdgeGridCellVisit(CandyIndex index, bool leftup, bool leftdown, bool rightup, bool rightdown);

	private:
		//标识格子上下左右是否存在非0格子
		unsigned int up;
		unsigned int down;
		unsigned int left;
		unsigned int right;
		unsigned int leftUp;
		unsigned int rightUp;
		unsigned int leftDown;
		unsigned int rightDown;

	private:
		float gridOffsetX;
		float gridOffsetY;
};

#endif

