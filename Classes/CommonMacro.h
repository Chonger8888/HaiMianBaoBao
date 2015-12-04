#ifndef COMMON_MACRO__H
#define COMMON_MACRO__H

#define DEMO_FOR_NEW_UI


//　记录点
#define CANDY_STATISITICAL_DATA

/*********发布版本控制 start*******************/
//#define CANDY_VERSIONS_FOR_SINGLE		//单机

//#define DEMO_FOR_TELECOM		

//#define DEMO_FOR_WEME_TESTER	

#define DEMO_FOR_GUEST					//游客主线版本

//#define DEMO_FOR_INTERFLOW			//社交主线版本

//#define DEMO_FOR_MOBILE				//移动版本    //svn://192.168.1.209/weme_game/candy.crush.guest.cmcc




/************************** 小版本号**********************/

//　区分不同服务器　　如MM　如 PT
#if defined( DEMO_FOR_GUEST )

//#define CANDY_GUEST_FOR_MM

//#define CANDY_GUEST_FOR_PT

//#define CANDY_GUEST_FOR_XIAOMI		// 小米

#endif


// 区分计费方式　　如　短信　
#if defined( DEMO_FOR_GUEST )

#define CANDY_GUEST_FEE_FOR_SMS			// SMS支付方式

#endif

/****************END****************************/

/*********发布版本控制 end*******************/

#if defined ( CANDY_GUEST_FOR_MM)

#define	 CANDY_CURRENT_VERSIONS		"2.0.6.guest.cmcc" 

#elif defined ( CANDY_GUEST_FOR_PT )

#define	 CANDY_CURRENT_VERSIONS		"1.0.0.guest.pt" 

#else

#define	 CANDY_CURRENT_VERSIONS		"1.0.0.guest.mini.stand.alone" 
//	2.0.0.guest
//	2.0.1.guest
//  2.0.2.guest
//	2.0.3.guest
//	2.0.4.guest
//	2.0.5.guest
//	2.0.7.guest 
//	2.0.8.guest 
//	3.0.0.guest 
//	3.0.1.guest 
//"3.0.2.guest.mini" 

#endif


#if defined( DEMO_FOR_GUEST )||defined( CANDY_VERSIONS_FOR_SINGLE)

#if defined( CANDY_GUEST_FOR_MM )

#define CANDY_PHP_ADD				"http://cmcc.guest.candy.weme-game.com/%s/dispatch.php?"

#else

#define CANDY_PHP_ADD				"http://guest.candy.weme-game.com/%s/dispatch.php?"

#endif

#elif defined( DEMO_FOR_MOBILE )

#define CANDY_PHP_ADD				"http://cmcc.guest.candy.weme-game.com/1.0.0.guest.cmcc/dispatch.php?"

#elif defined ( DEMO_FOR_INTERFLOW )
#define CANDY_PHP_ADD				"http://www.weme-game.com/%s/dispatch.php?"

#endif


#define	LILE_MIN_NUM	0		// 生命值最小个数

#if defined(DEMO_FOR_MOBILE)|| defined(DEMO_FOR_GUEST)|| defined(CANDY_VERSIONS_FOR_SINGLE) 

//#define TEST_FOR_MOBILE			// 关卡全开测试

#define MOBILE_GOURD_LIFENUM		5

#define MOBILE_MONEY5_BUY_LIFENUM	1		// 一笔订单  5元5个
#define MOBILE_MONEY5_BUY_PROPNUM	1
#define MOBILE_MONEY8_BUY_PROPNUM	1

#define MOBILE_GOURD_LIFENUM		5

#define MOBILE_MONEY5_FOR_PROP		5
#define MOBILE_MONEY8_FOR_PROP		8

typedef enum
{
	CANDY_BUYGEM_NUM_10				= 1,
	CANDY_BUYGEM_NUM_20				,//= 2,
	CANDY_BUYGEM_NUM_30				,//= 3,
	CANDY_BUYGEM_NUM_50				,//= 5,
	CANDY_BUYGEM_NUM_60				,//= 6
	CANDY_BUYGEM_NUM_80				,//= 8,
	CANDY_BUYGEM_NUM_100			,//= 10,
	CANDY_BUYGEM_NUM_200			,//= 20,
	CANDY_BUYGEM_NUM_320			,//= 30,
	CANDY_BUYGEM_NUM_588			,//= 50,
	CANDY_BUYGEM_NUM_1288			,//= 100,
	CANDY_BUYGEM_NUM_2588			,//= 200,
	CANDY_BUY_GIFTBIG_NUM_8			,//= 8,
	CANDY_BUY_GIFTBIG_NUM_18		,//= 18,
	CANDY_BUY_GIFTBIG_NUM_28		//= 28
}CANDY_BUYGEM_NUM_TYPE;




