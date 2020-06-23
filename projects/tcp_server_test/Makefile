TARGET := tcp_server_test
TINYIIOD ?= n

PLATFORM = aducm3029

ifeq (aducm3029,$(strip $(PLATFORM)))

SRC_DIRS += projects/$(TARGET)/src

DISABLE_SECURE_SOCKET=y
SRC_DIRS += network

ifeq (y,$(strip $(TINYIIOD)))
SRC_DIRS += libraries/iio
endif

include ../../tools/scripts/aducm.mk

else

ifeq ($(OS), Windows_NT)
include ../../tools/scripts/windows.mk
else
include ../../tools/scripts/linux.mk
endif

endif
