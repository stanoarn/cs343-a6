#include "watcard.h"

WATCard::WATCard(): balance(0){}   // WATCard::WATCard

void WATCard::deposit( unsigned int amount ){
    balance += amount;
}   // WATCard::deposit

void WATCard::withdraw( unsigned int amount ){
    balance -= amount;
}   // WATCard::withdraw

unsigned int WATCard::getBalance(){
    return balance;
}   // WATCard::getBalance