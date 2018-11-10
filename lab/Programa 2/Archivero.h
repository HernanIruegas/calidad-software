// Clase Archivero que guarda archivos dentro. Contiene las LDC totales del archivero y todas las partes de los archivos.
// Hernán Iruegas Villarreal A00817021
// 18/02/2018

//_p=Archivero
//_b=33
class Archivero {
	//_i
	public:
		//_d=4
		Archivero();
		Archivero( Archivo nombreArchivo, int totalLDC, vector<Parte> partesBase, vector<Parte> partesAgregadas, vector<Parte> partesReusadas ); //_m
		int getTotalLDC();
		vector<Archivo> getArchivos();
		vector<Parte> getPartesBase();
		vector<Parte> getPartesAgregadas();
		vector<Parte> getPartesReusadas();
		void setTotalLDC(int totalLDC);
		void setPartesBase( vector<Parte> partesBase );
		void setPartesAgregadas( vector<Parte> partesAgregadas );
		void setPartesReusadas( vector<Parte> partesReusadas );
		void setArchivo( Archivo nombreArchivo );
	//_i
	private:
		//_d=2
		int totalLDC;
		vector<Archivo> archivos;
		vector<Parte> partesBase;
		vector<Parte> partesAgregadas;
		vector<Parte> partesReusadas;
		
};

Archivero::Archivero(){

	this -> totalLDC = 0; //_m
}

Archivero::Archivero( Archivo nombreArchivo, int totalLDC, vector<Parte> partesBase, vector<Parte> partesAgregadas, vector<Parte> partesReusadas) {//_m
	//_d=2
	archivos.push_back(nombreArchivo);
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

int Archivero::getTotalLDC(){

	return this -> totalLDC;
}

vector<Archivo> Archivero::getArchivos(){

	return this -> archivos;
}

vector<Parte> Archivero::getPartesBase(){

	return this -> partesBase;
}

vector<Parte> Archivero::getPartesAgregadas(){

	return this -> partesAgregadas;
}

vector<Parte> Archivero::getPartesReusadas(){

	return this -> partesReusadas;
}

void Archivero::setTotalLDC( int totalLDC ){

	this -> totalLDC = this -> totalLDC + totalLDC;
}

void Archivero::setPartesBase( vector<Parte> partesBase ){

	for( int i = 0; i < partesBase.size(); i++ ){
		this -> partesBase.push_back( partesBase[i] );
	}
}

void Archivero::setPartesAgregadas( vector<Parte> partesAgregadas ){

	for( int i = 0; i < partesAgregadas.size(); i++ ){
		this -> partesAgregadas.push_back( partesAgregadas[i] );
	}
}

void Archivero::setPartesReusadas( vector<Parte> partesReusadas ){

	for( int i = 0; i < partesReusadas.size(); i++ ){
		this -> partesReusadas.push_back( partesReusadas[i] );
	}
}

void Archivero::setArchivo(Archivo nombreArchivo){

	this-> archivos.push_back(nombreArchivo);
}































