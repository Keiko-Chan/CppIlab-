#include "linal.h"
#include <vector>

int main(void)
{
	double x = 0, y = 0, z = 0;
	int num = 0, i = 0;
	std::vector<Triangle> trv;
	
	std::cin >> num;
	
	//TestCrossTriangle();
	
	char* point;
	point = (char*)calloc(num, sizeof(char));
	
	std::cin >> x >> y >> z;
	
	while(i < num)
	{
				
		Point p1{x, y, z};

		std::cin >> x >> y >> z;
		Point p2{x, y, z};
			
		std::cin >> x >> y >> z;
		Point p3{x, y, z};

		Triangle tr{p1, p2, p3, i};
			
		trv.push_back(tr);	
		
		std::cin >> x >> y >> z;
		i++;
	}
	
	for (auto it = trv.begin(); (it + 1) != trv.end(); ) 
	{
	     	for (auto jt = (it + 1); jt != trv.end(); ) 
		{
			if((*it).crossTriangle(*jt))
			{
				point[it->number] = 1;
				point[jt->number] = 1;
				
				std::cout<<it->number <<' '<< jt->number <<std::endl;
			}
		
			jt++;
	
		}
	
		it++;        	 
	}
	
	for(i = 0; i <= num; i++)
	{
		if(point[i] == 1)
		std::cout << i << std::endl;
	}
	
	free(point);		

	return 0;
}
