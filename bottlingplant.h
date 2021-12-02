#pragma once
#include "nameserver.h"
#include "printer.h"
#include "truck.h"
#include <uSemaphore.h>

_Task BottlingPlant {
	enum States : char {
		Start = 'S',
		Generating = 'G',
		Pickup = 'P',
		Finished = 'F'
	};
	Printer & printer;
	NameServer & nameServer;
	Truck truck;
	bool shutdown = false;
	uSemaphore truckReady = uSemaphore(0), productionReady = uSemaphore(0);
	unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour;
	unsigned int timeBetweenShipments, * truckCargo = nullptr;

	void main();
	
	public:
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};
