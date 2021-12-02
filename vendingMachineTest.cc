#include <iostream>
#include <unistd.h>         // access: getpid
#include <string>           // access: string
#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "vendingmachine.h"
#include "nameserver.h"

using namespace std;

MPRNG mprng;


int main(int argc, char * argv[]){
    // initialize concession service
    int num = 3;
    Printer printer(0, num, 0);
    NameServer nameServer(printer, num, num);
    VendingMachine * machines[num];
    for (int i = 0; i < num; i++){  // create voters
        machines[i] = new VendingMachine(printer, nameServer, i, 5);
    }   // for

    for (int i = 0; i < num; i++){  // create voters
        nameServer.VMregister(machines[i]);
        unsigned int * stock = machines[i]->inventory();
        for (int i = 0; i < 4; i++){
          stock[i] = i;
        }
        machines[i]->restocked();
        cout << machines[i]->getId() << " restocked" << endl;
    }   // for

    // delete students and vending machines
    for (int i = 0; i < num; i++){  // create voters
        delete machines[i];
    }   // for
}   // main
