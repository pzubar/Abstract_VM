//
// Created by Petro ZUBAR on 9/9/18.
//

#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include "Operand.hpp"

class Factory
{
  private:
	static IOperand *_createInt8operand(std::string &value)
	{
		return new Operand<int8_t>(std::stod(value), Int8);
	}
	static IOperand *_createInt16operand(std::string &value)
	{
		return new Operand<int16_t>(std::stod(value), Int16);
	}
	static IOperand *_createInt32operand(std::string &value)
	{
		return new Operand<int32_t>(std::stod(value), Int32);
	}
	static IOperand *_createFloatOperand(std::string &value)
	{
		return new Operand<float>(std::stod(value), Float);
	}
	static IOperand *_createDoubleOperand(std::string &value)
	{
		return new Operand<double>(std::stod(value), Double);
	}

  public:
	static IOperand *createOperand(std::string &value, eOperandType type)
	{
		static IOperand *((*arr[]))(std::string & value){
			_createInt8operand,
			_createInt16operand,
			_createInt32operand,
			_createFloatOperand,
			_createDoubleOperand
		};
		return arr[type](value);
	};
};
#endif //ABSTRACTVM_FACTORY_HPP
