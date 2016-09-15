APP_ABI := all

#APP_PLATFORM := android-15
APP_STL := gnustl_static
APP_CPPFLAGS  := -std=c++11
LOCAL_C_INCLUDES += ${ndk}/sources/cxx-stl/gnu-libstdc++/4.8/include

APP_CFLAGS := -pthread -frtti -fexceptions -O3 -mfloat-abi=softfp -mfpu=neon

LOCAL_ARM_NEON := true
APP_OPTIM := release