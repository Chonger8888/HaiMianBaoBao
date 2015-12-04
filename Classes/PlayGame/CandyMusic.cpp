#include "CandyMusic.h"
#include "CandyManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define CANDY_EFFECT_COMBO_NUM				12
#define CANDY_EFFECT_DROP_NUM					4

#define CANDY_MUSIC_PATH_HARMER			"Music/Harmer.mp3"
#define CANDY_MUSIC_PATH_CANDYCRUSH		"Music/candycrush.mp3"
#define CANDY_MUSIC_PATH_CHEER			"Music/Cheer.mp3"
#define CANDY_MUSIC_PATH_COMBO1			"Music/Combo1.mp3"
#define CANDY_MUSIC_PATH_COMBO2			"Music/Combo2.mp3"
#define CANDY_MUSIC_PATH_COMBO3			"Music/Combo3.mp3"
#define CANDY_MUSIC_PATH_COMBO4			"Music/Combo4.mp3"
#define CANDY_MUSIC_PATH_COMBO5			"Music/Combo5.mp3"
#define CANDY_MUSIC_PATH_COMBO6			"Music/Combo6.mp3"
#define CANDY_MUSIC_PATH_COMBO7			"Music/Combo7.mp3"
#define CANDY_MUSIC_PATH_COMBO8			"Music/Combo8.mp3"
#define CANDY_MUSIC_PATH_COMBO9			"Music/Combo9.mp3"
#define CANDY_MUSIC_PATH_COMBO10			"Music/Combo10.mp3"
#define CANDY_MUSIC_PATH_COMBO11			"Music/Combo11.mp3"
#define CANDY_MUSIC_PATH_COMBO12			"Music/Combo12.mp3"

#define CANDY_MUSIC_PATH_PRAISE2			"Music/ComboPraise2.mp3"
#define CANDY_MUSIC_PATH_PRAISE3			"Music/ComboPraise3.mp3"
#define CANDY_MUSIC_PATH_PRAISE4			"Music/ComboPraise4.mp3"
#define CANDY_MUSIC_PATH_PRAISE5			"Music/ComboPraise5.mp3"
#define CANDY_MUSIC_PATH_PRAISE6			"Music/ComboPraise6.mp3"
#define CANDY_MUSIC_PATH_PRAISE7			"Music/ComboPraise7.mp3"

#define CANDY_MUSIC_PATH_DROP1			"Music/Drop1.mp3"
#define CANDY_MUSIC_PATH_DROP2			"Music/Drop2.mp3"
#define CANDY_MUSIC_PATH_DROP3			"Music/Drop3.mp3"
#define CANDY_MUSIC_PATH_DROP4			"Music/Drop4.mp3"

#define CANDY_MUSIC_PATH_BUTTON			"Music/ButtonEffect.mp3"

#define CANDY_MUSIC_PATH_CHANGE_F			"Music/CandyChangeFail.mp3"
#define CANDY_MUSIC_PATH_CHANGE_D			"Music/CandyChangeDone.mp3"

