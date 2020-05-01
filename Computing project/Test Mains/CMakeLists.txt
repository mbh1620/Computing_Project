include(CTest)


add_library( 3d_viewer_libs ../cell_class/cell.cpp 
			    ../material_class/material.cpp
			    ../model_class/model.cpp
			    ../vector_class/vector.cpp
			    ../renderer_class/renderer.cpp)


add_executable(test1 ./Test\ Mains/Vector_test.cpp)

target_link_libraries(test1 3d_viewer_libs)

add_test(test1 test1)