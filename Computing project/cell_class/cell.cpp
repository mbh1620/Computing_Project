/// \file

#include "cell.hpp"
#include <iostream>

//Volume of tetrahedron function
#include <cmath>

float volume_of_tetra(Vector vertices[]){
	Vector a = vertices[0];
	Vector b = vertices[1];
	Vector c = vertices[2];
	Vector d = vertices[3];

	Vector x = a-d;
	Vector y = b-d;
	Vector z = c-d;



	Vector ycrossz = y.cross(z);

	float volume = x.dot(ycrossz);

		volume = pow(volume, 2);
		volume = sqrt(volume)/6; 
	
	return volume;


}


//-----------------------------------------------------------------------------
//
//						Cell Class and Sublasses of Cell
//	
//-----------------------------------------------------------------------------

// author: Matt Haywood 

int cell::getId(){			
	return id;
}

void cell::setId(int _id){
	id = _id;
}

void cell::set_material(material _cell_material){
	cell_material = _cell_material;
}

material cell::get_material(){
	return cell_material;
}

void cell::set_shape(char _shape){
	shape = _shape;
}

char cell::get_shape(){
	return shape;
}

cell::cell(std::deque<Vector> vertices_in, material _cell_material){		/*! The Constructor for cell takes in a list of vertices, and a material. It then copys these
																				vertices and material to itself. In the standard cell construction a shape is not defined and 
																				so the shape is just 'n'.  */

	vertices = vertices_in;

	cell_material = _cell_material;
	shape='n';
}

cell::cell(){							//Constructor for no vertices
	shape='n';
}

cell::~cell(){

}

cell::cell(const cell& a){
	id = a.id;
	vertices = a.vertices;
	volume = a.volume;
	cell_material = a.cell_material;
	cog = a.cog;
	weight = a.weight;
	shape = a.shape;
}

cell& cell:: operator=(const cell& a){
	id = a.id;
	vertices = a.vertices;
	volume = a.volume;
	cell_material = a.cell_material;
	cog = a.cog;
	weight = a.weight;
	shape = a.shape;
	return *this;
}

float cell::get_volume(){
	return volume;
}

void cell::set_volume(float _volume){
	volume = _volume;
}

Vector cell::get_cog(){
	return cog;
}

void cell::set_cog(Vector _cog){
	cog = _cog;
}

float cell::get_weight(){
	return weight;
}

void cell::set_weight(float _weight){
	weight = _weight;
}

std::deque<Vector> cell::get_vertices(){
	return vertices;
}

void cell::set_vertices(std::deque<Vector> _vertices){
	vertices = _vertices;
}

float cell::weight_calc(){
	//Code for calculating the weight
	//Volume * density
	return weight;
	
}

Vector cell::cog_calc(){
	//Code for calculating the COG
	//Centroid function 	
	Vector cog;

	return cog;
}

float cell::volume_calc(){
	//Code for calculating the Volume of a cell
	return 0;
}

//-----------------------------------------------------------------------------
//
//							Tetrahedron Subclass
//	
//-----------------------------------------------------------------------------

tetrahedron::tetrahedron(std::deque<Vector> vertices_in, material _cell_material){

	cell_material = _cell_material;
	
	set_vertices(vertices_in);
	
	shape='t';

	
}

float tetrahedron::weight_calc(){																

	//Get the density from the material of the cell
	float cell_density = cell_material.getDensity();

	//Multiply the cell density by the cell volume to get cell_weight;

	float cell_weight = cell_density * volume;

	set_weight(cell_weight);

	return(cell_weight);


}

