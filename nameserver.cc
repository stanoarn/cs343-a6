NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), machines(new VendingMachine*[numVendingMachines])
{}
void NameServer::main(){
    printer.print(Printer::Kind::NameServer, Start);
    for (;machineIndex < numVendingMachines; machineIndex += 1){
        _Accept (VMregister){
            machines[i] = newMachine;
            printer.print(Printer::Kind::NameServer, Register, newMachine->getId());
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
            newMachine = machines[machineIndex]
            printer.print(Printer::Kind::NameServer, NewMachine, studentId, newMachine->getId());
            machineIndex = (machineIndex + 1) % numVendingMachines;
            bench.signalBlock();
        }
        or _Accept(getMachineList) { }
    }
}

NameServer::~NameServer(){
    printer.print(Printer::Kind::NameServer, Finished);
}

void NameServer::VMregister( VendingMachine * vendingmachine ){
    newMachine = vengingmachine;
    bench.wait();
}
VendingMachine * NameServer::getMachine( unsigned int id ){
    studentId = id;
    bench.wait();
    return newMachine;
}
VendingMachine ** NameServer::getMachineList(){
    return machines;
}
