
cmake_minimum_required( VERSION 2.8 ) 
project( 3d_viewer )
add_library( 3d_viewer_libs ./cell_class/cell.cpp 
					   ./material_class/material.cpp
					   ./model_class/model.cpp
					   ./vector_class/vector.cpp
					   ./renderer_class/renderer.cpp)

add_executable( 3d_viewer main.cpp)

target_link_libraries( 3d_viewer 3d_viewer_libs)
