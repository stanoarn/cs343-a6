#include "student.h"
#include "printer.h"

Student::main(){
    unsigned int numPurchases = mprng(1, maxPurchases);
    unsigned int favFlavour = (VendingMachine::Flavours) mprng(3);
    printer.print(Printer::Kind::Student, id, Student::States::Start, (int)favFlavor, numPurchases);

    // create watcard and gift card
    WATCard::FWATCard watcard = cardOffice.create(id, 5);
    WATCard::FWATCard giftcard = groupoff.giftCard();

    // obtain location of a vending machine
    VendingMachine * machine = nameServer.getMachine(id);
    printer.print(Printer::Kind::Student, id, Student::States::SelectMachine, machine.getId());

    WATCard * card; // card used to make purchase
    unsigned int purchased = 0;
    while (purchased < numPurchases){   // iterate for the number of purchases
        _Select(watcard || giftcard){   // if either card is ready to use
            try {
                if (giftcard.available()){  // use gift card first, get giftcard
                    card = watcard();
                } else if (watcard.available()){    // get watcard
                    card = giftcard;
                }   // if

                yeild(mprng(1, 10));    // yield before attept to buy

                // buy soda
                machine->buy(favFlavor, *card);
                if (giftcard.available()){ // used giftcard to buy soda
                    printer.print(Printer::Kind::Student, id, Student::States::GiftCardSoda,
                        (int) favFlavor, card->getBalance());
                    delete giftcard();  // free giftcard future
                    giftcard.reset();   // reset so giftcard can only be used once
                }  else if (watcard.available()){
                    printer.print(Printer::Kind::Student, id, Student::States::BoughtSoda,
                        (int) favFlavor, card->getBalance());
                }
                purchased++;
            } catch ( WATCardOffice::Lost event){
                printer.print(Printer::Kind::Student, id, Student::States::WATCardLost);
                watcard.reset();
                watcard = cardOffice.create(id, 5);
            } catch ( VendingMachine::Free event){
                if (giftcard.available()){
                    printer.print(Printer::Kind::Student, id, Student::States::FreeSodaGC,
                        (int) favFlavor, card->getBalance());
                } else if (watcard.available()){
                    printer.print(Printer::Kind::Student, id, Student::States::FreeSodaWC,
                        (int) favFlavor, card->getBalance());
                }   // if
                yield(4);   // watch advertisement
                purchased++;
            } catch ( VendingMachine::Funds event){ // only occurs for watcard
                watcard = cardOffice.transfer(id, machine->cost() + 5, card);   // transfer funds
            } catch ( VendingMachine::Stock event){
                machine = nameServer.getMachine(id);    // get new machine
                printer.print(Printer::Kind::Student, id, Student::States::SelectMachine, machine.getId());
            }   // try
        }   // Select
    }   // for

    // free dynamically allocated memory
    _Select (watcard){
        try {
            card = watcard();
            delete card;
        } catch (WATCardOffice::Lost){}
    }
    _Select(giftcard){
        card = giftcard;
        delete card;
    }
}   // Student::main

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ): printer(prt), nameServer(nameServer), cardOffice(cardOffice),
    groupoff(groupoff), id(id), maxPurchases(maxPurchases) {}   // Student::Student

Student::~Student(){
    printer.print(Printer::Kind::Student, id, Student::States::Finished);
}   // Student::~Student