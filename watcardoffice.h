#pragma once

#include "watcard.h"
#include <queue>
#include <vector>

_Monitor Printer;
_Monitor Bank;

using namespace std;

_Task WATCardOffice {
	struct Job {							// marshalled arguments and return future
		unsigned int sid;     // student id
		unsigned int amount;
		WATCard * card;
		WATCard::FWATCard result;			// return future
		Job( unsigned int sid, unsigned int amount, WATCard * card ) : sid(sid), amount(amount), card(card) {}
	};
	_Task Courier {
		enum States : char {
			Start = 'S',
			TransferStart = 't',
			WATCardLost = 'L',
			TransferComplete = 'T',
			Finished = 'F'
		};
		Printer & printer;
		Bank & bank;
		WATCardOffice & office;
		unsigned int cid;   // courier id
		void main();

		public:
		Courier(Printer & printer, Bank & bank, WATCardOffice & office, unsigned int cid);
		~Courier();
	};					// communicates with bank

	void main();
	enum States : char {
		Start = 'S',
		WorkComplete = 'W',
		CreateComplete = 'C',
		TransferComplete = 'T',
		Finished = 'F'
	};
	Printer * printer;
	Bank & bank;
	vector<Courier *> couriers;
	queue<Job *> jobs;
	unsigned int numCouriers;
	void main();

	public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
	Job * requestWork();
};
