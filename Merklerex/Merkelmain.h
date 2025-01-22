#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"


class Merkelmain
{
public:
	Merkelmain();

	/* Call this method to start the simulation. */
	void init();

	
private:
	void printMenu();
	void printHelp();
	void printMarketStats();
	void enterAsk();
	void enterBid();
	void printWallet();
	void goToNextTimeframe();

	int getUserInput();
	void processUserInput(int userOption);

	std::string currentTime;

	OrderBook orderBook{ "20200317.csv" };
	Wallet wallet;
};
