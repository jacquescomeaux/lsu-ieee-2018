CXX = g++
CXX_FLAGS = -std=c++11 -Wall -O3 #-mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mneon-for-64bits -funsafe-math-optimizations
#-I/usr/local/include
LFLAGS = $(shell pkg-config --cflags --libs libserialport opencv)

BIN = mybin
BUILD_DIR = ./build

CPP = $(wildcard src/*.cpp)

OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(BIN) : $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $^ $(LFLAGS) -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm $(BUILD_DIR)/$(BIN) $(OBJ) $(DEP)
