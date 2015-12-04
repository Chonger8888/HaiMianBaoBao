#include "CandyPlace.h"
#include "CandyManager.h"
/************************/
/* 糖果位置ai			   */
/***********************/
USING_NS_CC;

#define PORTAL_ENTRANCE_IMG		"PortalEntrance"
#define PORTAL_EXIT_IMG				"PortalExit"

CandyPortalPlace CandyPlace::portalPlace[18] ={0};
int CandyPlace::portalNum = 0;
		
CandyPlace::CandyPlace()
{
	dropCandyArray = new CCArray();
	moveCandyArray = new CCArray();
	slideCandyArray = new CCArray();
	deletingCandyArray = new CCArray();
	memset(&dropCount[0], 0, sizeof(int) * CANDY_MAP_WIDTH);
}

CandyPlace::~CandyPlace()
{
	CC_SAFE_DELETE(dropCandyArray);
	CC_SAFE_DELETE(moveCandyArray);
	CC_SAFE_DELETE(slideCandyArray);
	CC_SAFE_DELETE(deletingCandyArray);
}

// 创建传送门出口
void CandyPlace::createPortalsLogo(CCPoint &pos, char *imgName)
{
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s1.png",imgName)->getCString());
	sprite->setPosition(pos);
	CandyManager::getInstance()->candyLayer->addToCandyBarrierTopBatchNode(sprite);

	CCArray *animFramesArray = CCArray::create();
	for(int i =0; i<9; i++)
		{
			CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				CCString::createWithFormat("%s%d.png",imgName,i+1)->getCString());
			animFramesArray->addObject(frame);
		}
	CCAnimation *portalAnimation = CCAnimation::createWithSpriteFrames(animFramesArray , 0.08f);
	sprite->runAction(CCRepeatForever::create(CCAnimate::create(portalAnimation)));
}

// 创建传送门入口
void CandyPlace::createPortalsLogos(void)
{
	for(int i=0; i<portalNum; i++)
		{
			CCPoint entrancePos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(portalPlace[i].entrance.x, portalPlace[i].entrance.y));
			entrancePos.y = entrancePos.y -  (CANDY_CELL_HEIGHT >>1);
			createPortalsLogo(entrancePos, (char *)PORTAL_ENTRANCE_IMG);

			CCPoint exitPos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(portalPlace[i].exit.x, portalPlace[i].exit.y));
			exitPos.y = exitPos.y + (CANDY_CELL_HEIGHT >>1);
			createPortalsLogo(exitPos, (char *)PORTAL_EXIT_IMG);
			#if 0
			CCPoint entrancePos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(portalPlace[i].entrance.x, portalPlace[i].entrance.y));
			CCSprite *entranceSprite = CCSprite::create(PORTAL_ENTRANCE_IMG);
			entranceSprite->setPosition(ccp(entrancePos.x, entrancePos.y - (CANDY_CELL_HEIGHT >>2)));
			CandyManager::getInstance()->candyLayer->addChild(entranceSprite);
		
			CCPoint exitPos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(portalPlace[i].exit.x, portalPlace[i].exit.y));
			CCSprite *exitSprite = CCSprite::create(PORTAL_EXIT_IMG);
			exitSprite->setPosition(ccp(exitPos.x, exitPos.y + (CANDY_CELL_HEIGHT >>2)));
			CandyManager::getInstance()->candyLayer->addChild(exitSprite);
			#endif
		}
}

void CandyPlace::updateCandyPlace(void)
{
	updateAvoidErrorPlace();
	updateCandyDrop();
	updateCandyPortals();
	updateCandyProduce();
	updateCandySlide();
}

void CandyPlace::updateAvoidErrorPlace(void)
{
	if(!CandyManager::getInstance()->shareMgr->getCandyIdle())
		return;
	
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y= 0; y<CANDY_MAP_HEIGH; y++)
			{
				CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
				
				if(!candy)
					continue;

				if(candy->index.x != x || candy->index.y != y)
					if(candy == CandyManager::getInstance()->mapDataMgr->getCandyByIndex(candy->index))
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(x, y), NULL);
			}
}

//取得最大下落点,遇到障碍物则停止
int CandyPlace::getMaxDownPos(CandyIndex index)
{
	int downPosY;
	
	for(downPosY = index.y; downPosY<CANDY_MAP_HEIGH; downPosY++)
		{
			int temDownPosY = downPosY;
			// 下方是否为空
			if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY), MAP_CELL_DOWN_EMPTY))
				{
					//循环直到找到非空
					while(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY+1), MAP_CELL_EXIST ))
						{
							if(++temDownPosY >= CANDY_MAP_HEIGH)//防止死循环
								return downPosY;
						}
				}

			//有障碍或锁，无法再下落
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY+1), MAP_CELL_BARRIER)
				 || CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY+1), MAP_CELL_LOCK)
				#ifndef rocklee
				 || CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY+1), MAP_CELL_CANDY)
				#endif
				  || !CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temDownPosY+1), MAP_CELL_EXIST ))
					return downPosY;

				downPosY = temDownPosY;
		}
	
	return downPosY;
	
}

