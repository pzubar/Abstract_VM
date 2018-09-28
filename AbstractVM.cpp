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

    _commands["push"] = &AbstractVM::push;

    _types["int8"] = Int8;
    _types["int16"] = Int16;
    _types["int32"] = Int32;
    _types["float"] = Float;
    _types["double"] = Double;

};

void AbstractVM::add() {
        _unstackElems();
        _container.push_front(*_buff[1] + *_buff[0]);
        delete (_buff[0]);
        delete (_buff[1]);
}

void AbstractVM::excecute(std::string operation) {
//	if (_containerSize < 2) {
//        throw Exception("Unable to ADD, there are less than 2 elements!!!");
//    }
    (this->*_operations[operation])();
}

void AbstractVM::excecute(std::string command, std::string type, std::string num) {

	(this->*_commands[command])(num, _types[type]);
}

void AbstractVM::checkExpression(std::string expression) {
	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
					   "((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|"
					   "(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
	if (!std::regex_match(expression.begin(), expression.end(), reg))
	{
		throw Exception("Invalid expression!");
//		std::cout << ("Invalid expression!\n");
//		return;
	}
	return;
}

void AbstractVM::print(void)
{
	if (_container.front()->getType() == Int8)
		std::cout << "PRINTING: " << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
	else
		std::cout << "Printing in ascii FAILED\n";

}

void AbstractVM::setExpression(std::string expression)
{
//	std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
//					   "((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|"
//					   "(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
//	if (!std::regex_match(expression.begin(), expression.end(), reg))
//	{
//		throw Exception("Invalid expression!");
//		std::cout << ("Invalid expression!\n");
//		return;
//	}
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
	if (result[2] != "")
	{
		try {
			AbstractVM::excecute(result[0], result[1], result[2]);
		}
		catch (std::exception &exception)
		{
			std::cout << "catch it!" << exception.what() << std::endl;
		}
	}
	else
	{
		try {
			AbstractVM::excecute(result[0]);
		}
		catch (std::exception &exception)
		{
			std::cout << "catch it!" << exception.what() << std::endl;
		}
	}
}

void AbstractVM::dump(void) {
	for (const auto iterator : _container) {
		std::cout << stod(iterator->toString()) << std::endl;
	}
};