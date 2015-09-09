LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Caramel

CRM_SRC := ../../src

LOCAL_SRC_FILES := \
	$(CRM_SRC)/CaramelPch.cpp \
	$(CRM_SRC)/Android.cpp \
	$(CRM_SRC)/Async.cpp \
	$(CRM_SRC)/Data.cpp \
	$(CRM_SRC)/DateTime.cpp \
	$(CRM_SRC)/Document.cpp \
	$(CRM_SRC)/Error.cpp \
	$(CRM_SRC)/FileSystem.cpp \
	$(CRM_SRC)/Io.cpp \
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


#
# Prebuilding Caramel
#

ifdef CARAMEL_CONFIG

#
# Make output directories, then copy the library to there
#

CRM_LIB := ../lib
CRM_ARCH_ABI := $(TARGET_ARCH_ABI)
NDK_CRM_CONFIG := Android.Ndk.$(CARAMEL_CONFIG)

all: $(CRM_ARCH_ABI)

$(CRM_ARCH_ABI): $(LOCAL_BUILT_MODULE)
	$(call host-mkdir,$(CRM_LIB)/$(NDK_CRM_CONFIG)/$@)
	$(call host-cp,obj/$(CARAMEL_CONFIG)/local/$@/libCaramel.a,$(CRM_LIB)/$(NDK_CRM_CONFIG)/$@/libCaramel.a)


#
# Clean the output directories
#

clean: $(CRM_ARCH_ABI)-clean

$(CRM_ARCH_ABI)-clean:
	$(call host-rm,$(CRM_LIB)/$(NDK_CRM_CONFIG)/$(subst -clean,,$@)/libCaramel.a)


endif
