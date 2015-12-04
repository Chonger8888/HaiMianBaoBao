#ifndef CANDY_CELL__H
#define CANDY_CELL__H


// �ǹ�������� �� ����  ����  
#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

//�ǹ�״̬
typedef enum
{
	CANDY_CELL_NORMAL = 0,	
	CANDY_CELL_MOVING,
	CANDY_CELL_DELETING,
	CANDY_CELL_DROPING,
	CANDY_CELL_SLIDEING,
	CANDY_CELL_PORTALING,
	CANDY_CELL_NEW_PORTALING,
	CANDY_CELL_EFFECTING,//��Ч ��ը+��ը��� 
	CANDY_CELL_DELAY_DELETING,
	CANDY_CELL_DELAY_CHANGING,
}CandyCellState;

class CandyCell : public CCSprite
{
	public:
		static CandyCell* create(CandyIndex index, CandyColor color, CandySpecial special);
		static void CreateNewCandySpecial(CandyIndex index, CandySpecial newSpecial);

	private:
		static char* getCandyImgName(CandyColor color, CandySpecial special);
		
	public:
		virtual void onEnter(void);
		virtual void onExit(void);
		virtual void update(float time);

	private:
		void runSpecialAnimation(void);
		void runAnimation(void);
		
	public:

		// ���������ǹ�
		CandyCell* changeCandySpecial(CandySpecial newSpecial, bool displayEffect =true);
		void runCandyChangeSpecialDelay(CandySpecial newSpecial, float time);

		// ��������ʱ����Ч
		void displayNewSpecialEffect(void);

		//�������ǹ���Ч
		void displaySpecialCandyEffect(void);
		int getSpecialCandyEffectIndex(void);
		
	public:
		static CandyCell* getRandomNormalCandy(void);
		
		// ���Ƕ������
	public:
		//�����ƶ�
		void runCandyMoveAction(CandyIndex movetIndex);
		//��б�·�����
		void runCandySlideAction(CandyIndex slideIndex, CandyIndex dropIndex, bool dopFlag);// ����
		void runCandyDeleteAction(void);// ����
		void runCandyPortalAction(CandyIndex portalIndex);// ������
		void runCandyDelayDelete(float time, int score=0); // ��ʱ����
		void runCandyDropAction(CandyIndex droptIndex, bool changeLastIndex = true);// ���µ�
		
	private:
		void candyMoveActionCallBack(void);
		void candySlideActionCallBack(void);
		void candyDeleteActionCallBack(void);
		void candyPortalActionCallBack(void);
		void candyDelayDeleteActionCallBack(CCNode* sender, void* data);
		void candyChangeSpecialDelayCallBack(CCNode* sender, void* data);

	private:
		void updateDropPos(float time);
		void checkCandyDropStatus(void);
		void dropAjustActionCallBack(void);

	public:

		void runCandyNewPortalAction(CandyIndex portalOrigin, CandyIndex portalTarget);

	private:
		CCFiniteTimeAction*  getCandyNewPortalAction(void);
		CCFiniteTimeAction*  getCandyNewPortalReverseAction(void);
		void newPortalActionCallback(void);
		void newPortalReverseActionCallback(void);
		
	public:
		void setCandyStates(CandyCellState  type, bool states);
		bool getCandyStates(CandyCellState  type);

	public:
		void setCandyProduceFlag(CandyIndex index);

	public:
		void removeFromArray(void);
		
	public:
		void destroyCandy(void);
		
	public:
		CandyIndex 	index;
		CandyColor 	color;
		CandySpecial 	special;

		//������ɫ
		CandyColor 	extraColor;

	private:
		float currentSpeed;
		float dropTargetY;
		bool slideToDrop;
		//��һ��λ��
		CandyIndex lastIndex;
		
/*���ڴ����ŵ�����ؿ���Ҫ*/
	private:
		bool produceFlag;
		CandyIndex visibleIndex;
			
	private:
		unsigned int stateValue;
		
	private:
		CandyIndex newPortalOrigin;
		CandyIndex newPortalTarget;
		
};


#endif
