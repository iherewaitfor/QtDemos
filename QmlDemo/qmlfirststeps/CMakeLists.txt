# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(qmlfirststeps)
#选择64位还是32位的Qt
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017_64)
else()
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017)
endif()
# 提供位置定位.cmake文件
# set(Qt5_DIR D:/Qt/Qt5.14.2/5.14.2/msvc2017/lib/cmake/Qt5)
set(Qt5_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5)

# 查找Qt库
find_package(Qt5 COMPONENTS Core Widgets Qml Quick REQUIRED)

# QML_IMPORT_PATH = ${Qt5HOMEDIR}/qml

# 设置moc rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${Qt5Quick_DEFINITIONS})
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

add_subdirectory(helloworld)
add_subdirectory(quickcontrols)
add_subdirectory(handlinguserinput)
add_subdirectory(PropertyBindings)
add_subdirectory(Animations)
add_subdirectory(CustomQmlTypes)
