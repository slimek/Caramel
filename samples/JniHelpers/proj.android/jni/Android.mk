#
# Store the Local Path
#

JNIHP_LOCAL_PATH := $(call my-dir)


#
# Load all pre-built Libraries
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


#
# Build JniHelpers App
#

include $(CLEAR_VARS)

LOCAL_PATH   := $(JNIHP_LOCAL_PATH)
LOCAL_MODULE := JniHelpers

JNIHP_SRC := ../../src

LOCAL_SRC_FILES := \
	$(JNIHP_SRC).android/NativeActions.cpp
	
LOCAL_C_INCLUDES := \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include
	
LOCAL_WHOLE_STATIC_LIBRARIES := \
	boost-chrono \
	boost-date_time \
	boost-filesystem \
	boost-system \
	Caramel

LOCAL_LDLIBS := \
	-landroid \
	-llog

	
include $(BUILD_SHARED_LIBRARY)


#
# Import other dependencies
#
 
$(call import-add-path,$(GIT_ROOT)/)
$(call import-module,Caramel/proj.android/jni)
