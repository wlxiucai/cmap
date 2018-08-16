#SRC_OBJ = $(patsubst %.c,%.o, $(wildcard *.c))
#CFLAGS += -g -Wall -Werror -O2
CPPFLAGS += -I.
LDFLAGS += -lpthread

SRC = $(wildcard *.c)
SRC_OBJ = $(SRC:.c=.o)
SRC_BIN = demo

all:$(SRC_BIN)
$(SRC_BIN) : $(SRC_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

tags:
	ctags -R

help:
	@echo "=====================================A commom Makefile for cprograms===================================="
	@echo "Copyright (C) 2018 wlxiucai@foxmail.com"
	@echo "The follwing targets are support:"
	@echo 
	@echo " all								- (==make) compile and link"
	@echo " obj								- just compile,without link"
	@echo " clean							- clean target"
	@echo " distclean						- clean target and otherinformation"
	@echo " tags							- create ctags for vim editor"
	@echo " help							- print help information"
	@echo
	@echo "To make a target do 'make [target]'"

clean:
	$(RM) $(SRC_OBJ) $(SRC_BIN)

distclean:
	$(RM) $(SRC_OBJ) $(SRC_BIN) $(SRC_BIN).exe tags *~

.PHONY : all tags help clean distclean
