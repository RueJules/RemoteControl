cmake_minimum_required(VERSION 3.16)

project(Controlled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets)
find_package(Qt6 6.4 REQUIRED COMPONENTS Multimedia)
qt_standard_project_setup()

set(SOURCES
    controlled.h
    controlled.cpp    
    systemapi.h
    systemapi.cpp
    socket.h
    socket.cpp
    protocol.h
    protocol.cpp
    virtualmouse.h
    virtualmouse.cpp
    remoteevent.h
    inputserver.h
    inputserver.cpp
    outputserver.h
    outputserver.cpp  
)
set(QMLFILES
    Main.qml
   # MyButton.qml
)

qt6_add_resources(RESOURCE_FILES
   
)

qt_add_executable(appControlled
    main.cpp
    ${SOURCES}
    ${RESOURCE_FILES}
)

qt_add_qml_module(appControlled
    URI Controlled
    VERSION 1.0
    QML_FILES
    ${QMLFILES}
)

set_target_properties(appControlled PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appControlled
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::Multimedia
)

install(TARGETS appControlled
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
