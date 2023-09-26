# cmake最低要求
cmake_minimum_required( VERSION 3.1.0 )
project(d3d11underqml)
aux_source_directory(. DIR_SRCS)
file (GLOB QML_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qml" )
file (GLOB RESOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR}
		"*.qrc")
qt_add_resources(QT_RESOURCES ${RESOURCE_FILES})

qt_standard_project_setup()

add_executable(${PROJECT_NAME} ${DIR_SRCS} ${QT_RESOURCES} ${QML_FILES})
SET_EXAMPLE_PROPERTIES(${PROJECT_NAME})

# 链接Qt库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
	d3d11
    d3dcompiler
)

qt_add_qml_module(d3d11underqml
    URI D3D11UnderQML
    QML_FILES
        main.qml
    RESOURCES
        squircle.frag
        squircle.vert
    RESOURCE_PREFIX /scenegraph/d3d11underqml
    NO_RESOURCE_TARGET_PATH
)

# 复制依赖库到对应exe文件
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${Qt6HOMEDIR}/bin/windeployqt.exe --qmldir ${Qt6HOMEDIR}/qml  ${EXAMPLE_TARGET_OUT_DIR}/${PROJECT_NAME}.exe
  )