Vector tetrahedron::cog_calc(){						/*! The Tetrahedron centre of gravity calculation is calculated by adding all the points up and then dividing by 4. This 
														is assuming that the density of the tetrahedron is constant through out.*/
	//Centroid function for a tetrahedron

	std::deque <Vector> points = get_vertices();

	Vector a = points[0];
	Vector b = points[1];
	Vector c = points[2];
	Vector d = points[3];

	Vector output;

	float output_x = (a.get('x') + b.get('x') + c.get('x') + d.get('x'))/4;
	float output_y = (a.get('y') + b.get('y') + c.get('y') + d.get('y'))/4;
	float output_z = (a.get('x') + b.get('z') + c.get('z') + d.get('z'))/4;

	output.set('x', output_x);
	output.set('y', output_y);
	output.set('z', output_z);

	set_cog(output);

	return get_cog();
}

float tetrahedron::volume_calc(){
	/*! The volume of a tetrahedron for four points can be defined as:
	
		V = [(a-d)dot((b-d)cross(c-d))]/6
		V = [xdot(ycrossz)]/6

		dot and cross functions have been defined in the vector.hpp library so we can use them.
		*/
		std::deque<Vector> points = get_vertices();

		// for(int i = 0; i < 4; i++){
		// 	std::cout << points[i].get('x') << " < x " << points[i].get('y') << " < y " << points[i].get('z') << " < z   \n";
		// }

		Vector a = points[0];
		Vector b = points[1];
		Vector c = points[2];
		Vector d = points[3];

		Vector x = a-d;
		Vector y = b-d;
		Vector z = c-d;
	
		Vector ycrossz = y.cross(z);
		float answer = x.dot(ycrossz);

		//std::cout << answer << " is answer \n ";

		answer = pow(answer, 2);
		answer = sqrt(answer)/6; 
		set_volume(answer);

		return get_volume();
}

//-----------------------------------------------------------------------------
//
//							Pyramid Subclass
//	
//-----------------------------------------------------------------------------


pyramid::pyramid(std::deque<Vector> vertices_in, material _cell_material){
	set_vertices(vertices_in);
	cell_material = _cell_material;
	shape = 'p';
}

float pyramid::weight_calc(){



	//Get the density from the material of the cell
	float cell_density = cell_material.getDensity();

	//Multiply the cell density by the cell volume to get cell_weight;

	float cell_weight = cell_density * volume;

	set_weight(cell_weight);

	return(cell_weight);


}

Vector pyramid::cog_calc(){
	//calculations for calculating the centre of gravity of a pyramid

	/*! The centre of gravity for a pyramid can be calculated by adding up all the vectors of the class and then dividing by 5. This is assuming the 
		pyramid is made of a single material and the density is constant throug out. */

	std::deque<Vector> points = get_vertices();


	Vector a = points[0];
	Vector b = points[1];
	Vector c = points[2];
	Vector d = points[3];
	Vector e = points[4];

	Vector output;

	float output_x = (a.get('x') + b.get('x') + c.get('x') + d.get('x') + e.get('x'))/5;
	float output_y = (a.get('y') + b.get('y') + c.get('y') + d.get('y') + e.get('y'))/5;
	float output_z = (a.get('z') + b.get('z') + c.get('z') + d.get('z') + e.get('z'))/5;

	output.set('x', output_x);
	output.set('y', output_y);
	output.set('z', output_z);

	set_cog(output);

	return get_cog();
}

float pyramid::volume_calc(){
	/*! The volume of a pyramid for 5 points can be defined as: 

		Split the pyramid into two tetrahedrons, work out the volume of both of them and then add their volumes together.

		tetrahedron 1 = 1,2,3,4

		tetrahedron 2 = 0,1,3,4

		The volume of the 2 tetrahedrons are calulated using the volume_of_tetra_function().

		*/

		std::deque<Vector> points = get_vertices();

		Vector a = points[0];
		Vector b = points[1];
		Vector c = points[2];
		Vector d = points[3];
		Vector e = points[4];

		Vector tetra_1[4];

		tetra_1[0] = b;
		tetra_1[1] = c;
		tetra_1[2] = d;
		tetra_1[3] = e;


 		Vector tetra_2[4];

 		tetra_2[0] = a;
 		tetra_2[1] = b;
 		tetra_2[2] = d;
 		tetra_2[3] = e;

 		float vol_tet_1 = volume_of_tetra(tetra_1);

 		float vol_tet_2 = volume_of_tetra(tetra_2);

 		float vol_of_pyramid = vol_tet_1 + vol_tet_2;

 		set_volume(vol_of_pyramid);

 		return get_volume();
}

