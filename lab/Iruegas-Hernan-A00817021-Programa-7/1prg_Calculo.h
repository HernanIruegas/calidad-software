// Clase Calculo que realiza la reducción por gauss
// Hernán Iruegas Villarreal A00817021
// 22/04/2018

//_p=Calculo
class Calculo {

	public:
		vector< double > calGauss( vector< vector< double > > matGauss );

};

//_i
vector< double > Calculo::calGauss( vector< vector< double > > matGauss ){

	int aux = 4;
	double dAux2 = 0;
	vector< double > vAux;

	for ( int i = 0; i < aux; i++ ){

	    for ( int j = 0; j < aux; j++ ){

	    	if ( j != i ){
	    	
		    	dAux2 = matGauss[ j ][ i ] / matGauss[ i ][ i ];

		        for ( int k = 0; k < aux + 1; k++ ){
		        	matGauss[ j ][ k ] = matGauss[ j ][ k ] - dAux2 * matGauss[ i ][ k ];
		        }
	    	}
	    }
	}

	for ( int i = 0; i < aux; i++ ){
		vAux.push_back( matGauss[ i ][ aux ] / matGauss[ i ][ i ] );
	}

  return vAux;
}









