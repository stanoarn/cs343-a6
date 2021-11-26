#include "printer.h"
#include "nameserver.h"
#include "watcard.h"

extern MPRNG mprng;

_Task VendingMachine {
  Printer & printer;
  NameServer & nameServer;
  unsigned int id, sodaCost, stock[4] = {0,0,0,0};
	void main();
  enum States : char {
    Start = 'S',
    ReloadStart = 'r',
    ReloadDone = 'R',
    FreeSoda = 'A',
    SodaBought = 'B',
    Finished = 'F'
  };
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
