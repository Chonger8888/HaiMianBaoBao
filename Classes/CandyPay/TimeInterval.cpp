#include "TimeInterval.h"


void TimeInterval::AddNewTime()
{
	cc_timeval new_time;
	CCTime::gettimeofdayCocos2d(&new_time, NULL);
	if (time_vec_.size() > 1)
	{
		time_vec_.erase(time_vec_.begin());
	}

	time_vec_.insert(time_vec_.begin(), new_time);
}

bool TimeInterval::IsTimeFree(float second)
{
	bool b = false;
	if (time_vec_.size() < 2)
	{
		return true;
	}

	std::vector<cc_timeval>::iterator it = time_vec_.begin();
	double  interval = CCTime::timersubCocos2d(&*(it+1),&*(it));
	float interval_sec = interval/1000;
	CCLog("interval = %f ", interval_sec);
	if ( interval_sec > second)
	{
		b= true;
		std::vector<cc_timeval> copy_vec = time_vec_;
		time_vec_.clear();
		time_vec_.push_back(*copy_vec.begin());
	}

	return b;
}

float TimeInterval::GetInterval()
{
	std::vector<cc_timeval>::iterator it = time_vec_.begin();
	if (time_vec_.size()<2)
	{
		return 0;
	}
	
	double  interval = CCTime::timersubCocos2d(&*(it+1),&*(it));
	float interval_sec = interval/1000;
	return interval_sec;
}

void TimeInterval::ClearTime()
{
	time_vec_.clear();
}

