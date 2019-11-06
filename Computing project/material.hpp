//----------------------------------------------------
//
//						Material Class
//	
//----------------------------------------------------

//Copryright: Matt Haywood

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
	float ID;
	const char *name;
	const char *colour;
	float density;

public:
	
	material(float _ID, const char *_name, const char *_colour, float _density); 	//constructor for when all information is supplied

	~material();						//Destructor

	material(const material& a);		//Copy Constructor

	material& operator=(const material& a);	//Assigment Operator

	float getId(); 			 		//Getter
	const char* getName(); 		 	//Getter
	const char* getColour(); 		//Getter
	float getDensity(); 	 		//Getter

	void set();						//Setter
};


material::material(float _ID, const char *_name, const char *_colour, float _density){
	ID = _ID;
	name = _name;
	colour = _colour;
	density = _density;
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

const char* material::getName(){
	return name;
}

const char* material::getColour(){
	return colour;
}

float material::getDensity(){
	return density;
}

