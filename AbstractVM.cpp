//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"

AbstractVM::AbstractVM() = default;

AbstractVM::~AbstractVM() = default;

AbstractVM &AbstractVM::operator=(const AbstractVM &rhs) {
	_container = rhs._container;
	_containerSize = rhs._containerSize;
	return *this;
}

AbstractVM::AbstractVM(const char *filename)
{
	std::string str;
	std::ifstream file(filename);

	if (!filename)
		while (getline(std::cin, str))
			_setExpression(str);
	else if (file.is_open())
	{
		_fromFile = true;
		while ( getline (file,str) )
			_setExpression(str);
		file.close();
	}
	//TODO cout usage string
	else std::cout << "Unable to open file";
}

void AbstractVM::_setExpression(std::string expression)
{
	try {
		_checkExpression(expression);
        for (size_t i = 0; !isalpha(expression[i]); i++)
			expression.erase(i--, 1);
        std::array<std::string, 3> result = {"", "", ""};

		std::regex splitBy("\\s+|\\(|\\)");
		std::copy(std::sregex_token_iterator(expression.begin(), expression.end(), splitBy, -1),
				  std::sregex_token_iterator(),
				  result.begin());
		if (!result[2].empty())
			AbstractVM::_execute(result[0], result[1], result[2]);
		else
			AbstractVM::_execute(result[0]);
	}
	catch (Exception::InputException &exception) {
		_out << "Line " << _line << ": Input Exception "
			<< exception.what() << "(expression: " << expression << ")" << std::endl;
	}
	catch (Exception::WrongExitException &exception) {
		_out << "Line " << _line << ": Wrong Exit Exception: " << exception.what() << std::endl;
		if (strcmp(exception.what(), "The program does not have an exit instruction") == 0)
			_terminate();
	}
	catch (Exception::SmallStackException &exception) {
		_out << "Line " << _line << ": Less that two values in stack: " << exception.what() << std::endl;
	}
	catch (Exception::OverflowException &exception) {
		_out << "Line " << _line << ": Overflow exception: " << exception.what() << std::endl;
	}
	catch (Exception::UnderflowException &exception) {
		_out << "Line " << _line << ": Underflow exception: " << exception.what() << std::endl;
	}
	catch (Exception::EmptyStackException &exception) {
		_out << "Line " << _line << ": Empty stack exception: " << exception.what() << std::endl;
	}
	catch (Exception::DivisionByZeroException &exception) {
		_out << "Line " << _line << ": Exception: " << exception.what() << std::endl;
	}
	catch (Exception::AssertionException &exception) {
		_out << "Line " << _line << ": Assertion Exception: " << exception.what() << std::endl;
	}
}

void AbstractVM::_push(std::string const &value, eOperandType type)
{
	Factory factory = Factory();
	const IOperand *operand = factory.createOperand(type, value);
	_container.push_front(operand);
	_containerSize++;
};

void AbstractVM::_pop() {
    if (_containerSize < 1) {
        throw Exception::EmptyStackException("Instruction \"pop\" on an empty stack");
    }
    _container.pop_front();
}

void AbstractVM::_assert(std::string const &value, eOperandType type)
{
	if (_container.front()->toString() != value && type)
		throw Exception::AssertionException("Values are not equal");
}

void AbstractVM::_add() {
    _unstackElements();
	_container.push_front(*_buff[1] + *_buff[0]);
	_containerSize++;
}

void AbstractVM::_sub() {
    _unstackElements();
	_container.push_front(*_buff[1] - *_buff[0]);
	_containerSize++;
}

void AbstractVM::_mul() {
    _unstackElements();
	_container.push_front(*_buff[1] * *_buff[0]);
	_containerSize++;
}

void AbstractVM::_div() {
	if (_buff[0]->toString() == "0") {
		throw Exception::DivisionByZeroException("Division by zero");
	}
    _unstackElements();
	_container.push_front(*_buff[1] / *_buff[0]);
	_containerSize++;
}

void AbstractVM::_mod() {
	if (_buff[0]->toString() == "0") {
		throw Exception::DivisionByZeroException("Modulo by zero");
	}
    _unstackElements();
	_container.push_front(*_buff[1] % *_buff[0]);
	_containerSize++;
}

void AbstractVM::_checkExpression(std::string expression) {
	_line++;
	if (expression == ";;")
	{
		if (_isExit && !_fromFile)
            _terminate();
		else if (!_isExit && !_fromFile)
		{
			_isExit = true;
			throw Exception::WrongExitException("The program does not have an exit instruction");
		}

	}
	expression = expression.substr(0, expression.find(';', 0));
	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
					   "((float|double)(\\([-]?\\d*[,]*?\\d+\\)))))|"
					   "(pop|dump|add|sub|mul|div|mod|print|exit))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg))
		throw Exception::InputException("Unknown instruction or invalid input");
}

void AbstractVM::_dump() {
	for (const auto iterator : _container) {
		_out << stod(iterator->toString()) << std::endl;
	}
};

void AbstractVM::_print() {
	if (!_containerSize)
		throw Exception::EmptyStackException("Instruction \"print\" on an empty stack");
	else if (_container.front()->getType() == Int8)
	{
		_out << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
	}
	else
		throw Exception::AssertionException("Printing failed, the first operand in stack is not Int8");
}

void AbstractVM::_quit() {
	if (_fromFile)
		_terminate();
	else
		_isExit = true;
}

void AbstractVM::_terminate() {
	if (!_isExit && !_fromFile)
		throw (Exception::WrongExitException("The program does not have an exit instruction"));
	std::cout << _out.str();
//    system("leaks avm");
	exit(0);
}

void AbstractVM::_execute(std::string operation) {
	if (_isExit)
		throw (Exception::WrongExitException("The program has an exit instruction"));
	std::map<std::string, void (AbstractVM::*)(void)> operations =
	{
		{"add", &AbstractVM::_add},
		{"dump", &AbstractVM::_dump},
		{"print", &AbstractVM::_print},
		{"pop", &AbstractVM::_pop},
		{"sub", &AbstractVM::_sub},
		{"mul", &AbstractVM::_mul},
		{"div", &AbstractVM::_div},
		{"mod", &AbstractVM::_mod},
		{"exit", &AbstractVM::_quit},
	};
	(this->*operations[operation])();
	if (_buff[0])
	{
		delete (_buff[0]);
		_buff[0] = nullptr;
		delete (_buff[1]);
		_buff[1] = nullptr;
	}
}

void AbstractVM::_execute(std::string command, std::string type, std::string num)
{
	std::map<std::string, void (AbstractVM::*)(std::string const &, eOperandType type)> commands =
	{
		{"push", &AbstractVM::_push},
		{"assert", &AbstractVM::_assert}
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
	_containerSize -= 2;
};