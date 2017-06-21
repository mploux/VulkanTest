NAME = VulkanTest
CC = g++
FILES = main.cpp

OBJS = $(addprefix bin/,$(FILES:.cpp=.o))
BIN = bin

VULKAN_SDK_PATH = ~/VulkanSDK/1.0.51.0/x86_64
VULKAN_SDK_INCLUDES = $(VULKAN_SDK_PATH)/include
VULKAN_SDK_LIBS = $(VULKAN_SDK_PATH)/lib

DEPS = -L $(VULKAN_SDK_LIBS)
INCLUDES = -I $(VULKAN_SDK_INCLUDES)

CXXFLAGS = -std=c++11
FLAGS = $(CXXFLAGS) $(INCLUDES)

LDFLAGS = $(DEPS) -lvulkan `pkg-config --static --libs glfw3`

$(NAME):$(BIN) $(OBJS)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LDFLAGS)

all: $(NAME)

$(BIN):
	mkdir -p $(dir $(OBJS))

bin/%.o: srcs/%.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@ $(INCLUDES)

test: all
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d ./VulkanTest

clean:
	rm -rf $(BIN)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re
