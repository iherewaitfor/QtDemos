# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
# 优先设置项目名字
project(Demo)

# 设置rcc
set(CMAKE_AUTORCC ON)
#选择64位还是32位的Qt
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017_64)
else()
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017)
endif()
#只引用Qt5Core写法一
# 提供Qt5位置定位.cmake文件
# set(Qt5_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5)
# find_package(Qt5 COMPONENTS Core)

#只引用Qt5Core写法二
#提供Qt5Core库的.cmake文件位置
set(Qt5Core_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5Core)
find_package(Qt5Core)


aux_source_directory(. DIR_SRCS)
file (GLOB HEADERS
		"*.h")
# 需要执行moc的头文件列表
set(MOC_HEADERS ${HEADERS})
# 可以排除某些头文件不执行moc
list(REMOVE_ITEM MOC_HEADERS ${PROJECT_SOURCE_DIR}/autosignalsemitter.h)

# qt5_wrap_cpp宏定义，位于Qt5CoreMacros.cmake
# qt5_wrap_cpp(outfiles inputfile ... )
qt5_wrap_cpp(mocfiles ${MOC_HEADERS})
#message(NOTICE "DIR_SRCS  ${DIR_SRCS}")
#message(NOTICE "HEADERS  ${HEADERS}")

add_executable(${PROJECT_NAME} ${DIR_SRCS} ${mocfiles} ${HEADERS})
# 添加可执行文件，注意添加WIN32，否则有一个控制台黑框
#add_executable(${PROJECT_NAME} WIN32 ${DIR_SRCS})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} Qt5::Core)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt5HOMEDIR}/bin/windeployqt.exe  ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/${PROJECT_NAME}.exe
  )