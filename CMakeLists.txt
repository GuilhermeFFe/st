cmake_minimum_required( VERSION 3.17 )

project( staple C )

add_executable( staple
    src/main.c
    src/util.c
    src/parser.c
    src/token.c
    src/compiler.c
    src/bytebuffer.c
    src/runtime.c )
include_directories( staple ${PROJECT_SOURCE_DIR}/include/ )
