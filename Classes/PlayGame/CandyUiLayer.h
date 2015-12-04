#ifndef CANDY_UI_LAYER__H
#define CANDY_UI_LAYER__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;


typedef enum
{
	CANDY_GAME_UI_WIDGE,
	CANDY_GAME_PAUSE_WIDGE,
	CANDY_GAME_SETTING,
	CANDY_GAME_GUIDE,			//指引界面
	CANDY_GAME_COUNT,
	CANDY_GAME_BUYGEM,
	CANDY_GAME_INVALID,			
	CANDY_GAME_SHOP,			//商城界面
	CANDY_GAME_SUPERGIFT,		//超级礼包
}CandyGameWidgetType;



class CandyCell;

class CandyUiLayer : public CCLayer
{
	public:
		CandyUiLayer();
		~CandyUiLayer();
		
	public:
   		CREATE_FUNC(CandyUiLayer);

	public:
		virtual bool init(void); 
		virtual void onEnter(void);
		virtual void onExit(void);
		
	public:
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	public:
		virtual void update(float time);

	public:
		virtual void keyBackClicked();

	public:
		void showComboPraise(int combo);
		void showTips(CCSprite *sprite);
		void showTipsCallback(CCNode* sender);
		
	public:
		void showGameWidget(CandyGameWidgetType type);
		CandyGameWidgetType getCurUIType();
	public:
		UILayer* getGameUiLayer(void);
		Layout* getGameUiLayout(void);
		Layout* getGamePauseLayout(void);
		
	private:
		void addUiWidget(void);
		void initUiWidget(void);
		void initCandyScoreStar(void);
		void adjustUiWidget(float fixedScreenHeight);

		

	public:
		void setScoreStarPercentage(float per);
		void displayStarPercentEffect(int starNum);
		void displayBlinkPercentEffect(float dt);
		void setScoreGrayStarVisible(int starNum, bool visible);
		void displayMoveWarning(void);
	
	public:
		CCNode* getEnergyJarNode(void);
		void resetEnergyJarPercentage(void);
		void increaseEnergyJarPercentage(int num);

	public:
		void updatePropNum(void);
		void useProp(int type);
		CCNode* getPropButtonNode(void);
		void candyUsePropStart(int type);
		void candyUsePropEnd(void);
		
	public:
		void updateCurrentTargetData(Layout* layout);

	private:
		void drawTargetTick(int num, UILabelAtlas* label);
		void drawTargetNumChange(UILabelAtlas* targetLabel, int num);
		
	public:
		CCLabelAtlas* getTargetLabel(int num);
		const CCPoint&  getStepNumLabelPos(void);
		const CCPoint&  getScoreNumLabelPos(void);
		const CCPoint& getTargetNumLabelPos(UILabelAtlas* label = NULL);
		const CCPoint&  getPropButtonPos(void);
	public:
		CCNode *getTargetIngreidentNode(int num, char *imgName, UILabelAtlas* label);
		CCNode *getTargetIconNode(int num);
		CCNode *getTargetCollectNode(int collectIndex, UILabelAtlas* targetLabel);
		
	private:
		void updateChatMsgNum(void);
		void updateTargetItem(void);
		void updateScoreItem(void);
		void updateMoveTimeItem(void);
		void updatePropItemStates(void);
		void updateBuy();
			
	private:
		void candySettingCallBack(CCObject *pSender);
		
	private:
		void candyPropChangeBSCallBack(CCObject *pSender);
		void candyPropChangeCCallBack(CCObject *pSender);
		void candyPropExtendCallBack(CCObject *pSender);
		void candyPropColorCallBack(CCObject* pSender);
		void candyPropBoomCallBack(CCObject* pSender);

		bool isFirstTimeUseProp();

		void propBuyBtnCallBack(CCNode* pSender);


	public:
		void setPropButtonTouchEnable(bool enable);
		
	private:
		void candyEnergyJarCallBack(CCObject *pSender);
		

	private:
		void gamePlayOnCallBack(CCObject *pSender);
		void gameExitCallBack(CCObject *pSender);
		void returnCallBack(CCObject *pSender);
		void pauseWidgetOutActionCb(void);


	//********************Added By Even*******************/
	public:
		Layout* getHelpUiLayout(void);
		Layout* getBuyGemUiLayout(void);

		void UIPerform(Layout* widget);
		void ShopEasein();		//商城入场动作
		void SuperGiftEaseIn();	//超级礼包入场动作
		void UIPerform_Guide(Layout* widget);
		void UIGray();
		void showPropBuy(int _propid);
		Layout* getPropBuyInfoLayout(int propid);
		void QuitPropWidget(Layout* widget = NULL);
		void AfterQuit(CCNode* node, void* data);

