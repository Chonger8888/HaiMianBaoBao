#ifndef CANDY_LICORICES__H
#define CANDY_LICORICES__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

class CandyLicorices
{
	public:
		CandyLicorices();
		~CandyLicorices();

	public:
		CandyCell* createLicorice(CandyIndex index);
		void createLicoricesWithMapData(void);
		bool isNeedToCreateNewLicorice(void);

	public:
		void removeLicorice(CandyIndex index);
		void dispelCandyEffectLicorice(CandyIndex dispelIndex);
		
	private:
		int getCurrentLicoricesNum(void);

	public:
		int currentLicoriceSpawn;
		
	public:
		static int licoriceMax;
		static int licoriceSpawn;
};


#endif