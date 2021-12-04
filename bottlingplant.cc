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
    delete production;
    printer.print(Printer::Kind::BottlingPlant, Finished);
}

void BottlingPlant::main(){
    printer.print(Printer::Kind::BottlingPlant, Start);

    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour); // create truck;

    while (!shutdown) {
        _Accept (~BottlingPlant) {
            shutdown = true;
            _Accept(getShipment);   // wait for truck to finish
            break;
        } _Else {
            // production run
            int total = 0;
            for (int i = 0; i < 4; i += 1){
                production[i] = mprng(maxShippedPerFlavour);
                total += production[i];
            }   // for
            printer.print(Printer::Kind::BottlingPlant, Generating, total);
            yield(timeBetweenShipments);    // yield between shipments, not including first production

            _Accept(getShipment);   // wait for truck to pickup shipment before starting next production run
            printer.print(Printer::Kind::BottlingPlant, Pickup);
        }   // Accept
    }
}   // BottlingPlant::main

void BottlingPlant::getShipment( unsigned int cargo[] ){
    if (shutdown) {
        _Throw Shutdown();
    }   // if

    // copy production into cargo array
    for (unsigned int i = 0; i < VendingMachine::Flavours::COUNT; i++){
        cargo[i] = production[i];
    }
}   // BottlingPlant::getShipment
