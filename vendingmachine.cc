#include "vendingmachine.h"
#include "printer.h"
#include "nameserver.h"
#include "watcard.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
	printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost)
	{
		nameServer.VMregister(this);
	}  // VendingMachine::VendingMachine

void VendingMachine::main(){
	printer.print(Printer::Kind::Vending, getId(), Start, sodaCost);
	for (;/*condition to terminate*/;){
		try {
			_Accept(~VendingMachine){
				printer.print(Printer::Kind::Vending, getId(), Finished);
				break;
			} or _Accept (inventory){ //accept inventory
				printer.print(Printer::Kind::Vending, getId(), ReloadStart);
				_Accept (restocked){
					printer.print(Printer::Kind::Vending, getId(), ReloadDone);
				} // Accept
			} or _Accept (buy){
				if (stock[comFlavour] == 0){
				  	status = StockStatus;
				} else if (watcard->getBalance() < sodaCost){
          			status = FundsStatus;
				} else {
          			stock[comFlavour] = stock[comFlavour] - 1;
					if (mprng(5 - 1) == 0){
						printer.print(Printer::Kind::Vending, getId(), FreeSoda);
						status = FreeStatus;
					} else {
						watcard->withdraw(sodaCost);
						printer.print(Printer::Kind::Vending, getId(), SodaBought, comFlavour, stock[comFlavour]);
						status = SuccStatus;
					} 	// if
				} 	// if
				bench.signalBlock();
			} 	// Accept
		} catch( uMutexFailure::RendezvousFailure & ) {
			//we threw an exception at a student
		}	 // try
	}	 //for
}	// VendingMachine::main

void VendingMachine::buy( Flavours flavour, WATCard & card ){
  	watcard = &card;
  	comFlavour = flavour;
	bench.wait();
	switch (status){
		case StockStatus:
		_Throw Stock();
		break;
		case FundsStatus:
		_Throw Funds();
		break;
		case FreeStatus:
		_Throw Free();
		break;
		case SuccStatus:
		break;
	}	//switch
}	// VendingMachine::buy

unsigned int * VendingMachine::inventory(){
	return stock;
}	// VendingMachine::inventory

void VendingMachine::restocked(){
	//do nothing
}	// VendingMachine::restocked

_Nomutex unsigned int VendingMachine::cost() const{
	return sodaCost;
}	// VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() const{
	return id;
}	// VendingMachine::getId()
