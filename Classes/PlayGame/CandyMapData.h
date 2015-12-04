#ifndef CANDY_MAP_DATA__H
#define CANDY_MAP_DATA__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

typedef enum
{
	MAP_CELL_EXIST,		// ���Ӵ���
	MAP_CELL_CANDY,		//�������ǹ�
	MAP_CELL_JELLY1,		//  1�����
	MAP_CELL_JELLY2,		//  2�����
	MAP_CELL_FACTORY,		// ����Դͷ
	MAP_CELL_BARRIER,		//�����ɿ������͵��ϰ���ʶ
	MAP_CELL_CREAM1,		//һ������
	MAP_CELL_LOCK,			//����
	MAP_CELL_CHOCOLATA,	//�ɿ���
	MAP_CELL_INGREDIENT_EXIT,// ���ӵ�������Ʒ����
	MAP_CELL_EXIT_EMPTY,	//�����Ƿ���ֿո�
	MAP_CELL_DOWN_EMPTY,// ��Ϊ�տɵ���
	MAP_CELL_UP_EMPTY		,//  ��Ϊ�տɵ���
	MAP_CELL_LICORICE =16, //�ʲ�
	MAP_CELL_EXPLOSION,		//��ʱը��
	MAP_CELL_CREAM2 =19,		//��������
	MAP_CELL_CREAM3 =20,		//��������
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