#define CANDY_MUSIC_PATH_CHANGE_LICORICE	"Music/ChangeLicorice.mp3"
#define CANDY_MUSIC_PATH_NEW_VERTICAL	"Music/NewVerticalCandy.mp3"
#define CANDY_MUSIC_PATH_NEW_HORIZON		"Music/NewHorizonCandy.mp3"
#define CANDY_MUSIC_PATH_NEW_BOMB		"Music/NewBombCandy.mp3"
#define CANDY_MUSIC_PATH_NEW_COLORFULL	"Music/NewColorFullCandy.mp3"
#define CANDY_MUSIC_PATH_COM_CC			"Music/ComColorColor.mp3"
#define CANDY_MUSIC_PATH_COM_CB			"Music/ComColorfullBomb.mp3"
#define CANDY_MUSIC_PATH_COM_CS			"Music/ComColorfullStripe.mp3"
#define CANDY_MUSIC_PATH_COM_CN			"Music/ComColorFullNormal.mp3"
#define CANDY_MUSIC_PATH_COM_BB			"Music/ComBombBomb.mp3"
#define CANDY_MUSIC_PATH_COM_BS			"Music/ComBombStripe.mp3"
#define CANDY_MUSIC_PATH_DISPEL_STRIPE	"Music/DispelStripe.mp3"
#define CANDY_MUSIC_PATH_DISPEL_BOMB		"Music/DispelBomb.mp3"
#define CANDY_MUSIC_PATH_NO_STEPS			"Music/NoEnoughSteps.mp3"
#define CANDY_MUSIC_PATH_STAGE_CLEAR		"Music/StageClear.mp3"
#define CANDY_MUSIC_PATH_GAME_WARNING	"Music/GameWarning.mp3"
#define CANDY_MUSIC_PATH_TIME_ALARM		"Music/TimeAlarm.mp3"
#define CANDY_MUSIC_PATH_ROULETTE_IN		"Music/RouletteInside.mp3"
#define CANDY_MUSIC_PATH_CLEAR_STAR		"Music/StageStarClear.mp3"
#define CANDY_MUSIC_PATH_CLEAR_TIPS		"Music/SageClearTips.mp3"
#define CANDY_MUSIC_PATH_FAILED_TIPS		"Music/SageFailedTips.mp3"
#define CANDY_MUSIC_PATH_RESORT_TIPS	"Music/ResortCandyTips.mp3"
#define CANDY_MUSIC_PATH_INGREDIENT		"Music/GetIngredient.mp3"
#define CANDY_MUSIC_PATH_USE_STEP1		"Music/UserStep1.mp3"
#define CANDY_MUSIC_PATH_USE_STEP2		"Music/UserStep2.mp3"
#define CANDY_MUSIC_PATH_USE_STEP3		"Music/UserStep3.mp3"
#define CANDY_MUSIC_PATH_USE_STEP4		"Music/UserStep4.mp3"
#define CANDY_MUSIC_PATH_USE_STEP5		"Music/UserStep5.mp3"


#define CANDY_MUSIC_PATH_BGM1				"Music/GameBgm1.mp3"
#define CANDY_MUSIC_PATH_BGM2				"Music/GameBgm1.mp3"
#define CANDY_MUSIC_PATH_BGM3				"Music/GameBgm1.mp3"
#define CANDY_MUSIC_PATH_BGM4				"Music/GameBgm1.mp3"
#define CANDY_MUSIC_PATH_BGMROULETTE		"Music/RouletteMusic.mp3"


#define CANDY_MUSIC_PATH_GAME_OVER		"Music/GameOver.mp3"
#define CANDY_MUSIC_PATH_GAME_CLEAR		"Music/GameClear.mp3"

CandyMusic::CandyMusic()
{
	initMusicPath();
	memset(&playingEffect[0], 0, sizeof(int) * CANDY_MUSIC_NUM);
	reloadCandyGameMusic();
}

CandyMusic::~CandyMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	//unreloadCandyGameMusic();
}

