#pragma once

#include "MPRNG.h"
#include "watcard.h"
#include <vector>

using namespace std;

_Monitor Printer;
extern MPRNG mprng;

_Task Groupoff {
	enum States : char {
		Start = 'S',
		Deposit = 'D',
		Finished = 'F'
	};
	Printer & printer;
	unsigned int numStudents, sodaCost, groupoffDelay;
	vector<WATCard::FWATCard *> giftcards;	// list of future giftcards
	vector<WATCard *> cards;	// list of cards assigned real WATCards
	void main();

	public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};
