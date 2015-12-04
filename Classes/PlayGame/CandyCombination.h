#ifndef CANDY_COMBINATION__H
#define CANDY_COMBINATION__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

class CandyCombination
{
	public:
		CandyCombination();
		~CandyCombination();

	public:
		bool getCombinationActionDone(void);
		void updateCandyCombination(void);

	public:
		void addActivedCombination(CandyCell *candy);
		bool activedCombinationContainsCandy(CandyCell *candy);
		void removeActivedCombination(CandyCell *candy);

	public:	
		bool checkCandyCombination(CandyCell *candy1, CandyCell *candy2);
		bool isSpecialCombination(CandyCell *candy1, CandyCell *candy2 );

	public:
		void runCandyCombination(CandyCell *candy1, CandyCell *candy2);

	public:
		void runCombinationCC(CandyCell *candy1, CandyCell *candy2);
		void runCombinationCS(CandyCell *candy1, CandyCell *candy2);
		void runCombinationCB(CandyCell *candy1, CandyCell *candy2);
		void runCombinationSS(CandyCell *candy1, CandyCell *candy2);
		void runCombinationSB(CandyCell *candy1, CandyCell *candy2);
		void runCombinationBB(CandyCell *candy1, CandyCell *candy2);
		void runCombinationCN(CandyCell *colorfulCandy);

	public:
		void runComCNEffect(CandyCell *colorfulCandy, CandyColor dispelColor);
		
	public:
		void comCNEffectCB(CCNode* sender, void* data);
		void comBBEffectCB(CCNode* sender);
		void comSBEffectCB(CCNode* sender);
		void comCCEffectCB(CCNode* sender);
		
	public:
		CandyIndex targetIndex;
		CandyComType combinationType;

	public:
		CandyCell *comCandy1;
		CandyCell *comCandy2;
		
	private:
		CCArray *combinationArray;
};

#endif
