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
	$(CRMTEST_SRC)/Async/AnyEventDispatcherSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventHandlerSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventReactorSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventQueueSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventSlotSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventSuite.cpp \
	$(CRMTEST_SRC)/Async/AnyEventTaskSuite.cpp \
	$(CRMTEST_SRC)/Async/FlowStateSuite.cpp \
	$(CRMTEST_SRC)/Async/ValueChangeSuite.cpp \
	$(CRMTEST_SRC)/Chrono/ClockProxySuite.cpp \
	$(CRMTEST_SRC)/Chrono/SecondClockSuite.cpp \
	$(CRMTEST_SRC)/Chrono/TickClockSuite.cpp \
	$(CRMTEST_SRC)/Chrono/TimedBoolSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentBlockingQueueSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentDelayQueueSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentIntervalSetSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentMapSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentPriorityQueueSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentQueueSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentSetSuite.cpp \
	$(CRMTEST_SRC)/Concurrent/ConcurrentStackSuite.cpp \
	$(CRMTEST_SRC)/Data/Base64Suite.cpp \
	$(CRMTEST_SRC)/Data/LookupTableSuite.cpp \
	$(CRMTEST_SRC)/DateTime/DateSuite.cpp \
	$(CRMTEST_SRC)/DateTime/DateTimeBoolSuite.cpp \
	$(CRMTEST_SRC)/DateTime/DateTimeSuite.cpp \
	$(CRMTEST_SRC)/DateTime/TimeOfDaySuite.cpp \
	$(CRMTEST_SRC)/DateTime/TimeSpanSuite.cpp \
	$(CRMTEST_SRC)/Document/IniDocumentSuite.cpp \
	$(CRMTEST_SRC)/Error/AlertSuite.cpp \
	$(CRMTEST_SRC)/Error/AnyFailureSuite.cpp \
	$(CRMTEST_SRC)/Error/CatchExceptionSuite.cpp \
	$(CRMTEST_SRC)/Error/ExceptionPtrSuite.cpp \
	$(CRMTEST_SRC)/Error/TryCatchResultSuite.cpp \
	$(CRMTEST_SRC)/FileSystem/PathSuite.cpp \
	$(CRMTEST_SRC)/Functional/BindSuite.cpp \
	$(CRMTEST_SRC)/Io/InputMemoryStreamSuite.cpp \
	$(CRMTEST_SRC)/Io/TextStreamWriterSuite.cpp \
	$(CRMTEST_SRC)/Lexical/LexicalBooleanSuite.cpp \
	$(CRMTEST_SRC)/Lexical/LexicalFloatingListSuite.cpp \
	$(CRMTEST_SRC)/Lexical/LexicalFloatingSuite.cpp \
	$(CRMTEST_SRC)/Lexical/LexicalIntegerSuite.cpp \
	$(CRMTEST_SRC)/Lexical/LexicalVersionSuite.cpp \
	$(CRMTEST_SRC)/Memory/SharedPtrUtilsSuite.cpp \
	$(CRMTEST_SRC)/Meta/IsGeneralStringSuite.cpp \
	$(CRMTEST_SRC)/Meta/MetaRangeSuite.cpp \
	$(CRMTEST_SRC)/Numeric/NumberConverterSuite.cpp \
	$(CRMTEST_SRC)/Numeric/NumberRelationSuite.cpp \
	$(CRMTEST_SRC)/Numeric/NumberTraitsSuite.cpp \
	$(CRMTEST_SRC)/Numeric/UnionBitsSuite.cpp \
	$(CRMTEST_SRC)/Object/InstanceCountedSuite.cpp \
	$(CRMTEST_SRC)/Random/UniformRandomSuite.cpp \
	$(CRMTEST_SRC)/Random/WeightedRandomMapSuite.cpp \
	$(CRMTEST_SRC)/Statechart/PromptStateMachineSuite.cpp \
	$(CRMTEST_SRC)/Statechart/StateMachineSuite.cpp \
	$(CRMTEST_SRC)/String/FormatSuite.cpp \
	$(CRMTEST_SRC)/String/SplitSuite.cpp \
	$(CRMTEST_SRC)/String/StringAlgorithmSuite.cpp \
	$(CRMTEST_SRC)/String/StringConvertibleSuite.cpp \
	$(CRMTEST_SRC)/String/StringToStringSuite.cpp \
	$(CRMTEST_SRC)/String/Utf8StringSuite.cpp \
	$(CRMTEST_SRC)/Task/ContinuationTraitsSuite.cpp \
	$(CRMTEST_SRC)/Task/PromiseSuite.cpp \
	$(CRMTEST_SRC)/Task/StdAsyncSuite.cpp \
	$(CRMTEST_SRC)/Task/TaskPollerSuite.cpp \
	$(CRMTEST_SRC)/Task/TaskSuite.cpp \
	$(CRMTEST_SRC)/Task/TaskTimerSuite.cpp \
	$(CRMTEST_SRC)/Task/ThreadPoolSuite.cpp \
	$(CRMTEST_SRC)/Task/WhenAllSuite.cpp \
	$(CRMTEST_SRC)/Task/WorkerThreadSuite.cpp \
	$(CRMTEST_SRC)/Thread/LockGuardSuite.cpp \
	$(CRMTEST_SRC)/Thread/LoopThreadGroupSuite.cpp \
	$(CRMTEST_SRC)/Thread/SpinMutexSuite.cpp \
	$(CRMTEST_SRC)/Thread/ThreadSuite.cpp \
	$(CRMTEST_SRC)/Thread/WaitableBoolSuite.cpp \
	$(CRMTEST_SRC)/Trace/TraceChannelSuite.cpp \
	$(CRMTEST_SRC)/Trace/TraceSuite.cpp \
	$(CRMTEST_SRC)/Value/AnySuite.cpp \
	$(CRMTEST_SRC)/Value/EnumFlagsSuite.cpp \
	$(CRMTEST_SRC)/Value/NamedValuesSuite.cpp \
	$(CRMTEST_SRC)/Value/ScalarSuite.cpp \
	$(CRMTEST_SRC)/Value/SharedArraySuite.cpp \


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

