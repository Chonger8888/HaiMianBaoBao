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
candy������Ԫ�࣬��Ҫ��¼������λ��
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
candy ��������࣬��Ҫ�ṩ���¹���:
1.addCandyToChangeArray ->���candy ��changedArray ( ����λ�ñ仯��candy����)
2.checkCandyDispel -> ���candy �����������򷵻�CandyDispelCell ��Ϣ
3.checkChangeArrayDispel -> ���changedArray,��������Ϣ��ӵ�dispelArray����

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
		//��齻�������Ƿ��п���������candy
		void checkChangeArrayDispel(void);
		//���ؿ���������candy
		CandyDispelCell* checkCandyDispel(CandyCell* candy);
		//�������������ǹ�
		void updateCandyDispel(void);
		
	public:
		bool dispelSingleCandy(CandyCell* candy, bool checkSpecial=true);
		int specialDispelSingleCandy(CandyIndex index, bool displayScore = false); //����������
		int specialDispelCandyByProp(CandyIndex index,bool displayScore);

	public:
		bool getDispelStateByChangeCandy(CandyIndex index1 ,CandyIndex index2); 
			
	private:
		
		bool isDispelContainsDispel(CandyDispelCell* dispel1, CandyDispelCell* dispel2);// dispel1  �Ƿ���� dispel2
		void removeRedundantDispel(void);

	private:
		CandyIndex checkToCreateNewCandy(CandyDispelCell* dispel);
		//��������Ѱ��ͬ��ɫ��candy
		bool checkCandyColorByIndex(CandyIndex index, CandyColor color);

	private:
		//������������������ǹ�
		void getNewBornSpecialCandy(CandyDispelCell* dispel, NewBornCandy &newBornCandyInfo);
		void createNewBornSpecialCandy(NewBornCandy &newBornCandyInfo);

	private:
		void resetDispelNum(void);
		//����ĳ��candy
		void normalDispelCandy(CandyCell *dispelCandy);
		//��������һƬ��candy
		void doNormalDispel(CandyDispelCell* dispel, NewBornCandy* newBorn);

	private:
		CCArray *changedArray;		//����λ�ñ仯��candy����
		CCArray *dispelArray;		//��������Ԫ�����
		CCArray* redundantArray;	//�ظ������������Ԫ����

	private:
		int dispelJellyNum;
		int dispelExplosionNum;
};

#endif
