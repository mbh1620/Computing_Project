#include <fstream>
#include <sstream>
#include "material.hpp"
//#include "vector.hpp" <---- included in cell.cpp
#include "cell.hpp"


//----------------------------------------------------
//
//						Model Class
//	
//----------------------------------------------------

//Copryright: Matt Haywood

/* This class is responsible for reading model entities from a VTK style datafile.

The modelclass should have the abillity to load points and cells from a datafile and create 
lists of the objects you created.

The model class should have the ability to save a loaded model to a different
datafile.

The model class should have the ability to perform the following operations on a model:

	- Display the number of vertices in the model
	- Display the number of cells and the type of each cell
	- Compute the model's centre (based on the positions of nodes). 

*/


using namespace std;

class model
{

private:

//private data

	//List of vertexes
	//List of cells 
	//List of materials
	//List of vectors

public:

	model(); 										//constructor

	~model();										//Destructor

	model(const model& a);							//Copy Constructor

	model& operator=(const model& a);				//Assigment Operator

	void readInFile(string filename);				//Function for reading in file. e.g readInFile("myfile.txt");

	void material_parser(string material_data);		//Functions for parsing and creating the respective objects

	void vertex_parser(string vertex_data);

	void cell_parser(string cell_data);

};

model::model(){

}

model::~model(){

}

model::model(const model& a){

}

model& model:: operator=(const model& a){
	return *this;
}

void model::readInFile(string filename){
	string line;

	ifstream myfile(filename);

	if(myfile.is_open()){
		while(getline(myfile,line)){
			if(line[0] == '#'){
				//Line ignored as # is found
			}
			if(line[0] == 'm') {
				//Material line function handles the line as m was found
				material_parser(line);
			}
			if(line[0] == 'v'){
				//Vertex line function handles the line as v was found
				vertex_parser(line);
			}
			if(line[0] == 'c'){
				//cell line function handles the line as c was found
				cell_parser(line);
			}
		}
		myfile.close();
	}

	else cout << "unable to open file!";

}

void model::material_parser(string material_data){
	//Code for interpreting a material line
	//Example line for a material:
	// m 0 8960 b87373 copper
	
	string words[5];

	//Split string into words over spaces 
	stringstream ssin(material_data);
	int i = 0;
	while (ssin.good() && i < 10){
		ssin >> words[i];
		++i;
	}
	string ID = words[1];
	int idint = stof(ID);
	string density = words[2];
	float densityflt = stof(density);
	string colour = words[3];
	string material = words[4];

	cout << idint << " " << density << " " << colour << " " << material << "\n";
	
	//Create a new material object

}

void model::vertex_parser(string vertex_data){
	//Code for interpreting a vertex line
	//v 0 0. 0. 0.
	//v 1 1. 0. 0.

	string words[5];

	//Split string into words over spaces 
	stringstream ssin(vertex_data);
	int i = 0;
	while (ssin.good() && i < 10){
		ssin >> words[i];
		++i;
	}
	string ID = words[1];
	int IDint = stof(ID);
	string xstr = words[2];
	float x = stof(xstr);
	string ystr = words[3];
	float y = stof(ystr);
	string zstr = words[4];
	float z = stof(zstr);

	cout << x << " " << y << " " << z << "\n";

	//Create a new vector object
}

void model::cell_parser(string cell_data){
	//Code for interpreting a cell 
	//c 1 t 1 8 9 10 11

	string words[10];

	//Split the string into words over spaces

	stringstream ssin(cell_data);
	int i = 0;
	while(ssin.good() && i < 10){
		ssin >> words[i];
		i++;
	}

	string ID = words[1];
	int IDint = stof(ID);

	string shape = words[2];

	string material = words[3];

	//vector
	cout << shape << " " << material << "\n";
	//Create a new cell object

	
}













