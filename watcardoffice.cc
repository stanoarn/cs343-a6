#include "watcardoffice.h"
#include "printer.h"
#include "bank.h"

// _________________________ Courier Task _________________________

void WATCardOffice::Courier::main(){

}   // WATCardOffice::Courier::main

WATCardOffice::Courier::Courier(Printer & printer, Bank & bank, WATCardOffice & office, unsigned int cid):
	printer(printer), bank(bank), office(office), cid(cid){}	// WATCardOffice::Courier::Courier

WATCardOffice::Courier::~Courier(){
	printer.print(Printer::Kind::Courier, cid, WATCardOffice::Courier::States::Finished);
}	// WATCardOffice::Courier::~Courier

// _________________________ WATCardOffice Class _________________________