// Programa para leer valores de X y Y de un archivo para calcular un resultado utilizando regresión linear
// Hernán Iruegas Villarreal A00817021
// 14/04/2018

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
// Sirve para obtener los valores de X y Y dentro del archivo, así como el valor con el que se calcula la predicción de la regresión lineal
void obtenerInfoArchivo( ifstream &archEntrada, vector<double> &vAllXValues, vector<double> &vAllYValues, int &iNumberOfPairs, int &iValueForRegression ){
	
	string linea = "", aux = "", delimitador = ",";

	getline( archEntrada, linea );
	linea = quitaEspacios( linea );
	iValueForRegression = atoi( linea.c_str() ); // Este valor es el primer número del archivo

	// Ahora hay que leer las parejas de datos
	while( getline( archEntrada, linea ) ){ 

		iNumberOfPairs++;

		linea = quitaEspacios( linea );

		int pos = linea.find( delimitador ); // Para obtener la posicion de la coma dentro de la pareja de datos "x" y "y"

		aux = linea.substr( 0, pos ); // Obtener el valor de "x"
		vAllXValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "x" como dato tipo double
		linea.erase(0, pos + delimitador.length() ); // Borrar valor de "x" junto con la coma
		aux = linea.substr( 0, string::npos ); // Obtener el valor de "y"
		vAllYValues.push_back( stod( aux.c_str() ) ); // Agregar valor de "y" como dato tipo double
	}
}

//_i
// Sirve para obtener la información del archivo y realizar los calculos necesarios para la regresión lineal
void calcularInfoArchivo( string sNombreArchivo, bool &bExiste, Archivo &archivo, int &iNumberOfPairs, int &iValueForRegression ){

	ifstream archEntrada; // Se necesita para abrir los archivos del usuario
	vector<double> vAllXValues;
	vector<double> vAllYValues;

	archEntrada.open( sNombreArchivo );

	// Hay que validar que el nombre del archivo existe
	if( archEntrada ){

		// Se lee el arhivo y se consiguen todos los valores de X y Y, además del valor con el que se quiere realizar el cálculo de la regresión lineal
		obtenerInfoArchivo( archEntrada, vAllXValues, vAllYValues, iNumberOfPairs, iValueForRegression ); 

		// Crear objeto calculo para tener acceso a las funciones que realizan los calculos sobre los valores del archivo
		Calculo calculo;

		archivo.setNombre( sNombreArchivo );

		// Obtener suma de valores de "x"
		// Obtener suma de valores de "y"
		// Obtener promedio de valores de "x"
		// Obtener promedio de valores de "y"
		// Obtener suma de valores de "x" al cuadrado
		// Obtener suma de valores de "y" al cuadrado
		// Obtener suma de valores de "x" * valores de "y"
		//_d=7
		archivo.calculateInfoXAndY( vAllXValues, vAllYValues, iNumberOfPairs );
		
		archivo.setTheta1( calculo.calculateTheta1(  archivo.getSumXTimesYValues(),  archivo.getSumSquaredXValues(),  archivo.getAvgY(),  archivo.getAvgX(),  iNumberOfPairs ) );
		archivo.setTheta0( calculo.calculateTheta0(  archivo.getAvgY(),  archivo.getTheta1(),  archivo.getAvgX() ) );

		archivo.setR( calculo.calculateR( iNumberOfPairs, archivo.getSumXTimesYValues(), archivo.getSumXValues(), archivo.getSumYValues(), archivo.getSumSquaredXValues(), archivo.getSumSquaredYValues() ) );
		archivo.setRSquared( calculo.calculateRSquared( archivo.getR() ) );
		
		archivo.setYPrediction( calculo.calculateYPrediction( archivo.getTheta0(), archivo.getTheta1(),  iValueForRegression ) );

		archEntrada.close();
	}else{
		bExiste = false;
		cout<< "Error: Este archivo no existe" << endl;
	}
}

//_i
// Sirve para desplegar los resultados de los calculos obtenidos a partir de la información del archivo
void desplegarInfoArchivo( Archivo archivo, int iNumberOfPairs, int iValueForRegression ){
	
	cout << fixed << setprecision(5) ; // Para desplegar numeros redondeadoscon 5 decimales
	cout << "N = " << iNumberOfPairs << endl;
	cout << "xk = " << iValueForRegression << endl;
	cout << "r =  " << setprecision(5) << fixed << archivo.getR() << endl;
	cout << "r2 =  " << setprecision(5) << fixed << archivo.getRSquared() << endl;
	cout << "b0 =  " << setprecision(5) << fixed << archivo.getTheta0() << endl;
	cout << "b1 =  " << setprecision(5) << fixed << archivo.getTheta1() << endl;
	cout << "yk =  " << setprecision(5) << fixed << archivo.getYPrediction() << endl;
}

//_i
int main(){

	string sNombreArchivo;
	bool bExiste = true;
	Archivo archivo;
	int iNumberOfPairs = 0;
	int iValueForRegression = 0;

	cout << "Ingrese el nombre del archivo: "; 
	cin >> sNombreArchivo;

	calcularInfoArchivo( sNombreArchivo, bExiste, archivo, iNumberOfPairs, iValueForRegression ); 
	
	if(bExiste)
		desplegarInfoArchivo( archivo, iNumberOfPairs, iValueForRegression ); 

	return 0;
}