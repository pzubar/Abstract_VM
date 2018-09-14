#include <iostream>
#include "AbstractVM.hpp"
#include "Operand.hpp"
#include "Factory.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

int main(void)
{
	AbstractVM abstractVM = AbstractVM();

	std::string str = "push int8(100)";
	std::regex reg ("(\\s*)?push\\s((int((8|16|32)\\(\\d*\\)))|((float|double)(\\(\\d*\\))))$");
	std::smatch mathes;

//	std::copy( std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
//			   std::sregex_token_iterator(),
//			   std::ostream_iterator<std::string>(std::cout, "\n"));
//	str::smatch

	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;
	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		std::cout << match.str() << "\n";
		currentMatch++;
	}
	std::cout << std::endl;

	std::regex ws_re("\\s|\\(|\\)");
	std::copy( std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1),
			   std::sregex_token_iterator(),
			   std::ostream_iterator<std::string>(std::cout, "\n"));

//	regexp: "(\s*)?push\s((int((8|16|32)\(\d*\)))|((float|double)(\(\d*\))))$"
	abstractVM.push("55.3", Double);
	abstractVM.push("75", Double);
	abstractVM.push("0", Int8);
	try {
		abstractVM.div();
	}
	catch (std::exception &exception)
	{
		std::cout << "catch it!" << exception.what() << std::endl;
	}
	abstractVM.dump();

//	abstractVM.assert("55");
//abstractVM.add();

//	abstractVM.dump();
//	std::cout << "----" << std::endl;
//	abstractVM.sub();
//	abstractVM.dump();
//
//
//	std::cout << "----" << std::endl;


//	system("leaks avm");
	return 0;
}