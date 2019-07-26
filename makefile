
RUNTIME_DIR = runtime
COMPILER_DIR = compiler
DISASSEMBLER_DIR = disassembler
COMMON_DIR = common

COMPILER_FILES = $(COMPILER_DIR)/main.c 	\
				 $(COMPILER_DIR)/builder.c 	\
				 $(COMPILER_DIR)/segment.c 	\
				 $(COMPILER_DIR)/ast.c 		\
				 $(COMPILER_DIR)/lex.yy.c

DISASSEMBLER_FILES = $(DISASSEMBLER_DIR)/main.c
RUNTIME_FILES = $(RUNTIME_DIR)/builtins.c 					\
				$(RUNTIME_DIR)/context.c 					\
				$(RUNTIME_DIR)/runtime.c 					\
				$(RUNTIME_DIR)/module.c 					\
				$(RUNTIME_DIR)/sources.c 					\
				$(RUNTIME_DIR)/objects.c 					\
				$(RUNTIME_DIR)/memory.c 					\
				$(RUNTIME_DIR)/objects/object_array.c 		\
				$(RUNTIME_DIR)/objects/object_bool.c 		\
				$(RUNTIME_DIR)/objects/object_cfunction.c 	\
				$(RUNTIME_DIR)/objects/object_dict.c 		\
				$(RUNTIME_DIR)/objects/object_float.c 		\
				$(RUNTIME_DIR)/objects/object_function.c 	\
				$(RUNTIME_DIR)/objects/object_int.c 		\
				$(RUNTIME_DIR)/objects/object_iterator.c 	\
				$(RUNTIME_DIR)/objects/object_module.c 		\
				$(RUNTIME_DIR)/objects/object_string.c 		\
				$(RUNTIME_DIR)/objects/object_type.c 		\
				$(RUNTIME_DIR)/main.c 						

COMMON_FILES = $(COMMON_DIR)/common.c $(COMMON_DIR)/utils.c
COMPILER_FLAGS = -lfl -g #-Wall -Wextra
RUNTIME_FLAGS = -rdynamic -g -pthread -ldl -Wall -Wextra
COMPILER_BISON_FLAGS = -d --verbose
COMPILER_FLEX_FLAGS =
CC = gcc

all: _runtime _disassembler _compiler

# Compiler

_bison_stuff: $(COMPILER_DIR)/hoyo.y
		cd $(COMPILER_DIR) && bison $(COMPILER_BISON_FLAGS) hoyo.y && cd ..

_flex_stuff: $(COMPILER_DIR)/hoyo.l $(COMPILER_DIR)/hoyo.tab.h
		cd $(COMPILER_DIR) && flex $(COMPILER_FLEX_FLAGS) hoyo.l && cd ..

_compiler: _flex_stuff _bison_stuff
	$(CC) $(COMPILER_FILES) $(COMPILER_FLAGS) -o hoyoc

# Runtime

_runtime:
	$(CC) $(COMMON_FILES) $(RUNTIME_FILES) $(RUNTIME_FLAGS) -o hoyo

# Disassembler

_disassembler:
	$(CC) $(DISASSEMBLER_FILES) $(COMMON_FILES) -o dis -g
