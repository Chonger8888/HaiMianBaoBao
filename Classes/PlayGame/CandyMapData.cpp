#include "CandyMapData.h"
#include "CandyManager.h"
#include "CCLuaEngine.h"
#include "../CppCallJava/CppCallJava.h"
extern "C"
{
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}


USING_NS_CC;


static lua_State* myLuaState;

CandyMapData::CandyMapData():candyDropMode(false)
{
	memset(&candyInMap[0][0],0,sizeof(CandyCell*) * CANDY_MAP_WIDTH * CANDY_MAP_HEIGH);

	//myLuaState = lua_open();  
	//luaopen_base(myLuaState);    

	initMapDataFromLua();
}

CandyMapData::~CandyMapData()
{
	//lua_close(myLuaState);   
}

void CandyMapData::initLoadLuaFile(void)
{

	CCLuaEngine* pEngine  = CCLuaEngine::defaultEngine();
	char *mapInfoPath= (char *)CCString::createWithFormat("lua/levelInfo.lua")->getCString();
	//char *mapInfoPath= (char *)CCString::createWithFormat("%slua/levelInfo.lua", AnalyseJson::CandPicPath)->getCString();
	CCLog("CandyMapData::initLoadLuaFile  %s", mapInfoPath );
	int err = pEngine->executeScriptFile(mapInfoPath);
	if(err)
	{
		CCLog("testBugLee--luaL_dofile   %s\n", lua_tostring(myLuaState, -1));
		CCAssert(0, "CandyMapData::luaL_dofile failed");
	}

	myLuaState = pEngine->getLuaStack()->getLuaState();
}

