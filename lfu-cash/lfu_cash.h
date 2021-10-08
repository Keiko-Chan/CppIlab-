#include "lfu_list.h"
#include <unordered_map>
#include <functional>

//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
using unmap_it = typename std::unordered_map<int, list_it<T>> :: iterator;			//type unodered-map iterator
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>
class LFU
{
	long int cash_size;									//cash size
	std::hash<T> T_hash;									//hash func
	list_it<T> l_it;									//iterator for list
	unmap_it<T> m_it;									//iterator for unodered map
	T delet_dat;										//data is needed to delete in push if cash is full
	long int hit;
//---------------------------------------------------------------------	
	std::unordered_map<int, list_it<T>> table;						//hash table
	MyList <T> LIST;									//my list
//---------------------------------------------------------------------
public:
//---------------------------------------------------------------------	
	LFU(long int get_size)									//create cash object
	{		
		cash_size = get_size;								//get cash size
		hit = 0;									//number if hits
	}
//---------------------------------------------------------------------	
	bool PUSH(T data)									//push things in cash
	{
		if(table.find(T_hash(data)) == table.end() && table.size() != cash_size)	//if it`s a new page and cash isn`t full
		{
			l_it = LIST.push(data);						//push to mylist
			table[T_hash(data)] = l_it;						//push to hash table
			return 0;	
		}
		
		if(table.find(T_hash(data)) == table.end() && table.size() == cash_size)	//if it`s new page and cash is full
		{
			delet_dat = LIST.pop();						//delete from my list
			m_it = table.find(T_hash(delet_dat));					//get hash-table-iterator of element i need to delete 
			table.erase(m_it);							//delete from hash table
			l_it = LIST.push(data);						//push to list
			table[T_hash(data)] = l_it;  						//push to hash table
			return 0;
		}
		
		if(table.find(T_hash(data)) != table.end())					//if page isn`t new
		{
			LIST.replace(table.find(T_hash(data))->second);			//replace page in list
			hit = hit + 1;								//hits + 1
			return 0;
		}
		
		return 1;
	}
//---------------------------------------------------------------------	
	void PRINT()									//print function
	{
		std::cout << "Your cash:\n";
		LIST.print();
	}
//---------------------------------------------------------------------	
	long int SIZE()									//returns cash size if you forgot
	{
		return cash_size;	
	}
//---------------------------------------------------------------------
	long int HITS()									//returns number of hits
	{
		return hit;
	}
};
