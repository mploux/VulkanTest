cmake_minimum_required(VERSION 3.5.1)
project(VulkanTest)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")

set(VULKAN_SDK_PATH "$ENV{HOME}/VulkanSDK/1.0.51.0/x86_64")
set(VULKAN_SDK_LIBS "${VULKAN_SDK_PATH}/lib/")
set(VULKAN_SDK_INCLUDES "${VULKAN_SDK_PATH}/include")

add_executable(
        VulkanTest
        srcs/main.cpp
        srcs/vulkan_system/vulkan_instance.cpp
        srcs/vulkan_system/validation_layers.cpp
        srcs/game.cpp
        includes/vulkan_system/utils.h)

add_library(vulkan SHARED IMPORTED)
set_property(TARGET vulkan PROPERTY IMPORTED_LOCATION ${VULKAN_SDK_LIBS}/libvulkan.so)


include_directories(includes/ ${VULKAN_SDK_INCLUDES} ${GLFW3_INCLUDE_DIRS})

target_link_libraries(VulkanTest vulkan glfw3)
