#include "Core.h"

#include <iostream>

namespace Core {
	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
		std::cin.get();
	}

	int AddInts(int a, int b) {
		return a + b;
	}
}