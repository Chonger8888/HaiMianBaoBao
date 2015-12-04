#ifndef CANDY_NEW_PORTAL__H
#define CANDY_NEW_PORTAL__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

typedef struct
{
	CandyIndex place[2];
}CandyNewPortalPlace;

class CandyNewPortal
{
	public:
		CandyNewPortal();
		~CandyNewPortal();

	public:
		void createNewPortalsLogo(void);

	public:
		void updateCandyNewPortal(void);

	public:
		void checkCandyMoveNewPortal(CandyIndex first, CandyIndex second);

	private:
		bool getPortalTargetIndex(CandyIndex origin, CandyIndex &target);
		
	public:
		static CandyNewPortalPlace newPortalPlace[18];
		static int newPortalNum;
};

#endif