#ifndef MAIN_MAP_UI_LAYER__H
#define MAIN_MAP_UI_LAYER__H

#include "cocos2d.h"
#include "MainMapCommon.h"
#include "MainMapScene.h"
#include "../CommonData/CommonWidgt.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum
{
	MAP_WIDGET_NULL,
	MAP_WIDGET_BUYLIFE_LIST,
	MAP_WIDGET_FRIEND_INFO,
	MAP_WIDGET_FRIEND_LIST,
	MAP_WIDGET_NOFRIEND_LIST,
	MAP_WIDGET_MESSAGE_LIST,
	MAP_WIDGET_SEACHFRIEND,
	MAP_WIDGET_LEVEL_INFO,
	MAP_WIDGET_SUCCEEDUI_DLG,
	MAP_WIDGET_PROPCLIAORHEANDLE_DLG,
	MAP_WIDGET_HELP_DLG,
	MAP_WIDGET_SYSTEMTOOLS_DLG,
	MAP_WIDGET_FEEDBACK_DLG,
	MAP_WIDGET_LACKLIFE_DLG,
	MAP_WIDGET_CLAIMLIFE_DLG,
	MAP_WIDGET_PROPBUY_DLG,
	MAP_WIDGET_NOTICE_DLG,
	MAP_WIDGET_CHANGEINFO_DLG,
	MAP_WIDGET_BUYGEM_LIST,
	MAP_WIDGET_SURFRIEND_DLG,
	MAP_WIDGET_SHOP_DLG,
	MAP_WIDGET_VIP_DLG,
	MAP_WIDGET_RANK_DLG,
	MAP_WIDGET_GIFT_DLG,
	MAP_WIDGET_UNLOCKLEVEL_DLG,
	MAP_WIDGET_GETHERSTAR,
	MAP_WIDGET_KNAPSACK,
	MAP_WIDGET_MAINTASK,
	MAP_WIDGET_TASK,
	MAP_WIDGET_MYINFORMAT,
	MAP_WIDGET_DAILYTASK_EXTRA,
	MAP_WIDGET_REMINDNETWORK,
	MAP_WIDGET_REWARDVIPUI,
	MAP_WIDGET_ACTIVEGIFT,
	MAP_WIDGET_SIGNIN,
	MAP_WIDGET_ROULETTE_DLG,
	MAP_WIDGET_PAY_DLG,


}MapWidgetType;


typedef enum
{
	TAG_WORLDRANK_TOOLSMENU_ITEM,
	TAG_BUYLIFE_TOOLSMENU_ITEM,
	TAG_BUYGEM_TOOLSMENU_ITEM,
	TAG_WEMECHCAT_TOOLSMENU_ITEM,
	TAG_NOTICE_TOOLSMENU_ITEM,
	TAG_FEEDBACK_TOOLSMENU_TIEM,
	TAG_SETTIONG_TOOLSMENU_TIEM,
	TAG_FRIENDLIST_TOOLSMENU_TIEM,
	TAG_NOFRIENDLIST_TOOLSMENU_TIEM,
	TAG_MESSAGELIST_TOLLSMENU_TIEM,
	TAG_GETHERSTAR_TOOLSMENU_TIME,
	TAG_KNAPSACK_TOOLSMENU_TIEM,
	TAG_MAINTASK_TOOLSEMNU_TIEM,
	TAG_GAMESHOP_TOOLSEMNU_TIEM,
	TAG_VIP_TOOLSEMNU_TIEM,
	TAG_DAILYTASK_GETCANDY_TOOLSMENU_TIEM,
	TAG_DAILYTASK_TARGETLEVEL_TOOLSMENU_TIEM,
	TAG_MYINFORMAT_TOOLSMENU_ITEM,
	TAG_ACTIVEGIFT_TOOLSMENU_ITEM,
	TAG_TASK_TOOLSMENU_ITEM,
	TAG_SIGNIN_TOOLSMENU_ITEM,

	TAG_BACK_TO_PAGEVIEW_ITEM,	//返回pageview按钮
	TAG_ROULETTE_TOOLSMENU_ITEM,

}MapToolsMenuStr;


