#ifndef __TOASTDISPLAY_H__
#define __TOASTDISPLAY_H__

#include "cocos2d.h"
#include "cocos-ext.h"

// 提示显示时间
#define	TIPS_SHOW_FADE		0.2f
#define TIPS_SHOW_TIME		2.0f
// 背景边缘
#define TIPS_BG_OFFSET_Y	10.0f
#define TIPS_BG_OFFSET_W	5.0f
#define TIPS_BG_OFFSET_H	3.0f

class ToastDisplay : public cocos2d::CCLayer
{
public:

	ToastDisplay();
	~ToastDisplay();

public:

	virtual void onEnter();

	// 设置提示信息
	void	SetTips(std::string tips);
	void	VisibleToast(float t);
	void	ShowToasDisplay(float t);
	
	// 刷新提示信息
	void	RefreshTips(std::string tips);
	// 显示时间到
	void	HideForTimeout(float dt);

public:

	std::string						m_tips;

	cocos2d::CCLayerColor*			m_pLayerBG;
	cocos2d::CCLabelTTF*			m_pLabTips;

	bool							m_isShowing;
};

#endif