// 　remove
#define	MOBILE_PROP1_ID							"30000816809503"   //增加五条生命			购买类-可重复购买   5元         
#define	MOBILE_PROP2_ID							"30000816809501"   //5元加三步帮助特效		购买类-可重复购买   5元         
#define	MOBILE_PROP3_ID							"30000816809502"   //5元条纹帮助特效		购买类-可重复购买   5元         
#define	MOBILE_PROP4_ID							"30000816809504"   //5元炸弹帮助特效		购买类-可重复购买   5元         
#define	MOBILE_PROP5_ID							"30000816809505"   //8元加五步特效帮助特效  购买类-可重复购买   8元         
#define	MOBILE_PROP6_ID							"30000816809506"   //8元条纹特效帮助		购买类-可重复购买   8元    
#define	MOBILE_PROP7_ID							"30000816809507"   //8元炸弹特效帮助特效    购买类-可重复购买   8元    
#define	MOBILE_PROP8_ID							"30000816809508"  	//充满糖果罐一  		购买类-可重复购买  	10元  	  	 
#define	MOBILE_PROP9_ID							"30000816809509"	//充满糖果罐二  		购买类-可重复购买  	20元  	  	 
#define	MOBILE_PROP10_ID						"30000816809510"	//充满糖果罐三  		购买类-可重复购买  	30元  


#if defined( CANDY_GUEST_FOR_MM )
// for MM free
#define APPID_FORCMCC							"300008040467"
#define APPKEY_FORCMCC							"6E2882557878DB8C" 

#define CMCC_BUYGEM_1_TO_10_ID					"30000804046711"	// 	10个宝石	1元
#define CMCC_BUYGEM_2_TO_20_ID					"30000804046712"	// 	20个宝石	2元
#define CMCC_BUYGEM_3_TO_30_ID					"30000804046713"	// 	30个宝石	3元
#define CMCC_BUYGEM_5_TO_50_ID					"30000804046714"	// 	50个宝石	5元
#define CMCC_BUYGEM_8_TO_80_ID					"30000804046715"	// 	80个宝石	8元
#define CMCC_BUYGEM_10_TO_100_ID				"30000804046716"	// 	100个宝石	10元
#define CMCC_BUYGEM_20_TO_200_ID				"30000804046717"	// 	200个宝石	20元
#define CMCC_BUYGEM_30_TO_320_ID				"30000804046718"	// 	320个宝石	30元

#elif defined( CANDY_GUEST_FOR_PT )

#define CMCC_BUYGEM_1_TO_10_ID					"10000011"	// 	10个宝石	1元
#define CMCC_BUYGEM_2_TO_20_ID					"10000012"	// 	20个宝石	2元
#define CMCC_BUYGEM_3_TO_30_ID					"10000013"	// 	30个宝石	3元
#define CMCC_BUYGEM_5_TO_50_ID					"10000014"	// 	50个宝石	5元
#define CMCC_BUYGEM_8_TO_80_ID					"10000015"	// 	80个宝石	8元
#define CMCC_BUYGEM_10_TO_100_ID				"10000016"	// 	100个宝石	10元
#define CMCC_BUYGEM_20_TO_200_ID				"10000017"	// 	200个宝石	20元
#define CMCC_BUYGEM_30_TO_320_ID				"10000018"	// 	320个宝石	30元


#elif defined( CANDY_GUEST_FOR_XIAOMI )

// for xiaomi
#define APPID_FORCMCC							"2882303761517172015"
#define APPKEY_FORCMCC							"5671717242015" 



#define CMCC_BUYGEM_1_TO_10_ID					"xm.migc_30000816809519"	// 	10个宝石	1元
#define CMCC_BUYGEM_2_TO_20_ID					"xm.migc_30000816809520"	// 	20个宝石	2元
#define CMCC_BUYGEM_3_TO_30_ID					"xm.migc_30000816809521"	// 	30个宝石	3元
#define CMCC_BUYGEM_5_TO_50_ID					"xm.migc_30000816809522"	// 	50个宝石	5元
#define CMCC_BUYGEM_8_TO_80_ID					"xm.migc_30000816809527"	// 	80个宝石	8元
#define CMCC_BUYGEM_10_TO_100_ID				"xm.migc_30000816809524"	// 	100个宝石	10元
#define CMCC_BUYGEM_20_TO_200_ID				"xm.migc_30000816809525"	// 	200个宝石	20元
#define CMCC_BUYGEM_30_TO_320_ID				"xm.migc_30000816809526"	// 	320个宝石	30元

