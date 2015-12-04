#ifndef COMMONWIDGT_H
#define COMMONWIDGT_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../MsgMgr/AnalyseJson.h"

USING_NS_CC;
USING_NS_CC_EXT;


enum
{
	TOOLS_ITEM_CHANGEUSER = 1,
	TOOLS_ITEM_HELPFORMAP,
	TOOLS_ITEM_HELPFORGAME,
	TOOLS_ITEM_LOGOUT,
	TOOLS_ITEM_CHANGEINFO,
	TOOLS_ITEM_MUSIC,			
	TOOLS_ITEM_VOL,				//背景音乐
	TOOLS_ITEM_MUSICOPEN,
	TOOLS_ITEM_MUSICCLOSE,
	TOOLS_ITEM_SOUNDOPEN,
	TOOLS_ITEM_SOUNDCLOSE,
	TOOLS_TIEM_CONTOUNE,
	TOOLS_TIEL_FEEDBACK,
	TOOLS_TILE_NOTICE,
	TOOLS_TILE_QUITGAME,
	TOOLS_TILE_EXITGAME,
	TOOLS_CONTINUE_GAME,		//继续游戏
};

typedef enum
{
	WIDGET_TYPE_LOADING,
	WIDGET_TYPE_MAP,
	WIDGET_TYPE_GAME,
}CommonWidgetType;

// enum
// {
// 	SUC_FOR_BUYLIFE,
// 	SUC_FOR_BUYPROP,
// 	SUC_FOR_FEEDBACK,
// 	SUC_FOR_INVITE,
// 	SUC_FOR_ALLACCEPT,
// 	SUC_FOR_SUBMIT,
// };

enum
{
	PROMPT_TYPE_CHITNOOPEN,
	PROMPT_TYPE_BUYSUC,
	PROMPT_TYPE_BUYLIFESUC,
	PROMPT_TYPE_BUYVIPSUC,
	PROMPT_TYPE_FEEDBACK,
	PROMPT_TYPE_INVITE,
	PROMPT_TYPE_SUBMITSUC,
	PROMPT_TYPE_NETERR,
	PROMPT_TYPE_DELFRIEND,
	PROMPT_TYPE_FRIENDLIMIT,
	PROMPT_TYPE_LIFELACK_TO_MAP,
	PROMPT_TYPE_REMINDNETWORK,
};

enum
{
	BTN_TAG_CLOSE,
	BTN_TAG_BUYGEM,
};


enum RouletteRewardType
{
	RouletteRewardType_Life = 1,
	RouletteRewardType_ColorCandy = 2,
	RouletteRewardType_Gem = 3,
	RouletteRewardType_Double = 4,
	RouletteRewardType_MultiLife = 5,
	RouletteRewardType_BombCandy = 6,
	RouletteRewardType_Harmmer = 7,
	RouletteRewardType_Huafei = 8
};


//区分游戏里面与外面的商城
enum ShopTag
{
	ShopInMaptag = 1,
	ShopinGametag
};

#define MUSIC_BUTTON_EFFECT			"Music/ButtonEffect.mp3"
#define MUSIC_MOVEHEAD_EFFECT		"Music/MoveHeadEffect.mp3"
#define MUSIC_BUTTON_BGMUSIC		"Music/MapBgm.mp3"
#define MUSIC_BUTTON_ROULETTE		"Music/RouletteInside.mp3"

class PropInfoWidget:public CCObject
{
public:
	PropInfoWidget();
	~PropInfoWidget();

public:
	Layout*  getPropInfoLayout(void);
	void releasePropInfoLayout(void);
	void ButtonCallBack(CCObject *pSender);
	void PropInfoUiClose();
//****************Added By Even**************/
public:

	Layout* PropInfoLayout;
	int propid;
	CommonWidgetType type;
};

class HelpWidgt:public CCObject
{
public:
	HelpWidgt(void);

public:
	static void CloseCallBackEx(void);

	Layout* getHelpLayout(void);
	void releaseHelpLayout(void);
	void NextPagButCallBack(CCObject* sender);
	void helpUiClose();
	void CloseCallBack(CCObject *pSender);

public:
	Layout			*HelpLayout;
	CommonWidgetType type;
};



class BuyGemWidget:public CCObject
{
public:
	BuyGemWidget();

public:
	Layout*  getBuyGemLayer(void);
	void releaseGemLayout(void);
	void ButtonCallBack(CCObject *pSender);
	void addGemItemtoList(void);
	void BuyGemUiClose();
	//****************Added By Even**************/
public:

	Layout* BuyGemLayout;
	CommonWidgetType type;
};