void CandyMapData::initMapDataFromLua(void)
{ 
	CCLog("initMapDataFromLua currentLevel[%d]", CandyManager::currentLevel);

	//num = %d",lua_gettop(myLuaState) get num
	lua_getglobal(myLuaState, CCString::createWithFormat("level%d",CandyManager::currentLevel)->getCString());	
	lua_pushstring(myLuaState, "CandyMapDataTable");  
	lua_gettable(myLuaState, -2);
	for(int h =0 ; h<CANDY_MAP_HEIGH ; h++)
		for(int w =0 ; w<CANDY_MAP_WIDTH ; w++)
		{
			mapData[h][w] = getTableNumFromLua(1+h*CANDY_MAP_WIDTH+w);
			if(mapData[h][w])
				mapData[h][w] |= 1;
		}
		lua_pop(myLuaState, 1);
		candyDropMode = getNumFromLua((char *)"candyDropMode")?true:false;
		CandyMove::moveLimit = getNumFromLua((char *)"moveLimit");
		CommonData::m_gamemode = CandyManager::gameMode = (CandyGameMode)getNumFromLua((char *)"gameMode");
		CandyManager::numberOfColours  = (int)getNumFromLua((char *)"numberOfColours");
		CandyScore::starScoreNum[0]= (int)getNumFromLua((char *)"oneStarScore");
		CandyScore::starScoreNum[1]  = (int)getNumFromLua((char *)"twoStarScore");
		CandyScore::starScoreNum[2]  = (int)getNumFromLua((char *)"threeStarScore");
		CandyLicorices::licoriceMax	= (int)getNumFromLua((char *)"licoriceMax");
		CandyLicorices::licoriceSpawn	= (int)getNumFromLua((char *)"licoriceSpawn");

		CandyExplosions::explosionMax	= (int)getNumFromLua((char *)"explosionMax");
		CandyExplosions::explosionTurns	= (int)getNumFromLua((char *)"explosionTurns");
		CandyExplosions::explosionSpawn	= (int)getNumFromLua((char *)"explosionSpawn");

		CandyManager::randomSeed	 =	getNumFromLua((char *)"randomSeed");
		//todo...
		CandyManager::modifyPercent	 =	getNumFromLua((char *)"modifyPercent");
		CandyManager::modifyRed		 =	getNumFromLua((char *)"modifyRed");
		CandyManager::modifyBlue	 =	getNumFromLua((char *)"modifyBlue");
		CandyManager::modifyGreen	 =	getNumFromLua((char *)"modifyGreen");
		CandyManager::modifyYellow   =	getNumFromLua((char *)"modifyYellow");
		CandyManager::modifyOrange   =	getNumFromLua((char *)"modifyOrange");
		CandyManager::modifyPurple   =	getNumFromLua((char *)"modifyPurple");

		CandyPlace::portalNum = getNumFromLua((char *)"portalNum");	
		if(CandyPlace::portalNum > 0)
		{
			lua_pushstring(myLuaState, "portalPlace");  
			lua_gettable(myLuaState, -2);
			for(int i=0; i<CandyPlace::portalNum; i++)
			{
				CandyPlace::portalPlace[i].entrance.x = getTableNumFromLua(1+i*4);
				CandyPlace::portalPlace[i].entrance.y = getTableNumFromLua(2+i*4);
				CandyPlace::portalPlace[i].exit.x = getTableNumFromLua(3+i*4);
				CandyPlace::portalPlace[i].exit.y = getTableNumFromLua(4+i*4);
			}
			lua_pop(myLuaState, 1);
		}
		CandyNewPortal::newPortalNum = getNumFromLua((char *)"newPortalNum");	
		if(CandyNewPortal::newPortalNum > 0)
		{
			lua_pushstring(myLuaState, "newPortalPlace");  
			lua_gettable(myLuaState, -2);
			for(int i=0; i<CandyNewPortal::newPortalNum; i++)
			{
				CandyNewPortal::newPortalPlace[i].place[0].x = getTableNumFromLua(1+i*4);
				CandyNewPortal::newPortalPlace[i].place[0].y = getTableNumFromLua(2+i*4);
				CandyNewPortal::newPortalPlace[i].place[1].x = getTableNumFromLua(3+i*4);
				CandyNewPortal::newPortalPlace[i].place[1].y = getTableNumFromLua(4+i*4);
			}
			lua_pop(myLuaState, 1);
		}
		if(CandyManager::numberOfColours == 0)
			CandyManager::numberOfColours = CANDY_COLOR_NORMAL_NUM;

		if(CandyExplosions::explosionTurns == 0)
			CandyExplosions::explosionTurns = 15;
		switch(CandyManager::gameMode)
		{
		case CANDY_MODE_NORMAL:
			break;

		case CANDY_MODE_JELLY:
			CandyIngredients::numjelly = (int)getNumFromLua((char *)"numjelly");
			break;

		case CANDY_MODE_INGREDIENT:
			{
				CandyIngredients::ingredientSpawnDensity = (int)getNumFromLua((char *)"ingredientSpawnDensity");
				CandyIngredients::numIngredientsOnScreen = (int)getNumFromLua((char *)"numIngredientsOnScreen");
				CandyIngredients::numCherry = (int)getNumFromLua((char *)"numCherry");
				CandyIngredients::numChesnut = (int)getNumFromLua((char *)"numChesnut");
			}
			break;

		case CANDY_MODE_TIMING:
			CandyManager::timeLimit = (float)getNumFromLua((char *)"timeLimit");
			break;

		case CANDY_MODE_COLLECT:
			lua_pushstring(myLuaState, "collectItem");  
			lua_gettable(myLuaState, -2);
			for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
			{
				CandyManager::collectCandy[i].type= (CandyCollectType)getTableNumFromLua(1+i*2);
				CandyManager::collectCandy[i].targetNum = getTableNumFromLua(2+i*2);
				CandyManager::collectCandy[i].currentNum = CandyManager::collectCandy[i].targetNum;
			}
			lua_pop(myLuaState, 1);
			break;
		}
		lua_pop(myLuaState, 1);
}


