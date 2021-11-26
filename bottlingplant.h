_Task BottlingPlant {
	void main();
  enum States : char {
    Start = 'S',
    Generating = 'G',
    Pickup = 'P',
    Finished = 'F'
  };
  public:
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};
