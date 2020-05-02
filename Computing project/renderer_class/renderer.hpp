#include <iostream>
#include <fstream>
#include "../model_class/model.hpp"

//----------------------------------------------------
//
//						Renderer Class
//	
//----------------------------------------------------

//Author: Matt Haywood

/// The Renderer class is used to create a renderer using the Three.js visualiser. It will then output a .html file which contains the 3d viewer with the correct objects.

/**
*
*This class will contain the functions for creating a three.js file
*
*Function to create file start.
*
*Function to add objects.
*
*Function to create file end.
*
*/

class renderer{
private:
	model the_model;

	string filename;

	ofstream outfile;

public:
	renderer(model _the_model);								///< Constructor
	
	~renderer();											///< Destructor

	renderer(const renderer& a);					 		///< Copy Constructor

	renderer& operator=(const renderer& a);					///< Assignment Operator

	model& get_model();										///< This function takes in a model object and copies it to the member variable the_model.

	void open_file();										///< This function opens a new file to write the html and JavaScript code to.

	void close_file();										///< This function is used to close the file once the code has been written in. 

	void file_start();										///< This function is used to write some standard HTML code found at the start of the file.

	void file_tetrahedrons();								///< This function is used to write all the JS code for all of the tetrahedrons in the model.

	void file_hexahedrons();								///< This function is used to write all the JS code for all of the hexahedrons in the model.

	void file_pyramids();									///< This is used to write all the JS code for all of the pyramids in the model.

	void file_end();										///< This function is used to write the closing code.
	
};