typedef enum
{
	PROMPT_TYPE_CHANGEINFO,					// 免费更改资料的机会
	PROMPT_TYPE_VIPLIFE,					// VIP可以加快生命恢复	
	PROMPT_TYPE_VIPTASK,					// VIP可以获得额外每日任务
	PROMPT_TYPE_UNLOCKSTARTASK,				// 您解锁了<星星收集>
	PROMPT_TYPE_UNLOCKMAINTASK,				// 您解锁了<糖果之旅>	
	PROMPT_TYPE_UNLOCKMSGORFRIEND,			// 您解锁了<好友列表>和<消息>
	PROMPT_TYPE_UNLOCKDAYTASK,				// 您解锁了<每日任务>
	PROMPT_TYPE_FRIENDNUMLIMIT,				// 好友上限+1
	PROMPT_TYPE_NOGETREWARD,				// 您今天已经不能再领取了
	PROMPT_TYPE_NOADDFRIEND,				// 您好友已满,请先扩充上限	
	PROMPT_TYPE_RANKEDUP,					// 恭喜!您的世界排名上升了
	PROMPT_TYPE_SIGNINSUC,					// 签到成功!


	PROMPT_TYPE_UNLOCK_STARTASK,			// 	大地图任务图标=>该功能第3关后开启
	PROMPT_TYPE_UNLOCK_MAINTASK,			// 	任务界面糖果之旅图标=>该功能第8关后开启
	PROMPT_TYPE_UNLOCK_EVERYDAYTASK,		// 	任务界面日常任务图标=>该功能第30关后开启
	PROMPT_TYPE_UNLOCK_FRIEND,				// 	大地图小伙伴图标=>该功能第20关后开启
	PROMPT_TYPE_UNLOCK_VIP,					// 	非VIP的补签按钮=>开通VIP才可以补签
}CandyPromptType;

// enum
// {
// 	TOOLS_ITEM_CHANGEUSER = 1,
// 	TOOLS_ITEM_HELP,
// 	TOOLS_ITEM_LOGOUT,
// 	TOOLS_ITEM_MUSIC,
// 	TOOLS_ITEM_VOL,
// };
enum
{
	EDITBOX_TYPE_FEEDBACK = 5,
	EDITBOX_TYPE_CHANGERINFO,
	EDITBOX_TYPE_QQINFO,
	EDITBOX_TYPE_SEACHFRIEND,
};

enum
{
	MESSAGE_TABLE_1 = 1,
	MESSAGE_TABLE_2,
	MESSAGE_TABLE_3,
};
enum
{
	SEX_BOY_BUT = 846,
	SEX_GIRL_BUT,
};
enum
{
	MESSAGE_ACCEPT_FRIEND,
	MESSAGE_NOACCEPT_FRIEND,
	MESSAGE_ACCEPT_LIFE,
};

enum
{
	MESSAGE_TYPE_HANDSELEFT = 1,		// 赠送的生命消息
	MESSAGE_TYPE_HANDSEPROP,			// 赠送的道具消息
	MESSAGE_TYPE_CLAIMEDPROP,			// 索取的道具消息
	MESSAGE_TYPE_RECORDPROP,
	MESSAGE_TYPE_INVATEFRIEND,
};

enum
{
	TIPMSG_TYPE_PROPINSUF = 1,
	TIPMSG_TYPE_LIFEINSUF,
	TIPMSG_TYPE_LIFELACK,
	TIPMSG_TYPE_WEMECHITCHAT,
};

enum
{
	DLG_TYPE_HANDSELLIFE = 1,
	DLG_TYPE_CLAIMLIFE,
	DLG_TYPE_HANDSELPROP,
	DLG_TYPE_CLAIMEPROP
};

enum
{
	CHANGEINFO_SELECT_HEAD1 = 1,
	CHANGEINFO_SELECT_HEAD2,
	CHANGEINFO_SELECT_HEAD3,
	CHANGEINFO_SELECT_HEAD4,
	CHANGEINFO_SELECT_SEXBOY,
	CHANGEINFO_SELECT_SEXGIRL,
	CHANGEINFO_SELECT_EXIT,
	CHANGEINFO_SELECT_SUBMIT,
};

enum
{
	INVITEFRIEND_FOR_SEACH,
	INVITEFRIEND_FOR_RECOMMEND,
};

#define	 MAP_DLG_QUIT	1//1.2f
#define	 MAP_DLG_ENTRY	2//0.8f

typedef struct ShowWidget_t
{
	Layout*			widget;
	MapWidgetType	type;
}WidgetNode;

