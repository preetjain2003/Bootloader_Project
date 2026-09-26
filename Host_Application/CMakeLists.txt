cmake_minimum_required(VERSION 3.23)

project(myproject)

add_compile_options("-Wall" "-Wextra" "-Werror")

add_executable(app
        Sources/MxBlcommands.c
        Sources/MxBlreplyprocessing.c 
        Sources/MxFileops.c 
        Sources/MxMain.c 
        Sources/MxUtilities.c 
        Sources/MxWindows_serial_port.c
        )


target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