void CandyMusic::initMusicPath(void)
{
	candyMusicPath[CANDY_EFFECT_HAMMER]		= 		(char *)CANDY_MUSIC_PATH_HARMER;
	candyMusicPath[CANDY_EFFECT_CANDYCRUSH]		= 	(char *)CANDY_MUSIC_PATH_CANDYCRUSH;
	candyMusicPath[CANDY_EFFECT_CHEER]			= 	(char *)CANDY_MUSIC_PATH_CHEER;
	candyMusicPath[CANDY_EFFECT_COMBO1]			= 	(char *)CANDY_MUSIC_PATH_COMBO1;
	candyMusicPath[CANDY_EFFECT_COMBO2]			= 	(char *)CANDY_MUSIC_PATH_COMBO2;
	candyMusicPath[CANDY_EFFECT_COMBO3]			= 	(char *)CANDY_MUSIC_PATH_COMBO3;
	candyMusicPath[CANDY_EFFECT_COMBO4]			= 	(char *)CANDY_MUSIC_PATH_COMBO4;
	candyMusicPath[CANDY_EFFECT_COMBO5]			= 	(char *)CANDY_MUSIC_PATH_COMBO5;
	candyMusicPath[CANDY_EFFECT_COMBO6]			= 	(char *)CANDY_MUSIC_PATH_COMBO6;
	candyMusicPath[CANDY_EFFECT_COMBO7]			= 	(char *)CANDY_MUSIC_PATH_COMBO7;
	candyMusicPath[CANDY_EFFECT_COMBO8]			= 	(char *)CANDY_MUSIC_PATH_COMBO8;
	candyMusicPath[CANDY_EFFECT_COMBO9]			= 	(char *)CANDY_MUSIC_PATH_COMBO9;
	candyMusicPath[CANDY_EFFECT_COMBO10]			= 	(char *)CANDY_MUSIC_PATH_COMBO10;
	candyMusicPath[CANDY_EFFECT_COMBO11]			= 	(char *)CANDY_MUSIC_PATH_COMBO11;
	candyMusicPath[CANDY_EFFECT_COMBO12]			= 	(char *)CANDY_MUSIC_PATH_COMBO12;
	candyMusicPath[CANDY_EFFECT_PRAISE2]			= 	(char *)CANDY_MUSIC_PATH_PRAISE2;
	candyMusicPath[CANDY_EFFECT_PRAISE3]			= 	(char *)CANDY_MUSIC_PATH_PRAISE3;
	candyMusicPath[CANDY_EFFECT_PRAISE4]			= 	(char *)CANDY_MUSIC_PATH_PRAISE4;
	candyMusicPath[CANDY_EFFECT_PRAISE5]			= 	(char *)CANDY_MUSIC_PATH_PRAISE5;
	candyMusicPath[CANDY_EFFECT_PRAISE6]			= 	(char *)CANDY_MUSIC_PATH_PRAISE6;
	candyMusicPath[CANDY_EFFECT_PRAISE7]			= 	(char *)CANDY_MUSIC_PATH_PRAISE7;
	candyMusicPath[CANDY_EFFECT_DROP1] 			= 	(char *)CANDY_MUSIC_PATH_DROP1;
	candyMusicPath[CANDY_EFFECT_DROP2] 			= 	(char *)CANDY_MUSIC_PATH_DROP2;
	candyMusicPath[CANDY_EFFECT_DROP3] 			= 	(char *)CANDY_MUSIC_PATH_DROP3;
	candyMusicPath[CANDY_EFFECT_DROP4] 			= 	(char *)CANDY_MUSIC_PATH_DROP4;
	candyMusicPath[CANDY_EFFECT_BUTTON] 			= 	(char *)CANDY_MUSIC_PATH_BUTTON;
	candyMusicPath[CANDY_EFFECT_CHANGE_FAIL] 		= 	(char *)CANDY_MUSIC_PATH_CHANGE_F;
	candyMusicPath[CANDY_EFFECT_CHANGE_LICORICE] 	= 	(char *)CANDY_MUSIC_PATH_CHANGE_LICORICE;
	candyMusicPath[CANDY_EFFECT_CHANGE_DONE] 		= 	(char *)CANDY_MUSIC_PATH_CHANGE_D;
	candyMusicPath[CANDY_EFFECT_NEW_VERTICAL] 		= 	(char *)CANDY_MUSIC_PATH_NEW_VERTICAL;
	candyMusicPath[CANDY_EFFECT_NEW_HORIZON] 		= 	(char *)CANDY_MUSIC_PATH_NEW_VERTICAL;//(char *)CANDY_MUSIC_PATH_NEW_HORIZON;
	candyMusicPath[CANDY_EFFECT_NEW_BOMB] 		= 	(char *)CANDY_MUSIC_PATH_NEW_BOMB;
	candyMusicPath[CANDY_EFFECT_NEW_COLORFULL] 	= 	(char *)CANDY_MUSIC_PATH_NEW_COLORFULL;
	candyMusicPath[CANDY_EFFECT_COM_COLOR_COLOR] 	= 	(char *)CANDY_MUSIC_PATH_COM_CC;
	candyMusicPath[CANDY_EFFECT_COM_COLOR_BOMB] 	= 	(char *)CANDY_MUSIC_PATH_COM_CB;
	candyMusicPath[CANDY_EFFECT_COM_COLOR_STRIPE] = 	(char *)CANDY_MUSIC_PATH_COM_CS;
	candyMusicPath[CANDY_EFFECT_COM_COLOR_NORMAL] = 	(char *)CANDY_MUSIC_PATH_COM_CN;
	candyMusicPath[CANDY_EFFECT_COM_BOMB_BOMB] 	= 	(char *)CANDY_MUSIC_PATH_COM_BB;
	candyMusicPath[CANDY_EFFECT_COM_BOMB_STRIPE] 	= 	(char *)CANDY_MUSIC_PATH_COM_BS;
	candyMusicPath[CANDY_EFFECT_DISPEL_STRIPE] 		= 	(char *)CANDY_MUSIC_PATH_DISPEL_STRIPE;
	candyMusicPath[CANDY_EFFECT_DISPEL_BOMB] 		= 	(char *)CANDY_MUSIC_PATH_DISPEL_BOMB;
	candyMusicPath[CANDY_EFFECT_NO_ENOUGH_STEPS] 	= 	(char *)CANDY_MUSIC_PATH_NO_STEPS;
	candyMusicPath[CANDY_EFFECT_STAGE_CLEAR] 		= 	(char *)CANDY_MUSIC_PATH_STAGE_CLEAR;
	candyMusicPath[CANDY_EFFECT_GAME_WARNING] 	= 	(char *)CANDY_MUSIC_PATH_GAME_WARNING;
	candyMusicPath[CANDY_EFFECT_TIME_ALARM] 		= 	(char *)CANDY_MUSIC_PATH_TIME_ALARM;
	candyMusicPath[CANDY_EFFECT_ROULETTE_IN] 		= 	(char *)CANDY_MUSIC_PATH_ROULETTE_IN;
	candyMusicPath[CANDY_EFFECT_CLEAR_STAR] 		= 	(char *)CANDY_MUSIC_PATH_CLEAR_STAR;
	candyMusicPath[CANDY_EFFECT_CLEAR_TIPS] 		= 	(char *)CANDY_MUSIC_PATH_CLEAR_TIPS;
	candyMusicPath[CANDY_EFFECT_FAILED_TIPS] 		= 	(char *)CANDY_MUSIC_PATH_FAILED_TIPS;
	candyMusicPath[CANDY_EFFECT_RESORT_TIPS] 		= 	(char *)CANDY_MUSIC_PATH_RESORT_TIPS;
	candyMusicPath[CANDY_EFFECT_INGREDIENT] 		= 	(char *)CANDY_MUSIC_PATH_INGREDIENT;
	candyMusicPath[CANDY_EFFECT_USE_STEP1] 		= 	(char *)CANDY_MUSIC_PATH_USE_STEP1;
	candyMusicPath[CANDY_EFFECT_USE_STEP2] 		= 	(char *)CANDY_MUSIC_PATH_USE_STEP2;
	candyMusicPath[CANDY_EFFECT_USE_STEP3] 		= 	(char *)CANDY_MUSIC_PATH_USE_STEP3;
	candyMusicPath[CANDY_EFFECT_USE_STEP4] 		= 	(char *)CANDY_MUSIC_PATH_USE_STEP4;
	candyMusicPath[CANDY_EFFECT_USE_STEP5] 		= 	(char *)CANDY_MUSIC_PATH_USE_STEP5;
	
	candyMusicPath[CANDY_BG_BGM1] 				= 	(char *)CANDY_MUSIC_PATH_BGM1;
	candyMusicPath[CANDY_BG_BGM2] 				= 	(char *)CANDY_MUSIC_PATH_BGM2;
	candyMusicPath[CANDY_BG_BGM3] 				= 	(char *)CANDY_MUSIC_PATH_BGM3;
	candyMusicPath[CANDY_BG_BGM4] 				= 	(char *)CANDY_MUSIC_PATH_BGM4;
	candyMusicPath[CANDY_BG_ROULETTE] 			= 	(char *)CANDY_MUSIC_PATH_BGMROULETTE;
	candyMusicPath[CANDY_BG_GAME_OVER] 			= 	(char *)CANDY_MUSIC_PATH_GAME_OVER;
	candyMusicPath[CANDY_BG_GAME_CLEAR] 			= 	(char *)CANDY_MUSIC_PATH_GAME_CLEAR;

#ifndef rocklee
	static char sdCardMusicPath[CANDY_MUSIC_NUM][100] = {0};
	for(int i =0; i<CANDY_MUSIC_NUM; i++)
		{
			sprintf(&sdCardMusicPath[i][0], "/sdcard/WemeCandy/%s",candyMusicPath[i]);
			FILE* sdCardMusic =  fopen(&sdCardMusicPath[i][0], "r+");
			if(sdCardMusic)
				{
					fclose(sdCardMusic);
					candyMusicPath[i] = &sdCardMusicPath[i][0];
				}
		}
#endif
	

}

