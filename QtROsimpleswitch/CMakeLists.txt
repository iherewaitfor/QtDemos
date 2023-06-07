# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )

# 设置moc rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(Demo)

# aux_source_directory(. DIR_SRCS)

#选择64位还是32位的Qt
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017_64)
else()
	set(Qt5HOMEDIR D:/Qt/Qt5.14.2/5.14.2/msvc2017)
endif()
#只引用Qt5Core写法一
# 提供Qt5位置定位.cmake文件
set(Qt5_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5)
find_package(Qt5 COMPONENTS Core RemoteObjects)

#只引用Qt5Core写法二
#提供Qt5Core库的.cmake文件位置
# set(Qt5Core_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5Core)
# set(Qt5RemoteObjects_DIR ${Qt5HOMEDIR}/lib/cmake/Qt5RemoteObjects)
# find_package(Qt5Core)
# find_package(Qt5RemoteObjects)

add_subdirectory(directconnectserver)
add_subdirectory(directconnectclient)
add_subdirectory(directconnectdynamicclient)
add_subdirectory(registryconnectedserver)
add_subdirectory(registryconnectedclient)
