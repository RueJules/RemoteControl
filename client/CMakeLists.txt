cmake_minimum_required(VERSION 3.25)

project(untitled2 LANGUAGES CXX)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)

add_executable(appuntitled2)

target_sources(appuntitled2
    PRIVATE
        main.cpp
        socket.h
        socket.cpp
        #client.h
        #client.cpp
        inputclient.cpp
        inputclient.h
        outputclient.cpp
        outputclient.h
        #iodevice.h
        #iodevice.cpp
        
    PUBLIC
        
)

qt_add_qml_module(appuntitled2
    URI untitled2
    VERSION 1.0
    QML_FILES Main.qml
)

target_compile_features(appuntitled2 PRIVATE cxx_std_20)

target_link_libraries(appuntitled2
    PRIVATE 
        Qt6::Quick
        Qt6::Multimedia
)






# set_target_properties(appuntitled2 PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# install(TARGETS appuntitled2
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
