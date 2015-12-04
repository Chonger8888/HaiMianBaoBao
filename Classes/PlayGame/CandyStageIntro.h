#ifndef CANDY_STAGE_INTRO__H
#define CANDY_STAGE_INTRO__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;
using namespace cocos2d::extension;

typedef enum
{
	STAGE_INTRO_MAIN_MAP,
	STAGE_INTRO_PLAY_GAME,
}StageIntroType;

#define COLLECT_TYPE_IMG_PATH			"Image/CandyGame/CollectType"

class CandyStageIntroLayout:public CCObject
{
	public:
		CandyStageIntroLayout();
	public:
		Layout* getStageIntroLayout(int level = 0);
		void initTargetInformat(int level);
		void releaseStageIntroLayout(void);
		void updatePropNum(int type);

	public:
		void buyProp(int type);
		void buyPropCb(int propId);
		void AddFriendToRank();
		
	private:
		void stageInfoPlayCallBack(CCObject *pSender);
		void stageInfoReturnCallBack(CCObject *pSender);
		void stageInfoUsePropCallBack(CCObject *pSender);
		void showPropBuy();
		void ShareBtnCb(CCObject *pSender);
		int TypeToCordinate(int type);
public:
		Layout			*stageIntroLayout;
		UIButton		*PropButton[5];
		UIImageView		*PropPriceShow[5];
		UIImageView	*PropBuy[5];
		UIImageView	*PropNumBg[5];
		UIImageView	*PropSelected[5];
		UILabelAtlas		*PropNumLabel[5];
		UIButton *m_shareWeixin;
		UIButton *m_shareTWeibo;
		UIButton *m_shareSWeibo;
		StageIntroType	type;
		int				lastLevel;
};

class CandyStageIntro
{
	public:
		static Layout* getLayout(StageIntroType type,int level = 0);
		static void releaseLayout(void);
		static void buyPropCallBack(int propId);

	public:
		static CandyStageIntroLayout* layout;
};
#endif