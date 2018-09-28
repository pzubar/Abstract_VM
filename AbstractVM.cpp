//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{
    _factory = Factory();

    _operations["add"] = &AbstractVM::add;
	_operations["dump"] = &AbstractVM::dump;
	_operations["print"] = &AbstractVM::print;
	_operations["pop"] = &AbstractVM::pop;
	_operations["sub"] = &AbstractVM::sub;
	_operations["sub"] = &AbstractVM::mul;

    _commands["push"] = &AbstractVM::push;
	_commands["assert"] = &AbstractVM::assert;

    _types["int8"] = Int8;
    _types["int16"] = Int16;
    _types["int32"] = Int32;
    _types["float"] = Float;
    _types["double"] = Double;
};

void AbstractVM::push(std::string const &value, eOperandType type) {
	const IOperand *operand = _factory.createOperand(type, value);
	_container.push_front(operand);
	_containerSize++;
};

void AbstractVM::assert(std::string const &value, eOperandType type)
{
	if (_container.front()->toString() == value && type)
		std::cout << "Assertation succesfull\n";
	else
		throw Exception("Assertation failed");
}

void AbstractVM::add() {
	if (_containerSize < 2) {
		throw Exception("Unable to ADD, there are less than 2 elements in the stack!!!");
	}
	_unstackElems();
	_container.push_front(*_buff[1] + *_buff[0]);
	delete (_buff[0]);
	delete (_buff[1]);
}

void AbstractVM::sub() {
	if (_containerSize < 2) {
		throw Exception("Unable to SUB, there are less than 2 elements in the stack!!!");
	}
	_unstackElems();
	_container.push_front(*_buff[1] - *_buff[0]);
	delete (_buff[0]);
	delete (_buff[1]);
}

void AbstractVM::mul() {
	if (_containerSize < 2) {
		throw Exception("Unable to MUL, there are less than 2 elements in the stack!!!");
	}
	_unstackElems();
	_container.push_front(*_buff[1] * *_buff[0]);
	delete (_buff[0]);
	delete (_buff[1]);
}


void AbstractVM::checkExpression(std::string expression) {
	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
					   "((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|"
					   "(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg))
	{
		throw Exception("Invalid expression!");
	}
}

void AbstractVM::print() {
	if (_container.front()->getType() == Int8)
		std::cout << "PRINTING: " << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
	else
		std::cout << "Printing in ascii FAILED\n";

}

void AbstractVM::setExpression(std::string expression) {
	_line++;
	try {
		checkExpression(expression);
	}
	catch (std::exception &exception)
	{
		std::cout << "catch it!" << exception.what() << std::endl;
		return;
	}
	std::array<std::string, 3> result = { "", "", "" };

	std::regex ws_re("\\s|\\(|\\)");
	std::copy( std::sregex_token_iterator(expression.begin(), expression.end(), ws_re, -1),
			   std::sregex_token_iterator(),
			   result.begin());
	if (!result[2].empty())
	{
		try {
			AbstractVM::execute(result[0], result[1], result[2]);
		}
		catch (std::exception &exception)
		{
			std::cout << "catch it!" << exception.what() << std::endl;
		}
	}
	else
	{
		try {
			AbstractVM::execute(result[0]);
		}
		catch (std::exception &exception) {
			std::cout << "catch it!" << exception.what() << std::endl;
		}
	}
}

void AbstractVM::dump() {
	for (const auto iterator : _container) {
		std::cout << stod(iterator->toString()) << std::endl;
	}
};

void AbstractVM::pop() {
	if (_containerSize < 1) {
		throw Exception("Error : Pop on empty stack");
	}
	_container.pop_front();
}

void AbstractVM::execute(std::string operation) {

	(this->*_operations[operation])();
}

void AbstractVM::execute(std::string command, std::string type, std::string num) {

	(this->*_commands[command])(num, _types[type]);
}
