cmake_minimum_required( VERSION 3.17 )

project( staple C )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_INSTALL_RPATH /usr/local/lib )

add_subdirectory( shared )
add_subdirectory( vm )
add_subdirectory( compiler )
