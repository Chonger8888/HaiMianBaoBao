#ifndef CANDY_MAP_DATA__H
#define CANDY_MAP_DATA__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

typedef enum
{
	MAP_CELL_EXIST,		// 格子存在
	MAP_CELL_CANDY,		//格子有糖果
	MAP_CELL_JELLY1,		//  1层果冻
	MAP_CELL_JELLY2,		//  2层果冻
	MAP_CELL_FACTORY,		// 生产源头
	MAP_CELL_BARRIER,		//存在巧克力奶油等障碍标识
	MAP_CELL_CREAM1,		//一层奶油
	MAP_CELL_LOCK,			//锁链
	MAP_CELL_CHOCOLATA,	//巧克力
	MAP_CELL_INGREDIENT_EXIT,// 栗子等特殊物品出口
	MAP_CELL_EXIT_EMPTY,	//上下是否出现空格
	MAP_CELL_DOWN_EMPTY,// 下为空可掉落
	MAP_CELL_UP_EMPTY		,//  上为空可掉落
	MAP_CELL_LICORICE =16, //甘草
	MAP_CELL_EXPLOSION,		//计时炸弹
	MAP_CELL_CREAM2 =19,		//二层奶油
	MAP_CELL_CREAM3 =20,		//三层奶油
}MapCellType;

class CandyMapData
{
	public:
		CandyMapData(); 
		~CandyMapData();
		
	public:
		bool getMapCellStates(CandyIndex index, MapCellType type);
		void setMapCellStates(CandyIndex index, MapCellType type, bool states);

	public:
		CCDrawNode* getMapShape(void);
		
	private:
		void initMapDataFromLua(void);
	
	public: 
		static void initLoadLuaFile(void);
		static int getTargetScore(int stage, int starNum =1);	
		static int getTargetMode(int level);
		static void getMapdataFromLua(int level);
		
	public:	
		static unsigned int getTableNumFromLua(int num);
		static unsigned int getNumFromLua(char *name);
		
	public:
		CandyCell* getCandyByIndex(CandyIndex index);
		void setCandyByIndex(CandyIndex index, CandyCell *candy,bool changePos = true,bool resetOrigin = true);
	private:
		unsigned int mapData[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];
		CandyCell* candyInMap[CANDY_MAP_HEIGH][CANDY_MAP_WIDTH];

	public:
		bool candyDropMode;
}; 

#endif