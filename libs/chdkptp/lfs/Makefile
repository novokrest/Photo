TOPDIR=..
include $(TOPDIR)/include.mk
ifdef LUA_INCLUDE_DIR
INC_PATHS+=-I$(LUA_INCLUDE_DIR)
endif
CFLAGS+=$(INC_PATHS) -I/usr/include/lua5.2
CFLAGS+=-fPIC
SRCS=lfs.c
OBJS=$(SRCS:.c=.o)
all: $(OBJS)

include $(TOPDIR)/bottom.mk

