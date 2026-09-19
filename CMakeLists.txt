cmake_minimum_required(VERSION 3.16)

project(Gimpo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

if(APPLE)

    add_executable(Gimpo MACOSX_BUNDLE 
        ./src/main.cpp
        ./src/paths.cpp
    )

else()

    add_executable(Gimpo
        ./src/main.cpp
        ./src/paths.cpp
    )

endif()

target_link_libraries(Gimpo PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

if(APPLE)

    set_target_properties(Gimpo PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.azmeer.gimpo"
        MACOSX_BUNDLE_BUNDLE_NAME "Gimpo"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    )

endif()

if(APPLE)

    add_custom_command(TARGET Gimpo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_BUNDLE_DIR:Gimpo>/Contents/Resources/Assets"
    )

elseif(WIN32)

    add_custom_command(TARGET Gimpo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Gimpo>/Assets"
    )

elseif(UNIX) 

    add_custom_command(TARGET Gimpo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Gimpo>/Assets"

    )

endif()