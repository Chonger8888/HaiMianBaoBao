#ifndef CANDY_CELL__H
#define CANDY_CELL__H


// 糖果主角相关 ： 动作  生成  
#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

//糖果状态
typedef enum
{
	CANDY_CELL_NORMAL = 0,	
	CANDY_CELL_MOVING,
	CANDY_CELL_DELETING,
	CANDY_CELL_DROPING,
	CANDY_CELL_SLIDEING,
	CANDY_CELL_PORTALING,
	CANDY_CELL_NEW_PORTALING,
	CANDY_CELL_EFFECTING,//特效 爆炸+爆炸组合 
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

		// 生成特殊糖果
		CandyCell* changeCandySpecial(CandySpecial newSpecial, bool displayEffect =true);
		void runCandyChangeSpecialDelay(CandySpecial newSpecial, float time);

		// 生成特殊时的特效
		void displayNewSpecialEffect(void);

		//　特殊糖果特效
		void displaySpecialCandyEffect(void);
		int getSpecialCandyEffectIndex(void);
		
	public:
		static CandyCell* getRandomNormalCandy(void);
		
		// 主角动作相关
	public:
		//交换移动
		void runCandyMoveAction(CandyIndex movetIndex);
		//向斜下方落下
		void runCandySlideAction(CandyIndex slideIndex, CandyIndex dropIndex, bool dopFlag);// 滑动
		void runCandyDeleteAction(void);// 消除
		void runCandyPortalAction(CandyIndex portalIndex);// 传关门
		void runCandyDelayDelete(float time, int score=0); // 延时消除
		void runCandyDropAction(CandyIndex droptIndex, bool changeLastIndex = true);// 往下掉
		
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

		//附加颜色
		CandyColor 	extraColor;

	private:
		float currentSpeed;
		float dropTargetY;
		bool slideToDrop;
		//上一次位置
		CandyIndex lastIndex;
		
/*由于传送门等特殊关卡需要*/
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
