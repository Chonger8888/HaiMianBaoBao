#ifndef CANDY_CHOCOLATE__H
#define CANDY_CHOCOLATE__H


// �ɿ������
#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyChocolateCell : public CCSprite
{
	public:
		// �����ɿ���
		static CandyChocolateCell* create(CandyIndex index, bool runAction =false);

	public:
		void runBornAction(void);

	private:
		CandyIndex index;
	
};

class CandyChocolate
{
	public:
		CandyChocolate();
		~CandyChocolate();
		
	public:
		void createChocolatesWithMapData(void);
		void addCandyChocolateCell(CandyIndex index, bool runAction = false);
		
	public:
		void updateCandyChocolate(void);
		
	public:
		bool removeCandyChocolateCell(CandyIndex index);
		void dispelCandyEffectChocolate(CandyIndex dispelIndex);

	public:
		void resetDispelChocolateFlag(void);

	public:
		CandyChocolateCell* getCandyChocolateCell(CandyIndex index);
		
	private:
		void swallowCandy(void);
		bool checkSwallowCandy(CandyIndex index);
		
	private:
		CandyChocolateCell* chocolateInMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];

	private:
		bool dispelChocolate;
};

#endif