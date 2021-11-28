VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost)
{};

void VendingMachine::main(){
  for (;/*condition to terminate*/;){
    try {
      _Accept (inventory){
        _Accept (restocked);
      }//accept inventory
      or _Accept (buy){
        if (stock[flavour] == 0){
          status = Stock;
        }
        else if (card.getBalance() < sodaCost){
          status = Funds;
        }
        stock[flavour] = stock[flavour] - 1;
        else if (mprng(5 - 1) == 0){
          status = Free;
        }
        else {
          card.withdraw(sodaCost);
          status = Succ;
        }
        bench.signalBlock();
      }//accept buy
    }
    catch( uMutexFailure::RendezvousFailure & ) {
      //we threw an exception at a student
    }//catch
  }//for
};

void buy( Flavours flavour, WATCard & card ){
  bench.wait();
  switch (status){
    case Stock:
      _Throw Stock();
      break;
    case Funds:
      _Throw Funds();
      break;
    case Free:
      _Throw Free();
      break;
  }//switch
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
