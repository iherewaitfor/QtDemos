# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )

# 设置moc rcc
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

project(registryconnected_objects_server)

aux_source_directory(. DIR_SRCS)
include_directories(${PROJECT_BINARY_DIR})# repc生成的文件在这个目录

# qt5_generate_repc宏定义在文件${Qt5HOMEDIR}\lib\cmake\Qt5RemoteObjects\Qt5RemoteObjectsMacros.cmake
# qt5_generate_repc outfiles infile outputtype
# 服务器这边outputtype使用SOURCE
#qt5_generate_repc(DIR_SRCS simpleswitch.rep SOURCE)

add_executable(${PROJECT_NAME} ${DIR_SRCS} )
# 添加可执行文件，注意添加WIN32，否则有一个控制台黑框
#add_executable(${PROJECT_NAME} WIN32 ${DIR_SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES
					ARCHIVE_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}"
					RUNTIME_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}"
					LIBRARY_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}")

# 链接Qt库
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::RemoteObjects)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt5HOMEDIR}/bin/windeployqt.exe  ${TARGET_OUT_DIR}/${PROJECT_NAME}.exe
  )