// Clase que sirve para guardar los resultados de operaciones
// Hernán Iruegas Villarreal A00817021
// 14/04/2018

//_p=Simpson
//_b=51
class Simpson {

	public:

		Simpson( double dX, int iDof, int iNumSeg );
		double getX();
		int getDof();
		double getW();
		int getNumSeg();
		double getP();
		double getF();
		void setX( double dX );
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
Simpson::Simpson( double dX, int iDof, int iNumSeg ){

	this -> dX = dX;
	this -> iDof = iDof;
	this -> iNumSeg = iNumSeg;
	dW = dX / iNumSeg;
	dP = 0;
	dF = 0;
}

//_i
double Simpson::getX(){

	return this -> dX;
}

//_i
int  Simpson::getDof(){

	return this -> iDof;
}

//_i
double Simpson::getW(){

	return this -> dW;
}

//_i
int Simpson::getNumSeg(){

	return this -> iNumSeg;
}

//_i
double Simpson::getP(){

	return this -> dP;
}

//_i
double Simpson::getF(){

	return this -> dF;
}

//_i
void Simpson::setX( double dX ){
	this -> dX = dX;
}

//_i
void Simpson::setW( double dX, int iNumSeg ){

	dW = dX / iNumSeg;
}

//_i
void Simpson::setNumSeg( int iNumSeg ){

	this -> iNumSeg = iNumSeg;
}

//_i
void Simpson::setP( double dP ){

	this -> dP = dP;
}

//_i
void Simpson::setF( double dF ){

	this -> dF = dF;
}