class SystemTools:public CCObject
{
public:
	SystemTools(void);

public:
	static void CloseCallBackEx(void);

	Layout* getSystemToolsLayout(void);
	void releaseSystemToolsLayout(void);
	void toolsmenuitemCallBack(CCObject *pSender);
	void MusicBtnCallBack(CCObject *pSender);
	void CloseCallBack(CCObject *pSender);
	void SystemtoolsClose(void);
	void funCallGameQuit(void);

public:
	Layout			*SystemtoolsLayout;
	CommonWidgetType type;
};

enum
{
	SUCCESSUI_BTNTAG_CONFIRM,
	SUCCESSUI_BTNTAG_TOMAP,
	SUCCESSUI_BTNTAG_NETERR,
	SUCCESSUI_BTNTAG_DELFRIENDCONFIRM,
	SUCCESSUI_BTNTAG_DELFRIENDCANCEL,
	SUCCESSUI_BTNTAG_REMINDNETWORK,

};

class SuccessWidget:public CCObject
{
public:
	SuccessWidget(void);
	~SuccessWidget(void);

public:
	static void CloseCallBackEx(void);

	Layout* getSuccessLayout(void);
	void releaseSuccessLayout(void);
	void ButtonCallBack(CCObject *pSender);
	void ButtonClose(void);

public:
	Layout			*SuccessLayout;
	CommonWidgetType type;
	int		sucType;
	int		data;
};

class SurpassFriend:public CCObject
{
public:
	SurpassFriend(void);
	~SurpassFriend(void);

public:
	Layout* getSurpassFriendLayout(void);
 	void ButtonCallBack(CCObject *pSender);
	UIWidget* addHeadImg(UserFriendInfoStr player);
	void CloseCallBack();
public:
	Layout			*SurpassFriendLayout;
};

enum
{
	UPDATAGAME_
};

enum
{
	TAG_FORUPDATA_NOWUPDATA,
	TAG_FORUPDATA_WAITUPDATA,
};

class UpdataGameWidget : public CCObject
{
public:
	UpdataGameWidget(void);
	~UpdataGameWidget(void);

public:
	Layout* getUpdataGameLayout(void);
	void ButtonCallBack(CCObject *pSender);
	void releaseLayout(void);
public:
	Layout			*UpdataGameLayout;
};

class GameShopWidget : public CCObject
{
public:
	GameShopWidget(void);
	~GameShopWidget(void);
public:
	Layout* getGameShopLayout(void);
	void ShopExitCallBack(CCObject *pSender);
	
	void InitShopScrollview();
	UIImageView* AddShopItem(int color, int propId, char* propName,char* propPrice);
	void RemoveShop();

	//购买道具按钮回调，调用JAVA接口
	void BuybtnCallback(CCObject* sender);
public:
	Layout			*GameShopLayout;
public:
	CommonWidgetType type;
	int m_buyNum;
	int m_buyPropid;
};


//新界面，超级大礼包
class GameSuperGiftWidget : public CCObject
{
public:
	GameSuperGiftWidget();
	~GameSuperGiftWidget();

	Layout* getGameSuperGiftLayout();

	//领取礼包回调
	void GetGiftCallback(CCObject* sender);
	//退出界面回调
	void GameGiftExit(CCObject* sender);

private:
	Layout			*GameSuperGiftLayout;

};

class GameVipWidget:public CCObject
{
public:
	GameVipWidget(void);
	~GameVipWidget(void);

public:
	Layout* getGameVipLayout(void);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);
public:
	Layout			*GameVipLayout;
};

class GameGiftWidget:public CCObject
{
public:
	GameGiftWidget(void);
	~GameGiftWidget(void);

public:
	Layout* getGameGiftLayout(int type);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);

public:
	Layout			*GameGiftLayout;

	bool m_isSelf;			//是否主动从地图界面购买
};


class GameRankWidget:public CCObject
{
public:
	GameRankWidget(void);
	~GameRankWidget(void);

public:
	Layout* getGameRankLayout(int type);
	void ExitCallBack(CCObject *pSender);
	void ButtonSelLabel(CCObject *pSender);
	void ButtonSendCandy(CCObject *pSender);
	void InviteButCallBack(CCObject *pSender);

public:
	void setRankLabel(int index);
	void AddFriendListContent();
	void AddWorldFriendListContent();
public:
	Layout			*GameRankLayout;
};


class GameSignInWidget:public CCObject
{
	enum
	{
		TAG_SIGNSTATE_DISABLED = 0, //　不可签
		TAG_SIGNSTATE_QD = 1,		//	签到
		TAG_SIGNSTATE_BQ = 2,		//　补签　
	};
public:
	GameSignInWidget(void);
	~GameSignInWidget(void);

public:
	Layout* getSignInLayout();
	void BtnSignInItemCallBack(CCObject* pSender);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);
	void setSignInRawardInfo(int day);
	void updataSignInfo(void);
	int getCurSignStart(void);//　1:签到状态　　2:为补签状态　　０：不可签到　也不可补签

