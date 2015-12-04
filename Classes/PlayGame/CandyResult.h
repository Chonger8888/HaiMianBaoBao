#ifndef CANDY_RESULT__H
#define CANDY_RESULT__H

#include "cocos2d.h"
#include "CandyCommon.h"
#include "CandyTarget.h"
#include "../MsgMgr/AnalyseJson.h"

USING_NS_CC;
using namespace cocos2d::extension;


typedef enum
{
	//������Ϸ
	CANDY_RESULT_PLAYING,
	//���������ǹ�
	CANDY_RESULT_ACTIVE_SPECIAL,
	//��ʱ״̬
	CANDY_RESULT_ACTIVE_SPECIAL_DELAY,
	//���ط��̻�
	CANDY_RESULT_CLEAR_TIPS,
	//��ʱ״̬
	CANDY_RESULT_STAGE_DELAY,
	CANDY_RESULT_NO_TIME_DELAY,		
	CANDY_RESULT_NO_MOVE_DELAY,		
	CANDY_RESULT_EXPLOSION_DELAY,	
	CANDY_RESULT_USE_STEPS_DELAY,
	//ʣ�²���ת�������ǹ�
	CANDY_RESULT_USE_STEPS,
	//û�дﵽĿ��
	CANDY_RESULT_LOSE_TARGET,
	//ʱ�����
	CANDY_RESULT_NO_TIME,
	//û�в���
	CANDY_RESULT_NO_MOVE,
	//�޷�����
	CANDY_RESULT_NO_DISPEL,
	//��ͣ
	CANDY_RESULT_PAUSE,
	//��ʱը����ը
	CANDY_RESULT_EXPLOSION,
	//��ʾĿ��  
	CANDY_RESULT_SHOW_TARGET,
	//����ʱ321��ʼ
	CANDY_RESULT_COUNT_DOWN,
	//����ʤ��ǰ��Ч
	CANDY_RESULT_STAGE_CLEAR_EFFECT,
	//����ʤ��
	CANDY_RESULT_STAGE_CLEAR,
	//����ʧ��
	CANDY_RESULT_STAGE_FAILED,
	//��ͣ�˳���Ϸ
	CANDY_PUSE_EXIT_GAME,
	//ʤ���˳���Ϸ
	CANDY_WIN_EXIT_GAME,
	//�������˳���Ϸ
	CANDY_NOLIFE_EXIT_GAME,
	//ʧ���˳���Ϸ
	CANDY_FAIL_EXIT_GAME,
	//��ʾ��Խ��������
	CANDY_RESULT_RESORTRANK,
	//����ʤ��2
	CANDY_RESULT_WIN,
	//����ʧ��2
	CANDY_RESULT_LOSE,
	//��һ��
	CANDY_RESULT_NEXT_STAGE,
	//ʹ�õ���
	CANDY_RESULT_USE_PROP,
	//��Ϸ��ʹ�õ���
	CANDY_RESULT_USE_PROP_GAME,
	//ת��
	CANDY_RESULT_ROULETTE,
	//����
	CANDY_RESULT_RESORT,
	//��������
	CANDY_REWARDS_PROP,
	// ����+5����
	CANDY_BUY_ADD5PROP,
	// ����ʧ����Ч
	CANDY_RESULT_LOST_EFFECT,
	//ֱ�ӹ���
	CANDY_RESULT_PASS_LEVEL,
	// ���������
	CANDY_RESULT_BUYPROPING,
}CandyResultType;

typedef enum
{
	RESULT_WIDGE_PROP_TIPS,
	RESULT_WIDGE_GAME_WIN,
	RESULT_WIDGE_GAME_RESORTRANK,
	RESULT_WIDGE_GAME_LOSE,
	RESULT_WIDGE_GAME_NEXT,
	RESULT_WIDGE_ROULETTE,
	RESULT_WIDGE_NO_LIFE,
	RESULT_WIDGE_REWARDS,
	RESULT_WIDGE_ADD5PROP,
	RESULT_WIDGE_DISCOUNTGOODS,
	RESULT_WIDGE_BUYGEM,
	RESULT_WIDGET_NET,
	RESULT_WIDGE_GAMEPAY
}ResultWidgetType;

enum
{
	SHARE_TO_WEXIN,
	SHARE_TO_SINA,
	SHARE_TO_QZONE,
	BUTTON_TO_SHARE,
	BUTTON_TO_RANK,
	BUTTON_TO_HANDLELIFE,
};

class CandyResultLayer : public CCLayer
{
	public:
		static CandyResultLayer* create(void);

	public:
		virtual void onEnter(void);
		virtual void onExit(void);
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	public:
		void showWidget(ResultWidgetType type,bool action = false,void *data = NULL);
		void showWidgetCb(CCNode* sender);
		void BuyAdd5DelayCB(void);
	
	public:
		UILayer* getUILayer(void);
		
public:
		Layout* getPropTipsLayout(void);
		Layout* getPropBuyLayout(void);
		Layout* getGameWinLayout(void);
		Layout* getGameLoseLayout(void);
		Layout* getNoLifeLayout(void);
		Layout* getResortRankLayout(void *data);

