LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/StartScene.cpp \
				   ../../Classes/ChapterScene.cpp \
				   ../../Classes/Person.cpp \
				   ../../Classes/Bullet.cpp \
				   ../../Classes/BulletManager.cpp \
				   ../../Classes/Role.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/SceneManager.cpp\
				   ../../Classes/Player.cpp \
				   ../../Classes/NPC.cpp \
				   ../../Classes/PauseLayer.cpp \
				   ../../Classes/FirstScene.cpp \
				   ../../Classes/SecondScene.cpp \
				   ../../Classes/ThirdScene.cpp  \
				   ../../Classes/StateController.cpp \
				   ../../Classes/SuccessLayer.cpp \
				   ../../Classes/FailureLayer.cpp \
				   ../../Classes/ModeSelecteScene.cpp \
				   ../../Classes/SurvivalScene.cpp \
				   ../../Classes/CompeteScene.cpp \
				   ../../Classes/Prop.cpp \
				   ../../Classes/PropManager.cpp \
				   ../../Classes/ConfigureScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

$(call import-module,Box2D)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,extensions)