//取得最大上方点,遇到障碍物则停止
int CandyPlace::getMinUpPos(CandyIndex index)
{
	int upPosY;
	
	for(upPosY = index.y; upPosY >= 0; upPosY--)
		{
			int temUpPosY = upPosY;
			
			//上方是否为可掉落空
			if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temUpPosY), MAP_CELL_UP_EMPTY))
				{
					//循环直到找到非空
					while(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temUpPosY-1), MAP_CELL_EXIST ))
						{
							if(--temUpPosY < 0)//防止死循环
								return upPosY;
						}
					
				}

			//有障碍或锁，无法再下落
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temUpPosY-1), MAP_CELL_BARRIER)
				 || CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temUpPosY-1), MAP_CELL_LOCK)
				  || !CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, temUpPosY -1), MAP_CELL_EXIST ))
					return upPosY;

			upPosY = temUpPosY;
		}
	
	return upPosY;
	
}

bool CandyPlace::getCandyDropEnable(CandyIndex index, CandyIndex &dropIndex)
{
 	int dropBottomY = getMaxDownPos(index);

	for(int y= dropBottomY; y> index.y; y--)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(index.x, y));
			if(candy && candy->getCandyStates(CANDY_CELL_DELETING) )
				return false;
		}
	
	for(int y= dropBottomY; y>index.y; y--)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, y), MAP_CELL_EXIST) 
				&& !CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(index.x, y),  MAP_CELL_CANDY)
				&& !CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(index.x, y),  MAP_CELL_BARRIER))
				{
					dropIndex  = cIndex(index.x, y);
					return true;
				}
		}
	return false;
}

void CandyPlace::updateCandyDrop(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y= CANDY_MAP_HEIGH-1; y>=0; y--)
			{
				if( !CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y),  MAP_CELL_CANDY) 
					|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y),  MAP_CELL_LOCK) )
					continue;

				CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
				if( !candy  || !candy->getCandyStates(CANDY_CELL_NORMAL))
					continue;

				CandyIndex dropIndex;
				if( getCandyDropEnable(candy->index, dropIndex) )
					{
						candy->runCandyDropAction(dropIndex);
					}
			}
}

//参数index为需填充candy的格子，获取掉落到该格子的candy 
CandyCell *CandyPlace::getCandyOfProduce(CandyIndex index, int &dropFlag)
{	
	for(int y=index.y; y>=0; y--)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex(index.x,  y));
			if(candy)
				{
					return candy;
				}
			else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x,  y), MAP_CELL_FACTORY))//生产新的candy
				{
					CandyCell *newCandy;
					if(CandyManager::getInstance()->ingredientsMgr->isNeedToCreateNewIngredient())
						{
							newCandy = CandyManager::getInstance()->ingredientsMgr->createIngredients(cIndex(index.x,  y+ (--dropFlag)));
							CandyManager::getInstance()->candyLayer->addToCandyParent(newCandy);
							
						}
					else if(CandyManager::getInstance()->explosionMgr->isNeedToCreateNewExplosion())
						{
							newCandy = CandyManager::getInstance()->explosionMgr->createExplosion(cIndex(index.x,  y+ (--dropFlag)));
							CandyManager::getInstance()->candyLayer->addToCandyParent(newCandy);
						}
					else if(CandyManager::getInstance()->licoricesMgr->isNeedToCreateNewLicorice())
						{
							newCandy = CandyManager::getInstance()->licoricesMgr->createLicorice(cIndex(index.x,  y+ (--dropFlag)));
							CandyManager::getInstance()->candyLayer->addToCandyParent(newCandy);
						}
					else
						{
							newCandy = CandyCell::create(cIndex(index.x,  y+ (--dropFlag)), 
									CandyManager::getInstance()->shareMgr->getCandyRandomColorByLua(), CANDY_SPECIAL_NORMAL);
							CandyManager::getInstance()->candyLayer->addToCandyParent(newCandy);
						}
					newCandy->setCandyProduceFlag(cIndex(index.x,  y-1));
					return newCandy;
				}
		}
	return NULL;
}


