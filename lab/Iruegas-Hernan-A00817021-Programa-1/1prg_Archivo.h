// Clase Archivo que guarda el nombre del archivo, las líneas en blanco que contiene y las líneas con información que contiene
// Hernán Iruegas Villarreal A00817021
// 24/01/2018

class Archivo {

	public:

		Archivo();
		Archivo(string nombreArchivo, int lineasBlanco, int lineasInfo);
		int getLineasBlanco();
		int getLineasInfo();
		string getNombre();
		void setLineasBlanco(int lineasBlanco);
		void setLineasInfo(int lineasInfo);
		void setNombre(string nombreArchivo);

	private:

		string nombreArchivo;
		int lineasBlanco;
		int lineasInfo;
	
};

Archivo::Archivo(){

	this -> nombreArchivo = "default.txt";
	this -> lineasBlanco = 0;
	this -> lineasInfo = 0;
}

Archivo::Archivo(string nombreArchivo, int lineasBlanco, int lineasInfo){

	this -> nombreArchivo = nombreArchivo;
	this -> lineasBlanco = lineasBlanco;
	this -> lineasInfo = lineasInfo;
}

int Archivo::getLineasBlanco() {

	return lineasBlanco;
}

int Archivo::getLineasInfo() {

	return lineasInfo;
}

string Archivo::getNombre(){

	return nombreArchivo;
}

void Archivo::setLineasBlanco(int lineasBlanco){

	this -> lineasBlanco = lineasBlanco;
}

void Archivo::setLineasInfo(int lineasInfo){

	this -> lineasInfo = lineasInfo;
}

void Archivo::setNombre(string nombreArchivo){

	this -> nombreArchivo = nombreArchivo;
}




































