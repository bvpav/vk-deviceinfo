cmake_minimum_required(VERSION 3.10)
project(VulkanDeviceInfo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan package
find_package(Vulkan REQUIRED)

# Add executable with the new name
add_executable(vk-deviceinfo main.cpp)

# Link Vulkan library
target_link_libraries(vk-deviceinfo PRIVATE Vulkan::Vulkan)
