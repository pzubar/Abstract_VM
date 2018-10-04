#include "AbstractVM.hpp"


int main(void)
{
	AbstractVM abstractVM = AbstractVM();
	std::string str;


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

//	system("leaks avm");
	return 0;
}