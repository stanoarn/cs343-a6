extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
printer(prt), nameServer(nameServer), machines(nameServer.getMachineList()), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour)
{}

void Truck::main(){
    try {
        for (;;) {
            yield(mprng(10) + 1);
            plant.getShipment(cargo);
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
    unsigned int * stock = machine->inventory();
    for (int i = 0; i < 4; i += 1){
        unsigned int spaceLeft = maxStockPerFlavour - stock[i];
        unsigned int availableBottles = cargo[i];
        unsigned int canFill = spaceLeft < availableBottles ? spaceLeft : availableBottles;
        stock[i] = stock[i] + canFill;
        cargo[i] = cargo[i] - canFill;
    }
    if (mprng(100) == 0){
        yield(10);
    }
}
