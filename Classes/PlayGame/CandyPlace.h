#ifndef CANDY_PLACE__H
#define CANDY_PLACE__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;

typedef struct
{
	CandyIndex entrance;
	CandyIndex exit;
}CandyPortalPlace;

class CandyPlace
{
	public:
		CandyPlace();
		~CandyPlace();

	public:
		void createPortalsLogo(CCPoint &pos, char *imgName);
		void createPortalsLogos(void);
		

	public:
		// 更新糖果位置
		void updateCandyPlace(void);

	public:
		void updateAvoidErrorPlace(void);
		
	private:
		int getMaxDownPos(CandyIndex index);
		int getMinUpPos(CandyIndex index);

	public:
		bool getCandyDropEnable(CandyIndex index, CandyIndex &dropIndex);
		void updateCandyDrop(void);

	private:
		CandyCell *getCandyOfProduce(CandyIndex index, int &dropFlag);
		int getMaxDownPosFromFactory(CandyIndex index);
		bool getDropRequireSituation(int x, int bottomY);
		void updateCandyProduce(void);

	private:
		bool getDropCandyBlcokExist(CandyIndex index);
		bool getSlideRequireSituation(CandyIndex &index);
		bool getCandySlideEnable(CandyCell *candy, int direction);
		void updateCandySlide(void);

	private://传送门
		CandyCell *getCandyOfPortal(CandyIndex index, int portal);
		void updateCandyPortals(void);
		
	public:
		void addCandyToDropArray(CandyCell *candy);
		void removeCandyFromDropArray(CandyCell *candy);
		
	public:
		static CandyPortalPlace portalPlace[18];
		static int portalNum;

	private:
		int dropCount[CANDY_MAP_WIDTH];
		
	private:
		CCArray *dropCandyArray;
		CCArray *moveCandyArray;
		CCArray *slideCandyArray;
		CCArray *deletingCandyArray;
};

#endif