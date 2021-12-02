#pragma once
#include "MPRNG.h"
#include "watcard.h"

_Monitor Printer;
_Task NameServer;

extern MPRNG mprng;

_Task VendingMachine {
	Printer & printer;
	NameServer & nameServer;
	unsigned int id, sodaCost, stock[4] = {0,0,0,0};
	uCondition bench;
	enum States : char {
		Start = 'S',
		ReloadStart = 'r',
		ReloadDone = 'R',
		FreeSoda = 'A',
		SodaBought = 'B',
		Finished = 'F'
	};
	enum Status {Stock, Funds, Free, Succ};
	Status status = Succ;

	void main();
	
	public:
	enum Flavours { Cherry = 0, Soda = 1, Root = 2, Lime = 3 }; 				// flavours of soda (YOU DEFINE)
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( Flavours flavour, WATCard & card );
	unsigned int * inventory();
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;
};
