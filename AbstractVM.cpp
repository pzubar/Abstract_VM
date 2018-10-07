//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{
    _factory = Factory();

    _commands["push"] = &AbstractVM::push;
	_commands["assert"] = &AbstractVM::assert;
};

void AbstractVM::push(std::string const &value, eOperandType type) {
	try {
		const IOperand *operand = _factory.createOperand(type, value);
		_container.push_front(operand);
		_containerSize++;
	}
	catch (Exception::OverflowException &exception) {
		std::cout << "Line " << _line << ": Overflow exception: " << exception.what() << std::endl;
	}
    catch (Exception::UnderflowException &exception) {
        std::cout << "Line " << _line << ": Underflow exception: " << exception.what() << std::endl;
    }
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


std::string AbstractVM::checkExpression(std::string expression) {
	if (expression == ";;")
	{
		if (_isExit) {
            terminate();
        }
		else
			throw Exception("Invalid termination!");
		return NULL;
	}
	expression = expression.substr(0, expression.find(";", 0));
	std::cout << "expression: " << expression << std::endl;
	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
					   "((float|double)(\\([-]?\\d*[,]*?\\d+\\)))))|"
					   "(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg))
	{
		std::stringstream error;
		error << "Line " << _line << ": Unknown instruction or invalid input: \"" << expression << "\"";
		throw Exception::InputException(error.str());
	}
	return expression;
}



void AbstractVM::setExpression(std::string expression) {
	_line++;
	try {
		checkExpression(expression);
	}
	catch (std::exception &exception) {
		std::cout << exception.what() << std::endl;
		if (std::strcmp(exception.what(), "Invalid termination!") == 0)
		{

		}
		return;
	}
	std::array<std::string, 3> result = {"", "", ""};

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
			std::cout << exception.what() << std::endl;
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

void AbstractVM::print() {
	if (_containerSize && _container.front()->getType() == Int8)
		std::cout << "PRINTING: " << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
	else
		throw Exception("Printing failed");
}

void AbstractVM::exit() {
	if (_fromFile)
	{
		std::cout << "!!!Exiting requested\n";
	}
	else
	{
		_isExit = true;
	}
}

void AbstractVM::terminate() {
	std::cout << _result;
    system("leaks avm");
	exit();
}

void AbstractVM::execute(std::string operation) {
	std::map<std::string, void (AbstractVM::*)(void)> operations =
	{
		{"add", &AbstractVM::add},
		{"dump", &AbstractVM::dump},
		{"print", &AbstractVM::print},
		{"pop", &AbstractVM::pop},
		{"sub", &AbstractVM::sub},
		{"mul", &AbstractVM::mul},
		{"exit", &AbstractVM::exit},
	};
	(this->*operations[operation])();
}

void AbstractVM::execute(std::string command, std::string type, std::string num) {

	std::map<std::string, eOperandType> types =
	{
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	};


	(this->*_commands[command])(num, types[type]);
}
