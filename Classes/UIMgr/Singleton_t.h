#pragma once

#include "stdlib.h"

/**
���ⵥ��ģ��
  �����ڼ̳���CCObject����
*/
template<class T>
class TSingleton
{
public:
	virtual ~TSingleton()
	{
		ms_pObject = NULL;
	}
    //get instance
    static T* GetInstance()
    {
		if ( !ms_pObject )
		{
			ms_pObject = new T;
			if (ms_pObject && ms_pObject->init())
			{
				ms_pObject->autorelease();
			}
			else
			{
				delete ms_pObject;
				ms_pObject = NULL;
			}
		}
        return ms_pObject;
    }

	//destroy
// 	static void Destroy()
// 	{
// 		if ( ms_pObject )
// 		{
// 			delete ms_pObject;
// 			ms_pObject = NULL;
// 		}
// 	}
protected:
    static T*	ms_pObject;
};

template<class T> 
T* TSingleton<T>::ms_pObject = NULL;
