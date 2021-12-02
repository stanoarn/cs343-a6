#pragma once
#include "nameserver.h"
#include "printer.h"
#include "truck.h"
_Task BottlingPlant {
	void main();
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
  unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments, * truckCargo = nullptr;
  public:
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};
