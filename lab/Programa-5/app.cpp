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
//_b=31

//_i
double getP( double dXAux, int iDof, Calculo calculo ){

	double diferencia = 0, error = 0.0000001;
	int iNumSeg = 20;

	Respuesta *pObj1 = new Respuesta( dXAux, iDof, 10 ); // crear primer objeto
	pObj1 -> setP( calculo.calculateP( pObj1 ) ); // calcular P para el primer objeto
	
	Respuesta *pObj2 = new Respuesta( dXAux, iDof, 20 ); // crear segundo objeto
	pObj2 -> setP( calculo.calculateP( pObj2 ) ); // calcular P para el segundo objeto

	diferencia = pObj1 -> getP() - pObj2 -> getP();

	while( abs( diferencia ) >= error ){

		pObj1 = pObj2;
		iNumSeg *= 2;
		pObj2 = new Respuesta( dXAux, iDof, iNumSeg );
		pObj2 -> setP( calculo.calculateP( pObj2 ) );
		diferencia = pObj1 -> getP() - pObj2 -> getP();
	}
	return pObj2 -> getP();
}

//_i
double getX( double dPOriginal, int iDof, Calculo calculo ){

	double dError = 0.00000000001;
	double dXAux = 1.0;
	double dIncrement = 0.5;

	double dPAux = getP( dXAux, iDof, calculo );
	double dDiferencia = dPAux - dPOriginal;
	double dDiferenciaAux = dDiferencia;

	while( abs( dDiferencia ) >= dError ){

		dDiferencia > 0 ? dXAux -= dIncrement : dXAux += dIncrement;

		if( (dDiferenciaAux > 0 && dDiferencia < 0) || (dDiferenciaAux < 0 && dDiferencia > 0) ){
			dIncrement = dIncrement / 2;
		}

		dPAux = getP( dXAux, iDof, calculo );
		dDiferenciaAux = dDiferencia;
		dDiferencia = dPAux - dPOriginal;
	}

	return dXAux; 
}


//_i
int main(){

	double dP = 0, diferencia = 0, dXAux = 1, dDeltaInc = dXAux / 2;
	int iDof = 0;
	Calculo calculo;

	cout << "Ingrese el valor de p: "; //_m
	cin >> dP; //_m
	while( dP < 0 || dP > 0.5 ){
		cout << "ERROR: dato invalido. Se debe proporcionar un número real con valor entre 0.0 - 0.5 para p"; //_m
		cout << "\nIngrese el valor de p: "; //_m
		cin >> dP; //_m
	}

	cout << "Ingrese el valor para los grados de libertad: "; 
	cin >> iDof; 
	while( iDof <= 0 || !cin ){ 
		cout << "ERROR: dato invalido. Se debe proporcionar un número entero mayor a cero para los grados de libertad"; 
		cout << "\nIngrese el valor para los grados de libertad: "; 
		cin >> iDof; 
	}

	//_d=5

	double dX = getX( dP, iDof, calculo );

	cout << endl;
	cout << "  p = " << setprecision(5) << fixed << dP << endl;
	cout << "dof = " << iDof << endl;
	cout << "  x = " << setprecision(5) << fixed << dX << endl; //_m
	
	
}








