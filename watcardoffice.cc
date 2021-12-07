#include "watcardoffice.h"
#include "printer.h"
#include "bank.h"

// _________________________ Courier Task _________________________

void WATCardOffice::Courier::main(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Start);

	for ( ;; ){
    WATCardOffice::Job * job = office.requestWork();
    if (job == NULL) {
        _Accept ( ~Courier ) {
          break;
      }
    }

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

void WATCardOffice::main(){
	printer.print( Printer::Kind::WATCardOffice, WATCardOffice::Start );

	for ( ;; ){
		_Accept(~WATCardOffice){
			break;
		} or _Accept(create, transfer){
		} or _When(!jobs.empty()) _Accept (requestWork){
		}	// Accept
	}
}	// WATCardOffice::main

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ):
	printer(prt), bank(bank), numCouriers(numCouriers), couriers(new Courier*[numCouriers]){
	// create the couriers
	for ( unsigned int i = 0; i < numCouriers; i++ ){
		couriers[i] = new Courier( printer, bank, *this, i );
	}	// for
}	// WATCardOffice::WATCardOffice

WATCardOffice::~WATCardOffice(){
	// delete left over jobs if any
	for (;!jobs.empty();){
		Job * job = jobs.front();
		jobs.pop();
		delete job;
	}

	for ( unsigned int i = 0; i < numCouriers; i++ ){
    	_Accept(requestWork);
	}	// for
	// delete the couriers
	for ( unsigned int i = 0; i < numCouriers; i++ ){
		delete couriers[i];
	}	// for
	delete couriers;
	
	printer.print( Printer::Kind::WATCardOffice, WATCardOffice::States::Finished );
}	// WATCardOffice::~WATCardOffice

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	WATCard * watcard = new WATCard();	// student must remember to free this memory
	// obtain funding from bank
	Job * job = new Job(sid, amount, watcard);
	jobs.push(job);
	printer.print(Printer::Kind::WATCardOffice, WATCardOffice::States::CreateComplete, sid, amount);
	return job->result;
}	// WATCardOffice::create

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ){
	// obtain funding from bank
	Job * job = new Job(sid, amount, card);
	jobs.push(job);
	printer.print(Printer::Kind::WATCardOffice, WATCardOffice::States::TransferComplete, sid, amount);
	return job->result;

}	// WATCardOffice::transfer

WATCardOffice::Job * WATCardOffice::requestWork(){
	if ( jobs.empty() ) return NULL;															// If null is returned that means everything is tearing down.
	Job * job = jobs.front();
	jobs.pop();

	printer.print( Printer::Kind::WATCardOffice, WATCardOffice::WorkComplete );
	return job;
}	// WATCardOffice::requestWork
