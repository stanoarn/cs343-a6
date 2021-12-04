#include "bottlingplant.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ):
    printer(prt), nameServer(nameServer),
    numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments)
    {
        production = new unsigned int[VendingMachine::Flavours::COUNT];
    }    // BottlingPlant::BottlingPlant

BottlingPlant::~BottlingPlant(){
    delete truck;
    printer.print(Printer::Kind::BottlingPlant, Finished);
}

void BottlingPlant::main(){
    printer.print(Printer::Kind::BottlingPlant, Start);

    truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour); // create truck;
<<<<<<< HEAD
=======

    // production run
    yield(timeBetweenShipments);    // yield between shipments, not including first production
>>>>>>> 4c624b6 (fix plant termination)

    while (!shutdown) {
        _Accept (~BottlingPlant) {
            shutdown = true;
            _Accept(getShipment);   // wait for truck to finish
            bench.signal();
            break;
        }
        or _Accept(getShipment){   // wait for truck to pickup shipment before starting next production run
            int total = 0;
            for (int i = 0; i < 4; i += 1){
                production[i] = mprng(maxShippedPerFlavour);
                total += production[i];
            }   // for
            printer.print(Printer::Kind::BottlingPlant, Generating, total);
            bench.signalBlock();
            yield(timeBetweenShipments);    // yield between shipments, not including first production

            printer.print(Printer::Kind::BottlingPlant, Pickup);
        }   // Accept
    }
}   // BottlingPlant::main

void BottlingPlant::getShipment( unsigned int cargo[] ){
    production = cargo;
    bench.wait();
    if (shutdown) {
        _Throw Shutdown();
    }   // if

    // copy production into cargo array
}   // BottlingPlant::getShipment
