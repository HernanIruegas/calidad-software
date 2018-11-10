// Clase Archivo que guarda todos los valores resultado de las operaciones para realizar la regresión lineal multivariable
// Hernán Iruegas Villarreal A00817021
// 22/04/2018

//_p=Archivo
//_b=108
class Archivo{
	
	public:
		
		Archivo();
		string getNombre();
		vector< vector< double > > getMat( int iNumberOfQuadruples ); // regresa una matriz lista para ser reducida por gauss
		vector< double > getBetas(); // regresa resultado de reducción por gauss
		double getZPrediction();
		void setNombre( string sNombreArchivo );
		void calculateInfo( vector< double > vAllWValues, vector< double > vAllXValues, vector< double > vAllYValues, vector< double > vAllZValues, int iNumberOfQuadruples );
		void setBetas( vector< double > vBetas );
		void setZPrediction( vector< double > vBetas, double dWk, double dXk, double dYK );

	private:
		
		string sNombreArchivo;
		//_d=12
		double dSumW;
		double dSumX;
		double dSumY;
		double dSumZ;
		double dSquaredW;
		double dWTimesX;
		double dWTimesY;
		double dWTimesZ;
		double dSquaredX;
		double dXTimesY;
		double dXTimesZ;
		double dSquaredY;
		double dYTimesZ;
		vector< double > vBetas;
		double dZk;

};

//_i
Archivo::Archivo(){

	sNombreArchivo = "default.txt";
	//_d=12
	dSumW = 0;
	dSumX = 0;
	dSumY = 0;
	dSumZ = 0;
	dSquaredW = 0;
	dWTimesX = 0;
	dWTimesY = 0;
	dWTimesZ = 0;
	dSquaredX = 0;
	dXTimesY = 0;
	dXTimesZ = 0;
	dSquaredY = 0;
	dYTimesZ = 0;
	dZk = 0;	
}

//_i
string Archivo::getNombre(){

	return this -> sNombreArchivo;
}

//_i
vector< vector<double> > Archivo::getMat( int iNumberOfQuadruples ){
	vector< vector<double> > matGauss = {	{ iNumberOfQuadruples * 1.0, dSumW, dSumX, dSumY, dSumZ },
                                        	{ dSumW, dSquaredW, dWTimesX, dWTimesY, dWTimesZ },
                                        	{ dSumX, dWTimesX, dSquaredX, dXTimesY, dXTimesZ },
                                        	{ dSumY, dWTimesY, dXTimesY, dSquaredY, dYTimesZ } };

	return matGauss;
}

//_i
vector< double > Archivo::getBetas(){

	return vBetas;
}

//_i
double Archivo::getZPrediction(){

	return dZk;
}

//_d=6

//_i
void Archivo::calculateInfo( vector<double> vAllWValues, vector<double> vAllXValues, vector<double> vAllYValues, vector<double> vAllZValues, int iNumberOfQuadruples ){

	for( int i = 0; i < iNumberOfQuadruples; i++){

		dSumW += vAllWValues[ i ];
		dSumX += vAllXValues[ i ];
		dSumY += vAllYValues[ i ];
		dSumZ += vAllZValues[ i ];
		dSquaredW += vAllWValues[ i ] * vAllWValues[ i ];
		dWTimesX += vAllWValues[ i ] * vAllXValues[ i ];
		dWTimesY += vAllWValues[ i ] * vAllYValues[ i ];
		dWTimesZ += vAllWValues[ i ] * vAllZValues[ i ];
		dSquaredX += vAllXValues[ i ] * vAllXValues[ i ];
		dXTimesY += vAllXValues[ i ] * vAllYValues[ i ];
		dXTimesZ += vAllXValues[ i ] * vAllZValues[ i ];
		dSquaredY += vAllYValues[ i ] * vAllYValues[ i ];
		dYTimesZ += vAllYValues[ i ] * vAllZValues[ i ];
	}
}

//_i
void Archivo::setBetas( vector< double > vBetas ){

	for( int i = 0; i < vBetas.size(); i++ ){
		this -> vBetas.push_back( vBetas[ i ] );
	}
}

//_i
void Archivo::setZPrediction( vector< double > vBetas, double dWk, double dXk, double dYk ){

	dZk = vBetas[0] + vBetas[1] * dWk + vBetas[2] * dXk + dYk * vBetas[3]; // obtener predicción de regresión lineal multivariable

}

//_i
void Archivo::setNombre( string sNombreArchivo ){

	this -> sNombreArchivo = sNombreArchivo;
}



















	






