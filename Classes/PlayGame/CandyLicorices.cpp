#include "CandyLicorices.h"
#include "CandyManager.h"

// ¸Ê²ÝÌÇ
USING_NS_CC;

int CandyLicorices::licoriceMax = 0;
int CandyLicorices::licoriceSpawn = 0;

CandyLicorices::CandyLicorices():currentLicoriceSpawn(0)
{

}

CandyLicorices::~CandyLicorices()
{
	
}

CandyCell* CandyLicorices::createLicorice(CandyIndex index)
{
	CandyCell *candy =  CandyCell::create(index, CANDY_COLOR_LICORICE, CANDY_SPECIAL_LICORICE);
	
	if(getCurrentLicoricesNum()+1 >= licoriceMax )
		licoriceSpawn = 0;
	
	return candy;
}

void CandyLicorices::createLicoricesWithMapData(void)
{
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
	{
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_LICORICE))
			{
				CandyCell *licorice = createLicorice(cIndex(x, y));
				CandyManager::getInstance()->mapDataMgr->setCandyByIndex(licorice->index, licorice);
				CandyManager::getInstance()->candyLayer->addToCandyParent(licorice);
			}
		}
	}
}

bool CandyLicorices::isNeedToCreateNewLicorice(void)
{
	if(licoriceMax == 0)
		return false;

	if(getCurrentLicoricesNum() >= licoriceMax)
		return false;

	if(currentLicoriceSpawn < licoriceSpawn)
		return false;
	
	return true;
}

int CandyLicorices::getCurrentLicoricesNum(void)
{
	int num = 0;
	
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	if(!candyArray)
		return 0;
	
	for(unsigned int i=0; i<candyArray->count(); i++)
		{
			CandyCell *candy = (CandyCell *)candyArray->objectAtIndex(i);
			if(candy->color == CANDY_COLOR_LICORICE)
				num ++;
		}
	return num;
}

void CandyLicorices::removeLicorice(CandyIndex index)
{
	CandyCell *candy;
	candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
	
	if(candy  && candy->getCandyStates(CANDY_CELL_NORMAL) && candy->color == CANDY_COLOR_LICORICE)
		{
			candy->runCandyDeleteAction();
			CandyManager::getInstance()->effectLayer->displayBreakLicorices(index);
		}
}

void CandyLicorices::dispelCandyEffectLicorice(CandyIndex dispelIndex)
{
	removeLicorice(cIndex(dispelIndex.x+1, dispelIndex.y));
	removeLicorice(cIndex(dispelIndex.x-1, dispelIndex.y));
	removeLicorice(cIndex(dispelIndex.x, dispelIndex.y+1));
	removeLicorice(cIndex(dispelIndex.x, dispelIndex.y-1));
}
