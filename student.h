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
    Starting = 'S',
    SelectMachine = 'V',
    GiftCardSoda = 'G',
    FreeSoda = 'a',
    BoughtSoda = 'B',
    FreeSodaAd = 'A',
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
