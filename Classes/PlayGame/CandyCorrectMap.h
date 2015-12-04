#ifndef CANDY_CORRECT_MAP__H
#define CANDY_CORRECT_MAP__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;
class CandyDispelCell;

typedef struct
{
	CandyColor 	color;
	int			num;
}CandyCount;

/*
，主要提供以下功能:
0.createCandyWithMapData    创建地图对应的candy
1.isNeedToResortCandy: 	判断地图上的candy(无法消除情况下)是否需要重排
2.resortCandyExecute: 		重排地图上的candy
*/
class CandyCorrectMap
{
	public:
		CandyCorrectMap();
		~CandyCorrectMap();

	public:
		void updateCandyCorrectMap(void);
		
	public:
		void createCandyWithMapData(int typeNum);

		// 重排相关
	public:
		bool isNeedToResortCandy(void);
		bool getStatesFromResortMap(CandyIndex index);
		bool resortCandyInit(bool changeLock);
		bool resortCandyExecute(bool changeLock);
	public:
		bool getResortState(void);
		void setResortState(bool state);
		bool getResortResult(void);
		void setResortResult(bool ret);
		// 糖果提示
public:
	void displayCandyDispelTips(void);
	void cancelCandyDispelTips(float dt=0);
	bool isDispelTipsCandy(CandyCell *candy);
	void setDisplayCandyDispelTipsFlag(bool flag);
private:
	bool isCandyDispelByMove(CandyCell *candy, CandyIndex changeIndex);
	bool isCandySpecialDispelByMove(CandyCell *candy, CandyIndex changeIndex);
	bool getMapDispelFlagByIndex(CandyIndex index, int horizontal, int verticcal);
	bool getMapDispelFlag(void);
	bool setCandyCanDispel(void);
	// 重排算法相关
	private:
		void getColorCount(bool fromArray);
		void sortColorCount(void);
		CandyCell* getCandyInArrayByColor(CandyColor color);
		bool setCandyByIndexAndCheckDispel(CandyIndex index, CandyCell* candy);
		bool isSuccessToSetCandyByIndex(CandyIndex index);
		void exchangeAvailableCandy(CandyIndex index);
		
	private:
		void setDispelTipsIndex(CandyDispelCell *dispel);

	private:
		void backTrackingResort(void);
		CandyCell* backTrackingGetCandy(int &x, int &y);
		bool backTrackingIndex(int &x, int &y);
		bool backTrackingGetNextColor(int &x, int& y);
		
	private:
		int startColor[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
		int currentColor[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];

	private:
		CCArray *sortArray;
		bool displayTipsFlag;
		CandyCount colorCout[CANDY_COLOR_NORMAL_NUM];
		CandyIndex dispelTips[3];		//提示
		CandyIndex dispelFlag[3];		//重新生成可消除
		CandyCell*  dispelTipsCandy[3];
		bool resortMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
		bool isResorting;
		bool resortRet;
};

#endif

