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


include $(CLEAR_VARS)
LOCAL_MODULE := Caramel
LOCAL_SRC_FILES := $(GIT_ROOT)/Caramel/proj.android/obj/$(CARAMEL_CONFIG)/local/$(TARGET_ARCH_ABI)/libCaramel.a
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
	