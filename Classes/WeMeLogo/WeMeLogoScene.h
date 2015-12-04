#ifndef WEME_LOGO_SCENE__H
#define WEME_LOGO_SCENE__H

#include "cocos2d.h"

USING_NS_CC;


class WeMeLogo: public CCLayer
{
	public:
   		CREATE_FUNC(WeMeLogo);
		
	public:
    		static CCScene* scene(void);
			
	public:
		virtual bool init(void); 

	public:
		void goMainMenu(float dt);
};


#endif
