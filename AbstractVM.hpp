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
#include <fstream>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Exception.hpp"

// TODO: refacror exception logic
// TODO: test absent "exit" option bug

class AbstractVM {
private:
    std::forward_list<const IOperand *>	_container;
    size_t								_containerSize = 0;
    int									_line = 0;
    bool								_isExit = false;
    bool								_fromFile = false;
	const IOperand *                    _buff[2];
	std::stringstream					_out;

    AbstractVM();
	void _unstackElements();
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
    void quit();
    void terminate();
    void execute(std::string operation);
    void execute(std::string command, std::string type, std::string num);
    std::string checkExpression(std::string expression);

public:
    explicit AbstractVM(const char *filename);

    AbstractVM &operator=(const AbstractVM &rhs) {
		_container = rhs._container;
		_out << rhs._out.rdbuf();
		return *this;
	}

	~AbstractVM();
	void setExpression(std::string expression);
};


#endif //AVM_ABSTRACTVM_HPP
