// Clase que sirve para guardar los resultados de operaciones
// Hernán Iruegas Villarreal A00817021
// 18/03/2018

//_p=Respuesta
class Respuesta {

	public:

		Respuesta( double dX, int iDof, int iNumSeg );
		double getX();
		int getDof();
		double getW();
		int getNumSeg();
		double getP();
		double getF();
		void setW( double dX, int iNumSeg );
		void setNumSeg( int iNumSeg );
		void setP( double dP );
		void setF( double dF );

	private:

		double dX;
		int iDof;
		int iNumSeg;
		double dW;
		double dP;
		double dF;

};

//_i
Respuesta::Respuesta( double dX, int iDof, int iNumSeg ){

	this -> dX = dX;
	this -> iDof = iDof;
	this -> iNumSeg = iNumSeg;
	dW = dX / iNumSeg;
	dP = 0;
	dF = 0;
}

//_i
double Respuesta::getX(){

	return this -> dX;
}

//_i
int  Respuesta::getDof(){

	return this -> iDof;
}

//_i
double Respuesta::getW(){

	return this -> dW;
}

//_i
int Respuesta::getNumSeg(){

	return this -> iNumSeg;
}

//_i
double Respuesta::getP(){

	return this -> dP;
}

//_i
double Respuesta::getF(){

	return this -> dF;
}

//_i
void Respuesta::setW( double dX, int iNumSeg ){

	dW = dX / iNumSeg;
}

//_i
void Respuesta::setNumSeg( int iNumSeg ){

	this -> iNumSeg = iNumSeg;
}

//_i
void Respuesta::setP( double dP ){

	this -> dP = dP;
}

//_i
void Respuesta::setF( double dF ){

	this -> dF = dF;
}

