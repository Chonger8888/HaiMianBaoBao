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

	TAG_BACK_TO_PAGEVIEW_ITEM,	//����pageview��ť
	TAG_ROULETTE_TOOLSMENU_ITEM,

}MapToolsMenuStr;


typedef enum
{
	PROMPT_TYPE_CHANGEINFO,					// ��Ѹ������ϵĻ���
	PROMPT_TYPE_VIPLIFE,					// VIP���Լӿ������ָ�	
	PROMPT_TYPE_VIPTASK,					// VIP���Ի�ö���ÿ������
	PROMPT_TYPE_UNLOCKSTARTASK,				// ��������<�����ռ�>
	PROMPT_TYPE_UNLOCKMAINTASK,				// ��������<�ǹ�֮��>	
	PROMPT_TYPE_UNLOCKMSGORFRIEND,			// ��������<�����б�>��<��Ϣ>
	PROMPT_TYPE_UNLOCKDAYTASK,				// ��������<ÿ������>
	PROMPT_TYPE_FRIENDNUMLIMIT,				// ��������+1
	PROMPT_TYPE_NOGETREWARD,				// �������Ѿ���������ȡ��
	PROMPT_TYPE_NOADDFRIEND,				// ����������,������������	
	PROMPT_TYPE_RANKEDUP,					// ��ϲ!������������������
	PROMPT_TYPE_SIGNINSUC,					// ǩ���ɹ�!


	PROMPT_TYPE_UNLOCK_STARTASK,			// 	���ͼ����ͼ��=>�ù��ܵ�3�غ���
	PROMPT_TYPE_UNLOCK_MAINTASK,			// 	��������ǹ�֮��ͼ��=>�ù��ܵ�8�غ���
	PROMPT_TYPE_UNLOCK_EVERYDAYTASK,		// 	��������ճ�����ͼ��=>�ù��ܵ�30�غ���
	PROMPT_TYPE_UNLOCK_FRIEND,				// 	���ͼС���ͼ��=>�ù��ܵ�20�غ���
	PROMPT_TYPE_UNLOCK_VIP,					// 	��VIP�Ĳ�ǩ��ť=>��ͨVIP�ſ��Բ�ǩ
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
	MESSAGE_TYPE_HANDSELEFT = 1,		// ���͵�������Ϣ
	MESSAGE_TYPE_HANDSEPROP,			// ���͵ĵ�����Ϣ
	MESSAGE_TYPE_CLAIMEDPROP,			// ��ȡ�ĵ�����Ϣ
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

// ���ѽڵ�
typedef struct FriendNode_t
{
	std::string		m_Idx;;
	std::string		m_sName;	// �ǳ�
	std::string		m_sHeadUrl;
	int				m_sex;		//�Ա�
	int				m_ID;	
}FriendNode;

typedef struct MessageNode_t
{
	int				m_type;		//  ��Ϣ����  0����  1�����͸��ҵ�������Ϣ  1�����͸��ҵĵ�����Ϣ  2��������Ҫ�ĵ�����Ϣ
	int				m_orderid;
	int				m_propnum;
	int				m_propid;
	int				m_friendid;
	int				m_sex;
	int				m_time;
	bool			m_isAccept;		// �Ƿ��ѽ���
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

		//���÷��ؼ��Ƿ���Ч
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

		// http����loading����
		void setLoading(bool state);

		// http�첽��Ϣ֪ͨ
		void HttpGetMyInfoAsyn(bool state = true);
		void HttpGetFriendListAsyn(bool state = true);
		void HttpGetAddSysLifeAsyn(bool state = true);
		void HttpBuyLifeAsyn(bool state = true);
		// ͬ����Ҫ
		void HttpClaimedPropAcceptAsyn(bool state = true);
		// �ܾ���Ҫ 
		void HttpClaimedPropRefuseAsyn(bool state = true);
		void UpdataMessageList();
		void UpdataPropNum();
		void HttpAcceptPropAsyn(bool state = true);
		void HttpGetConsumeLifeAsyn(bool state = true);// ��������
		void HttpHandselPropAsyn(bool state = true);//���͵���
		void HttpClaimPropAsyn(bool state = true);// ��Ҫ����
		void HttpGetLifePriceAsyn(bool state = true);
		void HttpAcceptLife(bool state = true);
		void HttpHandselLife(bool state = true);
		void HttpGetChatRecordAsyn(bool state = true);
		void HttpGetHandselLifeAsyn(bool state = true);
		void HttpGetHandselPropAsyn(bool state = true);
		void HttpGetClaimedPropAsyn(bool state = true);
		void HttpGetMyMessageAsyn(bool state = true);
		void HttpGetInviteFriendmsgAsyn(bool state = true);

		void onNetEvent(int state);//�������¼�
		void addMessagetoList(void);// �����Ϣ�б�
		void updataMessageList(CCPoint point);
		void addHistoryMsgtoList(void);// �����ʷ��Ϣ�б�
		void addNoticetoList(void);// ��ӹ���
		void addLifetoList(void);// ��Ӱ����б�
		void addGemItemtoList(void);// ��ӱ�ʯ�б�
		void addNofriendtoList(void);//����ӷǺ��ѵ��б�
		void addFriendtoList( void );//����Ӻ��ѵ��б�
		void removeFriendAndUpdataList(int friendid);
		void addFriendtoClaimList(void);// ��Ӻ��ѵ�������Ҫlist
		void addSeachFriendTolist(void);//������������ѵ��б�
		void addMainTaskToList(void);
		void addEveryDayTaskToList(void);
		CCActionInterval* getMoveAction(int state, CCPoint pos);
		CCActionInterval* getTaskMsgTipsAction(void);
		CCActionInterval* getEffectBezierAction(CCPoint originPos, CCPoint targetPos);

		void updataWorldRankedNumber(float t);

		void SwitchPageViewAndLevelLayer();
		void ShowTollgatePageview(int pagNum = -1);	//�ؿ���ҳҳ��
		void ShowLevelLayer();			//�ؿ�ѡ��ҳ��
		void BackTopageview(CCObject* sender);
		void SetTollgateTouchPriority(int Priority);
		void addTouchArea();

		// ��Ʒ���䱳��Ч��
		void playKnapsackAction( CCPoint pos ,int propid);

		//��������������ʾ
		void refreshLifeUI();

		UILayer* getWidgetUILayer(void);
	private:
		
		Layout* getBuyLifeListLayout(void);
		Layout* getFriendInfoLayout(void);	// ����������Ϣ
		Layout* getInviteFriendListLayout(void);
		Layout* getFriendListLayout(void);	//�����б�
		Layout* getMessageListLayout(void);		//��Ϣ
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
		Layout* getBuyGemLayer(void);	// ��ʯ���׽���
		Layout* getSeachfriendLayer(void);
		Layout* getSurpassFriendLayout(void);
		Layout* getGetherStarTaskLayout(void);
		Layout* getKnapsackLayout(void);		//����
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
		Layout* getGameRankLayout(void);		// ���� 
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
		void UpdateGlobeActionCB(float dt);//  ���µ�ͼ��Ԫ�ض���
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

		UIButton*		m_BackPageviewBtn;				//��ҳ���ذ�ť

		static MainMapUiLayer *m_mainmapuilayer;
		
	public:
		std::string m_feedbackstr;
		std::string m_Nicknamestr;
		std::string m_qqstr;
		std::string m_seachStr;
		bool		m_isEnableKey;
		bool		m_isKey;
		bool		m_AsynFlag; // ����Java���첽��Ϣ

		bool		m_isNetMessage;
		bool		m_isNetHistoryMsg;
		bool		m_isNetNofriendMsg;
		bool		m_isShowMessage;

		bool		mDelayBackKey;

		int			m_CountDown;
		int			m_CurSelFriendItem;
		int			m_ClaimLifeNum;
		
		// Msg�б�
		std::list<MessageNode>	m_messagelist;
		// DLG����
		std::list<WidgetNode> widgetList;
		
};



#endif