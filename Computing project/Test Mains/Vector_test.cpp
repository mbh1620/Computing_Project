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

	//Test of dot product
	Vector d = Vector(2, 1,2,3);
	Vector e = Vector(3, 6,7,8);

	std::cout << " dot product: " << d.dot(e);



}