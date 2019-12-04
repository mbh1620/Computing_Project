#include <iostream>
#include "renderer_class/renderer.hpp"


using namespace std;

int main(){
	model model1 = model();

	model1.readInFile("new.txt");
 
	cout << "vertex num: " << model1.get_vertex_num() << "\n";
	cout << "cell num: " << model1.get_cell_num() << "\n";

	int *array = model1.get_cell_type();

	cout << "num of tetrahedrons: " << array[0] << "\n" ;
	cout << "num of pyramids: " << array[1] << "\n";
	cout << "num of hexahedrons: " << array[2] << "\n";
	
	model1.saveNewFile("newfile.txt");

	model model2 = model1;

	cout << "cell num: " << model1.get_cell_num() << "\n";

	cout << model1.get_list_of_cells()[0].get_vertices()[2].get('x');
	cout << model1.get_list_of_cells()[0].get_vertices()[2].get('y');
	cout << model1.get_list_of_cells()[0].get_vertices()[2].get('z');
	


	


	renderer renderer1 = renderer(model1);

	

	renderer1.open_file();

	renderer1.file_start();

	renderer1.file_tetrahedrons();

	renderer1.file_end();

	renderer1.close_file();

}