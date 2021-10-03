#include "lfu_list.h"
#include <unordered_map>
#include <functional>

using namespace std;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>	
using unmap_it = typename unordered_map<int, list_it<T>> :: iterator;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
template <typename T>
class LFU
{
	long int cash_size;									//размер кэша
	hash<T> T_hash;									//это вроде для того чтобы получать хэш
	list_it<T> l_it;									//это тип для итератора листа
	unmap_it<T> m_it;									//это тип для итератора таблицы
	T delet_dat;										//это дата которую буду удалять из таблицы
	long int hit;
//---------------------------------------------------------------------	
	unordered_map<int, list_it<T>> table;							//это хэш таблица
	MyList <T> LIST;									//надо чтобы лист был
//---------------------------------------------------------------------
public:
//---------------------------------------------------------------------	
	LFU(long int get_size)									//создает обьект кэша
	{		
		cash_size = get_size;								//размер кэша
		hit = 0;									//кол-во попаданий
	}
//---------------------------------------------------------------------	
	bool PUSH(T data)									//добавляем штуки в кэш
	{
		if(table.find(T_hash(data)) == table.end() && table.size() != cash_size)	//если страницы нету и кэш не полон
		{
			l_it = LIST.push(data);						//добавить в лист
			table[T_hash(data)] = l_it;						//добавить в таблицу
			return 0;	
		}
		
		if(table.find(T_hash(data)) == table.end() && table.size() == cash_size)	//если страницы нет и кэш полон
		{
			delet_dat = LIST.pop();						//удалить из листа
			m_it = table.find(T_hash(delet_dat));					//получить итератор того что удаляем
			table.erase(m_it);							//удалить из таблицы
			l_it = LIST.push(data);						//добавляем в лист
			table[T_hash(data)] = l_it;  						//добавляем в таблицу
			return 0;
		}
		
		if(table.find(T_hash(data)) != table.end())					//если страница попадалась
		{
			LIST.replace(table.find(T_hash(data))->second);
			hit = hit + 1;
			return 0;
		}
		
		return 1;
	}
//---------------------------------------------------------------------	
	void PRINT(void)									//Оно должно печатать
	{
		printf("Your cash:\n");
		LIST.print();
	}
//---------------------------------------------------------------------	
	long int SIZE()
	{
		return cash_size;	
	}
//---------------------------------------------------------------------
	long int HITS(void)
	{
		return hit;
	}
};
