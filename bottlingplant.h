#pragma once
#include "nameserver.h"
#include "printer.h"
#include "truck.h"

_Task BottlingPlant {
	enum States : char {
		Start = 'S',
		Generating = 'G',
		Pickup = 'P',
		Finished = 'F'
	};
	Printer & printer;
	NameServer & nameServer;
	unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments;
	bool shutdown = false;	// flag variable to know when to throu Shutdown
	unsigned int * production;
	Truck * truck;
	uCondition bench;

	void main();

	public:
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
		unsigned int timeBetweenShipments );
	~BottlingPlant();
	void getShipment( unsigned int cargo[] );
};
