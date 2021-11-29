NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), machines(new VendingMachine*[numVendingMachines])
{}
void NameServer::main(){
    for (;machineIndex < numVendingMachines; machineIndex += 1){
        _Accept (VMregister){
            machines[i] = newMachine;
            bench.signalBlock();
        }//accept VMregister
    }//for
    machineIndex = 0;
    for (;;){
        _Accept(~NameServer){
            bench.signalBlock();
            break;
        }
        or _Accept(getMachine) {
            machineId = (machines[machineIndex])->getId();
            machineIndex = (machineIndex + 1) % numVendingMachines;
            bench.signalBlock();
        }
        or _Accept(getMachineList) { }
    }
}
void NameServer::VMregister( VendingMachine * vendingmachine ){
    newMachine = vengingmachine;
    bench.wait();
}
VendingMachine * NameServer::getMachine( unsigned int id ){
    bench.wait();
    return machineId;
}
VendingMachine ** NameServer::getMachineList(){
    return machines;
}