#define CMCC_BUY_GIFTBIG_8_ID					"xm.migc_30000816809528"	// 	新手大礼包	在大礼包的购买界面点击确定即可购买	开始游戏会弹出大礼包的购买界面,玩家确认之后即可购买	8元	短信类-可重复购买
#define CMCC_BUY_GIFTBIG_18_ID					"xm.migc_30000816809529"	// 	进阶大礼包	在进阶大礼包的购买界面确认之后即可购买	开始游戏会弹出进阶大礼包的购买界面,确认之后即可购买	18元	短信类-可重复购买
#define CMCC_BUY_GIFTBIG_28_ID					"xm.migc_30000816809530"	// 	高端大礼包	在高端大礼包的购买界面确认之后即可购买	开始游戏会弹出高端大礼包的购买界面,玩家确认之后即可完成购买	28元	短信类-可重复购买


#else 

// for cmcc fee
#define APPID_FORCMCC							"300008510789"
#define APPKEY_FORCMCC							"29A2E679AE6CD1E0" 


#if defined ( CANDY_GUEST_FEE_FOR_SMS )

#define CMCC_BUYGEM_1_TO_10_ID					"30000816809519"  	// 	10个宝石  	短信类-可重复购买  	1元  	  	 
#define CMCC_BUYGEM_2_TO_20_ID					"30000816809520"  	// 	20个宝石  	短信类-可重复购买  	2元  	  	 
#define CMCC_BUYGEM_3_TO_30_ID					"30000816809521"  	// 	30个宝石  	短信类-可重复购买  	3元  	  	 
#define CMCC_BUYGEM_5_TO_50_ID					"30000816809522"  	// 	50个宝石  	短信类-可重复购买  	5元
#define CMCC_BUYGEM_8_TO_80_ID					"30000816809527"  	// 	80个宝石  	短信类-可重复购买  8元  	  	 
#define CMCC_BUYGEM_10_TO_100_ID				"30000816809524"  	// 	100个宝石  	短信类-可重复购买  	10元  	  	 
#define CMCC_BUYGEM_20_TO_200_ID				"30000816809525"  	// 	200个宝石  	短信类-可重复购买  	20元  	  	 
#define CMCC_BUYGEM_30_TO_320_ID				"30000816809526"  	// 	320个宝石  	短信类-可重复购买  	30元  	 




//MINI版本计费点
#define CMCC_MINI_PROP_5LIFE					"30000851078901"	//生命 	短信类-可重复购买 	5元 
#define CMCC_MINI_PROP_RESORT					"30000851078902"	//刷新 	短信类-可重复购买 	6元 
#define CMCC_MINI_PROP_HAMER					"30000851078903"	//糖果锤 	短信类-可重复购买 	6元 
#define CMCC_MINI_PROP_SWAP						"30000851078904"	//互换 	短信类-可重复购买 	6元 
#define CMCC_MINI_PROP_COLORFULL				"30000851078905"	//彩糖炸弹 	短信类-可重复购买 	6元 
#define CMCC_MINI_PROP_BOMBNEW					"30000851078906"	//包装炸弹 	短信类-可重复购买 	6元 
#define CMCC_MINI_PROP_STEP5					"30000851078907"	//加5步 	短信类-可重复购买 	8元 
#define CMCC_BUY_GIFTBIG_8_ID					"30000851078908"	//新手礼包 	短信类-不可重复购买 	10元 
#define CMCC_BUY_GIFTBIG_18_ID					"30000851078909"	//进阶礼包 	短信类-不可重复购买 	10元 
#define CMCC_BUY_GIFTBIG_28_ID					"30000851078910"	//高端礼包 	短信类-不可重复购买 	10元 
#define CMCC_MINI_PROP_SUPERGIFT				"30000851078911"	//超级大礼包    短信类-不可重复购买   20元    

#else

#define CMCC_BUYGEM_1_TO_10_ID					"30000816809511"        // 	10个宝石 	购买类-可重复购买 	1元      
#define CMCC_BUYGEM_2_TO_20_ID					"30000816809512"		// 	20个宝石 	购买类-可重复购买 	2元 
#define CMCC_BUYGEM_3_TO_30_ID					"30000816809513"		// 	30个宝石 	购买类-可重复购买 	3元 
#define CMCC_BUYGEM_5_TO_50_ID					"30000816809514"		// 	50个宝石 	购买类-可重复购买 	5元 
#define CMCC_BUYGEM_8_TO_80_ID					"30000816809515"		// 	80个宝石 	购买类-可重复购买 	8元 
#define CMCC_BUYGEM_10_TO_100_ID				"30000816809516"		// 	100个宝石 	购买类-可重复购买 	10元 
#define CMCC_BUYGEM_20_TO_200_ID				"30000816809517"		// 	200个宝石 	购买类-可重复购买 	20元 
#define CMCC_BUYGEM_30_TO_320_ID				"30000816809518"		// 	320个宝石 	购买类-可重复购买 	30元 

