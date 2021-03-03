cmake_minimum_required( VERSION 3.17 )

project( stc C )

add_compile_options( -Wall -Wextra -Wswitch-enum )

add_executable( stc
    src/main.c
    src/compiler.c
    src/labellist.c
    src/parser.c
    src/token.c )
target_link_libraries( stc PRIVATE stlib )
target_include_directories( stc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ )


install( TARGETS stc
    CONFIGURATIONS Release
    DESTINATION /usr/bin/ )