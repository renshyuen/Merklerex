#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"


class Wallet
{
public:
	Wallet();

	/* Method to insert Currency to the Wallet. */
	void insertCurrency(std::string type, double amount);

	/* Method to remove Currency from the Wallet. */
	bool removeCurrency(std::string type, double amount);

	/* Method to check if the Wallet contains this much Currency or more. */
	bool containsCurrency(std::string type, double amount);

	/* Method to check if the Wallet can cope with the Ask or Bid. */
	bool canFulfilOrder(OrderBookEntry order);

	/* Method to update the contents of the Wallet, 
	assumes the Order was made by the owner of the Wallet. */
	void processSale(OrderBookEntry& sale);

	/* Method to generate string representation. */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};
