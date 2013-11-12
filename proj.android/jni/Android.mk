LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Caramel

MY_SRC_DIR := ../../src

LOCAL_SRC_FILES := \
	$(MY_SRC_DIR)/DateTime.cpp \
	$(MY_SRC_DIR)/Error.cpp \
	$(MY_SRC_DIR)/Lexical.cpp \
	$(MY_SRC_DIR)/Object.cpp \
	$(MY_SRC_DIR)/Statechart.cpp \
	$(MY_SRC_DIR)/String.cpp \
	$(MY_SRC_DIR)/Task.cpp \
	$(MY_SRC_DIR)/Thread.cpp \
	$(MY_SRC_DIR)/Trace.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../include \
	$(GIT_ROOT)/CandyJar/include
	
include $(BUILD_STATIC_LIBRARY)
 
