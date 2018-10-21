#include "../includes/Factory.hpp"

IOperand const * Factory::createInt8( std::string const & value ) const {
    if (stod(value) > SCHAR_MAX)
        throw Exception::OverflowException("Int8 overflow, element won't be added to stack");
    if (stod(value) < SCHAR_MIN)
        throw Exception::UnderflowException("Int8 underflow, element won't be added to stack");
    return new Operand<int8_t>(static_cast<int8_t>(std::stoi(value)), Int8);
};
IOperand const * Factory::createInt16( std::string const & value ) const {
    if (stod(value) > SHRT_MAX)
        throw Exception::OverflowException("Int16 overflow, element won't be added to stack");
    if (stod(value) < SHRT_MIN)
        throw Exception::UnderflowException("Int16 underflow, element won't be added to stack");
    return new Operand<int16_t>(static_cast<int16_t>(std::stoi(value)), Int16);
};
IOperand const * Factory::createInt32( std::string const & value ) const {
    if (stod(value) > INT_MAX)
        throw Exception::OverflowException("Int32 overflow, element won't be added to stack");
    if (stod(value) < INT_MIN)
        throw Exception::UnderflowException("Int32 underflow, element won't be added to stack");
    return new Operand<int32_t>(static_cast<int32_t>(std::stoi(value)), Int32);
};
IOperand const * Factory::createFloat( std::string const & value ) const {
    if (stod(value) > FLT_MAX)
        throw Exception::OverflowException("Float overflow, element won't be added to stack");
    if (stod(value) < -FLT_MAX)
        throw Exception::UnderflowException("Float underflow, element won't be added to stack");
    return new Operand<float>(std::stof(value), Float);
};
IOperand const * Factory::createDouble( std::string const & value ) const {
    if (stold(value) > DBL_MAX)
        throw Exception::OverflowException("Double overflow, element won't be added to stack");
    if (stold(value) < DBL_MIN)
        throw Exception::UnderflowException("Double underflow, element won't be added to stack");
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

Factory::Factory() = default;
Factory::~Factory() = default;
Factory& Factory::operator=(const Factory &rhs) = default;
Factory::Factory(const Factory &rhs) {
    *this = rhs;
}