void CandyMusic::updateCandyMusic(void)
{
	const int delay = 3;
	for(int i=0; i<CANDY_MUSIC_NUM; i++)
		{
			if( i == CANDY_EFFECT_GAME_WARNING)
				{
				
				}
			else if(playingEffect[i] != 0)
				{
					if( playingEffect[i]++ > delay)
						playingEffect[i] = 0;
				}
		}
}

void CandyMusic::reloadCandyGameMusic(void)
{
	static int k = 0;
	if(k++)
		return;
	for(int i= CANDY_EFFECT_COMBO1; i <= CANDY_EFFECT_GAME_WARNING; i++ )
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(candyMusicPath[i] );
		}
	
}

void CandyMusic::unreloadCandyGameMusic(void)
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				
	for(int i= CANDY_EFFECT_COMBO1; i <= CANDY_EFFECT_GAME_WARNING; i++ )
		{
			SimpleAudioEngine::sharedEngine()->unloadEffect(candyMusicPath[i] );
		}
}
		
void CandyMusic::playMusic(CandyMusicType type)
{
#if 1//ndef WIN32
	if(playingEffect[type] != 0)
		return;

	if(type <=CANDY_EFFECT_HAMMER && CommonData::getSoundEffectState()==false)
		return;

	if(type >CANDY_EFFECT_HAMMER && CommonData::getBackgroundState()==false)
		return;
	 
	switch(type)
		{
			case CANDY_EFFECT_COMBO1:
			case CANDY_EFFECT_COMBO2:
			case CANDY_EFFECT_COMBO3:
			case CANDY_EFFECT_COMBO4:
			case CANDY_EFFECT_COMBO5:
			case CANDY_EFFECT_COMBO6:
			case CANDY_EFFECT_COMBO7:
			case CANDY_EFFECT_COMBO8:
			case CANDY_EFFECT_COMBO9:
			case CANDY_EFFECT_COMBO10:
			case CANDY_EFFECT_COMBO11:
			case CANDY_EFFECT_COMBO12:
			case CANDY_EFFECT_PRAISE2:
			case CANDY_EFFECT_PRAISE3:
			case CANDY_EFFECT_PRAISE4:
			case CANDY_EFFECT_PRAISE5:
			case CANDY_EFFECT_PRAISE6:
			case CANDY_EFFECT_PRAISE7:
			case CANDY_EFFECT_DROP1:
			case CANDY_EFFECT_DROP2:
			case CANDY_EFFECT_DROP3:
			case CANDY_EFFECT_DROP4:
			case CANDY_EFFECT_BUTTON:
			case CANDY_EFFECT_CHANGE_FAIL:
			case CANDY_EFFECT_CHANGE_DONE:
			case CANDY_EFFECT_CHANGE_LICORICE:
			case CANDY_EFFECT_NEW_VERTICAL:
			case CANDY_EFFECT_NEW_HORIZON:
			case CANDY_EFFECT_NEW_BOMB:
			case CANDY_EFFECT_NEW_COLORFULL:
			case CANDY_EFFECT_COM_COLOR_COLOR:
			case CANDY_EFFECT_COM_COLOR_BOMB:
			case CANDY_EFFECT_COM_COLOR_STRIPE:
			case CANDY_EFFECT_COM_COLOR_NORMAL:
			case CANDY_EFFECT_COM_BOMB_BOMB:
			case CANDY_EFFECT_COM_BOMB_STRIPE:
			case CANDY_EFFECT_DISPEL_STRIPE:
			case CANDY_EFFECT_DISPEL_BOMB:
			case CANDY_EFFECT_NO_ENOUGH_STEPS:
			case CANDY_EFFECT_TIME_ALARM:
			case CANDY_EFFECT_ROULETTE_IN:
			case CANDY_EFFECT_CLEAR_STAR:
			case CANDY_EFFECT_STAGE_CLEAR:
			case CANDY_EFFECT_RESORT_TIPS:
			case CANDY_EFFECT_INGREDIENT:
			case CANDY_EFFECT_USE_STEP1:
			case CANDY_EFFECT_USE_STEP2:
			case CANDY_EFFECT_USE_STEP3:
			case CANDY_EFFECT_USE_STEP4:
			case CANDY_EFFECT_USE_STEP5:
			case CANDY_EFFECT_CHEER:
			case CANDY_EFFECT_CANDYCRUSH:
			case CANDY_EFFECT_HAMMER:
				SimpleAudioEngine::sharedEngine()->playEffect(candyMusicPath[type]);
				break;
			
			case CANDY_EFFECT_CLEAR_TIPS:
			case CANDY_EFFECT_FAILED_TIPS:
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				SimpleAudioEngine::sharedEngine()->playEffect(candyMusicPath[type]);
				break;
				
			case CANDY_EFFECT_GAME_WARNING:
			#if 1
				SimpleAudioEngine::sharedEngine()->playEffect(candyMusicPath[type]);
			#else
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				 SimpleAudioEngine::sharedEngine()->playBackgroundMusic(candyMusicPath[type], true);
			#endif
				break;
				
			case CANDY_BG_BGM1:
			case CANDY_BG_BGM2:
			case CANDY_BG_BGM3:
			case CANDY_BG_BGM4:
			case CANDY_BG_ROULETTE:
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(candyMusicPath[type]);
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(candyMusicPath[type], true);
				break;

			case CANDY_BG_GAME_CLEAR:
				if(0)//playingEffect[CANDY_EFFECT_GAME_WARNING] )
					SimpleAudioEngine::sharedEngine()->stopEffect(warningEffectId);

				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(candyMusicPath[type]);
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(candyMusicPath[type], false);
				break;

			case CANDY_BG_GAME_OVER:
				if(0)//playingEffect[CANDY_EFFECT_GAME_WARNING] )
					SimpleAudioEngine::sharedEngine()->stopEffect(warningEffectId);
				
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(candyMusicPath[type]);
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(candyMusicPath[type], true);
				break;
		}
	playingEffect[type]   =  1;
#endif
}