#endif
#endif

// for unicom free
#define APPID_FORUNICOM							"906114919620140305154342045400"
#define APPKEY_FORUNICPCODE						"9061149196"
#define APPKEY_FORUNICPID						"86007189"


#define UNICOM_BUYGEM_1_TO_10_ID				"140327030420"      // 	10个宝石 	购买类-可重复购买 	1元      
#define UNICOM_BUYGEM_2_TO_20_ID				"140327030421"		// 	20个宝石 	购买类-可重复购买 	2元 
#define UNICOM_BUYGEM_3_TO_30_ID				"140327030422"		// 	30个宝石 	购买类-可重复购买 	3元 
#define UNICOM_BUYGEM_5_TO_50_ID				"140327030423"		// 	50个宝石 	购买类-可重复购买 	5元 
#define UNICOM_BUYGEM_8_TO_80_ID				"140327030424"		// 	80个宝石 	购买类-可重复购买 	8元 
#define UNICOM_BUYGEM_10_TO_100_ID				"140327030425"		// 	100个宝石 	购买类-可重复购买 	10元 
#define UNICOM_BUYGEM_20_TO_200_ID				"140327030426"		// 	200个宝石 	购买类-可重复购买 	20元 
#define UNICOM_BUYGEM_30_TO_320_ID				"140327030427"		// 	320个宝石 	购买类-可重复购买 	30元 


#define UNICOM_BUY_GIFTBIG_8_ID					"140717045697"	// 	新手大礼包	在大礼包的购买界面点击确定即可购买	开始游戏会弹出大礼包的购买界面,玩家确认之后即可购买	8元	短信类-可重复购买
#define UNICOM_BUY_GIFTBIG_18_ID				"140717045698"	// 	进阶大礼包	在进阶大礼包的购买界面确认之后即可购买	开始游戏会弹出进阶大礼包的购买界面,确认之后即可购买	18元	短信类-可重复购买
#define UNICOM_BUY_GIFTBIG_28_ID				"140717045699"	// 	高端大礼包	在高端大礼包的购买界面确认之后即可购买	开始游戏会弹出高端大礼包的购买界面,玩家确认之后即可完成购买	28元	短信类-可重复购买


#define ALIPAY_BUYGEM_10_ID						"20000004"			// 	10个宝石 	购买类-可重复购买 	1元   20000004
#define ALIPAY_BUYGEM_20_ID						"20000005"			// 	20个宝石 	购买类-可重复购买 	2元   20000005
#define ALIPAY_BUYGEM_30_ID						"20000006"			// 	30个宝石 	购买类-可重复购买 	3元   20000006
#define ALIPAY_BUYGEM_50_ID						"20000007"			// 	50个宝石 	购买类-可重复购买 	5元   20000007
#define ALIPAY_BUYGEM_80_ID						"20000008"			// 	80个宝石 	购买类-可重复购买 	8元   20000008
#define ALIPAY_BUYGEM_100_ID					"20000009"			// 	100个宝石 	购买类-可重复购买 	10元  20000009
#define ALIPAY_BUYGEM_200_ID					"20000010"			// 	200个宝石 	购买类-可重复购买 	20元  20000010
#define ALIPAY_BUYGEM_320_ID					"20000011"			// 	320个宝石 	购买类-可重复购买 	30元  20000011
#define ALIPAY_BUYGEM_588_ID					"20000001"			//　大面额
#define ALIPAY_BUYGEM_1288_ID					"20000002"
#define ALIPAY_BUYGEM_2588_ID					"20000003"


#define UNICOM_OTHE_BUYGEM_1_TO_10_ID			"1"
#define UNICOM_OTHE_BUYGEM_2_TO_20_ID			"1"
#define UNICOM_OTHE_BUYGEM_3_TO_30_ID			"1"
#define UNICOM_OTHE_BUYGEM_5_TO_50_ID			"1"
#define UNICOM_OTHE_BUYGEM_8_TO_80_ID			"1"
#define UNICOM_OTHE_BUYGEM_10_TO_100_ID			"1"
#define UNICOM_OTHE_BUYGEM_20_TO_200_ID			"1"
#define UNICOM_OTHE_BUYGEM_30_TO_320_ID			"1"
#define UNICOM_OTHE_BUYGEM_588_ID				""
#define UNICOM_OTHE_BUYGEM_1288_ID				""
#define UNICOM_OTHE_BUYGEM_2588_ID				""


