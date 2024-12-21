cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME InvasionDefender)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(lib/stb)
target_link_libraries(${PROJECT_NAME} stb)

add_subdirectory(lib/glm)
target_link_libraries(${PROJECT_NAME} glm)

include(CPack)
