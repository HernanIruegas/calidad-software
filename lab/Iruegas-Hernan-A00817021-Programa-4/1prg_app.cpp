// Programa que calcula el valor de una integral usando el método de Simpson
// Hernán Iruegas Villarreal A00817021
// 18/03/2018

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h> // Para usar la función de square root
#include <cmath>
#include <iomanip> // Para imprimir los números con la precision de 5 decimales deseadas
using namespace std;
#include "Respuesta.h"
#include "Calculo.h"

//_p=Main
//_i
int main(){

	double dX = 0, diferencia = 0, error = 0.0000001;
	int iDof = 0, iNumSeg = 10;
	Calculo calculo;

	cout << "Ingrese el valor de x: ";
	cin >> dX;
	while( dX < 0 ){
		cout << "ERROR: dato invalido. Se debe proporcionar un número real mayor o igual a cero para x";
		cout << "\nIngrese el valor de x: ";
		cin >> dX;
	}

	cout << "Ingrese el valor para los grados de libertad: ";
	cin >> iDof;
	while( iDof <= 0 || !cin ){
		cout << "ERROR: dato invalido. Se debe proporcionar un número entero mayor a cero para los grados de libertad";
		cout << "\nIngrese el valor para los grados de libertad: ";
		cin >> iDof;
	}

	Respuesta *pObj1 = new Respuesta( dX, iDof, 10 );

	pObj1 -> setP( calculo.calculateP( pObj1 ) );

	Respuesta *pObj2 = new Respuesta( dX, iDof, 20 );

	pObj2 -> setP( calculo.calculateP( pObj2 ) );

	diferencia = pObj1 -> getP() - pObj2 -> getP();

	while( abs( diferencia ) >= error ){

		pObj1 = pObj2;
		iNumSeg *= 2;
		pObj2 = new Respuesta( dX, iDof, iNumSeg );
		pObj2 -> setP( calculo.calculateP( pObj2 ) );
		diferencia = pObj1 -> getP() - pObj2 -> getP();
	}

	cout << endl;
	cout << "  x  =  " << setprecision(5) << fixed << dX << endl;
	cout << "dof  =  " << iDof << endl;
	cout << "  p  =  " << setprecision(5) << fixed << pObj2 -> getP()<< endl;
}








