cmake_minimum_required( VERSION 3.17 )

project( stvm C )

add_compile_options( -Wall -Wextra -Wswitch-enum )

add_executable( stvm
    src/main.c
    src/runtime.c
    src/registers.c )
target_link_libraries( stvm PRIVATE stlib )
target_include_directories( stvm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ )

install( TARGETS stvm
    CONFIGURATIONS Release
    DESTINATION /usr/bin/ )