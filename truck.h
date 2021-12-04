#pragma once

_Task BottlingPlant;
_Task NameServer;
_Task VendingMachine;
_Monitor Printer;

_Task Truck {
	enum States : char {
		Start = 'S',
		Pickup = 'P',
		DeliveryBegin = 'd',
		DeliveryFail = 'U',
		DeliveryEnd = 'D',
		WaitForRepair = 'X',
		Finished = 'F'
	};
	Printer & printer;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines, maxStockPerFlavour;
	unsigned * cargo, machineIndex = 0;
	VendingMachine ** machines;

	void main();
	bool empty();
	unsigned int totalShipment();
	void restock(VendingMachine * machine);

	public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};
