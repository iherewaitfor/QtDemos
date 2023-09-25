# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(coffee)
aux_source_directory(. DIR_SRCS)
file (GLOB QML_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qml" "*content/*.qml" "*content/*.js")
file (GLOB RESOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qrc")
qt5_add_resources(QT_RESOURCES ${RESOURCE_FILES})


add_executable(${PROJECT_NAME} ${DIR_SRCS} ${QT_RESOURCES} ${QML_FILES})
SET_EXAMPLE_PROPERTIES(${PROJECT_NAME})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt5HOMEDIR}/bin/windeployqt.exe --qmldir ${Qt5HOMEDIR}/qml  ${EXAMPLE_TARGET_OUT_DIR}/${PROJECT_NAME}.exe
  )