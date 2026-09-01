ifeq ($(OS),Windows_NT)
    PLATFORM := Windows
    RM       := del /Q /F
else
    PLATFORM := Unix
    RM       := rm -f
endif

CXX      = g++
RAW_INCLUDES := include/cvm ../common/include
INCLUDES := $(addprefix -I,$(RAW_INCLUDES))
SRCS    = src
TARGET  = cvm

TARGET_ARCH ?= UNKNOWN_TARGET_ARCH

ALL_CPPS := $(wildcard $(SRCS)/*.cpp)

OBJ_DIR  := obj
OBJS     := $(patsubst $(SRCS)/%.cpp, $(OBJ_DIR)/%.o, $(ALL_CPPS))

CXXFLAGS := -Werror -Wfatal-errors -Wall -Wextra -O2 -std=c++23 -D$(TARGET_ARCH) $(INCLUDES)
LINKFLAGS := -O2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LINKFLAGS) -o $(TARGET) $<

$(OBJ_DIR)/%.o: $(SRCS)/%.cpp
	@mkdir -p $(OBJ_DIR) 2>/dev/null || true
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
ifeq ($(PLATFORM),Windows)
	$(RM) obj\*.o $(TARGET)$(LIB_EXT) 2>NUL || true
else
	$(RM) $(OBJS) $(TARGET)
	rm -rf $(OBJ_DIR)
endif

.PHONY: all clean
