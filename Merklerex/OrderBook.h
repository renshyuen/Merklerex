#pragma once

#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"


class OrderBook
{
public:
	/* Construct, reading a csv data file */
	OrderBook(std::string fileName);

	/* Method to get a vector of all known products in dataset. */
	std::vector<std::string> getKnownProducts();

	/* Method to retrieve a vector of Orders according to sent filters. */
	std::vector<OrderBookEntry> getOrders(OrderBookType type, 
										  std::string product, 
										  std::string timestamp);

	/* Method that returns the earliest time in the OrderBook. */
	std::string getEarliestTime();

	/* Method that returns the next timing after the sent time
	   in the OrderBook if there is no next timestamp, wrapping
	   around to the start.
	*/
	std::string getNextTime(std::string timestamp);

	void insertOrder(OrderBookEntry& order);

	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);


private:
	std::vector<OrderBookEntry> orders;
};