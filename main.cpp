#include "AbstractVM.hpp"


int main(int argc, char **argv)
{
	AbstractVM abstractVM = AbstractVM();
	std::string str;

    if (argc == 2)
    {
        AbstractVM abstractVMF = AbstractVM(argv[1]);
    } else
        while (getline(std::cin, str)) {
            abstractVM.setExpression(str);
        }



//	if (std::cin.bad()) {
//		// IO error
//		std::cout << "A";
//	} else if (!std::cin.eof()) {
//		std::cout << "B";
//		// format error (not possible with getline but possible with operator>>)
//	} else {
//		std::cout << "C";
//		// format error (not possible with getline but possible with operator>>)
//		// or end of file (can't make the difference)
//	}

//
	return 0;
}