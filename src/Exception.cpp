#include "Exception.hpp"

Exception::InputException::InputException(const char *msg) : _error(msg)
{
}
const char *Exception::InputException::what() const noexcept
{
    return _error.what();
}
Exception::InputException::~InputException() = default;

Exception::OverflowException::OverflowException(const char *msg) : _error(msg)
{
}
const char *Exception::OverflowException::what() const noexcept
{
    return _error.what();
}
Exception::OverflowException::~OverflowException() = default;

Exception::UnderflowException::UnderflowException(const char *msg) : _error(msg)
{
}
const char *Exception::UnderflowException::what() const noexcept
{
    return _error.what();
}
Exception::UnderflowException::~UnderflowException() = default;

Exception::EmptyStackException::EmptyStackException(const char *msg) : _error(msg)
{
}
const char *Exception::EmptyStackException::what() const noexcept
{
    return _error.what();
}
Exception::EmptyStackException::~EmptyStackException() = default;

Exception::DivisionByZeroException::DivisionByZeroException(const char *msg) : _error(msg)
{
}
const char *Exception::DivisionByZeroException::what() const noexcept
{
    return _error.what();
}
Exception::DivisionByZeroException::~DivisionByZeroException() = default;

Exception::SmallStackException::SmallStackException(const char *msg) : _error(msg)
{
}
const char *Exception::SmallStackException::what() const noexcept
{
    return _error.what();
}
Exception::SmallStackException::~SmallStackException() = default;

Exception::AssertionException::AssertionException(const char *msg) : _error(msg)
{
}
const char *Exception::AssertionException::what() const noexcept
{
    return _error.what();
}
Exception::AssertionException::~AssertionException() = default;

Exception::WrongExitException::WrongExitException(const char *msg) : _error(msg)
{
}
const char *Exception::WrongExitException::what() const noexcept
{
    return _error.what();
}
Exception::WrongExitException::~WrongExitException() = default;

Exception::NoExitException::NoExitException(const char *msg) : _error(msg)
{
}
const char *Exception::NoExitException::what() const noexcept
{
    return _error.what();
}
Exception::NoExitException::~NoExitException() = default;
