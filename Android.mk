LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES_JNI_PREFIXED := \
    $(wildcard $(LOCAL_PATH)/../../../Classes/*.cpp) \
    $(wildcard $(LOCAL_PATH)/../../../Classes/**/*.cpp) \
    $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/*.cpp)  

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   $(LOCAL_SRC_FILES_JNI_PREFIXED)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/IngameObject \
					$(LOCAL_PATH)/../../../Classes/IngameObject/Unit \
					$(LOCAL_PATH)/../../../Classes/IngameObject/Skill \
					$(LOCAL_PATH)/../../../Classes/GlobalClass 


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