// 好友节点
typedef struct FriendNode_t
{
	std::string		m_Idx;;
	std::string		m_sName;	// 昵称
	std::string		m_sHeadUrl;
	int				m_sex;		//性别
	int				m_ID;	
}FriendNode;

typedef struct MessageNode_t
{
	int				m_type;		//  消息类型  0：无  1：赠送给我的生命消息  1：赠送给我的道具消息  2：向我索要的道具消息
	int				m_orderid;
	int				m_propnum;
	int				m_propid;
	int				m_friendid;
	int				m_sex;
	int				m_time;
	bool			m_isAccept;		// 是否已接受
	std::string		m_adate;
	std::string		m_headurl;
	std::string		m_friendname;
	std::string		m_propname;
}MessageNode;

typedef struct RecordNode_t
{
	int				m_propnum;
	int				m_friendid;
	int				m_sex;
	std::string		m_friendname;
	std::string		m_propname;
	std::string     m_time;
}RecordNode;

#define MAP_LEVEL_NUMSTRING					"Image/MainMapUi/res_msg/m_lifenum.png"//"Image/BigMap_1/labelatlasimg.png"

#define MAP_LIFE_TIMEDOWN					"Image/MainMapUi/res_msg/m_lifetimenum.png"//"Image/BigMap_1/labelatlasimg.png"
#define CHAT_MSG_NUM_BG						"Image/MainMapUi/Tools/m_messageTips.png"


class TollgateSelectLayer;
class SelectLevelLayer;
class MainMapUiLayer:public CCLayer, public cocos2d::extension::CCEditBoxDelegate
{
	public:
		CREATE_FUNC(MainMapUiLayer);

