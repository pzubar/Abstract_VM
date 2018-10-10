//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{
	//	if (std::cin.bad()) {
	//		// IO error
	//		std::cout << "A";
	//	} else if (!std::cin.eof()) {
	//		std::cout << "B";
	//		// format error (not possible with getline but possible with operator>>)
	//	} else {
	//		std::cout << "C";
	//		// format error (not possible with getline but possible with operator>>)
	//		// or end of file (can't make the difference)
	//	}
};

AbstractVM::AbstractVM(const char * filename)
{
	std::string str;
	std::ifstream myfile(filename);

	if (!filename)
		while (getline(std::cin, str))
			setExpression(str);
	else if (myfile.is_open())
	{
		_fromFile = true;
		while ( getline (myfile,str) )
			setExpression(str);
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

void AbstractVM::setExpression(std::string expression)
{
	std::ostringstream out;

	_line++;
	try {
		checkExpression(expression);
		std::array<std::string, 3> result = {"", "", ""};

		std::regex splitBy("\\s|\\(|\\)");
		std::copy(std::sregex_token_iterator(expression.begin(), expression.end(), splitBy, -1),
				  std::sregex_token_iterator(),
				  result.begin());
		if (!result[2].empty())
			AbstractVM::execute(result[0], result[1], result[2]);
		else
			AbstractVM::execute(result[0]);
	}
	catch (Exception::InputException &exception) {
		out << "Line " << _line << ": Input Exception "
			<< exception.what() << "(expression: " << expression << ")" << std::endl;
	}
	catch (Exception::WrongExitException &exception) {
		out << "Line " << _line << ": Wrong Exit Exception: " << exception.what() << std::endl;
		if (strcmp(exception.what(), "The program does not have an exit instruction") == 0)
		{
			_isExit = true;
            _output += out.str();
			terminate();
		}
	}
	catch (Exception::SmallStackException &exception) {
		out << "Line " << _line << ": Less that two values in stack: " << exception.what() << std::endl;
	}
	catch (Exception::OverflowException &exception) {
		out << "Line " << _line << ": Overflow exception: "	<< exception.what() << std::endl;
	}
	catch (Exception::UnderflowException &exception) {
		out << "Line " << _line << ": Underflow exception: " << exception.what() << std::endl;
	}
	catch (Exception::EmptyStackException &exception) {
		out << "Line " << _line << ": Empty stack exception: " << exception.what() << std::endl;
	}
	catch (Exception::DivisionByZeroException &exception) {
		out << "Line " << _line << ": Exception: " << exception.what() << std::endl;
	}
	catch (Exception::AssertionException &exception) {
		out << "Line " << _line << ": Assertion Exception: " << exception.what() << std::endl;
	}
	_output += out.str();
}

void AbstractVM::push(std::string const &value, eOperandType type)
{
	Factory factory = Factory();
	const IOperand *operand = factory.createOperand(type, value);
	_container.push_front(operand);
	_containerSize++;
};

void AbstractVM::pop() {
    if (_containerSize < 1) {
        throw Exception::EmptyStackException("Instruction \"pop\" on an empty stack");
    }
    _container.pop_front();
}

void AbstractVM::assert(std::string const &value, eOperandType type)
{
	if (_container.front()->toString() != value && type)
		throw Exception::AssertionException("Values are not equal");
}

void AbstractVM::add() {
    _unstackElements();
	_container.push_front(*_buff[1] + *_buff[0]);
}

void AbstractVM::sub() {
    _unstackElements();
	_container.push_front(*_buff[1] - *_buff[0]);
}

void AbstractVM::mul() {
    _unstackElements();
	_container.push_front(*_buff[1] * *_buff[0]);
}

void AbstractVM::div() {
	if (_buff[0]->toString() == "0") {
		throw Exception::DivisionByZeroException("Division by zero");
	}
    _unstackElements();
	_container.push_front(*_buff[1] / *_buff[0]);
}

void AbstractVM::mod() {
	if (_buff[0]->toString() == "0") {
		throw Exception::DivisionByZeroException("Modulo by zero");
	}
    _unstackElements();
	_container.push_front(*_buff[1] % *_buff[0]);
}

std::string AbstractVM::checkExpression(std::string expression) {
	if (expression == ";;")
	{
		if (_isExit && !_fromFile)
            terminate();
		else if (!_isExit && !_fromFile)
			throw Exception::WrongExitException("The program does not have an exit instruction");
	}
	expression = expression.substr(0, expression.find(";", 0));
	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
					   "((float|double)(\\([-]?\\d*[,]*?\\d+\\)))))|"
					   "(pop|dump|add|sub|mul|div|mod|print|exit))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg))
		throw Exception::InputException("Unknown instruction or invalid input");
	return expression;
}

void AbstractVM::dump() {
	std::ostringstream out;

	for (const auto iterator : _container) {
		out << stod(iterator->toString()) << std::endl;
		_output += out.str();
	}
};

void AbstractVM::print() {
	std::ostringstream out;

	if (!_containerSize)
		throw Exception::EmptyStackException("Instruction \"print\" on an empty stack");
	else if (_container.front()->getType() == Int8)
	{
		out << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
		_output += out.str();
	}
	else
		throw Exception::AssertionException("Printing failed, the first operand in stack is not Int8");
}

void AbstractVM::quit() {
	if (_fromFile)
		terminate();
	else
		_isExit = true;
}

void AbstractVM::terminate() {
	if (!_isExit && !_fromFile)
		throw (Exception::WrongExitException("The program does not have an exit instruction"));
	std::cout << _output;
//    system("leaks avm");
	exit(0);
}

void AbstractVM::execute(std::string operation) {
	if (_isExit)
		throw (Exception::WrongExitException("The program has an exit instruction"));
	std::map<std::string, void (AbstractVM::*)(void)> operations =
	{
		{"add", &AbstractVM::add},
		{"dump", &AbstractVM::dump},
		{"print", &AbstractVM::print},
		{"pop", &AbstractVM::pop},
		{"sub", &AbstractVM::sub},
		{"mul", &AbstractVM::mul},
		{"div", &AbstractVM::div},
		{"mod", &AbstractVM::mod},
		{"exit", &AbstractVM::quit},
	};
	(this->*operations[operation])();
	if (_buff[0])
	{
		delete (_buff[0]);
		_buff[0] = NULL;
		delete (_buff[1]);
		_buff[1] = NULL;
	}
}

void AbstractVM::execute(std::string command, std::string type, std::string num)
{
	std::map<std::string, void (AbstractVM::*)(std::string const &, eOperandType type)> commands =
	{
		{"push", &AbstractVM::push},
		{"assert", &AbstractVM::assert}
	};
	std::map<std::string, eOperandType> types =
	{
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	};
	(this->*commands[command])(num, types[type]);
}

void AbstractVM::_unstackElements()
{
	if (_containerSize < 2)
		throw Exception::SmallStackException("Arithmetic instruction cannot be executed");
	_buff[0] = _container.front();
	_container.pop_front();
	_buff[1] = _container.front();
	_container.pop_front();
};