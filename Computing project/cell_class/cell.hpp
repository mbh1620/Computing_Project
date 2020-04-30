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

/// The Cell Class is used to create a pyramid, tetrahedron or hexahedron.

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
	char shape;							///< Shape 't','p' or 'h' corresponds to tetrahedron, pyramid or hexahedron. 

	material cell_material;				///< Cell material

	int id;								///< Unique id

	float volume;						///< Volume 


private:

//private data
	
	std::deque<Vector> vertices;		///< Array of vector objects

	Vector cog;							///< Centre of Gravity

	float weight;						///< Weight
	

public:
	//------------------------- standard class functions -----------------------

	cell(std::deque<Vector> vertices_in, material _cell_material); 		///< Constructor for list of vertices

	cell();																///< constructor for 0 values supplied

	~cell();															///< Destructor

	cell(const cell& a);												///< Copy Constructor

	cell& operator=(const cell& a);										///< Assigment Operator

	//-------------------------  getter/setter functions ----------------------
	int getId();														///< Getter function for cell id

	void setId(int _id);												///< Setter function for cell id

	void set_material(material _cell_material);							///< Set the material of the cell 

	material get_material();											///< Get the material of the cell

	char get_shape();													///< Get the shape of the cell

	void set_shape(char _shape);										///< Set the shape of the cell with 't','p' or 'h'.

	float get_volume();													///<getter for volume

	void set_volume(float _volume);										///<Setter for volume

	Vector get_cog();													///<getter for cog

	void set_cog(Vector _cog);											///<Setter for COG

	float get_weight();													///<getter for weight

	void set_weight(float _weight);										///<Setter for weight

	std::deque<Vector> get_vertices();									///<getter for the array of vertices

	void set_vertices(std::deque<Vector> _vertices);					///<setter for the vertices

	//------------------------ calulation functions --------------------------
	
	virtual float weight_calc();										///<Function to calculate weight. Virtual because it may need redefining based on what subclass is used.

	virtual Vector cog_calc();											///<Function to calculate Center of gravity

	virtual float volume_calc();										///<Function to calculate volume
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
/// The Tetrahedron class is a subclass of cell and contains the correct functions for a Tetrahedron shape.
/**	
*	Tetrahedron Subclass
*
*	- Calculate the tetrahedrons weight
*	- Calculate the centre of gravity 
*	- Calculate the volume 
*
*/


class tetrahedron : public cell 
{

public:
	tetrahedron(std::deque<Vector> vertices_in, material _cell_material); 		///< constructor Tetrahedron
	
	float weight_calc();														///< Weight calc redefined because weight of tetrahedron will different.

	Vector cog_calc();															///< Center of Gravity redefined because the centroid of a tetrahedron is different.

	float volume_calc();														///< Volume function redefined because the volume of a tetrahedron is different.

};

//-----------------------------------------------------------------------------
//
//							Pyramid Subclass 
//	
//-----------------------------------------------------------------------------

/// The Pyramid class is a subclass of the Cell Class and contains the correct functions for a Pyramid shape.

class pyramid : public cell
{
public:										
	pyramid(std::deque<Vector> vertices_in, material _cell_material);			///< Constructor for Pyramid 

	float weight_calc();														///< weight calculation redefined because it will be different.

	Vector cog_calc();															///< Centre of Gravity for a Pyramid will be different.

	float volume_calc(); 														///< Volume of Pyramid will be different.
};

//-----------------------------------------------------------------------------
//
//							Hexahedron Subclass
//	
//-----------------------------------------------------------------------------

/// The Hexahedron class is a subclass of the cell class and contains all the correct functions for a Hexahedron shape.

class hexahedron : public cell
{
public:
	hexahedron(std::deque<Vector> vertices_in, material _cell_material);		///< Constructor for Hexahedron

	float weight_calc();														///< Weight calculation redefined because it will be different for a Hexahedron.

	Vector cog_calc();															///< Centre of Gravity redefined because it will be different for a Hexahedron.

	float volume_calc();														///< Volume calculation redefined because it will be different for a Hexahedron.
};
























