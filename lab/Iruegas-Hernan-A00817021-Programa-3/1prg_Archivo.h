// Clase Archivo que guarda todos los valores resultado de las operaciones para realizar la regresión lineal
// Hernán Iruegas Villarreal A00817021
// 04/03/2018

//_p=Archivo
//_b=34
class Archivo {
	//_i
	public:
		//_d=9
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
		void setSumXValues( double fSumXValues );
		void setSumYValues( double fSumYValues );
		void setAvgX( double fAvgX );
		void setAvgY( double fAvgY );
		void setSumSquaredXValues( double fSumSquaredXValues );
		void setSumSquaredYValues( double fSumSquaredYValues );
		void setSumXTimesYValues( double fSumXtimesYValues );
		void setTheta0( double fTheta0 );
		void setTheta1( double fTheta1 );
		void setR( double fR);
		void setRSquared( double fRSquared );
		void setYPrediction( double fYPrediction );
		
	//_i
	private:
		//_d=4
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
//_d=9

string Archivo::getNombre(){

	return this -> sNombreArchivo;
}

double Archivo::getSumXValues(){

	return this -> fSumXValues;
}

double Archivo::getSumYValues(){

	return this -> fSumYValues;
}

double Archivo::getAvgX(){

	return this -> fAvgX;
}

double Archivo::getAvgY(){

	return this -> fAvgY;
}

double Archivo::getSumSquaredXValues(){

	return this -> fSumSquaredXValues;
}

double Archivo::getSumSquaredYValues(){

	return this -> fSumSquaredYValues;
}

double Archivo::getSumXTimesYValues(){

	return this -> fSumXtimesYValues;
}

double Archivo::getTheta0(){

	return this -> fTheta0;
}

double Archivo::getTheta1(){

	return this -> fTheta1;
}

double Archivo::getR(){

	return this -> fR;
}

double Archivo::getRSquared(){

	return this -> fRSquared;
}

double Archivo::getYPrediction(){

	return this -> fYPrediction;
}

//_d=8

void Archivo::setNombre( string sNombreArchivo ){

	this -> sNombreArchivo = sNombreArchivo;
}

void Archivo::setSumXValues( double fSumXValues ){

	this -> fSumXValues = fSumXValues; 
}

void Archivo::setSumYValues( double fSumYValues ){

	this -> fSumYValues = fSumYValues ; 
}

void Archivo::setAvgX( double fAvgX ){

	this -> fAvgX = fAvgX; 
}

void Archivo::setAvgY( double fAvgY ){

	this -> fAvgY = fAvgY; 
}

void Archivo::setSumSquaredXValues( double fSumSquaredXValues ){

	this -> fSumSquaredXValues = fSumSquaredXValues; 
}

void Archivo::setSumSquaredYValues( double fSumSquaredYValues ){

	this -> fSumSquaredYValues = fSumSquaredYValues; 
}

void Archivo::setSumXTimesYValues( double fSumXtimesYValues ){

	this -> fSumXtimesYValues = fSumXtimesYValues; 
}

void Archivo::setTheta0( double fTheta0 ){

	this -> fTheta0 = fTheta0; 
}

void Archivo::setTheta1( double fTheta1 ){

	this -> fTheta1 = fTheta1; 
}

void Archivo::setR( double fR){

	this -> fR = fR; 
}

void Archivo::setRSquared( double fRSquared ){

	this -> fRSquared = fRSquared; 
}

void Archivo::setYPrediction( double fYPrediction ){

	this -> fYPrediction = fYPrediction; 
}


	






