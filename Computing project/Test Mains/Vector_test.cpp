/// \file 

#include <iostream>
#include "../vector_class/vector.hpp"



//----------------------------------------------------
//
//						  Vector Test
//	
//----------------------------------------------------

/*! \author Matt Haywood*/

int main(){
	
	//Test of Cross Product
	Vector a = Vector(0, 2, 3, 4);
	Vector b = Vector(1, 5, 6, 7);

	Vector c = a.cross(b);

	std::cout << c.get('x') << " " << c.get('y') << " " << c.get('z');

	if( c.get('x') != -3){
		std::cout << "Vector Class Error: There is an error with the cross product in the x term";
		return 1;
	}
	if( c.get('y') != 6){
		std::cout << "Vector Class Error: There is an error with the cross product in the y term";
		return 1;
	}
	if( c.get('z') != -3){
		std::cout << "Vector Class Error: There is an error with the cross product in the z term";
		return 1;
	}


	Vector d = Vector(2, 1,2,3);
	Vector e = Vector(3, 6,7,8);

	std::cout << " dot product: " << d.dot(e);

	//Test of cross product

	float f = d.dot(e);

	if(f != 6 + 14 + 24){
		std::cout << "Vector Class Error: There is an error with the dot product function";
		return 1;
	}

}