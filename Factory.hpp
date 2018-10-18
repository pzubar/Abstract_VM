//
// Created by Petro ZUBAR on 9/9/18.
//

#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP


#include <climits>
#include <float.h>
#include "Operand.tpp"
#include "Exception.hpp"

class Factory
{
  private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

  public:
	Factory(){};
	~Factory(){};

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

};
#endif //ABSTRACTVM_FACTORY_HPP
