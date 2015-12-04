#ifndef PLAY_GAME_SCENE__H
#define PLAY_GAME_SCENE__H

#include "cocos2d.h"

USING_NS_CC;

class PlayGame : public CCLayer
{
	public:
   		CREATE_FUNC(PlayGame);
		virtual bool init(void); 
		virtual void update(float time);
		virtual void onEnter(void);
		virtual void onExit(void);
	public:
    		static CCScene* scene(void);

	public:
		//可以不使用
		static PlayGame* currentLayer;

		void initPlayGameRes(void);

	private:
		void startCrazyHappyMode(cocos2d::CCObject *pSender);
		void crazyModeUpdateTest(float time);

	public:
		void lastLevelCallBack(cocos2d::CCObject *pSender);
		void nextLevelCallBack(cocos2d::CCObject *pSender);

	public:
		void addBg(bool mixGrid = true);
		void addGameBg(void);
		void addTestMenu(void);
		void updateLife(float dt);
	public:
		bool lastMixGridState;
};

#endif
