TARGET := scop

BUILD_DIR := ./build
SRC_DIRS := ./srcs

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp') glad/src/glad.c
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) glfw/build/include glad/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX := g++
CXXFLAGS := $(INC_FLAGS) -Wall -Wextra -Werror

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	cmake -S glfw -B glfw/build
	make -C glfw/build
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -l GL -l glfw -ldl -lm

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
