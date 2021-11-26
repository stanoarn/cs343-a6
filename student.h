_Task Student {
	void main();
  enum States : char {
    Starting = 'S',
    SelectMachine = 'V',
    GiftCardSoda = 'G',
    FreeSoda = 'a',
    BoughtSoda = 'B',
    FreeSodaAd = 'A',
    WATCardLost = 'L',
    Finished = 'F'
  };
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};
