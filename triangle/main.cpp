#include "linal.h"
#include <vector>

struct tree_node
{
	double Mx, mx;
	double My, my;
	double Mz, mz;
	
	std::vector<Triangle<double>> trv;
	
	struct tree_node *v1 = nullptr;
	struct tree_node *v2 = nullptr;
	struct tree_node *v3 = nullptr;
	struct tree_node *v4 = nullptr;
	struct tree_node *v5 = nullptr;
	struct tree_node *v6 = nullptr;
	struct tree_node *v7 = nullptr;
	struct tree_node *v8 = nullptr;
	struct tree_node *rel = nullptr;
	
	bool in_cube(Triangle<double> tr)
	{
		if(tr.pt1.x <= Mx && tr.pt1.x >= mx && tr.pt1.z <= Mz && tr.pt1.z >= mz && tr.pt1.y <= My && tr.pt1.y >= my) 
			if(tr.pt2.x <= Mx && tr.pt2.x >= mx && tr.pt2.z <= Mz && tr.pt2.z >= mz && tr.pt2.y <= My && tr.pt2.y >= my) 
				if(tr.pt3.x <= Mx && tr.pt3.x >= mx && tr.pt3.z <= Mz && tr.pt3.z >= mz && tr.pt3.y <= My && tr.pt3.y >= my) 
					return true;
		
		return false;			
	}
	
	void create_level()
	{
		struct tree_node vec1;
		struct tree_node vec2;
		struct tree_node vec3;
		struct tree_node vec4;
		struct tree_node vec5;
		struct tree_node vec6;
		struct tree_node vec7;
		struct tree_node vec8;
		
		double nx = (Mx + mx)/2;
		double ny = (My + my)/2;
		double nz = (Mz + mz)/2;
		
		vec1.Mx = Mx; vec1.My = My; vec1.Mz = Mz;
		vec1.mx = nx; vec1.my = ny; vec1.mz = nz;
		
		vec2.Mx = Mx; vec2.My = ny; vec2.Mz = nz;
		vec2.mx = nx; vec2.my = my; vec2.mz = mz;
		
		vec3.Mx = nx; vec3.My = My; vec3.Mz = Mz;
		vec3.mx = mx; vec3.my = ny; vec3.mz = nz;
		
		vec4.Mx = nx; vec4.My = ny; vec4.Mz = nz;
		vec4.mx = mx; vec4.my = my; vec4.mz = mz;
		
		vec5.Mx = Mx; vec5.My = My; vec5.Mz = nz;
		vec5.mx = nx; vec5.my = ny; vec5.mz = mz;
		
		vec6.Mx = Mx; vec6.My = ny; vec6.Mz = Mz;
		vec6.mx = nx; vec6.my = my; vec6.mz = nz;
		
		vec7.Mx = nx; vec7.My = My; vec7.Mz = nz;
		vec7.mx = mx; vec7.my = ny; vec7.mz = mz;
		
		vec8.Mx = nx; vec8.My = ny; vec8.Mz = Mz;
		vec8.mx = mx; vec8.my = my; vec8.mz = nz;
		
		vec1.rel = this;
		vec2.rel = this;
		vec3.rel = this;
		vec4.rel = this;
		vec5.rel = this;
		vec6.rel = this;
		vec7.rel = this;
		vec8.rel = this;
		
		v1 = &vec1;
		v2 = &vec2;
		v3 = &vec3;
		v4 = &vec4;
		v5 = &vec5;
		v6 = &vec6;
		v7 = &vec7;
		v8 = &vec8;
	}
};

void make_tree(struct tree_node *head)
{
	head->create_level();
	size_t leng = head->trv.size();
	int i = 0;
	
	while(i < leng)
	{
		i++;
		Triangle<double> tr = head->trv.back();
		
		if(head->v1->in_cube(tr))
		{
			head->v1->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v2->in_cube(tr))
		{
			head->v2->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v3->in_cube(tr))
		{
			head->v3->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v4->in_cube(tr))
		{
			head->v4->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v5->in_cube(tr))
		{
			head->v5->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v6->in_cube(tr))
		{
			head->v6->trv.push_back(tr);
			head->trv.pop_back();	
			continue;		
		}
		
		if(head->v7->in_cube(tr))
		{
			head->v7->trv.push_back(tr);
			head->trv.pop_back();
			continue;			
		}
		
		if(head->v8->in_cube(tr))
		{
			head->v8->trv.push_back(tr);
			head->trv.pop_back();	
			continue;		
		}
		
		head->trv.insert(head->trv.begin(), tr);
		head->trv.pop_back();
	}
	
	if(leng == head->trv.size())
		return;
		
	if(!head->v1->trv.empty());
		make_tree(head->v1);
	if(!head->v2->trv.empty());
		make_tree(head->v2);
	if(!head->v3->trv.empty());
		make_tree(head->v3);	
	if(!head->v4->trv.empty());
		make_tree(head->v4);
	if(!head->v5->trv.empty());
		make_tree(head->v5);
	if(!head->v6->trv.empty());
		make_tree(head->v6);		
	if(!head->v7->trv.empty());
		make_tree(head->v7);
	if(!head->v8->trv.empty());
		make_tree(head->v8);
	return;	
}

