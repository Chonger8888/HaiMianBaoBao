#ifndef CPP_CALL_JAVA__H
#define CPP_CALL_JAVA__H

#include "cocos2d.h"
#include "string.h"
USING_NS_CC;

class CppCallJava
{
public:

	//************************************
	// Method:    getPlatfromInfo
	// FullName:  CppCallJava::getPlatfromInfo
	// Access:    public 
	// Returns:   void
	// Explain:　登录前必须获取
	// Parameter: void
	//************************************
	static void getPlatfromInfo(void);

	static void verifyLuas(int userid, int maxlevel);
	static bool logOut(void);
	static char* getCandyPicDir(void);
	static void loadNoCandyUserInfo(const char* jsondata);
	static void toPay(const char* subject, const char* num, const char* body, const char* fee, const char* nickname);
	static void patchTracker(const char* data);
	static void showFeedbackDialog(void);
	static void toBuyProp(int buytype, int num, int preciousid = 0);
	static void getChitNickName(void);
	static void initChat(int userid, int chatstate, const char* nickname);
	static void deleteUserImage();

	//购买超级大礼包
	static void BuySuperGift();

	//　分享接口
	static void ShareToqzone(const char* path);
	static bool isNetworkOk(void);
	static bool toSystemSet(void);
	static void sendRegeditOrLogin(int isRegedit, int userid);

	static void BuyProduct(int productId);

	static long getUserId( void );




};

#endif