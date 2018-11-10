// Clase Archivo que guarda el nombre del archivo, su total de LDC y sus partes clasificadas
// Hernán Iruegas Villarreal A00817021
// 18/02/2018

//_p=Archivo
//_b=34
class Archivo {
	//_i
	public:
		//_d=4
		Archivo();
		Archivo( string nombreArchivo, int totalLDC, vector<Parte> partesBase, vector<Parte> partesAgregadas, vector<Parte> partesReusadas );//_m
		string getNombre();
		int getTotalLDC();
		vector<Parte> getPartesBase();
		vector<Parte> getPartesAgregadas();
		vector<Parte> getPartesReusadas();
		void setNombre( string nombreArchivo );
		void setTotalLDC( int totalLDC );
		void setPartesBase( Parte parteBase );
		void setPartesAgregadas( Parte parteAgregada );
		void setPartesReusadas( Parte parteReusada );
	//_i
	private:
		//_d=2
		string nombreArchivo;
		int totalLDC;
		vector<Parte> partesBase;
		vector<Parte> partesAgregadas;
		vector<Parte> partesReusadas;
	
};

Archivo::Archivo(){

	this -> nombreArchivo = "default.txt";
	this -> totalLDC = 0; //_m
}

Archivo::Archivo( string nombreArchivo, int totalLDC, vector<Parte> partesBase, vector<Parte> partesAgregadas, vector<Parte> partesReusadas ){//_m
	//_d=2
	this -> nombreArchivo = nombreArchivo;
	this -> totalLDC = totalLDC;
	for( int i = 0; i < partesBase.size(); i++ ){
		this -> partesBase.push_back( partesBase[i] );
	}
	for( int i = 0; i < partesAgregadas.size(); i++ ){
		this -> partesAgregadas.push_back( partesAgregadas[i] );
	}
	for( int i = 0; i < partesReusadas.size(); i++ ){
		this -> partesReusadas.push_back( partesReusadas[i] );
	}
}

string Archivo::getNombre(){

	return this -> nombreArchivo;
}

int Archivo::getTotalLDC(){

	return this -> totalLDC;
}

vector<Parte> Archivo::getPartesBase(){

	return this -> partesBase;
}

vector<Parte> Archivo::getPartesAgregadas(){

	return this -> partesAgregadas;
}

vector<Parte> Archivo::getPartesReusadas(){

	return this -> partesReusadas;
}

void Archivo::setNombre(string nombreArchivo){

	this -> nombreArchivo = nombreArchivo;
}

void Archivo::setTotalLDC( int totalLDC ){

	this -> totalLDC = this -> totalLDC + totalLDC;
}

void Archivo::setPartesBase( Parte parteBase ){

	partesBase.push_back(parteBase);
}

void Archivo::setPartesAgregadas( Parte parteAgregada ){

	partesAgregadas.push_back(parteAgregada);
}

void Archivo::setPartesReusadas( Parte parteReusada ){

	partesReusadas.push_back(parteReusada);
}





































