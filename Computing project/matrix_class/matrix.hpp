//------------------------------------------------------------------------------------//
//
//									Matrix Class
//
//------------------------------------------------------------------------------------//


//Copyright: Matt Haywood

/*
	Matrix class:
	This would be able to store data for a 3x3 matrix
	You'll probably want a range of constructors to initialise different standard matrix types.
	It would implement basic matrix operations such as:
		- Addition
		- Subtraction
		- Multiplication
		- Inversion
		- Transpose
	An ability to initialise/set a rotation matrix.
	
	Array types
	
	3x3

	{(1,2,3)
	 (4,5,6)
	 (7,8,9)}
	
	3x2
	3x1

	2x3
	2x2
	2x1

	1x3
	1x2
	1x1
*/

class matrix
{
private: 
//private data
	float *data;

public:

	matrix();									// Constructor
	
	matrix(int first, int second_dimension, float data[]);	//a x b sized array

	~matrix();									// Destructor

	matrix(const matrix& a);					// Copy Constructor

	matrix& operator=(const matrix& a);			// Assignment Operator

};

matrix::matrix(int first, int second_dimension, float data[]){
	data = new float[first][second_dimension];


}

