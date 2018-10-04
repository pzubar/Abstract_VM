//
// Created by Petro ZUBAR on 02.09.2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <iostream>
#include <string>
#include "IOperand.hpp"
#include <algorithm>
#include <cmath>
#include <exception>
template <class Type>
class Operand : public IOperand
{
  private:
	Type _value;
	std::string _strval;
	eOperandType _type;

	Operand();
	eOperandType _getBiggerType(IOperand const &rhs) const{
		return static_cast<eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));
	};
  public:
	Operand(Type val, eOperandType type)
		: _value(val),
		  _type(type)
	{
		_strval = std::to_string(val);
	};
	int getPrecision( void ) const {
		return this->getType();
	}
	eOperandType getType(void) const
	{
		return this->_type;
	}
	virtual std::string const &toString(void) const
	{
		return _strval;
	}
	virtual IOperand const *operator+(IOperand const &rhs) const
	{
		return new Operand<int32_t>((this->_value) + std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	virtual IOperand const *operator-(IOperand const &rhs) const
	{
		return new Operand<int32_t>((this->_value) - std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	virtual IOperand const *operator*(IOperand const &rhs) const
	{
		return new Operand<int32_t>((this->_value) * std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	virtual IOperand const *operator/(IOperand const &rhs) const
	{
		return new Operand<int32_t>((this->_value) / std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	virtual IOperand const *operator%(IOperand const &rhs) const
	{
		return new Operand<int32_t>(std::fmod((this->_value),std::stod(rhs.toString())), _getBiggerType(rhs));
	}
};

#endif //AVM_OPERAND_HPP
