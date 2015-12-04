#include "Counter.h"
USING_NS_CC;

enum{
    k_Counter_Action = 0
};
Counter::Counter()
{
    _digit = 0;
}
Counter* Counter::create(CCArray* presenters, int digit)
{
    Counter* counter = new Counter();
    counter->init(presenters, digit);
    counter->autorelease();
    return counter;
}
bool Counter::init(CCArray* presenters, int digit)
{
    _presenters = CCNode::create();
	int size = presenters->count();
    for (int i = 0; i < size; i++) {
        CCNode* node = (CCNode*)presenters->objectAtIndex(i);
		int cordi_y = i * 250;
        node->setPosition(CCPointMake(0, cordi_y));
        _presenters->addChild(node, 0, i);
    }
    this->addChild(_presenters);
    return true;
}
void Counter::setDigit(int digit)
{
    if(_digit != digit){
        _digit = digit;
        animation(digit);
    }
}
int Counter::getDigit()
{
    return _digit;
}
void Counter::animation(int digit)
{
	CCNode* presenter = _presenters->getChildByTag(digit);
	CCPoint dest = presenter->getPosition();
	this->stopAllActions();
	CCMoveTo* moveTo = CCMoveTo::create(7.0f, CCPointMake(0, -dest.y));
	CCActionInterval*  act = CCEaseInOut::create(moveTo, 2.0f);
	_presenters->runAction(act);
}
 void Counter::visit()
 {
	 glEnable(GL_SCISSOR_TEST);
	 CCNode* presenter = _presenters->getChildByTag(0);
	 CCSize size = presenter->getContentSize();

	 float   scaleX = CCEGLView::sharedOpenGLView()->getScaleX();
	 float   scaleY = CCEGLView::sharedOpenGLView()->getScaleY();
	 CCRect   viewPortRect =  CCEGLView::sharedOpenGLView()->getViewPortRect();
	 CCPoint location = this->getParent()->convertToWorldSpace(CCPointMake(this->getPosition().x, this->getPosition().y));

	 glScissor(location.x*scaleX + viewPortRect.origin.x - size.width*0.5*scaleX , location.y*scaleY + viewPortRect.origin.y -130*scaleY, size.width*scaleX, 260*scaleY);
	 CCNode::visit();
	 glDisable(GL_SCISSOR_TEST);
 }
