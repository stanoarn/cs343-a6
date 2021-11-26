VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost)
{};

void VendingMachine::main(){
  for (;/*condition to terminate*/;){
    try {
      _Accept (inventory){
        _Accept (restocked);
      }//accept inventory
      or _Accept (buy);
    }
    catch( uMutexFailure::RendezvousFailure & ) {
      //we threw an exception at a student
    }//catch
  }//for
};

void buy( Flavours flavour, WATCard & card ){
  if (stock[flavour] == 0){
    _Throw Stock();
  }
  if (card.getBalance() < sodaCost){
    _Throw Funds();
  }
  stock[flavour] = stock[flavour] - 1;
  if (mprng(5 - 1) == 0){
    _Throw Free();
  }
  card.withdraw(sodaCost);
};

unsigned int * inventory(){
  return stock;
};

void restocked(){
  //do nothing
};

_Nomutex unsigned int cost() const{
  return sodaCost;
};

_Nomutex unsigned int getId() const{
  return id;
};
