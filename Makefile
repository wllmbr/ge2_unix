# Project Directories
SRC 		:= src
BLD 		:= bld
DEPDIR 		:= $(BLD)/deps
PRJ_NAME 	:= $(shell basename $(CURDIR))

# Application Files
C_SOURCE_FILES 			:= $(shell find ./$(SRC) -type f -name *.c)
C_SOURCE_FILES_BASE 	:= $(notdir $(C_SOURCE_FILES))
C_OBJECT_FILES 			:= $(addprefix $(BLD)/, $(patsubst %.c, %.o, $(C_SOURCE_FILES_BASE)))
C_DEP_FILES 			:= $(addprefix $(DEPDIR)/, $(patsubst %.c, %.d, $(C_SOURCE_FILES_BASE)))
CXX_SOURCE_FILES 		:= $(shell find ./$(SRC) -type f -name *.cpp)
CXX_SOURCE_FILES_BASE 	:= $(notdir $(CXX_SOURCE_FILES))
CXX_OBJECT_FILES 		:= $(addprefix $(BLD)/, $(patsubst %.cpp, %.o, $(CXX_SOURCE_FILES_BASE)))
CXX_DEP_FILES 			:= $(addprefix $(DEPDIR)/, $(patsubst %.cpp, %.d, $(CXX_SOURCE_FILES_BASE)))
SOURCE_FILES			:= $(C_SOURCE_FILES) $(CXX_SOURCE_FILES)
SOURCE_FILES_BASE		:= $(C_SOURCE_FILES_BASE) $(CXX_SOURCE_FILES_BASE)
OBJECT_FILES			:= $(C_OBJECT_FILES) $(CXX_OBJECT_FILES)
SOURCE_DIRS				:= $(shell find ./$(SRC)/* -type d)
DEP_FILES				:= $(C_DEP_FILES) $(CXX_DEP_FILES)

CC 		:= gcc
CXX		:= g++
ASM_CMD := objdump
IMG_CMD := objcopy

OPT 			:= -O3 -g
INCLUDE_DIRS 	:= $(addprefix -I, $(SOURCE_DIRS))
WARN			:= -Wall
LINK			:= -lsfml-window -lsfml-graphics -lsfml-system -lpthread -lX11
CFLAGS 			:= $(INCLUDE_DIRS) $(OPT) $(WARN) $(LINK)
DEPFLAGS		= -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# Output Files
EXE := $(PRJ_NAME).exe
IMG := $(PRJ_NAME).img

all: $(EXE)

exe: $(EXE)

img: $(IMG)

clean:
	@echo Cleaning
	@rm -rf $(BLD)/*.o $(EXE) $(IMG)

cleanall:
	@echo Cleaning all
	@rm -rf $(BLD)/* $(EXE) $(IMG)	
	

remake: clean all

$(EXE): $(OBJECT_FILES)
	@echo Linking
	@$(CXX) $(CFLAGS) -o $@ $^

$(IMG): $(EXE)
	@echo Building Image
	@$(IMG_CMD) -Obinary $^ $@

# Generic Rules
$(BLD)/%.o: $(SRC)/**/%.c $(SRC)/**/%.h $(DEPDIR)/%.d | $(DEPDIR)
	@echo Compiling $(@F)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -o $@ -c $<

$(BLD)/%.o: $(SRC)/**/%.c $(DEPDIR)/%.d | $(DEPDIR)
	@echo Compiling $(@F)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -o $@ -c $<

$(BLD)/%.o: $(SRC)/**/%.cpp $(SRC)/**/%.h $(DEPDIR)/%.d | $(DEPDIR)
	@echo Compiling $(@F)
	@$(CXX) $(DEPFLAGS) $(CFLAGS) -o $@ -c $<

$(BLD)/%.o: $(SRC)/**/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	@echo Compiling $(@F)
	@$(CXX) $(DEPFLAGS) $(CFLAGS) -o $@ -c $<

.PHONY: all exe img clean remake

$(DEP_FILES):

$(DEPDIR):
	mkdir $@

include $(wildcard $(DEP_FILES))