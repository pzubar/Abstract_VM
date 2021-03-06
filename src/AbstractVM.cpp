#include "AbstractVM.hpp"

AbstractVM::AbstractVM() = default;

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
		while (getline(file, str))
			_setExpression(str);
		try
		{
			if (!_isExit)
			{
				_isExit = !_isExit;
				throw Exception::NoExitException("No \"exit\" command in file");
			}
			else
			{
				_terminate();
			}
		}
		catch (Exception::NoExitException &exception)
		{
			_out << RED << "Line " << _line << ": " << CLOSE
				<< "No Exit Exception: " << exception.what() << std::endl;
			_terminate();
		}
		file.close();
	}
	else
		std::cout << "Unable to open file" << std::endl;
}

AbstractVM::~AbstractVM()
{
	_container.clear();
}

AbstractVM &AbstractVM::operator=(const AbstractVM &rhs)
{
	_container = rhs._container;
	_containerSize = rhs._containerSize;
	return *this;
}

AbstractVM::AbstractVM(const AbstractVM &rhs)
{
	*this = rhs;
}

void AbstractVM::_setExpression(std::string expression)
{
	try
	{
		_checkExpression(expression);
		for (size_t i = 0; !isalpha(expression[i]); i++)
		{
			if (expression.empty())
				return;
			expression.erase(i--, 1);
		}
		std::array<std::string, 3> result = {{"", "", ""}};
		std::regex splitBy{R"(\s+|\(|\))"};
		std::copy(std::sregex_token_iterator(expression.begin(), expression.end(), splitBy, -1),
				  std::sregex_token_iterator(),
				  result.begin());
		if (!result[2].empty())
			AbstractVM::_execute(result[0], result[1], result[2]);
		else
			AbstractVM::_execute(result[0]);
	}
	catch (Exception::InputException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Input Exception: "
			 << exception.what() << " (expression: " << expression << ")" << std::endl;
	}
	catch (Exception::WrongExitException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Wrong Exit Exception: "
			 << exception.what() << std::endl;
	}
	catch (Exception::NoExitException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "No Exit Exception: "
			 << exception.what() << std::endl;
		_terminate();
	}
	catch (Exception::SmallStackException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Less that two values in stack: "
			 << exception.what() << std::endl;
	}
	catch (Exception::OverflowException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Overflow exception: " << exception.what() << std::endl;
	}
	catch (Exception::UnderflowException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Underflow exception: " << exception.what() << std::endl;
	}
	catch (Exception::EmptyStackException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Empty stack exception: " << exception.what() << std::endl;
	}
	catch (Exception::DivisionByZeroException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Exception: " << exception.what() << std::endl;
	}
	catch (Exception::AssertionException &exception)
	{
		_out << RED << "Line " << _line << ": " << CLOSE << "Assertion Exception: " << exception.what() << std::endl;
	}
}

void AbstractVM::_push(std::string const &value, eOperandType type)
{
	Factory factory = Factory();
	const IOperand *operand = factory.createOperand(type, value);
	_container.push_front(operand);
	_containerSize++;
};

void AbstractVM::_pop()
{
	if (!_containerSize)
	{
		throw Exception::EmptyStackException("Instruction \"pop\" on an empty stack");
	}
	delete(_container.front());
	_container.pop_front();
	_containerSize--;
}

void AbstractVM::_assert(std::string const &value, eOperandType type)
{
	if (!_containerSize)
	{
		throw Exception::EmptyStackException("Instruction \"asert\" on an empty stack");
	}
	if (_container.front()->getType() == Float && _container.front()->toString() != std::to_string(std::stof(value)))
		throw Exception::AssertionException("Values are not equal");
	else if (_container.front()->getType() != Float &&
			 _container.front()->toString() != std::to_string(std::stod(value)) && type)
		throw Exception::AssertionException("Values are not equal");
}

void AbstractVM::_add()
{
	_unstackElements();
	_container.push_front(*_buff[1] + *_buff[0]);
	_containerSize++;
	_out << GREEN << "Line " << _line << ": " << CLOSE << "add" << std::endl;
}

void AbstractVM::_sub()
{
	_unstackElements();
	_container.push_front(*_buff[1] - *_buff[0]);
	_containerSize++;
	_out << GREEN << "Line " << _line << ": " << CLOSE << "sub" << std::endl;
}

void AbstractVM::_mul()
{
	_unstackElements();
	_container.push_front(*_buff[1] * *_buff[0]);
	_containerSize++;
	_out << GREEN << "Line " << _line << ": " << CLOSE << "mul" << std::endl;
}

