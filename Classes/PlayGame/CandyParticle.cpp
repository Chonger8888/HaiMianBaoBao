#include "CandyParticle.h"
#include "CandyManager.h"


#define CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM			1
#define CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM				7
#define CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM				4
#define CANDY_PARTICLE_CHUNZI_EFFECT_NUM					3
#define CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM				3
#define CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM			3
#define CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM			5
#define CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM			2
#define CANDY_PARTICLE_SONGXIN_EFFECT_NUM			2
#define CANDY_PARTICLE_XINFENG_EFFECT_NUM			2
#define CANDY_PARTICLE_YINTAO_EFFECT_NUM			3
#define CANDY_PARTICLE_WUYUN_EFFECT_NUM			2
#define CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM	2
#define CANDY_PARTICLE_WIN_EFFECT_NUM			3
#define CANDY_PARTICLE_PRESS_PROP_NUM			1
#define PARTICLE_REWARD_LIGHT_NUM			2
#define PARTICLE_WIN_LIGHT_NUM			2
#define PARTICLE_TARGET_ICON_NUM			3
#define PARTICLE_CANDY_APPEAR_NUM		1
#define PARTICLE_STAGE_CLEAR_NUM			4
#define PARTICLE_STAGE_FAILED1_NUM		2
#define PARTICLE_STAGE_FAILED2_NUM		3
#define PARTICLE_ROULETEE_EDGE_NUM		2
#define PARTICLE_ROULETEE_END_NUM		4
#define PARTICLE_LIGHT_NUM					2
#define PARTICLE_USE_PROP1_NUM			2
#define PARTICLE_USE_PROP2_NUM			4
#define PARTICLE_USE_PROP3_NUM			3
#define PARTICLE_USE_PROP4_NUM			4
#define PARTICLE_USE_PROP5_NUM			4
#define PARTICLE_USE_PROP6_NUM			2
#define PARTICLE_USE_PROP7_NUM			4
#define PARTICLE_PROP_BUTTON_NUM		2
#define PARTICLE_GUIDE_FINGER_NUM		2
#define PARTICLE_RESORT_IN_NUM			4
#define PARTICLE_RESORT_OUT_NUM			4
#define PARTICLE_JAR_FRONT_NUM			1
#define PARTICLE_JAR_BACK_NUM				2
#define PARTICLE_JAR_NUM					2
#define PARTICLE_EXPLOSION_NUM			3
#define PARTICLE_CSTRIPLE_NUM				2
#define PARTICLE_RCOLOR_NUM				2
#define PARTICLE_RBOMB_NUM				3
#define PARTICLE_RSTRIP_NUM				2
#define PARTICLE_BLINK_PER_NUM			1
#define PARTICLE_STAR_PER1_NUM			3
#define PARTICLE_STAR_PER2_NUM			4
#define PARTICLE_STAR_PERING_NUM			1
#define PARTICLE_STAR_PERDONE_NUM		1
#define PARTICLE_STAR_FIRE_NUM			4
#define PARTICLE_EXCHANGE_NUM			1
#define PARTICLE_DISPEL_NUM				2
#define PARTICLE_LICORICES_NUM			3
#define PARTICLE_CREAM_NUM				4
#define PARTICLE_LOCK_NUM					7
#define PARTICLE_CHOCOLATE_NUM			4
#define PARTICLE_JELLY_NUM					3
#define PARTICLE_JELLY2_NUM				2
#define PARTICLE_BOMB_NUM					5
#define PARTICLE_HORIZON_NUM				7
#define PARTICLE_VERTICAL_NUM				7
#define PARTICLE_CEMIT_NUM				10
#define PARTICLE_CFIRE_NUM					3
#define PARTICLE_CTARGET_NUM				5
#define PARTICLE_COMBB_NUM				6
#define PARTICLE_COMBS_NUM				13
#define PARTICLE_COMSS_NUM				14
#define PARTICLE_COMCC_NUM				5
#define MAP_ACTIVE_NEW_NUM				1
#define MAP_ACTIVE_NEW2_NUM				1
#define MAP_ACTIVE_LOVEIIFE_NUM			1
#define LOGIN_ACTIVE_BOOMFLY			1
#define MAP_ACTIVE_ADDLIFEMESSAGE		2		
#define LOGIN_FLASH_EFF_NUM				1

#define MAP_GIFT_EFFECT_FRONT_NUM			3		
#define MAP_GIFT_EFFECT_BACK_NUM			2

