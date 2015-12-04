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
����Ҫ�ṩ���¹���:
0.createCandyWithMapData    ������ͼ��Ӧ��candy
1.isNeedToResortCandy: 	�жϵ�ͼ�ϵ�candy(�޷����������)�Ƿ���Ҫ����
2.resortCandyExecute: 		���ŵ�ͼ�ϵ�candy
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

		// �������
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
		// �ǹ���ʾ
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
	// �����㷨���
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
		CandyIndex dispelTips[3];		//��ʾ
		CandyIndex dispelFlag[3];		//�������ɿ�����
		CandyCell*  dispelTipsCandy[3];
		bool resortMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
		bool isResorting;
		bool resortRet;
};

#endif

