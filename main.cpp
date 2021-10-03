#include "lfu_cash.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	long int size, i = 0, num;
	int x;

	cin >> size >> num;
	
	LFU<int> cash(size);
	
	while(i < num)
	{
		cin >> x;
		cash.PUSH(x);
		i++;
	}	
	
	cout << "hits:" << cash.HITS() << endl;
}

