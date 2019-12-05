#include <iostream>
#include "renderer_class/renderer.hpp"


using namespace std;

int main(){
	model model1 = model();

	model1.readInFile("input_file.txt");


 
	cout << "vertex num: " << model1.get_vertex_num() << "\n";
	cout << "cell num: " << model1.get_cell_num() << "\n";

	int *array = model1.get_cell_type();

	cout << "num of tetrahedrons: " << array[0] << "\n" ;
	cout << "num of pyramids: " << array[1] << "\n";
	cout << "num of hexahedrons: " << array[2] << "\n";
	
	model1.saveNewFile("output_file.txt");

	renderer renderer1 = renderer(model1);
	
	renderer1.open_file();

	renderer1.file_start();

	renderer1.file_tetrahedrons();

	renderer1.file_hexahedrons();

	renderer1.file_pyramids();

	renderer1.file_end();

	renderer1.close_file();

}