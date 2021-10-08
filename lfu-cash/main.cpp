#include "lfu_cash.h"

int main()
{
	long int size, i = 0, num;
	int x;

	std::cin >> size >> num;					//cash size//quantity of number you enter
	
	LFU<int> cash(size);
	
	while(i < num)
	{
		std::cin >> x;
		cash.PUSH(x);
		i++;
	}	
	
	std::cout << "hits:" << cash.HITS() << std::endl;
	
	//cash.PRINT();						//if you need to print it
}

