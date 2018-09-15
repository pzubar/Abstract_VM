//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include "Factory.hpp"
#include "Operand.hpp"
#include <map>
#include <exception>
#include <regex>

//TODO - add exceptions

class AbstractVM {
private:
    std::map<std::string, void (AbstractVM::*)(void)> _operations;
	std::map<std::string, void (AbstractVM::*)(std::string const &, eOperandType type)> _commands;
	std::map<std::string, eOperandType> _types;

	std::forward_list<const IOperand *> _container;
	size_t _containerSize = 0;
	Factory _factory;
	//array of two elems
	const IOperand * _buff[2];

	void _unstackElems(void) {
		_buff[0] = _container.front();
		_container.pop_front();
		_buff[1] = _container.front();
		_container.pop_front();
	};

public:
	AbstractVM();
	~AbstractVM() {};
class Exception : public std::exception
	{
		private:
			const char *_msg;
		public:
			Exception(const char *msg): _msg(msg){};
			virtual const char* what() const throw()
			{
				return (_msg);
			}
	};

	void push(std::string const &value, eOperandType type) {
		const IOperand *operand = _factory.createOperand(type, value);
		_container.push_front(operand);
		_containerSize++;
	};


	void pop(void) {
		_container.pop_front();
	}

	void dump(void) {
		for (const auto iterator : _container) {
			std::cout << stod(iterator->toString()) << std::endl;
		}

	};

	void assert(std::string const &value) const {
		if (_container.front()->toString() == value)
			std::cout << "Assertation succesfull\n";
		else
			std::cout << "Assertation FAILED\n";
	}

	void add(void);


	void print(void)
	{
		if (_container.front()->getType() == Int8)
			std::cout << "PRINTING: " << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
		else
			std::cout << "Printing in ascii FAILED\n";

	}

	void excecute(std::string operation);

	void excecute(std::string command, std::string type, std::string num);

	void setExpression(std::string expression)
	{
		std::regex reg(	"(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
				 		"((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|"
						"(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
		if (!std::regex_match(expression.begin(), expression.end(), reg))
		{
			throw Exception("Invalid expression!");
		}
		std::vector<std::string> result(3);

		std::regex ws_re("\\s|\\(|\\)");
		std::copy( std::sregex_token_iterator(expression.begin(), expression.end(), ws_re, -1),
				   std::sregex_token_iterator(),
				   result.begin());
		if (result.size() == 3)
		{

			AbstractVM::excecute(result[0], result[1], result[2]);
		}
	}
};


#endif //AVM_ABSTRACTVM_HPP

//		for (std::forward_list<const IOperand *>::iterator it = _container.begin(); it!=_container.end(); ++it) {
//			std::cout << stod((*it)->toString()) << std::endl;
//			std::cout << stod() << std::endl;
//		}