//-----------------------------------------------------------------------------
//
//							Hexahedron Subclass
//	
//-----------------------------------------------------------------------------



hexahedron::hexahedron(std::deque<Vector> vertices_in, material _cell_material){
	set_vertices(vertices_in);
	cell_material = _cell_material;
	shape = 'h';
}

float hexahedron::weight_calc(){

	//Get the density from the material of the cell
	float cell_density = cell_material.getDensity();

	//Multiply the cell density by the cell volume to get cell_weight;

	float cell_weight = cell_density * volume;

	set_weight(cell_weight);

	return(cell_weight);


}

Vector hexahedron::cog_calc(){

	/*! The centre of gravity of a hexahedron is calulated by adding all the points together and dividing by 8. This is assuming that the density is constant through out.*/

	std::deque<Vector> points = get_vertices();


	Vector a = points[0];
	Vector b = points[1];
	Vector c = points[2];
	Vector d = points[3];
	Vector e = points[4];
	Vector f = points[5];
	Vector g = points[6];
	Vector h = points[7];

	Vector output;

	float output_x = (a.get('x') + b.get('x') + c.get('x') + d.get('x') + e.get('x') + f.get('x') + g.get('x') + h.get('x'))/8;
	float output_y = (a.get('y') + b.get('y') + c.get('y') + d.get('y') + e.get('y') + f.get('y') + g.get('y') + h.get('y'))/8;
	float output_z = (a.get('z') + b.get('z') + c.get('z') + d.get('z') + e.get('z') + f.get('z') + g.get('z') + h.get('z'))/8;

	output.set('x', output_x);
	output.set('y', output_y);
	output.set('z', output_z);

	set_cog(output);

	return get_cog();
}

float hexahedron::volume_calc(){
	/*! The volume of a hexahedron for 8 points can be defined as: 

		Split the hexahedron into 5 tetrahedrons, calculate the volume of the 5 tetrahedrons and then add the volumes together.

		Tetrahedron 1 = (0,3,6,2)
		Tetrahedron 2 = (5,3,6,7)
		Tetrahedron 3 = (0,1,4,3)
		Tetrahedron 4 = (6,4,5,0)
		Tetrahedron 5 = (3,0,5,6) the volume of the inside tetrahedron is twice the outer tetrahedrons.

		*/

		//THIS SECTION NEEDS REFACTORING TO SMALLER AMOUNT OF CODE!

		std::deque<Vector> points = get_vertices();

		//Define all the tetrahedrons by their vertices

		Vector Tetra_1[] = {points[0], points[3], points[6], points[2]};
		Vector Tetra_2[] = {points[5], points[3], points[6], points[7]};
		Vector Tetra_3[] = {points[0], points[1], points[4], points[3]};
		Vector Tetra_4[] = {points[6], points[4], points[5], points[0]};
		Vector Tetra_5[] = {points[3], points[0], points[5], points[6]};

		//Perform the volume of tetra function on all of the tetras

		float vol_tet_1 = volume_of_tetra(Tetra_1);
		float vol_tet_2 = volume_of_tetra(Tetra_2);
		float vol_tet_3 = volume_of_tetra(Tetra_3);
		float vol_tet_4 = volume_of_tetra(Tetra_4);
		float vol_tet_5 = volume_of_tetra(Tetra_5);
		
		//Sum all of the volumes to get the total volume of the hexahedron

		set_volume(vol_tet_1 + vol_tet_2 + vol_tet_3 + vol_tet_4 + vol_tet_5);

		return get_volume();
}


