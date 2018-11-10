// Clase que sirve para calcular ecuaciones necesarias para calcular la integral usando el método de Simpson
// Hernán Iruegas Villarreal A00817021
// 18/03/2018

//_p=CalculoSimpson
//_b=33
class CalculoSimpson{

	public:
		double calculateGamma( double dAux );
		double calculateP( Simpson* pObj );
		double calculateF( int iDof, double dXAux );

};

//_i
double CalculoSimpson::calculateGamma( double dAux ){

	double dPi = 3.1415926535897;
	
	if( dAux == 0 ) return - 1;
	if( dAux == 1.0 ) return 1;

	if( dAux == 0.5 ) return sqrt( dPi );
	else return ( dAux - 1 ) * calculateGamma( dAux - 1 );

}

//_i
double CalculoSimpson::calculateP( Simpson* pObj ){

	int iMultiplicador = 0;
	double dXAux = 0, dRes = 0;

	for( int i = 0; i <= pObj -> getNumSeg(); i++ ){

		if (i == 0 || i == pObj -> getNumSeg() ) iMultiplicador = 1;
		else if( i % 2 == 0 ) iMultiplicador = 2;
		else iMultiplicador = 4;

		pObj -> setF( calculateF( pObj -> getDof(), dXAux ) );
		dRes += ( ( pObj -> getW() / 3 ) * iMultiplicador * pObj -> getF() );

		dXAux += pObj -> getW();
	}

	return dRes;
}

//_i
double CalculoSimpson::calculateF( int iDof, double dXAux ){

	double dPi = 3.1415926535897, dNum = 0, dDenIzq = 0, dDenDer = 0, dDivision = 0, dAux = 0, dExponente = 0, dAux2 = 0;

	dNum = calculateGamma( 1.0 * ( ( iDof + 1 ) * 0.5 ) ) ; // NUMERADOR 
	dDenIzq = pow( iDof * dPi, 0.5 ); // DENOMINADOR IZQUIERDA
	dDenDer = calculateGamma( 1.0 * ( iDof * 0.5 ) ); // DENOMINADOR DERECHA
	dDivision = dNum / ( dDenIzq * dDenDer );

	dAux = 1.0 + ( pow ( dXAux, 2 ) / iDof );
	dExponente = -1.0 * ( ( iDof + 1 ) * 0.5 );
	dAux2 = pow( dAux, dExponente );

	return dDivision * dAux2;

}




