#include <iostream>
#include <fstream>
#include "../model_class/model.hpp"

//----------------------------------------------------
//
//						Renderer Class
//	
//----------------------------------------------------

//Copyright: Matt Haywood

/* 

This class will contain the functions for creating a three.js file

//Function to create file start.

//Function to add objects.

//Function to create file end.

*/

class renderer{
private:
	model the_model;

	string filename;

public:
	renderer(model& the_model);									//Constructor
	
	~renderer();												//Destructor

	renderer(const renderer& a);					 			//Copy Constructor

	renderer& operator=(const renderer& a);						//Assignment Operator

	void open_file();				

	void close_file();

	void file_start();

	void file_tetrahedrons();

	void file_hexahedrons();

	void file_pyramids();

	void file_end();
	
};


