#include "linal.h"
#include <vector>

struct tree_node
{
	double Mx, mx;
	double My, my;
	double Mz, mz;
	
	std::vector<Triangle> trv;
	
	struct tree_node *v1 = nullptr;
	struct tree_node *v2 = nullptr;
	struct tree_node *v3 = nullptr;
	struct tree_node *v4 = nullptr;
	struct tree_node *v5 = nullptr;
	struct tree_node *v6 = nullptr;
	struct tree_node *v7 = nullptr;
	struct tree_node *v8 = nullptr;
	struct tree_node *rel = nullptr;
	
	bool in_cube(Triangle tr)
	{
		if(tr.pt1.x <= Mx && tr.pt1.x >= mx && tr.pt1.z <= Mz && tr.pt1.z >= mz && tr.pt1.y <= My && tr.pt1.y >= my) 
			if(tr.pt2.x <= Mx && tr.pt2.x >= mx && tr.pt2.z <= Mz && tr.pt2.z >= mz && tr.pt2.y <= My && tr.pt2.y >= my) 
				if(tr.pt3.x <= Mx && tr.pt3.x >= mx && tr.pt3.z <= Mz && tr.pt3.z >= mz && tr.pt3.y <= My && tr.pt3.y >= my) 
					return true;
		
		return false;			
	}
	
	void create_level()
	{
		v1 = new struct tree_node;
		v2 = new struct tree_node;
		v3 = new struct tree_node;
		v4 = new struct tree_node;
		v5 = new struct tree_node;
		v6 = new struct tree_node;
		v7 = new struct tree_node;
		v8 = new struct tree_node;
		
		double nx = (Mx + mx)/2;
		double ny = (My + my)/2;
		double nz = (Mz + mz)/2;
		
		v1->Mx = Mx; v1->My = My; v1->Mz = Mz;
		v1->mx = nx; v1->my = ny; v1->mz = nz;
		
		v2->Mx = Mx; v2->My = ny; v2->Mz = nz;
		v2->mx = nx; v2->my = my; v2->mz = mz;
		
		v3->Mx = nx; v3->My = My; v3->Mz = Mz;
		v3->mx = mx; v3->my = ny; v3->mz = nz;
		
		v4->Mx = nx; v4->My = ny; v4->Mz = nz;
		v4->mx = mx; v4->my = my; v4->mz = mz;
		
		v5->Mx = Mx; v5->My = My; v5->Mz = nz;
		v5->mx = nx; v5->my = ny; v5->mz = mz;
		
		v6->Mx = Mx; v6->My = ny; v6->Mz = Mz;
		v6->mx = nx; v6->my = my; v6->mz = nz;
		
		v7->Mx = nx; v7->My = My; v7->Mz = nz;
		v7->mx = mx; v7->my = ny; v7->mz = mz;
		
		v8->Mx = nx; v8->My = ny; v8->Mz = Mz;
		v8->mx = mx; v8->my = my; v8->mz = nz;
		
		v1->rel = this;
		v2->rel = this;
		v3->rel = this;
		v4->rel = this;
		v5->rel = this;
		v6->rel = this;
		v7->rel = this;
		v8->rel = this;		
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
		Triangle tr = head->trv.back();
		
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
		
	if(!(head->v1->trv.empty() || head->v1->trv.size() < 3))
		make_tree(head->v1);
	if(!(head->v2->trv.empty() || head->v2->trv.size() < 3))
		make_tree(head->v2);
	if(!(head->v3->trv.empty() || head->v3->trv.size() < 3))
		make_tree(head->v3);	
	if(!(head->v4->trv.empty() || head->v4->trv.size() < 3))
		make_tree(head->v4);
	if(!(head->v5->trv.empty() || head->v5->trv.size() < 3))
		make_tree(head->v5);
	if(!(head->v6->trv.empty() || head->v6->trv.size() < 3))
		make_tree(head->v6);		
	if(!(head->v7->trv.empty() || head->v7->trv.size() < 3))
		make_tree(head->v7);
	if(!(head->v8->trv.empty() || head->v8->trv.size() < 3))
		make_tree(head->v8);
	return;	
}

void cross_tr(struct tree_node *head, std::vector<Triangle> tr_cr, char* point)
{	
	if(!head->trv.empty())
	{
		for (auto it = head->trv.begin(); (it + 1) != head->trv.end(); ) 
		{
   		     	for (auto jt = (it + 1); jt != head->trv.end(); ) 
			{
				if((*it).crossTriangle(*jt) && !(point[it->number] && point[jt->number]))
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
    	
    	if(head->v1 != nullptr && (head->v1->v1 != nullptr || !head->v1->trv.empty()))
		cross_tr(head->v1, tr_cr, point);
	if(head->v2 != nullptr && (head->v2->v1 != nullptr || !head->v2->trv.empty()))
		cross_tr(head->v2, tr_cr, point);
	if(head->v1 != nullptr && (head->v3->v1 != nullptr || !head->v3->trv.empty()))
		cross_tr(head->v3, tr_cr, point);
	if(head->v1 != nullptr && (head->v4->v1 != nullptr || !head->v4->trv.empty()))
		cross_tr(head->v4, tr_cr, point);
	if(head->v1 != nullptr && (head->v5->v1 != nullptr || !head->v5->trv.empty()))
		cross_tr(head->v5, tr_cr, point);
	if(head->v1 != nullptr && (head->v6->v1 != nullptr || !head->v6->trv.empty()))
		cross_tr(head->v6, tr_cr, point);
	if(head->v1 != nullptr && (head->v7->v1 != nullptr || !head->v7->trv.empty()))
		cross_tr(head->v7, tr_cr, point);
	if(head->v1 != nullptr && (head->v8->v1 != nullptr || !head->v8->trv.empty()))
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
				
		Point p1{x, y, z};
		
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
		Point p2{x, y, z};
		
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
		Point p3{x, y, z};
		
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
		
		Triangle tr{p1, p2, p3, i};
			
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
	
	std::vector<Triangle> tr_cr{};
	
	make_tree(&head);
	cross_tr(&head, tr_cr, point);
	
	for(i = 0; i <= num; i++)
	{
		if(point[i] == 1)
		std::cout << i + 1 << std::endl;
	}
	
	free(point);		

	return 0;
}
