// Clase Calculo que realiza todas las operaciones para realizar la regresión lineal
// Hernán Iruegas Villarreal A00817021
// 14/04/2018

//_p=Calculo
//_b=70
class Calculo {

	public:
		//_d=7
		double calculateTheta0( double fAvgY, double fTheta1, double fAvgX );
		double calculateTheta1( double fSumXtimesYValues, double fSumSquaredXValues, double fAvgY, double fAvgX, int iNumberOfPairs );
		double calculateR( int iNumberOfPairs, double fSumXtimesYValues, double fSumXValues, double fSumYValues, double fSumSquaredXValues, double fSumSquaredYValues );
		double calculateRSquared( double fR );
		double calculateYPrediction( double fTheta0, double fTheta1, int iValueForRegression );

};


//_d=33

//_i
double Calculo::calculateTheta0( double fAvgY, double fTheta1, double fAvgX ){

	double fTheta0;

	fTheta0 = fAvgY - ( fTheta1 * fAvgX );

	return fTheta0;
}

//_i
double Calculo::calculateTheta1( double fSumXtimesYValues, double fSumSquaredXValues, double fAvgY, double fAvgX, int iNumberOfPairs ){

	double fTheta1;

	fTheta1 = ( fSumXtimesYValues - ( iNumberOfPairs * fAvgX * fAvgY ) ) / ( fSumSquaredXValues - ( iNumberOfPairs * fAvgX * fAvgX ) );

	return fTheta1;
}

//_i
double Calculo::calculateR( int iNumberOfPairs, double fSumXtimesYValues, double fSumXValues, double fSumYValues, double fSumSquaredXValues, double fSumSquaredYValues ){

	double fR;
	double nominator = iNumberOfPairs * fSumXtimesYValues - ( fSumXValues * fSumYValues ); 
	double denominatorPart1 = iNumberOfPairs * fSumSquaredXValues - ( fSumXValues * fSumXValues );
	double denominatorPart2 = iNumberOfPairs * fSumSquaredYValues - ( fSumYValues * fSumYValues );

	fR = nominator / sqrt( denominatorPart1 * denominatorPart2 );

	return fR;
}

//_i
double Calculo::calculateRSquared( double fR ){

	double fRSquared;

	fRSquared = fR * fR;

	return fRSquared;

}

//_i
double Calculo::calculateYPrediction( double fTheta0, double fTheta1, int iValueForRegression ){

	double fYPrediction;

	fYPrediction = 	fTheta0 + ( fTheta1 * iValueForRegression );

	return fYPrediction;
}