void CandyMusic::playComboEffect(int comboNumber)
{
	if(comboNumber  > CANDY_EFFECT_COMBO12)
		comboNumber = CANDY_EFFECT_COMBO12;
	CandyManager::getInstance()->musicMgr->playMusic((CandyMusicType)comboNumber);
}

void CandyMusic::playUseStepEffect(int num)
{
	CandyMusicType type = (CandyMusicType)(CANDY_EFFECT_USE_STEP1 + num);
	if(type < CANDY_EFFECT_USE_STEP1)
		type = CANDY_EFFECT_USE_STEP1;
	
	if(type > CANDY_EFFECT_USE_STEP5)
		type = CANDY_EFFECT_USE_STEP5;
	
	CandyManager::getInstance()->musicMgr->playMusic(type);
}

void CandyMusic::playPraiseEffect(int comboNumber)
{
	CandyMusicType praiseEffect;
	if(comboNumber <= 1)
		{
			return;
		}
	else if( comboNumber <= 2)
		{
			praiseEffect = CANDY_EFFECT_PRAISE2;
		}
	else if( comboNumber <= 3)
		{
			praiseEffect = CANDY_EFFECT_PRAISE3;
		}
	else if( comboNumber <= 4)
		{
			praiseEffect = CANDY_EFFECT_PRAISE4;
		}
	else if( comboNumber <= 5)
		{
			praiseEffect = CANDY_EFFECT_PRAISE5;
		}
	else if( comboNumber <= 6)
		{
			praiseEffect = CANDY_EFFECT_PRAISE6;
		}
	else if( comboNumber >=7)
		{
			praiseEffect = CANDY_EFFECT_PRAISE7;
		}
	else
		{
			return;
		}
	playMusic(praiseEffect);
}

void CandyMusic::playDropEffect(int dropLen)
{
	CandyMusicType dropEffect;
	if(dropLen <=3)
		{
			dropEffect = CANDY_EFFECT_DROP1;
		}
	else if(dropLen <=5)
		{
			dropEffect = CANDY_EFFECT_DROP2;
		}
	else if(dropLen <=7)
		{
			dropEffect = CANDY_EFFECT_DROP3;
		}
	else if(dropLen <=9)
		{
			dropEffect = CANDY_EFFECT_DROP4;
		}
	else
		{
			return;
		}
	playMusic(dropEffect);
}


void CandyMusic::playBgm(void)
{
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
				playMusic(CANDY_BG_BGM1);
				break;

			case CANDY_MODE_JELLY:
				playMusic(CANDY_BG_BGM1);
				break;

			case CANDY_MODE_INGREDIENT:
				playMusic(CANDY_BG_BGM2);
				break;

			case CANDY_MODE_TIMING:
				playMusic(CANDY_BG_BGM3);
				break;

			case CANDY_MODE_COLLECT:
				playMusic(CANDY_BG_BGM4);
				break;
				
		}
}