VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost)
{};

void VendingMachine::main(){
  printer.print(Printer::Kind::Vending, Start);
  for (;/*condition to terminate*/;){
    try {
      //accept destor
            //printer.print(Printer::Kind::Vending, Finished);
      _Accept (inventory){
        printer.print(Printer::Kind::Vending, ReloadStart);
        _Accept (restocked){
            printer.print(Printer::Kind::Vending, ReloadDone);
        }
      }//accept inventory
      or _Accept (buy){
        if (stock[flavour] == 0){
          status = Stock;
        }
        else if (card.getBalance() < sodaCost){
          status = Funds;
        }
        else {
          stock[flavour] = stock[flavour] - 1;
          if (mprng(5 - 1) == 0){
            printer.print(Printer::Kind::Vending, FreeSoda);
            status = Free;
          }
          else {
            card.withdraw(sodaCost);
            printer.print(Printer::Kind::Vending, SodaBought, flavour, stock[flavour]);
            status = Succ;
          }//else
        }//else
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
