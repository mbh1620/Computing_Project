//------------------------------------------------------------------------------------//
//
//									Vector Class
//
//------------------------------------------------------------------------------------//


//Copyright: Matt Haywood

/*
	Vector Class:

	- Must be able to store 3D vectors
	- Contains suitable constructors, destructors, accessors and mutators
	- Perform basic vector operations such as:
		- Addition
		- Subtraction
		- Inner/scalar product
		- Outer/vector product (final two are important for volume calculations)
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

	Vector();									// Constructor for when no values of the vector are supplied

	Vector(int id, float x, float y, float z);			// Constructor for when all 3 values of the vector are supplied

	~Vector();									// Destructor not required as no dynamic memory is allocated

	Vector(const Vector& a);					// Copy Constructor

	Vector& operator=(const Vector& a);			// Assignment Operator

	Vector& operator+(const Vector& a);			// Addition Operator

	Vector& operator-(const Vector& a);			// Subtraction Operator

	float get(char d);							// Getters get_value(x,y or z)

	void set(char d, float value);				// Setter set_value(x,y or z, value to change to)

	float dot(const Vector& a);					// Performs the dot product 

	float outer(const Vector& b);				// Performs the outer product 

	//Things to add 
	//				-- INNER/SCALAR PRODUCT FUNCTION
	//				-- OUTER/VECTOR PRODUCT FUNCTION
};

Vector::Vector(){
	id = 0;
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(int _id, float _x, float _y, float _z){
	id = _id;
	x = _x;
	y = _y;
	z = _z;
}

Vector::~Vector(){

}

Vector::Vector(const Vector& a){
	id = a.id;
	x = a.x;
	y = a.y;
	z = a.z;
}

Vector& Vector:: operator=(const Vector& a){
	id = a.id;
	x = a.x;
	y = a.y;
	z = a.z;

	return *this;
}

Vector& Vector:: operator+(const Vector& a){

	x = x + a.x;
	y = y + a.y;
	z = z + a.z;

	return *this;
} 

Vector& Vector:: operator-(const Vector& a){
	x = x - a.x;
	y = y - a.y;
	z = z - a.z;

	return *this;
}

float Vector::get(char d){
	if (d == 'x'){
		return x;
	} else if( d == 'y'){
		return y;
	} else if( d == 'z'){
		return z;
	} else {
		return 0;
	}
}

void Vector::set(char d, float value){
	if (d == 'x'){
		x = value;
	} else if( d == 'y'){
		y = value;
	} else if( d == 'z'){
		z = value;
	} else {
		
	}
}

float Vector::dot(const Vector& a){
	
	float dotx = x * a.x;
	float doty = y * a.y;
	float dotz = z * a.z;
	float sum = dotx + doty + dotz; 

	return sum;
} 




