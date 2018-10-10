
#include "AbstractVM.hpp"


int main(int argc, const char* argv[])
{
    if (argc <= 2)
        AbstractVM abstractVM = AbstractVM(argv[1]);
    else
        std::cout << "usage" << "\n";
	return 0;
}