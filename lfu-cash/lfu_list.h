#include <iostream>
#include <assert.h>
#include <list>    
#include <iterator> 

//---------------------------------------------------------------------
template <typename T>	
struct list_node;
//---------------------------------------------------------------------
template <typename T>	
struct lfu_node;
//---------------------------------------------------------------------
template <typename T>	
using list_it = typename std::list <struct lfu_node<T>> :: iterator;							
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
struct lfu_node														//node of cpp list
{
	T DATA;
	struct list_node<T>* where;												//pointer on list_node where we list is situated
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
struct list_node														//list_node wich contains cpp list and some things for simple list 
{
	std::list<struct lfu_node<T>> List;
	int frequency;
	list_node* next;
	list_node* prev;		
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>
class MyList
{
//---------------------------------------------------------------------			
	struct list_node<T>*	head;												//head of list_node
	struct list_node<T>* 	cur_l;												//just pointer I use in some functions
	struct lfu_node<T> 	node;												//node for pushing
	list_it<T> it;
	T d_pop;
//---------------------------------------------------------------------	
	struct list_node<T>* CreateNode(int freq, struct list_node<T>* Prev)							//create list_node
	{
		struct list_node<T>* res;
		res = new struct list_node<T>;
		res->prev = Prev;
		
		if(Prev->next != NULL)
		{
			res->next = Prev->next;
			Prev->next->prev = res;
		}
		else
			res->next = NULL;
		
		Prev->next = res;
		res->frequency = freq;
		
		return res;
	}
//---------------------------------------------------------------------	
	void DeletListNode (struct list_node<T> * del)									//deleter for list_node
	{
		if(del->prev != NULL )
			del->prev->next = del->next;
		if(del->next != NULL)
			del->next->prev = del->prev;
		delete del;											
	}
//---------------------------------------------------------------------	
public:
//---------------------------------------------------------------------
	MyList()														//mylist constructor
	{
		head = new struct list_node<T>;										//create head for list_node list
		head->next = NULL;
		head->prev = NULL;		
	}
//---------------------------------------------------------------------
	list_it<T> push(T data)												//push element in mylist
	{
		node.DATA = data;
	
		if(head->next != NULL && head->next->frequency == 1)								//list_node frequrency 1 is exist
		{
			node.where = head->next;
			head->next->List.push_back(node);
			it = --(head->next->List.end());
		}
		
		else														//list_node frequrency 1 isn`t exist
		{
			cur_l = CreateNode(1, head);
			node.where = head->next;
			cur_l->List.push_back(node);
			it = --(cur_l->List.end());
		}
		return it;
	}
//---------------------------------------------------------------------		
	~MyList()														//mylist distructor
	{
		cur_l = head;	
		while(cur_l != NULL && cur_l->next != NULL)
		{
			cur_l = cur_l->next;
			DeletListNode(cur_l->prev);
		}
		
		DeletListNode(cur_l);
	}
//---------------------------------------------------------------------	
	T pop()														//delete earlier element from mylist
	{
		assert(head->next != NULL);	
		d_pop = (head->next->List.begin())->DATA;	
		head->next->List.pop_front();
		
		return d_pop;
	}
//---------------------------------------------------------------------	
	bool replace(list_it<T> terator)
	{
		if(terator->where->next != NULL && terator->where->next->frequency == (terator->where->frequency + 1))	//check that node with frequrency +1 is exist
		{
			cur_l =  terator->where;										//pointer on the next frequrency
			terator->where = cur_l->next;										//change pointer on the list_node
			(cur_l->next->List).splice( (cur_l->next->List).end(), (cur_l->List), terator );			//replace lfu_node in next list
		}
		
		else
		{
			cur_l = CreateNode((terator->where->frequency + 1), terator->where);					//create needed frequrency
			cur_l = cur_l->prev;											//pointer on that frequrency
			terator->where = cur_l->next;										//change pointer on the list_node
			cur_l->next->List.splice( cur_l->next->List.end(), cur_l->List, terator );			//replace lfu_node in next list
		}
		
		if(cur_l->List.empty())											//delete empty list_node
		{
			DeletListNode(cur_l);
		}
		
		return 0;
	}
//---------------------------------------------------------------------
	bool print()														//print list
	{
		if(head == NULL || head->next == NULL)
		{
			std::cout << "list is empty\n";		
			return 0;
		}
		
		cur_l = head;
		list_it<T> pos;
		
		while(cur_l->next != NULL)
		{
			cur_l = cur_l->next;
			
			 for (pos = (cur_l->List).begin(); pos != (cur_l->List).end(); ++pos)
    				std::cout << pos->DATA << " ";
    				
    			std::cout<<"\n";
		}
		
		return 0;
	}
//---------------------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
 

