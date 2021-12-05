#pragma once

#include "watcard.h"
#include <queue>
#include <vector>
#include "MPRNG.h"

_Monitor Printer;
_Monitor Bank;
extern MPRNG mprng;

using namespace std;

_Task WATCardOffice {
	struct Job {							// marshalled arguments and return future
		unsigned int sid;     // student id
		unsigned int amount;
		WATCard * watcard;
		WATCard::FWATCard result;			// return future
		Job( unsigned int sid, unsigned int amount, WATCard * card ) : sid(sid), amount(amount), watcard(card) {}
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

	enum States : char {
		Start = 'S',
		WorkComplete = 'W',
		CreateComplete = 'C',
		TransferComplete = 'T',
		Finished = 'F'
	};
	Printer & printer;
	Bank & bank;
	unsigned int numCouriers;
	Courier ** couriers;
	queue<Job *> jobs;
	
	void main();

	public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
	Job * requestWork();
};
