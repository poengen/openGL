#include "myArmadilloClass.h"

vec MyArmadilloClass::getSolution(vec u) {

	u = solve(G,u);

	return u;
}

double MyArmadilloClass::getDouble(){
	return hx;
}

mat MyArmadilloClass::getMat(){
	return G;
}

MyArmadilloClass::MyArmadilloClass(){
	hx = 1./double(n-1);
	ht = 0.001; //time-step
	k = 100; //number of time-steps
	T = ht*k; //total time

	mat A = zeros<mat>(n*n,n*n);
	mat I = zeros<mat>(n*n,n*n);
	mat G = zeros<mat>(n*n,n*n);


	for (int i = 0; i < n*n; i++){ A(i,i) = 4; I(i,i) = 1;}
	for (int i = 0; i < n*n-n; i++) { A(i,n+i) = -1; A(n+i,i) = -1; }
	for (int i = 0; i < n*n-1; i++) { A(i,i+1) = -1; A(i+1,i) = -1; }
	for (int i = 0; i < n-1; i++) { A((i+1)*n-1,(i+1)*n) = 0; A((i+1)*n,(i+1)*n-1) = 0; }
	A = -1/(hx*hx)*A;
	G = I-ht*A;
}