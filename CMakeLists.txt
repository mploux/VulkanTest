cmake_minimum_required(VERSION 3.5.1)
project(VulkanTest)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

add_executable(
        VulkanTest
        srcs/main.cpp
        srcs/vulkan_system/vulkan_instance.cpp
        srcs/vulkan_system/validation_layers.cpp
        srcs/game.cpp
        includes/vulkan_system/utils.h)

set(VULKAN_SDK_PATH ~/VulkanSDK/1.0.51.0/x86_64)
set(VULKAN_SDK_LIBS ${VULKAN_SDK_PATH}/lib)
set(VULKAN_SDK_INCLUDES ${VULKAN_SDK_PATH}/include)

link_directories(${VULKAN_SDK_LIBS})
include_directories(includes/ ${VULKAN_SDK_INCLUDES} ${GLFW3_INCLUDE_DIRS})

target_link_libraries(VulkanTest vulkan ${GLFW3_LIBRARIES})
