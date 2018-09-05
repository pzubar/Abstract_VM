//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <iostream>
#include "IOperand.hpp"

template <class Type>
class Operand : public IOperand {
    private:
        Type _value;
        std::string type;

    public:
        Operand( Type val )
           :	_value ( val ) {};

        void getValue(void) {
            std::cout << _value << std::endl;
        }
        void    TT(){
            std::cout << "sdfsdf" << std::endl;
         }
        eOperandType getType( void ) const {
            return Int8;
        }


//    IOperand const * operator+( IOperand const & rhs ) const;

};

#endif //AVM_OPERAND_HPP
