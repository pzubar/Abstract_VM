#include <iostream>
#include "AbstractVM.hpp"
#include "Operand.hpp"
#include "Factory.hpp"
#include <vector>

template <class Type>
class Array
{
  public:
	Array(size_t size)
		: data_(new Type[size]),
		  size_(size) {}

	~Array()
	{
		delete[] data_;
	}

	size_t size() const
	{
		return size_;
	}

	Type operator[](size_t i) const
	{
		return data_[i];
	}

	Type &operator[](size_t i)
	{
		return data_[i];
	}
	void sayHello()
	{
		std::cout << "Hello, world!" << std::endl;
	}

  private:
	Type *data_;
	size_t size_;
};

int main(void)
{

	AbstractVM abstractVM = AbstractVM();

	abstractVM.push("55.3", Double);
	abstractVM.push("75", Double);
	abstractVM.push("93", Int8);
	abstractVM.print();
	abstractVM.assert("55");


	abstractVM.dump();
	std::cout << "----" << std::endl;
	abstractVM.sub();
	abstractVM.dump();


	std::cout << "----" << std::endl;


	system("leaks avm");
	return 0;
}