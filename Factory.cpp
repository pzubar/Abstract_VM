#include "Factory.hpp"

IOperand const * Factory::createInt8( std::string const & value ) const {
    if (stod(value) > INT8_MAX)
        throw Exception::OverflowException("Value: " + value + " Int8 overflow, element won't be added to stack");
    if (stod(value) < INT8_MIN)
        throw Exception::UnderflowException("Value: " + value + " Int8 underflow, element won't be added to stack");
    return new Operand<int8_t>(std::stod(value), Int8);
};
IOperand const * Factory::createInt16( std::string const & value ) const {
    if (stod(value) > INT16_MAX)
        throw Exception::OverflowException("Value: " + value + " Int16 overflow, element won't be added to stack");
    if (stod(value) < INT16_MIN)
        throw Exception::UnderflowException("Value: " + value + " Int16 underflow, element won't be added to stack");
    return new Operand<int16_t>(std::stod(value), Int16);
};
IOperand const * Factory::createInt32( std::string const & value ) const {
    if (stod(value) > INT32_MAX)
        throw Exception::OverflowException("Value: " + value + " Int32 overflow, element won't be added to stack");
    if (stod(value) < INT32_MIN)
        throw Exception::UnderflowException("Value: " + value + " Int32 underflow, element won't be added to stack");
    return new Operand<int32_t>(std::stod(value), Int32);
};
IOperand const * Factory::createFloat( std::string const & value ) const {
    if (stod(value) > FLT_MAX)
        throw Exception::OverflowException("Value: " + value + " Float overflow, element won't be added to stack");
    if (stod(value) < -FLT_MAX)
        throw Exception::UnderflowException("Value: " + value + " Float underflow, element won't be added to stack");
    return new Operand<float>(std::stod(value), Float);
};
IOperand const * Factory::createDouble( std::string const & value ) const {
    if (stold(value) > DBL_MAX)
        throw Exception::OverflowException("Value: " + value + " Double overflow, element won't be added to stack");
    if (stold(value) < DBL_MIN)
        throw Exception::UnderflowException("Value: " + value + " Double underflow, element won't be added to stack");
    return new Operand<double>(std::stod(value), Double);
};
IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    IOperand const * ((Factory::*arr[]))( std::string const & value ) const{
            &Factory::createInt8,
            &Factory::createInt16,
            &Factory::createInt32,
            &Factory::createFloat,
            &Factory::createDouble
    };
    return (this->*arr[type])(value);
};