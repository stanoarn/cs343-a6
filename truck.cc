#include "truck.h"
#include "MPRNG.h"
#include "printer.h"
#include "bottlingplant.h"
#include "nameserver.h"

extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
    printer(prt), nameServer(nameServer),
    plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour)
    {}  // Truck::Truck

void Truck::main(){
    try {
        machines = nameServer.getMachineList();
        printer.print(Printer::Kind::Truck, Start);
        for (;;) {
            yield(mprng(10) + 1);
            plant.getShipment(cargo);
            printer.print(Printer::Kind::Truck, Pickup, totalShipment());
            unsigned int currentMachineIndex = machineIndex;
            for (; !empty() ; ){
                VendingMachine * machine = machines[currentMachineIndex];
                restock(machine);
                currentMachineIndex = (currentMachineIndex + 1) % numVendingMachines;
                if (currentMachineIndex == machineIndex) break;
            }   // for
            machineIndex = currentMachineIndex;
        }   // for
    } catch(BottlingPlant::Shutdown &){
        //exit the main loop
        printer.print(Printer::Kind::Truck, Finished);
    }   // try
}   // Truck::main

bool Truck::empty(){
    bool notEmpty = false;
    for (int i = 0; i < 4; i += 1){
        notEmpty = notEmpty || cargo[i];
    }   // for
    return !notEmpty;
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

unsigned int Truck::totalShipment(){
    unsigned int result = 0;
    for (int i = 0; i < 4; i += 1) {
        result += cargo[i];
    }   // for
    return result;
}   // Truck::totalShipment
