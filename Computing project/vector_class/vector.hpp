#include <iostream>

//------------------------------------------------------------------------------------//
//
//									Vector Class
//
//------------------------------------------------------------------------------------//


/*! \author Matt Haywood */

///The Vector class is used to hold the x,y and z values for a point. It also holds the value for the id of the point.

/**
*	Vector Class:
*
*	- Must be able to store 3D vectors
*	- Contains suitable constructors, destructors, accessors and mutators
*	- Perform basic vector operations such as:
*		- Addition
*		- Subtraction
*		- Inner/scalar product also called dot product
*		- Outer/vector product (final two are important for volume calculations) also called cross product
*/




class Vector
{
private: 
												//private data
	int id;
	float x;
	float y;
	float z;

public:

	Vector();									///< Constructor for when no values of the vector are supplied

	Vector(int id, float x, float y, float z);	///< Constructor for when all 3 values of the vector are supplied

	~Vector();									///< Destructor not required as no dynamic memory is allocated

	Vector(const Vector& a);					///< Copy Constructor

	Vector& operator=(const Vector& a);			///< Assignment Operator

	Vector& operator+(const Vector& a);			///< Addition Operator

	Vector& operator-(const Vector& a);			///< Subtraction Operator

	float get(char d);							///< Getters get_value(x,y or z)

	void set(char d, float value);				///< Setter set_value(x,y or z, value to change to)

	float dot(const Vector& a);					///< Performs the dot product 

	Vector& cross(const Vector& b);				///< Performs the cross product 

};






