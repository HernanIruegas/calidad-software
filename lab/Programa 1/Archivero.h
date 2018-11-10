// Clase Archivero que guarda archivos dentro, también calcula el total de las líneas ocn información y el total de las líneas en blanco de todos los archivos dentro
// Hernán Iruegas Villarreal A00817021
// 24/01/2018

class Archivero {

	public:

		Archivero();
		Archivero(Archivo nombreArchivo, int lineasBlanco, int lineasInfo);
		int getTotalLineasBlanco();
		int getTotalLineasInfo();
		vector<Archivo> getArchivos();
		void setTotalLineasBlanco(int totalLineasBlanco);
		void setTotalLineasInfo(int totalLineasInfo);
		void setArchivo(Archivo nombreArchivo);

	private:

		vector<Archivo> archivos;
		int totalLineasBlanco;
		int totalLineasInfo;
};

Archivero::Archivero(){

	this -> totalLineasBlanco = 0;
	this -> totalLineasInfo = 0;
}

Archivero::Archivero(Archivo nombreArchivo, int lineasBlanco, int lineasInfo){

	archivos.push_back(nombreArchivo);
	this -> totalLineasBlanco = lineasBlanco;
	this -> totalLineasInfo = lineasInfo;
}

int Archivero::getTotalLineasBlanco(){

	return this -> totalLineasBlanco;
}

int Archivero::getTotalLineasInfo(){

	return this -> totalLineasInfo;
}

vector<Archivo> Archivero::getArchivos(){

	return this -> archivos;
}

void Archivero::setTotalLineasBlanco(int totalLineasBlanco){

	this -> totalLineasBlanco = this -> totalLineasBlanco + totalLineasBlanco;
}

void Archivero::setTotalLineasInfo(int totalLineasInfo){

	this -> totalLineasInfo = this -> totalLineasInfo + totalLineasInfo;
}

void Archivero::setArchivo(Archivo nombreArchivo){

	this-> archivos.push_back(nombreArchivo);
}