//获取起始位置上的candy最大掉落位置，遇到障碍物停止，返回-1表示不可掉落
int CandyPlace::getMaxDownPosFromFactory(CandyIndex index)
{
	int bottomEmptyY = index.y ;
	//跳过空格子
	while(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, bottomEmptyY), MAP_CELL_EXIST))
		{
			if(++bottomEmptyY >= CANDY_MAP_HEIGH)
				return -1;
		}
	
	//检测是否为障碍物
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, bottomEmptyY), MAP_CELL_BARRIER)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, bottomEmptyY), MAP_CELL_LOCK))
		 return -1;
			
	bottomEmptyY = getMaxDownPos(cIndex(index.x, bottomEmptyY));

	return bottomEmptyY;
	
}




//检测当前candy	是否已填充最底部的格子
bool CandyPlace::getDropRequireSituation(int x, int bottomY)
{	
	//寻找不带candy的格子
	for(; bottomY >= 0; bottomY--)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, bottomY), MAP_CELL_EXIST) 
				&& !CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, bottomY),  MAP_CELL_CANDY))
				break;
		}

	int topCandyY;
	for(topCandyY= getMinUpPos(cIndex(x, bottomY)); topCandyY<bottomY ; topCandyY++)
		{
			 if(CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x,topCandyY),  MAP_CELL_CANDY))
			 	break;
		}

	//最上方的candy位置在空格子的下方，则返回true，可检测掉落
	return topCandyY >= bottomY;
}
	
void CandyPlace::updateCandyProduce(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=0; y<CANDY_MAP_HEIGH; y++)
		{
			if(x == 3 && y ==5)
				x = 3;
			if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex( x, y), MAP_CELL_FACTORY))
				continue;
			
			int bottomEmptyY = getMaxDownPosFromFactory(cIndex( x, y));
			if(bottomEmptyY == -1)
				continue;
			
			if(!getDropRequireSituation(x, bottomEmptyY))
				continue;

			for(int y1= bottomEmptyY; y1>=y; y1--)
			{
				if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y1), MAP_CELL_EXIST) 
					|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y1),  MAP_CELL_CANDY))
					continue;
				
				CandyCell *dropCandy = getCandyOfProduce(cIndex(x, y1), dropCount[x]);
				
				if(dropCandy && dropCandy->getCandyStates(CANDY_CELL_NORMAL))
					{
						dropCandy->runCandyDropAction(cIndex(x, y1));
					}
			}
		}
		
	memset(&dropCount[0], 0, sizeof(int) * CANDY_MAP_WIDTH);	
}


/* 检测格子当前位置或上方是否有candy下落*/
bool CandyPlace::getDropCandyBlcokExist(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates( index,  MAP_CELL_CANDY))
		return true;
	
	CCPoint blockPos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(index.x, index.y+1));
	
	for(int i =0;	 i<(int)dropCandyArray->count(); 	i++)
		{
			CandyCell *candy =  (CandyCell *)dropCandyArray->objectAtIndex(i);
			if(candy->index.x == index.x)
				{
					float candyPosY = candy->getPositionY();
					if(candyPosY > blockPos.y)
						return true;
				}
		}
	return false;
}

//检测上方是否有candy要滑落
bool CandyPlace::getSlideRequireSituation(CandyIndex &index)
{
	int dropTopY = getMinUpPos(index);

	for(int i = 0; i<portalNum; i++)//检测传送门
		{
			if(portalPlace[i].exit.x == index.x  && portalPlace[i].exit.y == dropTopY)
				{
					return CandyManager::getInstance()->mapDataMgr->getMapCellStates( portalPlace[i].entrance,  MAP_CELL_BARRIER)
						|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( portalPlace[i].entrance,  MAP_CELL_LOCK);
				}
		}
	
	for(int y= index.y; y>=dropTopY; y--)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(index.x, y),  MAP_CELL_CANDY) 
				|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(index.x, y),  MAP_CELL_FACTORY) )
				{
					return false;
				}
		}
	return true;
}

/*direction : +1->right   -1 -> left */
bool CandyPlace::getCandySlideEnable(CandyCell *candy, int direction)
{	
	CandyIndex originIndex = candy->index;
	CandyIndex targetIndex = cIndex(originIndex.x + direction, originIndex.y +1);

	if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(targetIndex, MAP_CELL_EXIST) 
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( targetIndex,  MAP_CELL_CANDY)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( targetIndex,  MAP_CELL_BARRIER))
		return false;

	if(!getSlideRequireSituation(targetIndex))
		return false;

	//可以阻挡滑落的点
	CCPoint blockPos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex(targetIndex.x, targetIndex.y+1));
	
	for(int i =0;	 i<(int)dropCandyArray->count(); 	i++)
		{
			CandyCell *candy =  (CandyCell *)dropCandyArray->objectAtIndex(i);
			if(candy->index.x == targetIndex.x)
				{
					float candyPosY = candy->getPositionY();
					if(candyPosY > blockPos.y)
						return false;
				}
		}
	
	return true;
}

