#ifndef CANDY_SPECIAL_MANAGER__H
#define CANDY_SPECIAL_MANAGER__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

class CandySpecialManager
{
	public:
		CandySpecialManager();
		~CandySpecialManager();

	public:
		void updateActivedSpecial(float time);
		bool runSpecialCandy(CandyCell *candy, bool increaesEnergy = false);

	public:
		bool activedSpecialContainsCandy(CandyCell *candy);
		void addActivedSpecial(CandyCell *candy);
		void removeActivedSpecial(CandyCell *candy);

	public:
		bool activeSpecialCandyInMap(int num);
		
	public:
		void runSpecialBomb(CandyIndex index, CandyColor color, bool skipCenter,  int externScore =0);
		void runSpecialHorizontal(CandyIndex index, CandyColor color, bool display = true);
		void runSpecialVertical(CandyIndex index, CandyColor color,bool display = true);

	public:
		bool stripeDispelCandyDelay(CandyIndex index, float delay);
		void stripeDispelEmptyCallBack(CCNode* sender, void* data);

	public:
		void setDisplayEffectTime(float time);
		bool displayingEffect(float time);
		
	private:
		CCArray *activedSpecialArray;//存储会触发特殊效果的candy

	private:
		float displayEffectTime;
};

#endif