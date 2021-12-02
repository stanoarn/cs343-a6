#include "bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ): numStudents(numStudents){
    balances = new unsigned int[numStudents];
    for (unsigned int i = 0; i < numStudents; ++i) {    // initialize student accounts with $0
        balances[i] = 0;
    }
}   // Bank::Bank

Bank::~Bank(){
    delete balances;
}   // Bank::~Bank

void Bank::deposit( unsigned int id, unsigned int amount ){
    balances[id] += amount;
}   // Bank::deposit

void Bank::withdraw( unsigned int id, unsigned int amount ){
    for ( ;; ){ // makes sure student has enough money for current transaction
        if (balances[id] < amount){
            _Accept(deposit);
        } else {
            break;
        }   // if
    }   // for
    balances[id] -= amount;
}   // Bank::withdraw
