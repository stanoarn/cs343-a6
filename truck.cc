#include "truck.h"

extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, 
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
    printer(prt), nameServer(nameServer), machines(nameServer.getMachineList()), 
    plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour)
    {}  // Truck::Truck

void Truck::main(){
    try {
        printer.print(Printer::Kind::Truck, Start);
        for (;;) {
            yield(mprng(10) + 1);
            plant.getShipment(cargo);
            printer.print(Printer::Kind::Truck, Pickup, totalShipment());
            unsigned int currentMachineIndex = machineIndex;
            for (; !empty ; ){
                VendingMachine * machine = machines[currentMachineIndex];
                restock(machine);
                currentMachineIndex = (currentMachineIndex + 1) % numVendingMachines;
                if (currentMachineIndex == machineIndex) break;
            }   // for
            machineIndex = currentMachineIndex;
        }   // for
    } catch(Shutdown &){
        //exit the main loop
        printer.print(Printer::Kind::Truck, Finished);
    }   // try
}   // Truck::main

void Truck::empty(){
    bool result = true;
    for (int i = 0; i < 4; i += 1){
        result = result && cargo[i];
    }   // for
    return result;
}   // Truck::empty

void Truck::restock(VendingMachine * machine){
    printer.print(Printer::Kind::Truck, DeliveryBegin, totalShipment());
    unsigned int * stock = machine->inventory();
    unsigned int notReplenished = 0;
    for (int i = 0; i < 4; i += 1){
        unsigned int spaceLeft = maxStockPerFlavour - stock[i];
        unsigned int availableBottles = cargo[i];
        unsigned int canFill = spaceLeft < availableBottles ? spaceLeft : availableBottles;
        notReplenished += spaceLeft - canFill;
        stock[i] = stock[i] + canFill;
        cargo[i] = cargo[i] - canFill;
    }   // for
    if (notReplenished > 0){
        printer.print(Printer::Kind::Truck, DeliveryFail, notReplenished);
    } else {
        printer.print(Printer::Kind::Truck, DeliveryEnd, totalShipment());
    }  // if
    if (mprng(100) == 0){
        printer.print(Printer::Kind::Truck, WaitForRepair);
        yield(10);
    }   // if
}   // Truck::restock

unsigned int totalShipment(){
    unsigned int result = 0;
    for (int i = 0; i < 4; i += 1) {
        result += cargo[i];
    }   // for
    return result;
}   // Truck::totalShipment
