#include "CandyNewPortal.h"
#include "CandyManager.h"

#define NEW_PORTAL_IMG			"newPortal"

CandyNewPortalPlace CandyNewPortal::newPortalPlace[18] = {0};
int CandyNewPortal::newPortalNum = 0;

CandyNewPortal::CandyNewPortal()
{	

}

CandyNewPortal::~CandyNewPortal()
{
	
}

void CandyNewPortal::createNewPortalsLogo(void)
{

	for(int i=0; i<CandyNewPortal::newPortalNum; i++)
		{
			for(int j=0; j<2; j++)
				{
					CCPoint pos= CandyManager::getInstance()->shareMgr->getPosByIndex(CandyNewPortal::newPortalPlace[i].place[j]);
					CCSprite *sprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s1.png",NEW_PORTAL_IMG)->getCString());
					sprite->setPosition(pos);
					CandyManager::getInstance()->candyLayer->addToCandyBarrierBottomBatchNode(sprite);

					CCArray *animFramesArray = CCArray::create();
					for(int i =0; i<9; i++)
						{
							CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
								CCString::createWithFormat("%s%d.png",NEW_PORTAL_IMG,i+1)->getCString());
							animFramesArray->addObject(frame);
						}
					CCAnimation *portalAnimation = CCAnimation::createWithSpriteFrames(animFramesArray , 0.08f);
					sprite->runAction(CCRepeatForever::create(CCAnimate::create(portalAnimation)));
					
				}
		}
}

void CandyNewPortal::updateCandyNewPortal(void)
{
	
}

bool CandyNewPortal::getPortalTargetIndex(CandyIndex origin, CandyIndex &target)
{
	for(int i=0; i<CandyNewPortal::newPortalNum; i++)
		{
			for(int j=0; j<2; j++)
				if(newPortalPlace[i].place[j].x == origin.x && newPortalPlace[i].place[j].y == origin.y)
					{
						target = newPortalPlace[i].place[1-j];
						return true;
					}
		}
	return false;
}

void CandyNewPortal::checkCandyMoveNewPortal(CandyIndex first, CandyIndex second)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(first, MAP_CELL_LOCK))
		return;

	CandyCell *portalCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(first);
	if(!portalCandy)
		return;

	CandyIndex portalTargetIndex;
	if(!getPortalTargetIndex(second, portalTargetIndex))
		return;
	
	portalCandy->runCandyNewPortalAction(second, portalTargetIndex);
	

}