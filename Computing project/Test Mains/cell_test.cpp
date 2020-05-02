/// \file

#include <iostream>
#include "../cell_class/cell.hpp"


int main(){
	
	/*! Test for cell class
		
		- Create some Vectors to pass in to constructor
		- Create a Material to pass in to constructor 
		- Test different functions of a cell

	*/
	//Create some vertices

	Vector a = Vector(0, 1, 2, 3);
	Vector b = Vector(1, 2, 3, 2);
	Vector c = Vector(2, 2, 3, 4);

	//Add these vectors to a deque so they can be passed into the Cell

	std::deque<Vector> vectors;

	vectors.push_back(a);
	vectors.push_back(b);
	vectors.push_back(c);

	//Create a Material 

	material wood = material(0, "Wood", "hexcolorval", 89238);

	//Create a cell

	cell a_cell = cell(vectors, wood);

	//Now we can do tests on cells functions to makesure they are working properly

	a_cell.getId();

	a_cell.setId(1);

	a_cell.set_material(wood);

	a_cell.get_material();

	a_cell.get_shape();

	a_cell.set_shape('t');

	a_cell.get_volume();

	a_cell.set_volume(1234);

	a_cell.get_cog();

	a_cell.set_cog(a);

	a_cell.get_weight();

	a_cell.set_weight(14345);

	a_cell.get_vertices();

	a_cell.set_vertices(vectors);

	a_cell.weight_calc();

	a_cell.cog_calc();

	a_cell.volume_calc();

	
	return 0; //return 0 if all is good 

}