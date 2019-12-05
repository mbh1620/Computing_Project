#include "model.hpp"


model::model(){
	tetrahedrons = 0;
	pyramids = 0;
	hexahedrons = 0;
}

model::~model(){

}

model::model(const model& a){
	list_of_cells = a.list_of_cells;
	list_of_materials = a.list_of_materials;
	list_of_vertexes = a.list_of_vertexes;
}

model& model:: operator=(const model& a){
	list_of_cells = a.list_of_cells;
	list_of_materials = a.list_of_materials;
	list_of_vertexes = a.list_of_vertexes;
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

	else std::cout << "unable to open file!";

}

void model::saveNewFile(string filename){
	ofstream myfile;

	myfile.open(filename);

	//get all Vertexes and write them to the file in order
	myfile << "# Vertices \n";
	for(int i = 0; i < list_of_vertexes.size(); i++){
		myfile << "v " << list_of_vertexes[i].get('i') << " " << list_of_vertexes[i].get('x') << " " << list_of_vertexes[i].get('y') << " " << list_of_vertexes[i].get('z') << "\n"; 
	}

	//Get all materials and write them to the file 
	myfile << "# Materials \n";
	for(int i = 0; i < list_of_materials.size(); i++){
		myfile << "m " << list_of_materials[i].getId() << " " << list_of_materials[i].getDensity() << " " << list_of_materials[i].getColour() << " " << list_of_materials[i].getName() << "\n"; 
	}

	//Get all cells and write them to the file 
	myfile << "# Cells \n";
	for(int i = 0; i < list_of_cells.size(); i++){
		myfile << "c " << list_of_cells[i].getId() << " " << list_of_cells[i].get_shape() << " " << list_of_cells[i].get_material().getId() << " ";
		
		std::deque<Vector> z = list_of_cells[i].get_vertices();

		for(int s = 0; s < z.size(); s++){
			myfile << (int) z[s].get('i') << " ";
		}

		myfile <<"\n";
	}

	myfile.close();

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
	string name = words[4];
	
	//Create a new material object and put it into the material list

	material new_material = material(idint, name, colour, densityflt);

	list_of_materials.push_back(new_material);

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

	//Create a new vector object and put it into the vector list 

	Vector new_vertex = Vector(IDint, x, y, z);

	list_of_vertexes.push_front(new_vertex); 

}

void model::cell_parser(string cell_data){
	//Code for interpreting a cell 
	//c 1 t 1 8 9 10 11
	deque<string> words;
	//string words[10];

	//Split the string into words over spaces

	stringstream ssin(cell_data);
	int i = 0;
	while(ssin.good() && i < 12){
		string word;
		ssin >> word;
		words.push_back(word);
		i++;	
	}

	string ID = words[1];
	int IDint = stof(ID);

	string shape = words[2];

	string stringmaterial = words[3];

	int cell_material_id = std::stoi(stringmaterial);

	material cell_material;

	//CHECK STRING_MATERIAL ID AGAINST THE LIST OF LOADED MATERIALS IN THE MATERIAL LIST
	//THEN CHANGE CELL_MATERIAL TO THAT MATERIAL

	for(int i = 0; i < list_of_materials.size(); i++ ){
		if( list_of_materials[i].getId() == cell_material_id){
			cell_material = list_of_materials[i];
		}
	}
	//Take in the list of vertices ids 


	deque<int> vertices_ID;

	for(int i = 0; i < words.size()-4; i++){
		stringstream func(words[i+4]);
		int a;
		func >> a;
		vertices_ID.push_back(a);

		//cout << vertices_ID[i] << " vertices ID!!! \n";

	}
 
 	
	std::deque<Vector> vertices;
	//convert the list of ids to actual vertices in the list 

	//Iterate through the vertices list and pick out the chosen vertexes by looking at each vertices ID.
	//Then put it into the vector array ready to put into the cell constructor.
	int z = 0;
	for(int i = 0; i < vertices_ID.size(); i++){

		//cout << vertices_ID[i] << " \n" ;
		for(int x = 0; x < list_of_vertexes.size(); x++){
			if(vertices_ID[i] == (int) list_of_vertexes[x].get('i')){
				
				vertices.push_back(list_of_vertexes[x]);  
				z++;
			}
		}
	}
	

	//vector
	//cout << shape << " " << material << "\n";
	//Create a new cell object and put it into the cell list 

	if(shape[0] == 't'){
		tetrahedron new_tet = tetrahedron(vertices, cell_material); 
		new_tet.volume_calc();
		new_tet.cog_calc();
		new_tet.weight_calc();
		new_tet.setId(IDint);
		
		//new_tet.weight_calc();
		
		//Push the newly created tetrahedron to list of cells
		list_of_cells.push_back(new_tet);

	} else if(shape[0] == 'p'){
		pyramid new_pyramid = pyramid(vertices, cell_material);
		new_pyramid.volume_calc();
		new_pyramid.cog_calc();
		new_pyramid.weight_calc();
		new_pyramid.setId(IDint);
		
		//new_pyramid.weight_calc();

		//Push the newly created pyramid to list of cells
		list_of_cells.push_back(new_pyramid);
		

	} else if(shape[0] == 'h'){
		hexahedron new_hexa = hexahedron(vertices, cell_material);
		new_hexa.volume_calc();
		new_hexa.weight_calc();
		new_hexa.setId(IDint);
		
		list_of_cells.push_back(new_hexa);
		list_of_cells[list_of_cells.size()-1].set_shape('h');	
	}	
	
}

deque<cell> model::get_list_of_cells(){
	return list_of_cells;
}

deque<Vector> model::get_list_of_vertices(){
	return list_of_vertexes;
}

deque<material> model::get_list_of_materials(){
	return list_of_materials;
}

int model::get_material_num(){
	return list_of_materials.size();
}		

int model::get_vertex_num(){
	return list_of_vertexes.size();
}							

int model::get_cell_num(){
	return list_of_cells.size();
}

int * model::get_cell_type(){
	//Return info about the type of cells in the model.
	static int t_p_h[3];
	//Go through list of cells and return types of cells

	for(int i = 0; i < list_of_cells.size(); i++){
		char shape = list_of_cells[i].get_shape();
		if(shape == 't'){
			tetrahedrons++;
		}
		if(shape == 'p'){
			pyramids++;
		}
		if(shape == 'h'){
			hexahedrons++;
		}
	}
	t_p_h[0] = tetrahedrons;
	t_p_h[1] = pyramids;
	t_p_h[2] = hexahedrons;

	return t_p_h;

	
}	
