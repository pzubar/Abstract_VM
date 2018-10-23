#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include <iostream>
#include <forward_list>
#include <map>
#include <exception>
#include <regex>
#include <array>
#include <sstream>
#include <fstream>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Exception.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[1;32m"
#define CLOSE "\033[0m"

class AbstractVM
{
  private:
    std::forward_list<const IOperand *> _container;
    size_t _containerSize = 0;
    int _line = 0;
    bool _isExit = false;
    bool _fromFile = false;
    const IOperand *_buff[2];
    std::stringstream _out;

    AbstractVM();
    void _unstackElements();
    void _push(std::string const &value, eOperandType type);
    void _pop();
    void _dump();
    void _assert(std::string const &value, eOperandType type);
    void _add();
    void _sub();
    void _mul();
    void _div();
    void _mod();
    void _print();
    void _quit();
    void _terminate();
    void _sort();
    void _max();
    void _min();
    void _execute(std::string operation);
    void _execute(std::string command, std::string type, std::string num);
    void _setExpression(std::string expression);
    void _checkExpression(std::string expression);

  public:
    explicit AbstractVM(const char *filename);
    AbstractVM &operator=(const AbstractVM &rhs);
    AbstractVM(const AbstractVM &rhs);
    ~AbstractVM();
};

#endif
