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