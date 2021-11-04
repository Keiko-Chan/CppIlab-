#include <iostream>
#include <math.h>
#include <assert.h>
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>	
struct Point
{
	T x = 0;
	T y = 0;
	T z = 0;
	int invalid = 0;
	
	Point(T x1, T y1, T z1) : x(x1), y(y1), z(z1) {}
	Point() : invalid(0){} 
	Point(int a) : invalid(a){} 
	
	void print() const
	{
		if(invalid == 1)
			std::cout<<"invalid point";
			
		else
			std::cout<<"point: ";
			std::cout<<x<<' '<<y<<' '<<z<<'\n';
	}
	
	bool same(const struct Point<T> point) const
	{
		if(x == point.x && y == point.y && z == point.z && invalid == point.invalid)
			return true;
		else
			return false;
		
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>
static struct Point<T> invalid_point{1};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>
struct Vector
{
	T ax = 0;
	T ay = 0;
	T az = 0;
	
	Vector(T x1, T y1, T z1)
	{
		ax = x1;
		ay = y1;
		az = z1;
	}
	
	Vector(struct Point<T> p1, struct Point<T> p2)
	{
		ax = p2.x - p1.x;
		ay = p2.y - p1.y;
		az = p2.z - p1.z;
	}
	
	Vector(){}
	
	T leng()
	{
		return sqrt(ay*ay + ax*ax + az*az);
	}
	
	struct Vector<T> norvec() const
	{
		struct Vector<T> v{ax, ay, az};
		
		if(ax == 0 && ay == 0 && az == 0)
			std::cout<<"Error invalid vector"<<'\n';
		
		T lenge = v.leng();
		
		v.ax = v.ax / lenge;
		v.ay = v.ay / lenge;
		v.az = v.az / lenge;
		
		return v;
	}
	
	bool same(const struct Vector<T> vect) const	
	{
		assert(!vect.invalid() && "invalid vector in samevect(i)");
		assert(!this->invalid() && "invalid vector in i.samevect");
	
		struct Vector<T> v1;		
		v1 = vect.norvec();
		
		struct Vector<T> v2;		
		v2 = this->norvec();
		
		if((v2.ax == v1.ax || v2.ax == -v1.ax) && (v2.ay == v1.ay || v2.ay == -v1.ay) && (v2.az == v1.az || v2.az == -v1.az ))
			return true;
			
		return false;
		
	}
	
	void print() const
	{
		std::cout<<"vector: ";
		std::cout<<ax<<' '<<ay<<' '<<az<<'\n';
	}	
	
	struct Vector<T> vectmul(const struct Vector<T> v)
	{
		struct Vector<T> res{};
		
		//v.print();
		//this->print();
		
		res.ax = ay * v.az - az * v.ay;
		res.ay = v.ax * az - ax * v.az;
		res.az = ax * v.ay - ay * v.ax;
		
		return res;		 
	}
	
	bool invalid() const
	{
		if(ax == 0 && ay == 0 && az == 0)
			return true;
		return false;	
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>
struct Line
{
	struct Point<T> lp;
	struct Vector<T> v;
	int invalid = 0;
//-------------------------------------------------------------------------------------------	
	Line(struct Point<T> p1, struct Vector<T> v1)
	{
		if(!(v1.invalid())) invalid = 1;
		lp = p1;
		v = v1;
	}
	
	Line(struct Point<T> p1, struct Point<T> p2) : lp(p1), v{p1, p2} {if(!(p1.same(p2))) invalid = 1;}
//-------------------------------------------------------------------------------------------	
	bool onLine(const struct Point<T> p1) const
	{
		if(p1.same(lp))
			return true;
	
		struct Vector<T> v1(p1, lp);		
		v1 = v1.norvec();
		
		struct Vector<T> v2;
		
		v2 = v.norvec();
		
		if((v2.ax == v1.ax && v2.ay == v1.ay && v2.az == v1.az) || (v2.ax == -v1.ax && v2.ay == -v1.ay && v2.az == -v1.az))
			return true;			
			
		else 
			return false;
	} 
//-------------------------------------------------------------------------------------------	
	bool same(const struct Line<T> line) const
	{
		if(!(line.v).same(v))
			return false;
		
		struct Line<T> newline{line.lp, lp};
		
		if(!newline.v.same(v))
			return false;
		
		return true;
	}
//-------------------------------------------------------------------------------------------	
	struct Point<T> cross(const struct Line<T> line) const
	{
		if(this->same(line))
			return invalid_point<T>;
			
		if(v.same(line.v))
			return invalid_point<T>;
			
		T k;
		T m;
		
		if((v.ay * line.v.ax - v.ax * line.v.ay) != 0)
		{
		
			m = (v.ax * (line.lp.y - lp.y) + v.ay * (lp.x - line.lp.x)) / (v.ay * line.v.ax - line.v.ay * v.ax);
			
			if(v.ax != 0)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
		
			if(v.az != 0)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(v.ax != 0)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(v.ay != 0)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
		
			struct Point<T> res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		if((v.az * line.v.ax - v.ax * line.v.az) != 0)
		{
		
			m = (v.ax * (line.lp.z - lp.z) + v.az * (lp.x - line.lp.x)) / (v.az * line.v.ax - line.v.az * v.ax);
			
			if(v.ax != 0)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
		
			if(v.az != 0)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(v.ax != 0)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(v.ay != 0)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
		
			struct Point<T> res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		if((v.ay * line.v.az - v.az * line.v.ay) != 0)
		{
		
			m = (v.az * (line.lp.y - lp.y) + v.ay * (lp.z - line.lp.z)) / (v.ay * line.v.az - line.v.ay * v.az);
			
			if(v.az != 0)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(v.ax != 0)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(v.ay != 0)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
			
			if(lp.x + k * v.ax != line.lp.x + m * line.v.ax)
				return invalid_point<T>;
		
			struct Point<T> res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		return invalid_point<T>;
		
	}
//-------------------------------------------------------------------------------------------	
	void print() const
	{
		std::cout<<"line: ";
		std::cout<<v.ax<<' '<<v.ay<<' '<<v.az<<"(vector) ";
		std::cout<<lp.x<<' '<<lp.y<<' '<<lp.z<<"(point)\n";
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>
struct Segment
{
	struct Line<T> ls;
	struct Point<T> ps1;
	struct Point<T> ps2;
	int invalid = 0 ;
//-------------------------------------------------------------------------------------------	
	Segment(struct Line<T> l, struct Point<T> p1, struct Point<T> p2) : ls(l), ps1(p1), ps2(p2){}
	
	Segment(struct Point<T> p1, struct Point<T> p2) : ls{p1, p2}, ps1(p1), ps2(p2) {if(!ps1.same(ps2)) {invalid = 1;}}
//-------------------------------------------------------------------------------------------	
	bool same(const struct Segment<T> ot) const
	{
		if(!ot.ls.same(ls))
			return false;
			
		if((ps1 == ot.ps1 || ps1 == ot.ps2) && (ps2 == ot.ps1 || ps2 == ot.ps2))
			return true;
		return false;
	}
//-------------------------------------------------------------------------------------------	
	bool onSegment(const struct Point<T> p) const
	{
		if(!ls.onLine(p))
			return false;
		
		if(!((p.x >= ps1.x && p.x <= ps2.x) || (p.x <= ps1.x && p.x >= ps2.x)))
			return false;
			
		if(!((p.z >= ps1.z && p.z <= ps2.z) || (p.z <= ps1.z && p.z >= ps2.z)))
			return false;
			
		if(!((p.y >= ps1.y && p.y <= ps2.y) || (p.y <= ps1.y && p.y >= ps2.y)))
			return false;	
			
		return true;		
	}
//-------------------------------------------------------------------------------------------	
	struct Point<T> cross(const struct Segment<T> ot) const //проверить работает ли оно
	{
		struct Point<T> res;
		res = ls.cross(ot.ls);
		
		if(res.invalid == 0)
			if(this->onSegment(res) && ot.onSegment(res))
				return res;
		
		return invalid_point<T>;
	}
//-------------------------------------------------------------------------------------------
	void print() const
	{
		std::cout<<"segment: ";
		ls.print();
		std::cout<<"seg 1 ";
		ps1.print();
		std::cout<<"seg 2 ";
		ps2.print();		
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>	
struct Surface
{
	struct Vector<T> n;
	struct Line<T> a1;
	struct Line<T> a2;
	T 		D;
	
	Surface(struct Line<T> b1, struct Line<T> b2) : a1(b1), a2(b2), n((b1.v.vectmul(b2.v)).norvec()) 
	{
		assert(!n.invalid() && "surface not exist");
		D = -(n.ax * b1.lp.x + n.ay * b1.lp.y + n.az * b1.lp.z);
	}
	
	void print() const
	{
		std::cout<<"normal ";
		n.print();
		std::cout<<"D = "<<D<<'\n';
	}
	
	bool parallel(const struct Surface<T> sur) const
	{
		if((sur.n.ax == n.ax  && sur.n.az == n.az && sur.n.ay == n.ay) || (sur.n.ax == -n.ax  && sur.n.az == -n.az && sur.n.ay == -n.ay))
			return true;
		return false;
	}
	
	bool same(const struct Surface<T> sur) const
	{
		if(!this->parallel(sur))
			return false;
			
		if(sur.n.ax == n.ax && D != sur.D)
			return false;
		
		if(sur.n.ax == -n.ax && D != -sur.D)
			return false;
			
		return true;
	}
	
	struct Point<T> crossLine(const struct Line<T> l) const 	//ПОЧИНИ
	{
		T t0;
		struct Point<T> res;
		
		if(n.ax * l.v.ax + n.ay * l.v.ay + n.az * l.v.az == 0)
			return invalid_point<T>;
		
		t0 = -(n.ax * l.lp.x + n.ay * l.lp.y + n.az * l.lp.z + D)/(n.ax * l.v.ax + n.ay * l.v.ay + n.az * l.v.az);
		
		res.x = l.v.ax * t0 + l.lp.x;
		res.y = l.v.ay * t0 + l.lp.y;
		res.z = l.v.az * t0 + l.lp.z;
		
		return res;
	}
	
	struct Point<T> crossSegment(const struct Segment<T> otr) const	//ПОЧИНИ
	{
		struct Point<T> res{0, 0, 0};
		
		res = this->crossLine(otr.ls);
		
		if(res.invalid)
			return res;
			
		if(otr.onSegment(res))
			return res;
			
		return invalid_point<T>;
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
template <typename T>	
struct Triangle
{
	struct Point<T> pt1;
	struct Point<T> pt2;
	struct Point<T> pt3;
	struct Segment<T> a;
	struct Segment<T> b;
	struct Segment<T> c;
//-------------------------------------------------------------------------------------------	
	Triangle(struct Point<T> p1, struct Point<T> p2, struct Point<T> p3) : pt1(p1), pt2(p2), pt3(p3), a{p1, p2}, b{p2, p3}, c{p3, p1}{}
	
//-------------------------------------------------------------------------------------------	
	bool no_exist() const
	{
		if(a.invalid || b.invalid || c.invalid)
			return true;
	
		if(a.ls.onLine(pt3) == true)	
			return true;
			
		if(pt1.same(pt2) || pt1.same(pt3) || pt2.same(pt3))
			return true;
			
		return false;	
	}
//-------------------------------------------------------------------------------------------
	void print() const
	{
		if(this->no_exist())
			std::cout<<"Triangle not exist"<<'\n';
	
		else
		{
		std::cout<<"Triangle:"<<'\n';
		std::cout<<"a"<<'\n';
		a.print();
		std::cout<<"b"<<'\n';
		b.print();
		std::cout<<"c"<<'\n';
		c.print();
		}
	}
//-------------------------------------------------------------------------------------------
	bool inTriangle(const struct Point<T> p) const
	{
		struct Vector<T> v1{pt1, pt2};
		struct Vector<T> v2{pt2, pt3};
		struct Vector<T> v3{pt3, pt1};
		
		struct Vector<T> a1{pt1, p};
		struct Vector<T> a2{pt2, p};
		struct Vector<T> a3{pt3, p};
		
		struct Vector<T> res1 = a1.vectmul(v1);
		struct Vector<T> res2 = a2.vectmul(v2);
		struct Vector<T> res3 = a3.vectmul(v3);
		
		if(res1.invalid() && res2.invalid())
			return true;
		if(res2.invalid() && res3.invalid())
			return true;
		if(res1.invalid() && res3.invalid())
			return true;
		
		if(!((res1.ax * res2.ax >= 0) && (res1.ax * res3.ax >= 0) && (res3.ax * res2.ax >= 0)))		//maybe error is here
			return false;
			
		if(!((res1.ay * res2.ay >= 0) && (res1.ay * res3.ay >= 0) && (res3.ay * res2.ay >= 0)))
			return false;
			
		if(!((res1.az * res2.az >= 0) && (res1.az * res3.az >= 0) && (res3.az * res2.az >= 0)))
			return false;
		
		return true;
	} 	
//-------------------------------------------------------------------------------------------
	bool crossTriangle(const struct Triangle<T> tr) const
	{
		struct Surface<T> sur{a.ls, b.ls};
		struct Surface<T> sur0{tr.a.ls, tr.b.ls};
		
		struct Point<T> p1{tr.pt1.x, tr.pt1.y, tr.pt1.z};
		struct Point<T> p2{tr.pt2.x, tr.pt2.y, tr.pt2.z};
		struct Point<T> p3{tr.pt3.x, tr.pt3.y, tr.pt3.z};		

		if(!sur.same(sur0))
		{		
		p1 = sur.crossSegment(tr.a);
		p2 = sur.crossSegment(tr.b);
		p3 = sur.crossSegment(tr.c);
		}
		
		if(p1.invalid && p2.invalid && p3.invalid)
			return false;
		
		if(!(p1.invalid) && this->inTriangle(p1))
			return true;
			
		if(!(p2.invalid) && this->inTriangle(p2))
			return true;
			
		if(!(p3.invalid) && this->inTriangle(p3))
			return true;
			
		if(!(p1.invalid) && !(p2.invalid) && !(p3.invalid))
		{				
			if(tr.inTriangle(pt1))
				return true;
			
			if(tr.inTriangle(pt2))
				return true;
			
			if(tr.inTriangle(pt3))
				return true;
		}	
			
		if(!(p1.invalid) && !(p2.invalid) && !(p1.same(p2)))
		{
			struct Segment<T> otr{p1, p2};
			
			if(!(otr.cross(a).invalid) || !(otr.cross(b).invalid) || !(otr.cross(c).invalid) )
				return true;		
		}
		
		if(!(p2.invalid) && !(p3.invalid) && !(p2.same(p3)))
		{
			struct Segment<T> otr{p2, p3};
			
			if(!otr.cross(a).invalid || !otr.cross(b).invalid || !otr.cross(c).invalid )
				return true;
		}
		
		if(!(p1.invalid) && !(p3.invalid) && !(p1.same(p3)))
		{
			struct Segment<T> otr{p1, p3};
			
			if(!otr.cross(a).invalid || !otr.cross(b).invalid || !otr.cross(c).invalid )
				return true;
		}
		
		return false;
	}
//-------------------------------------------------------------------------------------------	
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void TestCrossLine()
{
	struct Point<float> p0{0, 0, 3};
	struct Point<float> p1{1, 0, 4};
	struct Line<float> line1{p0, p1};	//line 1 for surface
	
	struct Point<float> p2{0, 0, 3};
	struct Point<float> p3{0, 1, 1};
	struct Line<float> line2{p2, p3};	//line 2 for surface
	
	struct Surface<float> sur{line1, line2};
	
	sur.print();
	
	((line1.v).vectmul(line2.v)).print();
	((line1.v).vectmul(line2.v)).norvec().print();
	
	struct Point<float> p4{ -3, 0, -2};
	struct Point<float> p5{-4, -3, -5};
	struct Line<float> line3{p4, p5};	//line for cross
	
	struct Point<float> res = sur.crossLine(line3);
	
	res.print();
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void TestCrossTriangle()
{	
	struct Point<float> p2{1, 1, 1};
	struct Point<float> p1{1, 1, 1};
	struct Point<float> p3{1, 1, 1};

	p1.x = 0;	p1.y = 0;	p1.z = 0;
	p2.x = 2;	p2.y = 2;	p2.z = 1;
	p3.x = 0;	p3.y = 0;	p3.z = 2;
	struct Triangle<float> T1{p1, p2, p3}; 	//основной
	p1.x = 0;	p1.y = 0;	p1.z = 2;
	p2.x = 0;	p2.y = 0;	p2.z = 10;
	p3.x = 5;	p3.y = 5;	p3.z = 5;
	struct Triangle<float> T2{p1, p2, p3}; 	//пересекает в точке такой же
	p1.x = -2;	p1.y = -2;	p1.z = -1;
	p2.x = 4;	p2.y = 4;	p2.z = 2;
	p3.x = 0;	p3.y = 3;	p3.z = 0;
	struct Triangle<float> T3{p1, p2, p3}; 	//пересекает по прямой но сторона бошльше
	p1.x = 10;	p1.y = 0;	p1.z = 0;
	p2.x = 19;	p2.y = 0;	p2.z = 0;
	p3.x = 18;	p3.y = 2;	p3.z = 2;
	struct Triangle<float> T4{p1, p2, p3}; 	// не пересекает
	p1.x = 1;	p1.y = 1;	p1.z = 1;
	p2.x = 2;	p2.y = -1;	p2.z = 1;
	p3.x = 10;	p3.y = 0;	p3.z = 1;
	struct Triangle<float> T5{p1, p2, p3}; 	//точка внутри
	p1.x = 0;	p1.y = 0;	p1.z = 1;
	p2.x = 0;	p2.y = -10;	p2.z = 1;
	p3.x = 4;	p3.y = -5;	p3.z = 1;
	struct Triangle<float> T6{p1, p2, p3}; 	//точка на линии
	p1.x = 1;	p1.y = 1;	p1.z = 1;
	p2.x = 0.2;	p2.y = 0.2;	p2.z = 1.5;
	p3.x = 0.2;	p3.y = 0.2;	p3.z = 0.5;
	struct Triangle<float> T7{p1, p2, p3}; 	//в одной плоскости внутри
	p1.x = -0.5;	p1.y = -0.5;	p1.z = 2.5;
	p2.x = -0.5;	p2.y = -0.5;	p2.z = -0.5;
	p3.x = 3;	p3.y = 3;	p3.z = 1;
	struct Triangle<float> T8{p1, p2, p3}; 	//в одной плоскости снаружи
	p1.x = -0.5;	p1.y = -0.5;	p1.z = 2.5;
	p2.x = -0.5;	p2.y = -0.5;	p2.z = -0.5;
	p3.x = -6;	p3.y = -6;	p3.z = 1;
	struct Triangle<float> T9{p1, p2, p3}; 	//в одной плоскости но не пересекает
	p1.x = 0;	p1.y = 0;	p1.z = 2.46;
	p2.x = 0.54;	p2.y = -0.6;	p2.z = 0;
	p3.x = -1.35;	p3.y = 0;	p3.z = 0;
	struct Triangle<float> T10{p1, p2, p3}; 	//рядышком не в одной плоскости и не пересекает
	
	
	if(T1.crossTriangle(T2))
		std::cout<<"T1 cross T2"<<'\n';
	else
		std::cout<<"T1 not cross T2"<<'\n';
		
	if(T1.crossTriangle(T3))
		std::cout<<"T1 cross T3"<<'\n';
	else
		std::cout<<"T1 not cross T3"<<'\n';
		
	if(T1.crossTriangle(T4))
		std::cout<<"T1 cross T4"<<'\n';
	else
		std::cout<<"T1 not cross T4"<<'\n';
		
	if(T1.crossTriangle(T5))
		std::cout<<"T1 cross T5"<<'\n';
	else
		std::cout<<"T1 not cross T5"<<'\n';
		
	if(T1.crossTriangle(T6))
		std::cout<<"T1 cross T6"<<'\n';
	else
		std::cout<<"T1 not cross T6"<<'\n'; 		
		
	if(T1.crossTriangle(T7))
		std::cout<<"T1 cross T7"<<'\n';
	else
		std::cout<<"T1 not cross T7"<<'\n'; 
		
	if(T1.crossTriangle(T8))
		std::cout<<"T1 cross T8"<<'\n';
	else
		std::cout<<"T1 not cross T8"<<'\n'; 
		
	if(T1.crossTriangle(T9))
		std::cout<<"T1 cross T9"<<'\n';
	else
		std::cout<<"T1 not cross T9"<<'\n'; 
		
	if(T1.crossTriangle(T1))
		std::cout<<"T1 cross T1"<<'\n';
	else
		std::cout<<"T1 not cross T1"<<'\n'; 
		
	if(T1.crossTriangle(T10))
		std::cout<<"T1 cross T10"<<'\n';
	else
		std::cout<<"T1 not cross T10"<<'\n'; 	
}

			
		


