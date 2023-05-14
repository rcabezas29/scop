TARGET := scop

BUILD_DIR := ./build
SRC_DIRS := ./srcs

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX := clang++
CXXFLAGS := $(INC_FLAGS) -Wall -Wextra -Werror

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	cmake -S glfw -B build/glfw -D GLFW_USE_WAYLAND=1

clean:
	rm -r $(BUILD_DIR)

re: clean all

.PHONY: clean fclean re
