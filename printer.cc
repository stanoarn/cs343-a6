#include "printer.h"
#include <iostream>
#include <string>

using namespace std;

int Printer::getPosition(Printer::Kind kind, unsigned int lid = 0){
    switch(kind){
        case Printer::Kind::Parent:
            return 0;
        case Printer::Kind::Groupoff:
            return 1;
        case Printer::Kind::WATCardOffice:
            return 2;
        case Printer::Kind::NameServer:
            return 3;
        case Printer::Kind::Truck:
            return 4;
        case Printer::Kind::BottlingPlant:
            return 5;
        case Printer::Kind::Student:
            return 6 + lid;
        case Printer::Kind::Vending:
            return 6 + numStudents + lid;
        case Printer::Kind::Courier:
            return 6 + numStudents + numVendingMachines + lid;
        default:
            return -1;
    }
}   // Printer::getPosition

void Printer::update(unsigned int location, Info newString){
    if (!buffer[location].filled){
        buffer[location] = newString;
    } else {
        flush(location, newString);
    }
}   // Printer::update

void Printer::flush(unsigned int location, Info newString){
    for(unsigned int i = 0; i < 6 + numStudents + numVendingMachines + numCouriers; i++){
        if (i){
            cout << "\t";
        }

        if (buffer[i].filled){
            // cout << buffer[i];      // print if there is usefui information
            if (buffer[i].numValues == 0){
                cout << buffer[i].state;
            } else if (buffer[i].numValues == 1){
                cout << buffer[i].state << to_string(buffer[i].value1);
            } else if (buffer[i].numValues == 2){
                cout << buffer[i].state << to_string(buffer[i].value1) << "," << to_string(buffer[i].value2);
            }
            buffer[i].filled = false;     // flush old data
        }

        if (i == location){   // add new data
            buffer[i] = newString;
        }
    }
    cout << endl;
}   // Printer::flush

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ):
numStudents(numStudents),  numVendingMachines(numVendingMachines), numCouriers(numCouriers)
{
    unsigned int numColumns = 6 + numStudents + numVendingMachines + numCouriers;
    buffer = new Info[numColumns];

    // parent header
    cout << "Parent" << "\t";

    // groupoff header
    cout << "Gropoff" << "\t";

    // watcard office header
    cout << "WATOff" << "\t";

    // name server header
    cout << "Names" << "\t";

    // truck header
    cout << "Truck" << "\t";

    // bottling plant header
    cout << "Plant" << "\t";

    // students header
    for( unsigned int i = 0; i < numStudents; i++){
        // print voter ids in the header
        cout << "Stud" << i << "\t";
    }

    // vending machines header
    for( unsigned int i = 0; i < numVendingMachines; i++){
        // print voter ids in the header
        cout << "Mach" << i << "\t";
    }

    // courier header
    for( unsigned int i = 0; i < numCouriers; i++){
        // print voter ids in the header
        cout << "Cour" << i << "\t";
    }

    // print sepearator in header
    cout << endl;
    for( unsigned int i = 0; i < numColumns; i++){
        // print separators in the header
        if (i){
            cout << "\t";
        }
        cout << "*******";
    }
    cout << endl;
}   // Printer::Printer

Printer::~Printer(){
    // final flush
    Info newString;
    flush(Printer::Kind::Parent, newString);

    // print footer
    cout << "***********************" << endl;

    // delete buffer
    delete [] buffer;
}   // Printer::~Printer

void Printer::print( Printer::Kind kind, char state ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.numValues = 0;

    update(getPosition(kind), newString);
}   // Printer::print

void Printer::print( Printer::Kind kind, char state, unsigned int value1 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.numValues = 1;

    update(getPosition(kind), newString);
}   // Printer::print

void Printer::print( Printer::Kind kind, char state, unsigned int value1, unsigned int value2 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.value2 = value2;
    newString.numValues = 2;

    update(getPosition(kind), newString);
}   // Printer::print

void Printer::print( Printer::Kind kind, unsigned int lid, char state ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.numValues = 0;

    update(getPosition(kind, lid), newString);
}   // Printer::print

void Printer::print( Printer::Kind kind, unsigned int lid, char state, unsigned int value1 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.numValues = 1;

    update(getPosition(kind, lid), newString);
}   // Printer::print

void Printer::print( Printer::Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.value2 = value2;
    newString.numValues = 2;

    update(getPosition(kind, lid), newString);
}   // Printer::print
