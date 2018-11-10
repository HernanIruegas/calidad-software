// Clase Parte que guarda todas las caracteristicas de una parte, lineas agregadas, modificadas, etc.
// Hernán Iruegas Villarreal A00817021
// 18/02/2018

//_p=Parte
class Parte {
	//_i
	public:

		Parte();
		Parte(string nombreParte, int totalLDC, int base, int deleted, int modified, int added, int items);
		string getNombreParte();
		int getTotalLDC();
		int getBase();
		int getDeleted();
		int getModified();
		int getAdded();
		int getItems();
		void setNombreParte( string nombreParte );
		void setTotalLDC( int totalLDC );
		void setBase( int base );
		void setDeleted( int deleted );
		void setModified( int modified );
		void setAdded( int added );
		void setItems( int items );
	//_i
	private:

		string nombreParte;
		int totalLDC, base, deleted, modified, added, items;

};

Parte::Parte(){

	this -> nombreParte = "default";
	this -> totalLDC = 0;
	this -> base = 0;
	this -> deleted = 0;
	this -> modified = 0;
	this -> added = 0;
	this -> items = 0;
}

Parte::Parte( string nombreParte, int totalLDC, int base, int deleted, int modified, int added, int items ) {
	
	this -> nombreParte = nombreParte;
	this -> totalLDC = totalLDC;
	this -> base = base;
	this -> deleted = deleted;
	this -> modified = modified;
	this -> added = added;
	this -> items = items;
}

string Parte::getNombreParte(){

	return this -> nombreParte;
}

int Parte::getTotalLDC(){

	return this -> totalLDC;
}

int Parte::getBase(){

	return this -> base;
}

int Parte::getDeleted(){

	return this -> deleted;
}

int Parte::getModified(){

	return this -> modified;
}

int Parte::getAdded(){

	return this -> added;
}

int Parte::getItems(){

	return this -> items;
}

void Parte::setNombreParte( string nombreParte ){

	this -> nombreParte = nombreParte;
}

void Parte::setTotalLDC( int totalLDC ){

	this -> totalLDC =  this -> totalLDC + totalLDC;
}

void Parte::setBase( int base ){

	this -> base = this -> base + base;
}

void Parte::setDeleted( int deleted ){

	this -> deleted =  this -> deleted + deleted;
}

void Parte::setModified( int modified ){

	this -> modified =  this -> modified + modified;
}

void Parte::setAdded( int added ){

	this -> added =  this -> added + added;
}

void Parte::setItems( int items ){

	this -> items =  this -> items + items;
}
























