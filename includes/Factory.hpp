#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include <climits>
#include <float.h>
#include "Operand.hpp"
#include "Exception.hpp"

class Factory
{
private:
	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

public:
	Factory();
	Factory &operator=(const Factory &rhs);
	Factory(const Factory &rhs);
	~Factory();
	IOperand const *createOperand(eOperandType type, std::string const &value) const;
};
#endif
