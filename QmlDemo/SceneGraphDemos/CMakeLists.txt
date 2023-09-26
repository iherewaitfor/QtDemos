# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(SceneGraphDemos)
#选择64位还是32位的Qt
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Qt6HOMEDIR D:/Qt6/6.6.0/msvc2019_64)
else()
	#to do: install the 32bit qt6
endif()
# 提供位置定位.cmake文件
# set(Qt6_DIR D:/Qt6/6.6.0/msvc2019_64/lib/cmake)
set(Qt6_DIR ${Qt6HOMEDIR}/lib/cmake/Qt6)

# 查找Qt库
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

# QML_IMPORT_PATH = ${Qt5HOMEDIR}/qml

# 设置moc rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(${QtGui_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${QtGui_INCLUDE_DIRS} ${QtQml_DEFINITIONS} ${QtQuick_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(EXAMPLE_TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# Set properties common to all example targets.
macro(SET_EXAMPLE_PROPERTIES target)
  # Output all binaries to the configuration-specific build directory.
  set_target_properties(${target} PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}"
                        RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}"
                        LIBRARY_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}")
endmacro()

add_subdirectory(openglunderqml)
add_subdirectory(d3d11underqml)


