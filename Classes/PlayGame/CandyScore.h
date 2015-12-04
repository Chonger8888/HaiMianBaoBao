#ifndef CANDY_SCORE__H
#define CANDY_SCORE__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

#define DIFFERENCE_DATA		222
class CandyScore
{
	public:
		CandyScore();
		~CandyScore();

	public:
		void updateCandyScore(void);
		
	public:
		void updateStarScoreProgressBar(void);

	public:
		int getCurrentScore(void);
		
	public:
		int getComboNumber(void);
		void increaseComboNumber(void);

	public:
		void addCandyScore(int score, CCPoint pos, CandyColor color = CANDY_COLOR_RED);

	public:
		void setAccumulateScoreFlag(bool state, bool display=false);
		
	private:
		void displayCandyScore(int score, CCPoint pos, CandyColor color= CANDY_COLOR_RED);
		void displayCandyScoreCallBack(CCNode* sender);
		
public:
		bool accumulateFlag;
		int accumulateScore;
		int comboNumber;
		int totalScore;
		CCLabelTTF *totalScoreLabel;

	private:
		const int candyBaseScore;

	private:
		CCProgressTimer *oneStar;
		CCProgressTimer *twoStar;
		CCProgressTimer *threeStar;

	public:	
		static int starScoreNum[3];
};

#endif