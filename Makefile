# Project Directories
SRC := src
BLD := bld
PRJ_NAME := $(shell basename $(CURDIR))

# Application Files
C_SOURCE_FILES 			:= $(shell find ./$(SRC) -type f -name *.c)
C_SOURCE_FILES_BASE 	:= $(notdir $(C_SOURCE_FILES))
C_OBJECT_FILES 			:= $(addprefix $(BLD)/, $(patsubst %.c, %.o, $(C_SOURCE_FILES_BASE)))
CXX_SOURCE_FILES 		:= $(shell find ./$(SRC) -type f -name *.cpp)
CXX_SOURCE_FILES_BASE 	:= $(notdir $(CXX_SOURCE_FILES))
CXX_OBJECT_FILES 		:= $(addprefix $(BLD)/, $(patsubst %.cpp, %.o, $(CXX_SOURCE_FILES_BASE)))
SOURCE_FILES			:= $(C_SOURCE_FILES) $(CXX_SOURCE_FILES)
SOURCE_FILES_BASE		:= $(C_SOURCE_FILES_BASE) $(CXX_SOURCE_FILES_BASE)
OBJECT_FILES			:= $(C_OBJECT_FILES) $(CXX_OBJECT_FILES)
SOURCE_DIRS				:= $(shell find ./$(SRC)/* -type d)

CC 		:= gcc
CXX		:= g++
ASM_CMD := objdump
IMG_CMD := objcopy

OPT 			:= -O3 -g
INCLUDE_DIRS 	:= $(addprefix -I, $(SOURCE_DIRS))
WARN			:= -Wall
CFLAGS 			:= $(INCLUDE_DIRS) $(OPT) $(WARN)

# Output Files
EXE := $(PRJ_NAME).exe
IMG := $(PRJ_NAME).img

all: $(EXE)

exe: $(EXE)

img: $(IMG)

clean:
	@echo Cleaning
	@rm -rf $(BLD)/* $(EXE) $(IMG)

remake: clean all


$(EXE): $(OBJECT_FILES)
	@echo Linking
	@$(CXX) $(CFLAGS) -o $@ $^

$(IMG): $(EXE)
	@echo Building Image
	@$(IMG_CMD) -Obinary $^ $@

# Generic Rules
$(BLD)/%.o: $(SRC)/**/%.c $(SRC)/**/%.h
	@echo Compiling $(@F)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BLD)/%.o: $(SRC)/**/%.c 
	@echo Compiling $(@F)
	@$(CC) $(CFLAGS) -o $@ -c $^

$(BLD)/%.o: $(SRC)/**/%.cpp $(SRC)/**/%.h
	@echo Compiling $(@F)
	@$(CXX) $(CFLAGS) -o $@ -c $<

$(BLD)/%.o: $(SRC)/**/%.cpp 
	@echo Compiling $(@F)
	@$(CXX) $(CFLAGS) -o $@ -c $^

.PHONY: all exe img clean remake