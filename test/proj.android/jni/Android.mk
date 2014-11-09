#
# Store the local path
#

CRMTEST_LOCAL_PATH := $(call my-dir)


#
# Load all pre-built libraries
#

CANDY_LIB := $(GIT_ROOT)/CandyJar/lib/Android.Ndk.$(CARAMEL_CONFIG)/$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-chrono
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-chrono.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-date_time
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-date_time.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-filesystem
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-filesystem.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-system
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-system.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := UnitTest++
LOCAL_SRC_FILES := $(CANDY_LIB)/libUnitTest++.a
include $(PREBUILT_STATIC_LIBRARY)


#
# Build Carver App
#

include $(CLEAR_VARS)

LOCAL_PATH := $(CRMTEST_LOCAL_PATH)

LOCAL_MODULE := CaramelTest

CRMTEST_SRC := ../../src

LOCAL_SRC_FILES := \
	$(CRMTEST_SRC)/CaramelTestPch.cpp \
	$(CRMTEST_SRC)/AndroidRun.cpp \
	$(CRMTEST_SRC)/Arithmetic/FlagsSuite.cpp \
	$(CRMTEST_SRC)/Arithmetic/PowerOfTwoSuite.cpp \
	$(CRMTEST_SRC)/Chrono/ClockProxySuite.cpp \
	$(CRMTEST_SRC)/Chrono/SecondClockSuite.cpp \
	$(CRMTEST_SRC)/Chrono/TickClockSuite.cpp \
	$(CRMTEST_SRC)/Chrono/TimedBoolSuite.cpp \
	$(CRMTEST_SRC)/Error/AlertSuite.cpp \
	$(CRMTEST_SRC)/Error/AnyFailureSuite.cpp \
	$(CRMTEST_SRC)/Error/CatchExceptionSuite.cpp \
	$(CRMTEST_SRC)/Error/ExceptionPtrSuite.cpp \
	$(CRMTEST_SRC)/String/FormatSuite.cpp \
	$(CRMTEST_SRC)/String/SplitSuite.cpp \
	$(CRMTEST_SRC)/String/SprintfSuite.cpp \
	$(CRMTEST_SRC)/String/StringAlgorithmSuite.cpp \
	$(CRMTEST_SRC)/String/StringConvertibleSuite.cpp \
	$(CRMTEST_SRC)/String/StringToStringSuite.cpp \
	$(CRMTEST_SRC)/String/Utf8StringSuite.cpp \
	$(CRMTEST_SRC)/Trace/TraceChannelSuite.cpp \
	$(CRMTEST_SRC)/Trace/TraceSuite.cpp \


LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include
	
	
LOCAL_WHOLE_STATIC_LIBRARIES := \
	boost-chrono \
	boost-date_time \
	boost-filesystem \
	boost-system \
	Caramel \
	UnitTest++

LOCAL_LDLIBS := \
	-landroid \
	-llog

	
include $(BUILD_SHARED_LIBRARY)
	

#
# Import other dependencies
#
 
$(call import-add-path,$(GIT_ROOT)/)
$(call import-module,Caramel/proj.android/jni)

