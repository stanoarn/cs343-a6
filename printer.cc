#include "printer.h"
#include <iostream>
#include <string>

using namespace std;

int getPosition(Kind kind){
    switch(kind){
        case Kind::Parent:
            return 0;
        case Kind::Groupoff:
            return 1;
        case Kind::WATCardOffice:
            return 2;
        case Kind::NameServer:
            return 3;
        case Kind::Truck:
            return 4;
        case Kind::BottlingPlant:
            return 5;
    }
}

int getPosition(Kind kind, unsigned int lid){
    switch(kind){
        case Kind::Student:
            return 6 + lid;
        case Kind::Vending:
            return 6 + numStudents + lid;
        case Kind::Courier:
            return 6 + numStudents + numVendingMachines + lid;
    }
}

void Printer::flush(unsigned int location, Info newString){
    for(unsigned int i = 0; i < voters; i++){
        if (i){
            cout << "\t";
        }

        if (buffer[i].filled){
            // cout << buffer[i];      // print if there is usefui information
            if (buffer[i].numValues == 0){
                cout << buffer[i].state;
            } else if (buffer[i].numValues == 1){
                cout << buffer[i].state << "," << to_string(buffer[i].value1);
            } else if (buffer[i].numValues == 2){
                cout << buffer[i].state << "," << to_string(buffer[i].value1) << "," << to_string(buffer[i].value2);
            }
            buffer[i].filled = false;     // flush old data
        }

        if (i == location){   // add new data
            buffer[i] = newString;
        }
    }
    cout << endl;
}

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ){
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
}

Printer::~Printer(){
    // final flush
    Info newString;
    flush(Kind::Parent, newString);

    // print footer
    cout << "***********************" << endl;

    // delete buffer
    delete [] buffer;
}

void Printer::print( Kind kind, char state ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.numValues = 0;

    if (!buffer[getPosition(kind)].filled){
        buffer[getPosition(kind)] = newString;
    } else {
        flush(getPosition(kind), newString);
    }
}

void Printer::print( Kind kind, char state, unsigned int value1 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.numValues = 1;

    if (!buffer[getPosition(kind)].filled){
        buffer[getPosition(kind)] = newString;
    } else {
        flush(getPosition(kind), newString);
    }
}

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.value2 = value2;
    newString.numValues = 2;

    if (!buffer[getPosition(kind)].filled){
        buffer[getPosition(kind)] = newString;
    } else {
        flush(getPosition(kind), newString);
    }
}

void Printer::print( Kind kind, unsigned int lid, char state ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.numValues = 0;

    if (!buffer[getPosition(kind, lid)].filled){
        buffer[getPosition(kind, lid)] = newString;
    } else {
        flush(getPosition(kind, lid), newString);
    }
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.numValues = 1;

    if (!buffer[getPosition(kind, lid)].filled){
        buffer[getPosition(kind, lid)] = newString;
    } else {
        flush(getPosition(kind, lid), newString);
    }
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ){
    Info newString;
    newString.filled = true;
    newString.state = state;
    newString.value1 = value1;
    newString.value2 = value2;
    newString.numValues = 2;

    if (!buffer[getPosition(kind, lid)].filled){
        buffer[getPosition(kind, lid)] = newString;
    } else {
        flush(getPosition(kind, lid), newString);
    }
}