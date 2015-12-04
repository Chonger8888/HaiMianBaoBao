#ifndef CANDY_DISPEL__H
#define CANDY_DISPEL__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

typedef struct
{
	CandySpecial 	special;
	CandyColor 	color;
	CandyIndex 	index;
	bool 			flag;
}NewBornCandy;



/*
candy消除单元类，主要记录消除的位置
*/
class CandyDispelCell : public CCObject
{
	public:
		static CandyDispelCell* create(CandyIndex index);

	public:
		CandyIndex index;
		int left;
		int right;
		int up;
		int down;
};




/*
candy 检测消除类，主要提供以下功能:
1.addCandyToChangeArray ->添加candy 到changedArray ( 发生位置变化的candy队列)
2.checkCandyDispel -> 检测candy ，若可消除则返回CandyDispelCell 信息
3.checkChangeArrayDispel -> 检测changedArray,将消除信息添加到dispelArray队列

*/
class CandyDispel
{
	public:
		CandyDispel();
		~CandyDispel();

	public:
		void removeCandyFromChangeArray(CandyCell* candy);
		void addCandyToChangeArray(CandyCell* candy);
	public:
		//检查交换队列是否有可以消除的candy
		void checkChangeArrayDispel(void);
		//返回可以消除的candy
		CandyDispelCell* checkCandyDispel(CandyCell* candy);
		//　消除更新新糖果
		void updateCandyDispel(void);
		
	public:
		bool dispelSingleCandy(CandyCell* candy, bool checkSpecial=true);
		int specialDispelSingleCandy(CandyIndex index, bool displayScore = false); //　特殊消除
		int specialDispelCandyByProp(CandyIndex index,bool displayScore);

	public:
		bool getDispelStateByChangeCandy(CandyIndex index1 ,CandyIndex index2); 
			
	private:
		
		bool isDispelContainsDispel(CandyDispelCell* dispel1, CandyDispelCell* dispel2);// dispel1  是否包含 dispel2
		void removeRedundantDispel(void);

	private:
		CandyIndex checkToCreateNewCandy(CandyDispelCell* dispel);
		//上下左右寻找同颜色的candy
		bool checkCandyColorByIndex(CandyIndex index, CandyColor color);

	private:
		//　获得重新生成特殊糖果
		void getNewBornSpecialCandy(CandyDispelCell* dispel, NewBornCandy &newBornCandyInfo);
		void createNewBornSpecialCandy(NewBornCandy &newBornCandyInfo);

	private:
		void resetDispelNum(void);
		//消除某个candy
		void normalDispelCandy(CandyCell *dispelCandy);
		//消除连成一片的candy
		void doNormalDispel(CandyDispelCell* dispel, NewBornCandy* newBorn);

	private:
		CCArray *changedArray;		//发生位置变化的candy队列
		CCArray *dispelArray;		//可消除单元类队列
		CCArray* redundantArray;	//重复多余的消除单元队列

	private:
		int dispelJellyNum;
		int dispelExplosionNum;
};

#endif
