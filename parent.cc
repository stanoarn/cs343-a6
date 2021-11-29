#include "parent.h"
#include "printer.h"
#include "bank.h"

void Parent::main(){
    printer.print(Printer::Kind::Parent, Parent::States::Start);

    for ( ;; ){
        _Accept (~Parent){
            break;
        } _Else {
            yield(parentalDelay);   // yield before gitf

            unsigned int sid = mprng( numStudents - 1 );    // select random student
			unsigned int amount = mprng ( 1, 3 );   // select random amount of money

			bank.deposit( id, amount );					// Deposit the amount to the selected student's balance
			prt.print( Printer::Parent, Parent::States::Deposit, sid, amount );
        }
    }
}   // Parent::main

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ):
    printer(ptr), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}   // Parent::Parent

Parent::~Parent(){
    printer.print(Printer::Kind::Parent, Parent::States::Finished);
}   // Parent::~Parent
