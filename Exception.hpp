//
// Created by Petro ZUBAR on 10/6/18.
//

#ifndef ABSTRACTVM_EXCEPTION_HPP
#define ABSTRACTVM_EXCEPTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>

//class Exception : public std::exception
//{
//private:
//    const char *_msg;
//public:
//
//class InputError : public std::invalid_argument
//{
//    private:
//        const char *_msg;
//    public:
////        InputError(){};
//        explicit InputError( const std::string& what_arg );
//};
//
//    Exception(const char *msg): _msg(msg){};
//    virtual const char* what() const throw()
//    {
//        return (_msg);
//    }
//};

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
                    _msg = message;
                }
                virtual ~InputException() throw (){}

                virtual const char* what() const throw (){
                    return _msg.c_str();
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
