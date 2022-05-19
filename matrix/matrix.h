#include<iostream>

//--------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> void construct(T *p, const T &rhs)
{ 
	new (p) T(rhs); 
}

template <typename T> void construct(T *p, T &&rhs)
{
	new (p) T(std::move(rhs));
}

template <class T> void destroy(T *p) 
{ 
	p->~T();
}

template <typename FwdIter> void destroy(FwdIter first, FwdIter last)
{
	while (first != last)
	destroy(&*first++);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> struct MyVectorBuf 
{
protected:
	T *data;
	size_t v_size = 0;
	size_t used = 0;

protected:
	MyVectorBuf(const MyVectorBuf &) = delete;
	
	MyVectorBuf &operator=(const MyVectorBuf &) = delete;
	
	MyVectorBuf(MyVectorBuf &&rhs) noexcept: data(rhs.data), v_size(rhs.v_size), used(rhs.used)
	{
		rhs.data = nullptr;
		rhs.v_size = 0;
		rhs.used = 0;
	}

	MyVectorBuf &operator=(MyVectorBuf &&rhs) noexcept 
	{
		std::swap(data, rhs.data);
		std::swap(v_size, rhs.v_size);
		std::swap(used, rhs.used);
		return *this;
	}

	MyVectorBuf(size_t sz = 0) : data((sz == 0) ? nullptr : static_cast<T *>(::operator new(sizeof(T) * sz))), v_size(sz) {}

	~MyVectorBuf() 
	{
		destroy(data, data + used);
		::operator delete(data);
  	}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> struct MyVector : private MyVectorBuf<T> 
{
	using MyVectorBuf<T>::used;
	using MyVectorBuf<T>::v_size;
	using MyVectorBuf<T>::data;

	explicit MyVector(size_t sz = 0) : MyVectorBuf<T>(sz) {}

	MyVector(MyVector &&rhs) = default;
	MyVector &operator=(MyVector &&rhs) = default;

	MyVector(const MyVector &rhs) : MyVectorBuf<T>(rhs.used) 
	{
		while (used < rhs.used) 
		{
			construct(data + used, rhs.data[used]);
			used += 1;
		}
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--op-=---------------------------------------------------------------------------------------------------------------------------------------------------
	MyVector &operator=(const MyVector &rhs) 
	{
		MyVector tmp(rhs);
		std::swap(*this, tmp);
		return *this;
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--top----------------------------------------------------------------------------------------------------------------------------------------------------
	T top() const 
	{
		if (used < 1)
		throw std::runtime_error("Vector is empty");
		return data[used - 1];
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--pop----------------------------------------------------------------------------------------------------------------------------------------------------
	void pop() 
	{
		if (used < 1)
		throw std::runtime_error("Vector is empty");
		used -= 1;
		destroy(data + used);
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--push &-------------------------------------------------------------------------------------------------------------------------------------------------
	void push(const T &t) 
	{
		T t2(t);
		push(std::move(t2));
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--push &&------------------------------------------------------------------------------------------------------------------------------------------------
	void push(T &&t) 
	{

		if (used == v_size) 
		{
			MyVector tmp(v_size * 2 + 1);
			
			while (tmp.used < used)
				tmp.push(std::move(data[tmp.used]));
				
			tmp.push(std::move(t));
			std::swap(*this, tmp);
		}
		 
		else 
		{
			construct(data + used, std::move(t));
			used += 1;
		}
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--get-size-----------------------------------------------------------------------------------------------------------------------------------------------
	size_t size() const 
	{ 
		return used; 
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--get-not empty-size-------------------------------------------------------------------------------------------------------------------------------------	
	size_t capacity() const 
	{ 
		return size; 
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--op-[]--------------------------------------------------------------------------------------------------------------------------------------------------	
	T& operator[](size_t x)
	{ 
		if (x < 0 || used <= x) throw std::out_of_range{"MyVector::operator[]"};
		
		return *(data + x);  
	}
	
	const T& operator[](size_t x) const
	{ 
		if (x < 0 || size <= x) throw std::out_of_range{"MyVector::operator[]"};
			
		return *(data + x); 
	}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
class Matrix 
{
	size_t m_size = 0;
	MyVector<T> m_data;
//--------------------------------------------------------------------------------------------------------------------------------------------------------	
//--constructors------------------------------------------------------------------------------------------------------------------------------------------
public:	
	Matrix(size_t size) : m_size(size), m_data(MyVector<T>{size * size}){}						//matrix with zero
	
	Matrix(size_t size, T* data) : m_size(size), m_data(MyVector<T>{size * size})					//matrix with numbers
	{
		size_t i = 0;
		
		while(i < size * size)
		{
			i++;
			m_data.push(data[i]);			
		}
	}
	
	Matrix(size_t size, MyVector<T> data) : m_size(size), m_data(data){}						
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--get-size-----------------------------------------------------------------------------------------------------------------------------------------------
	size_t get_size() const noexcept
	{
		return m_size;
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--print-function-----------------------------------------------------------------------------------------------------------------------------------------	
	void print() const
	{
		for(size_t i = 0; i < m_size * m_size; i++)
		{
			std::cout<<m_data[i]<<' ';
			
			if((i + 1) % m_size == 0)
				std::cout<<std::endl;
		}
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------	
//--Pointer-for-[][]--------------------------------------------------------------------------------------------------------------------------------------
private:	
	class Pointer
	{
		int str ;
		MyVector<T> &data;
		int size;

	public:	
		Pointer(int str_plc, MyVector<T> &dat, int s) : str(str_plc), data(dat), size(s){}
		
		T& operator[](int y) 
		{ 
			if (y < 0 || size <= y) throw std::out_of_range{"Matrix::operator[][]"};
			
			return data[str + y]; 
		}
		
		const T& operator[](int y) const
		{ 
			if (y < 0 || size <= y) throw std::out_of_range{"Matrix::operator[][]"};
			
			return data[str + y]; 
		}
	};

public:	
	Pointer operator[](int x) 
	{ 
		if (x < 0 || m_size <= x) throw std::out_of_range{"Matrix::operator[][]"};
		
		Pointer it{x * (int)m_size, m_data, (int)m_size};
		return it;  
	}
	
	const Pointer operator[](int x) const 
	{ 
		if (x < 0 || m_size <= x) throw std::out_of_range{"Matrix::operator[][]"};
		
		const Pointer it{x * (int)m_size, const_cast<MyVector<T>&>(m_data), (int)m_size};
		return it; 
	}	
//-------------------------------------------------------------------------------------------------------------------------------------------------------	
//--transpon---------------------------------------------------------------------------------------------------------------------------------------------
	Matrix transpon() const
	{
		Matrix<T> tran{m_size * m_size};
		
		for(size_t i = 0; i < m_size; i++)
			for(size_t j = 0; j < m_size; j++)
				tran.m_data[i * m_size + j]= (*this)[j][i];
				
		Matrix res{m_size, tran.m_data};
		
		return res;						//move-op= 
	}	
//-------------------------------------------------------------------------------------------------------------------------------------------------------	
//--deter------------------------------------------------------------------------------------------------------------------------------------------------
	double deter() const
	{
		Matrix<double> help = *this;
		double k;
		
		double res = (double)help[0][0];
		
		for(size_t i = 1; i < m_size; i++)
		{		
			//std::cout << help[2][2] << std::endl;	
			for(size_t r = 0; r < i; r++)
			{
				if(help[r][r] == 0)
				{	
					size_t l = 0;
				
					while(help[l][r] == 0)
					{
						l++;
						if(l == m_size)
							return 0;
					}
				
					for(size_t j = 0; j < m_size; j++)
						help[r][j] = help[r][j] + help[l][j];								
				}

				k = help[i][r] / help[r][r];  
				
				for(size_t j = r; j < m_size; j++)
					help[i][j] = help[i][j] - k * help[r][j];
			}
			
			res = res * help[i][i];
			
			//std::cout << help[i][i] << std::endl;
		}			
		
		//help.print();	
		
		return res;	
	}

};


