APP_PLATFORM := android-15
APP_ABI := x86 armeabi

APP_STL := gnustl_static
NDK_TOOLCHAIN_VERSION := 4.8

APP_CFLAGS := -fexceptions
APP_CPPFLAGS := -std=c++11 -frtti -fsigned-char
APP_LDFLAGS := -latomic

ifeq ($(NDEBUG),1)

# Release
APP_OPTIM := release
CARAMEL_CONFIG := gcc48.Release

else

# Debug

APP_OPTIM := debug
CARAMEL_CONFIG := gcc48.Debug

APP_CFLAGS += -g

endif

NDK_APP_OUT := obj/$(CARAMEL_CONFIG)
