//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include "Factory.hpp"


class AbstractVM {
    private:
		std::forward_list<const IOperand *> _container;
        Factory _factory;
    public:
    AbstractVM(){
        _factory = Factory();
    };
    ~AbstractVM(){};

    void push(std::string const & value, eOperandType type) {
        const IOperand * operand = _factory.createOperand(type, value);
        _container.push_front(operand);
    };

    void dump(void) {
		std::cout << "fwd_list:\n";
		for (const auto iterator : _container)
		{
			std::cout << stod(iterator->toString()) << std::endl;
		}
//		for (std::forward_list<const IOperand *>::iterator it = _container.begin(); it!=_container.end(); ++it) {
//			std::cout << stod((*it)->toString()) << std::endl;
//			std::cout << stod() << std::endl;
//		}
    };
    void pop(void) {
		_container.pop_front();
    }

//	void add(void) {
//		_container.pop_front();
//	}
};


#endif //AVM_ABSTRACTVM_HPP
