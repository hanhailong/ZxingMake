APP_ABI := armeabi-v7a

#APP_PLATFORM := android-14
APP_STL := gnustl_static
APP_CPPFLAGS  := -std=c++11
LOCAL_C_INCLUDES += ${ndk}/sources/cxx-stl/gnu-libstdc++/4.8/include


#http://www.cnblogs.com/hrlnw/p/3653695.html 下一步优化方向

#APP_CFLAGS := -pthread -frtti -fexceptions -O3 -mfloat-abi=softfp -mfpu=neon

APP_CFLAGS := -pthread -frtti -fexceptions -O3

LOCAL_ARM_NEON := true
APP_OPTIM := release