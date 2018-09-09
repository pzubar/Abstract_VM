//
// Created by Petro ZUBAR on 9/9/18.
//

#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include "IOperand.hpp"
#include "Operand.hpp"

class Factory {
    public:
        static IOperand * createInt8operand(std::string & value)
        {
            return new Operand<int8_t>(std::stod(value), Int8);
        }
        static IOperand * createInt16operand(std::string & value)
        {
            return new Operand<int16_t>(std::stod(value), Int16);
        }
        static IOperand * createOperand(std::string & value, eOperandType type) {

            static IOperand *((*arr[]))(std::string &value) {
                Factory::createInt8operand,
                Factory::createInt16operand
            };

            return arr[type](value);
        }

//            static IOperand * (*options []) (std::string & value) = {
//                    Factory::createInt8operand,
//                    Factory::createInt16operand;
//            };
//            return new Operand<int16_t>(std::stod(value), Int16);
//        }
};


#endif //ABSTRACTVM_FACTORY_HPP