	/**
     * Default constructor
     */
    MainMapUiLayer(void);
	virtual ~MainMapUiLayer();
	public:
		virtual bool init(void); 
		virtual void onEnter(void);
		virtual void onExit(void);
		virtual void update(float time);
		virtual void keyBackClicked();
#if defined(DEMO_FOR_GUEST)
		virtual void keyMenuClicked();
#endif
	public:
		virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
		virtual void editBoxReturn(cocos2d::extension::CCEditBox * myeditbox); 
		virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox * myeditbox); 
		virtual void editBoxTextChanged(cocos2d::extension::CCEditBox * myeditbox,const std::string&text);  

	private:
		void updateChatMsgNum(void);
	public:
		void initMapMenu(void);
		void ShowYijieUserId();
	
	public:
		void toolsMenuCallback(CCObject*pSender);
		void feedbackbutCallBack(CCObject *pSender);
		void LevelInfoNextCB(CCObject *pSender);
		void LevelInfoReturnCB(CCObject *pSender);
		void SuccendDlgSurCB(CCObject *pSender);
		void CliamLifeSurCB(CCObject *pSender);
		void UpdataMapHead();
		void uploadInfo();
		void updateHead(float dt);
		void setDailyTask(void);
		void ResetVipTask(void);
		void showBuyPrompt(int type);
		void updataShopGemAndCandNum(void);
		void showOtherPrompt(CandyPromptType type);
		void showUnlockPrompt( CandyPromptType type, CCPoint pos);
		void FunCallBuyPromptAction();
		void FunCallOtherPromptAction(CCNode* sender, void* data);
		void FunCallUnlockPromptAction(CCNode* sender, void* data);
		void FunCallPassReward(CCNode* pSende, void* data);

		//设置返回键是否有效
		void setKeybackEnabled(bool b);

	public:
		void passLevelRewardCandy(void);
		void runGemAnimation(void);
		void PlayEffect(int index);
		void removeWidgetUILayer(void);
		void setAsynFlag(bool state);
		void sendInviteNofriendmsg(void);

		void showPropInfoBuy(const int propid);
		void showMapWidget(MapWidgetType type, int para = 1, int para1 = 1);
		void QuitMapWidget(MapWidgetType nexttype = MAP_WIDGET_NULL);
		void QuitMapWidgetCallback(CCNode* node = NULL, void* data = NULL);
		void QuitMapWidgetDirect(void);

		static void showLevelInfo(int level);
		void EnteyGameCallBack(void);
		void EnteyBuyLifeCallBack(void);

		// http加载loading界面
		void setLoading(bool state);

		// http异步消息通知
		void HttpGetMyInfoAsyn(bool state = true);
		void HttpGetFriendListAsyn(bool state = true);
		void HttpGetAddSysLifeAsyn(bool state = true);
		void HttpBuyLifeAsyn(bool state = true);
		// 同意索要
		void HttpClaimedPropAcceptAsyn(bool state = true);
		// 拒绝索要 
		void HttpClaimedPropRefuseAsyn(bool state = true);
		void UpdataMessageList();
		void UpdataPropNum();
		void HttpAcceptPropAsyn(bool state = true);
		void HttpGetConsumeLifeAsyn(bool state = true);// 消耗生命
		void HttpHandselPropAsyn(bool state = true);//赠送道具
		void HttpClaimPropAsyn(bool state = true);// 索要道具
		void HttpGetLifePriceAsyn(bool state = true);
		void HttpAcceptLife(bool state = true);
		void HttpHandselLife(bool state = true);
		void HttpGetChatRecordAsyn(bool state = true);
		void HttpGetHandselLifeAsyn(bool state = true);
		void HttpGetHandselPropAsyn(bool state = true);
		void HttpGetClaimedPropAsyn(bool state = true);
		void HttpGetMyMessageAsyn(bool state = true);
		void HttpGetInviteFriendmsgAsyn(bool state = true);

		void onNetEvent(int state);//　网络事件
		void addMessagetoList(void);// 添加消息列表
		void updataMessageList(CCPoint point);
		void addHistoryMsgtoList(void);// 添加历史消息列表
		void addNoticetoList(void);// 添加公告
		void addLifetoList(void);// 添加爱心列表
		void addGemItemtoList(void);// 添加宝石列表
		void addNofriendtoList(void);//　添加非好友到列表
		void addFriendtoList( void );//　添加好友到列表
		void removeFriendAndUpdataList(int friendid);
		void addFriendtoClaimList(void);// 添加好友到生命索要list
		void addSeachFriendTolist(void);//　添加搜索好友到列表
		void addMainTaskToList(void);
		void addEveryDayTaskToList(void);
		CCActionInterval* getMoveAction(int state, CCPoint pos);
		CCActionInterval* getTaskMsgTipsAction(void);
		CCActionInterval* getEffectBezierAction(CCPoint originPos, CCPoint targetPos);

		void updataWorldRankedNumber(float t);

		void SwitchPageViewAndLevelLayer();
		void ShowTollgatePageview(int pagNum = -1);	//关卡翻页页面
		void ShowLevelLayer();			//关卡选择页面
		void BackTopageview(CCObject* sender);
		void SetTollgateTouchPriority(int Priority);
		void addTouchArea();

		// 物品掉落背包效果
		void playKnapsackAction( CCPoint pos ,int propid);

		//更新生命数量显示
		void refreshLifeUI();

		UILayer* getWidgetUILayer(void);
	private:
		
		Layout* getBuyLifeListLayout(void);
		Layout* getFriendInfoLayout(void);	// 单个好友信息
		Layout* getInviteFriendListLayout(void);
		Layout* getFriendListLayout(void);	//好友列表
		Layout* getMessageListLayout(void);		//消息
		Layout* getLevelInfoLayout(int level);
		Layout*	getHelpUiLayout(void);
		Layout*	GetReminderlayout(int type);
		Layout* getSucceedDlgUilayout(int sucType = PROMPT_TYPE_BUYSUC, int data = 0);
		Layout* getPropDlgLayout(int propid, int dlgtype);
		Layout* getSystemToolsLayout(void);
		Layout* getFeedbackLayout(void);
		Layout* getLackLifeLayout(void);
		Layout* getCliamLifeLayout(void);
		Layout* getPropBuyLayout(int propid);
		Layout* getNoticeLayout(void);
		Layout* getChangeInfoLayout(void);
		Layout* getBuyGemLayer(void);	// 宝石购米界面
		Layout* getSeachfriendLayer(void);
		Layout* getSurpassFriendLayout(void);
		Layout* getGetherStarTaskLayout(void);
		Layout* getKnapsackLayout(void);		//背包
		Layout* getMainTaskLayout(void);
		Layout* getGameShopLayout(void);
		Layout* getGameVipLayout(void);
		Layout* getGameGiftLayout(int type);
		Layout* getGameUnlockLevelLayout(int level);
		Layout* getDailyTaskExtraLayout(int tasktype);
		Layout* getTaskLayout(void);
		Layout* getMyInformatLayout(void);
		Layout* getRewardUILayout(void);
		Layout* getSignInUILayout(void);
		Layout* getGameRankLayout(void);		// 排名 
		Layout* getGameRouletteLayout(void);



	private:
		void initChangeInfoLayout(void);


		void ReminderLifeCB(CCObject *pSender);
		void ReminderExitCB(CCObject *pSender);
		void ReminderNetCB(CCObject *pSender);

		void ItemCallBackCliamList(CCObject *pSender);
		void BtnCallBackBuyLife(CCObject *pSender);
		void BtnCallBackFriendList(CCObject *pSender);
		void BtnCallBackDelFriend(CCObject* pSender);
		void BtnCallBackBuyFriendLimit(CCObject* pSender);
		void BtnCallBackMessageList(CCObject *pSender);

		void BtnCallBackCloseBuyLife(CCObject *pSender);
		void BtnCallBackCloseFriendInfo(CCObject *pSender);
		void BtnCallBackCloseFriendList(CCObject *pSender);
		void ButCallBackInviteFriend(CCObject *pSender);
		void ButCallBackSeachFriend(CCObject *pSender);
		void ButCallBackInviteFriendList(CCObject *pSender);
		void BtnCallBackTask(CCObject *pSender);
		void BtnCallBackMainTaskItem(CCObject *pSender);
		void BtnCallBackMainTaskInfo(CCObject *pSender);
		void BtnCallBackMainTaskRewar(CCObject *pSender);
		void BtnCallBackEveryDayTaskItem(CCObject *pSender);
		void BtnCallBackEveryDayTaskInfo(CCObject *pSender);
		void BtnCallBackEveryDayTaskRewar(CCObject *pSender);
		void BtnCallBackMyInformat(CCObject *pSender);
		void InviteButCallBack(CCObject *pSender);
		void messageListCloseCallBack(CCObject *pSender);
		void CloseCallBack(CCObject *pSender);
		void LackLifeUiButCallBack(CCObject *pSender);
		void CliamLifeUiButCallBack(CCObject *pSender);
		void NoticeUiButCallBack(CCObject* pSender);
		void ChangeInfoButCallBack(CCObject* pSender);
		void ChangeInfoSelectCallBack(CCObject* pSender);
		void SeachfriendBtnCB(CCObject* pSender);
		void getherStarBtnCallBack(CCObject* pSender);
		void knapsackBtnCallBack(CCObject* pSender);
		void mainTaskBtnCallBack(CCObject* pSender);
		void mainTaskImgCallBack(CCObject* pSender);

		void BtnCallBackForRewardUI(CCObject *pSender);


		void TaskRewardActionCallBack(CCNode* pSende);
		void DailyTaskActionCallBack(CCNode* pSende, void* data);

		void friendPropButCB(CCObject *pSender);

		void MessageTabCallBack(CCObject *pSender);
		void MessageTab2CallBack(CCObject *pSender);
		void MessageTab3CallBack(CCObject *pSender);
		void AllAcceptProcCallBack(CCObject *pSender);


		void setTaskLable(int index);
		void InitTaskLable1(void);
		void InitTaskLable2(void);
		void InitTaskLable3(void);
		void setMainTaskInfo(int taskid);
		void setEveryDayTaskInfo(int taskid);
		void setMyInformatLable(int index);
		void InitMyInformatLable1(void);
		void InitMyInformatLable2(void);


		void showMessageTab1(void);
		void showMessageTab2(void);
		void showMessageTab3(void);
		void messageListClose();
		void friendListClose();
		void LevelInfoClose();
		void friendInfoClose();
		void CliamActionCB();
		void WidgitrunAction();
		void InviteFirendClose();
		void InviteFriendButCB();
		void feedbackClose();
		void ReminderClose();
		void buyUnlockMainTask(int buyprice);

		void updataMyInformtion(char* nickname,int qq);
		void UpdataDelayKey(float t);
		void UpdataCountDown(float t);
		void UpdateGlobeAction(void);
		void UpdateGlobeActionCB(float dt);//  更新地图上元素动画
		void updataFriendListTime(float t);
		void FirstLevelInfoDelay(float t);
		void FirstConsumsLifeDelay(float t);
		void updataTaskDownTime(float t);
		void updataLackLifeUi(void);

		int getHourForSever(unsigned int hour);
		int getMinuteForSever(int hour, unsigned int time);
		int getSecoudForSever(int hour, int min, unsigned int time);
		void updateLife(float dt);
		void UpdateFriendRank();
		void SexBtnCallBack(CCObject *pSender);
		void uploadHead(CCObject *pSender);

		void createLeftImgPrompt(CCPoint pos, const char* name);
		void createDownImgPrompt(CCPoint pos, const char* name);

		void setKnapsackAction( float t );
		void callfuncKnapsack( CCNode* node, void* data);

		bool getMainTaskRewardStatus(void);
		bool getMainTaskLetRewardStatus(void);
		bool getMessagePropmtStatus(void);
		bool getTaskLetRewardStatus(void);

		char* getDailyTexturesBtnBuyId(int claimid);


		void callfuncKnapsackGoods( CCNode* node, void* data);
		void ShowRoulete(CCObject* sender);
	public:
		UIImageView* m_BuyPrompt;
		UILabelBMFont* m_FntPrompt;
		UILabelBMFont* m_FntUnlockPrompt;
		//UILabelBMFont* m_BuyPrompt;
		UIButton* m_currSelButton;
		CCArmature *m_loadArmature;
		UIImageView *m_ploading;
		UILayer* widgetUiLayer;;

		//Layout* LifeListLayout;
		Layout* friendInfoLayout;
		Layout* friendListLayout;
		Layout*	noFriendListLayout;
		Layout* messageListLayout;
		Layout*	globeLayout;
		Layout* LevelInfoLayout;
		Layout* reminderLayout;
		Layout* succeeddlgLayout;
		Layout* cliamsucLayout;
		Layout*	feedbacklayout;
		Layout*	LackLifelayout;
		Layout*	CliamLifelayout;
		Layout*	noticeLayout;
		Layout*	changeinfoLayout;
		Layout* gembuyLayout;
		Layout* seachfriendLayout;
		Layout* levelLayout;
		Layout* getherStarLayout;
		Layout* knapsackLayout;
		Layout* mainTasklayout;
		Layout* mapToolbarlayout;
		Layout* dailyTaskExtralayout;
		Layout* tasklayout;
		Layout* myInformatlayout;
		Layout* rewardlayout;

		TollgateSelectLayer* tollgaetPageview;
		SelectLevelLayer* levelSelectLayer;

		CCEditBox* m_pEditBox;
		UITextField *m_pLevelField;

		cocos2d::extension::UIPanel* m_pPanel;

		MapWidgetType	m_CurWidgetType;
		UILabelAtlas*	m_plifeNum;

		UIImageView*	m_toolsT;
		UIButton*		m_gameLifeBut;
	
		UIButton*		m_messageListBut;
		UIButton*		m_friendListBut;
		//UIButton*		m_wemeChatBut;
		//UIButton*		m_friendBut;
		//UIButton*		m_MessageBut;
		UIButton*		m_GetherStarBut;
		UIButton*		m_KnapsacBut;
		UIButton*		m_mainTaskBut;
		UIButton*		m_gameShopBut;
		//UIImageView*		chatMsgNumBg;

		UILabelAtlas*	m_lifeTime;
		//UILabelAtlas*	m_pGemNum;

		UIImageView*	m_pAddLifeTips;
		UIImageView*	m_pFullLifeTips;
		UIImageView*	m_MessagehightTab1; 
		UIImageView*	m_MessagehightTab2; 
		UIImageView*	m_MessagehightTab3; 
		//UIImageView*	m_messagetips;
		UIImageView*	m_pMsgTip;
		UIButton*		m_pTools;

		UIButton*		m_BackPageviewBtn;				//翻页返回按钮

		static MainMapUiLayer *m_mainmapuilayer;
		
	public:
		std::string m_feedbackstr;
		std::string m_Nicknamestr;
		std::string m_qqstr;
		std::string m_seachStr;
		bool		m_isEnableKey;
		bool		m_isKey;
		bool		m_AsynFlag; // 来自Java的异步消息

		bool		m_isNetMessage;
		bool		m_isNetHistoryMsg;
		bool		m_isNetNofriendMsg;
		bool		m_isShowMessage;

		bool		mDelayBackKey;

		int			m_CountDown;
		int			m_CurSelFriendItem;
		int			m_ClaimLifeNum;
		
		// Msg列表
		std::list<MessageNode>	m_messagelist;
		// DLG队列
		std::list<WidgetNode> widgetList;
		
};



#endif