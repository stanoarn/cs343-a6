BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ):
printer(prt), nameServer(nameServer), truck(Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments)
{}
BottlingPlant::void main(){
    for (;/*termination condition*/;) {
        yield(timeBetweenShipments);//pruduction
        productionReady.V();
        truckReady.P();
        for (int i = 0; i < 4; i += 1){
            truckCargo[i] = maxShippedPerFlavour;
        }
        //if shutting down {
        //  shutdown = true;
        //}
        productionReady.V();
    }
}
BottlingPlant::void getShipment( unsigned int cargo[] ){
    productionReady.P();
    truckCargo = cargo;
    truckReady.V();
    productionReady.P();
    if (shutdown) {
        _Throw Shutdown();
    }
}
