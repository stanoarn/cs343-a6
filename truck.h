_Task Truck {
	void main();
  enum States : char {
    Starting = 'S',
    Pickup = 'P',
    DeliveryBegin = 'd',
    DeliveryFail = 'U',
    DeliveryEnd = 'D',
    WaitForRepair = 'X',
    Finished = 'F'
  };
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
