cmake_minimum_required(VERSION 3.7)

#POGEngine is dll of game engine
set(NAME POGEngine)

set(CMAKE_CXX_STANDARD 20)

#dll has to be in same directory as exe, so both output to bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Vulkan is, of course, required
find_package(Vulkan REQUIRED)

#Make a variable with all source files and one with headers
set(SOURCES platform/platform.cpp core/logger.cpp engine.cpp renderer/vulkanRenderer.cpp  )
set(HEADERS defines.h platform/platform.h core/logger.h engine.h renderer/vulkanRenderer.h
        renderer/vulkanAssets.h)

#Make dll
add_library(${NAME} SHARED ${SOURCES} ${HEADERS})

#Set POG_EXPORT for __declspec(dllexport)
target_compile_definitions(${NAME} PUBLIC POG_EXPORT)

#Set for debug build vs release
target_compile_definitions(${NAME} PUBLIC _DEBUG)

#Target is currently windows, can come back later and add
#logic to handle platform selection
target_compile_definitions(${NAME} PUBLIC POG_PLATFORM_WINDOWS)

#Now include and link Vulkan
target_include_directories(${NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${NAME} ${Vulkan_LIBRARY})





