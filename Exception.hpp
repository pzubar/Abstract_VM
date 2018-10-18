//
// Created by Petro ZUBAR on 10/6/18.
//

#ifndef ABSTRACTVM_EXCEPTION_HPP
#define ABSTRACTVM_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <type_traits>

class Exception {
public:
    class InputException : public std::exception {
        std::invalid_argument _error;
    public:
        explicit InputException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class OverflowException : public std::exception {
        std::overflow_error _error;
    public:
        explicit OverflowException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class UnderflowException : public std::exception {
        std::underflow_error _error;
    public:
        explicit UnderflowException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class EmptyStackException : public std::exception {
        std::runtime_error _error;
    public:
        explicit EmptyStackException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class DivisionByZeroException : public std::exception {
        std::runtime_error _error;
    public:
        explicit DivisionByZeroException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class SmallStackException : public std::exception {
        std::runtime_error _error;
    public:
        explicit SmallStackException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class AssertionException : public std::exception {
        std::runtime_error _error;
    public:
        explicit AssertionException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class WrongExitException : public std::exception {
        std::logic_error _error;
    public:
        explicit WrongExitException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };

    class NoExitException : public std::exception {
        std::logic_error _error;
    public:
        explicit NoExitException(const char *msg) : _error(msg) {}
        const char *what() const noexcept override {
            return _error.what();
        }
    };
};

#endif
