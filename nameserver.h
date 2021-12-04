#pragma once
#include "vendingmachine.h"

_Monitor Printer;

_Task NameServer {
	void main();
	enum States : char {
		Start = 'S',
		Register = 'R',
		NewMachine = 'N',
		Finished = 'F'
	};
	Printer & printer;
	unsigned int numVendingMachines, numStudents, studentId = 0;//communication variable for getMachine
	VendingMachine ** machines;
	unsigned int machineIndex = 0;
	VendingMachine * newMachine;//communication variable for getMachineList
	uCondition bench;
	public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
  ~NameServer();
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine ** getMachineList();
};
