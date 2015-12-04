#ifndef CANDY_PARTICLE__H
#define CANDY_PARTICLE__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;



typedef enum
{
	CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT,				//双倍得分的火焰特效
	CANDY_PARTICLE_DOUBLESCORE_EFFECT,				//双倍得分特效
	CANDY_PARTICLE_CHUNZI_EFFECT,				//锤子特效
	CANDY_PARTICLE_SHENDENGOPEN_EFFECT,			//神灯开启特效
	CANDY_PARTICLE_SHENDENGYAODONG_EFFECT,		//神灯摇动特效
	CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT,		//神灯炸开特效
	CANDY_PARTICLE_YINTAO_EFFECT,				//运输樱桃掉落特效
	CANDY_PARTICLE_WUYUN_EFFECT,				//失败界面乌云特效
	CANDY_PARTICLE_CANDYCRUSH_EFFECT,
	CANDY_PARTICLE_WIN_EFFECT,					//胜利界面彩带特效
	CANDY_PARTICLE_PRESS_PROP,
	CANDY_PARTICLE_REWARD_LIGHT,
	CANDY_PARTICLE_WIN_LIGHT,
	CANDY_PARTICLE_TARGET_ICON,
	CANDY_PARTICLE_CANDY_APPEAR,
	CANDY_PARTICLE_STAGE_CLEAR,
	CANDY_PARTICLE_STAGE_FAILED1,
	CANDY_PARTICLE_STAGE_FAILED2,
	CANDY_PARTICLE_ROULETEE_EDGE,
	CANDY_PARTICLE_ROULETEE_END,
	CANDY_PARTICLE_LIGHT,
	CANDY_PARTICLE_USE_PROP1,
	CANDY_PARTICLE_USE_PROP2,
	CANDY_PARTICLE_USE_PROP3,
	CANDY_PARTICLE_USE_PROP4,
	CANDY_PARTICLE_USE_PROP5,
	CANDY_PARTICLE_USE_PROP6,
	CANDY_PARTICLE_USE_PROP7,
	CANDY_PARTICLE_PROP_BUTTON,
	CANDY_PARTICLE_GUIDE_FINGER,
	CANDY_PARTICLE_RESORT_IN,
	CANDY_PARTICLE_RESORT_OUT,	
	CANDY_PARTICLE_JAR_FRONT,
	CANDY_PARTICLE_JAR_BACK,
	CANDY_PARTICLE_JAR,
	CANDY_PARTICLE_EXPLOSION,
	CANDY_PARTICLE_CHANGE_STRIPLE,
	CANDY_PARTICLE_RCOLOR,
	CANDY_PARTICLE_RBOMB,
	CANDY_PARTICLE_RSTRIP,
	CANDY_PARTICLE_BLINK_PERCENT,
	CANDY_PARTICLE_STAR_PERCENT1,
	CANDY_PARTICLE_STAR_PERCENT2,
	CANDY_PARTICLE_STAR_PERCENTING,
	CANDY_PARTICLE_STAR_PERCENTDONE,
	CANDY_PARTICLE_STAR_FIREWORKS,
	CANDY_PARTICLE_NORMAL_EXCHANGE,
	CANDY_PARTICLE_NORMAL_DISPEL,
	CANDY_PARTICLE_BREAK_LICORICES,
	CANDY_PARTICLE_BREAK_CREAM,
	CANDY_PARTICLE_BREAK_LOCK,
	CANDY_PARTICLE_BREAK_CHOCOLATE,
	CANDY_PARTICLE_BREAK_JEELY,
	CANDY_PARTICLE_BREAK_JEELY2,
	CANDY_PARTICLE_SPE_BOMB,
	CANDY_PARTICLE_SPE_HORIZON,
	CANDY_PARTICLE_SPE_VERTICAL,
	CANDY_PARTICLE_SPE_COLOR_EMIT,
	CANDY_PARTICLE_SPE_COLOR_FIRE,
	CANDY_PARTICLE_SPE_COLOR_TARGET,
	CANDY_PARTICLE_COM_BB,
	CANDY_PARTICLE_COM_BS,
	CANDY_PARTICLE_COM_SS,
	CANDY_PARTICLE_COM_CC,//play_Game_MAX
	CANDY_LOGIN_BOOMFLY_EFF,
	CANDY_MAP_ACTIVE_NEW,
	CANDY_MAP_ACTIVE_NEW2,
	CANDY_MAP_ACTIVE_LOVELIFE,
	CANDY_PARTICLE_SONGXIN_EFFECT,		//送心特效
	CANDY_PARTICLE_XINFENG_EFFECT,		//消息特效
	CANDY_PARTICLE_ADDLIFE_EFFECT,		//消息特效
	CANDY_PARTICLE_SONGDAOJU_EFFECT,	//赠送道具特效
	CANDY_LOGIN_FLASH_EFFECT,			//登录界面闪烁
	CANDY_UNLOCKLEVEL_EFFECT,			//解锁界面
	CANDY_EFFECT_TEST,			//登录界面闪烁
	CANDY_GIFT_BACK_EFFECT,				//宝箱特效下
	CANDY_GIFT_FRONT_EFFECT,			//宝箱特效上
	CANDY_PARTICLE_NUM,

}CandyParticleType;


typedef struct
{
	int		x;
	int		y;
}CandyParticlePos;

typedef struct
{
	int		time;
	int		x;
	int		y;
}CandyParticleMove;


typedef struct 
{
	CandyParticleType type;
	int filenum;
	int isloop;
	std::vector<int> emission;
	std::vector<int> blend;
	std::vector<int> time;
	std::vector<int> rotate;
	std::vector<CandyParticlePos> pos;
	std::vector<CandyParticleMove> move;
}CandyParticleManager;

class CandyParticle:public CCNode
{
	public:
		CREATE_FUNC(CandyParticle);


	public:
		static void readParticleXML(int type, char* filepath);

	public:
		static void initCandyParicleForXml(void);
		static void initCandyParticle(void);
		static void destroyCandyParticle(void);
		static CCParticleSystemQuad* getCandyParticle(CandyParticleType type, int num);
		
	public:
		static CCNode* displayCandyParticleForXml(CandyParticleType type, CCPoint pos, CCNode* parent=NULL, int tag =0, int order = 10);
		static CCNode* displayCandyParticle(CandyParticleType type, CCPoint pos, CCNode* parent=NULL, int tag =0, int order = 10);

	public:
		void callbackParticle(CCNode* sender, void* data);
		void callBackRemove(CCNode* sender);
		
	public:
		static void colorfullCandyParticle(CandyParticleType type, CandyColor color1=CANDY_COLOR_NORMAL_NUM,CandyColor color2=CANDY_COLOR_NORMAL_NUM);

	public:
		static void setCandyParticleMove(CandyParticleType type, int time, int posX, int posY);

public:
	static std::vector<CandyParticleManager>	mCandyParticle;
		
};

#endif