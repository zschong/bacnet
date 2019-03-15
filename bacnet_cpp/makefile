ARCH:=
CC:=$(ARCH)g++
AR:=$(ARCH)ar
ARFLAGS:= -r
STRIP:=$(ARCH)strip
CFLAGS:= -Iinclude -Ilinux
SRC:=$(shell find ./ | grep "\.c$$")
OBJ:=$(SRC:.c=.o)
LIB:= bacnet.a

all:$(LIB)
	@du -sh *

$(LIB):$(OBJ)
	@$(AR) $(ARFLAGS) $@ $+

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $+
	@echo $@

clean:
	@rm -vf $(OBJ) bacnet.a
