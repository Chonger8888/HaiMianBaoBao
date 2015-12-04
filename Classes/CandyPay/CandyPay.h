/********************************************************************
������:		2014/10/24  10:00	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\candy.mini.3.0.3.newMM\Classes\CommonData\CandyPay.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/10/24  10:00	

Ŀ  ��:		��װһ���µ�֧�����ܣ�����ɹ����󣬲��ȴ�ƽ̨�Ļص������·�����
*********************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"
#include "TimeInterval.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum Tipstype
{
	SUCCESS_TIPS,		//�ɹ���ʾ
	RECEIVE_TIPS,		//��ȡ��ʾ
};

/************************************************************************/
/* 
��֧����ص�һЩ���������ܣ��磺��ʾ
*/
/************************************************************************/
class PayHelper
{
public:
	/**
	@���ܣ�����ɹ���ʾ
	@��������
	@���أ���
	*/
	void BuySuccessTips(Tipstype tips = SUCCESS_TIPS);

	/**
	@���ܣ���׿��ʾ
	@������string����ʾ���ַ���
	@���أ���
	*/
	void AndroidPrompt(std::string text);
	void AndroidPrompt_Net(std::string text);
private:
	void FuncAfterTips( CCNode* node );

protected:
	std::string		m_orderId;			//���������ɵĶ����ţ�userdata��
	std::string		m_tradeId;			//ƽ̨���ɵĶ�����
	std::string		m_curPaycode;		//��ǰ������߶�Ӧ��paycode
	bool			m_isBuygift;		//�Ƿ���ĳ��������
	int				m_BuyPropId;		//��ǰ����ĵ��߶�Ӧ��id
	int				m_buyPricePoint;	//�Ʒѽ��
};

/************************************************************************/
/* 
sdk֧���࣬����
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
	@���ܣ�������������ɷ��������ɵĶ����ţ����Զ�������
	@������propid;��ǰ����ĵ���ID
	@���أ���
	*/
	void RequestCandyOrder(int propId);
	
	/**
	@���ܣ����ŷ��ͳɹ��������ӷ��������µ���,��JAVA����
	@������
	@���أ�
	*/
	void UpdateProp(char* tradeid,bool isWait = true);

	/**
	@���ܣ�����ʧ�ܣ�java����
	@��������
	@���أ���
	*/
	void CandyPayFailed();
private:

	

	/**
	@���ܣ�����֧��SDK����
	@��������
	@���أ���
	*/
	void ShowSDKBuyGUI();

	/**
	@���ܣ��ӷ�������ȡ������orderid�ص�
	@������1.sender��ִ�лص��Ķ���
			2.data�����緵�ص��ַ������ݣ��ɶ������json����
	@���أ���
	*/
	void CandyOrderCallback( CCNode* sender, void* data );

	/**
	@���ܣ����Ͷ��ųɹ��Ժ󣬴ӷ������������µ�����Ϣ
	@������1.sender��ִ�лص��Ķ���
			2.data�����緵�ص��ַ������ݣ��ɶ������json����
	@���أ���
	*/
	void UpdatePropCallback( CCNode* sender, void* data );

	//�������µ���
	void UpdatePropCallbackSingle();
	/**
	@���ܣ��洢�ӷ�������ȡ�Ķ�����orderid
	@������str���ӷ�������ȡ�Ķ������ַ���
	@���أ���
	*/
	void setOrderId(char* str);

	/**
	@���ܣ�cpp����java�ĺ�����������ʾ���Ͷ��Ž���
	@������1.paycode;��ǰ����ĵ��߶�Ӧ��paycode
			2.orderid;���������ɵĶ�����
	@���أ�
	*/
	void JniCallFunc(char* paycode,char* orederId ,int pricepoint, int buyNum = 1);
	
	/**
	@���ܣ�������������µ���δ�ܸ��µ��������ݣ����Ը���
	@��������
	@���أ���
	*/
	void RetryUpdate();

	/**
	@���ܣ�
	@������
	@���أ�
	*/
	void RetryFunc();

private:
	CandyPay();
	
	std::string		m_CurUpdateUrl;		//��ǰ���µ���url����������
	CCNode*			m_RetryNode;		//���Զ����ӿ�
	int				m_retryTimes;		//���Դ���
	bool			m_isFinished;		//��ǰ֧�������Ƿ����
};