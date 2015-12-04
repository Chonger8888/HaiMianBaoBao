#ifndef LOADING_SCENE__H
#define LOADING_SCENE__H
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../MsgMgr/HeadDownMgr.h"
#include "cocos2d.h"

USING_NS_CC;

/********************************* define aap res ***************************************/
#define CANDY_RES_FORGAME_NUM				4

// game use plist file
#define CANDY_PLIST_GAME_ELEMENT				"Image/CandyGame/Candy/CandyElement.plist"
#define CANDY_PLIST_GAME_BARRIER_TOP			"Image/CandyGame/Candy/CandyBarrierTop.plist"
#define CANDY_PLIST_GAME_BARRIER_BOTTOM			"Image/CandyGame/Candy/CandyBarrierBottom.plist"
#define CANDY_PLIST_GAME_UI_LAYOUT				"Image/CandyGame/CandyGameUi/CandyGameUi0.plist"
//#define CANDY_PLIST_GAME_UI_LAYOUT1				"Image/CandyGame/CandyGameUi/CandyGameUi1.plist"
// game use image file
#define CANDY_IMG_GAME_ELEMENT					"Image/CandyGame/Candy/CandyElement.png"
#define CANDY_IMG_GAME_BARRIER_TOP				"Image/CandyGame/Candy/CandyBarrierTop.png"
#define CANDY_IMG_GAME_BARRIER_BOTTOM			"Image/CandyGame/Candy/CandyBarrierBottom.png"
#define CANDY_IMG_GAME_UI_LAYOUT				"Image/CandyGame/CandyGameUi/CandyGameUi0.png"
//#define CANDY_IMG_GAME_UI_LAYOUT1				"Image/CandyGame/CandyGameUi/CandyGameUi1.png"
/*****************************************************************************************/


/********************************* define aap res ***************************************/
#define CANDY_RES_FORCOMMOND_NUM				2

//¡¡commond use plist file
#define CANDY_PLIST_COMMOND_SETTING1			"Image/MainMapUi/Tools/SystemTools0.plist"
#define CANDY_PLIST_COMMOND_SETTING2			"Image/MainMapUi/Tools/SystemTools1.plist"
// #define CANDY_PLIST_COMMOND_SETTING3			"Image/MainMapUi/Tools/SystemTools2.plist"
// #define CANDY_PLIST_COMMOND_SETTING4			"Image/MainMapUi/Tools/SystemTools3.plist"
// #define CANDY_PLIST_COMMOND_SETTING5			"Image/MainMapUi/Tools/SystemTools4.plist"
//#define CANDY_PLIST_COMMOND_SETTING6			"Image/MainMapUi/Tools/SystemTools5.plist"
//¡¡commond use image file
#define CANDY_IMG_COMMOND_SETTING1			"Image/MainMapUi/Tools/SystemTools0.png"
#define CANDY_IMG_COMMOND_SETTING2			"Image/MainMapUi/Tools/SystemTools1.png"
// #define CANDY_IMG_COMMOND_SETTING3			"Image/MainMapUi/Tools/SystemTools2.png"
// #define CANDY_IMG_COMMOND_SETTING4			"Image/MainMapUi/Tools/SystemTools3.png"
// #define CANDY_IMG_COMMOND_SETTING5			"Image/MainMapUi/Tools/SystemTools4.png"
//#define CANDY_IMG_COMMOND_SETTING6			"Image/MainMapUi/Tools/SystemTools5.png"
/*****************************************************************************************/


/********************************* define map res ***************************************/
#define CANDY_RES_FORMAP_NUM				(12 - 9)

//¡¡Map use plist file !
#define CANY_PLIST_MAP_MAINMAPUI0			"Image/MainMapUi/MainMapUi/MainMapUi0.plist"
//#define CANY_PLIST_MAP_MAINMAPUI1			"Image/MainMapUi/MainMapUi/MainMapUi1.plist"
//#define CANY_PLIST_MAP_MAINMAPUI2			"Image/MainMapUi/MainMapUi/MainMapUi2.plist"
//#define CANY_PLIST_MAP_GEMEFF				"Image/MainMapUi/gemeff/gemanimation.plist"

