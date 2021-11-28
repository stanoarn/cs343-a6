#pragma once

// _Monitor / _Cormonitor Printer {
_Monitor Printer {
	unsigned int numStudents, numVendingMachines, numCouriers;
	struct Info{
		bool filled  = false;
		char state;
		unsigned int value1;
		unsigned int value2;
		unsigned int numValues;
	}
	Info* buffer;

	// get column in buffer information should be depending on its kind
	int getPosition(Kind kind);
	int getPosition(Kind kind, unsigned int lid);

	void flush(unsigned int location, Info newString);
  public:
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	~Printer();
	void print( Kind kind, char state );
	void print( Kind kind, char state, unsigned int value1 );
	void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );
};
