#include <iostream>
#include <armadillo>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
using namespace arma;

#define PI 3.14159

int const n = 3;
vec u = ones<vec>(n);
GLdouble vertices[n]; //3*n^2

class MyClass
{
	private:
	int a;
	vec v;
	mat M;

	public:
	MyClass(); //konstruktør
	int getInt(){return a;}
	vec getVec(){return v;}
	mat getMat();
};

int main() {

	MyClass myVariable; //ENDRING HER. ikke bruk myVariable() parentes
	mat A = zeros<mat>(n,n);
	//int b = myVariable.getInt();
	//A = myVariable.getMat();
	cout << myVariable.getMat() << endl;
	return 0;
}

MyClass::MyClass(){
	a = 10;
	v = ones<vec>(n);
	M = ones<mat>(n,n);
	cout << M << endl;
}

mat MyClass::getMat(){
	return M;
}


