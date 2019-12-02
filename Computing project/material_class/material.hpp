#include <iostream>
//----------------------------------------------------
//
//						Material Class
//	
//----------------------------------------------------

//Copyright: Matt Haywood

/* This class defines a material, it must hold the following properites:

- ID
- Name
- Colour
- Density

*/


class material
{

private:

//private data
	int ID;	

	std::string name;
	
	std::string colour;
	
	float density;

public:
	
	material(int _ID, std::string _name, std::string _colour, float _density); 	//constructor for when all information is supplied

	material();

	~material();																	//Destructor

	material(const material& a);													//Copy Constructor

	material& operator=(const material& a);											//Assigment Operator

	float getId(); 			 														//Getter

	std::string getName(); 		 													//Getter

	std::string getColour(); 														//Getter
	
	float getDensity(); 	 														//Getter

	void set();																		//Setter
};