void CandyPlace::updateCandySlide(void)
{
	for(int y= 0; y < CANDY_MAP_HEIGH; y++)
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
			{
				if( !CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y),  MAP_CELL_CANDY) 
					|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y),  MAP_CELL_LOCK) )
					continue;

				CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
				if( !candy  || !candy->getCandyStates(CANDY_CELL_NORMAL))
					continue;

				if(getCandySlideEnable(candy, -1))
					{
						CandyIndex targetIndex = cIndex(candy->index.x-1,  candy->index.y+1);
						CandyIndex dropIndex;
						bool dropFlag = getCandyDropEnable(targetIndex, dropIndex);
						candy->runCandySlideAction(targetIndex, dropIndex, dropFlag);
					}
				else if(getCandySlideEnable(candy, 1))
					{
						CandyIndex targetIndex = cIndex(candy->index.x+1,  candy->index.y+1);
						CandyIndex dropIndex;
						bool dropFlag = getCandyDropEnable(targetIndex, dropIndex);
						candy->runCandySlideAction(targetIndex, dropIndex, dropFlag);
					}
				
			}
			
}

//参数index为需填充candy的格子，获取掉落到该格子的candy 
CandyCell *CandyPlace::getCandyOfPortal(CandyIndex index, int portal)
{	
	for(int y=index.y; y>= portalPlace[portal].exit.y;  y--)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex(index.x,  y));
			if(candy)
				return candy;
		}
	//传送candy  此处 y == portalPlace[portal].exit.y-1

	CandyCell *entranceCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( portalPlace[portal].entrance);
	if(!entranceCandy || !entranceCandy->getCandyStates(CANDY_CELL_NORMAL))
		return NULL;

	entranceCandy->runCandyPortalAction(cIndex(portalPlace[portal].entrance.x, portalPlace[portal].entrance.y+1));

	//此处判断是普通糖果还是板栗甘草等特殊物品

	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(portalPlace[portal].exit.x, portalPlace[portal].exit.y),  MAP_CELL_FACTORY) )
		--dropCount[portalPlace[portal].exit.x];
	
	CandyCell *exitCandy = CandyCell::create(cIndex(portalPlace[portal].exit.x, portalPlace[portal].exit.y-1), 
					entranceCandy->color, entranceCandy->special);

	if(exitCandy->special == CANDY_SPECIAL_EXPLOSION)
		{
			int time = (int)entranceCandy->getUserData();
			CandyManager::getInstance()->explosionMgr->setCandyExplosionTime(exitCandy, time);
		}
	
	CandyManager::getInstance()->candyLayer->addToCandyParent(exitCandy);

//新建的糖果需要加入旧糖果的所在的一些队列
	if(CandyManager::getInstance()->specialMgr->activedSpecialContainsCandy(entranceCandy))
		{
			CandyManager::getInstance()->specialMgr->removeActivedSpecial(entranceCandy);
			CandyManager::getInstance()->specialMgr->addActivedSpecial(exitCandy);
		}

	if(CandyManager::getInstance()->combinationMgr->activedCombinationContainsCandy(entranceCandy))
		{
			CandyManager::getInstance()->combinationMgr->removeActivedCombination(entranceCandy);
			CandyManager::getInstance()->combinationMgr->addActivedCombination(exitCandy);
		}
	
	return exitCandy;
			
}


void CandyPlace::updateCandyPortals(void)
{
	for(int i=0; i<portalNum; i++)
		{
			int x = portalPlace[i].exit.x;

			int bottomEmptyY = getMaxDownPosFromFactory(portalPlace[i].exit);
			if(bottomEmptyY == -1)
				continue;
			
			if(!getDropRequireSituation(x, bottomEmptyY))
				continue;

			for(int y= bottomEmptyY; y>=portalPlace[i].exit.y; y--)
			{
				if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXIST) 
					|| CandyManager::getInstance()->mapDataMgr->getMapCellStates( cIndex(x, y),  MAP_CELL_CANDY))
					continue;
				
				CandyCell *portalCandy = getCandyOfPortal(cIndex(x, y), i);
				
				if(portalCandy && portalCandy->getCandyStates(CANDY_CELL_NORMAL))
					{
						portalCandy->runCandyDropAction(cIndex(x, y));
					}
			}
		}
}

void CandyPlace::addCandyToDropArray(CandyCell *candy)
{
	if(!dropCandyArray->containsObject(candy))
		dropCandyArray->addObject(candy);
}

void CandyPlace::removeCandyFromDropArray(CandyCell *candy)
{
	if(dropCandyArray->containsObject(candy))
		dropCandyArray->removeObject(candy);
}
