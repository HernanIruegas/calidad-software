// Programa para leer valores de X y Y de un archivo para calcular un resultado utilizando regresión linear
// Hernán Iruegas Villarreal A00817021
// 14/04/2018

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // para usar abs()
#include <cmath>
#include <math.h> // Para usar la función de square root
#include <iomanip> // Para imprimir los números con la precision de 5 decimales deseadas
using namespace std;
#include "Archivo.h"
#include "CalculoRegresion.h"
#include "Simpson.h"
#include "CalculoSimpson.h"

//_p=Main
//_b=91

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
void obtenerInfoArchivo( ifstream &archEntrada, vector<double> &vAllXValues, vector<double> &vAllYValues, int &iNumberOfPairs, double &iValueForRegression, bool &validFormatting ){
	
	string linea = "", aux = "", delimitador = ",";

	getline( archEntrada, linea );
	linea = quitaEspacios( linea );

	if( linea.length() > 0 ){

		iValueForRegression = stod( linea.c_str() ); // Este valor es el primer número del archivo

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
	}else{
		validFormatting = false;
	}
}

//_i
// Sirve para obtener la información del archivo y realizar los calculos necesarios para la regresión lineal
void calcularInfoArchivo( vector<double> &vAllXValues, vector<double> &vAllYValues, string sNombreArchivo, bool &bExiste, Archivo &archivo, int &iNumberOfPairs, double &iValueForRegression ){

	bool validFormatting = true;

	ifstream archEntrada; // Se necesita para abrir los archivos del usuario

	archEntrada.open( sNombreArchivo );

	// Hay que validar que el nombre del archivo existe
	if( archEntrada ){

		// Se lee el arhivo y se consiguen todos los valores de X y Y, además del valor con el que se quiere realizar el cálculo de la regresión lineal
		obtenerInfoArchivo( archEntrada, vAllXValues, vAllYValues, iNumberOfPairs, iValueForRegression, validFormatting ); 

		if( validFormatting ){
			// Crear objeto calculo para tener acceso a las funciones que realizan los calculos sobre los valores del archivo
			CalculoRegresion calculo;

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
			cout << "Error: El formato del archivo es el incorrecto, la primera línea no puede estar vacia" << endl;
		}
	}else{
		bExiste = false;
		cout<< "Error: Este archivo no existe" << endl;
	}
}

//_i
double getP( double dXAux, int iDof, CalculoSimpson calSimpson ){

	double diferencia = 0, error = 0.0000001;
	int iNumSeg = 20;

	Simpson *pObj1 = new Simpson( dXAux, iDof, 10 ); // crear primer objeto
	pObj1 -> setP( calSimpson.calculateP( pObj1 ) ); // calcular P para el primer objeto
	
	Simpson *pObj2 = new Simpson( dXAux, iDof, 20 ); // crear segundo objeto
	pObj2 -> setP( calSimpson.calculateP( pObj2 ) ); // calcular P para el segundo objeto

	diferencia = pObj1 -> getP() - pObj2 -> getP();

	while( abs( diferencia ) >= error ){

		pObj1 = pObj2;
		iNumSeg *= 2;
		pObj2 = new Simpson( dXAux, iDof, iNumSeg );
		pObj2 -> setP( calSimpson.calculateP( pObj2 ) );
		diferencia = pObj1 -> getP() - pObj2 -> getP();
	}
	return pObj2 -> getP();
}

//_i
double getX( double dPOriginal, int iDof, CalculoSimpson calSimpson ){

	double dError = 0.00000000001;
	double dXAux = 1.0;
	double dIncrement = 0.5;

	double dPAux = getP( dXAux, iDof, calSimpson );
	double dDiferencia = dPAux - dPOriginal;
	double dDiferenciaAux = dDiferencia;

	while( abs( dDiferencia ) >= dError ){

		dDiferencia > 0 ? dXAux -= dIncrement : dXAux += dIncrement;

		if( (dDiferenciaAux > 0 && dDiferencia < 0) || (dDiferenciaAux < 0 && dDiferencia > 0) ){
			dIncrement = dIncrement / 2;
		}

		dPAux = getP( dXAux, iDof, calSimpson );
		dDiferenciaAux = dDiferencia;
		dDiferencia = dPAux - dPOriginal;
	}

	return dXAux; 
}

//_i
double calStandardDeviation( int iNumberOfPairs, int iDof, vector<double> vAllXValues, vector<double> vAllYValues, double dTheta0, double dTheta1 ){

	double aux = 0;
	
	for( int i = 0; i < iNumberOfPairs; i++ ){
		aux += ( vAllYValues[ i ] - dTheta0 - ( dTheta1 *  vAllXValues[ i ] ) ) * ( vAllYValues[ i ] - dTheta0 - ( dTheta1 *  vAllXValues[ i ] ) );
	}
	
	return sqrt( 1.0 / iDof * aux );
}

