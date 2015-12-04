#include "CandyMove.h"
#include "CandyManager.h"

int CandyMove::moveLimit = 0;

CandyMove::CandyMove()
{	
	if(CandyManager::gameMode != CANDY_MODE_TIMING)
		{
		/*
			if(CandyMove::moveLimit <8)
				warningMoveNum = 2;
			else if(CandyMove::moveLimit <15)
				warningMoveNum = 5;
			else if(CandyMove::moveLimit <25)
				warningMoveNum = 7;
			else if(CandyMove::moveLimit <35)
				warningMoveNum = 10;
			else if(CandyMove::moveLimit <45)
				warningMoveNum = 12;
			else// if(CandyMove::moveLimit <60)
				warningMoveNum = 15;
		*/
			warningMoveNum = 5;
		}
}

CandyMove::~CandyMove()
{
	
}
		
void CandyMove::updateCandyMove(void)
{
	if(moveFlag == false)
		return;

	CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstMove);
	CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(secondMove);
	if(!candy1  || !candy2 || candy1->getCandyStates(CANDY_CELL_MOVING) || candy2->getCandyStates(CANDY_CELL_MOVING))
		return;

	moveFlag = false;


	if(moveMode == CHANGE_MODE_BY_SYS)
		{
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy1);
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy2);
			return;
		}
	else if(CandyManager::getInstance()->combinationMgr->checkCandyCombination(candy1, candy2))/*是否特殊组合*/
		{
			CandyManager::getInstance()->combinationMgr->runCandyCombination(candy1, candy2);
			
		}
	else/*正常消除*/
		{
			CandyDispelCell *dispel1 = CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy1);
			CandyDispelCell *dispel2 = CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy2);	

			if(!dispel1  && !dispel2)	// 移动位置后 ,无法造成消除,回置
				{
					moveCandy( firstMove,  secondMove, CHANGE_MODE_BY_SYS);
					CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CHANGE_FAIL);
					return;
				}
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CHANGE_DONE);
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy1);
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy2);	
		}
	
	moveDone();
	
}

void CandyMove::moveDone(void)
{
	//此处移动成功，需减步数
	if(CandyManager::gameMode != CANDY_MODE_TIMING)
		{
			--CandyMove::moveLimit;
			if(CandyMove::moveLimit <= warningMoveNum)
				CandyManager::getInstance()->uiLayer->displayMoveWarning();
		}
		

	//重置巧克力
	CandyManager::getInstance()->chocolateMgr->resetDispelChocolateFlag();

	//减去炸弹时间
	CandyManager::getInstance()->explosionMgr->decreaseExplosionsTime();
	CandyManager::getInstance()->explosionMgr->decreaseExplosionsSpawn();

	//甘草糖生成计时
	CandyManager::getInstance()->licoricesMgr->currentLicoriceSpawn++;
#if 0
	if(CandyMove::moveLimit <= 0)
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_NO_ENOUGH_STEPS);

	if(CandyManager::gameMode == CANDY_MODE_TIMING)
		{
			if(CandyManager::timeLimit <10.0f)
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_GAME_WARNING);
		}
	else
		{
			if(CandyMove::moveLimit < warningMoveNum)
				void CandyUiLayer::displayMoveWarning(void)
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_GAME_WARNING);
		}
#endif
	}

void CandyMove::moveCandy(CandyIndex first, CandyIndex second, CandyChangeMode mode)
{	
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(first, MAP_CELL_LOCK)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(second, MAP_CELL_LOCK))
		return;
		
	CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(first);
	CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(second);
	if(!candy1  || !candy2)
		return;

	candy1->runCandyMoveAction(second);
	candy2->runCandyMoveAction(first);
	
	moveMode = mode;
	switch(moveMode)
		{
			case CHANGE_MODE_BY_USER:
				moveFlag = true;
				firstMove = first;
				secondMove = second;
				if(candy1->color == CANDY_COLOR_LICORICE || candy2->color == CANDY_COLOR_LICORICE)
					CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CHANGE_LICORICE);
				CandyManager::getInstance()->effectLayer->displayExchangeCandyEffect(firstMove);
				CandyManager::getInstance()->effectLayer->displayExchangeCandyEffect( secondMove);
				break;

			case CHANGE_MODE_BY_SYS:
				moveFlag = true;
				break;

			case CHANGE_MODE_BY_ANYWAY:
				CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy1);
				CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(candy2);	
				break;
		}
}


