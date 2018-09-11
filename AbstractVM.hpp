//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <vector>
#include "Factory.hpp"


class AbstractVM {
    private:
        std::vector<const IOperand *> _vector;
        Factory _factory;
    public:
    AbstractVM(){
        _factory = Factory();
    };
    ~AbstractVM(){};

    void push(std::string const & value, eOperandType type) {
        const IOperand * operand = _factory.createOperand(type, value);
        _vector.push_back(operand);
    };

    void dump(void) {
        for(int i = 0; i < _vector.size(); i++) {
            std::cout << _vector[i]->toString() << std::endl;
        };
    };

};


#endif //AVM_ABSTRACTVM_HPP
