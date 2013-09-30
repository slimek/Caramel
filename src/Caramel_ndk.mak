#
# Environment Settings
#

# NDK Standalone Toolchain Path
NDK_BIN := /cygdrive/d/Android/standalone-14/bin

# Boost Path
BOOST_INC := ../../Boost

#
# Compilation Tools & Flags
#

CPP := $(NDK_BIN)/arm-linux-androideabi-g++
AR  := $(NDK_BIN)/arm-linux-androideabi-ar

CPPFLAGS += \
-I../src \
-I../include \
-I$(BOOST_INC) \
-std=c++11


#
# Source List and Functions
#

cppfiles := \
Chrono.cpp Error.cpp FileSystem.cpp FileView.cpp Io.cpp Lexical.cpp \
Object.cpp Program.cpp String.cpp Trace.cpp Windows.cpp

make-source = $(addprefix Caramel/,$1)
make-object = $(addprefix ../obj/,$(subst .cpp,.o,$1))

objfiles := $(addprefix ../obj/,$(subst .cpp,.o,$(cppfiles)))

# call source, object
define compile-one-rule
  $2 : $1
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define compile-rules
  $(foreach f, $(cppfiles),\
    $(call compile-one-rule,$(call make-source,$f),$(call make-object,$f))
  )
endef


#
# Compilation Recipes
#

.PHONY : all
all : libCaramel.a

OUT := libCaramel.a

libCaramel.a : $(objfiles)
	$(AR) -crs $(OUT) $(objfiles)
	
$(eval $(compile-rules))

