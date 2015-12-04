#include "CandyExplosions.h"
#include "CandyManager.h"



// ¶¨Ê±Õ¨µ¯ 
USING_NS_CC;

#define EXPLOSION_NUM_LABEL		"Image/CandyGame/Candy/Cell/ExplosionNumLabel.png"	
#define EXPLOSION_ANIMATION_IMG	"ExplosionAnimation"
#define EXPLOSION_NUM_WIDTH		15	
#define EXPLOSION_NUM_HEIGH		16
#define TAG_EXPLOSION_NUM1        	201
#define TAG_EXPLOSION_NUM2       	202

int CandyExplosions::explosionMax = 0;
int CandyExplosions::explosionTurns = 0;
int CandyExplosions::explosionSpawn = 0;

CandyExplosions::CandyExplosions():currentExplosionSpawn(0)
{
	
}


CandyExplosions::~CandyExplosions()
{

}

void CandyExplosions::updateExplosions(void)
{
	
}

void CandyExplosions::decreaseExplosionsTime(void)
{
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	for(unsigned int i=0; i<candyArray->count(); i++)
	{
		CandyCell *candy = (CandyCell *)candyArray->objectAtIndex(i);
		if(candy->special == CANDY_SPECIAL_EXPLOSION)
		{
			int time = (int)candy->getUserData();
			setCandyExplosionTime(candy, time-1);
			if(time == 3)
				addExplosionsAnimation(candy, true);
		}
	}
}

void CandyExplosions::addExplosionsAnimation(CCNode* node, bool offsetFlag)
{
#ifdef CANDY_USE_PLIST
	const int explosionsAnimationTag = 305;
	if(node->getChildByTag(explosionsAnimationTag))
		return;
	
	CCSprite *actionSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s0.png",EXPLOSION_ANIMATION_IMG)->getCString());
	CCArray *animFramesArray = CCArray::create();
	for(int i =0; i<10; i++)
		{
			CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				CCString::createWithFormat("%s%d.png",EXPLOSION_ANIMATION_IMG,i)->getCString());
			animFramesArray->addObject(frame);
		}
	CCAnimation *portalAnimation = CCAnimation::createWithSpriteFrames(animFramesArray , 0.05f);
	actionSprite->runAction(CCRepeatForever::create(CCAnimate::create(portalAnimation)));
	if(offsetFlag)
		actionSprite->setPosition(ccp(40,28));
	node->addChild(actionSprite,1,explosionsAnimationTag);
#endif
}

void CandyExplosions::decreaseExplosionsSpawn(void)
{
	if(getCurrentExplosionsNum() < explosionMax)
		CandyManager::getInstance()->explosionMgr->currentExplosionSpawn++;
}

CandyCell* CandyExplosions::getExplosionsCandy(void)
{
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	if(candyArray)
		{
			for(unsigned int i=0; i<candyArray->count(); i++)
				{
					CandyCell *candy = (CandyCell *)candyArray->objectAtIndex(i);
					if(candy->special == CANDY_SPECIAL_EXPLOSION)
						{
							int time = (int)candy->getUserData();
							if(time <=0)
								return candy;
						}
				}
		}
	
	return NULL;
	
}

bool CandyExplosions::isReadyToExplode(void)
{
	return getExplosionsCandy()?true:false;
}

void CandyExplosions::setCandyExplosionTime(CandyCell *candy, int time)
{
	candy->setUserData((void *)time);
	
	candy->removeChildByTag(TAG_EXPLOSION_NUM1);
	candy->removeChildByTag(TAG_EXPLOSION_NUM2);
#ifdef CANDY_USE_PLIST	
	float scale = 1.5f;
	CCPoint pos = ccp(CANDY_CELL_WIDTH>>1, CANDY_CELL_HEIGHT>>1);
	pos.y = pos.y - 10;

	ccColor4F  color4;
	CandyShare::changeColor(candy->color, color4);
	ccColor3B  color3 ={color4.r *255, color4.g *255,color4.b *255};
	if(time/10)
		{
			const char *numString1 = CCString::createWithFormat("CandyExplosionNum%d.png",time/10)->getCString();
			CCSprite *numSprite1 = CCSprite::createWithSpriteFrameName(numString1);
			numSprite1->setPosition(ccp(pos.x -numSprite1->getTextureRect().size.width*0.5*scale, pos.y));
			numSprite1->setScale(scale);
			numSprite1->setColor(ccBLACK);
			candy->addChild(numSprite1,0,TAG_EXPLOSION_NUM1);
			pos = ccp(pos.x +numSprite1->getTextureRect().size.width*0.5*scale, pos.y);
		}
	
	const char *numString2 = CCString::createWithFormat("CandyExplosionNum%d.png",time%10)->getCString();
	CCSprite *numSprite2 = CCSprite::createWithSpriteFrameName(numString2);
	numSprite2->setPosition(pos);
	numSprite2->setScale(scale);
	numSprite2->setColor(ccBLACK);
	candy->addChild(numSprite2,0,TAG_EXPLOSION_NUM2);

#else
	CCPoint pos = ccp(CANDY_CELL_WIDTH>>1, CANDY_CELL_HEIGHT>>1);
	pos.x = pos.x +2;
	pos.y = pos.y -8;
	
	CCLabelAtlas* numLabel = CCLabelAtlas::create(CCString::createWithFormat("%d",time)->getCString(), 
							EXPLOSION_NUM_LABEL, EXPLOSION_NUM_WIDTH, EXPLOSION_NUM_HEIGH, '0');
	numLabel->setAnchorPoint(ccp(0.5,0.5));
	numLabel->setPosition(pos);
	candy->addChild(numLabel,0,TAG_EXPLOSION_NUM);
#endif
}

CandyCell* CandyExplosions::createExplosion(CandyIndex index)
{
	CandyCell *candy = CandyCell::create(index, CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_EXPLOSION);
	setCandyExplosionTime(candy, explosionTurns);

	if(getCurrentExplosionsNum()+1 >= explosionMax )
		currentExplosionSpawn = 0;
	
	return candy;
}


void CandyExplosions::createExplosionsWithMapData(void)
{
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		{
			for(int x=0; x<CANDY_MAP_WIDTH; x++)
				{
					if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXPLOSION))
						{
							CandyCell *explosion = createExplosion(cIndex(x, y));
							CandyManager::getInstance()->mapDataMgr->setCandyByIndex(explosion->index, explosion);
							CandyManager::getInstance()->candyLayer->addToCandyParent(explosion);
						}
				}
		}
}

bool CandyExplosions::isNeedToCreateNewExplosion(void)
{
	if(explosionMax == 0)
		return false;

	if(getCurrentExplosionsNum() >= explosionMax)
		return false;

	if(currentExplosionSpawn < explosionSpawn)
		return false;
	
	return true; 
}

int CandyExplosions::getCurrentExplosionsNum(void)
{
	int num = 0;
	
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	if(!candyArray)
		return 0;
	
	for(unsigned int i=0; i<candyArray->count(); i++)
		{
			CandyCell *candy = (CandyCell *)candyArray->objectAtIndex(i);
			if(candy->special == CANDY_SPECIAL_EXPLOSION)
				num ++;
		}
	return num;
}
