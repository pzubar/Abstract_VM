//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <iostream>
#include <string>
#include "IOperand.hpp"
#include <typeinfo>
#include <algorithm> //for max

template <class Type>
class Operand : public IOperand
{
  private:
	Type _value;
    std::string _strval;
	eOperandType _type;
	int _precision;
	Operand();

  public:
	Operand(Type val, eOperandType type)
		:   _value(val),
		    _type(type)
    {
			_strval = std::to_string(val);
    };

	eOperandType getType(void) const
	{
		return this->_type;
	}
    virtual std::string const & toString( void ) const
    {
//		std::string result = new	std::to_string(555);
		//std::string s = "akaka";
        return _strval;
//        return "gega";
//        return new Operand<int32_t>((static_cast<int32_t>(this->_value) + static_cast<int32_t>(rhs->toString()), Int32);
    }
    virtual IOperand const * operator+( IOperand const & rhs ) const
    {
		eOperandType bigerType = std::max(this->getType(),rhs.getType());
		std::cout << "bigger_type: " << bigerType << std::endl; //this->getType() > rhs.getType() ? this->getType()
		return new Operand<int32_t>((this->_value) + std::stod(rhs.toString()), bigerType);
    }
    // /    IOperand const * operator+( IOperand const & rhs ) const;
};

#endif //AVM_OPERAND_HPP
