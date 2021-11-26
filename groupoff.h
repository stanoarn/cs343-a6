_Task Groupoff {
	void main();
  enum States : char {
    Start = 'S',
    Deposit = 'D',
    Finished = 'F'
  };
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();
};
