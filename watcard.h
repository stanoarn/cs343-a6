#pragma once

#include <uFuture.h>

class WATCard {
	WATCard( const WATCard & ) = delete;	// prevent copying
	WATCard & operator=( const WATCard & ) = delete;
	unsigned int balance;
  public:
	typedef Future_ISM<WATCard *> FWATCard;	// future watcard pointer
	WATCard();
	void deposit( unsigned int amount );
	void withdraw( unsigned int amount );
	unsigned int getBalance();
};