void AbstractVM::_div()
{
	_unstackElements();
	if (std::stod(_buff[0]->toString()) == 0)
	{
		throw Exception::DivisionByZeroException("Division by zero");
	}
	_container.push_front(*_buff[1] / *_buff[0]);
	_containerSize++;
	_out << GREEN << "Line " << _line << ": " << CLOSE << "div" << std::endl;
}

void AbstractVM::_mod()
{
	_unstackElements();
	if (std::stod(_buff[0]->toString()) == 0)
	{
		throw Exception::DivisionByZeroException("Modulo by zero");
	}
	_container.push_front(*_buff[1] % *_buff[0]);
	_containerSize++;
	_out << GREEN << "Line " << _line << ": " << CLOSE << "mod" << std::endl;
}

void AbstractVM::_checkExpression(std::string & expression)
{
	_line++;
	if (_isExit && expression != ";;")
		throw(Exception::WrongExitException("The program has an \"exit\" instruction"));
	if (expression == ";;")
	{
		if (_isExit && !_fromFile)
			_terminate();
		else if (!_isExit && !_fromFile)
		{
			_isExit = true;
			throw Exception::NoExitException("The program does not have an exit instruction");
		}
	}

	std::regex reg("(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
				   "((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|"
				   "(pop|dump|add|sub|mul|div|mod|print|exit|sort|max|min|size)|(\\;.*)|(\\n))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg) && !expression.empty())
		throw Exception::InputException("Unknown instruction or invalid input");
    expression = expression.substr(0, expression.find(';', 0));
}

void AbstractVM::_dump()
{
	_out << GREEN << "Line " << _line << ": " << CLOSE << "dump" << std::endl;
	for (const auto iterator : _container)
	{
		_out << stod(iterator->toString()) << std::endl;
	}
};

void AbstractVM::_print()
{
	if (!_containerSize)
		throw Exception::EmptyStackException("Instruction \"print\" on an empty stack");
	else if (_container.front()->getType() == Int8)
	{
		_out << GREEN << "Line " << _line << ": " << CLOSE << "print" << std::endl;
		_out << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
	}
	else
		throw Exception::AssertionException("Printing failed, the first operand in stack is not Int8");
}

void AbstractVM::_quit()
{
	_out << GREEN << "Line " << _line << ": " << CLOSE << "exit" << std::endl;
	_isExit = true;
}

void AbstractVM::_terminate()
{
	if (!_isExit && !_fromFile)
		throw(Exception::WrongExitException("The program does not have an exit instruction"));
	std::cout << _out.str();
	exit(0);
}

void AbstractVM::_execute(std::string operation)
{
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
			{"sort", &AbstractVM::_sort},
			{"max", &AbstractVM::_max},
			{"min", &AbstractVM::_min},
			{"size", &AbstractVM::_size},
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
			{"assert", &AbstractVM::_assert}};
	std::map<std::string, eOperandType> types =
		{
			{"int8", Int8},
			{"int16", Int16},
			{"int32", Int32},
			{"float", Float},
			{"double", Double}};
	(this->*commands[command])(num, types[type]);
	_out << GREEN << "Line " << _line << ": " << CLOSE << command << " " << type << "(" << num << ")" << std::endl;
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

void AbstractVM::_sort()
{
	_container.sort([](const IOperand *first, const IOperand *second) {
		return stod(first->toString()) < stod(second->toString());
	});
	_out << GREEN << "Line " << _line << ": " << CLOSE << "sort" << std::endl;
}

void AbstractVM::_max()
{
	std::forward_list<const IOperand *> buff;

	if (!_containerSize)
	{
		throw Exception::EmptyStackException("Instruction \"max\" on an empty stack");
	}
	buff = _container;
	buff.sort([](const IOperand *first, const IOperand *second) {
		return stod(first->toString()) > stod(second->toString());
	});
	_out << GREEN << "Line " << _line << ": " << CLOSE << "max" << std::endl;
	_out << stod(buff.front()->toString()) << std::endl;
	buff.clear();
}

void AbstractVM::_min()
{
	std::forward_list<const IOperand *> buff;

	if (!_containerSize)
	{
		throw Exception::EmptyStackException("Instruction \"min\" on an empty stack");
	}
	buff = _container;
	buff.sort([](const IOperand *first, const IOperand *second) {
		return stod(first->toString()) < stod(second->toString());
	});
	_out << GREEN << "Line " << _line << ": " << CLOSE << "min" << std::endl;
	_out << stod(buff.front()->toString()) << std::endl;
	buff.clear();
}

void AbstractVM::_size()
{
	_out << GREEN << "Line " << _line << ": " << CLOSE << "size" << std::endl << _containerSize << std::endl;
}