		Layout* getAdd5PropLayout(void);
		Layout* getRewardsPropLayout(void);
		Layout* getDiscountGoodsLayout(void);
		
		
	public:
		void rewardsPropBtnCallBack(CCObject* pSender);
		void BuyAdd5PropBtnCallBack(CCObject* pSender);
		void PropTipsPlayOnCallBack(CCObject *pSender);
		void PropTipsExitCallBack(CCObject *pSender);
		void PropBuyOKCallBack(CCObject *pSender);
		void PropBuyCancelCallBack(CCObject *pSender);
		void gameWinNextCallBack(CCObject *pSender);
		void gameWinReturnCallBack(CCObject *pSender);
		void gameWinPalyAgainCallback(CCObject* pSender);
		void gameLosePlayAgainCallBack(CCObject *pSender);
		void gameLoseReturnCallBack(CCObject *pSender);

		void BuySuperLifePackCallback(CCObject* sender);
		void CancelBuySuperLifeCallback(CCObject* sender);

	public:
		void UpdataAdd5CountDown(void);	
		void UpdataCountDown(float t);
		void stageInfoPlayGame(void);
		void gameNextReturnCallBack(CCObject *pSender);

	public:
		void noLifeReturnCallBack(CCObject *pSender);

		ResultWidgetType getCurResultLayer(){return currentWidgetType;}

	private:
		void displayScoreStarParticle(CCNode* sender);

	private:
		UIButton *propTipsPlayOnButton;
		UIButton *propTipsExitButton;
		UIButton *gameWinNextButton;
		UIButton *gameWinReturnButton;
		UIButton *gameLosePlayOnButton;
		UIButton *gameLoseReturnButton;
		UIButton *noLifeReturnButton;
		UIButton *m_shareWeixin;
		UIButton *m_shareTWeibo;
		UIButton *m_shareSWeibo;
		UIButton* m_ChoujiangBtn;
		
	public:
		UILayer* UiLayer;
		Layout* propTipsLayout;
		Layout* propBuyLayout;
		Layout* noLifeLayout;
		Layout* gemeResortRankLayout;
		Layout* gameWinLayout;
		Layout* gameLoseLayout;
		Layout* gameNextLayout;
		Layout* gamePropLayout;
		Layout* add5PropLayout;
		Layout* rewardsPropLayout;
		Layout* discountGoodsLayout;
	private:
		UIImageView	*PropImg[3];
		UIImageView	*PropBuy[3];
		UIImageView	*PropNumBg[3];
		UIImageView	*PropSelected[3];
		UILabelAtlas		*PropNumLabel[3];

	private:
		UIImageView *ScoreStar[3];
	public:
		int			currentGetStar;
		
	private:
		ResultWidgetType currentWidgetType;

	private:
		int m_nCountDown;
		
	public:
		void AddFriendToRank(ResultWidgetType type);
		void moveOutGameLayerAction(void);
		void runStageClearAction(void);
		void stageClearCallback(void);
		void runPropTipsAction(void);
		void runExplosionBomb(void);
		void runStageFailedAction(void);
		void returnMainMapCallBack(void);
			
	public:
		void nextStageCallbackBefore(void);
		void nextStageCallback(void);
		void playAgainCallback(void);
		void playNextCallback(void);
		void discountGoodsCallback(void);

	private:
		void showNoLifeTips(void);
		
//*****************Added By Even**********************/
public:
		void performUI_Fall(Layout* widget);
		void showPropBuy();
		Layout* getPropBuyInfoLayout(int propid);
		CC_SYNTHESIZE(int, _propid, propId);
		void QuitPropWidget();
		void showStageInfoLayout();

//*****************Added By Even**********************/

	public:
		CCActionInterval* getMoveAction(bool inFlag, float time, CCPoint pos);
		void AddRewardCallback(CCNode* pSender);
		void removeRewardCallBack();
		void removeYouWin2();
		void ShareBtnCb(CCObject *pSender);
		UIWidget* addHeadImg(UserSingleLevelStr player);
		void ButtonCallBack(CCObject *pSender);
		void TurnToGameWinLayout();
		void ResortShareBtnCb(CCObject *pSender);
		void QuitPropWidget_dis();
		void DiscountGoodsExitCallBack(CCObject *pSender);
		void DiscountGoodsButtonCallBack(CCObject *pSender);
		void updateEnterNextLevel( float dt);
		void TurnToGameWinLayoutByJava();
		void Add5Dispear(void);
		void ChoujiangCallback(CCObject* sender);
		void BackToMainMapAndShowChoujiangUI();
	public:
		CCLayerColor *grayLayer;

};

class CandyResult
{
	public:
		CandyResult();
		~CandyResult();

	public:
		void initCandyResult(void);
		void updateCandyResult(float time);

	public:
		bool getGameRunning(void);

	public:
		void unDisplayTargetTips(void);
		
	public:
		void setCurrentResult(CandyResultType result);
		CandyResultType getCurrentResult(void);
		
	public:
		CandyResultLayer* getResultLayer(void);
		void removeResultLayer(void);

	private:
		void timeDelayChangeResult(float &currentTime, float time, float delayTime,CandyResultType nextRet);
		void addGrayLayer(void);
	private:
		CandyTarget *targetMgr;
		CandyResultType currentResult;
		CandyResultType lastResult;
		float remainTime;

public:
	CandyResultLayer* resultLayer;
		int		gamestate;
};




#endif
