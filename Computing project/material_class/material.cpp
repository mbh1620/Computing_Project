#include "material.hpp"
#include <iostream>

//----------------------------------------------------
//
//						Material Class Implementation
//	
//----------------------------------------------------

// author Matt Haywood 

material::material(int _ID, std::string _name, std::string _colour, float _density){
	ID = _ID;
	name = _name;
	colour = _colour;
	density = _density;
}

material::material(){

}

material::~material(){

}

material::material(const material& a){
	ID = a.ID;
	name = a.name;
	colour = a.colour;
	density = a.density;
}

material& material:: operator=(const material& a){
	ID = a.ID;
	name = a.name;
	colour = a.colour;
	density = a.density;

	return *this;
}

float material::getId(){
	return ID;
}

std::string material::getName(){
	return name;
}

std::string material::getColour(){
	return colour;
}

float material::getDensity(){
	return density;
}

