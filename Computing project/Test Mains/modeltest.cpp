/// \file

#include <iostream>
#include "../model_class/model.hpp"


//----------------------------------------------------
//
//						   Model Test
//	
//----------------------------------------------------

//Author: Matt Haywood


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

}