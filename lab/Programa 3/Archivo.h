// Clase Archivo que guarda todos los valores resultado de las operaciones para realizar la regresión lineal
// Hernán Iruegas Villarreal A00817021
// 14/04/2018

//_p=Archivo
//_b=108
class Archivo {
	
	public:
		
		Archivo();
		string getNombre();
		double getSumXValues();
		double getSumYValues();
		double getAvgX();
		double getAvgY();
		double getSumSquaredXValues();
		double getSumSquaredYValues();
		double getSumXTimesYValues();
		double getTheta0();
		double getTheta1();
		double getR();
		double getRSquared();
		double getYPrediction();
		void setNombre( string sNombreArchivo );
		//_d=7
		void calculateInfoXAndY( vector<double> vAllXValues, vector<double> vAllYValues, int iNumberOfPairs );
		void setTheta0( double fTheta0 );
		void setTheta1( double fTheta1 );
		void setR( double fR);
		void setRSquared( double fRSquared );
		void setYPrediction( double fYPrediction );
		
	private:
		
		string sNombreArchivo;
		double fSumXValues;
		double fSumYValues;
		double fAvgX;
		double fAvgY;
		double fSumSquaredXValues;
		double fSumSquaredYValues;
		double fSumXtimesYValues;
		double fTheta0;
		double fTheta1;
		double fR;
		double fRSquared;
		double fYPrediction;	
};

//_i
Archivo::Archivo(){

	sNombreArchivo = "default.txt";
	fSumXValues = 0;
	fSumYValues = 0;
	fAvgX = 0;
	fAvgY = 0;
	fSumSquaredXValues = 0;
	fSumSquaredYValues = 0;
	fSumXtimesYValues = 0;
	fTheta0 = 0;
	fTheta1 = 0;
	fR = 0;
	fRSquared = 0;
	fYPrediction = 0;	
}

//_i
string Archivo::getNombre(){

	return this -> sNombreArchivo;
}

//_i
double Archivo::getSumXValues(){

	return this -> fSumXValues;
}

//_i
double Archivo::getSumYValues(){

	return this -> fSumYValues;
}

//_i
double Archivo::getAvgX(){

	return this -> fAvgX;
}

//_i
double Archivo::getAvgY(){

	return this -> fAvgY;
}

//_i
double Archivo::getSumSquaredXValues(){

	return this -> fSumSquaredXValues;
}

//_i
double Archivo::getSumSquaredYValues(){

	return this -> fSumSquaredYValues;
}

//_i
double Archivo::getSumXTimesYValues(){

	return this -> fSumXtimesYValues;
}

//_i
double Archivo::getTheta0(){

	return this -> fTheta0;
}

//_i
double Archivo::getTheta1(){

	return this -> fTheta1;
}

//_i
double Archivo::getR(){

	return this -> fR;
}

//_i
double Archivo::getRSquared(){

	return this -> fRSquared;
}

//_i
double Archivo::getYPrediction(){

	return this -> fYPrediction;
}

//_i
void Archivo::setNombre( string sNombreArchivo ){

	this -> sNombreArchivo = sNombreArchivo;
}

//_d=14

//_i 
void Archivo::calculateInfoXAndY( vector<double> vAllXValues, vector<double> vAllYValues, int iNumberOfPairs ){

	double fSumXValuesAux;
	double fSumYValuesAux;
	double fSumSquaredXValuesAux;
	double fSumSquaredYValuesAux;
	double fSumXtimesYValuesAux;

	for( int i = 0; i < iNumberOfPairs; i++ ){

		fSumXValuesAux += vAllXValues[i];
		fSumYValuesAux += vAllYValues[i];
		fSumSquaredXValuesAux += ( vAllXValues[i] * vAllXValues[i] );
		fSumSquaredYValuesAux += ( vAllYValues[i] * vAllYValues[i] );
		fSumXtimesYValuesAux += ( vAllXValues[i] * vAllYValues[i] );

	}

	this -> fSumXValues = fSumXValuesAux;
	this -> fSumYValues = fSumYValuesAux;
	this -> fAvgX = fSumXValuesAux / iNumberOfPairs;
	this -> fAvgY = fSumYValuesAux / iNumberOfPairs;
	this -> fSumSquaredXValues = fSumSquaredYValuesAux;
	this -> fSumSquaredYValues = fSumXtimesYValuesAux;
}

//_i
void Archivo::setTheta0( double fTheta0 ){

	this -> fTheta0 = fTheta0; 
}

//_i
void Archivo::setTheta1( double fTheta1 ){

	this -> fTheta1 = fTheta1; 
}

//_i
void Archivo::setR( double fR){

	this -> fR = fR; 
}

//_i
void Archivo::setRSquared( double fRSquared ){

	this -> fRSquared = fRSquared; 
}

//_i
void Archivo::setYPrediction( double fYPrediction ){

	this -> fYPrediction = fYPrediction; 
}











	






