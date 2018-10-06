//
// Created by Petro ZUBAR on 10/6/18.
//

#ifndef ABSTRACTVM_EXCEPTION_HPP
#define ABSTRACTVM_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>

class Exception: public std::exception
{
    public:
        class InputException: public std::logic_error
        {
            public:
                explicit InputException(const char* message) : std::logic_error(message)
                {
                    _msg = message;
                }
                explicit InputException(const std::string& message) : std::logic_error(message)
                {
                    _msg = "Input Exception: " + message;
                }
                InputException(const InputException &rhs) : std::logic_error(rhs)
                {
                    *this = rhs;
                }
                virtual ~InputException() _NOEXCEPT {};
                InputException &operator=(const InputException &rhs) _NOEXCEPT {
                    _msg = rhs._msg;
                    return *this;
                }
                virtual const char* what() const _NOEXCEPT
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
                virtual ~OverflowException() _NOEXCEPT {};
                OverflowException &operator=(const OverflowException &rhs) _NOEXCEPT {
                    _msg = rhs._msg;
                    return *this;
                }
                virtual const char* what() const _NOEXCEPT
                {
                    std::string result = "Overflow Exception: " + _msg;
                    return result.c_str();
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
        virtual ~UnderflowException() _NOEXCEPT {};
        UnderflowException &operator=(const UnderflowException &rhs) _NOEXCEPT {
            _msg = rhs._msg;
            return *this;
        }
        virtual const char* what() const _NOEXCEPT
        {
            std::string result = "Underflow Exception: " + _msg;
            return result.c_str();
        }
    private:
        std::string _msg;
    };

    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the char* lies
     *                 with the caller.
     */
    explicit Exception(const char* message):
            msg_(message)
    {
    }

    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit Exception(const std::string& message):
            msg_(message)
    {}

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~Exception() throw (){}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw (){
        return msg_.c_str();
    }

protected:
    /** Error message.
     */
    std::string msg_;
};


#endif //ABSTRACTVM_EXCEPTION_HPP