		void initFlyCandy(void);
		void initArmature(void);
		void RabbitPutSugar();
		void animationEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
		void onFrameEvent1(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);
		void animationEvent2(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
		void CandyFly();
		void SpecialCandyFly();
		void RabbitAppear();
		void RabbitDisappear();
		void RabbitDisappearCallBack();
		void RabbitPointToSugar();
		void RabbitStop();
		void updateEnergy();
		void displaySpecialCandyEffect(CCNode* targetNode,int special);
		void displaySpecialCandyEffectCb1(CCNode *pSender);
		void displaySpecialCandyEffectCb2(CCNode *pSender);
		void CandyAppear();
		void SpecialReward();
		void removeYouWinAni(void);
		CCDrawNode* getShape(int type);
		void QuitPropWidget_dis();
		void removeUsePropEffect();
		void updateMagicLampTime(float dt);
		void CandyScoreFire(void);
		//显示神灯
		void showMagicLamp();
		void shenDengStart();

		//商城
		Layout* getShopLayout();

		//超级大礼包
		Layout* getSuperGiftLayout();

		void ShowShop(CCObject* sender);		//弹出商城
		void ShowSuperGiftUI(CCObject* sender);	//弹出超级礼包

		//设置
		void SettingBtn();
		void SettingCallback(CCObject* sender);
		
		//********************Added By Even*******************/
	public:
	  	bool		 bPlayAnim;
		CCSprite	*m_pCandy1;	
		CCSprite	*m_pCandy2;	
		CCSprite	*m_pCandy3;	
		CCSprite	*m_pCandy4;	
		//CCArmature	*m_pShenDeng;
		CCArmature	*m_pShenDengRabbit;
// 		CCArmature	*m_pRabbitShake1;
// 		CCArmature	*m_pRabbitShake2;

//		bool		m_bReward;
		int			m_nRewardNum;
		int			m_nRewardType;
		
	private:
		int jellyFinishNum;
		int cherryFinishNum;
		int chestnutFinishNum;
		int targetScoreNum;
	private:
		int currentCollect[COLLECT_MAX_TYPE_NUM];
		
	private:
		int currentScore;
		int moveRemain;
		int timeRemain;
		
	private:
		CCMenu* pPropMenu;
		CCMenuItemImage *pPropScrap;
		CCMenuItemImage *pPropChange;
		CCMenuItemImage *pPropExtend;

		int pPropScrapNum;
		int pPropChangeNum;
		int pPropExtendNum;
		
		CCLabelTTF *pPropScrapNumLabel;
		CCLabelTTF *pPropChangeNumLabel;
		CCLabelTTF *pPropExtendNumLabel;
		
		bool selectedFlag;
		CandyIndex selectedIndex;

	private:
		CandyCell *changeCandy;

	public:
		Layout 			*gameUiLayout;
		//UIPanel		*energyJarButton;
		//UILabelAtlas	*labelTime;
		
		UIPanel			*collectModePanel;
		UIImageView	*collectTypeImg[3];
		UILabelAtlas		*collectTypeLabel[3];
	private:
		UILayer 			*gameUiLayer;
		Layout			*gamePauseLayout;

		
		UILoadingBar 		*scoreBar;
		UIImageView 	*starGap[3];
		UIImageView 	*grayStar[3];

		//UIImageView	*targetContent;
		UIImageView	*moveContent;
		UIImageView	*bottomUi;
		//UIImageView *chatMsgNumBg;	//消息数量

		UIImageView	*moveLabelImg;
		UIImageView	*timeLabelImg;
		
		UILabelAtlas		*actionNumLabel;
		UILabelAtlas		*scoreNumLabel;


		UIPanel			*jellyModePanel;
		UILabelAtlas		*jellyNumLabel;

		UIPanel			*transportModePanel;
		UIImageView	*chesnutImg;
		UIImageView	*cherryImg;
		UILabelAtlas		*chesnutNumLabel;
		UILabelAtlas		*cherryNumLabel;

		UIPanel			*targetNumPanel;
		UILabelAtlas		*targetNumLabel;

		//UIButton		*settingButton;
		UIImageView	*PropBuy[5];
		UIImageView	*PropNumBg[5];
		UILabelAtlas		*PropNumLabel[5];

	public:
		UIButton		*PropButton[5];
	private:
		UIButton *pausePlayOnButton;
		UIButton *pauseExitButton;
		Layout* gamePropLayout;
		Layout* gameShopLayout;		//商城
		Layout* SuperGiftLayout;	//超级礼包

		CandyGameWidgetType	m_curWidgetType;	//当前或最近显示的UI类型

	private:
		CCNode 			*percentingNode;
		CCNode 			*percentDoneNode;

	private:
		int propsNum[5];


};

#endif
