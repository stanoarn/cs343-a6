#include "truck.h"

extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
printer(prt), nameServer(nameServer), machines(nameServer.getMachineList()), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour)
{}

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
            }
            machineIndex = currentMachineIndex;
        }
    }
    catch(Shutdown &){
        //exit the main loop
        printer.print(Printer::Kind::Truck, Finished);
    }
}

void Truck::empty(){
    bool result = true;
    for (int i = 0; i < 4; i += 1){
        result = result && cargo[i];
    }
    return result;
}

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
    }
    if (notReplenished > 0){
        printer.print(Printer::Kind::Truck, DeliveryFail, notReplenished);
    }
    else {
        printer.print(Printer::Kind::Truck, DeliveryEnd, totalShipment());
    }
    if (mprng(100) == 0){
        printer.print(Printer::Kind::Truck, WaitForRepair);
        yield(10);
    }
}

unsigned int totalShipment(){
    unsigned int result = 0;
    for (int i = 0; i < 4; i += 1) {
        result += cargo[i];
    }
    return result;
}
