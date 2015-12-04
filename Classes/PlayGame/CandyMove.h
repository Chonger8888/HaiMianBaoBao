#ifndef CANDY_MOVE__H
#define CANDY_MOVE__H

#include "cocos2d.h"
#include "CandyCommon.h"

//���ƶ��ǹ�

USING_NS_CC;

typedef enum
{
	CHANGE_MODE_BY_USER,			//�û���ͨ����
	CHANGE_MODE_BY_SYS,			//ϵͳ����
	CHANGE_MODE_BY_ANYWAY,		//����ģʽ�£��������
}CandyChangeMode;

class CandyMove
{
	public:
		CandyMove();
		~CandyMove();
	public:
		void moveCandy(CandyIndex first, CandyIndex second, CandyChangeMode mode);
		void updateCandyMove(void);

	public:
		void moveDone(void);
		
	private:
		bool moveFlag;
		CandyIndex firstMove;
		CandyIndex secondMove;
		CandyChangeMode moveMode;

	private:
		int warningMoveNum;
		
	public:
		static int moveLimit;
};

#endif