cmake_minimum_required(VERSION 3.16)

project(Controller VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup()

set(SOURCES
    controller.h
    controller.cpp
    imageprovider.h
    imageprovider.cpp
    protocol.h
    protocol.cpp
    socket.h
    socket.cpp
    remoteevent.h
    keythread.h
    keythread.cpp
    inputclient.h
    inputclient.cpp
    outputclient.h
    outputclient.cpp
)

set(QMLFILES
    Main.qml
    MyButton.qml
)

qt6_add_resources(RESOURCE_FILES
   resource.qrc
)

qt_add_executable(appController
    main.cpp
    ${SOURCES}
    ${RESOURCE_FILES}
)

qt_add_qml_module(appController
    URI Controller
    VERSION 1.0
    QML_FILES
    ${QMLFILES}
)

set_target_properties(appController PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appController
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::Multimedia
)

install(TARGETS appController
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
