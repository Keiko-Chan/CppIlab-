#include "matrix.h"

int main(void)
{
	double *dat;
	size_t size = 0;
	
	std::cin >> size;
	dat = new double [size * size];
	
	for(int i = 0; i < size * size; i++)
		std::cin >> dat[i];
		
	Matrix<double> m{size, dat};
	double res;
		 
	res = m.deter();
	
	std::cout << res << std::endl; 
	
	return 0;
}
