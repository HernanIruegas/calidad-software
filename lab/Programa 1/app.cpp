// 
// Hernán Iruegas Villarreal A00817021
// 28/01/2018
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include "Archivo.h"
#include "Archivero.h"
using namespace std;

// Sirve para contar las líneas en blanco y con información de cierto archivo
void contarLineas(ifstream &archEntrada, int &lineasBlanco, int &lineasInfo){

	string linea = "";

    while(getline(archEntrada, linea)){

    	string lineaAux = ""; 

    	// Hay que limpiar la línea leída de todos aquellos espacios en blanco
    	for(int i = 0; i < linea.length(); i++){
            if(linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\r' && linea[i] != '\v'){
              lineaAux += linea[i];
            }
        }

    	( lineaAux.length() == 0 ) ? lineasBlanco++ :  lineasInfo++;
    }
}

// Sirve para crear archivos y agregarlos al archivero
// Recibe el mapa ArchivosUnicos para validar que no se repitan los nombres de los archivos
// Recibe el priority queue pqLineasInfo para ordenar las líneas con información de los archivos
// Recibe cantidadArchivos y la variable i del ciclo for donde se manda a llamar esta función, con el propósito de controlar cuantos archivos se deben de desplegar en pantalla 
void agregarArchivos(map<string, string>& ArchivosUnicos, Archivero &archivos, priority_queue<int, std::vector<int>, std::greater<int> >& pqLineasInfo, map<int, Archivo>& mArchivos, int &cantidadArchivos, int &i){

	ifstream archEntrada; // Se necesita para abrir los archivos del usuario
	string nombreArchivo;
	int lineasBlanco = 0, lineasInfo = 0;

	cout << "\nIngrese el nombre del archivo: ";
	cin >> nombreArchivo;

	// Hay que validar que el nombre del archivo no se repita
	if( ArchivosUnicos.find(nombreArchivo) == ArchivosUnicos.end() ){

		archEntrada.open(nombreArchivo);

		// Hay que validar que el nombre del archivo existe
		if(archEntrada){
			//funcion para contar lineas y ponerlas en lineasBlanco, lineasInfo;
			contarLineas(archEntrada, lineasBlanco, lineasInfo);

			// Se crea el archivo y se agrega al archivero
			Archivo archivo(nombreArchivo, lineasBlanco, lineasInfo); 
			archivos.setArchivo(archivo); 

			// Actualizo las propiedades del archivero
			archivos.setTotalLineasBlanco(archivo.getLineasBlanco());
			archivos.setTotalLineasInfo(archivo.getLineasInfo());

			// Actualizo el orden de los archivos 
			pqLineasInfo.push(archivo.getLineasInfo());
			mArchivos[archivo.getLineasInfo()] = archivo;

			archEntrada.close();
			ArchivosUnicos[nombreArchivo] = nombreArchivo;
		}else{

			cout<< "Error: Este archivo no existe" << endl;
			cantidadArchivos -= 1;
			i -= 1;
		}

	}else{ // El nombre del archivo es repetido

		cout << "Error: Este archivo es repetido, introduzca archivos únicos" << endl;
		cantidadArchivos -= 1;
		i -= 1;
	}

}

// Sirve para desplegar en pantalla todos los archivos validos que el usuario registro, los que se encuentran dentro del archivero
void desplegarArchivos(int cantidadArchivos, priority_queue<int, std::vector<int>, std::greater<int> >& pqLineasInfo, map<int, Archivo>& mArchivos, Archivero archivos){

	for(int i = 0; i < cantidadArchivos; i++){

		cout << "\nNombre del archivo: " << mArchivos[pqLineasInfo.top()].getNombre() << endl;
		cout << "Cantidad de líneas en blanco: " << mArchivos[pqLineasInfo.top()].getLineasBlanco() << endl;
		cout << "Cantidad de líneas con información: " << mArchivos[pqLineasInfo.top()].getLineasInfo() << endl;
		cout << "----------------------------------------------------" << endl;
		pqLineasInfo.pop();
	}

	cout << "\nTOTALES:" << endl;
	cout << "Cantidad de archivos: " << cantidadArchivos << endl;
	cout << "Cantidad total de líneas en blanco: " << archivos.getTotalLineasBlanco() << endl;
	cout << "Cantidad total de líneas con información: " << archivos.getTotalLineasInfo() << "\n" << endl;
}

int main(){

	priority_queue<int, std::vector<int>, std::greater<int> > pqLineasInfo; // Contiene las lineas con información de los archivos ordenadas ascendentemente
	map<int, Archivo> mArchivos; // Contiene la relación entre los archivos (objetos) y su cantidad de líneas con información
	map<string, string> ArchivosUnicos; // Contiene los nombres de los archivos únicos, sirve para validar que un archivo no se repita
	int cantidadArchivos; 
	Archivero archivos; // Contiene a los archivos que el usuario registra

	cout << "Cuantos archivos desea ingresar? ";
	cin >> cantidadArchivos;

	for(int i = 0; i < cantidadArchivos; i++){

		agregarArchivos(ArchivosUnicos, archivos, pqLineasInfo, mArchivos, cantidadArchivos, i);
	}

	if( cantidadArchivos > 0 )
		desplegarArchivos(cantidadArchivos, pqLineasInfo, mArchivos, archivos);

	return 0;
}