static int particleDoubleScoreFireEffectEmission[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] ={300};
static int particleDoubleScoreFireEffectBlend[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] ={1};
static int particleDoubleScoreFireEffectTime[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] ={0};
static int particleDoubleScoreFireEffectRotate[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] ={0};
static CandyParticlePos particleDoubleScoreFireEffecEffectPos[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM ] ={{0,0}};
static CandyParticleMove particleDoubleScoreFireEffecEffectMove[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleDoubleScoreFireEffecEffect[CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM] ={0};


static int particleUnlockLevelEffectEmission[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] ={10,10,10,10,10,10,10};
static int particleUnlockLevelEffectBlend[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] ={0};
static int particleUnlockLevelEffectTime[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] ={0};
static int particleUnlockLevelEffectRotate[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] ={0};
static CandyParticlePos particleUnlockLevelEffecEffectPos[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM ] ={{0,0}};
static CandyParticleMove particleUnlockLevelEffecEffectMove[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleUnlockLevelEffecEffect[CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM] ={0};


static int particleDoubleScoreEffectEmission[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] ={10,10,80,300};
static int particleDoubleScoreEffectBlend[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] ={1,1,1,1};
static int particleDoubleScoreEffectTime[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] ={0,500,0,600};
static int particleDoubleScoreEffectRotate[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] ={0};
static CandyParticlePos particleDoubleScoreEffecEffectPos[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM ] ={{0,0},{0,0},{0,-40}};
static CandyParticleMove particleDoubleScoreEffecEffectMove[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleDoubleScoreEffecEffect[CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM] ={0};


static int particleChuiZiEffectEmission[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] ={30,50,300};
static int particleChuiZiEffectBlend[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] ={1,1,1};
static int particleChuiZiEffectTime[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] ={0};
static int particleChuiZiEffectRotate[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] ={0};
static CandyParticlePos particleChuiZiEffecEffectPos[CANDY_PARTICLE_CHUNZI_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleChuiZiEffecEffectMove[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleChuiZiEffecEffect[CANDY_PARTICLE_CHUNZI_EFFECT_NUM] ={0};


static int particleShenDengOpenEffectEmission[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] ={20,30,10};
static int particleShenDengOpenEffectBlend[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] ={1,1,1};
static int particleShenDengOpenEffectTime[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] ={0};
static int particleShenDengOpenEffectRotate[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] ={0};
static CandyParticlePos particleShenDengOpenEffectPos[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleShenDengOpenEffectMove[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleShenDengOpenEffect[CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM] ={0};


static int particleShenDengYaoDongEffectEmission[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] ={20,15,20};
static int particleShenDengYaoDongEffectBlend[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] ={1,1,1};
static int particleShenDengYaoDongEffectTime[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] ={0};
static int particleShenDengYaoDongEffectRotate[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] ={0};
static CandyParticlePos particleShenDengYaoDongEffectPos[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM ] ={{0,0},{0,0},{0,-50}};
static CandyParticleMove particleShenDengYaoDongEffectMove[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleShenDengYaoDongEffect[CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM] ={0};



static int particleShenDengZhaKaiEffectEmission[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] ={60,100,20,100,80};
static int particleShenDengZhaKaiEffectBlend[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] ={0,1,1,0,1};
static int particleShenDengZhaKaiEffectTime[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] ={0};
static int particleShenDengZhaKaiEffectRotate[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] ={0};
static CandyParticlePos particleShenDengZhaKaiEffectPos[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleShenDengZhaKaiEffectMove[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleShenDengZhaKaiEffect[CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM] ={0};



static int particleSongDaojuEffectEmission[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] ={300,20};
static int particleSongDaojuEffectBlend[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] ={1,1};
static int particleSongDaojuEffectTime[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] ={0,0};
static int particleSongDaojuEffectRotate[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] ={0};
static CandyParticlePos particleSongDaojuEffectPos[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleSongDaojuEffectMove[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleSongDaojuEffect[CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM] ={0};

static int particleSongXinEffectEmission[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] ={10,100};
static int particleSongXinEffectBlend[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] ={1,1};
static int particleSongXinEffectTime[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] ={0,0};
static int particleSongXinEffectRotate[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] ={0};
static CandyParticlePos particleSongXinEffectPos[CANDY_PARTICLE_SONGXIN_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleSongXinEffectMove[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] = {{0,0,0},{700,0,80}};
static CCParticleSystemQuad* particleSongXinEffect[CANDY_PARTICLE_SONGXIN_EFFECT_NUM] ={0};

static int particleXinFengEffectEmission[CANDY_PARTICLE_XINFENG_EFFECT_NUM] ={10,100};
static int particleXinFengEffectBlend[CANDY_PARTICLE_XINFENG_EFFECT_NUM] ={1,1};
static int particleXinFengEffectTime[CANDY_PARTICLE_XINFENG_EFFECT_NUM] ={0,0};
static int particleXinFengEffectRotate[CANDY_PARTICLE_XINFENG_EFFECT_NUM] ={0};
static CandyParticlePos particleXinFengEffectPos[CANDY_PARTICLE_XINFENG_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleXinFengEffectMove[CANDY_PARTICLE_XINFENG_EFFECT_NUM] = {{0,0,0},{700,0,80}};
static CCParticleSystemQuad* particleXinFengEffect[CANDY_PARTICLE_XINFENG_EFFECT_NUM] ={0};

static int particleYinTaoEffectEmission[CANDY_PARTICLE_YINTAO_EFFECT_NUM] ={100,100,50};
static int particleYinTaoEffectBlend[CANDY_PARTICLE_YINTAO_EFFECT_NUM] ={1,1,1};
static int particleYinTaoEffectTime[CANDY_PARTICLE_YINTAO_EFFECT_NUM] ={0,0,0};
static int particleYinTaoEffectRotate[CANDY_PARTICLE_YINTAO_EFFECT_NUM] ={0};
static CandyParticlePos particleYinTaoEffectPos[CANDY_PARTICLE_YINTAO_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleYinTaoEffectMove[CANDY_PARTICLE_YINTAO_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleYinTaoEffect[CANDY_PARTICLE_YINTAO_EFFECT_NUM] ={0};

static int particleWuYunEffectEmission[CANDY_PARTICLE_WUYUN_EFFECT_NUM] ={100,150};
static int particleWuYunEffectBlend[CANDY_PARTICLE_WUYUN_EFFECT_NUM] ={1,0};
static int particleWuYunEffectTime[CANDY_PARTICLE_WUYUN_EFFECT_NUM] ={0};
static int particleWuYunEffectRotate[CANDY_PARTICLE_WUYUN_EFFECT_NUM] ={0};
static CandyParticlePos particleWuYunEffectPos[CANDY_PARTICLE_WUYUN_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleWuYunEffectMove[CANDY_PARTICLE_WUYUN_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleWuYunEffect[CANDY_PARTICLE_WUYUN_EFFECT_NUM] ={0};


static int particleCandyCrushEffectEmission[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] ={200,60};
static int particleCandyCrushEffectBlend[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] ={1,1};
static int particleCandyCrushEffectTime[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] ={0};
static int particleCandyCrushEffectRotate[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] ={0};
static CandyParticlePos particleCandyCrushEffectPos[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleCandyCrushEffectMove[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleCandyCrushEffect[CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM] ={0};



static int particleWinEffectEmission[CANDY_PARTICLE_WIN_EFFECT_NUM] ={5,5,5};
static int particleWinEffectBlend[CANDY_PARTICLE_WIN_EFFECT_NUM] ={0};
static int particleWinEffectTime[CANDY_PARTICLE_WIN_EFFECT_NUM] ={0};
static int particleWinEffectRotate[CANDY_PARTICLE_WIN_EFFECT_NUM] ={0};
static CandyParticlePos particleWinEffectPos[CANDY_PARTICLE_WIN_EFFECT_NUM ] ={{0}};
static CandyParticleMove particleWinEffectMove[CANDY_PARTICLE_WIN_EFFECT_NUM] = {0};
static CCParticleSystemQuad* particleWinEffect[CANDY_PARTICLE_WIN_EFFECT_NUM] ={0};


static int particlePressPropEmission[CANDY_PARTICLE_PRESS_PROP_NUM] ={40};
static int particlePressPropBlend[CANDY_PARTICLE_PRESS_PROP_NUM] ={1};
static int particlePressPropTime[CANDY_PARTICLE_PRESS_PROP_NUM] ={0};
static int particlePressPropRotate[CANDY_PARTICLE_PRESS_PROP_NUM] ={0};
static CandyParticlePos particlePressPropPos[CANDY_PARTICLE_PRESS_PROP_NUM ] ={{0}};
static CandyParticleMove particlePressPropMove[CANDY_PARTICLE_PRESS_PROP_NUM] = {0};
static CCParticleSystemQuad* particlePressProp[CANDY_PARTICLE_PRESS_PROP_NUM] ={0};


static int particleRewardLightEmission[PARTICLE_REWARD_LIGHT_NUM] ={100,30};
static int particleRewardLightBlend[PARTICLE_REWARD_LIGHT_NUM] ={1,1};
static int particleRewardLightTime[PARTICLE_REWARD_LIGHT_NUM] ={0};
static int particleRewardLightRotate[PARTICLE_REWARD_LIGHT_NUM] ={0};
static CandyParticlePos particleRewardLightPos[PARTICLE_REWARD_LIGHT_NUM ] ={{0}};
static CandyParticleMove particleRewardLightMove[PARTICLE_REWARD_LIGHT_NUM] = {0};
static CCParticleSystemQuad* particleRewardLight[PARTICLE_REWARD_LIGHT_NUM] ={0};

static int particleWinLightEmission[PARTICLE_WIN_LIGHT_NUM] ={100,30};
static int particleWinLightBlend[PARTICLE_WIN_LIGHT_NUM] ={1,1};
static int particleWinLightTime[PARTICLE_WIN_LIGHT_NUM] ={ 0};
static int particleWinLightRotate[PARTICLE_WIN_LIGHT_NUM] ={0};
static CandyParticlePos particleWinLightPos[PARTICLE_WIN_LIGHT_NUM ] ={0};
static CandyParticleMove particleWinLightMove[PARTICLE_WIN_LIGHT_NUM] = {0};
static CCParticleSystemQuad* particleWinLight[PARTICLE_WIN_LIGHT_NUM] ={0};

static int particleTargetIconEmission[PARTICLE_TARGET_ICON_NUM] ={300,50,30};
static int particleTargetIconBlend[PARTICLE_TARGET_ICON_NUM] ={1,1,1};
static int particleTargetIconTime[PARTICLE_TARGET_ICON_NUM] ={ 0,0,50};
static int particleTargetIconRotate[PARTICLE_TARGET_ICON_NUM] ={0};
static CandyParticlePos particleTargetIconPos[PARTICLE_TARGET_ICON_NUM ] ={{0},{-100,0}};
static CandyParticleMove particleTargetIconMove[PARTICLE_TARGET_ICON_NUM] = {0};
static CCParticleSystemQuad* particleTargetIcon[PARTICLE_TARGET_ICON_NUM] ={0};

static int particleCandyAppearEmission[PARTICLE_CANDY_APPEAR_NUM] ={300};
static int particleCandyAppearBlend[PARTICLE_CANDY_APPEAR_NUM] ={1};
static int particleCandyAppearTime[PARTICLE_CANDY_APPEAR_NUM] ={0};
static int particleCandyAppearRotate[PARTICLE_CANDY_APPEAR_NUM] ={0};
static CandyParticlePos particleCandyAppearPos[PARTICLE_CANDY_APPEAR_NUM ] ={{0,0}};
static CandyParticleMove particleCandyAppearMove[PARTICLE_CANDY_APPEAR_NUM] = {0};
static CCParticleSystemQuad* particleCandyAppear[PARTICLE_CANDY_APPEAR_NUM] ={0};

static int particleStageClearEmission[PARTICLE_STAGE_CLEAR_NUM] ={100,200,20,30};
static int particleStageClearBlend[PARTICLE_STAGE_CLEAR_NUM] ={1,1,1,1};
static int particleStageClearTime[PARTICLE_STAGE_CLEAR_NUM] ={0,50,0,10};
static int particleStageClearRotate[PARTICLE_STAGE_CLEAR_NUM] ={0};
static CandyParticlePos particleStageClearPos[PARTICLE_STAGE_CLEAR_NUM ] ={0};
static CandyParticleMove particleStageClearMove[PARTICLE_STAGE_CLEAR_NUM] = {0};
static CCParticleSystemQuad* particleStageClear[PARTICLE_STAGE_CLEAR_NUM] ={0};

static int particleStageFailed1Emission[PARTICLE_STAGE_FAILED1_NUM] ={200,200};
static int particleStageFailed1Blend[PARTICLE_STAGE_FAILED1_NUM] ={1,1};
static int particleStageFailed1Time[PARTICLE_STAGE_FAILED1_NUM] ={0};
static int particleStageFailed1Rotate[PARTICLE_STAGE_FAILED1_NUM] ={0};
static CandyParticlePos particleStageFailed1Pos[PARTICLE_STAGE_FAILED1_NUM ] ={{0,0},{0,0}};
static CandyParticleMove particleStageFailed1Move[PARTICLE_STAGE_FAILED1_NUM] = {0};
static CCParticleSystemQuad* particleStageFailed1[PARTICLE_STAGE_FAILED1_NUM] ={0};

static int particleStageFailed2Emission[PARTICLE_STAGE_FAILED2_NUM] ={300,200,200};
static int particleStageFailed2Blend[PARTICLE_STAGE_FAILED2_NUM] ={1,0,0};
static int particleStageFailed2Time[PARTICLE_STAGE_FAILED2_NUM] ={0};
static int particleStageFailed2Rotate[PARTICLE_STAGE_FAILED2_NUM] ={0};
static CandyParticlePos particleStageFailed2Pos[PARTICLE_STAGE_FAILED2_NUM ] ={{0,-30}};
static CandyParticleMove particleStageFailed2Move[PARTICLE_STAGE_FAILED2_NUM] = {0};
static CCParticleSystemQuad* particleStageFailed2[PARTICLE_STAGE_FAILED2_NUM] ={0};


static int particleRouleteeEdgeEmission[PARTICLE_ROULETEE_EDGE_NUM] ={500,500};
static int particleRouleteeEdgeBlend[PARTICLE_ROULETEE_EDGE_NUM] ={1,1};
static int particleRouleteeEdgeTime[PARTICLE_ROULETEE_EDGE_NUM] ={0};
static int particleRouleteeEdgeRotate[PARTICLE_ROULETEE_EDGE_NUM] ={0};
static CandyParticlePos particleRouleteeEdgePos[PARTICLE_ROULETEE_EDGE_NUM ] ={{350,0}, {-350,0}};
static CandyParticleMove particleRouleteeEdgeMove[PARTICLE_ROULETEE_EDGE_NUM] = {0};
static CCParticleSystemQuad* particleRouleteeEdge[PARTICLE_ROULETEE_EDGE_NUM] ={0};

static int particleRouleteeEndEmission[PARTICLE_ROULETEE_END_NUM] ={10,50,10,10};
static int particleRouleteeEndBlend[PARTICLE_ROULETEE_END_NUM] ={1,1,1,1};
static int particleRouleteeEndTime[PARTICLE_ROULETEE_END_NUM] ={0};
static int particleRouleteeEndRotate[PARTICLE_ROULETEE_END_NUM] ={0};
static CandyParticlePos particleRouleteeEndPos[PARTICLE_ROULETEE_END_NUM ] ={0};
static CandyParticleMove particleRouleteeEndMove[PARTICLE_ROULETEE_END_NUM] = {0};
static CCParticleSystemQuad* particleRouleteeEnd[PARTICLE_ROULETEE_END_NUM] ={0};

static int particleLightEmission[PARTICLE_LIGHT_NUM] ={10,20};
static int particleLightInBlend[PARTICLE_LIGHT_NUM] ={1,1};
static int particleLightInTime[PARTICLE_LIGHT_NUM] ={0};
static int particleLightInRotate[PARTICLE_LIGHT_NUM] ={0};
static CandyParticlePos particleLightPos[PARTICLE_LIGHT_NUM ] ={{0,-400}};
static CandyParticleMove particleLightMove[PARTICLE_LIGHT_NUM] = {0};
static CCParticleSystemQuad* particleLight[PARTICLE_LIGHT_NUM] ={0};

static int particleUseProp1Emission[PARTICLE_USE_PROP1_NUM] ={400,50};
static int particleUseProp1Blend[PARTICLE_USE_PROP1_NUM] ={1,1};
static int particleUseProp1Time[PARTICLE_USE_PROP1_NUM] ={ 0};
static int particleUseProp1Rotate[PARTICLE_USE_PROP1_NUM] ={0};
static CandyParticlePos particleUseProp1Pos[PARTICLE_USE_PROP1_NUM ] ={0};
static CandyParticleMove particleUseProp1Move[PARTICLE_USE_PROP1_NUM] = {0};
static CCParticleSystemQuad* particleUseProp1[PARTICLE_USE_PROP1_NUM] ={0};

static int particleUseProp2Emission[PARTICLE_USE_PROP2_NUM] ={400,50,50,50};
static int particleUseProp2Blend[PARTICLE_USE_PROP2_NUM] ={1,1,1,1};
static int particleUseProp2Time[PARTICLE_USE_PROP2_NUM] ={ 0,0,100,0};
static int particleUseProp2Rotate[PARTICLE_USE_PROP2_NUM] ={0};
static CandyParticlePos particleUseProp2Pos[PARTICLE_USE_PROP2_NUM ] ={0};
static CandyParticleMove particleUseProp2Move[PARTICLE_USE_PROP2_NUM] = {0};
static CCParticleSystemQuad* particleUseProp2[PARTICLE_USE_PROP2_NUM] ={0};

static int particleUseProp3Emission[PARTICLE_USE_PROP3_NUM] ={150,50,30};
static int particleUseProp3Blend[PARTICLE_USE_PROP3_NUM] ={1,1,1};
static int particleUseProp3Time[PARTICLE_USE_PROP3_NUM] ={ 0,0,100};
static int particleUseProp3Rotate[PARTICLE_USE_PROP3_NUM] ={0};
static CandyParticlePos particleUseProp3Pos[PARTICLE_USE_PROP3_NUM ] ={0};
static CandyParticleMove particleUseProp3Move[PARTICLE_USE_PROP3_NUM] = {0};
static CCParticleSystemQuad* particleUseProp3[PARTICLE_USE_PROP3_NUM] ={0};

static int particleUseProp4Emission[PARTICLE_USE_PROP4_NUM] ={10,100,50,150};
static int particleUseProp4Blend[PARTICLE_USE_PROP4_NUM] ={0,1,1,1};
static int particleUseProp4Time[PARTICLE_USE_PROP4_NUM] ={  200,0,100,800};
static int particleUseProp4Rotate[PARTICLE_USE_PROP4_NUM] ={0};
static CandyParticlePos particleUseProp4Pos[PARTICLE_USE_PROP4_NUM ] ={0};
static CandyParticleMove particleUseProp4Move[PARTICLE_USE_PROP4_NUM] = {0};
static CCParticleSystemQuad* particleUseProp4[PARTICLE_USE_PROP4_NUM] ={0};

static int particleUseProp5Emission[PARTICLE_USE_PROP5_NUM] ={10,100,50,150};
static int particleUseProp5Blend[PARTICLE_USE_PROP5_NUM] ={0,1,1,1};
static int particleUseProp5Time[PARTICLE_USE_PROP5_NUM] ={   200,0,100,800};
static int particleUseProp5Rotate[PARTICLE_USE_PROP5_NUM] ={0};
static CandyParticlePos particleUseProp5Pos[PARTICLE_USE_PROP5_NUM ] ={0};
static CandyParticleMove particleUseProp5Move[PARTICLE_USE_PROP5_NUM] = {0};
static CCParticleSystemQuad* particleUseProp5[PARTICLE_USE_PROP5_NUM] ={0};

static int particleUseProp6Emission[PARTICLE_USE_PROP6_NUM] ={30,300};
static int particleUseProp6Blend[PARTICLE_USE_PROP6_NUM] ={1,1};
static int particleUseProp6Time[PARTICLE_USE_PROP6_NUM] ={200,200};
static int particleUseProp6Rotate[PARTICLE_USE_PROP6_NUM] ={0};
static CandyParticlePos particleUseProp6Pos[PARTICLE_USE_PROP6_NUM ] ={0};
static CandyParticleMove particleUseProp6Move[PARTICLE_USE_PROP6_NUM] = {0};
static CCParticleSystemQuad* particleUseProp6[PARTICLE_USE_PROP6_NUM] ={0};

static int particleUseProp7Emission[PARTICLE_USE_PROP7_NUM] ={200,200,200,200};
static int particleUseProp7Blend[PARTICLE_USE_PROP7_NUM] ={1,1,1,1};
static int particleUseProp7Time[PARTICLE_USE_PROP7_NUM] ={0};
static int particleUseProp7Rotate[PARTICLE_USE_PROP7_NUM] ={0};
static CandyParticlePos particleUseProp7Pos[PARTICLE_USE_PROP7_NUM ] ={{0,345},{0,-345},{345,0},{-345,0}};
static CandyParticleMove particleUseProp7Move[PARTICLE_USE_PROP7_NUM] = {0};
static CCParticleSystemQuad* particleUseProp7[PARTICLE_USE_PROP7_NUM] ={0};

static int particlePropButtonEmission[PARTICLE_PROP_BUTTON_NUM] ={85,85};
static int particlePropButtonBlend[PARTICLE_PROP_BUTTON_NUM] ={1,1};
static int particlePropButtonTime[PARTICLE_PROP_BUTTON_NUM] ={ 0,0};
static int particlePropButtonRotate[PARTICLE_PROP_BUTTON_NUM] ={0};
static CandyParticlePos particlePropButtonPos[PARTICLE_PROP_BUTTON_NUM ] ={0};
static CandyParticleMove particlePropButtonMove[PARTICLE_PROP_BUTTON_NUM] = {0};
static CCParticleSystemQuad* particlePropButton[PARTICLE_PROP_BUTTON_NUM] ={0};

static int particleGuideEmission[PARTICLE_GUIDE_FINGER_NUM] ={60,50};
static int particleGuideBlend[PARTICLE_GUIDE_FINGER_NUM] ={1,1};
static int particleGuideTime[PARTICLE_GUIDE_FINGER_NUM] ={0};
static int particleGuideRotate[PARTICLE_GUIDE_FINGER_NUM] ={0};
static CandyParticlePos particleGuidePos[PARTICLE_GUIDE_FINGER_NUM ] ={0};
static CandyParticleMove particleGuideMove[PARTICLE_GUIDE_FINGER_NUM] = {0};
static CCParticleSystemQuad* particleGuide[PARTICLE_GUIDE_FINGER_NUM] ={0};

static int particleResortInEmission[PARTICLE_RESORT_IN_NUM] ={450,450,850,750};
static int particleResortInBlend[PARTICLE_RESORT_IN_NUM] ={1,1,1,1};
static int particleResortInTime[PARTICLE_RESORT_IN_NUM] ={0};
static int particleResortInRotate[PARTICLE_RESORT_IN_NUM] ={0};
static CandyParticlePos particleResortInPos[PARTICLE_RESORT_IN_NUM ] ={0};
static CandyParticleMove particleResortInMove[PARTICLE_RESORT_IN_NUM] = {0};
static CCParticleSystemQuad* particleResortIn[PARTICLE_RESORT_IN_NUM] ={0};

static int particleResortOutEmission[PARTICLE_RESORT_OUT_NUM] ={450,450,850,750};
static int particleResortOutBlend[PARTICLE_RESORT_OUT_NUM] ={1,1,1,1};
static int particleResortOutTime[PARTICLE_RESORT_OUT_NUM] ={0};
static int particleResortOutRotate[PARTICLE_RESORT_OUT_NUM] ={0};
static CandyParticlePos particleResortOutPos[PARTICLE_RESORT_OUT_NUM ] ={0};
static CandyParticleMove particleResortOutMove[PARTICLE_RESORT_OUT_NUM] = {0};
static CCParticleSystemQuad* particleResortOut[PARTICLE_RESORT_OUT_NUM] ={0};

static int particleJarFrontEmission[PARTICLE_JAR_FRONT_NUM] ={15};
static int particleJarFrontBlend[PARTICLE_JAR_FRONT_NUM] ={1};
static int particleJarFrontTime[PARTICLE_JAR_FRONT_NUM] ={0};
static int particleJarFrontRotate[PARTICLE_JAR_FRONT_NUM] ={0};
static CandyParticlePos particleJarFrontPos[PARTICLE_JAR_FRONT_NUM ] ={0};
static CandyParticleMove particleJarFrontMove[PARTICLE_JAR_FRONT_NUM] = {0};
static CCParticleSystemQuad* particleJarFront[PARTICLE_JAR_FRONT_NUM] ={0};

static int particleJarBackEmission[PARTICLE_JAR_BACK_NUM] ={100,30};
static int particleJarBackBlend[PARTICLE_JAR_BACK_NUM] ={1,1};
static int particleJarBackTime[PARTICLE_JAR_BACK_NUM] ={0};
static int particleJarBackRotate[PARTICLE_JAR_BACK_NUM] ={0};
static CandyParticlePos particleJarBackPos[PARTICLE_JAR_BACK_NUM ] ={0};
static CandyParticleMove particleJarBackMove[PARTICLE_JAR_BACK_NUM] = {0};
static CCParticleSystemQuad* particleJarBack[PARTICLE_JAR_BACK_NUM] ={0};

static int particleJarEmission[PARTICLE_JAR_NUM] ={85,85};
static int particleJarBlend[PARTICLE_JAR_NUM] ={1,1};
static int particleJarTime[PARTICLE_JAR_NUM] ={0};
static int particleJarRotate[PARTICLE_JAR_NUM] ={0};
static CandyParticlePos particleJarPos[PARTICLE_JAR_NUM ] ={0};
static CandyParticleMove particleJarMove[PARTICLE_JAR_NUM] = {0};
static CCParticleSystemQuad* particleJar[PARTICLE_JAR_NUM] ={0};

static int particleExplosionEmission[PARTICLE_EXPLOSION_NUM] ={60,100,300};
static int particleExplosionBlend[PARTICLE_EXPLOSION_NUM] ={1,1,1};
static int particleExplosionTime[PARTICLE_EXPLOSION_NUM] ={0};
static int particleExplosionRotate[PARTICLE_EXPLOSION_NUM] ={0};
static CandyParticlePos particleExplosionPos[PARTICLE_EXPLOSION_NUM ] ={0};
static CandyParticleMove particleExplosionMove[PARTICLE_EXPLOSION_NUM] = {0};
static CCParticleSystemQuad* particleExplosion[PARTICLE_EXPLOSION_NUM] ={0};

static int particleCStripleEmission[PARTICLE_CSTRIPLE_NUM] ={80,80};
static int particleCStripleBlend[PARTICLE_CSTRIPLE_NUM] ={1,1};
static int particleCStripleTime[PARTICLE_CSTRIPLE_NUM] ={0};
static int particleCStripleRotate[PARTICLE_CSTRIPLE_NUM] ={0};
static CandyParticlePos particleCStriplePos[PARTICLE_CSTRIPLE_NUM ] ={0};
static CandyParticleMove particleCStripleMove[PARTICLE_CSTRIPLE_NUM] = {0};
static CCParticleSystemQuad* particleCStriple[PARTICLE_CSTRIPLE_NUM] ={0};

static int particleRColorEmission[PARTICLE_RCOLOR_NUM] ={100,100};
static int particleRColorBlend[PARTICLE_RCOLOR_NUM] ={1,1};
static int particleRColorTime[PARTICLE_RCOLOR_NUM] ={0,150};
static int particleRColorRotate[PARTICLE_RCOLOR_NUM] ={0};
static CandyParticlePos particleRColorPos[PARTICLE_RCOLOR_NUM ] ={0};
static CandyParticleMove particleRColorMove[PARTICLE_RCOLOR_NUM] = {0};
static CCParticleSystemQuad* particleRColor[PARTICLE_RCOLOR_NUM] ={0};

static int particleRBombEmission[PARTICLE_RBOMB_NUM] ={150,300,150};
static int particleRBombBlend[PARTICLE_RBOMB_NUM] ={1,1,1};
static int particleRBombTime[PARTICLE_RBOMB_NUM] ={0};
static int particleRBombRotate[PARTICLE_RBOMB_NUM] ={0};
static CandyParticlePos particleRBombPos[PARTICLE_RBOMB_NUM ] ={0};
static CandyParticleMove particleRBombMove[PARTICLE_RBOMB_NUM] = {0};
static CCParticleSystemQuad* particleRBomb[PARTICLE_RBOMB_NUM] ={0};

static int particleRStripEmission[PARTICLE_RSTRIP_NUM] ={150,100};
static int particleRStripBlend[PARTICLE_RSTRIP_NUM] ={1,1};
static int particleRStripTime[PARTICLE_RSTRIP_NUM] ={0};
static int particleRStripRotate[PARTICLE_RSTRIP_NUM] ={0};
static CandyParticlePos particleRStripPos[PARTICLE_RSTRIP_NUM ] ={0};
static CandyParticleMove particleRStripMove[PARTICLE_RSTRIP_NUM] = {0};
static CCParticleSystemQuad* particleRStrip[PARTICLE_RSTRIP_NUM] ={0};

static int particleStarBlinkEmission[PARTICLE_BLINK_PER_NUM] ={30};
static int particleStarBlinkBlend[PARTICLE_BLINK_PER_NUM] ={1};
static int particleStarBlinkTime[PARTICLE_BLINK_PER_NUM] ={0};
static int particleStarBlinkRotate[PARTICLE_BLINK_PER_NUM] ={0};
static CandyParticlePos particleStarBlinkPos[PARTICLE_BLINK_PER_NUM ] ={0};
static CandyParticleMove particleStarBlinkMove[PARTICLE_BLINK_PER_NUM] = {0};
static CCParticleSystemQuad* particleStarBlink[PARTICLE_BLINK_PER_NUM] ={0};

static int particleStarPer1Emission[PARTICLE_STAR_PER1_NUM] ={300,50,500};
static int particleStarPer1Blend[PARTICLE_STAR_PER1_NUM] ={1,1,1};
static int particleStarPer1Time[PARTICLE_STAR_PER1_NUM] ={0,0,600};
static int particleStarPer1Rotate[PARTICLE_STAR_PER1_NUM] ={0};
static CandyParticlePos particleStarPer1Pos[PARTICLE_STAR_PER1_NUM ] ={0};
static CandyParticleMove particleStarPer1Move[PARTICLE_STAR_PER1_NUM] = {0};
static CCParticleSystemQuad* particleStarPer1[PARTICLE_STAR_PER1_NUM] ={0};

static int particleStarPer2Emission[PARTICLE_STAR_PER2_NUM] ={300,20,50,600};
static int particleStarPer2Blend[PARTICLE_STAR_PER2_NUM] ={1,1,1,1};
static int particleStarPer2Time[PARTICLE_STAR_PER2_NUM] ={ 500,0,500,900};
static int particleStarPer2Rotate[PARTICLE_STAR_PER2_NUM] ={0};
static CandyParticlePos particleStarPer2Pos[PARTICLE_STAR_PER2_NUM ] ={0};
static CandyParticleMove particleStarPer2Move[PARTICLE_STAR_PER2_NUM] = {0};
static CCParticleSystemQuad* particleStarPer2[PARTICLE_STAR_PER2_NUM] ={0};

static int particleStarPeringEmission[PARTICLE_STAR_PERING_NUM] ={50};
static int particleStarPeringBlend[PARTICLE_STAR_PERING_NUM] ={1};
static int particleStarPeringTime[PARTICLE_STAR_PERING_NUM] ={0};
static int particleStarPeringRotate[PARTICLE_STAR_PERING_NUM] ={0};
static CandyParticlePos particleStarPeringPos[PARTICLE_STAR_PERING_NUM ] ={0};
static CandyParticleMove particleStarPeringMove[PARTICLE_STAR_PERING_NUM] = {0};
static CCParticleSystemQuad* particleStarPering[PARTICLE_STAR_PERING_NUM] ={0};

static int particleStarPerDoneEmission[PARTICLE_STAR_PERDONE_NUM] ={100};
static int particleStarPerDoneBlend[PARTICLE_STAR_PERDONE_NUM] ={1};
static int particleStarPerDoneTime[PARTICLE_STAR_PERDONE_NUM] ={0};
static int particleStarPerDoneRotate[PARTICLE_STAR_PERDONE_NUM] ={0};
static CandyParticlePos particleStarPerDonePos[PARTICLE_STAR_PERDONE_NUM ] ={0};
static CandyParticleMove particleStarPerDoneMove[PARTICLE_STAR_PERDONE_NUM] = {0};
static CCParticleSystemQuad* particleStarPerDone[PARTICLE_STAR_PERDONE_NUM] ={0};

static int particleStarFireEmission[PARTICLE_STAR_FIRE_NUM] ={500,250,10,10};
static int particleStarFireBlend[PARTICLE_STAR_FIRE_NUM] ={1,1,1,1};
static int particleStarFireTime[PARTICLE_STAR_FIRE_NUM] ={0};
static int particleStarFireRotate[PARTICLE_STAR_FIRE_NUM] ={0};
static CandyParticlePos particleStarFirePos[PARTICLE_STAR_FIRE_NUM ] ={0};
static CandyParticleMove particleStarFireMove[PARTICLE_STAR_FIRE_NUM] = {0};
static CCParticleSystemQuad* particleStarFire[PARTICLE_STAR_FIRE_NUM] ={0};

static int particleExchangeEmission[PARTICLE_EXCHANGE_NUM] ={10000};
static int particleExchangeBlend[PARTICLE_EXCHANGE_NUM] ={0};
static int particleExchangeTime[PARTICLE_EXCHANGE_NUM] ={0};
static int particleExchangeRotate[PARTICLE_EXCHANGE_NUM] ={0};
static CandyParticlePos particleExchangePos[PARTICLE_EXCHANGE_NUM ] ={0};
static CandyParticleMove particleExchangeMove[PARTICLE_EXCHANGE_NUM] = {0};
static CCParticleSystemQuad* particleExchange[PARTICLE_EXCHANGE_NUM] ={0};

static int particleDsipelEmission[PARTICLE_DISPEL_NUM] ={100,700};
static int particleDsipelBlend[PARTICLE_DISPEL_NUM] ={1,1};
static int particleDsipelTime[PARTICLE_DISPEL_NUM] ={0};
static int particleDsipelRotate[PARTICLE_DISPEL_NUM] ={0};
static CandyParticlePos particleDsipelPos[PARTICLE_DISPEL_NUM ] ={0};
static CandyParticleMove particleDsipelMove[PARTICLE_DISPEL_NUM] = {0};
static CCParticleSystemQuad* particleDsipel[PARTICLE_DISPEL_NUM] ={0};

static int particleLicoricesEmission[PARTICLE_LICORICES_NUM] ={100,15,15};
static int particleLicoricesBlend[PARTICLE_LICORICES_NUM] ={1,1,1};
static int particleLicoricesTime[PARTICLE_LICORICES_NUM] ={0};
static int particleLicoricesRotate[PARTICLE_LICORICES_NUM] ={0};
static CandyParticlePos particleLicoricesPos[PARTICLE_LICORICES_NUM ] ={0};
static CandyParticleMove particleLicoricesMove[PARTICLE_LICORICES_NUM] = {0};
static CCParticleSystemQuad* particleLicorices[PARTICLE_LICORICES_NUM] ={0};

static int particleCreamEmission[PARTICLE_CREAM_NUM] ={100,150,20,150};
static int particleCreamBlend[PARTICLE_CREAM_NUM] ={0,0,1,1,};
static int particleCreamTime[PARTICLE_CREAM_NUM] ={0};
static int particleCreamRotate[PARTICLE_CREAM_NUM] ={0};
static CandyParticlePos particleCreamPos[PARTICLE_CREAM_NUM ] ={0};
static CandyParticleMove particleCreamMove[PARTICLE_CREAM_NUM] = {0};
static CCParticleSystemQuad* particleCream[PARTICLE_CREAM_NUM] ={0};

static int particleLockEmission[PARTICLE_LOCK_NUM] ={10,10,10,10,10,10,10};
static int particleLockBlend[PARTICLE_LOCK_NUM] ={0};
static int particleLockTime[PARTICLE_LOCK_NUM] ={0};
static int particleLockRotate[PARTICLE_LOCK_NUM] ={0};
static CandyParticlePos particleLockPos[PARTICLE_LOCK_NUM ] ={0};
static CandyParticleMove particleLockMove[PARTICLE_LOCK_NUM] = {0};
static CCParticleSystemQuad* particleLock[PARTICLE_LOCK_NUM] ={0};

static int particleChocolateEmission[PARTICLE_CHOCOLATE_NUM] ={ 20,90,20,10,};
static int particleChocolateBlend[PARTICLE_CHOCOLATE_NUM] ={0};
static int particleChocolateTime[PARTICLE_CHOCOLATE_NUM] ={0};
static int particleChocolateRotate[PARTICLE_CHOCOLATE_NUM] ={0};
static CandyParticlePos particleChocolatePos[PARTICLE_CHOCOLATE_NUM ] ={{0,0}, {0,0}, {0,0}, {-10,-10}};
static CandyParticleMove particleChocolateMove[PARTICLE_CHOCOLATE_NUM] = {0};
static CCParticleSystemQuad* particleChocolate[PARTICLE_CHOCOLATE_NUM] = {0};

static int particleJellyEmission[PARTICLE_JELLY_NUM] ={ 75,100,80};
static int particleJellyBlend[PARTICLE_JELLY_NUM] ={0,1,1};
static int particleJellyTime[PARTICLE_JELLY_NUM] ={0};
static int particleJellyRotate[PARTICLE_JELLY_NUM] ={0};
static CandyParticlePos particleJellyPos[PARTICLE_JELLY_NUM ] ={0};
static CandyParticleMove particleJellyMove[PARTICLE_JELLY_NUM] = {0};
static CCParticleSystemQuad* particleJelly[PARTICLE_JELLY_NUM] = {0};

static int particleJelly2Emission[PARTICLE_JELLY2_NUM] ={ 80,80};
static int particleJelly2Blend[PARTICLE_JELLY2_NUM] ={1,1};
static int particleJelly2Time[PARTICLE_JELLY2_NUM] ={0};
static int particleJelly2Rotate[PARTICLE_JELLY2_NUM] ={0};
static CandyParticlePos particleJelly2Pos[PARTICLE_JELLY2_NUM ] ={0};
static CandyParticleMove particleJelly2Move[PARTICLE_JELLY2_NUM] = {0};
static CCParticleSystemQuad* particleJelly2[PARTICLE_JELLY2_NUM] = {0};

static int particleBombEmission[PARTICLE_BOMB_NUM] ={15,20,20,170,300};
static int particleBombBlend[PARTICLE_BOMB_NUM] ={1,1,0,0,0};
static int particleBombTime[PARTICLE_BOMB_NUM] ={0,0,0,0,300};
static int particleBombRotate[PARTICLE_BOMB_NUM] ={0};
static CandyParticlePos particleBombPos[PARTICLE_BOMB_NUM ] ={0};
static CandyParticleMove particleBombMove[PARTICLE_BOMB_NUM] = {0};
static CCParticleSystemQuad* particleBomb[PARTICLE_BOMB_NUM] = {0};


static int particleHorizonEmission[PARTICLE_HORIZON_NUM] ={50,100,50,100,50,100,100};
static int particleHorizonBlend[PARTICLE_HORIZON_NUM] ={0,1,0,1,1,1,1};
static int particleHorizonTime[PARTICLE_HORIZON_NUM] ={0};
static int particleHorizonRotate[PARTICLE_HORIZON_NUM] ={0,0,180,0,0};
static CandyParticlePos particleHorizonPos[PARTICLE_HORIZON_NUM ] ={{-30,0},{0,0},{30,0}};
static CandyParticleMove particleHorizonMove[PARTICLE_HORIZON_NUM] = {{0},{1600,1500,0},{0},{1600,-1500,0},{0},{1600,2000,0},{1600,-2000,0}};
static CCParticleSystemQuad* particleHorizon[PARTICLE_HORIZON_NUM] = {0};

static int particleVerticalEmission[PARTICLE_VERTICAL_NUM] ={50,100,50,100,50,100,100};
static int particleVerticalBlend[PARTICLE_VERTICAL_NUM] ={0,1,0,1,1,1,1};
static int particleVerticalTime[PARTICLE_VERTICAL_NUM] ={0};
static int particleVerticalRotate[PARTICLE_VERTICAL_NUM] ={90,0,270,0};
static CandyParticlePos particleVerticalPos[PARTICLE_VERTICAL_NUM ] ={{0,30},{0,0},{0,-30}};
static CandyParticleMove particleVerticalMove[PARTICLE_VERTICAL_NUM] = {{0},{1600,0,1500},{0},{1600,0,-1500},{0},{1600,0,2000},{1600,0,-2000}};
static CCParticleSystemQuad* particleVertical[PARTICLE_VERTICAL_NUM] = {0};

static int particleCEmitEmission[PARTICLE_CEMIT_NUM] ={20,20,20,10,20,20,170,10,10,100};
static int particleCEmitBlend[PARTICLE_CEMIT_NUM] ={1,1,1,1,1,1,1,1,0,1};
static int particleCEmitTime[PARTICLE_CEMIT_NUM] ={50,10,10,500,500,500,500,600,0,450};
static int particleCEmitRotate[PARTICLE_CEMIT_NUM] ={0};
static CandyParticlePos particleCEmitPos[PARTICLE_CEMIT_NUM ] ={0};
static CandyParticleMove particleCEmitMove[PARTICLE_CEMIT_NUM] = {0};
static CCParticleSystemQuad* particleCEmit[PARTICLE_CEMIT_NUM] = {0};

static int particleCFireEmission[PARTICLE_CFIRE_NUM] ={200,250,100};
static int particleCFireBlend[PARTICLE_CFIRE_NUM] ={1,1,1};
static int particleCFireTime[PARTICLE_CFIRE_NUM] ={0};
static int particleCFireRotate[PARTICLE_CFIRE_NUM] ={0};
static CandyParticlePos particleCFirePos[PARTICLE_CFIRE_NUM ] ={0};
static CandyParticleMove particleCFireMove[PARTICLE_CFIRE_NUM] = {0};
static CCParticleSystemQuad* particleCFire[PARTICLE_CFIRE_NUM] = {0};

static int particleCTargetEmission[PARTICLE_CTARGET_NUM] ={20,15,20,20,170};
static int particleCTargetBlend[PARTICLE_CTARGET_NUM] ={1,1,1,1,1};
static int particleCTargetTime[PARTICLE_CTARGET_NUM] ={0,0,0,0,0};
static int particleCTargetRotate[PARTICLE_CTARGET_NUM] ={0};
static CandyParticlePos particleCTargetPos[PARTICLE_CTARGET_NUM ] ={0};
static CandyParticleMove particleCTargetMove[PARTICLE_CTARGET_NUM] = {0};
static CCParticleSystemQuad* particleCTarget[PARTICLE_CTARGET_NUM] = {0};

static int particleComBBEmission[PARTICLE_COMBB_NUM] ={ 85,  30, 7, 20, 1000,500};
static int particleComBBBlend[PARTICLE_COMBB_NUM] ={1,1,1,1,0,1};
static int particleComBBTime[PARTICLE_COMBB_NUM] ={ 0,0,250,350,400,0};
static int particleComBBRotate[PARTICLE_COMBB_NUM] ={0};
static CandyParticlePos particleComBBPos[PARTICLE_COMBB_NUM] ={0};
static CandyParticleMove particleComBBMove[PARTICLE_COMBB_NUM] = {0};
static CCParticleSystemQuad* particleComBB[PARTICLE_COMBB_NUM] = {0};

static int particleComBSEmission[PARTICLE_COMBS_NUM] ={555,35,100,15,25,25,25,25,120,220,220,220,220};
static int particleComBSBlend[PARTICLE_COMBS_NUM] ={1,1,1,1,0,0,0,0,1,1,1,1,1};
static int particleComBSTime[PARTICLE_COMBS_NUM] ={  0,950,950,100,950,950,950,950,950,950,950,950,950};
static int particleComBSRotate[PARTICLE_COMBS_NUM] ={0,0,0,0,0,90,180,270,0,0,0,0,0};
static CandyParticlePos particleComBSPos[PARTICLE_COMBS_NUM] ={0};
static CandyParticleMove particleComBSMove[PARTICLE_COMBS_NUM] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{1400,1000,0},{1400,0,1000},
{1400,-1000,0},{1400,0,-1000}	};
static CCParticleSystemQuad* particleComBS[PARTICLE_COMBS_NUM] = {0};

static int particleComSSEmission[PARTICLE_COMSS_NUM] ={50,100,20,200,50,50,50,100,100,100,50,50,50,50};
static int particleComSSBlend[PARTICLE_COMSS_NUM] ={0,1,1,1,0,0,0,1,1,1,1,1,1,1};
static int particleComSSTime[PARTICLE_COMSS_NUM] ={0};
static int particleComSSRotate[PARTICLE_COMSS_NUM] ={0,0,0,0,90,180,-90,0,0,0};
static CandyParticlePos particleComSSPos[PARTICLE_COMSS_NUM] ={{-30,0},{0,0},{0,0},{0,0},{0,30},{30,0},{0,-30},{0,0},{0,0},{0,0}};
static CandyParticleMove particleComSSMove[PARTICLE_COMSS_NUM] = {{0},{2000,1500,0},{0},{0},{0},{0},{0},{2000,0,-1500},{2000,-1500,0},
{2000,0,1500},{2000,2000,0},{2000,-2000,0},{2000,0,2000},{2000,0,-2000}};
static CCParticleSystemQuad* particleComSS[PARTICLE_COMSS_NUM] = {0};

static int particleComCCEmission[PARTICLE_COMCC_NUM] ={20,10,10,20,70};
static int particleComCCBlend[PARTICLE_COMCC_NUM] ={1,0,1,1,1};
static int particleComCCTime[PARTICLE_COMCC_NUM] ={0,0,600,650,300};
static int particleComCCRotate[PARTICLE_COMCC_NUM] ={0};
static CandyParticlePos particleComCCPos[PARTICLE_COMCC_NUM] ={0};
static CandyParticleMove particleComCCMove[PARTICLE_COMCC_NUM] = {0};
static CCParticleSystemQuad* particleComCC[PARTICLE_COMCC_NUM] = {0};

static int mapActiveNewEmission[MAP_ACTIVE_NEW_NUM] ={300};
static int mapActiveNewBlend[MAP_ACTIVE_NEW_NUM] ={0};
static int mapActiveNewTime[MAP_ACTIVE_NEW_NUM] ={0};
static int mapActiveNewRotate[MAP_ACTIVE_NEW_NUM] ={1};
static CandyParticlePos mapActiveNewPos[MAP_ACTIVE_NEW_NUM ] ={0};
static CandyParticleMove mapActiveNewMove[MAP_ACTIVE_NEW_NUM] = {0};
static CCParticleSystemQuad* mapActiveNew[MAP_ACTIVE_NEW_NUM] ={0};

static int mapActiveNew2Emission[MAP_ACTIVE_NEW2_NUM] ={30};
static int mapActiveNew2Blend[MAP_ACTIVE_NEW2_NUM] ={1};
static int mapActiveNew2Time[MAP_ACTIVE_NEW2_NUM] ={0};
static int mapActiveNew2Rotate[MAP_ACTIVE_NEW2_NUM] ={0};
static CandyParticlePos mapActiveNew2Pos[MAP_ACTIVE_NEW2_NUM ] ={0};
static CandyParticleMove mapActiveNew2Move[MAP_ACTIVE_NEW2_NUM] = {0};
static CCParticleSystemQuad* mapActiveNew2[MAP_ACTIVE_NEW2_NUM] ={0};

static int mapActiveloveEmission[MAP_ACTIVE_LOVEIIFE_NUM] ={3};
static int mapActiveloveBlend[MAP_ACTIVE_LOVEIIFE_NUM] ={1};
static int mapActiveloveTime[MAP_ACTIVE_LOVEIIFE_NUM] ={0};
static int mapActiveloveRotate[MAP_ACTIVE_LOVEIIFE_NUM] ={0};
static CandyParticlePos mapActivelovePos[MAP_ACTIVE_LOVEIIFE_NUM ] ={0};
static CandyParticleMove mapActiveloveMove[MAP_ACTIVE_LOVEIIFE_NUM] = {0};
static CCParticleSystemQuad* mapActivelove[MAP_ACTIVE_LOVEIIFE_NUM] ={0};

static int LoginEffectEmission[LOGIN_ACTIVE_BOOMFLY] ={500};
static int LoginEffectBlend[LOGIN_ACTIVE_BOOMFLY] ={0};
static int LoginEffectTime[LOGIN_ACTIVE_BOOMFLY] ={0};
static int LoginEffectRotate[LOGIN_ACTIVE_BOOMFLY] ={1};
static CandyParticlePos LoginEffectPos[LOGIN_ACTIVE_BOOMFLY ] ={0};
static CandyParticleMove LoginEffectMove[LOGIN_ACTIVE_BOOMFLY] = {0};
static CCParticleSystemQuad* LoginEffect[LOGIN_ACTIVE_BOOMFLY] ={0};

static int particleAddlifeMessageEffectEmission[MAP_ACTIVE_ADDLIFEMESSAGE] ={10,100};
static int particleAddlifeMessageEffectBlend[MAP_ACTIVE_ADDLIFEMESSAGE] ={1,1};
static int particleAddlifeMessageEffectTime[MAP_ACTIVE_ADDLIFEMESSAGE] ={0,0};
static int particleAddlifeMessageEffectRotate[MAP_ACTIVE_ADDLIFEMESSAGE] ={0};
static CandyParticlePos particleAddlifeMessageEffectPos[MAP_ACTIVE_ADDLIFEMESSAGE] ={{0}};
static CandyParticleMove particleAddlifeMessageEffectMove[MAP_ACTIVE_ADDLIFEMESSAGE] = {{0,0,0},{700,0,80}};
static CCParticleSystemQuad* particleAddlifeMessageEffect[MAP_ACTIVE_ADDLIFEMESSAGE] ={0};

static int LoginFlashEffectEmission[LOGIN_FLASH_EFF_NUM] ={500};
static int LoginFlashEffectBlend[LOGIN_FLASH_EFF_NUM] ={1};
static int LoginFlashEffectTime[LOGIN_FLASH_EFF_NUM] ={0};
static int LoginFlashEffectRotate[LOGIN_FLASH_EFF_NUM] ={1};
static CandyParticlePos LoginFlashEffectPos[LOGIN_FLASH_EFF_NUM ] ={0};
static CandyParticleMove LoginFlashEffectMove[LOGIN_FLASH_EFF_NUM] = {0};
static CCParticleSystemQuad* LoginFlashEffect[LOGIN_FLASH_EFF_NUM] ={0};

static int GiftFrontEffectBlend[MAP_GIFT_EFFECT_FRONT_NUM] ={1,1,1};
static int GiftBackEffectBlend[MAP_GIFT_EFFECT_BACK_NUM] ={1,1};
static int GiftFrontEffectEmission[MAP_GIFT_EFFECT_FRONT_NUM] ={5,10,25};
static int GiftBackEffectEmission[MAP_GIFT_EFFECT_BACK_NUM] ={15,30};
static CandyParticlePos GiftFrontEffectPos[MAP_GIFT_EFFECT_FRONT_NUM ] ={0};
static CandyParticlePos GiftBackEffectPos[MAP_GIFT_EFFECT_BACK_NUM ] ={0};
static int GiftFrontEffectRotate[MAP_GIFT_EFFECT_FRONT_NUM] ={0};
static int GiftBackEffectRotate[MAP_GIFT_EFFECT_BACK_NUM] ={0};
static int GiftFrontEffectTime[MAP_GIFT_EFFECT_FRONT_NUM] ={0};
static int GiftBackEffectTime[MAP_GIFT_EFFECT_BACK_NUM] ={0};
static CandyParticleMove GiftFrontEffectMove[MAP_GIFT_EFFECT_FRONT_NUM] = {0};
static CandyParticleMove GiftBackEffectMove[MAP_GIFT_EFFECT_BACK_NUM] = {0};



static int particleFileNum[CANDY_PARTICLE_NUM] =
{	
	CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM,
	CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM,
	CANDY_PARTICLE_CHUNZI_EFFECT_NUM,
	CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM,
	CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM,
	CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM,
	CANDY_PARTICLE_YINTAO_EFFECT_NUM,
	CANDY_PARTICLE_WUYUN_EFFECT_NUM,
	CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM,
	CANDY_PARTICLE_WIN_EFFECT_NUM,
	CANDY_PARTICLE_PRESS_PROP_NUM,
	PARTICLE_REWARD_LIGHT_NUM,
	PARTICLE_WIN_LIGHT_NUM,
	PARTICLE_TARGET_ICON_NUM,
	PARTICLE_CANDY_APPEAR_NUM,
	PARTICLE_STAGE_CLEAR_NUM,
	PARTICLE_STAGE_FAILED1_NUM,
	PARTICLE_STAGE_FAILED2_NUM,
	PARTICLE_ROULETEE_EDGE_NUM,
	PARTICLE_ROULETEE_END_NUM,
	PARTICLE_LIGHT_NUM,
	PARTICLE_USE_PROP1_NUM,
	PARTICLE_USE_PROP2_NUM,
	PARTICLE_USE_PROP3_NUM,
	PARTICLE_USE_PROP4_NUM,
	PARTICLE_USE_PROP5_NUM,
	PARTICLE_USE_PROP6_NUM,
	PARTICLE_USE_PROP7_NUM,
	PARTICLE_PROP_BUTTON_NUM,
	PARTICLE_GUIDE_FINGER_NUM,
	PARTICLE_RESORT_IN_NUM,
	PARTICLE_RESORT_OUT_NUM,
	PARTICLE_JAR_FRONT_NUM,
	PARTICLE_JAR_BACK_NUM,
	PARTICLE_JAR_NUM,
	PARTICLE_EXPLOSION_NUM,
	PARTICLE_CSTRIPLE_NUM,
	PARTICLE_RCOLOR_NUM,
	PARTICLE_RBOMB_NUM,
	PARTICLE_RSTRIP_NUM,
	PARTICLE_BLINK_PER_NUM,
	PARTICLE_STAR_PER1_NUM,
	PARTICLE_STAR_PER2_NUM,
	PARTICLE_STAR_PERING_NUM,
	PARTICLE_STAR_PERDONE_NUM,
	PARTICLE_STAR_FIRE_NUM,
	PARTICLE_EXCHANGE_NUM,
	PARTICLE_DISPEL_NUM,
	PARTICLE_LICORICES_NUM,
	PARTICLE_CREAM_NUM,
	PARTICLE_LOCK_NUM,
	PARTICLE_CHOCOLATE_NUM,
	PARTICLE_JELLY_NUM,
	PARTICLE_JELLY2_NUM,
	PARTICLE_BOMB_NUM,
	PARTICLE_HORIZON_NUM,
	PARTICLE_VERTICAL_NUM,
	PARTICLE_CEMIT_NUM,
	PARTICLE_CFIRE_NUM,
	PARTICLE_CTARGET_NUM,
	PARTICLE_COMBB_NUM,
	PARTICLE_COMBS_NUM,
	PARTICLE_COMSS_NUM,
	PARTICLE_COMCC_NUM,
	LOGIN_ACTIVE_BOOMFLY,
	MAP_ACTIVE_NEW_NUM,
	MAP_ACTIVE_NEW2_NUM,
	MAP_ACTIVE_LOVEIIFE_NUM,
	CANDY_PARTICLE_SONGXIN_EFFECT_NUM,
	CANDY_PARTICLE_XINFENG_EFFECT_NUM,
	MAP_ACTIVE_ADDLIFEMESSAGE,
	CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM,
	LOGIN_FLASH_EFF_NUM,
	CANDY_PARTICLE_UNLOCKLEVEL_EFFECT_NUM,
	MAP_GIFT_EFFECT_FRONT_NUM,
	MAP_GIFT_EFFECT_BACK_NUM,
};

static int* particleEmission[CANDY_PARTICLE_NUM]=
{
	(int *)particleDoubleScoreFireEffectEmission,
	(int *)particleDoubleScoreEffectEmission,
	(int *)particleChuiZiEffectEmission,
	(int *)particleShenDengOpenEffectEmission,
	(int *)particleShenDengYaoDongEffectEmission,
	(int *)particleShenDengZhaKaiEffectEmission,
	(int *)particleYinTaoEffectEmission,
	(int *)particleWuYunEffectEmission,
	(int *)particleCandyCrushEffectEmission,
	(int *)particleWinEffectEmission,
	(int *)particlePressPropEmission,
	(int *)particleRewardLightEmission,
	(int *)particleWinLightEmission,
	(int *)particleTargetIconEmission,
	(int *)particleCandyAppearEmission,
	(int *)particleStageClearEmission,
	(int *)particleStageFailed1Emission,
	(int *)particleStageFailed2Emission,
	(int *)particleRouleteeEdgeEmission,
	(int *)particleRouleteeEndEmission,
	(int *)particleLightEmission,
	(int *)particleUseProp1Emission,
	(int *)particleUseProp2Emission,
	(int *)particleUseProp3Emission,
	(int *)particleUseProp4Emission,
	(int *)particleUseProp5Emission,
	(int *)particleUseProp6Emission,
	(int *)particleUseProp7Emission,
	(int *)particlePropButtonEmission,
	(int *)particleGuideEmission,
	(int *)particleResortInEmission,
	(int *)particleResortOutEmission,
	(int *)particleJarFrontEmission,
	(int *)particleJarBackEmission,
	(int *)particleJarEmission,
	(int *)particleExplosionEmission,
	(int *)particleCStripleEmission,
	(int *)particleRColorEmission,
	(int *)particleRBombEmission,
	(int *)particleRStripEmission,
	(int *)particleStarBlinkEmission,
	(int *)particleStarPer1Emission,
	(int *)particleStarPer2Emission,
	(int *)particleStarPeringEmission,
	(int *)particleStarPerDoneEmission,
	(int *)particleStarFireEmission,
	(int *)particleExchangeEmission,
	(int *)particleDsipelEmission,
	(int *)particleLicoricesEmission,
	(int *)particleCreamEmission,
	(int *)particleLockEmission,
	(int *)particleChocolateEmission,
	(int *)particleJellyEmission,
	(int *)particleJelly2Emission,
	(int *)particleBombEmission,
	(int *)particleHorizonEmission,
	(int *)particleVerticalEmission,
	(int *)particleCEmitEmission,
	(int *)particleCFireEmission,
	(int *)particleCTargetEmission,
	(int *)particleComBBEmission,
	(int *)particleComBSEmission,
	(int *)particleComSSEmission,
	(int *)particleComCCEmission,
	(int *)LoginEffectEmission,
	(int *)mapActiveNewEmission,
	(int *)mapActiveNew2Emission,
	(int *)mapActiveloveEmission,
	(int *)particleSongXinEffectEmission,
	(int *)particleXinFengEffectEmission,
	(int *)particleAddlifeMessageEffectEmission,
	(int *)particleSongDaojuEffectEmission,
	(int *)LoginFlashEffectEmission,
	(int *)particleUnlockLevelEffectEmission,
	(int *)GiftFrontEffectEmission,
	(int *)GiftBackEffectEmission,
};

static int* particleBlend[CANDY_PARTICLE_NUM] =
{		
	(int *)particleDoubleScoreFireEffectBlend,
	(int *)particleDoubleScoreEffectBlend,
	(int *)particleChuiZiEffectBlend,
	(int *)particleShenDengOpenEffectBlend,
	(int *)particleShenDengYaoDongEffectBlend,
	(int *)particleShenDengZhaKaiEffectBlend,
	(int *)particleYinTaoEffectBlend,
	(int *)particleWuYunEffectBlend,
	(int *)particleCandyCrushEffectBlend,
	(int *)particleWinEffectBlend,
	(int *)particlePressPropBlend,
	(int *)particleRewardLightBlend,
	(int *)particleWinLightBlend,
	(int *)particleTargetIconBlend,
	(int *)particleCandyAppearBlend,
	(int *)particleStageClearBlend,
	(int *)particleStageFailed1Blend,
	(int *)particleStageFailed2Blend,	
	(int *)particleRouleteeEdgeBlend,
	(int *)particleRouleteeEndBlend,
	(int *)particleLightInBlend,
	(int *)particleUseProp1Blend,
	(int *)particleUseProp2Blend,
	(int *)particleUseProp3Blend,
	(int *)particleUseProp4Blend,
	(int *)particleUseProp5Blend,
	(int *)particleUseProp6Blend,
	(int *)particleUseProp7Blend,
	(int *)particlePropButtonBlend,
	(int *)particleGuideBlend,
	(int *)particleResortInBlend,
	(int *)particleResortOutBlend,
	(int *)particleJarFrontBlend,
	(int *)particleJarBackBlend,
	(int *)particleJarBlend,
	(int *)particleExplosionBlend,
	(int *)particleCStripleBlend,
	(int *)particleRColorBlend,
	(int *)particleRBombBlend,
	(int *)particleRStripBlend,
	(int *)particleStarBlinkBlend,
	(int *)particleStarPer1Blend,
	(int *)particleStarPer2Blend,
	(int *)particleStarPeringBlend,
	(int *)particleStarPerDoneBlend,
	(int *)particleStarFireBlend,
	(int *)particleExchangeBlend,
	(int *)particleDsipelBlend,
	(int *)particleLicoricesBlend,
	(int *)particleCreamBlend,
	(int *)particleLockBlend,
	(int *)particleChocolateBlend,
	(int *)particleJellyBlend,
	(int *)particleJelly2Blend,
	(int *)particleBombBlend,
	(int *)particleHorizonBlend,
	(int *)particleVerticalBlend,
	(int *)particleCEmitBlend,
	(int *)particleCFireBlend,
	(int *)particleCTargetBlend,
	(int *)particleComBBBlend,
	(int *)particleComBSBlend,
	(int *)particleComSSBlend,
	(int *)particleComCCBlend,
	(int *)LoginEffectBlend,
	(int *)mapActiveNewBlend,
	(int *)mapActiveNew2Blend,
	(int *)mapActiveloveBlend,
	(int *)particleSongXinEffectBlend,
	(int *)particleXinFengEffectBlend,
	(int *)particleAddlifeMessageEffectBlend,
	(int *)particleSongDaojuEffectBlend,
	(int *)LoginFlashEffectBlend,
	(int *)particleUnlockLevelEffectBlend,
	(int *)GiftFrontEffectBlend,
	(int *)GiftBackEffectBlend,
};

static int* particleTime[CANDY_PARTICLE_NUM] =
{	
	(int *)particleDoubleScoreFireEffectTime,
	(int *)particleDoubleScoreEffectTime,
	(int *)particleChuiZiEffectTime,
	(int *)particleShenDengOpenEffectTime,
	(int *)particleShenDengYaoDongEffectTime,
	(int *)particleShenDengZhaKaiEffectTime,
	(int *)particleYinTaoEffectTime,
	(int *)particleWuYunEffectTime,
	(int *)particleCandyCrushEffectTime,
	(int *)particleWinEffectTime,
	(int *)particlePressPropTime,
	(int *)particleRewardLightTime,
	(int *)particleWinLightTime,
	(int *)particleTargetIconTime,
	(int *)particleCandyAppearTime,
	(int *)particleStageClearTime,
	(int *)particleStageFailed1Time,
	(int *)particleStageFailed2Time,
	(int *)particleRouleteeEdgeTime,
	(int *)particleRouleteeEndTime,
	(int *)particleLightInTime,
	(int *)particleUseProp1Time,
	(int *)particleUseProp2Time,
	(int *)particleUseProp3Time,
	(int *)particleUseProp4Time,
	(int *)particleUseProp5Time,
	(int *)particleUseProp6Time,
	(int *)particleUseProp7Time,
	(int *)particlePropButtonTime,
	(int *)particleGuideTime,
	(int *)particleResortInTime,
	(int *)particleResortOutTime,
	(int *)particleJarFrontTime,
	(int *)particleJarBackTime,
	(int *)particleJarTime,
	(int *)particleExplosionTime,
	(int *)particleCStripleTime,
	(int *)particleRColorTime,
	(int *)particleRBombTime,
	(int *)particleRStripTime,
	(int *)particleStarBlinkTime,
	(int *)particleStarPer1Time,
	(int *)particleStarPer2Time,
	(int *)particleStarPeringTime,
	(int *)particleStarPerDoneTime,
	(int *)particleStarFireTime,
	(int *)particleExchangeTime,
	(int *)particleDsipelTime,
	(int *)particleLicoricesTime,
	(int *)particleCreamTime,
	(int *)particleLockTime,
	(int *)particleChocolateTime,
	(int *)particleJellyTime,
	(int *)particleJelly2Time,
	(int *)particleBombTime,
	(int *)particleHorizonTime,
	(int *)particleVerticalTime,
	(int *)particleCEmitTime,
	(int *)particleCFireTime,
	(int *)particleCTargetTime,
	(int *)particleComBBTime,
	(int *)particleComBSTime,
	(int *)particleComSSTime,
	(int *)particleComCCTime,
	(int *)LoginEffectTime,
	(int *)mapActiveNewTime,
	(int *)mapActiveNew2Time,
	(int *)mapActiveloveTime,
	(int *)particleSongXinEffectTime,
	(int *)particleXinFengEffectTime,
	(int *)particleAddlifeMessageEffectTime,
	(int *)particleSongDaojuEffectTime,
	(int *)LoginFlashEffectTime,
	(int *)particleUnlockLevelEffectTime,
	(int *)GiftFrontEffectTime,
	(int *)GiftBackEffectTime,
};

static int* particleRotate[CANDY_PARTICLE_NUM] =
{
	(int *)particleDoubleScoreFireEffectRotate,
	(int *)particleDoubleScoreEffectRotate,
	(int *)particleChuiZiEffectRotate,
	(int *)particleShenDengOpenEffectRotate,
	(int *)particleShenDengYaoDongEffectRotate,
	(int *)particleShenDengZhaKaiEffectRotate,
	(int *)particleYinTaoEffectRotate,
	(int *)particleWuYunEffectRotate,
	(int *)particleCandyCrushEffectRotate,
	(int *)particleWinEffectRotate,
	(int *)particlePressPropRotate,
	(int *)particleRewardLightRotate,
	(int *)particleWinLightRotate,
	(int *)particleTargetIconRotate,
	(int *)particleCandyAppearRotate,
	(int *)particleStageClearRotate,
	(int *)particleStageFailed1Rotate,
	(int *)particleStageFailed2Rotate,
	(int *)particleRouleteeEdgeRotate,
	(int *)particleRouleteeEndRotate,
	(int *)particleLightInRotate,
	(int *)particleUseProp1Rotate,
	(int *)particleUseProp2Rotate,
	(int *)particleUseProp3Rotate,
	(int *)particleUseProp4Rotate,
	(int *)particleUseProp5Rotate,
	(int *)particleUseProp6Rotate,
	(int *)particleUseProp7Rotate,
	(int *)particlePropButtonRotate,
	(int *)particleGuideRotate,
	(int *)particleResortInRotate,
	(int *)particleResortOutRotate,
	(int *)particleJarFrontRotate,
	(int *)particleJarBackRotate,
	(int *)particleJarRotate,
	(int *)particleExplosionRotate,
	(int *)particleCStripleRotate,
	(int *)particleRColorRotate,
	(int *)particleRBombRotate,
	(int *)particleRStripRotate,
	(int *)particleStarBlinkRotate,
	(int *)particleStarPer1Rotate,
	(int *)particleStarPer2Rotate,
	(int *)particleStarPeringRotate,
	(int *)particleStarPerDoneRotate,
	(int *)particleStarFireRotate,
	(int *)particleExchangeRotate,
	(int *)particleDsipelRotate,
	(int *)particleLicoricesRotate,
	(int *)particleCreamRotate,
	(int *)particleLockRotate,
	(int *)particleChocolateRotate,
	(int *)particleJellyRotate,
	(int *)particleJelly2Rotate,
	(int *)particleBombRotate,
	(int *)particleHorizonRotate,
	(int *)particleVerticalRotate,
	(int *)particleCEmitRotate,
	(int *)particleCFireRotate,
	(int *)particleCTargetRotate,
	(int *)particleComBBRotate,
	(int *)particleComBSRotate,
	(int *)particleComSSRotate,
	(int *)particleComCCRotate,
	(int *)LoginEffectRotate,
	(int *)mapActiveNewRotate,
	(int *)mapActiveNew2Rotate,
	(int *)mapActiveloveRotate,
	(int *)particleSongXinEffectRotate,
	(int *)particleXinFengEffectRotate,
	(int *)particleAddlifeMessageEffectRotate,
	(int *)particleSongDaojuEffectRotate,
	(int *)LoginFlashEffectRotate,
	(int *)particleUnlockLevelEffectRotate,
	(int *)GiftFrontEffectRotate,
	(int *)GiftBackEffectRotate,
};

static CandyParticlePos* particlePos[CANDY_PARTICLE_NUM] =
{
	(CandyParticlePos *)particleDoubleScoreFireEffecEffectPos,
	(CandyParticlePos *)particleDoubleScoreEffecEffectPos,
	(CandyParticlePos *)particleChuiZiEffecEffectPos,
	(CandyParticlePos *)particleShenDengOpenEffectPos,
	(CandyParticlePos *)particleShenDengYaoDongEffectPos,
	(CandyParticlePos *)particleShenDengZhaKaiEffectPos,
	(CandyParticlePos *)particleYinTaoEffectPos,
	(CandyParticlePos *)particleWuYunEffectPos,
	(CandyParticlePos *)particleCandyCrushEffectPos,
	(CandyParticlePos *)particleWinEffectPos,
	(CandyParticlePos *)particlePressPropPos,
	(CandyParticlePos *)particleRewardLightPos,
	(CandyParticlePos *)particleWinLightPos,
	(CandyParticlePos *)particleTargetIconPos,
	(CandyParticlePos *)particleCandyAppearPos,
	(CandyParticlePos *)particleStageClearPos,
	(CandyParticlePos *)particleStageFailed1Pos,
	(CandyParticlePos *)particleStageFailed2Pos,
	(CandyParticlePos *)particleRouleteeEdgePos,
	(CandyParticlePos *)particleRouleteeEndPos,
	(CandyParticlePos *)particleLightPos,
	(CandyParticlePos *)particleUseProp1Pos,
	(CandyParticlePos *)particleUseProp2Pos,
	(CandyParticlePos *)particleUseProp3Pos,
	(CandyParticlePos *)particleUseProp4Pos,
	(CandyParticlePos *)particleUseProp5Pos,
	(CandyParticlePos *)particleUseProp6Pos,
	(CandyParticlePos *)particleUseProp7Pos,
	(CandyParticlePos *)particlePropButtonPos,
	(CandyParticlePos *)particleGuidePos,
	(CandyParticlePos *)particleResortInPos,
	(CandyParticlePos *)particleResortOutPos,
	(CandyParticlePos *)particleJarFrontPos,
	(CandyParticlePos *)particleJarBackPos,
	(CandyParticlePos *)particleJarPos,
	(CandyParticlePos *)particleExplosionPos,
	(CandyParticlePos *)particleCStriplePos,
	(CandyParticlePos *)particleRColorPos,
	(CandyParticlePos *)particleRBombPos,
	(CandyParticlePos *)particleRStripPos,
	(CandyParticlePos *)particleStarBlinkPos,
	(CandyParticlePos *)particleStarPer1Pos,
	(CandyParticlePos *)particleStarPer2Pos,
	(CandyParticlePos *)particleStarPeringPos,
	(CandyParticlePos *)particleStarPerDonePos,
	(CandyParticlePos *)particleStarFirePos,
	(CandyParticlePos *)particleExchangePos,
	(CandyParticlePos *)particleDsipelPos,
	(CandyParticlePos *)particleLicoricesPos,
	(CandyParticlePos *)particleCreamPos,
	(CandyParticlePos *)particleLockPos,
	(CandyParticlePos *)particleChocolatePos,
	(CandyParticlePos *)particleJellyPos,
	(CandyParticlePos *)particleJelly2Pos,
	(CandyParticlePos *)particleBombPos,
	(CandyParticlePos *)particleHorizonPos,
	(CandyParticlePos *)particleVerticalPos,
	(CandyParticlePos *)particleCEmitPos,
	(CandyParticlePos *)particleCFirePos,
	(CandyParticlePos *)particleCTargetPos,
	(CandyParticlePos *)particleComBBPos,
	(CandyParticlePos *)particleComBSPos,
	(CandyParticlePos *)particleComSSPos,
	(CandyParticlePos *)particleComCCPos,
	(CandyParticlePos *)LoginEffectPos,
	(CandyParticlePos *)mapActiveNewPos,
	(CandyParticlePos *)mapActiveNew2Pos,
	(CandyParticlePos *)mapActivelovePos,
	(CandyParticlePos *)particleSongXinEffectPos,
	(CandyParticlePos *)particleXinFengEffectPos,
	(CandyParticlePos *)particleAddlifeMessageEffectPos,
	(CandyParticlePos *)particleSongDaojuEffectPos,
	(CandyParticlePos *)LoginFlashEffectPos,
	(CandyParticlePos *)particleUnlockLevelEffecEffectPos,
	(CandyParticlePos *)GiftFrontEffectPos,
	(CandyParticlePos *)GiftBackEffectPos,
};


static CandyParticleMove* particleMove[CANDY_PARTICLE_NUM] =
{	
	(CandyParticleMove *)particleDoubleScoreFireEffecEffectMove,
	(CandyParticleMove *)particleDoubleScoreEffecEffectMove,
	(CandyParticleMove *)particleChuiZiEffecEffectMove,
	(CandyParticleMove *)particleShenDengOpenEffectMove,
	(CandyParticleMove *)particleShenDengYaoDongEffectMove,
	(CandyParticleMove *)particleShenDengZhaKaiEffectMove,
	(CandyParticleMove *)particleYinTaoEffectMove,
	(CandyParticleMove *)particleWuYunEffectMove,
	(CandyParticleMove *)particleCandyCrushEffectMove,
	(CandyParticleMove *)particleWinEffectMove,
	(CandyParticleMove *)particlePressPropMove,
	(CandyParticleMove *)particleRewardLightMove,
	(CandyParticleMove *)particleWinLightMove,
	(CandyParticleMove *)particleTargetIconMove,
	(CandyParticleMove *)particleCandyAppearMove,
	(CandyParticleMove *)particleStageClearMove,
	(CandyParticleMove *)particleStageFailed1Move,
	(CandyParticleMove *)particleStageFailed2Move,
	(CandyParticleMove *)particleRouleteeEdgeMove,
	(CandyParticleMove *)particleRouleteeEndMove,
	(CandyParticleMove *)particleLightMove,
	(CandyParticleMove *)particleUseProp1Move,
	(CandyParticleMove *)particleUseProp2Move,
	(CandyParticleMove *)particleUseProp3Move,
	(CandyParticleMove *)particleUseProp4Move,
	(CandyParticleMove *)particleUseProp5Move,
	(CandyParticleMove *)particleUseProp6Move,
	(CandyParticleMove *)particleUseProp7Move,
	(CandyParticleMove *)particlePropButtonMove,
	(CandyParticleMove *)particleGuideMove,
	(CandyParticleMove *)particleResortInMove,
	(CandyParticleMove *)particleResortOutMove,
	(CandyParticleMove *)particleJarFrontMove,
	(CandyParticleMove *)particleJarBackMove,
	(CandyParticleMove *)particleJarMove,
	(CandyParticleMove *)particleExplosionMove,
	(CandyParticleMove *)particleCStripleMove,
	(CandyParticleMove *)particleRColorMove,
	(CandyParticleMove *)particleRBombMove,
	(CandyParticleMove *)particleRStripMove,
	(CandyParticleMove *)particleStarBlinkMove,
	(CandyParticleMove *)particleStarPer1Move,
	(CandyParticleMove *)particleStarPer2Move,
	(CandyParticleMove *)particleStarPeringMove,
	(CandyParticleMove *)particleStarPerDoneMove,
	(CandyParticleMove *)particleStarFireMove,
	(CandyParticleMove *)particleExchangeMove,
	(CandyParticleMove *)particleDsipelMove,
	(CandyParticleMove *)particleLicoricesMove,
	(CandyParticleMove *)particleCreamMove,
	(CandyParticleMove *)particleLockMove,
	(CandyParticleMove *)particleChocolateMove,
	(CandyParticleMove *)particleJellyMove,
	(CandyParticleMove *)particleJelly2Move,
	(CandyParticleMove *)particleBombMove,
	(CandyParticleMove *)particleHorizonMove,
	(CandyParticleMove *)particleVerticalMove,
	(CandyParticleMove *)particleCEmitMove,
	(CandyParticleMove *)particleCFireMove,
	(CandyParticleMove *)particleCTargetMove,
	(CandyParticleMove *)particleComBBMove,
	(CandyParticleMove *)particleComBSMove,
	(CandyParticleMove *)particleComSSMove,
	(CandyParticleMove *)particleComCCMove,
	(CandyParticleMove *)LoginEffectMove,
	(CandyParticleMove *)mapActiveNewMove,
	(CandyParticleMove *)mapActiveNew2Move,
	(CandyParticleMove *)mapActiveloveMove,
	(CandyParticleMove *)particleSongXinEffectMove,
	(CandyParticleMove *)particleXinFengEffectMove,
	(CandyParticleMove *)particleAddlifeMessageEffectMove,
	(CandyParticleMove *)particleSongDaojuEffectMove,
	(CandyParticleMove *)LoginFlashEffectMove,
	(CandyParticleMove *)particleUnlockLevelEffecEffectMove,
	(CandyParticleMove *)GiftFrontEffectMove,
	(CandyParticleMove *)GiftBackEffectMove,
};


static CCParticleSystemQuad** particle[CANDY_PARTICLE_NUM]=
{	
	(CCParticleSystemQuad**)&particleDoubleScoreFireEffecEffect[0],
	(CCParticleSystemQuad**)&particleDoubleScoreEffecEffect[0],
	(CCParticleSystemQuad**)&particleChuiZiEffecEffect[0],
	(CCParticleSystemQuad**)&particleShenDengOpenEffect[0],
	(CCParticleSystemQuad**)&particleShenDengYaoDongEffect[0],
	(CCParticleSystemQuad**)&particleShenDengZhaKaiEffect[0],
	(CCParticleSystemQuad**)&particleYinTaoEffect[0],
	(CCParticleSystemQuad**)&particleWuYunEffect[0],
	(CCParticleSystemQuad**)&particleCandyCrushEffect[0],
	(CCParticleSystemQuad**)&particleWinEffect[0],
	(CCParticleSystemQuad**)&particlePressProp[0],
	(CCParticleSystemQuad**)&particleRewardLight[0],
	(CCParticleSystemQuad**)&particleWinLight[0],
	(CCParticleSystemQuad**)&particleTargetIcon[0],
	(CCParticleSystemQuad**)&particleCandyAppear[0],
	(CCParticleSystemQuad**)&particleStageClear[0],
	(CCParticleSystemQuad**)&particleStageFailed1[0],
	(CCParticleSystemQuad**)&particleStageFailed2[0],
	(CCParticleSystemQuad**)&particleRouleteeEdge[0],
	(CCParticleSystemQuad**)&particleRouleteeEnd[0],
	(CCParticleSystemQuad**)&particleLight[0],
	(CCParticleSystemQuad**)&particleUseProp1[0],
	(CCParticleSystemQuad**)&particleUseProp2[0],
	(CCParticleSystemQuad**)&particleUseProp3[0],
	(CCParticleSystemQuad**)&particleUseProp4[0],
	(CCParticleSystemQuad**)&particleUseProp5[0],
	(CCParticleSystemQuad**)&particleUseProp6[0],
	(CCParticleSystemQuad**)&particleUseProp7[0],
	(CCParticleSystemQuad**)&particlePropButton[0],
	(CCParticleSystemQuad**)&particleGuide[0],
	(CCParticleSystemQuad**)&particleResortIn[0],
	(CCParticleSystemQuad**)&particleResortOut[0],
	(CCParticleSystemQuad**)&particleJarFront[0],
	(CCParticleSystemQuad**)&particleJarBack[0],
	(CCParticleSystemQuad**)&particleJar[0],
	(CCParticleSystemQuad**)&particleExplosion[0],
	(CCParticleSystemQuad**)&particleCStriple[0],
	(CCParticleSystemQuad**)&particleRColor[0],
	(CCParticleSystemQuad**)&particleRBomb[0],
	(CCParticleSystemQuad**)&particleRStrip[0],
	(CCParticleSystemQuad**)&particleStarBlink[0],
	(CCParticleSystemQuad**)&particleStarPer1[0],
	(CCParticleSystemQuad**)&particleStarPer2[0],
	(CCParticleSystemQuad**)&particleStarPering[0],
	(CCParticleSystemQuad**)&particleStarPerDone[0],
	(CCParticleSystemQuad**)&particleStarFire[0],
	(CCParticleSystemQuad**)&particleExchange[0],
	(CCParticleSystemQuad**)&particleDsipel[0],
	(CCParticleSystemQuad **)&particleLicorices[0],
	(CCParticleSystemQuad**)&particleCream[0],
	(CCParticleSystemQuad**)&particleLock[0],
	(CCParticleSystemQuad**)&particleChocolate[0],
	(CCParticleSystemQuad**)&particleJelly[0],
	(CCParticleSystemQuad**)&particleJelly2[0],
	(CCParticleSystemQuad**)&particleBomb[0],
	(CCParticleSystemQuad**)&particleHorizon[0],
	(CCParticleSystemQuad**)&particleVertical[0],
	(CCParticleSystemQuad**)&particleCEmit[0],
	(CCParticleSystemQuad**)&particleCFire[0],
	(CCParticleSystemQuad**)&particleCTarget[0],
	(CCParticleSystemQuad**)&particleComBB[0],
	(CCParticleSystemQuad**)&particleComBS[0],
	(CCParticleSystemQuad**)&particleComSS[0],
	(CCParticleSystemQuad**)&particleComCC[0],
	(CCParticleSystemQuad**)&LoginEffect[0],
	(CCParticleSystemQuad**)&mapActiveNew[0],
	(CCParticleSystemQuad**)&mapActiveNew2[0],
	(CCParticleSystemQuad**)&mapActivelove[0],
	(CCParticleSystemQuad**)&particleSongXinEffect[0],
	(CCParticleSystemQuad**)&particleXinFengEffect[0],
	(CCParticleSystemQuad**)&particleAddlifeMessageEffect[0],
	(CCParticleSystemQuad**)&particleSongDaojuEffect[0],
	(CCParticleSystemQuad**)&LoginFlashEffect[0],
	(CCParticleSystemQuad**)&particleUnlockLevelEffecEffect[0],


};

static bool particleLoop[CANDY_PARTICLE_NUM] = 
{
	true,//CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT_NUM
	false,//CANDY_PARTICLE_DOUBLESCORE_EFFECT_NUM
	false,//CANDY_PARTICLE_CHUNZI_EFFECT_NUM
	false,//CANDY_PARTICLE_SHENDENGOPEN_EFFECT_NUM
	false,//CANDY_PARTICLE_SHENDENGYAODONG_EFFECT_NUM
	false,//CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT_NUM
	true,//CANDY_PARTICLE_YINTAO_EFFECT_NUM
	true,//CANDY_PARTICLE_WUYUN_EFFECT_NUM
	true,//CANDY_PARTICLE_CANDYCRUSH_EFFECT_NUM
	true,//CANDY_PARTICLE_WIN_EFFECT_NUM
	true,//CANDY_PARTICLE_PRESS_PROP_NUM
	true,//CANDY_PARTICLE_TARGET_ICON
	true,//CANDY_PARTICLE_WIN_LIGHT
	false,//CANDY_PARTICLE_TARGET_ICON
	false,//CANDY_PARTICLE_STAGE_CLEAR
	false,//CANDY_PARTICLE_STAGE_CLEAR
	false,//CANDY_PARTICLE_STAGE_FAILED1
	false,//CANDY_PARTICLE_STAGE_FAILED2
	true,//CANDY_PARTICLE_ROULETEE_EDGE,
	true,//CANDY_PARTICLE_ROULETEE_END,
	true,//CANDY_PARTICLE_LIGHT,
	true,//CANDY_PARTICLE_USE_PROP1
	false,//CANDY_PARTICLE_USE_PROP2
	false,//CANDY_PARTICLE_USE_PROP3
	false,//CANDY_PARTICLE_USE_PROP4
	false,//CANDY_PARTICLE_USE_PROP5
	false,//CANDY_PARTICLE_USE_PROP6
	true,//CANDY_PARTICLE_USE_PROP7
	true,//CANDY_PARTICLE_PROP_BUTTON
	false,//CANDY_PARTICLE_GUIDE_FINGER
	false,//CANDY_PARTICLE_RESORT_IN,
	false,//CANDY_PARTICLE_RESORT_OUT,
	true,//CANDY_PARTICLE_JAR_FRONT,
	true,//CANDY_PARTICLE_JAR_BACK,
	true,//CANDY_PARTICLE_JAR,
	false,//CANDY_PARTICLE_EXPLOSION,
	false,//CANDY_PARTICLE_CHANGE_STRIPLE,
	false,//CANDY_PARTICLE_RCOLOR,
	false,//CANDY_PARTICLE_RBOMB,
	false,//CANDY_PARTICLE_RSTRIP,
	false,//CANDY_PARTICLE_BLINK_PERCENT,
	false,//CANDY_PARTICLE_STAR_PERCENT1,
	false,//CANDY_PARTICLE_STAR_PERCENT2,	
	true,//CANDY_PARTICLE_STAR_PERCENTING,
	true,//CANDY_PARTICLE_STAR_PERCENTDONE
	false,//CANDY_PARTICLE_STAR_FIREWORKS,
	false,//CANDY_PARTICLE_NORMAL_EXCHANGE,
	false,//CANDY_PARTICLE_NORMAL_DISPEL,
	false,//CANDY_PARTICLE_BREAK_LICORICES,
	false,//CANDY_PARTICLE_BREAK_CREAM,
	false,//CANDY_PARTICLE_BREAK_LOCK,
	false,//CANDY_PARTICLE_BREAK_CHOCOLATE,
	false,//CANDY_PARTICLE_BREAK_JEELY,
	false,//CANDY_PARTICLE_BREAK_JEELY2,
	false,//CANDY_PARTICLE_SPE_BOMB,
	false,//CANDY_PARTICLE_SPE_HORIZON,
	false,//CANDY_PARTICLE_SPE_VERTICAL,
	false,//CANDY_PARTICLE_SPE_COLOR_EMIT,
	false,//CANDY_PARTICLE_SPE_COLOR_FIRE,
	false,//CANDY_PARTICLE_SPE_COLOR_TARGET,
	false,//CANDY_PARTICLE_COM_BB,
	false,//CANDY_PARTICLE_COM_BS,
	false,//CANDY_PARTICLE_COM_SS,
	false,//CANDY_PARTICLE_COM_CC,
	false,//CANDY_LOGIN_BOOMFLY_EFF,
	false,//CANDY_MAP_ACTIVE_NEW,
	true,//CANDY_MAP_ACTIVE_NEW2,
	true,//CANDY_MAP_ACTIVE_LOVELIFE,
	false,//CANDY_PARTICLE_SONGXIN_EFFECT_NUM
	false,//CANDY_PARTICLE_XINFENG_EFFECT_NUM
	false,//MAP_ACTIVE_ADDLIFEMESSAGE
	false,//CANDY_PARTICLE_SONGDAOJU_EFFECT_NUM
	true,//LOGIN_FLASH_EFF_NUM
	false,//LOGIN_FLASH_EFF_NUM
	true,//CANDY_GIFT_FRONT_EFFECT
	true,//CANDY_GIFT_BACK_EFFECT
};

static char* particleFile[CANDY_PARTICLE_NUM]=
{	
	(char *)"Particle/DoubleScoreFireEffect/",
	(char *)"Particle/DoubleScoreEffect/",
	(char *)"Particle/ChuiZiEffect/",
	(char *)"Particle/ShenDengOpenEffect/",
	(char *)"Particle/ShenDengYaoDongEffect/",
	(char *)"Particle/ShenDengZhaKaiEffect/",
	(char *)"Particle/YinTaoEffect/",
	(char *)"Particle/WuYunEffect/",
	(char *)"Particle/CandyCrushEffect/",
	(char *)"Particle/WinEffect/",
	(char *)"Particle/PressProp/",
	(char *)"Particle/RewardLight/",
	(char *)"Particle/StageClearLight/",
	(char *)"Particle/TargetIcon/",
	(char *)"Particle/CandyAppear/",
	(char *)"Particle/StageClearEffect/",
	(char *)"Particle/StageFailedEffect1/",
	(char *)"Particle/StageFailedEffect2/",
	(char *)"Particle/RouleteeEdge/",
	(char *)"Particle/RouleteeEnd/",
	(char *)"Particle/RouleteeLight/",
	(char *)"Particle/UsePropEffect1/",
	(char *)"Particle/UsePropEffect2/",
	(char *)"Particle/UsePropEffect3/",
	(char *)"Particle/UsePropEffect4/",
	(char *)"Particle/UsePropEffect5/",
	(char *)"Particle/UsePropEffect6/",
	(char *)"Particle/UsePropEffect7/",
	(char *)"Particle/PropButtonEffect/",
	(char *)"Particle/GuideFinger/",
	(char *)"Particle/ResortCandyIn/",
	(char *)"Particle/ResortCandyOut/",
	(char *)"Particle/CandyJarFront/",
	(char *)"Particle/CandyJarBack/",
	(char *)"Particle/CandyJarFull/",
	(char *)"Particle/ExplosionBomb/",
	(char *)"Particle/ChangeStriple/",
	(char *)"Particle/RouleteeBornColor/",
	(char *)"Particle/RouleteeBornBomb/",
	(char *)"Particle/RouleteeBornStrip/",
	(char *)"Particle/StarBlink/",
	(char *)"Particle/StarPercent1/",
	(char *)"Particle/StarPercent2/",
	(char *)"Particle/StarPercenting/",	
	(char *)"Particle/StarPercentDone/",
	(char *)"Particle/StarFireworks/",
	(char *)"Particle/NormalExchange/",
	(char *)"Particle/NormalDispel/",
	(char *)"Particle/BreakLicorices/",
	(char *)"Particle/BreakCream/",
	(char *)"Particle/BreakLock/",
	(char *)"Particle/BreakChocolate/",
	(char *)"Particle/BreakJelly/",
	(char *)"Particle/BreakJelly2/",
	(char *)"Particle/SpeBomb/",
	(char *)"Particle/SpeHorizon/",
	(char *)"Particle/SpeVertical/",
	(char *)"Particle/SpeColorEmit/",
	(char *)"Particle/SpeColorFire/",
	(char *)"Particle/SpeColorTarget/",
	(char *)"Particle/ComBBEffect/",
	(char *)"Particle/ComBSEffect/",
	(char *)"Particle/ComSSEffect/",
	(char *)"Particle/ComCCEffect/",
	(char *)"Particle/ggboomfly/",
	(char *)"Particle/MapActiveNew/",
	(char *)"Particle/MapActiveNew2/",
	(char *)"Particle/lovelife/",
	(char *)"Particle/SongXinEffect/",
	(char *)"Particle/XinFengEffect/",
	(char *)"Particle/addlifeeff/",
	(char *)"Particle/SongDaoju/",
	(char *)"Particle/logineff2/",
	(char *)"Particle/UnlockLevelEffect/",
	(char *)"Particle/GiftEffect2/",
	(char *)"Particle/GiftEffect1/",
	(char *)"Particle/testEffect/",
};

std::vector<CandyParticleManager>	CandyParticle::mCandyParticle;;

void CandyParticle::readParticleXML(int type, char* filepath)
{
	CCDictionary* pXmlFile = CCDictionary::createWithContentsOfFileThreadSafe( 
		CCString::createWithFormat("%sParticle.xml",filepath)->getCString() );

	if ( !pXmlFile )
		return;

	CandyParticleManager candyParMager;
	candyParMager.type = (CandyParticleType)type;
	candyParMager.filenum  = atoi( ((CCString*)pXmlFile->objectForKey( "fileNum" ))->m_sString.c_str() );
	candyParMager.isloop  = atoi( ((CCString*)pXmlFile->objectForKey( "isloop" ))->m_sString.c_str() );

	for (int i = 1; i<= candyParMager.filenum; i++)
	{
		int emission = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("emission%d",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.emission.push_back( emission );

		int blend = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("blend%d",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.blend.push_back( blend );

		int time = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("time%d",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.time.push_back( time );

		int rotate = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("rotate%d",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.rotate.push_back( rotate );

		CandyParticlePos pos;
		pos.x = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("pos%dX",i)->getCString()  ))->m_sString.c_str() );
		pos.y = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("pos%dY",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.pos.push_back( pos );

		CandyParticleMove move;
		move.x = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("move%dX",i)->getCString()  ))->m_sString.c_str() );
		move.y = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("move%dY",i)->getCString()  ))->m_sString.c_str() );
		move.time = atoi( ((CCString*)pXmlFile->objectForKey( 
			CCString::createWithFormat("move%dtime",i)->getCString()  ))->m_sString.c_str() );
		candyParMager.move.push_back( move );

		
	}
	mCandyParticle.push_back(candyParMager);
	pXmlFile->release();
	pXmlFile = NULL;

}

void CandyParticle::initCandyParicleForXml(void)
{
	mCandyParticle.clear();
	for(int type=0; type<CANDY_PARTICLE_NUM; type++)
	{
		readParticleXML(type, "Particle/testEffect/");
		for(int i=0; i<particleFileNum[type]; i++)
		{	
			if(particle[type][i])
				continue;
			particle[type][i] = CCParticleSystemQuad::create( CCString::createWithFormat("%stest%d.plist",particleFile[type],i+1)->getCString() );
			particle[type][i] ->retain();
		}
	}
}

void CandyParticle::initCandyParticle(void)
{
	for(int type=0; type<=CANDY_PARTICLE_COM_CC; type++)
	{
		for(int i=0; i<particleFileNum[type]; i++)
		{	
			if(particle[type][i])
				continue;
			particle[type][i] = CCParticleSystemQuad::create( CCString::createWithFormat("%stest%d.plist",particleFile[type],i+1)->getCString() );
			particle[type][i] ->retain();
		}
	}
}

void CandyParticle::destroyCandyParticle(void)
{
	for(int type=0; type<=CANDY_PARTICLE_COM_CC; type++)
	{
		for(int i=0; i<particleFileNum[type]; i++)
		{	
			if(!particle[type][i])
				continue;

			particle[type][i]->unscheduleUpdate();
			CC_SAFE_RELEASE_NULL(particle[type][i]);
		}
	}
}

CCParticleSystemQuad* CandyParticle::getCandyParticle(CandyParticleType type, int num)
{
	if(particle[type][num])
	{
		CCParticleSystemQuad* emitter = CCParticleSystemQuad::create(particle[type][num]);
		if(emitter)
			return emitter;
	}
	return NULL;
}


CCNode* CandyParticle::displayCandyParticleForXml(CandyParticleType type, CCPoint pos, CCNode* parent, int tag, int order)
{
	CCNode *node = CCNode::create();
	node->setPosition(pos);
	if(parent)
		parent->addChild(node,order,tag);
	else if(type < CANDY_LOGIN_BOOMFLY_EFF)
		CandyManager::getInstance()->effectLayer->addChild(node,0,tag);

	CCParticleSystemQuad* emitter;

	for(int i=0; i<mCandyParticle.at(type).filenum; i++)
	{
		if(type < CANDY_LOGIN_BOOMFLY_EFF)
		{
			emitter = getCandyParticle(type, i);
		}
		else
		{
			emitter = CCParticleSystemQuad::create( CCString::createWithFormat("%stest%d.plist",particleFile[type],i+1)->getCString() );
			emitter->setPositionType(kCCPositionTypeGrouped);
		}

		emitter->setBlendAdditive(mCandyParticle.at(type).blend.at(i)?true:false);
		emitter->setAutoRemoveOnFinish(!mCandyParticle.at(type).isloop);
		emitter->setEmissionRate(mCandyParticle.at(type).emission.at(i));
		emitter->setPosition(ccp(mCandyParticle.at(type).pos.at(i).x,mCandyParticle.at(type).pos.at(i).y));
		emitter->setRotation((float)mCandyParticle.at(type).rotate.at(i));
		emitter->_setZOrder(i);
		emitter->retain();
		if(mCandyParticle.at(type).time.at(i))
		{	
			node->runAction( CCSequence::create(CCDelayTime::create(0.001 * mCandyParticle.at(type).rotate.at(i) ),
				CCCallFuncND::create(node, callfuncND_selector(CandyParticle::callbackParticle), (void*)emitter),
				NULL));
		}
		else
		{
			node->runAction(CCCallFuncND::create(node, callfuncND_selector(CandyParticle::callbackParticle), (void*)emitter));
		}

		if(mCandyParticle.at(type).move.at(i).time)
		{
			CCAction *actionNode = CCMoveBy::create(0.001f * mCandyParticle.at(type).move.at(i).time,
				ccp(mCandyParticle.at(type).move.at(i).x, mCandyParticle.at(type).move.at(i).y));
			emitter->setUserData((void*)actionNode);
			actionNode->retain();
		}
		if(type == CANDY_PARTICLE_WIN_LIGHT)
			emitter->setPositionType(kCCPositionTypeRelative);
		else if(type == CANDY_PARTICLE_REWARD_LIGHT)
			emitter->setPositionType(kCCPositionTypeRelative);
	}
	if(!particleLoop[type])
	{
		node->runAction(CCSequence::create(
			CCDelayTime::create(10.0f),// finish effect in 10s 
			CCCallFuncN::create(node, callfuncN_selector(CandyParticle::callBackRemove)),
			NULL));
	}

	return node;	
}

CCNode* CandyParticle::displayCandyParticle(CandyParticleType type, CCPoint pos, CCNode* parent, int tag, int order)
{
	CCNode *node = CCNode::create();
	node->setPosition(pos);
	if(parent)
		parent->addChild(node,order,tag);
	else if(type < CANDY_LOGIN_BOOMFLY_EFF)
		CandyManager::getInstance()->effectLayer->addChild(node,0,tag);

	CCParticleSystemQuad* emitter;

	for(int i=0; i<particleFileNum[type]; i++)
	{
		if(type < CANDY_LOGIN_BOOMFLY_EFF)
		{
			emitter = getCandyParticle(type, i);
		}
		else
		{
			std::string path = CCString::createWithFormat("%stest%d.plist",particleFile[type],i+1)->getCString();
			emitter = CCParticleSystemQuad::create( path.c_str() );
			emitter->setPositionType(kCCPositionTypeGrouped);
		}

		emitter->setBlendAdditive(particleBlend[type][i]?true:false);
		emitter->setAutoRemoveOnFinish(!particleLoop[type]);
		emitter->setEmissionRate(particleEmission[type][i]);
		emitter->setPosition(ccp(particlePos[type][i].x,particlePos[type][i].y));
		emitter->setRotation((float)particleRotate[type][i]);
		emitter->_setZOrder(i);
		emitter->retain();
		if(particleTime[type][i])
		{
			node->runAction( CCSequence::create(CCDelayTime::create(0.001 * particleTime[type][i]),
				CCCallFuncND::create(node, callfuncND_selector(CandyParticle::callbackParticle), (void*)emitter),
				NULL));
		}
		else
		{
			node->runAction(CCCallFuncND::create(node, callfuncND_selector(CandyParticle::callbackParticle), (void*)emitter));
		}

		if(particleMove[type][i].time)
		{
			CCAction *actionNode = CCMoveBy::create(0.001f * particleMove[type][i].time,
				ccp(particleMove[type][i].x, particleMove[type][i].y));
			emitter->setUserData((void*)actionNode);
			actionNode->retain();
		}
		if(type == CANDY_PARTICLE_WIN_LIGHT)
			emitter->setPositionType(kCCPositionTypeRelative);
		else if(type == CANDY_PARTICLE_REWARD_LIGHT)
			emitter->setPositionType(kCCPositionTypeRelative);
	}
	if(!particleLoop[type])
	{
		node->runAction(CCSequence::create(
			CCDelayTime::create(10.0f),// finish effect in 10s 
			CCCallFuncN::create(node, callfuncN_selector(CandyParticle::callBackRemove)),
			NULL));
	}

	return node;	
}

void CandyParticle::callbackParticle(CCNode* sender, void* data)
{
	CCParticleSystemQuad* emitter = (CCParticleSystemQuad*)data;
	sender->addChild(emitter);

	CCAction *actionNode  = (CCAction *)emitter->getUserData();
	if(actionNode)
	{
		emitter->runAction(actionNode);
		actionNode->release();
	}
	emitter->release();
}


void CandyParticle::callBackRemove(CCNode* sender)
{
	sender->removeFromParent();
}

void CandyParticle::colorfullCandyParticle(CandyParticleType type,CandyColor color1,CandyColor color2)
{
	switch(type)
	{
	case CANDY_PARTICLE_SPE_HORIZON:
	case CANDY_PARTICLE_SPE_VERTICAL:
		if(color1<CANDY_COLOR_NORMAL_NUM)
		{
			ccColor4F c1;
			CandyShare::changeColor(color1, c1);
			if(particle[type][0] && particle[type][2] )
			{
				particle[type][0]->setStartColor(c1);
				particle[type][0]->setEndColor(c1);
				particle[type][2]->setStartColor(c1);
				particle[type][2]->setEndColor(c1);
			}
		}
		break;

	case CANDY_PARTICLE_COM_SS:
		if(color1<CANDY_COLOR_NORMAL_NUM)
		{
			ccColor4F c1;
			CandyShare::changeColor(color1, c1);
			if(particle[type][0] && particle[type][5] )
			{
				particle[type][0]->setStartColor(c1);
				particle[type][0]->setEndColor(c1);
				particle[type][5]->setStartColor(c1);
				particle[type][5]->setEndColor(c1);
			}
		}
		if(color2<CANDY_COLOR_NORMAL_NUM)
		{
			ccColor4F  c2;
			CandyShare::changeColor(color2, c2);
			if(particle[type][4] && particle[type][6] )
			{
				particle[type][4]->setStartColor(c2);
				particle[type][4]->setEndColor(c2);
				particle[type][6]->setStartColor(c2);
				particle[type][6]->setEndColor(c2);
			}
		}
		break;

	case CANDY_PARTICLE_EXPLOSION:
		if(color1<CANDY_COLOR_NORMAL_NUM)
		{
			ccColor4F c1;
			CandyShare::changeColor(color1, c1);
			if(particle[type][1] && particle[type][2] )
			{
				particle[type][1]->setStartColor(c1);
				particle[type][2]->setStartColor(c1);
				particle[type][2]->setEndColor(c1);
			}
		}
		break;

	case CANDY_PARTICLE_SPE_COLOR_TARGET:
		if(color1<CANDY_COLOR_NORMAL_NUM)
		{
			ccColor4F c1;
			CandyShare::changeColor(color1, c1);
			if(particle[type][0])
			{
				particle[type][0]->setStartColor(c1);
			}
		}
		break;
	}

}

void CandyParticle::setCandyParticleMove(CandyParticleType type,int time, int posX, int posY)
{
	if(type < 0 || type >= CANDY_PARTICLE_NUM)
		return;

	for(int i=0; i<particleFileNum[type]; i++ )
	{
		particleMove[type][i].time 		= time;
		particleMove[type][i].x 		= posX;
		particleMove[type][i].y 		= posY;
	}
}
