LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=  nativeSurface.cpp

LOCAL_SHARED_LIBRARIES := \
	liblog libutils libbinder libgui libcutils libui

LOCAL_CFLAGS += -Wno-multichar

LOCAL_MODULE_TAGS := debug

LOCAL_MODULE:= nativeSurface

include $(BUILD_EXECUTABLE)
