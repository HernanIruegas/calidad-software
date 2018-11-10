// Programa para leer valores de X y Y de un archivo para calcular un resultado utilizando regresión linear
// Hernán Iruegas Villarreal A00817021
// 04/03/2018

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h> // Para usar la función de square root
#include <iomanip> // Para imprimir los números con la precision de 5 decimales deseadas
using namespace std;
#include "Archivo.h"
#include "Calculo.h"


// Sirve para limpiar una línea, quitar espacios en blanco y otros caracteres especiales
//_p=QuitaEspacios
//_b=6
string quitaEspacios( string &linea ){
	//_i
	string lineaAux = ""; 

	// Hay que limpiar la línea leída de todos aquellos espacios en blanco
	for(int i = 0; i < linea.length(); i++){
        if(linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\r' && linea[i] != '\v'){
          lineaAux += linea[i];
        }
    }

   return lineaAux;
}

// Sirve para obtener los valores de X y Y dentro del archivo, así como el valor con el que se calcula la predicción de la regresión lineal
//_p=obtenerInfoArchivo
void obtenerInfoArchivo( ifstream &archEntrada, vector<double> &vAllXValues, vector<double> &vAllYValues, int &iNumberOfPairs, int &iValueForRegression ){
	//_i
	string linea = "", aux = "", delimitador = ",";

	getline( archEntrada, linea );
	linea = quitaEspacios( linea );
	iValueForRegression = atoi( linea.c_str() );

	while( getline( archEntrada, linea ) ){

		iNumberOfPairs++;

		linea = quitaEspacios( linea );

		int pos = linea.find( delimitador );

		aux = linea.substr( 0, pos );
		vAllXValues.push_back( stod( aux.c_str() ) );
		linea.erase(0, pos + delimitador.length() );
		aux = linea.substr( 0, string::npos );
		vAllYValues.push_back( stod( aux.c_str() ) );
	}
}

// Sirve para obtener la información del archivo y realizar los calculos necesarios para la regresión lineal
//_p=calcularInfoArchivo
//_b=26
void calcularInfoArchivo(string sNombreArchivo, bool &bExiste, Archivo &archivo, int &iNumberOfPairs, int &iValueForRegression){

	//_i
	ifstream archEntrada; // Se necesita para abrir los archivos del usuario
	vector<double> vAllXValues;
	vector<double> vAllYValues;
	//_d=3
	//_d=2
	//_d=1

	archEntrada.open(sNombreArchivo);

	// Hay que validar que el nombre del archivo existe
	if(archEntrada){

		// Se lee el arhivo y se consiguen todos los valores de X y Y, además del valor con el que se quiere realizar el cálculo de la regresión lineal
		obtenerInfoArchivo( archEntrada, vAllXValues, vAllYValues, iNumberOfPairs, iValueForRegression ); 

		// Se crea el archivo y se obtiene los valores para sus atributos
		Calculo calculo;

		archivo.setNombre( sNombreArchivo );

		archivo.setSumXValues( calculo.calculateSumXValues( vAllXValues ) );
		archivo.setSumYValues( calculo.calculateSumYValues( vAllYValues ) );

		archivo.setAvgX( calculo.calculateAvgX( archivo.getSumXValues(), iNumberOfPairs ) );
		archivo.setAvgY( calculo.calculateAvgY( archivo.getSumYValues(), iNumberOfPairs ) );

		archivo.setSumSquaredXValues( calculo.calculateSumSquaredXValues( vAllXValues ) );
		archivo.setSumSquaredYValues( calculo.calculateSumSquaredYValues( vAllYValues ) );

		archivo.setSumXTimesYValues( calculo.calculateSumXTimesYValues( vAllXValues, vAllYValues ) );

		archivo.setTheta1( calculo.calculateTheta1(  archivo.getSumXTimesYValues(),  archivo.getSumSquaredXValues(),  archivo.getAvgY(),  archivo.getAvgX(),  iNumberOfPairs ) );
		archivo.setTheta0( calculo.calculateTheta0(  archivo.getAvgY(),  archivo.getTheta1(),  archivo.getAvgX() ) );

		archivo.setR( calculo.calculateR( iNumberOfPairs, archivo.getSumXTimesYValues(), archivo.getSumXValues(), archivo.getSumYValues(), archivo.getSumSquaredXValues(), archivo.getSumSquaredYValues() ) );
		archivo.setRSquared( calculo.calculateRSquared( archivo.getR() ) );
		
		archivo.setYPrediction( calculo.calculateYPrediction( archivo.getTheta0(), archivo.getTheta1(),  iValueForRegression ) );

		//_d=1
		//_d=5	

		archEntrada.close();
	}else{
		bExiste = false;
		cout<< "Error: Este archivo no existe" << endl;
	}
		//_d=2
	//_d=4
}

// Sirve para desplegar los resultados de los calculos obtenidos a partir de la información del archivo
//_p=desplegarInfoArchivo
void desplegarInfoArchivo(Archivo archivo, int iNumberOfPairs, int iValueForRegression){
	//_i
	cout << fixed << setprecision(5) ; // Para desplegar numeros redondeadoscon 5 decimales
	cout << "N = " << iNumberOfPairs << endl;
	cout << "xk = " << iValueForRegression << endl;
	cout << "r =  " << setprecision(5) << fixed << archivo.getR() << endl;
	cout << "r2 =  " << setprecision(5) << fixed << archivo.getRSquared() << endl;
	cout << "b0 =  " << setprecision(5) << fixed << archivo.getTheta0() << endl;
	cout << "b1 =  " << setprecision(5) << fixed << archivo.getTheta1() << endl;
	cout << "yk =  " << setprecision(5) << fixed << archivo.getYPrediction() << endl;
}

//_p=Main
//_b=11
int main(){
	//_i
	//_d=3
	string sNombreArchivo;
	bool bExiste = true;
	Archivo archivo;
	int iNumberOfPairs = 0;
	int iValueForRegression = 0;

	cout << "Ingrese el nombre del archivo: "; //_m
	cin >> sNombreArchivo;

	//_d=1
	calcularInfoArchivo(sNombreArchivo, bExiste, archivo, iNumberOfPairs, iValueForRegression ); //_m
	
	if(bExiste)
		desplegarInfoArchivo(archivo, iNumberOfPairs, iValueForRegression); //m

	return 0;
}