/// \file

#include <sstream>
#include <iostream>

#include "../vector_class/vector.hpp"
//#include "../Volume_of_tetra_function/volume_of_tetra.hpp"
#include "../material_class/material.hpp"
#include <deque>

#include <cmath>



//-----------------------------------------------------------------------------
//
//						Cell Class and Sublasses of Cell
//	
//-----------------------------------------------------------------------------

//Copyright: Matt Haywood

/**
*A cell is a shape that is defined by 2 or more vertices (vectors). The following types of
*cell may be encountered in the model file:
*
*- Tetrahedron, 4 vertices
*- Hexahedron, 8 vertices,
*- Pyramid, 5 vertices
*
*A cell object should be able to calculate its own volume
*
*It should also be able to estimate its centre of gravity
*
*It should be able to estimate its weight.
*/


class cell
{

protected: 
	char shape;

	material cell_material;				//Cell material

	int id;								//unique id

	float volume;						//Volume 


private:

//private data
	
	std::deque<Vector> vertices;					//Array of vector objects

	Vector cog;							//Centre of Gravity

	float weight;						//Weight
	

public:
	//------------------------- standard class functions -----------------------

	cell(std::deque<Vector> vertices_in, material _cell_material); 		//constructor for list of vertices

	cell();								//constructor for 0 values supplied

	~cell();							//Destructor

	cell(const cell& a);				//Copy Constructor

	cell& operator=(const cell& a);		//Assigment Operator

	//-------------------------  getter/setter functions ----------------------
	int getId();

	void setId(int _id);

	void set_material(material _cell_material);

	material get_material();

	char get_shape();

	void set_shape(char _shape);

	float get_volume();					//getter for volume

	void set_volume(float _volume);		//Setter for volume

	Vector get_cog();					//getter for cog

	void set_cog(Vector _cog);			//Setter for COG

	float get_weight();					//getter for weight

	void set_weight(float _weight);		//Setter for weight

	std::deque<Vector> get_vertices();			//getter for the array of vertices

	void set_vertices(std::deque<Vector> _vertices);	//setter for the vertices

	//------------------------ calulation functions --------------------------
	
	virtual float weight_calc();			//Function to calculate weight. Virtual because it may need redefining based on what subclass is used

	virtual Vector cog_calc();			//Function to calculate Center of gravity

	virtual float volume_calc();		//Function to calculate volume
};


//-----------------------------------------------------------------------------
//
//				Sublasses of Cell. Pyramid, Tetrahedron and Hexahedron
//	
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//							Tetrahedron Subclass
//	
//-----------------------------------------------------------------------------

//Function:
/*	
	- Calculate the tetrahedrons weight
	- Calculate the centre of gravity 
	- Calculate the volume 

*/


class tetrahedron : public cell 
{

public:
	tetrahedron(std::deque<Vector> vertices_in, material _cell_material); 		//constructor for list of vertices
	
	float weight_calc();

	Vector cog_calc();

	float volume_calc();

};

//-----------------------------------------------------------------------------
//
//							Pyramid Subclass 
//	
//-----------------------------------------------------------------------------


class pyramid : public cell
{
public:
	pyramid(std::deque<Vector> vertices_in, material _cell_material);

	float weight_calc();

	Vector cog_calc();

	float volume_calc(); 
};

//-----------------------------------------------------------------------------
//
//							Hexahedron Subclass
//	
//-----------------------------------------------------------------------------


class hexahedron : public cell
{
public:
	hexahedron(std::deque<Vector> vertices_in, material _cell_material);

	float weight_calc();

	Vector cog_calc();

	float volume_calc();
};
























