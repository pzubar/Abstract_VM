//
// Created by Petro ZUBAR on 9/9/18.
//

#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include "Operand.hpp"

class Factory
{
  private:
//	static IOperand *_createInt8operand(std::string &value)
//	{
//		return new Operand<int8_t>(std::stod(value), Int8);
//	}
//	static IOperand *_createInt16operand(std::string &value)
//	{
//		return new Operand<int16_t>(std::stod(value), Int16);
//	}
//	static IOperand *_createInt32operand(std::string &value)
//	{
//		return new Operand<int32_t>(std::stod(value), Int32);
//	}
//	static IOperand *_createFloatOperand(std::string &value)
//	{
//		return new Operand<float>(std::stod(value), Float);
//	}
//	static IOperand *_createDoubleOperand(std::string &value)
//	{
//		return new Operand<double>(std::stod(value), Double);
//	}

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

  public:
	Factory(){};
	~Factory(){};

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
//	{
//		IOperand const * ((*arr[]))( std::string const & value ) const{
//			_createInt8,
//			_createInt16,
//			_createInt32,
//			_createFloat,
//			_createDouble
//		};
//		return arr[type](value);
//	};
};
#endif //ABSTRACTVM_FACTORY_HPP
