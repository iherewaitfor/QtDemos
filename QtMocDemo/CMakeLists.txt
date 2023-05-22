# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )

# 设置moc rcc uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(Demo)

aux_source_directory(. DIR_SRCS)

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
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 添加可执行文件，注意添加WIN32，否则有一个控制台黑框
add_executable(${PROJECT_NAME}
WIN32
${DIR_SRCS}
)

# 链接Qt库
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt5HOMEDIR}/bin/windeployqt.exe  ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/${PROJECT_NAME}.exe
  )