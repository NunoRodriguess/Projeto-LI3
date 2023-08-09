#DEFAULT SHELL
SHELL   = bash

#VARIABLES
CC      = gcc
LD      = gcc
CFLAGS  = -O2 `pkg-config  --cflags --libs glib-2.0` 
LIBS    = `pkg-config --libs glib-2.0`
INCLDS  = -I $(INC_DIR)
SUPP 	= --suppressions=/usr/share/glib-2.0/valgrind/glib.supp
#DIRS
BLD_DIR = build
INC_DIR = includes
SRC_DIR = src
RES_DIR = Resultados
RET_DIR = output_teste
PER_DIR = performance_output
TRASH   = $(BLD_DIR) $(RES_DIR) $(BLT_DIR) $(RET_DIR) $(PER_DIR)
#
SRC     = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))
#
PROGRAM = programa-principal
#

vpath %.c $(SRC_DIR)

.DEFAULT_GOAL = build

$(BLD_DIR)/%.o: %.c
	@echo -n "Building $(shell basename $@)... "
	@$(CC) -c $(INCLDS)  $(CFLAGS) $< -o $@ $(LIBS)
	@echo -e "$(OK_STRING)"

$(PROGRAM): $(OBJS)
	@echo -n "Compiling... " 
	@$(CC) $(INCLDS)  $(CFLAGS) src-teste/main.c -o programa-testes -g build/drivers.o build/interative.o build/interperter.o  build/model.o  build/read.o  build/rides.o build/table.o   build/users.o  build/stats.o  $(LIBS)
	@$(CC) $(INCLDS)  $(CFLAGS) -o $@  -g $(OBJS) $(LIBS)
	@echo -e "$(OK_STRING)"


build: setup $(PROGRAM)

run: build
	@ ./$(PROGRAM) data-folder input.txt 

teste: build
	@ time ./$(PROGRAM) data-folder input.txt 

setup:
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(RES_DIR)
	@mkdir -p $(RET_DIR)
	@mkdir -p $(PER_DIR)

clean:
	@echo -n "Cleaning... "
	@-rm -rf $(TRASH) programa-principal programa-testes
	@echo -e "$(OK_STRING)"

clean_out:
	@echo -n "Cleaning outputs... "
	@-rm -f Resultados/*
	@-rm -f output_teste/*
	@-rm -f performance_output/*
	@echo -e "$(OK_STRING)"