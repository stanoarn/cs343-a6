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
	Printer & printer;
  NameServer & nameServer;
  vendingMachine ** machines;
  BottlingPlant & plant;
  unsigned int numVendingMachines, maxStockPerFlavour, cargo[4] = {0,0,0,0}, machineIndex = 0;
  bool empty();
  unsigned int totalShipment();
  void restock(VendingMachine * machine);
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
};
