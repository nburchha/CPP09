#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _btcPrices;
		//parsing
		void getPrices();
		void printPrice(const std::string& date, const float value);
		//cannonical
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& copy);
	public:
		void processInput(const std::string filename);
		BitcoinExchange();
		~BitcoinExchange();
};