//
// Created by Petro ZUBAR on 10/6/18.
//

#ifndef ABSTRACTVM_EXCEPTION_HPP
#define ABSTRACTVM_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <type_traits>

class Exception
{
    public:
        class InputException: public std::invalid_argument
        {
            public:
                explicit InputException(const char* message) : std::invalid_argument(message)
                {
                    _msg = message;
                }
                explicit InputException(const std::string& message) : std::invalid_argument(message)
                {
                    _msg = message;
                }
                InputException(const InputException &rhs) : std::invalid_argument(rhs)
                {
                    *this = rhs;
                }
                virtual ~InputException()= default;
                InputException &operator=(const InputException &rhs) noexcept {
                    _msg = rhs._msg;
                    return *this;
                }
                virtual const char* what() const noexcept
                {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };

        class OverflowException: public std::overflow_error
        {
            public:
                explicit OverflowException(const char* message) : std::overflow_error(message)
                {
                    _msg = message;
                }
                explicit OverflowException(const std::string& message) : std::overflow_error(message)
                {
                    _msg = message;
                }
                OverflowException(const OverflowException &rhs) : std::overflow_error(rhs)
                {
                    *this = rhs;
                }
                virtual ~OverflowException() noexcept {};
                OverflowException &operator=(const OverflowException &rhs) noexcept {
                    _msg = rhs._msg;
                    return *this;
                }
                virtual const char* what() const noexcept
                {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };
    class UnderflowException: public std::underflow_error
    {
        public:
            explicit UnderflowException(const char* message) : std::underflow_error(message)
            {
                _msg = message;
            }
            explicit UnderflowException(const std::string& message) : std::underflow_error(message)
            {
                _msg = message;
            }
            UnderflowException(const UnderflowException &rhs) : std::underflow_error(rhs)
            {
                *this = rhs;
            }
            virtual ~UnderflowException() noexcept {};
            UnderflowException &operator=(const UnderflowException &rhs) noexcept {
                _msg = rhs._msg;
                return *this;
            }
            virtual const char* what() const noexcept
            {
                return  _msg.c_str();
            }
        private:
            std::string _msg;
    };

    class EmptyStackException: public std::runtime_error
    {
        public:
            explicit EmptyStackException(const char* message) : std::runtime_error(message)
            {
                _msg = message;
            }
            explicit EmptyStackException(const std::string& message) : std::runtime_error(message)
            {
                _msg = message;
            }
            EmptyStackException(const EmptyStackException &rhs) : std::runtime_error(rhs)
            {
                *this = rhs;
            }
            virtual ~EmptyStackException() noexcept {};
            EmptyStackException &operator=(const EmptyStackException &rhs) noexcept {
                _msg = rhs._msg;
                return *this;
            }
            virtual const char* what() const noexcept
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
    };

    class DivisionByZeroException: public std::runtime_error
    {
        public:
            explicit DivisionByZeroException(const char* message) : std::runtime_error(message)
            {
                _msg = message;
            }
            explicit DivisionByZeroException(const std::string& message) : std::runtime_error(message)
            {
                _msg = message;
            }
            DivisionByZeroException(const DivisionByZeroException &rhs) : std::runtime_error(rhs)
            {
                *this = rhs;
            }
            ~DivisionByZeroException() noexcept override = default;
            DivisionByZeroException &operator=(const DivisionByZeroException &rhs) noexcept {
                _msg = rhs._msg;
                return *this;
            }
            const char* what() const noexcept override
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
    };

    class SmallStackException: public std::runtime_error
    {
        public:
            explicit SmallStackException(const char* message) : std::runtime_error(message)
            {
                _msg = message;
            }
            SmallStackException(const SmallStackException &rhs) : std::runtime_error(rhs)
            {
                *this = rhs;
            }
            ~SmallStackException() override = default;
            SmallStackException &operator=(const SmallStackException &rhs) noexcept {
                _msg = rhs._msg;
                return *this;
            }
            const char* what() const noexcept override
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
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

};


#endif //ABSTRACTVM_EXCEPTION_HPP