void cross_tr(struct tree_node *head, std::vector<Triangle<double>> tr_cr, char* point)
{	
	if(!head->trv.empty())
	{
		for (auto it = head->trv.begin(); it++ != head->trv.end(); ) 
		{
   		     	for (auto jt = it++; jt != head->trv.end(); ) 
			{
				if((*it).crossTriangle(*jt))
				{
					point[it->number] = 1;
					point[jt->number] = 1;
				}
			
				jt++;
        	
    			}
    		
    			it++;        	
    		}
    		
    		if(!tr_cr.empty())
    		{
    			for (auto it = head->trv.begin(); it != head->trv.end();) 
			{
				for (auto jt = tr_cr.begin(); jt != tr_cr.end();) 
				{
		  			if((*it).crossTriangle(*jt))
					{
						point[it->number] = 1;
						point[jt->number] = 1;
					} 
					jt++;     	
    				}			
    				it++;	        	
    			}
    		}
    		
    		if(!head->trv.empty())
    		{
    			for (auto it = head->trv.begin(); it != head->trv.end();) 
    			{
    				tr_cr.push_back(*it);
    				it++;
    			}
    		}
    	}
    	
    	if(head->v1 != nullptr)
		cross_tr(head->v1, tr_cr, point);
	if(head->v2 != nullptr)
		cross_tr(head->v2, tr_cr, point);
	if(head->v3 != nullptr)
		cross_tr(head->v3, tr_cr, point);
	if(head->v4 != nullptr)
		cross_tr(head->v4, tr_cr, point);
	if(head->v5 != nullptr)
		cross_tr(head->v5, tr_cr, point);
	if(head->v6 != nullptr)
		cross_tr(head->v6, tr_cr, point);
	if(head->v7 != nullptr)
		cross_tr(head->v7, tr_cr, point);
	if(head->v8 != nullptr)
		cross_tr(head->v8, tr_cr, point);
	
	return; 
}

int main(void)
{
	double x = 0, y = 0, z = 0;
	double M = 0, m = 0;
	int num = 0, i = 0;
	struct tree_node head;	
	
	std::cin >> num;
	
	char* point;
	point = (char*)calloc(num, sizeof(char));
	
	std::cin >> x >> y >> z;
	
	m = x;
	M = x;
	
	while(i < num)
	{
				
		Point<double> p1{x, y, x};
		
		if(x < m)
			m = x;
		if(x > M)
			M = x;
			
		if(y < m)
			m = y;
		if(y > M)
			M = y;
			
		if(z < m)
			m = z;
		if(z > M)
			M = z;		
		
		std::cin >> x >> y >> z;
		Point<double> p2{x, y, z};
		
		if(x < m)
			m = x;
		if(x > M)
			M = x;
			
		if(y < m)
			m = y;
		if(y > M)
			M = y;
			
		if(z < m)
			m = z;
		if(z > M)
			M = z;	
			
		std::cin >> x >> y >> z;
		Point<double> p3{x, y, z};
		
		if(x < m)
			m = x;
		if(x > M)
			M = x;
			
		if(y < m)
			m = y;
		if(y > M)
			M = y;
			
		if(z < m)
			m = z;
		if(z > M)
			M = z;	
		
		Triangle<double> tr{p1, p2, p3, i};
			
		head.trv.push_back(tr);	
		
		std::cin >> x >> y >> z;
		i++;
	}
	
	head.Mx = M;
	head.mx = m;
	head.My = M;
	head.my = m;
	head.Mz = M;
	head.mz = m;
	
	std::vector<Triangle<double>> tr_cr;
	
	make_tree(&head);
	cross_tr(&head, tr_cr, point);
	
	free(point);		

	return 0;
}
