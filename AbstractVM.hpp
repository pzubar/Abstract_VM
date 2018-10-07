//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <forward_list>
#include <map>
#include <exception>
#include <regex>
#include <array>
#include <sstream>
#include "Factory.hpp"
#include "Operand.hpp"

//TODO - add exceptions
#include "Exception.hpp"

class AbstractVM {
private:

	std::map<std::string, void (AbstractVM::*)(std::string const &, eOperandType type)> _commands;

	std::forward_list<const IOperand *> _container;
	size_t _containerSize = 0;
	Factory _factory;
	int _line = 0;
    bool _isExit = false;
    bool _fromFile = false;

    std::string _result;
	const IOperand * _buff[2];

	void _unstackElems() {
		_buff[0] = _container.front();
		_container.pop_front();
		_buff[1] = _container.front();
		_container.pop_front();
	};
    void _stackBack() {
        _container.push_front(_buff[1]);
        _container.push_front(_buff[0]);
    };

public:
	AbstractVM();
	~AbstractVM() {};
	void push(std::string const &value, eOperandType type);
	void pop();
	void dump();
	void assert(std::string const &value, eOperandType type);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
    void exit();
    void terminate();
	void execute(std::string operation);
	void execute(std::string command, std::string type, std::string num);
	void setExpression(std::string expression);
	std::string checkExpression(std::string expression);
    void checkStack();
};


#endif //AVM_ABSTRACTVM_HPP
