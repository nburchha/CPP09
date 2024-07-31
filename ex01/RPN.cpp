#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this == &other)
		return *this;
	_stack = other._stack;
	return *this;
}

bool RPN::checkInput(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;

	for (std::string::const_iterator it = input.begin(); it != input.end(); ++it)
	{
		char c = *it;
		if (!std::isdigit(c) && c != ' ' && c != '/' && c != '*' && c != '+' && c != '-')
			return std::cerr << "Invalid character in input: " << c << std::endl, false;
	}
	while (iss >> token)
	{
		if (token == "/" || token == "*" || token == "+" || token == "-")
			continue;
		char* end;
		long num = std::strtol(token.c_str(), &end, 10);
		if (*end != '\0')
			return std::cerr << "Invalid token: " << token << std::endl, false;
		if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min())
			return std::cerr << "Invalid token: Out of range: " << token << std::endl, false;
	}
	return true;
}

static int add(int a, int b) {return a + b;}
static int subtract(int a, int b) {return a - b;}
static int multiply(int a, int b) {return a * b;}
static int divide(int a, int b) {if (b == 0) throw std::runtime_error("Division by zero!");return a / b;}

int RPN::calculate(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;

	Operation operations[] = {
		{"+", add},
		{"-", subtract},
		{"*", multiply},
		{"/", divide}
	};

	while (iss >> token)
	{
		if (std::isdigit(token[0]))
			_stack.push(std::atoi(token.c_str()));
		else if (_stack.size() > 1)
		{
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			for (int i = 0; i < 4; ++i)
			{
				if (token == operations[i].symbol)
				{
					int result = operations[i].function(a, b);
					_stack.push(result);
				}
			}
		}
		else
			throw std::runtime_error("Not a valid calculation!");
	}
	return _stack.top();
}
