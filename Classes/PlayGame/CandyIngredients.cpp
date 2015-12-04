#include "CandyIngredients.h"
#include "CandyManager.h"


// 运输模式
USING_NS_CC;

#define CANDY_INGREDIENT_EXIT_IMG		"dropIngredientFlag.png"

int CandyIngredients::numjelly = 0;
int CandyIngredients::ingredientSpawnDensity = 0;
int CandyIngredients::numIngredientsOnScreen = 0;
int CandyIngredients::numCherry = 0;
int CandyIngredients::numChesnut = 0;

CandyIngredients::CandyIngredients():numInMapCherry(0),numInMapChesnut(0),numDropDoneCherry(0),numDropDoneChesnut(0)
{
	
}

CandyIngredients::~CandyIngredients()
{
	
}

CandyCell* CandyIngredients::createIngredients(CandyIndex index)
{
	CandyColor type = getOneRemainIngredient();
	if(type == CANDY_COLOR_CHESNUT)
		{
			numInMapChesnut++;
		}
	else
		{
			numInMapCherry++;
		}

	moveCountFlag = CandyMove::moveLimit;
	return CandyCell::create(index, type, CANDY_SPECIAL_INGREDIENT);
}

void CandyIngredients::createIngredientsWithMapData(void)
{
	if(CandyManager::gameMode != CANDY_MODE_INGREDIENT)
		return;

	CandyIndex produceIndex[CANDY_MAP_WIDTH]; //可掉落位置
	int indexFlag[CANDY_MAP_WIDTH] = {0};
	int dropEnableNum = 0;				// 可掉落个数
	
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		{
			for(int x=0; x<CANDY_MAP_WIDTH; x++)
				{
					if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CANDY)
						|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_LOCK)
						|| !CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_FACTORY))
						continue;

					indexFlag[dropEnableNum] = 1;
					produceIndex[dropEnableNum++] = cIndex(x, y);
				}
		}
	for(int i=0; i<numIngredientsOnScreen; i++)
		{
			int flag = getRandomIndexFlag(&indexFlag[0], dropEnableNum);
			CandyCell *ingredients = createIngredients(produceIndex[flag]);
			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(ingredients->index, ingredients);
			CandyManager::getInstance()->candyLayer->addToCandyParent(ingredients);
		}
}

void CandyIngredients::createExitWithMapData(void)
{
	if(CandyManager::gameMode != CANDY_MODE_INGREDIENT)
		return;
	
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_INGREDIENT_EXIT))
			{
				CCSprite *ingredientExitSprite = CCSprite::createWithSpriteFrameName(CANDY_INGREDIENT_EXIT_IMG);
				CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(x, y));
				ingredientExitSprite->setPosition(ccp(pos.x, pos.y -30));
				ingredientExitSprite->setOpacity(100);
				ingredientExitSprite->setScale(0.5f);
				CandyManager::getInstance()->candyLayer->addToCandyBarrierTopBatchNode(ingredientExitSprite,1);

				CCActionInterval*  actionMove = CCMoveBy::create(1, ccp(0,-10));
				CCActionInterval*  actionMoveBack = actionMove->reverse();
				ingredientExitSprite->runAction( CCRepeatForever::create(CCSequence::create(actionMove, actionMoveBack, NULL)));

				CCActionInterval*  actionFade = CCFadeTo::create(1, 200);
				CCActionInterval*  actionFadeBack = CCFadeTo::create(1, 100);
				ingredientExitSprite->runAction( CCRepeatForever::create(CCSequence::create(actionFade, actionFadeBack, NULL)));
			}
		}
}

void CandyIngredients::updateIngredients(void)
{
	if(CandyManager::gameMode != CANDY_MODE_INGREDIENT)
		return;

	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
			{
				CandyCell* ingredients = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
				if(ingredients)
					if(ingredients->special  == CANDY_SPECIAL_INGREDIENT)
						if(ingredients->getCandyStates(CANDY_CELL_NORMAL))
							if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_INGREDIENT_EXIT))
								{
									CCPoint pos = ingredients->getPosition();
									ingredients->runCandyDeleteAction();
									if(ingredients->color == CANDY_COLOR_CHESNUT)
										{
											numDropDoneChesnut++;
											numInMapChesnut--;
											CandyParticle::displayCandyParticle(CANDY_PARTICLE_YINTAO_EFFECT,  pos);
											
										}
									else if(ingredients->color == CANDY_COLOR_CHERRY)
										{
											numDropDoneCherry++;
											numInMapCherry--;
										}

									CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_INGREDIENT, pos , ingredients->color);	
									CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_INGREDIENT);
								}
							
			}
}

bool CandyIngredients::isNeedToCreateNewIngredient(void)
{
	if(CandyManager::gameMode != CANDY_MODE_INGREDIENT)
		return false;

	int existedCherry  = numInMapCherry + numDropDoneCherry;
	int existedChesnut = numInMapChesnut + numDropDoneChesnut;
	
	if(existedCherry >= numCherry  &&  existedChesnut >= numChesnut)
		return false;

	if(moveCountFlag - CandyMove::moveLimit == ingredientSpawnDensity)
		return true;

	if(numInMapCherry + numInMapChesnut ==0)
		return true;
	
	return false;
}

int CandyIngredients::getRandomIndexFlag(int *array, int arrayNum)
{
	int i = rand()%arrayNum;
	while(!array[i])
		{
			i = ++i % arrayNum;
		}
	array[i] = 0;
	return i;
}

CandyColor CandyIngredients::getOneRemainIngredient(void)
{
	int existedCherry  = numInMapCherry + numDropDoneCherry;
	int existedChesnut = numInMapChesnut + numDropDoneChesnut;
	
	if(existedCherry < numCherry  &&  existedChesnut < numChesnut)
		return rand()%2?CANDY_COLOR_CHESNUT:CANDY_COLOR_CHERRY;
	else if(existedCherry < numCherry)
		return CANDY_COLOR_CHERRY;
	else
		return CANDY_COLOR_CHESNUT;
}
