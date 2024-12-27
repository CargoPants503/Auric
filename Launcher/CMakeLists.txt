cmake_minimum_required(VERSION 3.15)

project(
	AuricLauncher
	DESCRIPTION "Private servers for STAR WARS Battlefront 2015"
	HOMEPAGE_URL "https://github.com/CargoPants503/Auric"
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
        ${CMAKE_SOURCE_DIR}/Source/Public/Render/Fonts
)
include_directories(SYSTEM INTERFACE
        ${CMAKE_SOURCE_DIR}/Libraries/Include
        ${PROJECT_SOURCE_DIR}/Libraries/Include
)

file(GLOB_RECURSE INCLUDE_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/Libraries/Sources/*.cpp
        ${PROJECT_SOURCE_DIR}/Libraries/Sources/*.cpp
)

add_executable(AuricLauncher WIN32 Main.cpp ${INCLUDE_SOURCES} "Libraries/Images/resource.rc")

set_target_properties(AuricLauncher PROPERTIES LINK_FLAGS "/ignore:4098")
set(LAUNCHER_BINARIES_DIR ${PROJECT_SOURCE_DIR}/Libraries/Binaries)
set(KYBER_BINARIES_DIR ${CMAKE_SOURCE_DIR}/Libraries/Binaries)
target_link_libraries(
    AuricLauncher
    ${LAUNCHER_BINARIES_DIR}/glfw3.lib
    ${LAUNCHER_BINARIES_DIR}/OpenGL32.lib
    ${KYBER_BINARIES_DIR}/libcrypto_static.lib
    ${KYBER_BINARIES_DIR}/libssl_static.lib
)