#define CANDY_PLIST_LOGIN_LOGINUI1			"Image/LoginUi/LoginUi0.plist"
#define CANDY_PLIST_LOGIN_LOGINUI2			"Image/LoginUi/LoginUi1.plist"


// Map use image file
#define CANY_IMG_MAP_MAINMAPUI0				"Image/MainMapUi/MainMapUi/MainMapUi0.png"
//#define CANY_IMG_MAP_MAINMAPUI1				"Image/MainMapUi/MainMapUi/MainMapUi1.png"
//#define CANY_IMG_MAP_MAINMAPUI2				"Image/MainMapUi/MainMapUi/MainMapUi2.png"
//#define CANY_IMG_MAP_GEMEFF					"Image/MainMapUi/MainMapUi/gemanimation.png"

//#define CANY_IMG_MAP_BIGMAP1				"Image/BigMap_1/BigMap1.jpg"
//#define CANY_IMG_MAP_BIGMAP2				"Image/BigMap_1/BigMap2.jpg"
//#define CANY_IMG_MAP_BIGMAP3				"Image/BigMap_1/BigMap3.jpg"
//#define CANY_IMG_MAP_BIGMAP4				"Image/BigMap_1/BigMap4.jpg"
//#define CANY_IMG_MAP_BIGMAP5				"Image/BigMap_1/BigMap5.jpg"
//#define CANY_IMG_MAP_BIGMAP6				"Image/BigMap_1/BigMap6.jpg"

#define CANDY_IMG_LOGIN_LOGINUI1			"Image/LoginUi/LoginUi0.png"
#define CANDY_IMG_LOGIN_LOGINUI2			"Image/LoginUi/LoginUi1.png"
/*****************************************************************************************/

typedef enum
{
	CANDY_SCENCE_DOWNLOAD,
	CANDY_SCENCE_MAIN_MAP,
	CANDY_SCENCE_LOGIN,
	CANDY_SCENCE_ROULETTE,
	CANDY_SCENCE_PLAY_GAME,	
}candyScenceType;

typedef enum
{
	LOGINUI_WIDGET_TYPE_HINT,
	LOGINUI_WIDGET_TYPE_UPDATA,
}LoginWidgetType;

class Loading: public CCLayer
{
public:
	CREATE_FUNC(Loading);

public:
	Loading(void);
	static CCScene* scene(candyScenceType type);

public:
	static void replaceScence(candyScenceType type);	

public:
	virtual bool init(void); 
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish(void); 
	virtual void onExit();

public:
	void HttpGetMyInfoAsyn(bool state);
	void HttpGetFriendListAsyn(bool state = false);
	void HttpGetHeadImgAsyn(void);
	void initPlayGameRes(void);
	void initMainMapRes(void);
	void changeScene(void);	
	void NetworkErrBtnCallback(void);
	void UPdataBtnBtnCallback(CCObject* pSender);
	void showWidget(LoginWidgetType type);

private:
	void FunNDActionCallback(CCNode* sender, void* data);
	void SoundOutLogin(void);
	UILayer* getWidgetUILayer(void);
	void initInterludeRes(void);
	void headMoveDelay(float t);
	void loadingMapCallBack(CCObject *obj);
	void loadingGameCallBack(CCObject *obj);

public:
	bool m_isDownOver;
	UILayer* widgetUiLayer;

public:

	CCLabelTTF* m_pLabelPercent;
	static candyScenceType scenceType;
	//HeadDownMgr* m_pHeadDownPic;
	static Loading*		m_loading;
/*	HeadDownMgr* m_pHeadDownPic;*/

};


#endif
