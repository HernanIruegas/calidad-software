// Programa para leer archivos y desplegar las partes de los mismos, asi como el total de LDC de todos los archivos.
// Hernán Iruegas Villarreal A00817021
// 18/02/2018
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <map>
#include <queue>
using namespace std;
#include "Parte.h"
#include "Archivo.h"
#include "Archivero.h"

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

// Sirve para limpiar una línea, quita los caracteres que están dentro de strings
//_p=quitaStrings
string quitaStrings( string &linea ){
	//_i
	string lineaAux = ""; // Contiene una linea sin caracteres dentro de strings
	bool insideString = false;

	// Añado caracteres que no estén dentro de un string
	for( int i = 0; i < linea.length(); i++ ){
		if( linea[i] == '"' )
			insideString = !insideString;
        if( !insideString ){
          lineaAux += linea[i];
        }
    }

    return lineaAux;
}

// Valida que una linea no contenga puros espacios en blanco, que no sea parte de un comentario de tipo bloque ni que tampoco
// tenga un solo caracter como '{' o '}'
//_p=validaLDC
bool validaLDC( string linea, stack<string> &stackComment ){
	//_i
	if( linea.length() > 0 ){

		// Tengo que asegurarme que estos caracteres no estén dentro de un string, porque en ese caso no sería un comentario
		if( linea.find("/*") != string::npos ) 
			stackComment.push( "/*" );

		if( stackComment.empty() ){

			if( !( linea.length() == 1 && ( linea[0] == '}' || linea[0] == '{' ) ) )
				return true;
			else
				return false;

		}else{

			if( linea.find("*/") != string::npos ) 
				stackComment.pop();
			return false;
		}
	}else 
		return false;

}

//_p=obtenerPartes

// Sirve para actualizar en el mapa la información de la Parte en cuanto a sus líneas
void actualizaDatosParte( map<string, Parte> &partesArchivo, string nombreParte, int totalLDCParte, int base, int deleted, int modified, int added, int items ){

	if( partesArchivo.find( nombreParte ) != partesArchivo.end() ){ // La parte ya existe, solo hay que actualizar valores
		partesArchivo[ nombreParte ].setTotalLDC( totalLDCParte );
		partesArchivo[ nombreParte ].setBase( base );
		partesArchivo[ nombreParte ].setDeleted( deleted );
		partesArchivo[ nombreParte ].setModified( modified );
		partesArchivo[ nombreParte ].setAdded( added );
		partesArchivo[ nombreParte ].setItems( items );
	}
	else{ // La parte no existe, por lo que se crea un nuevo objeto y se introduce en el mapa
		Parte parte( nombreParte, totalLDCParte, base, deleted, modified, added, items );
		partesArchivo[ nombreParte ] = parte;
	}
}

// Sirve para sumar un número dentro de un comentario a alguna de las propiedades de la Parte
// la variable tipoDeLDC puede representar a las líneas base o a las líneas deleted
void obtenerNumeroEnCommentLinea( string delimitador, string linea, int &tipoDeLDC){

	// Se necesita obtener el número que representa las líneas base o deleted
	// Se elimina lo que está antes del número en el string
	int pos = linea.find( delimitador );
	linea.erase(0, pos + delimitador.length() );

	tipoDeLDC += atoi(linea.c_str());
}

// Sirve para leer el archivo completo y obtener todas sus partes y LDC
void obtenerPartes( ifstream &archEntrada, map<string, Parte> &partesArchivo, int &totalLDCArchivo ){

	int totalLDCParte = 0, base = 0, deleted = 0, added = 0, modified = 0, items = 0; // Propiedades de las partes
	bool partes = false, primeraVez = true;
	string nuevaParte = "", aux = "", linea = "";
	stack<string> stackComment;
	//_i
	while( getline( archEntrada, linea ) ){

		linea = quitaEspacios( linea );

		linea = quitaStrings( linea );

		if( validaLDC( linea, stackComment ) ){

			// Aseguramos que sea una LDC contable
			if( linea.find( "//" ) == string::npos || linea.substr( 0, 2 ) != "//")
				( partes ) ? totalLDCArchivo++, totalLDCParte++ : totalLDCArchivo++;
			
			// Encontramos una nueva parte dentro del archivo, tenemos que guardar los datos de la parte anterior
			if( linea.find( "_p" ) != string::npos ){

				partes = true;
				aux = nuevaParte;
				added = totalLDCParte - base + deleted; // Calculamos las lineas agregadas de la parte

				// Se necesita obtener el nombre de la parte
				// Se elimina lo que está antes del nombre en el string
				string delimitador = "_p=";
				int pos = linea.find( "_p=" );
				nuevaParte = linea.erase(0, pos + delimitador.length() );

				// Se guarda la información de la parte en el mapa
				// Si no existe entonces se crea un nuevo objeto, si ya existe entonces se actualiza
				if( primeraVez ){
					Parte parte( nuevaParte, totalLDCParte, base, deleted, modified, added, items );
					partesArchivo[ nuevaParte ] = parte;  
					primeraVez = false;
				}else{
					actualizaDatosParte( partesArchivo, aux, totalLDCParte, base, deleted, modified, added, items );
				}

				totalLDCParte = 0;
				base = 0;
				deleted = 0;
				added = 0;
				modified = 0;
				items = 0;

			}
			//_i
			if( linea.find( "_i" ) != string::npos )
				items++;

			if( linea.find( "_m" ) != string::npos )
				modified++;
		
			if( linea.find( "_b" ) != string::npos )
				obtenerNumeroEnCommentLinea( "_b=", linea, base);

			if( linea.find( "_d" ) != string::npos )
				obtenerNumeroEnCommentLinea( "_d=", linea, deleted);

		}		
	}

	added = totalLDCParte - base + deleted; // Calculamos las lineas agregadas de la parte
	//_i
	// Tengo que actualizar para la ultima parte del archivo
	actualizaDatosParte( partesArchivo, nuevaParte, totalLDCParte, base, deleted, modified, added, items );
}

