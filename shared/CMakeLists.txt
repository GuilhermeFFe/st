cmake_minimum_required( VERSION 3.17 )

project( stlib C )

add_library( stlib SHARED
    src/bytebuffer.c
    src/util.c
    src/registerid.c )

target_include_directories( stlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ )

install( TARGETS stlib
    CONFIGURATIONS Release
    DESTINATION /usr/local/lib/ )