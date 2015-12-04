#ifndef CANDY_ROULETTE__H
#define CANDY_ROULETTE__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;


class CandyCell;

class CandyRouletteLayout:public CCObject
{
	public:
		CandyRouletteLayout();

	public:
		Layout* getRouletteLayout(void);
		void releaseRouletteLayout(void);

	private:
		void rouletteButtonCallback(CCObject *pSender);

	private:
		int adjustRouletteProbability(void);
		
	private:
		void rotateMusicCallback(void);
		void rouletteInCallback(void);
		void rotateDoneCallback(void);
		void rouletteOutCallback(void);

		
	public:
		Layout		*rouletteLayout;
		UIButton 	*rouletteStart;
		UIImageView	*rouletteBg;
		UIImageView	*rouletteNum;
		UIImageView	*rouletteType;

	public:
		CCPoint			roulettePos;
		float 			rouletteNumRotate;
		float 			rouletteTypeRotate;

		int				rouletteSpecialNum;
		int 				rouletteSpecialtype;
		
};

class CandyRoulette
{
	public:
		static Layout* getLayout(void);
		static void releaseLayout(void);
		static void startRunRoulette(void);
	public:
		static CandyRouletteLayout* layout;
		
};

#endif
