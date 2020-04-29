#Cmake lists to run the tests for Travis on 

include(CTest)

add_library( 3d_viewer_libs ../cell_class/cell.cpp 
			    ../material_class/material.cpp
			    ../model_class/model.cpp
			    ../vector_class/vector.cpp
			    ../renderer_class/renderer.cpp)


#Add tests and test executables here 

add_executable(test1 ./Test\ Mains/cell_test.cpp)
add_executable(test2 ./Test\ Mains/material_test.cpp)
add_executable(test3 ./Test\ Mains/model_test.cpp)
add_executable(test4 ./Test\ Mains/Vector_test.cpp)

target_link_libraries(test1 3d_viewer_libs)
target_link_libraries(test2 3d_viewer_libs)
target_link_libraries(test3 3d_viewer_libs)
target_link_libraries(test4 3d_viewer_libs)

add_test(test1 3d_viewer_libs)
add_test(test2 3d_viewer_libs)
add_test(test3 3d_viewer_libs)
add_test(test4 3d_viewer_libs)

