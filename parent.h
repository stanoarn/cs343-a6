#pragma once

#include "MPRNG.h"

_Monitor Printer;
_Monitor Bank;
extern MPRNG mprng;

_Task Parent {
  enum States : char {
    Start = 'S',
    Deposit = 'D',
    Finished = 'F'
  };
  Printer & printer;
  Bank & bank;
  unsigned int numStudents, parentalDelay;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
  ~Parent();
};
