#include <iostream>
#include <stdlib.h>
#include "dynamic_array.h"

int main()
{
	dynamic_array<int> d_array;
	d_array.push(1);
	d_array.push(2);
	d_array.push(3);
	d_array.push(4);
	d_array.push(5);

	for (int i = 0; i < d_array.size(); i++)
	{
		std::cout << d_array[i] << std::endl;
	}

	std::cout << std::endl;

	d_array.removeAt(0);

	std::cout << std::endl;

	for (auto& i : d_array)
	{
		std::cout << i << std::endl;
	}
	std::cin.get();

	return 0;
}