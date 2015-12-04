#include "CandyBgGrid.h"
#include "CandyManager.h"

#define CROSS_GRID_WIDTH	12
#define CROSS_GRID_HEIGHT	12
#define GRID_CELL_WIDTH		38
#define GRID_CELL_HEIGHT	38

#define CROSS_GRID_IMG		"Image/CandyGame/Candy/game_grid6.png"	


static unsigned int crossGridData[CROSS_GRID_HEIGHT][CROSS_GRID_WIDTH]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,	
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,0,0,0,0,0,	
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,
};

CandyBgGrid::CandyBgGrid()
{

}

CandyBgGrid::~CandyBgGrid()
{
	
}
		
unsigned int CandyBgGrid::getCrossGridData(CandyIndex index)
{
	if(index.x <0 || index.x>=CROSS_GRID_WIDTH|| index.y<0 || index.y>=CROSS_GRID_HEIGHT)
		return 0;
	
	return crossGridData[index.y][index.x];
}

bool CandyBgGrid::getCrossGridIndex(CandyIndex &index)
{
	for(int h=0; h<CROSS_GRID_HEIGHT; h++)
		for(int w=0; w<CROSS_GRID_WIDTH; w++)
			if(getCrossGridData(cIndex(w-1,h))==left
					&& getCrossGridData(cIndex(w+1,h))==right
					&& getCrossGridData(cIndex(w,h-1))==up
					&& getCrossGridData(cIndex(w,h+1))==down
					&& getCrossGridData(cIndex(w-1,h-1))==leftUp
					&& getCrossGridData(cIndex(w-1,h+1))==leftDown
					&& getCrossGridData(cIndex(w+1,h-1))==rightUp
					&& getCrossGridData(cIndex(w+1,h+1))==rightDown )
				{
					index = cIndex(w,h);
					return true;
				}
	return false;
}

void CandyBgGrid::createNormalGridCellVisit(CandyIndex index)
{
	//获取十字架最中间的格子
	CCSprite *sprite = CCSprite::create(CROSS_GRID_IMG, CCRectMake(	((CROSS_GRID_WIDTH -2)>>1)*GRID_CELL_WIDTH,
																((CROSS_GRID_HEIGHT -2)>>1)*GRID_CELL_HEIGHT,
																GRID_CELL_WIDTH<<1, 
																GRID_CELL_HEIGHT<<1 ));
	if(!sprite)
		return;
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index) ;
	sprite->setAnchorPoint(ccp(0,0));
	sprite->setPosition(ccp(pos.x - GRID_CELL_WIDTH +gridOffsetX,  pos.y - GRID_CELL_HEIGHT+gridOffsetY) );
	sprite->visit();
}

void CandyBgGrid::createEmptyEdgeGridCellVisit(CandyIndex index, bool leftup, bool leftdown, bool rightup, bool rightdown)
{
	//根据小格子的位置调整锚点
	CCPoint anchor = ccp(0.5,0.5);
	
	this->up 			= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, index.y-1), MAP_CELL_EXIST);
	this->down 		= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x, index.y+1), MAP_CELL_EXIST);
	this->left 		= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x-1, index.y), MAP_CELL_EXIST);
	this->right 		= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x+1, index.y), MAP_CELL_EXIST);
	this->leftUp		= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x-1, index.y-1), MAP_CELL_EXIST);
	this->leftDown	= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x-1, index.y+1), MAP_CELL_EXIST);
	this->rightUp		= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x+1, index.y-1), MAP_CELL_EXIST);
	this->rightDown	= 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(index.x+1, index.y+1), MAP_CELL_EXIST);

	if(leftup)
		{
			rightUp 		= 	up;
			right 		= 	0;
			leftDown 		= 	left;
			down 		= 	0;
			rightDown 	= 	0;

			if(left && up)
				leftUp = 1;
			
			anchor = ccp(1,0);
		}
	else if(leftdown)
		{
			leftUp 		= 	left;
			up 			= 	0;
			rightUp 		=	0;
			right			=	0;
			rightDown 	= 	down;
			
			if(left && down)
				leftDown = 1;
			
			anchor = ccp(1,1);
		}
	else if(rightup)
		{
			leftUp 		= 	up;
			left 			= 	0;
			leftDown 		= 	0;
			down 		= 	0;
			rightDown 	= 	right;

			if(right && up)
				rightUp = 1;
			
			anchor = ccp(0,0);
		}
	else if(rightdown)
		{
			leftUp 		= 	0;
			up 			= 	0;
			rightUp 		= 	right;
			left 			= 	0;
			leftDown 		= 	down;

			if(right && down)
				rightDown = 1;
			
			anchor = ccp(0,1);
		}

	if(!up && !down && !left && !right && !leftUp && !leftDown && !rightUp && !rightDown)
		return;


	CandyIndex crossIndex;
	if( getCrossGridIndex( crossIndex) )
		{
			
			CCSprite *sprite = CCSprite::create(CROSS_GRID_IMG, CCRectMake(crossIndex.x*GRID_CELL_WIDTH, crossIndex.y*GRID_CELL_HEIGHT, 
																		GRID_CELL_WIDTH, GRID_CELL_HEIGHT));
			if(!sprite)
				return;
			CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
			pos = ccpAdd(pos, ccp(gridOffsetX, gridOffsetY));
			sprite->setAnchorPoint(anchor);
			sprite->setPosition( pos );
			sprite->visit();
		}
}

void CandyBgGrid::createGridsVisit(float offsetX , float offsetY )
{
	gridOffsetX = offsetX;
	gridOffsetY = offsetY;
	
	for(int h=-1; h<CANDY_MAP_HEIGH+1; h++)
		for(int w=-1; w<CANDY_MAP_WIDTH+1; w++)
			{
				if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(w, h), MAP_CELL_EXIST))
					{
						createNormalGridCellVisit(cIndex(w, h));
					}
				else
					{
						createEmptyEdgeGridCellVisit(cIndex(w, h), 1, 0, 0 ,0);
						createEmptyEdgeGridCellVisit(cIndex(w, h), 0, 1, 0 ,0);
						createEmptyEdgeGridCellVisit(cIndex(w, h), 0, 0, 1 ,0);
						createEmptyEdgeGridCellVisit(cIndex(w, h), 0, 0, 0 ,1);
					}
			}
}

void CandyBgGrid::createBgGrid(void)
{	
	removeBgGrid();
	CCPoint leftUpPos = CandyManager::getInstance()->shareMgr->leftUpPos;
	leftUpPos.y = leftUpPos.y -TARGET_SCREEN_WIDTH + 18;// 18 =( TARGET_SCREEN_WIDTH - GRID_CELL_WIDTH*2 *9)/2
	
	CCRenderTexture* texture = CCRenderTexture::create(TARGET_SCREEN_WIDTH, TARGET_SCREEN_WIDTH);
	texture->begin();
	createGridsVisit(0,-leftUpPos.y);
	texture->end();
	
	CCSprite* ret = CCSprite::createWithTexture(texture->getSprite()->getTexture());
	ret->setFlipY(true);
	ret->setAnchorPoint(ccp(0.0,0.0));
	ret->setPosition(ccp(0,leftUpPos.y));
	CandyManager::getInstance()->candyLayer->addChild(ret,BG_GRID_ORDER,BG_GRID_TAG);
}

void CandyBgGrid::removeBgGrid(void)
{
	CandyManager::getInstance()->candyLayer->removeChildByTag(BG_GRID_TAG);
}
