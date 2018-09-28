#include <iostream>
#include "AbstractVM.hpp"
#include "Operand.hpp"
#include "Factory.hpp"
#include <vector>
#include <algorithm>
#include <iterator>



void printscreen(std::string string)
{
	std::cout << string << "\n";
}

int main(void)
{
//	std::string line;
//	while (std::getline(std::cin, line))
//	{
//		std::cout << line << std::endl;
//
//	}
	AbstractVM abstractVM = AbstractVM();
	std::string str;


	while (getline(std::cin, str)) {
//		std::cout << str << std::endl;
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


//	AbstractVM abstractVM = AbstractVM();
//
////	abstractVM.excecute("push", "int8", "100");
////	std::string str = "push int8(100)";
//	try {
//		abstractVM.setExpression("push int8(100)");
//	}
//	catch (std::exception &exception)
//	{
//		std::cout << "Error occured:!" << exception.what() << std::endl;
//	}
//	abstractVM.setExpression("push int8(200)");

//	if (str.find(";;") == std::string::npos) {
//		str = str.substr(0, str.find(";"));
//	}
//
//	std::cout << "New string:" << str << "\n";
//	std::regex reg("(\\s*)?(((push|assert)(\\s+)((int((8|16|32)\\([-]?\\d+\\)))|"
//				 "((float|double)(\\([-]?\\d*[.]*?\\d+\\)))))|(pop|dump|add|sub|mul|div|mod|print|exit|;;))(\\s*)?$");
//	std::smatch mathes;
//

//	std::cout << "Match? " << std::regex_match(str.begin(), str.end(), reg)  << "\n";





//	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
//	std::sregex_iterator lastMatch;
//	while (currentMatch != lastMatch)
//	{
//		std::smatch match = *currentMatch;
//		std::cout << match.str() << "\n";
//		currentMatch++;
//	}
//	std::cout << std::endl;



//	std::vector<std::string> result(3);
//
//
//
//	std::regex ws_re("\\s|\\(|\\)");
//	std::copy( std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1),
//			   std::sregex_token_iterator(),
//			   result.begin());
//
//	for (auto i : result)
//	{
//		std::cout << i << std::endl;
//	}
//	std::cout << result.size();


	//if result.size == 3
	//AVM parser(res[0]..[2])
//	else
//		AVM parser(res[0])

//
//abstractVM.push("55.3", Double);
//	abstractVM.push("75", Double);
//	abstractVM.push("0", Int8);
//
//	try {
//		abstractVM.div();
//	}
//	catch (std::exception &exception)
//	{
//		std::cout << "catch it!" << exception.what() << std::endl;
//	}
//	abstractVM.dump();

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