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
    {
        cargo = new unsigned int[VendingMachine::Flavours::COUNT];
        for (unsigned int i = 0; i < VendingMachine::Flavours::COUNT; i++){
            cargo[i] = 0;
        }  
    }  // Truck::Truck

Truck::~Truck(){
    delete cargo;
    printer.print(Printer::Kind::Truck, Finished);
}

void Truck::main(){
    printer.print(Printer::Kind::Truck, Start);
    machines = nameServer.getMachineList(); // get list of vending machines

    for (;;) {
        yield(mprng(1, 10));   // yield to get coffee from Tim Hortons

        // obtain new shipment
        try {
            plant.getShipment(cargo);
            printer.print(Printer::Kind::Truck, Pickup, totalShipment());
        } catch (BottlingPlant::Shutdown &){
            //exit the main loop
            break;
        }   // 

        unsigned int currentMachineIndex = machineIndex;
        while (!empty()){
            VendingMachine * machine = machines[currentMachineIndex];
            restock(machine);
            currentMachineIndex = (currentMachineIndex + 1) % numVendingMachines;
            if (currentMachineIndex == machineIndex) break; // check if delivered to all machines
        }   // for
        machineIndex = currentMachineIndex;
    }   // fortry
}   // Truck::main

bool Truck::empty(){
    bool notEmpty = false;
    for (int i = 0; i < 4; i += 1){
        notEmpty = notEmpty || cargo[i];
    }   // for
    return !notEmpty;
}   // Truck::empty

void Truck::restock(VendingMachine * machine){
    printer.print(Printer::Kind::Truck, DeliveryBegin, machine->getId(), totalShipment());
    unsigned int * stock = machine->inventory();
    unsigned int notReplenished = 0;
    for (int i = 0; i < VendingMachine::Flavours::COUNT; i++){
        unsigned int spaceLeft = maxStockPerFlavour - stock[i];
        unsigned int availableBottles = cargo[i];
        unsigned int canFill = spaceLeft < availableBottles ? spaceLeft : availableBottles;
        notReplenished += spaceLeft - canFill;
        stock[i] = stock[i] + canFill;
        cargo[i] = cargo[i] - canFill;
    }   // for

    if (notReplenished > 0){    // uncessfully filled vending machine
        printer.print(Printer::Kind::Truck, DeliveryFail, machine->getId(), notReplenished);
    }  // if

    printer.print(Printer::Kind::Truck, DeliveryEnd, machine->getId(), totalShipment());  // finised delivery

    if (mprng(100) == 0){   // change of flat tire
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
