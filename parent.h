_Task Parent {
	void main();
  enum States : char {
    Start = 'S',
    Deposit = 'D',
    Finished = 'F'
  };
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};
