/// \file

#include <fstream>
#include <sstream>
#include <iostream>
//#include "material.hpp" <---- included in cell.cpp
//#include "vector.hpp" <---- included in cell.cpp
#include "../cell_class/cell.hpp"
#include <deque>
#include <typeinfo>
#include <string>


//----------------------------------------------------
//
//						Model Class
//	
//----------------------------------------------------

//Copyright: Matt Haywood

/// The model class is used for reading in model entities from a  VTK style datafile. The model class is also responsible for saving models to a VTK style file.

/** This class is responsible for reading model entities from a VTK style datafile.
*
*The modelclass should have the abillity to load points and cells from a datafile and create 
*lists of the objects you created.
*
*The model class should have the ability to save a loaded model to a different
*datafile.
*
*The model class should have the ability to perform the following operations on a model:
*
*	- Display the number of vertices in the model
*	- Display the number of cells and the type of each cell
*	- Compute the model's centre (based on the positions of nodes). 
*
*/


using namespace std;

/// The model class is used for reading in model entities from a  VTK style datafile. The model class is also responsible for saving models to a VTK style file.

class model
{

private:

//private data

	//List of vertexes
	//List of cells 
	//List of materials

	///Deques were chosen as object slicing occured with <vectors> causing some of the information stored to be lost.

	deque<cell> list_of_cells;						//Create a list of cells vector				
	deque<Vector> list_of_vertexes; 				//Change to deque 
	deque<material> list_of_materials; 				//Change to deque

	int tetrahedrons;								//Number of tetrahedrons in model

	int pyramids;									//Number of pyramids in model 

	int hexahedrons;								//Number of hexahedrons in model

	Vector centre;									//Models Centre 


public:

	model(); 										///< Constructor

	~model();										///< Destructor

	model(const model& a);							///< Copy Constructor

	model& operator=(const model& a);				///< Assigment Operator

	void readInFile(string filename);				///< Function for reading in file. e.g readInFile("myfile.txt");

	void saveNewFile(string filename);				///< Function for saving model to new file e.g saveNewFile("mynewfile.txt");

	void material_parser(string material_data);		///< Functions for parsing and creating the respective objects

	void vertex_parser(string vertex_data);			///< Passes in a vertex line for sorting

	void cell_parser(string cell_data);				///< Passes in a cell line for sorting

	deque<cell> get_list_of_cells();				///< Gets deque of cells

	deque<Vector> get_list_of_vertices();			///< Gets deque of vertexes

	deque<material> get_list_of_materials(); 		///< Gets deque of materials

	int get_material_num();							///< Get number of total materials in model

	int get_vertex_num();							///< Get total number of vertices in model

	int get_cell_num();								///< Get total number of cells in model

	int * get_cell_type();							///< Get cell type returns array of ints tetrahedrons, pyramids and hexahedrons

	//void set_models_centre();						//Set models centre

	//Vector get_models_centre();					//Get models centre

	//void compute_model_centre();					//Compute models centre

};

















