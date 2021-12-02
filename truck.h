#pragma once

_Task BottlingPlant;

_Task Truck {
	enum States : char {
		Starting = 'S',
		Pickup = 'P',
		DeliveryBegin = 'd',
		DeliveryFail = 'U',
		DeliveryEnd = 'D',
		WaitForRepair = 'X',
		Finished = 'F'
	};
	Printer & printer;
	NameServer & nameServer;
	VendingMachine ** machines;
	BottlingPlant & plant;
	unsigned int numVendingMachines, maxStockPerFlavour, cargo[4] = {0,0,0,0}, machineIndex = 0;
	
	void main();
	bool empty();
	unsigned int totalShipment();
	void restock(VendingMachine * machine);
	public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, 
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
