#include "bottlingplant.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ):
    printer(prt), nameServer(nameServer), truck(Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)),
    numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments){}
void BottlingPlant::main(){
    printer.print(Printer::Kind::BottlingPlant, Start);
    for (;!shutdown;) {
        _Accept (~BottlingPlant) {
            shutdown = true;
        }
        _Else {
            yield(timeBetweenShipments);//pruduction
            printer.print(Printer::Kind::BottlingPlant, Generating, 4*maxShippedPerFlavour);
            productionReady.V();
            truckReady.P();
            for (int i = 0; i < 4; i += 1){
                truckCargo[i] = maxShippedPerFlavour;
            }
            printer.print(Printer::Kind::BottlingPlant, Pickup);
            productionReady.V();
        }
    }
    printer.print(Printer::Kind::BottlingPlant, Finished);
}
void BottlingPlant::getShipment( unsigned int cargo[] ){
    productionReady.P();
    truckCargo = cargo;
    truckReady.V();
    productionReady.P();
    if (shutdown) {
        _Throw Shutdown();
    }
}
