cmake_minimum_required(VERSION 3.25)

project(Controlled LANGUAGES CXX)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)

add_executable(appControlled)

target_sources(appControlled
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

qt_add_qml_module(appControlled
    URI Controlled
    VERSION 1.0
    QML_FILES Main.qml
)

target_compile_features(appControlled PRIVATE cxx_std_20)

target_link_libraries(appControlled
    PRIVATE 
        Qt6::Quick
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
