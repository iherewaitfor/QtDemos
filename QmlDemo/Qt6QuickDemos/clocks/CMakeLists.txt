# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(clocks)
aux_source_directory(. DIR_SRCS)
file (GLOB QML_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qml" "content/*.qml" "content/*.png" )
file (GLOB RESOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qrc")
qt_add_resources(QT_RESOURCES ${RESOURCE_FILES})

qt_standard_project_setup()

add_executable(${PROJECT_NAME} ${DIR_SRCS} ${QT_RESOURCES} ${QML_FILES})
SET_EXAMPLE_PROPERTIES(${PROJECT_NAME})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::GuiPrivate
    Qt6::Qml
    Qt6::Quick
)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt6HOMEDIR}/bin/windeployqt.exe --qmldir ${Qt6HOMEDIR}/qml  ${EXAMPLE_TARGET_OUT_DIR}/${PROJECT_NAME}.exe
  )