public:
	Layout			*GameSignInLayout;

};



class GameUnlockLevelWidget:public CCObject
{
public:
	GameUnlockLevelWidget(void);
	~GameUnlockLevelWidget(void);

public:
	Layout* getGameUnlockLevelLayout(int level);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);

public:
	Layout			*m_GameUnlockLevelLayout;
	int m_Currentlevel;
};

//转盘
class GameRouletteWidget:public CCObject
{
public:
	GameRouletteWidget(void);
	~GameRouletteWidget(void);

public:
	Layout* getGameRouletteLayout(int level);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);
	void ExitCallBack1(void);
public:
	int AdjustRouletteProbability(void);
	void RewardCallBack(void);

public:
	Layout			*m_GameRouletteLayout;
	int				m_RewardType;
	UILabel			*m_RemindDes;

};

//支付widget
class GamePayWidget:public CCObject
{
public:
	GamePayWidget(void);
	~GamePayWidget(void);

public:
	Layout* getGamePayLayout(int type);
	void ButtonCallBack(CCObject *pSender);
	void ExitCallBack(CCObject *pSender);
	void WidgetRemove();
public:
	Layout			*m_GamePayLayout;
	int				m_PayType;
};

class GiftRewardEffWidget:public CCObject
{
public:
	GiftRewardEffWidget(void);
	~GiftRewardEffWidget(void);

public:
	Layout* getGiftEffectLayout(int ui_type);
	void ButtonCallBack(CCObject *pSender);
	void CallFunOpenGift(void);
	void CallFuncConfirm(void);
	void CallFunGoodsFly(CCNode* sender, void* data);
	void releaseGiftEffectLayout(void);
	void PropFadeOutCallBack(CCObject* sender);
public:
	Layout			*m_GiftEffectLayout;
	CommonWidgetType type;
	int				m_UiType;
public:
	int m_CurrentDay;
public:
	int m_RouletteReward;
};



class CommonWidgt:public CCLayer
{
public:
	CommonWidgt(void);
	~CommonWidgt();

public:

	static Layout*  getGamePayWidgetUI( CommonWidgetType type ,int widget_type);
	static Layout*  getGameRankWidgetUI( CommonWidgetType type );
	static Layout*  getGameUnlockLevelUI( CommonWidgetType type ,int level);
	static Layout*  getGameGiftUI( CommonWidgetType type,int pra );
	static Layout*  getGameVipUI( CommonWidgetType type );
	static Layout*  getGameShopUI( CommonWidgetType type );
	static Layout*  getGameSuperGiftUI( CommonWidgetType type );	//超级礼包
	static Layout*  getUpdataGameUI( CommonWidgetType type);
	static Layout*	getSystemToolsUI(CommonWidgetType type);
	static Layout*	getHelpUI( CommonWidgetType type );
	static Layout*	getPropInfoUI( CommonWidgetType type, int propid );
	static Layout*	getSuccessUI( CommonWidgetType type ,int sucType, int data = 0);
	static Layout*	getBuyGemUI( CommonWidgetType type );
	static Layout*  getSurpassFriendUI();
	static Layout*	getSignInUI(void);

	static Layout*  getGiftRewardUI(CommonWidgetType type, int ui_type,int data);
	static Layout*  getGameRouletteWidgetUI( CommonWidgetType type );	//转盘

	static void releaseWidgt(void);
public:
	static GamePayWidget* m_GamePayWidget;
	static GameRankWidget* m_GameRankWidget;
	static UpdataGameWidget* Updatalayout;
	static HelpWidgt* Helplayout;
	static SystemTools* Systemlayout;
	static PropInfoWidget* PropWidgetLayout;
	static SuccessWidget* SuccessWidgetLayout;
	static BuyGemWidget* BuyGemWidgetLayout;
	static SurpassFriend* SurpassFriendLayout;
	static GameShopWidget* m_GameShopLayout;
	static GameVipWidget* m_GameVipWidget;
	static GameGiftWidget* m_GameGiftWidget;
	static GameUnlockLevelWidget* m_GameUnlockLevelWidget;
	static GameSignInWidget* m_SignInWidget;

	static GameRouletteWidget* m_GameRouletteWidget;
	static GiftRewardEffWidget* m_GiftRewardWidget;
	static GameSuperGiftWidget* m_SuperGiftWidget;;

};
#endif