void CandyMapData::getMapdataFromLua( int level )
{
	lua_getglobal(myLuaState, CCString::createWithFormat("level%d",level)->getCString());	
	lua_pushstring(myLuaState, "CandyMapDataTable");  
	lua_gettable(myLuaState, -2);

	lua_pop(myLuaState, 1);
	CandyMove::moveLimit = getNumFromLua((char *)"moveLimit");
	CommonData::m_gamemode = CandyManager::gameMode = (CandyGameMode)getNumFromLua((char *)"gameMode");
	CandyManager::numberOfColours  = (int)getNumFromLua((char *)"numberOfColours");
	CandyScore::starScoreNum[0]= (int)getNumFromLua((char *)"oneStarScore");
	CandyScore::starScoreNum[1]  = (int)getNumFromLua((char *)"twoStarScore");
	CandyScore::starScoreNum[2]  = (int)getNumFromLua((char *)"threeStarScore");
	CandyLicorices::licoriceMax	= (int)getNumFromLua((char *)"licoriceMax");
	CandyLicorices::licoriceSpawn	= (int)getNumFromLua((char *)"licoriceSpawn");

	CandyExplosions::explosionMax	= (int)getNumFromLua((char *)"explosionMax");
	CandyExplosions::explosionTurns	= (int)getNumFromLua((char *)"explosionTurns");
	CandyExplosions::explosionSpawn	= (int)getNumFromLua((char *)"explosionSpawn");

	CandyManager::randomSeed	 =	getNumFromLua((char *)"randomSeed");
	//todo...
	CandyManager::modifyPercent	 =	getNumFromLua((char *)"modifyPercent");
	CandyManager::modifyRed		 =	getNumFromLua((char *)"modifyRed");
	CandyManager::modifyBlue	 =	getNumFromLua((char *)"modifyBlue");
	CandyManager::modifyGreen	 =	getNumFromLua((char *)"modifyGreen");
	CandyManager::modifyYellow   =	getNumFromLua((char *)"modifyYellow");
	CandyManager::modifyOrange   =	getNumFromLua((char *)"modifyOrange");
	CandyManager::modifyPurple   =	getNumFromLua((char *)"modifyPurple");

	CandyPlace::portalNum = getNumFromLua((char *)"portalNum");	
	if(CandyPlace::portalNum > 0)
	{
		lua_pushstring(myLuaState, "portalPlace");  
		lua_gettable(myLuaState, -2);
		for(int i=0; i<CandyPlace::portalNum; i++)
		{
			CandyPlace::portalPlace[i].entrance.x = getTableNumFromLua(1+i*4);
			CandyPlace::portalPlace[i].entrance.y = getTableNumFromLua(2+i*4);
			CandyPlace::portalPlace[i].exit.x = getTableNumFromLua(3+i*4);
			CandyPlace::portalPlace[i].exit.y = getTableNumFromLua(4+i*4);
		}
		lua_pop(myLuaState, 1);
	}
	CandyNewPortal::newPortalNum = getNumFromLua((char *)"newPortalNum");	
	if(CandyNewPortal::newPortalNum > 0)
	{
		lua_pushstring(myLuaState, "newPortalPlace");  
		lua_gettable(myLuaState, -2);
		for(int i=0; i<CandyNewPortal::newPortalNum; i++)
		{
			CandyNewPortal::newPortalPlace[i].place[0].x = getTableNumFromLua(1+i*4);
			CandyNewPortal::newPortalPlace[i].place[0].y = getTableNumFromLua(2+i*4);
			CandyNewPortal::newPortalPlace[i].place[1].x = getTableNumFromLua(3+i*4);
			CandyNewPortal::newPortalPlace[i].place[1].y = getTableNumFromLua(4+i*4);
		}
		lua_pop(myLuaState, 1);
	}
	if(CandyManager::numberOfColours == 0)
		CandyManager::numberOfColours = CANDY_COLOR_NORMAL_NUM;

	if(CandyExplosions::explosionTurns == 0)
		CandyExplosions::explosionTurns = 15;
	switch(CandyManager::gameMode)
	{
	case CANDY_MODE_NORMAL:
		break;

	case CANDY_MODE_JELLY:
		CandyIngredients::numjelly = (int)getNumFromLua((char *)"numjelly");
		break;

	case CANDY_MODE_INGREDIENT:
		{
			CandyIngredients::ingredientSpawnDensity = (int)getNumFromLua((char *)"ingredientSpawnDensity");
			CandyIngredients::numIngredientsOnScreen = (int)getNumFromLua((char *)"numIngredientsOnScreen");
			CandyIngredients::numCherry = (int)getNumFromLua((char *)"numCherry");
			CandyIngredients::numChesnut = (int)getNumFromLua((char *)"numChesnut");
		}
		break;

	case CANDY_MODE_TIMING:
		CandyManager::timeLimit = (float)getNumFromLua((char *)"timeLimit");
		break;

	case CANDY_MODE_COLLECT:
		lua_pushstring(myLuaState, "collectItem");  
		lua_gettable(myLuaState, -2);
		for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
		{
			CandyManager::collectCandy[i].type= (CandyCollectType)getTableNumFromLua(1+i*2);
			CandyManager::collectCandy[i].targetNum = getTableNumFromLua(2+i*2);
			CandyManager::collectCandy[i].currentNum = CandyManager::collectCandy[i].targetNum;
		}
		lua_pop(myLuaState, 1);
		break;
	}
	lua_pop(myLuaState, 1);
}


int CandyMapData::getTargetScore(int stage, int starNum)
{
	lua_getglobal(myLuaState, CCString::createWithFormat("level%d",stage)->getCString());
	switch(starNum)
	{
	case 1:
		return  (int)getNumFromLua((char *)"oneStarScore");
	case 2:
		return  (int)getNumFromLua((char *)"twoStarScore");
	case 3:
		return  (int)getNumFromLua((char *)"threeStarScore");
	}
	lua_pop(myLuaState, 1);
	return 0;
}

