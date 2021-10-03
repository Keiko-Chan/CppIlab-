#include <iostream>
#include <assert.h>
#include <list>    
#include <iterator> 

using namespace std;
//---------------------------------------------------------------------
template <typename T>	
struct list_node;
//---------------------------------------------------------------------
template <typename T>	
struct lfu_node;
//---------------------------------------------------------------------
template <typename T>	
using list_it = typename list <struct lfu_node<T>> :: iterator;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
struct lfu_node
{
	T DATA;
	struct list_node<T>* where;
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
struct list_node							
{
	list<struct lfu_node<T>> List;
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
	struct list_node<T>*	head;
	struct list_node<T>* 	cur_l;
	struct lfu_node<T> 	node;
	list_it<T> it;
	T d_pop;
//---------------------------------------------------------------------	
	struct list_node<T>* CreateNode(int freq, struct list_node<T>* Prev)
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
	void DeletListNode (struct list_node<T> * del)
	{
		if(del->prev != NULL )
			del->prev->next = del->next;
		if(del->next != NULL)
			del->next->prev = del->prev;
		delete del;													//надеюсь лист удалится вместе со всей структурой в которой он содержится
	}
//---------------------------------------------------------------------	
public:
//---------------------------------------------------------------------
	MyList()
	{
		//head = (struct list_node<T>*)calloc (1, sizeof(struct list_node<T>));
		head = new struct list_node<T>;
		head->next = NULL;
		head->prev = NULL;		
	}

	list_it<T> push(T data)
	{
		node.DATA = data;
	
		if(head->next != NULL && head->next->frequency == 1)
		{
			node.where = head->next;
			head->next->List.push_back(node);
			it = --(head->next->List.end());
		}
		
		else
		{
			cur_l = CreateNode(1, head);
			node.where = head->next;
			cur_l->List.push_back(node);
			it = --(cur_l->List.end());
		}
		return it;
	}
//---------------------------------------------------------------------		
	~MyList()
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
	T pop()
	{
		assert(head->next != NULL);	
		d_pop = (head->next->List.begin())->DATA;	
		head->next->List.pop_front();
		
		return d_pop;
	}
//---------------------------------------------------------------------	
	bool replace(list_it<T> terator)
	{
		if(terator->where->next != NULL && terator->where->next->frequency == (terator->where->frequency + 1))	//проверяю начиличие следующей ноды частоты +1
		{
			cur_l =  terator->where;										//указатель на текущую частоту 
			terator->where = cur_l->next;										//перетираем в сруктуре листа указатель на другую частоту
			(cur_l->next->List).splice( (cur_l->next->List).end(), (cur_l->List), terator );			//перемещаю штуку листа в другой лист частоты +1
		}
		
		else
		{
			cur_l = CreateNode((terator->where->frequency + 1), terator->where);					//создаю нужную частоту
			cur_l = cur_l->prev;											//указатель на текущую частоту
			terator->where = cur_l->next;										//переделывем указатель в структуре
			(cur_l->next->List).splice( (cur_l->next->List).end(), (cur_l->List), terator );			//перемещаю штуку
		}
		
		if((cur_l->List).empty())											//нужно удалить если структура с пустым листом
		{
			DeletListNode(cur_l);
		}
		
		return 0;
	}
//---------------------------------------------------------------------
	bool print()
	{
		if(head == NULL || head->next == NULL)
		{
			printf("list is empty\n");		
			return 0;
		}
		
		cur_l = head;
		list_it<T> pos;
		
		while(cur_l->next != NULL)
		{
			cur_l = cur_l->next;
			
			 for (pos = (cur_l->List).begin(); pos != (cur_l->List).end(); ++pos)
    				cout << pos->DATA << " ";
    				
    			printf("\n");
		}
		
		return 0;
	}
//---------------------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
 

