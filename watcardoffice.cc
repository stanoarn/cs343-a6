#include "watcardoffice.h"
#include "printer.h"
#include "bank.h"

// _________________________ Courier Task _________________________

void WATCardOffice::Courier::main(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Start);

	for ( ;; ){
		WATCardOffice::Job * job = office.requestWork();
		if (job == NULL) break;		// no jobs available

		// get money from bank
		printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::TransferStart, 
			job->sid, job->amount);
		bank.withdraw(job->sid, job->amount);

		// update WATCard
			printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::TransferComplete, 
				job->sid, job->amount);
		job->watcard->deposit(job->amount);

		if (mprng(5) == 0){	// 1/6 change that watcard is lost
			printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::WATCardLost, job->sid);
			job->result.exception(new WATCardOffice::Lost());
			delete job->watcard;
		} else {	// card is not lost
			job->result.delivery(job->watcard);
		}	// if

		delete job;	// deallocate job from heap
	}
}   // WATCardOffice::Courier::main

WATCardOffice::Courier::Courier(Printer & printer, Bank & bank, WATCardOffice & office, unsigned int cid):
	printer(printer), bank(bank), office(office), cid(cid){}	// WATCardOffice::Courier::Courier

WATCardOffice::Courier::~Courier(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Finished);
}	// WATCardOffice::Courier::~Courier

// _________________________ WATCardOffice Class _________________________