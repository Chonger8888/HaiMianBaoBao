/********************************************************************
������:		2014/11/03  15:00	
�ļ���: 	E:\cocos2d-x-2.2.0\projects\mini.crush\Classes\CandyPay\TimeInterval.h 
��  ��:		��־��(alex)
�޸��ڣ�	2014/11/03  15:00	

Ŀ  ��:		����ʱ����
*********************************************************************/

#ifndef _TIME_INTERVAL_H_
#define _TIME_INTERVAL_H_

#include "cocos2d.h"
#include "time.h"

USING_NS_CC;


class TimeInterval
{
public:
	void AddNewTime();
	bool IsTimeFree(float second);
	float GetInterval();
	void ClearTime();
private:
	std::vector<cc_timeval>	 time_vec_;

};




#endif