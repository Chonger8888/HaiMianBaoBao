/********************************************************************
创建于:		2014/10/24  10:00	
文件名: 	E:\cocos2d-x-2.2.0\projects\candy.mini.3.0.3.newMM\Classes\CommonData\CandyPay.h 
作  者:		彭志宏(alex)
修改于：	2014/10/24  10:00	

目  的:		封装一个新的支付功能：购买成功立后，不等待平台的回调，先下发道具
*********************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"
#include "TimeInterval.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum Tipstype
{
	SUCCESS_TIPS,		//成功提示
	RECEIVE_TIPS,		//领取提示
};

/************************************************************************/
/* 
与支付相关的一些弱关联功能，如：提示
*/
/************************************************************************/
class PayHelper
{
public:
	/**
	@功能：购买成功提示
	@参数：无
	@返回：无
	*/
	void BuySuccessTips(Tipstype tips = SUCCESS_TIPS);

	/**
	@功能：安卓提示
	@参数：string，提示的字符串
	@返回：无
	*/
	void AndroidPrompt(std::string text);
	void AndroidPrompt_Net(std::string text);
private:
	void FuncAfterTips( CCNode* node );

protected:
	std::string		m_orderId;			//服务器生成的订单号（userdata）
	std::string		m_tradeId;			//平台生成的订单号
	std::string		m_curPaycode;		//当前购买道具对应的paycode
	bool			m_isBuygift;		//是否购买的超级大礼包
	int				m_BuyPropId;		//当前购买的道具对应的id
	int				m_buyPricePoint;	//计费金额
};

/************************************************************************/
/* 
sdk支付类，单例
*/
/************************************************************************/

class CandyPay : public CCObject, public PayHelper, public TimeInterval
{
public:
	~CandyPay();
	static CandyPay* getInstance()
	{
		static CandyPay instance;
		return &instance;
	}

	/**
	@功能：向服务器请求由服务器生成的订单号，即自定义数据
	@参数：propid;当前购买的道具ID
	@返回：无
	*/
	void RequestCandyOrder(int propId);
	
	/**
	@功能：短信发送成功，立即从服务器更新道具,由JAVA调用
	@参数：
	@返回：
	*/
	void UpdateProp(char* tradeid,bool isWait = true);

	/**
	@功能：购买失败，java调用
	@参数：无
	@返回：无
	*/
	void CandyPayFailed();
private:

	

	/**
	@功能：调出支付SDK界面
	@参数：无
	@返回：无
	*/
	void ShowSDKBuyGUI();

	/**
	@功能：从服务器获取订单号orderid回调
	@参数：1.sender；执行回调的对象
			2.data；网络返回的字符串数据，可对其进行json解析
	@返回：无
	*/
	void CandyOrderCallback( CCNode* sender, void* data );

	/**
	@功能：发送短信成功以后，从服务器更新最新道具信息
	@参数：1.sender；执行回调的对象
			2.data；网络返回的字符串数据，可对其进行json解析
	@返回：无
	*/
	void UpdatePropCallback( CCNode* sender, void* data );

	//单机更新道具
	void UpdatePropCallbackSingle();
	/**
	@功能：存储从服务器获取的订单号orderid
	@参数：str；从服务器获取的订单号字符窜
	@返回：无
	*/
	void setOrderId(char* str);

	/**
	@功能：cpp调用java的函数，让其显示发送短信界面
	@参数：1.paycode;当前都买的道具对应的paycode
			2.orderid;服务器生成的订单号
	@返回：
	*/
	void JniCallFunc(char* paycode,char* orederId ,int pricepoint, int buyNum = 1);
	
	/**
	@功能：在网络差的情况下导致未能更新到道具数据，重试更新
	@参数：无
	@返回：无
	*/
	void RetryUpdate();

	/**
	@功能：
	@参数：
	@返回：
	*/
	void RetryFunc();

private:
	CandyPay();
	
	std::string		m_CurUpdateUrl;		//当前更新道具url，用于重试
	CCNode*			m_RetryNode;		//重试动作接口
	int				m_retryTimes;		//重试次数
	bool			m_isFinished;		//当前支付流程是否完成
};