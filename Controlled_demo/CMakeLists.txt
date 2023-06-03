cmake_minimum_required(VERSION 3.15)

project(demo LANGUAGES CXX)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
 find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)

add_executable(appdemo)

target_sources(appdemo
    PRIVATE
        main.cpp
        controlled.cpp
        controlled.h
        systemapi.h
        systemapi.cpp
        socket.h
        socket.cpp
        protocol.h
        protocol.cpp
        virtualmouse.h
        virtualmouse.cpp
        remoteevent.h
    PUBLIC
        
)

qt_add_qml_module(appdemo
    URI demo
    VERSION 1.0
    QML_FILES Main.qml
)

target_compile_features(appdemo PRIVATE cxx_std_20)

target_link_libraries(appdemo
    PRIVATE 
        Qt6::Quick
        Qt6::Widgets
)






# set_target_properties(appdemo PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# install(TARGETS appdemo
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