// Sirve para actualizar las propiedas del archivo con las partes que se encuentran en el mapa de partes
//_p=actualizarArchivo
void actualizarArchivo( Archivo &archivo, map<string, Parte> &partesArchivo, int &totalLDCArchivo, string nombreArchivo ){
	//_i
	archivo.setNombre( nombreArchivo );
	archivo.setTotalLDC( totalLDCArchivo );

	//_i
	for( map<string, Parte>::iterator it = partesArchivo.begin(); it != partesArchivo.end(); it++ ){

		if( partesArchivo[ it -> first ].getBase() > 0  && ( partesArchivo[ it -> first ].getModified() > 0 || partesArchivo[ it -> first ].getDeleted() > 0 || partesArchivo[ it -> first ].getAdded() > 0 ) )
			archivo.setPartesBase( partesArchivo[ it -> first ] ); // Es una parte base
		else{
			if( partesArchivo[ it -> first ].getBase() > 0 && partesArchivo[ it -> first ].getModified() == 0 && partesArchivo[ it -> first ].getDeleted() == 0  && partesArchivo[ it -> first ].getAdded() == 0 )
				archivo.setPartesReusadas( partesArchivo[ it -> first ] ); // Es una parte reusada
			else{
				if( partesArchivo[ it -> first ].getBase() == 0 && partesArchivo[ it -> first ].getModified() == 0 && partesArchivo[ it -> first ].getDeleted() == 0  && partesArchivo[ it -> first ].getAdded() > 0 )
					archivo.setPartesAgregadas( partesArchivo[ it -> first ] ); // Es una parte nueva
			}
		}
	}
}

