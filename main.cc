#include <iostream>
#include <unistd.h>         // access: getpid
#include <string>           // access: string
#include "MPRNG.h"
#include "config.h"
#include "bank.h"
#include "bottlingplant.h"
#include "groupoff.h"
#include "nameserver.h"
#include "parent.h"
#include "printer.h"
#include "student.h"
#include "truck.h"
#include "vendingmachine.h"
#include "watcard.h"
#include "watcardoffice.h"

using namespace std;

MPRNG mprng;

int main(int argc, char * argv[]){
    // setting default values
    string configFile = "soda.config";
    int seed = getpid();
    int processors = 1;

    try {												// process command-line arguments
		switch ( argc ) {
          case 4:
            if (strcmp( argv[3], "d" ) != 0){
                processors = stoi( argv[3] );
                if ( processors <= 0 ) throw 1;
            }
          case 3:
            if (strcmp( argv[2], "d" ) != 0){
                seed = stoi( argv[2] );
                if ( seed <= 0 ) throw 1;
            }
		  case 2:
            if (strcmp( argv[1], "d" ) != 0){
                configFile = argv[1];
            }
          case 1:
            mprng.set_seed(seed);   // set mprng seed
            break;
          default: throw 1;
		} // switch
	} catch( ... ) {
		cout << "Usage: vote [voters(>0)|’d’[group(>0)|’d’[votes(>0)|’d’[seed(>0)|’d’[processors(>0)|’d’]]]]]" << endl;
		exit( 1 );
	} // try

    // process config file
    ConfigParms configParms;
    processConfigFile(configFile.c_str(), configParms);

    // set processors
    uProcessor p[processors - 1]; // number of kernel threads
    if ( processors == 1 ) uThisProcessor().setPreemption( 0 ); // turn off time - slicing for reproducibility

    // initialize printer
    Printer printer(configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers);

    // initialize production
    NameServer nameServer(printer, configParms.numVendingMachines, configParms.numStudents);
    BottlingPlant plant(printer, nameServer, configParms.numVendingMachines, configParms.maxShippedPerFlavour,
        configParms.maxStockPerFlavour, configParms.timeBetweenShipments);

    VendingMachine * machines[configParms.numVendingMachines];
    for (unsigned int i = 0; i < configParms.numVendingMachines; i++){  // create voters
        machines[i] = new VendingMachine(printer, nameServer, i, configParms.sodaCost);
    }   // for

    // initialize finances
    Bank bank(configParms.numStudents);
    Parent parent(printer, bank, configParms.numStudents, configParms.parentalDelay);
    Groupoff groupoff(printer, configParms.numStudents, configParms.sodaCost, configParms.groupoffDelay);
    WATCardOffice cardOffice(printer, bank, configParms.numCouriers);
    
    // initialize student
    Student * students[configParms.numStudents];
    for (unsigned int i = 0; i < configParms.numStudents; i++){  // create voters
        students[i] = new Student(printer, nameServer, cardOffice, groupoff, i, configParms.maxPurchases);
    }   // for

    // delete students and vending machines
    for (unsigned int i = 0; i < configParms.numStudents; i++){  // create voters
        delete students[i];
    }   // for

    for (unsigned int i = 0; i < configParms.numVendingMachines; i++){  // create voters
        delete machines[i];
    }   // for
}   // main
