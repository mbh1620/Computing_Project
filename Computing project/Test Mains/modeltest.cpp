/// \file

#include <iostream>
#include "../model_class/model.hpp"


//----------------------------------------------------
//
//						   Model Test
//	
//----------------------------------------------------

/*! \author Matt Haywood */


using namespace std;

int main(){
	model model1 = model();

	model1.readInFile("new.txt");
 
	cout << "vertex num: " << model1.get_vertex_num() << "\n";
	cout << "cell num: " << model1.get_cell_num() << "\n";

	if(model1.get_vertex_num() != 4){
		std::cout << "Model Class Error: There is an error in the readInFile() function when it reads in vectors";
		return 1;
	}

	if(model1.get_cell_num() != 1){
		std::cout << "Model Class Error: There is an error in the readInFile() function where it reads in cells";
		return 1;
	}

	if(model1.get_material_num() != 1){
		std::cout << "Model Class Error: There is an error in the readInFile() function where it reads in materials";
		return 1;
	}

	int *array = model1.get_cell_type();

	cout << "num of tetrahedrons: " << array[0] << "\n" ;
	cout << "num of pyramids: " << array[1] << "\n";
	cout << "num of hexahedrons: " << array[2] << "\n";
	
	model1.saveNewFile("newfile.txt");

}