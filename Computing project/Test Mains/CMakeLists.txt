cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

include(CTest)


add_library( 3d_viewer_libs ../cell_class/cell.cpp 
			    ../material_class/material.cpp
			    ../model_class/model.cpp
			    ../vector_class/vector.cpp
			    ../renderer_class/renderer.cpp)


add_executable(test1 ./cell_test.cpp)
add_executable(test1 ./material_test.cpp)
add_executable(test1 ./modeltest.cpp)
add_executable(test1 ./Vector_test.cpp)

target_link_libraries(test1 3d_viewer_libs)
target_link_libraries(test2 3d_viewer_libs)
target_link_libraries(test3 3d_viewer_libs)
target_link_libraries(test4 3d_viewer_libs)

add_test(test1 test1)
add_test(test2 test2)
add_test(test3 test3)
add_test(test4 test4)