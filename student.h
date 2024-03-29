#pragma once
#include "vendingmachine.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "groupoff.h"
#include "MPRNG.h"

_Monitor Printer;
extern MPRNG mprng;

_Task Student {
  enum States : char {
    Start = 'S',
    SelectMachine = 'V',
    GiftCardSoda = 'G',
    FreeSodaGC = 'a',
    BoughtSoda = 'B',
    FreeSodaWC = 'A',
    WATCardLost = 'L',
    Finished = 'F'
	};
	Printer & printer;
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	Groupoff & groupoff;
	unsigned int id, maxPurchases;
	void main();

	public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
		unsigned int id, unsigned int maxPurchases );
	~Student();
};
