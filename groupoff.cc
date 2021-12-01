#include "groupoff.h"
#include "printer.c"

void Groupoff::main(){
    printer.print(Printer::Kind::Groupoff, Groupoff::States::Start);

    for (unsigned int i = 0; i < numStudents; i++){ // wait for all student to acquire a giftcard
        _Accept(giftCard);
    }

    for (unsigned int i = 0; i < numStudents; ){ // periodically create real WATCards for each student
        ~Accept(~Groupoff){ // loops until destructor is called or all student have a real card
            break;
        } _Else {
            yield(groupoffDelay);   // yield before creating each card

            // create gift card to be sent
            WATCard * card = new WATCard();
            card->deposit(sodaCost);
            cards.push_back(card);

            // select random student to give card to
            unsigned int student = mprng(numStudents - i - 1);
            printer.print(Printer::Kind::Groupoff, Groupoff::States::Deposit, sodaCost);
            giftcards[student].delivery(card);

            // erase future from giftcards vector as the card has been sent out
            giftcards.erase(giftcards.begin() + student);
        }   // Accept
    }
}   // Groupoff::main

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ):
    printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay){}   // Groupoff::Groupoff

Groupoff::~Groupoff(){
    for (unsigned int i = 0; i < giftcards->size(); i++){
        delete giftcards->at(i);
    }
    for (unsigned int i = 0; i < cards->size(); i++){
        delete cards->at(i);
    }
    delete unusedWatCards;
    delete usedWatCards;
    printer.print(Printer::Kind::Groupoff, Groupoff::States::Finished);
}   // Groupoff::~Groupoff

WATCard::FWATCard Groupoff::giftCard(){
    WATCard::FWATCard giftcard = new WATCard::FWATCard();
    giftcards.push_back(giftcard);
    return giftcard;
}   // Groupoff::giftCard