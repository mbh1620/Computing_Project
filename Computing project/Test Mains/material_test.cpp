/// \file

#include <iostream>
#include "../material_class/material.hpp"

//----------------------------------------------------
//
//						   Material Test 
//	
//----------------------------------------------------

/*! \author/ Matt Haywood */

int main(){

//Create a material "wood" with density 2700 and color h4h4h4
	material wood = material(1, "wood", "h4h4h4", 2700);

//Test getters
	std::cout << wood.getId() << " \n";
	std::cout << wood.getName() << " \n";
	std::cout << wood.getColour() << " \n";
	std::cout << wood.getDensity() << " \n";

	if( wood.getId() != 1){

		std::cout << "Material Class Error: There is an error in the constructor function";
		return 1;
	} 
	if( wood.getName() != "wood"){
		std::cout << "Material Class Error: There is an error in the constructor function";
		return 1;
	}
	if( wood.getColour() != "h4h4h4" ){
		std::cout << "Material Class Error: There is an error in the constructor function";
		return 1;
	}
	if( wood.getDensity() != 2700 ){ 
		std::cout << "Material Class Error: There is an error in the constructor function";
		return 1;
	}

//Test assignment operator and copy constructor 

	material a = wood;

	std::cout << a.getId() << " \n";
	std::cout << a.getName() << " \n";
	std::cout << a.getColour() << " \n";
	std::cout << a.getDensity() << " \n";

	if( a.getId() != 1){

		std::cout << "Material Class Error: There is an error in the copy constructor function";
		return 1;
	} 
	if( a.getName() != "wood"){
		std::cout << "Material Class Error: There is an error in the copy constructor function";
		return 1;
	}
	if( a.getColour() != "h4h4h4" ){
		std::cout << "Material Class Error: There is an error in the copy constructor function";
		return 1;
	}
	if( a.getDensity() != 2700 ){ 
		std::cout << "Material Class Error: There is an error in the copy constructor function";
		return 1;
	}

	material b;

	b = a;

	std::cout << b.getId() << " \n";
	std::cout << b.getName() << " \n";
	std::cout << b.getColour() << " \n";
	std::cout << b.getDensity() << " \n";

	

	return 0; //Return 0 if all is good 

}