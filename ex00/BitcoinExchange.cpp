#include "BitcoinExchange.hpp"

static std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

void BitcoinExchange::printPrice(const std::string& date, const float value)
{
	std::map<std::string, float>::iterator it = _btcPrices.lower_bound(date);
	if (it == _btcPrices.end() || it->first != date) {
		if (it == _btcPrices.begin()) {
			std::cerr << "Error: no available exchange rate for the date " << date << std::endl;
			return;
		}
		--it;
	}
	const std::string& closestDate = it->first;
	float exchangeRate = it->second;

	float result = value * exchangeRate;
	std::cout << closestDate << " => " << value << " = " << result << std::endl;
}


void BitcoinExchange::processInput(const std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Error: couldn't open file!");
	
	std::string line;
	std::getline(file, line);
	if (line != "date | value")
		throw std::runtime_error("Database header invalid!\n");
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string date, valueStr;

		if (!std::getline(iss, date, '|') || !std::getline(iss, valueStr))
			std::cerr << "Error: incorrect number of cells!" << std::endl;
		date = trim(date);
		valueStr = trim(valueStr);
		try {
			float value = std::stof(valueStr);
			if (value < 0)
				throw std::out_of_range("Error: not a positive number!");
			else if (value > 1000)
				throw std::out_of_range("Error: too large a number!");
			printPrice(date, value);
		} catch (const std::invalid_argument& e) {
			std::cerr << "Error: invalid value in file!" << std::endl;
		} catch (const std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	file.close();
}

void BitcoinExchange::getPrices()
{
	std::ifstream file("./data.csv");

	if (!file.is_open())
		throw std::runtime_error("Error: couldn't open database!");
	std::string line;
	std::getline(file, line);
	if (line != "date,exchange_rate") {
		file.close();
		throw std::runtime_error("Error: Database header invalid!\n");
	}
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string date, valueStr;
		if (!std::getline(iss, date, ',') || !std::getline(iss, valueStr)) {
			file.close();
			throw std::runtime_error("Error: incorrect number of cells in Database!");
		}
		try {
			float value = std::stof(valueStr);
			_btcPrices[date] = value;
		} catch (const std::invalid_argument& e) {
			std::cerr << "Error: invalid value '" << valueStr << "' for date " << date << std::endl;
		} catch (const std::out_of_range& e) {
			std::cerr << "Error: value out of range '" << valueStr << "' for date " << date << std::endl;
		}
	}
	file.close();
}

BitcoinExchange::BitcoinExchange()
{
	getPrices();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_btcPrices = other._btcPrices;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy)
{
	if (this == &copy)
		return *this;
	_btcPrices = copy._btcPrices;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}
