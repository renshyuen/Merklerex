#include <iostream>
#include "Wallet.h"
#include "CSVReader.h"


Wallet::Wallet()
{

}


void Wallet::insertCurrency(std::string type, double amount)
{
	double balance;
	if (amount < 0)
	{
		// crash the program if user puts negative amount
		throw std::exception{};
	}

	// checks if the specified currency type exists
	if (currencies.count(type) == 0)
	{
		balance = 0;
	}

	else
	{
		balance = currencies[type];
	}

	balance += amount;
	currencies[type] = balance;
}


bool Wallet::removeCurrency(std::string type, double amount)
{
	if (amount < 0 || currencies.count(type) == 0 || currencies[type] < amount)
	{
		return false;
	}

	currencies[type] -= amount;
	return true;
}


bool Wallet::containsCurrency(std::string type, double amount)
{
	if (currencies.count(type) == 0)
	{
		return false;
	}

	return currencies[type] >= amount;
}


bool Wallet::canFulfilOrder(OrderBookEntry order)
{
	/*
		Currency 1 / Currency 2, price, amount
		Currency 1 is the currency you own
		Currency 2 is the currency you want
	*/
	std::vector<std::string> currencies = CSVReader::tokenise(order.product, '/');

	// ask: check if you own enough Currency 1 to buy Currency 2
	if (order.orderType == OrderBookType::ask)
	{
		double amount = order.amount;
		std::string currency = currencies[0];
		std::cout << "Wallet::canFulfilOrder: currency = " << currency << ", amount = " << amount << "\n";
		return containsCurrency(currency, amount);
	}

	// bid: check if you own enough Currency 2 to sell Currency 1
	if (order.orderType == OrderBookType::bid)
	{
		double amount = order.amount * order.price;
		std::string currency = currencies[1];
		return containsCurrency(currency, amount);
	}

	return false;
}


void Wallet::processSale(OrderBookEntry& sale)
{
	std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

	if (sale.orderType == OrderBookType::asksale)
	{
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currs[0];

		double incomingAmount = sale.amount * sale.price;
		std::string incomingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
}


std::string Wallet::toString()
{
	std::string s;
	for (std::pair<std::string, double> pair : currencies)
	{
		std::string currency = pair.first;
		double amount = pair.second;
		s += currency + ": " + std::to_string(amount) + "\n";
	}
	return s;
}