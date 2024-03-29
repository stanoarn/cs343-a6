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
	enum Status {StockStatus, FundsStatus, FreeStatus, SuccStatus};
	Status status = SuccStatus;

	void main();

	public:
	enum Flavours { Cherry, Soda, Root, Lime, COUNT }; 	// flavours of soda, COUNT is the number of flavours 
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( Flavours flavour, WATCard & card );
	unsigned int * inventory();
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;

  private:
  Flavours comFlavour = Cherry;
  WATCard * watcard = nullptr;
};
