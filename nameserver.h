_Task NameServer {
	void main();
  enum States : char {
    Start = 'S',
    Register = 'R',
    NewMachine = 'N',
    Finished = 'F'
  };
  public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine ** getMachineList();
};
