// Programa para leer valores de cuadruplos de un archivo para calcular un resultado utilizando regresión linear multivariable
// Hernán Iruegas Villarreal A00817021
// 22/04/2018

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h> // Para usar la función de square root
#include <iomanip> // Para imprimir los números con la precision de 5 decimales deseadas
using namespace std;
#include "Archivo.h"
#include "Calculo.h"

//_p=Main
//_b=65

//_i
// Sirve para limpiar una línea, quitar espacios en blanco y otros caracteres especiales
string quitaEspacios( string &linea ){
	
	string lineaAux = ""; 

	// Hay que limpiar la línea leída de todos aquellos espacios en blanco
	for(int i = 0; i < linea.length(); i++){
        if(linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\r' && linea[i] != '\v'){
          lineaAux += linea[i];
        }
    }

   return lineaAux;
}

//_i
// Se lee el archivo y se consiguen todos los valores de los cuadruplos, además de los parametros para la regresión líneal
void obtenerInfoArchivo( ifstream &archEntrada, vector<double> &vAllWValues, vector<double> &vAllXValues, vector<double> &vAllYValues, vector<double> &vAllZValues, double &iNumberOfQuadruples, double &dWk, double &dXk, double &dYk, bool &validFormatting ){
	
	string linea = "", aux = "", delimitador = ",";

	getline( archEntrada, linea );
	linea = quitaEspacios( linea );

	if( linea.length() > 0 ){
		/* OBTENER VALORES DE PARAMETROS PARA LA REGRESION LINEAL */

		int pos = linea.find( delimitador );
		aux = linea.substr( 0, pos ); // Obtener el valor de "wk" en string
		dWk = stod( aux.c_str() ); // Obtener el valor de "wk" como double
		linea.erase(0, pos + delimitador.length() ); // Borrar valor de "wk" junto con la coma

		pos = linea.find( delimitador );
		aux = linea.substr( 0, pos ); // Obtener el valor de "xk" en string
		dXk = stod( aux.c_str() ); // Obtener el valor de "xk" como double
		linea.erase(0, pos + delimitador.length() ); // Borrar valor de "xk" junto con la coma

		aux = linea.substr( 0, string::npos ); // Obtener el valor de "yk"
		dYk = stod( aux.c_str() ); // Obtener el valor de "yk" como double


		/* OBTENER VALORES DE LOS CUADRUPLES */

		while( getline( archEntrada, linea ) ){ 

			iNumberOfQuadruples++;

			linea = quitaEspacios( linea );

			pos = linea.find( delimitador ); 
			aux = linea.substr( 0, pos ); // Obtener el valor de "w"
			vAllWValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "w" como dato tipo double
			linea.erase(0, pos + delimitador.length() ); // Borrar valor de "w" junto con la coma

			pos = linea.find( delimitador ); 
			aux = linea.substr( 0, pos ); // Obtener el valor de "x"
			vAllXValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "x" como dato tipo double
			linea.erase(0, pos + delimitador.length() ); // Borrar valor de "x" junto con la coma

			pos = linea.find( delimitador ); 
			aux = linea.substr( 0, pos ); // Obtener el valor de "y"
			vAllYValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "y" como dato tipo double
			linea.erase(0, pos + delimitador.length() ); // Borrar valor de "y" junto con la coma

			aux = linea.substr( 0, string::npos ); // Obtener el valor de "z"
			vAllZValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "z" como dato tipo double

		}

	}else{
		validFormatting = false;
	}
}

//_i
// Sirve para obtener la información del archivo y realizar los calculos necesarios para la regresión lineal con multiples parametros
void calcularInfoArchivo( string sNombreArchivo, bool &bExiste, Archivo &archivo, double &iNumberOfQuadruples, double &dWk, double &dXk, double &dYk ){ //_m

	ifstream archEntrada; // Se necesita para abrir los archivos del usuario
	vector<double> vAllWValues;
	vector<double> vAllXValues;
	vector<double> vAllYValues;
	vector<double> vAllZValues;
	bool validFormatting = true;


	archEntrada.open( sNombreArchivo );

	// Hay que validar que el nombre del archivo existe
	if( archEntrada ){

		// Se lee el archivo y se consiguen todos los valores de los cuadruplos, además de los parametros para la regresión líneal
		obtenerInfoArchivo( archEntrada, vAllWValues, vAllXValues, vAllYValues, vAllZValues, iNumberOfQuadruples, dWk, dXk, dYk, validFormatting ); //_m

		if( validFormatting ){

			// Crear objeto calculo para tener acceso a las funciones que realizan los calculos sobre los valores del archivo
			Calculo calculo;

			archivo.setNombre( sNombreArchivo );

			// Organizar todo para que se pueda crear la matriz de gauss, lista para ser reducida y encontrar valores de betas
			archivo.calculateInfo( vAllWValues, vAllXValues, vAllYValues, vAllZValues, iNumberOfQuadruples ); //_m

			archivo.setBetas( calculo.calGauss( archivo.getMat( iNumberOfQuadruples ) ) ); // Obtener resultado de parametros para la regresión ( valores de betas )

			archivo.setZPrediction( archivo.getBetas(), dWk, dXk, dYk ); // Obtener predicción de regresión líneal multivariable

			//_d=5

			archEntrada.close();
		}else{
			bExiste = false;
			cout << "Error: El formato del archivo es el incorrecto, la primera línea no puede estar vacia" << endl;
		}
		
	}else{
		bExiste = false;
		cout<< "Error: Este archivo no existe" << endl;
	}
}

//_i
// Sirve para desplegar los resultados de los calculos obtenidos a partir de la información del archivo
void desplegarInfoArchivo( Archivo archivo, int iNumberOfQuadruples, double dWk, double dXk, double dYk ){ //_m
	
	cout << fixed << setprecision(5) ; // Para desplegar numeros redondeadoscon 5 decimales
	cout << "N  = " << iNumberOfQuadruples << endl;
	cout << "wk = " << setprecision(5) << fixed << dWk << endl;
	cout << "xk = " << setprecision(5) << fixed << dXk << endl;
	cout << "yk = " << setprecision(5) << fixed << dYk << endl;

	cout << "------------" << endl;

	vector< double > vBetas = archivo.getBetas();

	cout << "b0 = " << setprecision(5) << fixed << vBetas[ 0 ] << endl; //_m
	cout << "b1 = " << setprecision(5) << fixed << vBetas[ 1 ] << endl; //_m
	cout << "b2 = " << setprecision(5) << fixed << vBetas[ 2 ] << endl; //_m
	cout << "b3 = " << setprecision(5) << fixed << vBetas[ 3 ] << endl; //_m

	cout << "------------" << endl;

	cout << "zk = " << setprecision(5) << fixed << archivo.getZPrediction() << endl; //_m
}

//_i
int main(){

	string sNombreArchivo = "";
	bool bExiste = true;
	Archivo archivo;
	double iNumberOfQuadruples = 0; //_m
	double dWk = 0;
	double dXk = 0;
	double dYk = 0;

	cout << "Ingrese el nombre del archivo: "; 
	cin >> sNombreArchivo;

	calcularInfoArchivo( sNombreArchivo, bExiste, archivo, iNumberOfQuadruples, dWk, dXk, dYk ); //_m
	
	if(bExiste)
		desplegarInfoArchivo( archivo, iNumberOfQuadruples, dWk, dXk, dYk ); //_m

	return 0;
}