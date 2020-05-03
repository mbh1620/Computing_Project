/// \file

#include <iostream>
#include "../cell_class/cell.hpp"

//----------------------------------------------------
//
//						   Cell Test 
//	
//----------------------------------------------------

/*! \author Matt Haywood */


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

	//If the get id does not get 1 then there is an error in the function

	if(a_cell.getId() != 1){
		std::cout << "Cell Class Error: setId function not working";
		return 1;
	}

	a_cell.set_material(wood);

	if(a_cell.get_material() != "wood"){
		std::cout << "Cell Class Error: There is an error in the 'set_material()' function";
		return 1;
	}

	a_cell.get_material();

	if( a_cell.get_shape() != 'n') {
		std::cout << "Cell Class Error: The cell shape has not been defaulted to 'n' ";
		return 1;
	}


	a_cell.set_shape('t');

	if( a_cell.get_shape() != 't') {

		std::cout << "Cell Class Error: There is an error in the set_shape() function";
		return 1;
	}

	a_cell.get_volume();

	a_cell.set_volume(1234);

	if( a_cell.get_volume() != 1234) {
		std::cout << "Cell Class Error: There is an error in the set_volume() function";
		return 1;
	}

	a_cell.get_cog();

	a_cell.set_cog(a);

	a_cell.get_weight();

	a_cell.set_weight(14345);

	if( a_cell.get_weight() != 14345){
		std::cout << "Cell Class Error: There is an error in the set_weight() function";
		return 1;
	}

	a_cell.get_vertices();

	a_cell.set_vertices(vectors);

	a_cell.weight_calc();

	a_cell.cog_calc();

	a_cell.volume_calc();

	
	return 0; //return 0 if all is good 

}