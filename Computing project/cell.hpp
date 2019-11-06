#include <sstream>
#include "vector.hpp"
//----------------------------------------------------
//
//						Cell Class
//	
//----------------------------------------------------

//Copryright: Matt Haywood


/* A cell is a shape that is defined by 2 or more vertices (vectors). The following types of
cell may be encountered in the model file:

- Tetrahedron, 4 vertices
- Hexahedron, 8 vertices,
- Pyramid, 5 vertices

A cell object should be able to calculate its own volume

It should also be able to estimate its centre of gravity

It should be able to estimate its weight.
*/



class cell
{

private:

//private data

	std::string shape;

	Vector *vertices;

	string shape;

	float volume;

	float cog;

	float weight;
	

public:

	cell(Vector vertices_in[]); 		//constructor

	cell();

	~cell();							//Destructor

	cell(const cell& a);				//Copy Constructor

	cell& operator=(const cell& a);		//Assigment Operator
	
	weight_calc();						//Function to calculate weight

	cog_calc();							//Function to calculate Center of gravity

	volume_calc();						//Function to calculate volume
};

cell::cell(Vector vertices_in[]){		//Constructor for list of vertices
	vertices = vertices_in;
}

cell::cell(){

}

cell::~cell(){

}

cell::cell(const cell& a){

}

cell& cell:: operator=(const cell& a){

	return *this;
}

cell::weight_calc(){

}

cell::cog_calc(){

}

cell::volume_calc(){
	
}
















