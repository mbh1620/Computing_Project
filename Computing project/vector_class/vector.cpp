#include "vector.hpp"
#include <iostream>

//----------------------------------------------------
//
//						Vector Class Implementation 
//	
//----------------------------------------------------

//Author: Matt Haywood

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
	} else if( d == 'i'){
		return id;
	}else{
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

	/*! Dot product of a(x,y,z) and b(x,y,z) = 
		(ax * bx) + (ay * by) + (az * bz)

	*/
	
	float dotx = x * a.x;
	float doty = y * a.y;
	float dotz = z * a.z;
	float sum = dotx + doty + dotz; 

	return sum;
}

Vector& Vector::cross(const Vector& b){

	/*! cross product of a(x,y,z) and b(x,y,z) = 

	cx = aybz - azby
	cy = azbx - axbz
	cz = axby - aybx
	
	*/

	static Vector answer = Vector();

	answer.x = (y * b.z) - (z * b.y);
	answer.y = (z * b.x) - (x*b.z);
	answer.z = (x * b.y) - (y*b.x);

	return answer;

}
