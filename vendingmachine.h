_Task VendingMachine {
	void main();
  enum States : char {
    Start = 'S',
    ReloadStart = 'r',
    ReloadDone = 'R',
    FreeSoda = 'A',
    SodaBought = 'B',
    Finished = 'F'
  };
  public:
	enum Flavours { ... }; 				// flavours of soda (YOU DEFINE)
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( Flavours flavour, WATCard & card );
	unsigned int * inventory();
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;
};
