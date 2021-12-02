#include "watcardoffice.h"
#include "printer.h"
#include "bank.h"

// _________________________ Courier Task _________________________

void WATCardOffice::Courier::main(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Start);

	for ( ;; ){
		_Accept ( ~Courier ) {
			break;
		} _Else {
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
		}	// Accept
	}
}   // WATCardOffice::Courier::main

WATCardOffice::Courier::Courier(Printer & printer, Bank & bank, WATCardOffice & office, unsigned int cid):
	printer(printer), bank(bank), office(office), cid(cid){}	// WATCardOffice::Courier::Courier

WATCardOffice::Courier::~Courier(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Finished);
}	// WATCardOffice::Courier::~Courier

// _________________________ WATCardOffice Class _________________________

void WATCardOffice::main(){
	prt.print( Printer::Kind::WATCardOffice, WATCardOffice::Start );

	for ( ;; ){
		_Accept(~WATCardOffice){
			break;
		} or _Accept(create, transfer){
		} or _When(!jobs.empty()) _Accept (requestWork){
		}	// Accept
	}
}	// WATCardOffice::main

WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ):
	printer(ptr), bank(bank), numCouriers(numCouriers){
	// create the \ couriers
	for ( unsigned int i = 0; i < numCouriers; i++ ){
		couriers.push_back( new Courier( prt, bank, *this, i ) );
	}	// for
}	// WATCardOffice::WATCardOffice

~WATCardOffice(){
	// delete the couriers
	for ( unsigned int i = 0; i < numCouriers; i++ ){
		couriers.push_back( new Courier( prt, bank, *this, i ) );
	}	// for
	printer.print( Printer::Kind::WATCardOffice, WATCardOffice::States::Finished );
}	// WATCardOffice::~WATCardOffice

WATCard::FWATCard create( unsigned int sid, unsigned int amount ){
	WATCard * watcard = new WATCard();
	// obtain funding from bank
	Job * job = new Job(sid, amount, watcard);
	jobs.push(job);
	printer.print(Printer::Kind::WATCardOffice, WATCardOffice::States::CreateComplete, sid, amount);
	return job->result;
}	// WATCardOffice::create

WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ){
	// obtain funding from bank
	Job * job = new Job(sid, amount, card);
	jobs.push(job);
	printer.print(Printer::Kind::WATCardOffice, WATCardOffice::States::TransferComplete, sid, amount);
	return job->result;

}	// WATCardOffice::transfer

Job * requestWork(){
	if ( jobs.empty() ) return NULL;															// If null is returned that means everything is tearing down.
	Job * job = jobs.front();
	jobs.pop();

	prt.print( Printer::Kind::WATCardOffice, WATCardOffice::WorkComplete );
	return job;
}	// WATCardOffice::requestWork
