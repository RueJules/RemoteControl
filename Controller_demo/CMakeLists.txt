cmake_minimum_required(VERSION 3.25)

project(Control_demo LANGUAGES CXX)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)

add_executable(appControl_demo)

target_sources(appControl_demo
    PRIVATE
        main.cpp
        controller.h
        controller.cpp
        imageprovider.cpp
        imageprovider.h
        protocol.h
        protocol.cpp
        socket.cpp
        socket.h
        remoteevent.h
    PUBLIC
        
)

qt_add_qml_module(appControl_demo
    URI Control_demo
    VERSION 1.0
    QML_FILES Main.qml
)

target_compile_features(appControl_demo PRIVATE cxx_std_20)

target_link_libraries(appControl_demo
    PRIVATE 
        Qt6::Quick
)






# set_target_properties(appControl_demo PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# install(TARGETS appControl_demo
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
