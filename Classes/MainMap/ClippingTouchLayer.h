/********************************************************************
创建于:		2014/10/22  10:24	
文件名: 	E:\cocos2d-x-2.2.0\samples\Cpp\HelloCpp\Classes\ClippingTouchLayer.h 
作  者:		彭志宏(alex)
修改于：	2014/10/22  10:24	

目  的:		创建一个层，在层上加上一些ClippingNode的镂空区域；只有当点击在这些镂空区域的时候才能
			触发点击事件
*********************************************************************/

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef struct 
{
	CCPoint		centerPos;
	float		radius;
}TouchArea;

class PointerFinger
{
public:
	void addFinger(CCNode* node, const CCPoint& pos);
	CCPoint FixPoint(const CCPoint& pos);
};

class ClippingAreaTouchableLayer : public CCLayer, public PointerFinger
{
public:
	CREATE_FUNC(ClippingAreaTouchableLayer);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void addTouchArea(const TouchArea& area);
	void noticeCallback(CCObject* sender);

private:
	bool containsTouchLocation( CCTouch* pTouch ,const CCRect& rect);
	void createTouchableArea();

	CCDrawNode* getShape();

private:
	std::vector<TouchArea>		m_AreaVec;
	std::vector<CCRect>			m_RectVec;
};