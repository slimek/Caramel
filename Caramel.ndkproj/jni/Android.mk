LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Caramel

LOCAL_SRC_FILES := \
	../../src/Configuration.cpp \
	../../src/DateTime.cpp \
	../../src/Debug.cpp \
	../../src/Document.cpp \
	../../src/Error.cpp \
	../../src/FileSystem.cpp \
	../../src/Io.cpp \
	../../src/Lexical.cpp \
	../../src/Object.cpp \
	../../src/Program.cpp \
	../../src/Random.cpp \
	../../src/Statechart.cpp \
	../../src/String.cpp \
	../../src/Task.cpp \
	../../src/Thread.cpp \
	../../src/Trace.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../include \
	$(GIT_ROOT)/CandyJar/include
	
LOCAL_WHOLE_STATIC_LIBRARIES := boost-chrono
LOCAL_WHOLE_STATIC_LIBRARIES += boost-filesystem
LOCAL_WHOLE_STATIC_LIBRARIES += boost-program_options
LOCAL_WHOLE_STATIC_LIBRARIES += boost-system
LOCAL_WHOLE_STATIC_LIBRARIES += boost-thread

include $(BUILD_SHARED_LIBRARY)


$(call import-add-path,$(GIT_ROOT)/CandyJar)

$(call import-module,Boost.Chrono)
$(call import-module,Boost.FileSystem)
$(call import-module,Boost.ProgramOptions)
$(call import-module,Boost.System)
$(call import-module,Boost.Thread)

 
