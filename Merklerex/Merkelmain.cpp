#include <iostream>
#include <vector>
#include "Merkelmain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"


Merkelmain::Merkelmain()
{

}


void Merkelmain::init()
{
	int input;
	currentTime = orderBook.getEarliestTime();
	// wallet.insertCurrency("BTC", 10);

	while (true)
	{
		printMenu();
		input = getUserInput();
		processUserInput(input);
	}
}


void Merkelmain::printMenu()
{
	// command-line menu interface
	std::cout << "1: Print help \n";
	std::cout << "2: Print exchange stats \n";
	std::cout << "3: Make an offer \n";
	std::cout << "4: Make a bid \n";
	std::cout << "5: Print wallet \n";
	std::cout << "6: Continue \n";
	std::cout << "=============";
	std::cout << "Current time: " << currentTime << "\n";
}


void Merkelmain::printHelp()
{
	std::cout << "Your aim is to make money. Analyse the market and make bids. \n";
}


void Merkelmain::printMarketStats()
{
	for (std::string const& p : orderBook.getKnownProducts())
	{
		std::cout << "Product: " << p << "\n";
		
		std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
																  p,
																  currentTime);

		std::cout << "Asks seen: " << entries.size() << "\n";
		std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << "\n";
		std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << "\n";
	}
}


void Merkelmain::enterAsk()
{
	std::cout << "Make an offer - enter the following: product, price, amount (e.g. ETH/BTC,200,5) \n";
	std::string input;
	std::getline(std::cin, input);

	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
	if (tokens.size() != 3)
	{
		std::cout << "Invalid input: " << input << "\n";
	}
	else
	{
		try
		{
			OrderBookEntry obe = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::ask
			);

			if (wallet.canFulfilOrder(obe))
			{
				std::cout << "Wallet looks good. \n";
				orderBook.insertOrder(obe);
			}
			else
			{
				std::cout << "Wallet has insufficient funds. \n";
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Merkelmain::enterAsk invalid input. \n";
		}
	}

	std::cout << "You typed: " << input << "\n";
}


void Merkelmain::enterBid()
{
	std::cout << "Make a bid - enter the following: product, price, amount (e.g. ETH/BTC,200,5) \n";
	std::string input;
	std::getline(std::cin, input);

	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
	if (tokens.size() != 3)
	{
		std::cout << "Invalid input: " << input << "\n";
	}
	else
	{
		try
		{
			OrderBookEntry obe = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::bid
			);

			if (wallet.canFulfilOrder(obe))
			{
				std::cout << "Wallet looks good. \n";
				orderBook.insertOrder(obe);
			}
			else
			{
				std::cout << "Wallet has insufficient funds. \n";
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Merkelmain::enterAsk invalid input. \n";
		}
	}

	std::cout << "You typed: " << input << "\n";
}


void Merkelmain::printWallet()
{
	std::cout << wallet.toString() << "\n";
}


void Merkelmain::goToNextTimeframe()
{
	std::cout << "Going to next time frame.. \n";
	for (std::string& p : orderBook.getKnownProducts())
	{
		std::cout << "Matching " << p << "\n";
		std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
		std::cout << "Sales: " << sales.size() << "\n";
		for (OrderBookEntry& sale : sales)
		{
			std::cout << "Sale price: " << sale.price << "\n";
			std::cout << "Amount: " << sale.amount << "\n";

			wallet.processSale(sale);
		}
	}

	currentTime = orderBook.getNextTime(currentTime);
}


int Merkelmain::getUserInput()
{
	int userOption = 0;
	std::string line;
	std::cout << "Type in option 1 to 6 \n";
	std::getline(std::cin, line);

	try
	{
		userOption = std::stoi(line);
	}
	catch (const std::exception& e)
	{
		// Handle error here.
	}

	std::cout << "You chose: " << userOption << "\n";
	return userOption;
}


void Merkelmain::processUserInput(int userOption)
{
	// bad input
	if (userOption <= 0 || userOption >= 7)
	{
		std::cout << "Invalid choice. Choose 1 to 6 only. \n";
	}

	if (userOption == 1)
	{
		printHelp();
	}

	if (userOption == 2)
	{
		printMarketStats();
	}

	if (userOption == 3)
	{
		enterAsk();
	}

	if (userOption == 4)
	{
		enterBid();
	}

	if (userOption == 5)
	{
		printWallet();
	}

	if (userOption == 6)
	{
		goToNextTimeframe();
	}
}