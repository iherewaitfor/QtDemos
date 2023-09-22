# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(Demo)
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
aux_source_directory(. DIR_SRCS)
file (GLOB RESOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qrc")
qt5_add_resources(QT_RESOURCES qml.qrc)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${Qt5Quick_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


add_executable(${PROJECT_NAME} ${DIR_SRCS} ${QT_RESOURCES} ${RESOURCE_FILES})
# 添加可执行文件，注意添加WIN32，否则有一个控制台黑框
#add_executable(${PROJECT_NAME} WIN32 ${DIR_SRCS})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt5HOMEDIR}/bin/windeployqt.exe  ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/${PROJECT_NAME}.exe
  )