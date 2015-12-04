#ifndef SHADER_SPRITE__H
#define SHADER_SPRITE__H

#include "cocos2d.h"
USING_NS_CC;

class ShaderSprite : public CCSprite
{
	public:
		static ShaderSprite* create(const char* pszFileName);

	public:
		virtual bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect);
		virtual void draw(void);
};

#endif