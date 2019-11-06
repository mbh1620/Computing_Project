#include <iostream>
#include "model.hpp"

using namespace std;

int main(){
	model model1 = model();

	model1.readInFile("new.txt");

	Vector a[4];

	for(int i = 0; i < 4; i++){
		a[i].set('x', i);
		a[i].set('y', i*2);
		a[i].set('z', i/2);

		cout << a[i].get('y');
	}



	cell cell1 = cell(a);

}