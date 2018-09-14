//
// Created by Petro ZUBAR on 02.09.2018.
//

#include "AbstractVM.hpp"


void sayhi(){
    std::cout << "HI!!!\n";
}
AbstractVM::AbstractVM()
{
    _factory = Factory();
    sayhi();
    _map["add"] = &AbstractVM::add;

//    (this->*_map["add"])();

};

void AbstractVM::add() {
        std::array<const IOperand *, 2> buff;

        if (_containerSize < 2) {
            std::cout << "unable to ADD, there are less than 2 elements!!!" << std::endl;
        }
        buff[0] = _container.front();
        _container.pop_front();
        buff[1] = _container.front();
        _container.pop_front();
        const IOperand *operand = *buff[1] + *buff[0];
        _container.push_front(operand);
        delete (buff[0]);
        delete (buff[1]);
//std::cout << "hello";
//sayhi();
}

//void AbstractVM::sayHello() {
//    std::cout << "Hello, ma friend!\n";
//}