// 支付宝
#define ALIPAY_DEFAULT_PARTNER					"2088111839722914"
//商户帐号
#define ALIPAY_DEFAULT_SELLER					"wemegame@wemepower.com"
//商户私钥
#define ALIPAY_PRIVATE							"MIICeQIBADANBgkqhkiG9w0BAQEFAASCAmMwggJfAgEAAoGBAMkFUVP1BwlCd2AhwLN/PGZO/XRG8Baz9SOgXYu6heQWPMwv+ppubwJ3GAELnEh4ivxnpqEd8X29aposWZ+QSJBDRRzg6ye16A3MM7gD94zCLDQbKK8lfQ/5pNO8TEsvAtFjNStgZb9EufF3I4N6qbH22C4tj/CmXKwiwLf6c9ZRAgMBAAECgYEAupIe64dtYmC4Hxb0nSQoUORbRMJaLxgTG1/JstgJUKp6/yBAvXhlu6oBM2ctQ+3tQVqKQtthuUxGVpV3ESt+zA8k1lFOnPW4u5xcmmrlupf0LKzHg/8XZvaXiZKyF1N5UCimIu6cDwtIRU+V/eEUeVRwdI2XuBfv62ant0CutGECQQD6Nrf8L9szUM+ChY9C0kiySuw+7lXj0WxLZ4EcLaap0QmM6yfe06PePFACVgLVygAZ/h+z9EhOW2WNvajcbtztAkEAzatfm1GxP7CvBKXbNwowZnNFNpJXaRmwXaHEfMSPGYYs8HMGeW9v300Iw6bm/unv5T6xAeb8mHLuUpoaKu6WdQJBAO1Y8If5gW4ZDu6Z8P6K6Mivx5AelzznEFoq0c9AAqN9lhiljImTqxMJlT/SBRh1aEk/xST36Yriqd+ddEu9ojUCQQDMoKZmDXiSCsOHl1EtSNjxBd0mN6H6ctGzxwCMtrA9z+6kaX1WkxY2kRmYOFX56F2Ds8U/REerkiYmTyab8ngFAkEAjl4jPfMUAB4tCfJQz64vUYIsKq3DwzHlFbKHkFocrnwvGwS3DPeQFasJBVpT7YU6eOzsSCNHlXTLth5MLgxE8Q=="
//淘宝公钥
#define ALIPAY_PUBLIC							"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCnxj/9qwVfgoUh/y2W89L6BkRAFljhNhgPdyPuBV64bfQNN1PjbCzkIM6qRdKBoLPXmKKMiFYnkd6rAoprih3/PrQEB/VsW8OoM8fxn67UDYuyBTqA23MML9q1+ilIZwBC2AQ2UBVOrFXfFl75p6/B5KsiNG9zpgmLCUYuLkxpLQIDAQAB"


#elif defined(DEMO_FOR_INTERFLOW)

#define MOBILE_GOURD_LIFENUM		10

#endif


#define TARGET_SCREEN_WIDTH		720.0f
#define TARGET_SCREEN_HEIGHT	1280.0f

#if 0
#define GAME_UI_TOP1_IDLE_LEN				44.0f
#define GAME_UI_TOP2_IDLE_LEN				44.0f
#define GAME_UI_BOTTOM1_IDLE_LEN			100.0f
#define GAME_UI_BOTTOM2_IDLE_LEN			44.0f
#define GAME_UI_TOTAL_IDLE_LEN				(GAME_UI_TOP1_IDLE_LEN + GAME_UI_TOP2_IDLE_LEN +GAME_UI_BOTTOM1_IDLE_LEN+ GAME_UI_BOTTOM2_IDLE_LEN)
#endif

#define GAME_UI_LEN1						420.0f
#define GAME_UI_LEN2						200.0f
#define GAME_UI_LINE_LEN					35.0f

#define SCREEN_DEMARCATION1_HEIGHT		(720.0f + GAME_UI_LEN1)
#define SCREEN_DEMARCATION2_HEIGHT		960.0f


#define TOLLGATE_SCENE_TAG	101
#define MAINMAPUILAYER_TAG	102
#define MAINMAP_TAG			103
#define SELECT_LVL_LAYER_TAG 104


//消息模式的消息字符窜
extern const char* receiveCollectMsg;
extern const char* ShowOrHideLayer;
extern const char* IntoGameLvl1;

//KKPAY版本支付
#define KK_PAY_VERSION

//纯净版本控制
//#define CLEAN_VERSION

#endif