// Sirve para crear archivos y agregarlos al archivero
// Recibe el mapa ArchivosUnicos para validar que no se repitan los nombres de los archivos
// Recibe cantidadArchivos y la variable i del ciclo for donde se manda a llamar esta función, con el propósito de controlar cuantos archivos se deben de desplegar en pantalla 
//_p=agregarArchivos
//_b=26
void agregarArchivos(map<string, string>& ArchivosUnicos, Archivero &archivos, int &cantidadArchivos, int &i){
	//_d=1
	//_i
	ifstream archEntrada; // Se necesita para abrir los archivos del usuario
	string nombreArchivo;
	map<string, Parte> partesArchivo; // Contiene las partes del archivo que se está leyendo
	int totalLDCArchivo = 0;

	cout << "\nIngrese el nombre del archivo: ";
	cin >> nombreArchivo;

	// Hay que validar que el nombre del archivo no se repita
	if( ArchivosUnicos.find(nombreArchivo) == ArchivosUnicos.end() ){

		archEntrada.open(nombreArchivo);

		// Hay que validar que el nombre del archivo existe
		if(archEntrada){

			// Se lee el arhivo y se consiguen todas sus partes y LDC
			obtenerPartes( archEntrada, partesArchivo, totalLDCArchivo ); 

			// Se crea el archivo y se actualiza con sus partes y nombre
			Archivo archivo; //_m
			actualizarArchivo( archivo, partesArchivo, totalLDCArchivo, nombreArchivo);

			// Se agrega el archivo al archivero
			archivos.setArchivo(archivo); 

			//_i
			//_d=2
			// Actualizo las propiedades del archivero
			archivos.setTotalLDC( archivo.getTotalLDC() ); //_m
			archivos.setPartesBase( archivo.getPartesBase() ); //_m
			archivos.setPartesAgregadas( archivo.getPartesAgregadas() );
			archivos.setPartesReusadas( archivo.getPartesReusadas() );

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
// Tambien escribe estos resultados en un archivo de salida llamado ConteoLDC.txt
//_p=desplegarPartes
//_b=11
void desplegarPartes(int cantidadArchivos, Archivero archivos){//_m

	ofstream archSalida;
	string nombreArchivoSalida = "ConteoLDC.txt";

	archSalida.open(nombreArchivoSalida);
	//_i
	cout << "\nPARTES BASE:" << endl;
	archSalida << "\nPARTES BASE:" << endl;
	for(int i = 0; i < archivos.getPartesBase().size(); i++){
		//_d=4
		cout << "\t" << archivos.getPartesBase()[i].getNombreParte() << ": ";
		archSalida << "\t" << archivos.getPartesBase()[i].getNombreParte() << ": ";

		cout << "T=" << archivos.getPartesBase()[i].getTotalLDC() << ", ";
		archSalida << "T=" << archivos.getPartesBase()[i].getTotalLDC() << ", ";

		cout << "I=" << archivos.getPartesBase()[i].getItems() << ", ";
		archSalida << "I=" << archivos.getPartesBase()[i].getItems() << ", ";

		cout << "B=" << archivos.getPartesBase()[i].getBase() << ", ";
		archSalida << "B=" << archivos.getPartesBase()[i].getBase() << ", ";

		cout << "D=" << archivos.getPartesBase()[i].getDeleted() << ", ";
		archSalida << "D=" << archivos.getPartesBase()[i].getDeleted() << ", ";

		cout << "M=" << archivos.getPartesBase()[i].getModified() << ", ";
		archSalida << "M=" << archivos.getPartesBase()[i].getModified() << ", ";

		cout << "A=" << archivos.getPartesBase()[i].getAdded() << endl;
		archSalida << "A=" << archivos.getPartesBase()[i].getAdded() << endl;
	}
	cout << "----------------------------------------------------" << endl;
	archSalida << "----------------------------------------------------" << endl;

	cout << "PARTES NUEVAS:" << endl;
	archSalida << "\nPARTES NUEVAS:" << endl;
	for(int i = 0; i < archivos.getPartesAgregadas().size(); i++){

		cout << "\t" << archivos.getPartesAgregadas()[i].getNombreParte() << ": ";
		archSalida << "\t" << archivos.getPartesAgregadas()[i].getNombreParte() << ": ";

		cout << "T=" << archivos.getPartesAgregadas()[i].getTotalLDC() << ", ";
		archSalida << "T=" << archivos.getPartesAgregadas()[i].getTotalLDC() << ", ";

		cout << "I=" << archivos.getPartesAgregadas()[i].getItems() << endl;
		archSalida << "I=" << archivos.getPartesAgregadas()[i].getItems() << endl;

	}
	cout << "----------------------------------------------------" << endl;
	archSalida << "----------------------------------------------------" << endl;

	cout << "PARTES REUSADAS:" << endl;
	archSalida << "\nPARTES REUSADAS:" << endl;
	for(int i = 0; i < archivos.getPartesReusadas().size(); i++){

		cout << "\t" << archivos.getPartesReusadas()[i].getNombreParte() << ": ";
		archSalida << "\t" << archivos.getPartesReusadas()[i].getNombreParte() << ": ";

		cout << "T=" << archivos.getPartesReusadas()[i].getTotalLDC() << ", ";
		archSalida << "T=" << archivos.getPartesReusadas()[i].getTotalLDC() << ", ";

		cout << "I=" << archivos.getPartesReusadas()[i].getItems() << ", ";
		archSalida << "I=" << archivos.getPartesReusadas()[i].getItems() << ", ";

		cout << "B=" << archivos.getPartesReusadas()[i].getBase() << endl;
		archSalida << "B=" << archivos.getPartesReusadas()[i].getBase() << endl;

	}
	cout << "----------------------------------------------------" << endl;
	archSalida << "----------------------------------------------------" << endl;

	//_d=4
	cout << "Total de LDC:" << archivos.getTotalLDC() << endl;
	archSalida << "\nTotal de LDC:" << archivos.getTotalLDC() << endl;

	archSalida.close();
}

//_p=Main
//_b=11
int main(){

	//_d=2
	map<string, string> ArchivosUnicos; // Contiene los nombres de los archivos únicos, sirve para validar que un archivo no se repita
	int cantidadArchivos; 
	Archivero archivos; // Contiene a los archivos que el usuario registra

	cout << "Cuantos archivos desea ingresar? ";
	cin >> cantidadArchivos;

	for(int i = 0; i < cantidadArchivos; i++){

		agregarArchivos(ArchivosUnicos, archivos, cantidadArchivos, i);
	}

	if( cantidadArchivos > 0 )
		desplegarPartes(cantidadArchivos, archivos);

	return 0;
}