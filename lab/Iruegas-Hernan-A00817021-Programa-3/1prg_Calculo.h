// Clase Calculo que realiza todas las operaciones para realizar la regresión lineal
// Hernán Iruegas Villarreal A00817021
// 04/03/2018

//_p=Calculo
class Calculo {

	//_i
	public:

		double calculateSumXValues( vector<double> vAllXValues );
		double calculateSumYValues( vector<double> vAllYValues );
		double calculateAvgX( double fSumXValues, int iNumberOfPairs );
		double calculateAvgY( double fSumYValues, int iNumberOfPairs );
		double calculateSumSquaredXValues( vector<double> vAllXValues );
		double calculateSumSquaredYValues( vector<double> vAllYValues );
		double calculateSumXTimesYValues( vector<double> vAllXValues, vector<double> vAllYValues );
		double calculateTheta0( double fAvgY, double fTheta1, double fAvgX );
		double calculateTheta1( double fSumXtimesYValues, double fSumSquaredXValues, double fAvgY, double fAvgX, int iNumberOfPairs );
		double calculateR( int iNumberOfPairs, double fSumXtimesYValues, double fSumXValues, double fSumYValues, double fSumSquaredXValues, double fSumSquaredYValues );
		double calculateRSquared( double fR );
		double calculateYPrediction( double fTheta0, double fTheta1, int iValueForRegression );

};


double Calculo::calculateSumXValues( vector<double> vAllXValues ){

	double fSumXValues;

	for( int i = 0; i < vAllXValues.size(); i++ )
		fSumXValues += vAllXValues[i];
	
	return fSumXValues;
}

double Calculo::calculateSumYValues( vector<double> vAllYValues ){

	double fSumYValues;

	for( int i = 0; i < vAllYValues.size(); i++ )
		fSumYValues += vAllYValues[i];

	return fSumYValues;
}

double Calculo::calculateAvgX( double fSumXValues, int iNumberOfPairs ){

	double fAvgXAux;

	fAvgXAux = fSumXValues / iNumberOfPairs;

	return fAvgXAux;
}

double Calculo::calculateAvgY( double fSumYValues, int iNumberOfPairs ){

	double fAvgYAux;

	fAvgYAux = fSumYValues / iNumberOfPairs; 

	return fAvgYAux;
}

double Calculo::calculateSumSquaredXValues( vector<double> vAllXValues ){

	double fSumSquaredXValues;

	for( int i = 0; i < vAllXValues.size(); i++ )
		fSumSquaredXValues += ( vAllXValues[i] * vAllXValues[i] );

	return fSumSquaredXValues;
}

double Calculo::calculateSumSquaredYValues( vector<double> vAllYValues ){

	double fSumSquaredYValues;

	for( int i = 0; i < vAllYValues.size(); i++ )
		fSumSquaredYValues += ( vAllYValues[i] * vAllYValues[i] );

	return fSumSquaredYValues;
}

double Calculo::calculateSumXTimesYValues( vector<double> vAllXValues, vector<double> vAllYValues ){

	double fSumXtimesYValues;

	for( int i = 0; i < vAllYValues.size(); i++ )
		fSumXtimesYValues += ( vAllXValues[i] * vAllYValues[i] );

	return fSumXtimesYValues;
}

double Calculo::calculateTheta0( double fAvgY, double fTheta1, double fAvgX ){

	double fTheta0;

	fTheta0 = fAvgY - ( fTheta1 * fAvgX );

	return fTheta0;
}

double Calculo::calculateTheta1( double fSumXtimesYValues, double fSumSquaredXValues, double fAvgY, double fAvgX, int iNumberOfPairs ){

	double fTheta1;

	fTheta1 = ( fSumXtimesYValues - ( iNumberOfPairs * fAvgX * fAvgY ) ) / ( fSumSquaredXValues - ( iNumberOfPairs * fAvgX * fAvgX ) );

	return fTheta1;
}

double Calculo::calculateR( int iNumberOfPairs, double fSumXtimesYValues, double fSumXValues, double fSumYValues, double fSumSquaredXValues, double fSumSquaredYValues ){

	double fR;
	double nominator = iNumberOfPairs * fSumXtimesYValues - ( fSumXValues * fSumYValues ); 
	double denominatorPart1 = iNumberOfPairs * fSumSquaredXValues - ( fSumXValues * fSumXValues );
	double denominatorPart2 = iNumberOfPairs * fSumSquaredYValues - ( fSumYValues * fSumYValues );

	fR = nominator / sqrt( denominatorPart1 * denominatorPart2 );

	return fR;
}

double Calculo::calculateRSquared( double fR ){

	double fRSquared;

	fRSquared = fR * fR;

	return fRSquared;

}

double Calculo::calculateYPrediction( double fTheta0, double fTheta1, int iValueForRegression ){

	double fYPrediction;

	fYPrediction = 	fTheta0 + ( fTheta1 * iValueForRegression );

	return fYPrediction;
}









