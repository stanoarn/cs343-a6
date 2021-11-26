_Task WATCardOffice {
	struct Job {							// marshalled arguments and return future
		Args args;							// call arguments (YOU DEFINE "Args")
		WATCard::FWATCard result;			// return future
		Job( Args args ) : args( args ) {}
	};
	_Task Courier {
    enum States : char {
      Start = 'S',
      TransferStart = 't',
      WATCardLost = 'L',
      TransferComplete = 'T',
      Finished = 'F'
    };
  };					// communicates with bank

	void main();
  enum States : char {
    Start = 'S',
    WorkComplete = 'W',
    CreateComplete = 'C',
    TransferComplete = 'T',
    Finished = 'F'
  };

  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
	Job * requestWork();
};
