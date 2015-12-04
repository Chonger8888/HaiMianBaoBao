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

		//��Ե���ӷ��ĸ�С���ӣ����ϡ����¡����ϡ�����
		void createEmptyEdgeGridCellVisit(CandyIndex index, bool leftup, bool leftdown, bool rightup, bool rightdown);

	private:
		//��ʶ�������������Ƿ���ڷ�0����
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

