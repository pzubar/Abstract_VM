#include "AbstractVM.hpp"

int main(int argc, const char *argv[])
{
    if (argc <= 2)
        AbstractVM AbstractVM(argv[1]);
    else
        std::cout << "usage: ./avm [filename]?" << std::endl;
    return 0;
}