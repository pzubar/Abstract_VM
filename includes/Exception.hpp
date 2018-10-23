#ifndef ABSTRACTVM_EXCEPTION_HPP
#define ABSTRACTVM_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <type_traits>

class Exception
{
  public:
    class InputException : public std::exception
    {
        std::invalid_argument _error;

      public:
        explicit InputException(const char *msg);
        const char *what() const noexcept override;
        ~InputException() override;
    };

    class OverflowException : public std::exception
    {

        std::overflow_error _error;

      public:
        explicit OverflowException(const char *msg);
        const char *what() const noexcept override;
        ~OverflowException() override;
    };

    class UnderflowException : public std::exception
    {
        std::underflow_error _error;

      public:
        explicit UnderflowException(const char *msg);
        const char *what() const noexcept override;
        ~UnderflowException() override;
    };

    class EmptyStackException : public std::exception
    {
        std::runtime_error _error;

      public:
        explicit EmptyStackException(const char *msg);
        const char *what() const noexcept override;
        ~EmptyStackException() override;
    };

    class DivisionByZeroException : public std::exception
    {
        std::runtime_error _error;

      public:
        explicit DivisionByZeroException(const char *msg);
        const char *what() const noexcept override;
        ~DivisionByZeroException() override;
    };

    class SmallStackException : public std::exception
    {
        std::runtime_error _error;

      public:
        explicit SmallStackException(const char *msg);
        const char *what() const noexcept override;
        ~SmallStackException() override;
    };

    class AssertionException : public std::exception
    {
        std::runtime_error _error;

      public:
        explicit AssertionException(const char *msg);
        const char *what() const noexcept override;
        ~AssertionException() override;
    };

    class WrongExitException : public std::exception
    {
        std::logic_error _error;

      public:
        explicit WrongExitException(const char *msg);
        const char *what() const noexcept override;
        ~WrongExitException() override;
    };

    class NoExitException : public std::exception
    {
        std::logic_error _error;

      public:
        explicit NoExitException(const char *msg);
        const char *what() const noexcept override;
        ~NoExitException() override;
    };
};

#endif
