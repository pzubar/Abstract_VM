#include <iostream>
#include "AbstractVM.hpp"
#include "Operand.hpp"
#include <vector>

template <class Type>
class Array {
    public:
        Array( size_t size )
                :	data_ ( new Type [ size ]),
                    size_ ( size ) {}

        ~Array () {
            delete [] data_ ;
        }

        size_t size() const {
            return size_ ;
        }

        Type operator []( size_t i) const {
            return data_[i];
        }

        Type & operator []( size_t i) {
            return data_[i];
        }
    private :
        Type * data_ ;
        size_t size_ ;
};

int main(void)
{


    for (int i = 0; i < 5 ; ++i) {
        std::cout << "THIS->" << eOperandType(i) << std::endl;
    }

    std::cout << "_____________****______________" << "\n";


    AbstractVM duren;
	duren.sayHello();


	std::cout << "_________" << "\n";

	// Создание вектора, содержащего целые числа
	std::vector<int> v = {7, 5, 16, 8};

	// Добавление ещё двух целых чисел в вектор
	v.push_back(25);
	v.push_back(13);

	// Проход по вектору с выводом значений
	for ( int n : v ) {
		std::cout << n << '\n';
	}

	std::cout << "_________" << "\n";

	Array <int > ai (10);
	ai[0] = 5;
	std::cout << ai[0] << "\n";
	std::cout << "size: " << ai.size() << "\n";
	Array <float > af (20);
	af[0] = 66.3423;
	std::cout << af[0];
	return 0;
}