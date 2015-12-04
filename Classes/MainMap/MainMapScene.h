#ifndef MAIN_MAP_SCENE__H
#define MAIN_MAP_SCENE__H

#include "cocos2d.h"
#include "MainMapCommon.h"
#include "../MsgMgr/AnalyseJson.h"

USING_NS_CC;
using namespace cocos2d::extension;

// entey main map for scene
enum
{
	SCENE_FOR_OTHER,
	SCENE_FOR_PLAYGAME_NEXT,
};

typedef enum
{
	MAP_TOUCH_DRAG,
	MAP_TOUCH_SCALE,
	MAP_TOUCH_DEFAULT,
}MapTouchType;

typedef enum
{
	GAME_STATE_SUCCEE,
	GAME_STATE_SUCCEE_NEXT,
	GAME_STATE_FAIL,
}GAME_STAUE;

typedef enum
{
	KEY_EMPTY,
	KEY_FIRST,
	KEY_SECOND,
}KeyStateType;

typedef enum
{
	MAP_SCALE_NULL,
	MAP_SCALE_MAGNIFY,
	MAP_SCALE_SHRINK,
}MapScaleType;

enum
{
	MUSIC_ITEM_BUTTON_E = 0,
	MUSIC_ITEM_MOVEHEAD_E,
	MUSIC_ITEM_ROULETTE_E,
	MUSIC_ITEM_MAX_NUM,
};

#define GAME_MAX_LEVEL_NUM	225

class TouchBlockerLayer;
class MainMap: public CCLayer
{
public:
	CREATE_FUNC(MainMap);
	/**
     * Default constructor
     */
    MainMap(void);
public:
	static CCScene* scene(bool pare);

public:
	virtual bool init(void); 
	virtual void update(float time);
public:
	virtual void onEnter(void);
	virtual void onEnterTransitionDidFinish(void); 
	virtual void onExit(void);

public:
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

public:
//	virtual void keyBackClicked();

private:
	void MapBorderCheck(void);
	void buttonCallBack(CCObject *pSender);

	void LevelInfoNextCB(CCObject *pSender);
	CCActionInterval* getMoveAction(float time, CCPoint pos);

	void callFuncMoveHead(void);
	void callFuncRewardCandy(void);


public:
	static void playMapBgm(void);

	// For here entey main map scene, playgame call. 
	// GAME_STAUE==> GAME_STATE_SUCCEE GAME_STATE_SUCCEE_NEXT  GAME_STATE_FAIL 
	static void EnteyMapScene( int para );

public:
	static void initMapLuaFile();
	static void setPassStageNum(int num);
	static int getPassStageNum(void);
	void HideMapUi(void);
	void DisplayMapUi(void);
	void PlayEffect(int index);

	CCPoint& getLevelNumFromLua(int level);
	unsigned int getTableNumFromLua(const int level, const int num);
	static unsigned int getDataNumFromLua(int num);
	void addMapLevelButton(int level,int maxlevel , int score,bool isEnabled);

	void initPreloadEffect(void);
	void unLoadEffect(void);
	void StopAllEffect(void);
	void stopAllMusic( void );
	void setHeadMove(void);
	void showFriendHeadImg();
	void setVipHead(void);

private:
	void initMapBackground(void);
	void MoveMapCallback(void);
	void FirstConsumsLifeDelay(float t);
private:
	void setMapScale(float newScale);
	void updateMapScale(float time);
	void setMapPos(CCPoint pos);
	void updateMapPos(float time);
	void headMoveDelay(float t);
	void UpdataDelayTouchEnabled(float t);

	// Partical
	void initParical(void);
	void getPartical(void);
	void playParticalType(void);
	void releasePartical(void);
	void setHeadImg(UserFriendInfoStr player);
	void funcallBarMoveOut(void);
	void funcallBarMoveEntry(void);

private:
	CCPoint touchPoint[2];
	CCPoint firstPoint;
	MapTouchType touchType;
	int touchNum;
	float m_moveTime;
	float m_doubleClickTime;
	bool m_isMapScale;
	bool m_isMove;
	KeyStateType	m_keystate;

	char*	EffectMusicPath[MUSIC_ITEM_MAX_NUM];

public:
	UILayer* getBigMapUILayer(){return bigMapUiLayer;}
private:

	UILayer* widgetUiLayer;
	UILayer* bigMapUiLayer;
	Layout* bigMapLayout;
	Layout*	bigDlgLayout;
	Layout* gameNextLayout;
	CCNode* m_pParticle;
	CCPoint m_MapOffset;
	UIImageView* m_particlePos;
	CCParticleSystemQuad* particle;
public:
	UIImageView *m_pHeadbgImg;
	MapScaleType	m_mapScaleType;
	cocos2d::extension::UIPanel* m_pPanel;
	CCPoint			m_nLevelPos;

	bool m_isTouches;

	static MainMap* m_mainmap;
	static float 	currentScale;
	static CCPoint  currentPos;
//	static int m_MapLevelData[GAME_MAX_LEVEL_NUM][4];
	static int m_LevInfoShowNum;
	static bool	m_isFirst;
	static int m_GameState;



};


#endif