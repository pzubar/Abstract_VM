//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{
    _factory = Factory();

    _operations["add"] = &AbstractVM::add;

    _commands["push"] = &AbstractVM::push;
    _types["int8"] = Int8;
    _types["int16"] = Int16;
    _types["int32"] = Int32;
    _types["float"] = Float;
    _types["double"] = Double;


};

void AbstractVM::add() {
        if (_containerSize < 2) {
            std::cout << "unable to ADD, there are less than 2 elements!!!" << std::endl;
        }
        _unstackElems();
        _container.push_front(*_buff[1] + *_buff[0]);
        delete (_buff[0]);
        delete (_buff[1]);
}

void AbstractVM::excecute(std::string operation) {
    (this->*_operations[operation])();
}

void AbstractVM::excecute(std::string command, std::string type, std::string num) {
    (this->*_commands[command])(num, _types[type]);
}