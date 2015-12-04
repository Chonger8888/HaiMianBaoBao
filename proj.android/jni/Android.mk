LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/CandyPay/CandyPay.cpp \
                   ../../Classes/CandyPay/NetWork.cpp \
				   ../../Classes/CandyPay/TimeInterval.cpp \
                   ../../Classes/CommonData/CommonData.cpp \
                   ../../Classes/CommonData/CommonWidgt.cpp \
                   ../../Classes/CommonData/Counter.cpp \
                   ../../Classes/CommonData/ToastDisplay.cpp \
                   ../../Classes/CommonData/UIcontroller.cpp \
                   ../../Classes/CppCallJava/CppCallJava.cpp \
                   ../../Classes/JavaCallCpp/JavaCallCpp.cpp \
                   ../../Classes/jni/org_weme_candy_util_CandyPay.cpp \
                   ../../Classes/Loading/LoadingScene.cpp \
				   ../../Classes/Loading/MMLog.cpp \
                   ../../Classes/Login/UILogin.cpp \
                   ../../Classes/MainMap/ClippingTouchLayer.cpp \
                   ../../Classes/MainMap/CollectStarsUI.cpp \
                   ../../Classes/MainMap/MainMapScene.cpp \
                   ../../Classes/MainMap/MainMapUiLayer.cpp \
                   ../../Classes/MainMap/ShaderSprite.cpp \
                   ../../Classes/MainMap/TollgatePage.cpp \
                   ../../Classes/MainMenu/MainMenuScene.cpp \
                   ../../Classes/MsgMgr/AnalyseJson.cpp \
                   ../../Classes/MsgMgr/HeadDownMgr.cpp \
                   ../../Classes/MsgMgr/MsgMgr.cpp \
                   ../../Classes/MsgMgr/UrlMgr.cpp \
                   ../../Classes/PlayGame/CandyBgGrid.cpp \
                   ../../Classes/PlayGame/CandyCell.cpp \
                   ../../Classes/PlayGame/CandyChocolate.cpp \
                   ../../Classes/PlayGame/CandyCombination.cpp \
                   ../../Classes/PlayGame/CandyCorrectMap.cpp \
                   ../../Classes/PlayGame/CandyCream.cpp \
                   ../../Classes/PlayGame/CandyDispel.cpp \
                   ../../Classes/PlayGame/CandyEffectLayer.cpp \
                   ../../Classes/PlayGame/CandyExplosions.cpp \
                   ../../Classes/PlayGame/CandyGuideLayer.cpp \
                   ../../Classes/PlayGame/CandyIngredients.cpp \
                   ../../Classes/PlayGame/CandyInterludeAction.cpp \
                   ../../Classes/PlayGame/CandyJelly.cpp \
                   ../../Classes/PlayGame/CandyLayer.cpp \
                   ../../Classes/PlayGame/CandyLicorices.cpp \
                   ../../Classes/PlayGame/CandyLock.cpp \
                   ../../Classes/PlayGame/CandyManager.cpp \
                   ../../Classes/PlayGame/CandyMapData.cpp \
                   ../../Classes/PlayGame/CandyMove.cpp \
                   ../../Classes/PlayGame/CandyMusic.cpp \
                   ../../Classes/PlayGame/CandyNewPortal.cpp \
                   ../../Classes/PlayGame/CandyParticle.cpp \
                   ../../Classes/PlayGame/CandyPlace.cpp \
                   ../../Classes/PlayGame/CandyResult.cpp \
                   ../../Classes/PlayGame/CandyRoulette.cpp \
                   ../../Classes/PlayGame/CandyRouletteNew.cpp \
                   ../../Classes/PlayGame/CandyRouletteStory.cpp \
                   ../../Classes/PlayGame/CandyScore.cpp \
                   ../../Classes/PlayGame/CandyShare.cpp \
                   ../../Classes/PlayGame/CandySpecialManager.cpp \
                   ../../Classes/PlayGame/CandyStageIntro.cpp \
                   ../../Classes/PlayGame/CandyTarget.cpp \
                   ../../Classes/PlayGame/CandyUiLayer.cpp \
                   ../../Classes/PlayGame/PlayGameScene.cpp \
                   ../../Classes/UIMgr/UIMgrTurn.cpp \
                   ../../Classes/WeMeLogo/WeMeLogoScene.cpp \







                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
			$(LOCAL_PATH)/../../../../scripting/lua/lua \
			$(LOCAL_PATH)/../../../../scripting/lua/tolua\
			$(LOCAL_PATH)/../../../../scripting/lua/cocos2dx_support\
			$(LOCAL_PATH)/../../../../extensions/spine

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,scripting/lua/proj.android)
