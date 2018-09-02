//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "IOperand.hpp"

//template <class Type>
//class Array {
//public:
//    Array( size_t size )
//            :	data_ ( new Type [ size ]),
//                 size_ ( size ) {}
//
//    ~Array () {
//        delete [] data_ ;
//    }
//
//    size_t size() const {
//        return size_ ;
//    }
//
//    Type operator []( size_t i) const {
//        return data_[i];
//    }
//
//    Type & operator []( size_t i) {
//        return data_[i];
//    }
//private :
//    Type * data_ ;
//    size_t size_ ;
//};


#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

class Oper : IOperand {
    private:
        enum eOperandType{ Int8, Int16, Int32, Float, Double };
//    IOperand const * operator+( IOperand const & rhs ) const;

};

#endif //UNTITLED_OPER_HPP