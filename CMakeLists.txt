project(vismed2)
cmake_minimum_required(VERSION 3.1.0)

# add CMakeLists.txt source dir and cmake module dir to the cmake module path
# cmake modules are cmake files used e.g. to find library files
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}"
)

# find moc includes (ui files etc.) in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON) # run qt moc (meta object compiler, expands Q_OBJECT c++ ui header macro)
set(CMAKE_AUTOUIC ON) # run qt uic (ui xml to c++ header file compiler)


### EXTERNAL LIBRARIES ###

find_package(OpenGL REQUIRED)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5UiTools)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5OpenGLExtensions)
find_package(Qt53DCore)
find_package(Qt53DRender)


### SOURCE FILES ###

# relative path to every single h and cpp file
set(SRC_CLASSES
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/glwidget.h
    src/glwidget.cpp
    src/volume.h
    src/volume.cpp
)

# relative path to shader files
set(SRC_SHADERS
    src/shaders/rayvolumeexitposmap_shader.vert
    src/shaders/rayvolumeexitposmap_shader.frag
    src/shaders/raycast_shader.vert
    src/shaders/raycast_shader.frag
)

QT5_WRAP_UI(UI_HEADERS
    src/mainwindow.ui
)

# adds an executable target with given name to be built from the source files listed afterwards
add_executable(${PROJECT_NAME} ${SRC_CLASSES} ${SRC_SHADERS} ${UI_HEADERS})

### INCLUDE HEADER FILES ###
include_directories(
    ${OPENGL_INCLUDE_DIRS}
)

### LINK LIBRARIES ###
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::UiTools
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::OpenGLExtensions
    Qt5::3DCore
    Qt5::3DRender
)
### COPY SHADERS ###

add_custom_target(shaders)

add_custom_command(TARGET shaders PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
)

add_dependencies(${PROJECT_NAME} shaders)
