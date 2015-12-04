#ifndef CANDY_CREAM__H
#define CANDY_CREAM__H


// длсм
#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCreamCell : public CCSprite
{
	public:
		static CandyCreamCell* create(CandyIndex index, int layerNum);
		static char *getCreamImgName(int layerNum);

	private:
		CandyIndex index;
		int layerNum;
	
};

class CandyCream
{
	public:
		CandyCream();
		~CandyCream();

	public:
		void createCreamsWithMapData(void);
		void addCandyCreamCell(CandyIndex index, int layerNum);
		bool removeCandyCreamCell(CandyIndex index);
		CandyCreamCell* getCandyCreamCell(CandyIndex index);
		void dispelCandyEffectCream(CandyIndex dispelIndex);
		
		
	public:
		CandyCreamCell* creamInMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
};

#endif