LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := wubaZxing

LOCAL_CPP_FEATURES += exceptions

LOCAL_C_INCLUDES += .

LOCAL_CPPFLAGS := -DNO_ICONV=1

define all-cpp-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "*.cpp" -and -not -name ".*") \
 )
endef

define all-cc-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "*.cc" -and -not -name ".*") \
 )
endef

define all-subdir-cpp-files
$(call all-cpp-files-under,.)
endef

define all-subdir-cc-files
$(call all-cc-files-under,.)
endef

LOCAL_SRC_FILES += $(call all-subdir-cpp-files)
LOCAL_SRC_FILES += $(call all-subdir-cc-files)


include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)