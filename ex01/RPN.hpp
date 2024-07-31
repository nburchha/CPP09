#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <cctype>

struct Operation
{
	std::string symbol;
	int (*function)(int, int);
};

class RPN
{
	private:
		std::stack<int> _stack;
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		bool checkInput(const std::string& input);
		int calculate(const std::string& input);
};