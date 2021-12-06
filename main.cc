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
		cout << "Usage: soda [config-file|’d’[seed(>0)|’d’[processors(>0)|’d’]]]" << endl;
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
    
    // initialize finances
    Bank bank(configParms.numStudents);
    Parent parent(printer, bank, configParms.numStudents, configParms.parentalDelay);
    WATCardOffice *cardOffice = new WATCardOffice(printer, bank, configParms.numCouriers);
    Groupoff groupoff(printer, configParms.numStudents, configParms.sodaCost, configParms.groupoffDelay);

    // initialize production
    NameServer nameServer(printer, configParms.numVendingMachines, configParms.numStudents);
    VendingMachine * machines[configParms.numVendingMachines];
    for (unsigned int i = 0; i < configParms.numVendingMachines; i++){  // create voters
        machines[i] = new VendingMachine(printer, nameServer, i, configParms.sodaCost);
    }   // for
    BottlingPlant * plant = new BottlingPlant(printer, nameServer, configParms.numVendingMachines, configParms.maxShippedPerFlavour,
        configParms.maxStockPerFlavour, configParms.timeBetweenShipments);

    // initialize student
    Student * students[configParms.numStudents];
    for (unsigned int i = 0; i < configParms.numStudents; i++){  // create voters
        students[i] = new Student(printer, nameServer, *cardOffice, groupoff, i, configParms.maxPurchases);
    }   // for

    // delete students
    for (unsigned int i = 0; i < configParms.numStudents; i++){  // create voters
        delete students[i];
    }   // for

    // delete plant before vending machines
    delete plant;
    delete cardOffice;
    for (unsigned int i = 0; i < configParms.numVendingMachines; i++){  // create voters
        delete machines[i];
    }   // for
}   // main
