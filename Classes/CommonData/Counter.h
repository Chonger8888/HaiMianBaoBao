#ifndef COUNT__H
#define COUNT__H

#include "cocos2d.h"
class Counter : public cocos2d::CCNode
{
public:
    Counter();

    static Counter* create(cocos2d::CCArray* presenters, int digit = 0);
    bool init(cocos2d::CCArray* presenters, int digit = 0);
    
    CC_PROPERTY(int, _digit, Digit);
public:
    void visit();
    cocos2d::CCNode* _presenters;
    void animation(int digit);
};

#endif


















