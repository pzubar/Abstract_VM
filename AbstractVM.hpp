//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include "Factory.hpp"
#include <array>
//TODO - add exceptions
class AbstractVM {
private:
	std::forward_list<const IOperand *> _container;
	size_t _containerSize = 0;
	Factory _factory;

	std::array<const IOperand *, 2> _unstackElems(void) {
		std::array<const IOperand *, 2> buff;

		buff[0] = _container.front();
		_container.pop_front();
		buff[1] = _container.front();
		_container.pop_front();
		return (buff);
	};

public:
	AbstractVM() {
		_factory = Factory();
	};

	~AbstractVM() {};

	void push(std::string const &value, eOperandType type) {
		const IOperand *operand = _factory.createOperand(type, value);
		_container.push_front(operand);
		_containerSize++;
	};


	void pop(void) {
		_container.pop_front();
	}

	void dump(void) {
		std::cout << "fwd_list:\n";
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

	void add(void) {
		std::array<const IOperand *, 2> buff;

		if (_containerSize < 2) {
			std::cout << "unable to ADD, there are less than 2 elements!!!" << std::endl;
		}
		buff[0] = _container.front();
		_container.pop_front();
		buff[1] = _container.front();
		_container.pop_front();
		const IOperand *operand = *buff[0] + *buff[1];
		_container.push_front(operand);
		delete (buff[0]);
		delete (buff[1]);

	}

	void sub(void) {
		std::array<const IOperand *, 2> buff;

		if (_containerSize < 2) {
			std::cout << "unable to SUB, there are less than 2 elements!!!" << std::endl;
		}

		buff = _unstackElems();
		const IOperand *operand = *buff[1] - *buff[0];
		_container.push_front(operand);
		delete (buff[0]);
		delete (buff[1]);


	}

	void print(void)
	{
		if (_container.front()->getType() == Int8)
			std::cout << "PRINTING: " << static_cast<char>(std::stoi(_container.front()->toString())) << std::endl;
		else
			std::cout << "Printing in ascii FAILED\n";

	}

};


#endif //AVM_ABSTRACTVM_HPP

//		for (std::forward_list<const IOperand *>::iterator it = _container.begin(); it!=_container.end(); ++it) {
//			std::cout << stod((*it)->toString()) << std::endl;
//			std::cout << stod() << std::endl;
//		}