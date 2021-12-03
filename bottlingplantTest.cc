#include <iostream>
#include <unistd.h>         // access: getpid
#include <string>           // access: string
#include "MPRNG.h"
#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"
#include "truck.h"

using namespace std;

MPRNG mprng;

int main(int argc, char * argv[]){
     int num = 3;
    Printer printer(0, num, 0);
    NameServer nameServer(printer, num, num);
    BottlingPlant plant(printer, nameServer, num, 3, 5, 2);
    VendingMachine * machines[num];
    for (int i = 0; i < num; i++){  // create voters
        machines[i] = new VendingMachine(printer, nameServer, i, 5);
    }   // for

    // delete students and vending machines
    for (int i = 0; i < num; i++){  // create voters
        delete machines[i];
    }   // for
   // initialize concession service
}   // main
