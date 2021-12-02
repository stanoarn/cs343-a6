#include "bottlingplant.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ):
    printer(prt), nameServer(nameServer), truck(Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)),
    numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments)
    {}    // BottlingPlant::BottlingPlant

void BottlingPlant::main(){
    printer.print(Printer::Kind::BottlingPlant, Start);
    yield(timeBetweenShipments);//pruduction
    for (;!shutdown;) {
        _Accept (~BottlingPlant) {
            shutdown = true;
        }
        or _Accept(getShipment) {
            printer.print(Printer::Kind::BottlingPlant, Generating, 4*maxShippedPerFlavour);
            for (int i = 0; i < 4; i += 1){
                truckCargo[i] = maxShippedPerFlavour;
            }   // for
            printer.print(Printer::Kind::BottlingPlant, Pickup);
            bench.signalBlock();
            yield(timeBetweenShipments);//pruduction
        }   // Accept
    }
    printer.print(Printer::Kind::BottlingPlant, Finished);
}   // BottlingPlant::main

void BottlingPlant::getShipment( unsigned int cargo[] ){
    truckCargo = cargo;
    bench.wait();
    if (shutdown) {
        _Throw Shutdown();
    }   // if
}   // BottlingPlant::getShipment