//_i
double calRightSideRangeEquation( int iNumberOfPairs, double iValueForRegression, double dAvgX, vector<double> vAllXValues ){

	double aux = 0;

	for( int i = 0; i < iNumberOfPairs; i++ ){
		aux += ( vAllXValues[ i ] - dAvgX ) * ( vAllXValues[ i ] - dAvgX );
	}

	return sqrt( 1.0 + ( 1.0 / iNumberOfPairs ) + ( ( ( iValueForRegression - dAvgX ) * ( iValueForRegression - dAvgX ) ) / aux )  )  ;
}

//_i
// Sirve para desplegar los resultados de los calculos obtenidos a partir de la información del archivo
void desplegarInfoArchivo( Archivo archivo, int iNumberOfPairs, double iValueForRegression, double dSignificancia, double dRange, double dUppLimit, double dLowLimit ){ //_m
	
	cout << fixed << setprecision(5) ; // Para desplegar numeros redondeados con 5 decimales
	cout << "N  = " << iNumberOfPairs << endl;
	cout << "xk = " << setprecision(5) << fixed << iValueForRegression << endl;
	cout << "r  = " << setprecision(5) << fixed << archivo.getR() << endl;
	cout << "r2 = " << setprecision(5) << fixed << archivo.getRSquared() << endl;
	cout << "b0 = " << setprecision(5) << fixed << archivo.getTheta0() << endl;
	cout << "b1 = " << setprecision(5) << fixed << archivo.getTheta1() << endl;
	cout << "yk = " << setprecision(5) << fixed << archivo.getYPrediction() << endl;
	cout << "sig= " << setprecision(10) << fixed << dSignificancia << endl;
	cout << "ran= " << setprecision(5) << fixed << dRange << endl;
	cout << "LS = " << setprecision(5) << fixed << dUppLimit << endl;
	dLowLimit > 0 ? cout << "LI = " << setprecision(5) << fixed << dLowLimit << endl : cout << "LI = 0.00000" << endl;
	
}

//_i
int main(){

	string sNombreArchivo;
	bool bExiste = true;
	Archivo archivo;
	int iNumberOfPairs = 0;
	double iValueForRegression = 0;
	vector<double> vAllXValues;
	vector<double> vAllYValues;
	int iNumSeg = 20; // utilizado para calcular el resultado de simpson
	double diferencia = 0; // auxiliar para asegurar que el resultado de simpson cumpla con el margen de error
	double error = 0.00000001; // margen de error permitido para el resultado de simpson
	CalculoSimpson calSimpson; // objeto para acceder a las funciones que calculan la integral simpson

	cout << "Ingrese el nombre del archivo: "; 
	cin >> sNombreArchivo;

	calcularInfoArchivo( vAllXValues, vAllYValues, sNombreArchivo, bExiste, archivo, iNumberOfPairs, iValueForRegression );

	if( bExiste ){ // validar que el archivo exista

		/* CALCULAR LA SIGNIFICANCIA */

		int iDof = iNumberOfPairs - 2; // grados de libertad para el calculo de simpson

		double dX = abs( archivo.getR() ) * sqrt( iDof ) / sqrt( 1 - ( archivo.getR() * archivo.getR() ) ); // valor de "x" para el calculo de simpson

		Simpson *pObj1 = new Simpson( dX, iDof, 10 ); 

		pObj1 -> setP( calSimpson.calculateP( pObj1 ) ); 

		Simpson *pObj2 = new Simpson( dX, iDof, 20 );

		pObj2 -> setP( calSimpson.calculateP( pObj2 ) );

		diferencia = pObj1 -> getP() - pObj2 -> getP();

		// Obtener un resultado de la integral simpson que cumpla con el margen de error
		while( abs( diferencia ) >= error ){

			pObj1 = pObj2;
			iNumSeg *= 2;
			pObj2 = new Simpson( dX, iDof, iNumSeg );
			pObj2 -> setP( calSimpson.calculateP( pObj2 ) );
			diferencia = pObj1 -> getP() - pObj2 -> getP();
		}
	 
		double dSignificancia = 1 - ( 2 * pObj2 -> getP() );

		/* CALCULAR EL RANGO, UPPER LIMIT Y LOWER LIMIT */

		double dXGivenP = getX( 0.35, iDof, calSimpson ); // calcular el valor de x dado p = 0.35 y dof = n - 2

		double dStdDeviation = calStandardDeviation( iNumberOfPairs, iDof, vAllXValues, vAllYValues, archivo.getTheta0(), archivo.getTheta1() );

		double rightSideRangeEquation = calRightSideRangeEquation( iNumberOfPairs, iValueForRegression, archivo.getAvgX(), vAllXValues );

		double dRange = dXGivenP * dStdDeviation * rightSideRangeEquation;

		double dUppLimit = archivo.getYPrediction() + dRange;

		double dLowLimit = archivo.getYPrediction() - dRange;

		/* DESPLEGAR RESULTADOS */
	
		desplegarInfoArchivo( archivo, iNumberOfPairs, iValueForRegression, dSignificancia, dRange, dUppLimit, dLowLimit ); //_m

	}

	return 0;
}













