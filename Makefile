# compilers
CC := clang
CFLAGS := -Wall -Wno-strict-aliasing -Wno-deprecated-register -Iinclude -std=c++11
LFLAGS := -lstdc++

# directories
INCLUDES_DIR := include
BUILD_DIR := build
EXEC_DIR := bin
vpath %.cpp src
vpath %.cpp src/parser
vpath %.cpp src/nodes

# files
MAIN := src/main.cpp
PARSER := src/parser/parser.ypp
PARSER_GEN := $(addsuffix .gen.cpp, $(basename $(PARSER)))
LEXER := src/parser/lexer.l
LEXER_GEN := $(addsuffix .gen.cpp, $(basename $(LEXER)))
EXEC_NAME := prolog
SOURCES := $(shell find src -name *.cpp)
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o, $(notdir $(basename $(SOURCES)))))

# Sort out sad platform discrepencies
ifeq ($(shell uname -s), Darwin)
	LFLAGS += -ll
	CFLAGS += -DOSX=1 -DLINUX=0
else
	LFLAGS += -lfl
	CFLAGS += -DOSX=0 -DLINUX=1
endif

all: prelude
	$(MAKE) parser
	$(MAKE) prolog

prelude:
	@mkdir -p $(INCLUDES_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(EXEC_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@echo "\nBuilding $<"
	$(CC) $(CFLAGS) -c -o $@ $<

prolog: $(OBJS)
	@echo "\nBuilding program $(EXEC_NAME)..."
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(EXEC_DIR)/$(EXEC_NAME)

parser: 
	@echo "\nGenerating parser..."
	flex --header-file=$(INCLUDES_DIR)/lexer.h -o $(LEXER_GEN) $(LEXER)
	bison --defines=$(INCLUDES_DIR)/parser.h -o $(PARSER_GEN) $(PARSER)

run: all
	@echo "\nRunning..."
	./$(EXEC_DIR)/$(EXEC_NAME)

clean:
	rm -r $(BUILD_DIR)
	rm $(PARSER_GEN)
	rm $(LEXER_GEN)

.PHONY: prelude prolog parser run clean
