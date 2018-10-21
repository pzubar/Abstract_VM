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

    Operand() {
        _type = 0;
    };
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
	int getPrecision() const override {
		return this->getType();
	}
	eOperandType getType() const override
	{
		return this->_type;
	}
	std::string const &toString() const override
	{
		return _strval;
	}
	IOperand const *operator+(IOperand const &rhs) const override
	{
		return new Operand<double>((this->_value) + std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	IOperand const *operator-(IOperand const &rhs) const override
	{
		return new Operand<double>((this->_value) - std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	IOperand const *operator*(IOperand const &rhs) const override
	{
		return new Operand<double>((this->_value) * std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	IOperand const *operator/(IOperand const &rhs) const override
	{
		return new Operand<double>((this->_value) / std::stod(rhs.toString()), _getBiggerType(rhs));
	}
	IOperand const *operator%(IOperand const &rhs) const override
	{
		return new Operand<double>(std::fmod((this->_value), std::stod(rhs.toString())), _getBiggerType(rhs));
	}
};

#endif //AVM_OPERAND_HPP