int CandyMapData::getTargetMode(int level)
{
	lua_getglobal(myLuaState, CCString::createWithFormat("level%d",level)->getCString());
	return  (int)getNumFromLua((char *)"gameMode");
}


unsigned int CandyMapData::getTableNumFromLua(int num)
{
	unsigned int result = 0;

	lua_pushnumber(myLuaState, (lua_Number)num);
	lua_gettable(myLuaState, -2);
	if (lua_isnumber(myLuaState, -1))
		result = (unsigned int)lua_tonumber(myLuaState, -1);
	lua_pop(myLuaState, 1);

	return result;
}

unsigned int CandyMapData::getNumFromLua(char *name)
{
	unsigned int result = 0;

	lua_pushstring(myLuaState, name);  
	lua_gettable(myLuaState, -2);
	if (lua_isnumber(myLuaState, -1))
		result = (unsigned int)lua_tonumber(myLuaState, -1);
	lua_pop(myLuaState, 1);

	return result;
}

bool CandyMapData::getMapCellStates(CandyIndex index, MapCellType type)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return false;

	return (mapData[index.y][index.x]>>type)&1;
}

void CandyMapData::setMapCellStates(CandyIndex index, MapCellType type, bool states)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return;

	if(states)
		mapData[index.y][index.x] |= (1<<type);
	else
		mapData[index.y][index.x] &= (~(1<<type));
}

CCDrawNode* CandyMapData::getMapShape(void)
{
	CCDrawNode *shape = CCDrawNode::create();

	CCPoint pos;
	CCPoint triangle[4];
	ccColor4F green = {0, 1, 0, 1};//  Ã»×÷ÓÃ?

	for(int h =0 ; h<CANDY_MAP_HEIGH ; h++)
		for(int w =0 ; w<CANDY_MAP_WIDTH ; w++)
		{
			if( getMapCellStates(cIndex(w, h), MAP_CELL_EXIST) )
			{
				pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(w, h));
				triangle[0] = ccp(pos.x -(CANDY_CELL_WIDTH>>1) , pos.y - (CANDY_CELL_HEIGHT>>1));
				triangle[1] = ccp(pos.x +(CANDY_CELL_WIDTH>>1) , pos.y - (CANDY_CELL_HEIGHT>>1));
				triangle[2] = ccp(pos.x +(CANDY_CELL_WIDTH>>1) , pos.y + (CANDY_CELL_HEIGHT>>1));
				triangle[3] = ccp(pos.x -(CANDY_CELL_WIDTH>>1) , pos.y + (CANDY_CELL_HEIGHT>>1));
				shape->drawPolygon(triangle, 4, green, 0, green);
				//return shape;	
			}
		}
		for(int i=0; i<CandyNewPortal::newPortalNum; i++)
		{
			for(int j=0; j<2; j++)
			{
				pos = CandyManager::getInstance()->shareMgr->getPosByIndex(CandyNewPortal::newPortalPlace[i].place[j]);
				triangle[0] = ccp(pos.x -(CANDY_CELL_WIDTH>>1) , pos.y - (CANDY_CELL_HEIGHT>>1));
				triangle[1] = ccp(pos.x +(CANDY_CELL_WIDTH>>1) , pos.y - (CANDY_CELL_HEIGHT>>1));
				triangle[2] = ccp(pos.x +(CANDY_CELL_WIDTH>>1) , pos.y + (CANDY_CELL_HEIGHT>>1));
				triangle[3] = ccp(pos.x -(CANDY_CELL_WIDTH>>1) , pos.y + (CANDY_CELL_HEIGHT>>1));
				shape->drawPolygon(triangle, 4, green, 0, green);
			}
		}


		return shape;	
}


CandyCell* CandyMapData::getCandyByIndex(CandyIndex index)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return NULL;

	return candyInMap[index.y][index.x] ;
}

void CandyMapData::setCandyByIndex(CandyIndex index, CandyCell *candy, bool changePos, bool resetOrigin)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return;

	candyInMap[index.y][index.x]  = candy;

	if(candy)
	{
		CandyCell *originCandy = getCandyByIndex(candy->index);
		if( !(candy->index.x == index.x && candy->index.y == index.y))
			if(resetOrigin && originCandy == candy)
				setCandyByIndex(candy->index, NULL);

		candy->index = index;
		setMapCellStates(index, MAP_CELL_CANDY, true);
		if(changePos)
			candy->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(candy->index));
	}
	else
	{
		setMapCellStates(index, MAP_CELL_CANDY, false);
	}
}

