LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Caramel

CRM_SRC := ../../src

LOCAL_SRC_FILES := \
	$(CRM_SRC)/Android.cpp \
	$(CRM_SRC)/Async.cpp \
	$(CRM_SRC)/Data.cpp \
	$(CRM_SRC)/DateTime.cpp \
	$(CRM_SRC)/Error.cpp \
	$(CRM_SRC)/FileSystem.cpp \
	$(CRM_SRC)/Lexical.cpp \
	$(CRM_SRC)/Math.cpp \
	$(CRM_SRC)/Object.cpp \
	$(CRM_SRC)/Random.cpp \
	$(CRM_SRC)/Statechart.cpp \
	$(CRM_SRC)/String.cpp \
	$(CRM_SRC)/Task.cpp \
	$(CRM_SRC)/Thread.cpp \
	$(CRM_SRC)/Trace.cpp \
	$(CRM_SRC)/Value.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../include \
	$(GIT_ROOT)/CandyJar/include
	
include $(BUILD_STATIC_LIBRARY)
 
