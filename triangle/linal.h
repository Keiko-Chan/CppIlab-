#include <iostream>
#include <math.h>
#include <assert.h>
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
double e = 0.00001; //accuracy
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
struct Point
{
	double x = 0;
	double y = 0;
	double z = 0;
	int invalid = 0;
	
	Point(double x1, double y1, double z1) : x(x1), y(y1), z(z1) {}
	Point() : invalid(0) {} 
	Point(int a) : invalid(a) {} 
	
	void print() const
	{
		if(invalid == 1)
			std::cout<<"invalid point";
			
		else
			std::cout<<"point: ";
			std::cout<<x<<' '<<y<<' '<<z<<'\n';
	}
	
	bool same(const struct Point point) const
	{
		if(fabs(x - point.x) < e && fabs(y - point.y) < e && fabs(z - point.z) < e && invalid == point.invalid)
			return true;
		else
			return false;
		
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
static struct Point invalid_point{1};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
struct Vector
{
	double ax = 0;
	double ay = 0;
	double az = 0;
	
	Vector(double x1, double y1, double z1) : ax(x1), ay(y1), az(z1) {}
	
	Vector(struct Point p1, struct Point p2) : ax(p2.x - p1.x), ay(p2.y - p1.y), az(p2.z - p1.z) {}
	
	Vector() {}
	
	double leng() const
	{
		return sqrt(ay*ay + ax*ax + az*az);
	}
	
	struct Vector norvec() const
	{
		struct Vector v{ax, ay, az};
		
		assert((ax != 0 || ay != 0 || az != 0) && "invalid vector leng");
		
		double lenge = v.leng();
		
		v.ax = v.ax / lenge;
		v.ay = v.ay / lenge;
		v.az = v.az / lenge;
		
		return v;
	}
	
	bool same(const struct Vector vect) const	
	{
		if(vect.invalid() && invalid())
			return true;
	
		struct Vector v2;
		struct Vector v1;		
		v1 = vect.norvec();
		v2 = norvec();
		
		if(((fabs(v2.ax - v1.ax) < e) && (fabs(v2.ay - v1.ay) < e) && (fabs(v2.az - v1.az) < e)) || ((fabs(v2.ax + v1.ax) < e) && (fabs(v2.ay + v1.ay) < e) && (fabs(v2.az + v1.az) < e)))
			return true;
			
		return false;		
	}
	
	void print() const
	{
		std::cout<<"vector: ";
		std::cout<<ax<<' '<<ay<<' '<<az<<'\n';
	}	
	
	struct Vector vectmul(const struct Vector v)
	{
		struct Vector res{};
		
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
struct Line
{
	struct Point lp;
	struct Vector v;
	int invalid = 0;
//-------------------------------------------------------------------------------------------	
	Line(struct Point p1, struct Vector v1) : v(v1), lp(p1) { if((v1.invalid())) invalid = 1; }
	
	Line(struct Point p1, struct Point p2) : lp(p1), v{p1, p2} { if((p1.same(p2))) invalid = 1; }
//-------------------------------------------------------------------------------------------	
	bool onLine(const struct Point p1) const
	{
		if(p1.same(lp))
			return true;
	
		struct Vector v1(p1, lp);		
		
		if(v1.same(v))
			return true;			
			
		else 
			return false;
	} 
//-------------------------------------------------------------------------------------------	
	bool same(const struct Line line) const
	{
		if(!(line.v).same(v))
			return false;
		
		struct Line newline{line.lp, lp};
		
		if(!newline.v.same(v))
			return false;
		
		return true;
	}
//-------------------------------------------------------------------------------------------	
	struct Point cross(const struct Line line) const
	{
		if(same(line))
			return invalid_point;
			
		if(v.same(line.v))
			return invalid_point;
			
		double k;
		double m;
		
		if(fabs(v.ay * line.v.ax - v.ax * line.v.ay) > e)
		{
		
			m = (v.ax * (line.lp.y - lp.y) + v.ay * (lp.x - line.lp.x)) / (v.ay * line.v.ax - line.v.ay * v.ax);		
		
			if(fabs(v.az) > e)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(fabs(v.ax) > e)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(fabs(v.ay) > e)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
		
			struct Point res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		if(fabs(v.az * line.v.ax - v.ax * line.v.az) > e)
		{
		
			m = (v.ax * (line.lp.z - lp.z) + v.az * (lp.x - line.lp.x)) / (v.az * line.v.ax - line.v.az * v.ax);
		
			if(fabs(v.az) > e)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(fabs(v.ax) > e)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(fabs(v.ay) > e)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
		
			struct Point res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		if(fabs(v.ay * line.v.az - v.az * line.v.ay) > e)
		{
		
			m = (v.az * (line.lp.y - lp.y) + v.ay * (lp.z - line.lp.z)) / (v.ay * line.v.az - line.v.ay * v.az);
			
			if(fabs(v.az) > e)
				k = (line.lp.z + m * line.v.az - lp.z) / v.az;
				
			if(fabs(v.ax) > e)
				k = (line.lp.x + m * line.v.ax - lp.x) / v.ax;
				
			if(fabs(v.ay) > e)
				k = (line.lp.y + m * line.v.ay - lp.y) / v.ay;
			
			if(lp.x + k * v.ax != line.lp.x + m * line.v.ax)
				return invalid_point;
		
			struct Point res(lp.x + k * v.ax, lp.y + k * v.ay, lp.z + k * v.az);
			return res;
		}
		
		return invalid_point;
		
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
struct Segment
{
	struct Line ls;
	struct Point ps1;
	struct Point ps2;
	int invalid = 0 ;
//-------------------------------------------------------------------------------------------	
	Segment(struct Line l, struct Point p1, struct Point p2) : ls(l), ps1(p1), ps2(p2){}
	
	Segment(struct Point p1, struct Point p2) : ls{p1, p2}, ps1(p1), ps2(p2) { if(p1.same(p2)) { invalid = 1; } }
//-------------------------------------------------------------------------------------------	
	bool same(const struct Segment ot) const
	{
		if(!ot.ls.same(ls))
			return false;
			
		if((ps1.same(ot.ps1) || ps1.same(ot.ps2)) && (ps2.same(ot.ps1) || ps2.same(ot.ps2)))
			return true;
		return false;
	}
//-------------------------------------------------------------------------------------------	
	bool onSegment(const struct Point p) const
	{
		if(!ls.onLine(p))
			return false;
		
		if(!(fabs(ps2.x - p.x) + fabs(p.x - ps1.x) <= fabs(ps2.x - ps1.x) + e))
			return false;
			
		if(!(fabs(ps2.z - p.z) + fabs(p.z - ps1.z) <= fabs(ps2.z - ps1.z) + e))
			return false;
			
		if(!(fabs(ps2.y - p.y) + fabs(p.y - ps1.y) <= fabs(ps2.y - ps1.y) + e))
			return false;	
			
		return true;		
	}
//-------------------------------------------------------------------------------------------	
	struct Point cross(const struct Segment ot) const 
	{
		struct Point res;
		res = ls.cross(ot.ls);
		
		if(res.invalid == 0)
			if(onSegment(res) && ot.onSegment(res))
				return res;
		
		return invalid_point;
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
struct Surface
{
	struct Vector n;
	struct Line a1;
	struct Line a2;
	double 		D;
	
	Surface(struct Line b1, struct Line b2) : a1(b1), a2(b2), n((b1.v.vectmul(b2.v)).norvec()) 
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
	
	bool parallel(const struct Surface sur) const
	{
		if(sur.n.same(n))
			return true;
		return false;
	}
	
	bool same(const struct Surface sur) const
	{
		if(!this->parallel(sur))
			return false;
			
		if(fabs(D - sur.D) > e)
			return false;
			
		return true;
	}
	
	bool belongPoint(const struct Point p) const
	{
		if(fabs(p.x * n.ax + p.y * n.ay + p.z * n.az + D) < e)
			return true;
		return false;
	}
	
	struct Point crossLine(const struct Line l) const 	
	{
		double t0;
		struct Point res;
		
		if(fabs(n.ax * l.v.ax + n.ay * l.v.ay + n.az * l.v.az) < e)
			return invalid_point;
		
		t0 = -(n.ax * l.lp.x + n.ay * l.lp.y + n.az * l.lp.z + D)/(n.ax * l.v.ax + n.ay * l.v.ay + n.az * l.v.az);
		
		res.x = l.v.ax * t0 + l.lp.x;
		res.y = l.v.ay * t0 + l.lp.y;
		res.z = l.v.az * t0 + l.lp.z;
		
		return res;
	}
	
	struct Point crossSegment(const struct Segment otr) const	
	{
		struct Point res{0, 0, 0};
		
		res = crossLine(otr.ls);
		
		if(res.invalid)
			return res;
			
		if(otr.onSegment(res))
			return res;
			
		return invalid_point;
	}
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------	
struct Triangle
{
	struct Point pt1;
	struct Point pt2;
	struct Point pt3;
	struct Segment a;
	struct Segment b;
	struct Segment c;
	int invalid = 0; 		//invalid = 0 - valid, invalid = 1 - point, invalid = 2 - line;
	int number = 0;
//-------------------------------------------------------------------------------------------	
	Triangle(struct Point p1, struct Point p2, struct Point p3) : pt1(p1), pt2(p2), pt3(p3), a{p1, p2}, b{p2, p3}, c{p3, p1}
	{
		if(a.invalid && b.invalid)
		{
			invalid = 1;
			return;
		}	
		
		if(a.invalid || b.invalid || c.invalid)
		{
			invalid = 2;
			return;
		}
		
		if(a.ls.v.same(b.ls.v))
		{
			invalid = 2;
			return;
		}
	}
	Triangle(struct Point p1, struct Point p2, struct Point p3, int num) : pt1(p1), pt2(p2), pt3(p3), a{p1, p2}, b{p2, p3}, c{p3, p1}, number(num)
	{
		if(a.invalid && b.invalid)
		{
			invalid = 1;
			return;
		}	
		
		if(a.invalid || b.invalid || c.invalid)
		{
			invalid = 2;
			return;
		}
		
		if(a.ls.v.same(b.ls.v))
		{
			invalid = 2;
			return;
		}
	}
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
	bool inTriangle(const struct Point p) const
	{
		if(p.invalid == 1)
			return false;		
		
		struct Vector v1{pt1, pt2};
		struct Vector v2{pt2, pt3};
		struct Vector v3{pt3, pt1};
		
		struct Vector a1{pt1, p};
		struct Vector a2{pt2, p};
		struct Vector a3{pt3, p};
		
		struct Vector res1 = a1.vectmul(v1);
		struct Vector res2 = a2.vectmul(v2);
		struct Vector res3 = a3.vectmul(v3);
		
		if(res1.invalid() && res2.invalid())
			return true;
		if(res2.invalid() && res3.invalid())
			return true;
		if(res1.invalid() && res3.invalid())
			return true;
		
		if(!((res1.ax * res2.ax >= 0) && (res1.ax * res3.ax >= 0) && (res3.ax * res2.ax >= 0)))		
			return false;
			
		if(!((res1.ay * res2.ay >= 0) && (res1.ay * res3.ay >= 0) && (res3.ay * res2.ay >= 0)))
			return false;
			
		if(!((res1.az * res2.az >= 0) && (res1.az * res3.az >= 0) && (res3.az * res2.az >= 0)))
			return false;
		
		return true;
	} 
//-------------------------------------------------------------------------------------------
	bool Tr_Tr(const struct Triangle tr) const
	{
		struct Surface sur{a.ls, b.ls};
			struct Surface sur0{tr.a.ls, tr.b.ls};
			
			struct Point p1{tr.pt1.x, tr.pt1.y, tr.pt1.z};
			struct Point p2{tr.pt2.x, tr.pt2.y, tr.pt2.z};
			struct Point p3{tr.pt3.x, tr.pt3.y, tr.pt3.z};		

			if(!sur.same(sur0))
			{		
				p1 = sur.crossSegment(tr.a);
				p2 = sur.crossSegment(tr.b);
				p3 = sur.crossSegment(tr.c);
			}
			
			if(p1.invalid && p2.invalid && p3.invalid)
				return false;
			
			if(!(p1.invalid) && inTriangle(p1))
				return true;
				
			if(!(p2.invalid) && inTriangle(p2))
				return true;
				
			if(!(p3.invalid) && inTriangle(p3))
				return true;
				
			if(sur.same(sur0))
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
				struct Segment otr{p1, p2};
				
				if(!(otr.cross(a).invalid) || !(otr.cross(b).invalid) || !(otr.cross(c).invalid) )
					return true;		
			}
			
			if(!(p2.invalid) && !(p3.invalid) && !(p2.same(p3)))
			{
				struct Segment otr{p2, p3};
				
				if(!otr.cross(a).invalid || !otr.cross(b).invalid || !otr.cross(c).invalid )
					return true;
			}
			
			if(!(p1.invalid) && !(p3.invalid) && !(p1.same(p3)))
			{
				struct Segment otr{p1, p3};
				
				if(!otr.cross(a).invalid || !otr.cross(b).invalid || !otr.cross(c).invalid )
					return true;
			}
			
			return false;
	}	
//-------------------------------------------------------------------------------------------
	bool Tr_Otr(const struct Triangle tr) const
	{
		struct Surface sur{a.ls, b.ls};
			
		struct Point res{};	
			
		if(tr.c.invalid == 0)
		{
			if(sur.belongPoint(tr.c.ps1) && sur.belongPoint(tr.c.ps2))
			{				
				if(!tr.c.cross(a).invalid || !tr.c.cross(b).invalid || !tr.c.cross(c).invalid )
					return true;	
				
				if(this->inTriangle(tr.c.ps1) || inTriangle(tr.c.ps2))
					return true;
			}
		
			res = sur.crossSegment(tr.c);				
			if(res.invalid == 0 && inTriangle(res))
				return true;
		}
		
		if(tr.a.invalid == 0)
		{		
			if(sur.belongPoint(tr.a.ps1) && sur.belongPoint(tr.a.ps2))
			{				
				if(!tr.a.cross(a).invalid || !tr.a.cross(b).invalid || !tr.a.cross(c).invalid )
					return true;
					
				if(this->inTriangle(tr.a.ps1) || inTriangle(tr.a.ps2))
					return true;	
			}
		
			res = sur.crossSegment(tr.a);				
			if(res.invalid == 0 && inTriangle(res))
				return true;
		}
		
		if(tr.b.invalid == 0)
		{	
			if(sur.belongPoint(tr.b.ps1) && sur.belongPoint(tr.b.ps2))
			{				
				if(!tr.b.cross(a).invalid || !tr.b.cross(b).invalid || !tr.b.cross(c).invalid )
					return true;	
					
				if(this->inTriangle(tr.b.ps1) || inTriangle(tr.b.ps2))
					return true;
			}
			
			res = sur.crossSegment(tr.b);				
			if(res.invalid == 0 && inTriangle(res))
				return true;
		}
		
		return false;
	}
//-------------------------------------------------------------------------------------------
	bool Tr_P(const struct Triangle tr) const
	{
		struct Surface sur{a.ls, b.ls};
			
		if(!(sur.belongPoint(tr.pt1)))
			return false;
			
		if(this->inTriangle(tr.pt1))
			return true;
				
		return false;
	}
//-------------------------------------------------------------------------------------------
	bool P_Otr(const struct Triangle tr) const
	{
		if(tr.a.invalid == 0)
		{
			if(tr.a.onSegment(pt1))
				return true;
				
			return false;
		}
		
		if(tr.b.invalid == 0)
		{
			if(tr.b.onSegment(pt1))
				return true;
				
			return false;
		}
		
		return false;
	}
//-------------------------------------------------------------------------------------------
	bool Otr_Otr(const struct Triangle tr) const
	{
		struct Point res{};	
		
		if(a.invalid == 0)
		{
			if(tr.a.invalid == 0)
			{
				res = a.cross(tr.a);
				if(res.invalid == 0)
					return true;
				return false;
			}
			
			if(tr.b.invalid == 0)
			{
				res = a.cross(tr.b);
				if(res.invalid == 0)
					return true;
				return false;
			}
			
			return false;
		}
		
		if(b.invalid == 0)
		{
			if(tr.a.invalid == 0)
			{
				res = b.cross(tr.a);
				if(res.invalid == 0)
					return true;
				return false;
			}
			
			if(tr.b.invalid == 0)
			{
				res = b.cross(tr.b);
				if(res.invalid == 0)
					return true;
				return false;
			}
			
			return false;
		}
		
		return false;
	}
//-------------------------------------------------------------------------------------------
	bool P_P(const struct Triangle tr) const
	{
		if(pt1.same(tr.pt1))
			return true;
		return false;
	}
//-------------------------------------------------------------------------------------------
	bool crossTriangle(const struct Triangle tr) const
	{		
		if(invalid == 0 && tr.invalid == 0)
			return Tr_Tr(tr);
		
		if(invalid == 1 && tr.invalid == 1)
			return P_P(tr);		
		
		if(invalid == 0 && tr.invalid == 1)
			return Tr_P(tr);
		
		if(invalid == 1 && tr.invalid == 0)
			return tr.Tr_P(*this);
		
		if(invalid == 2 && tr.invalid == 0)
			return tr.Tr_Otr(*this);
		
		if(invalid == 0 && tr.invalid == 2)
			return Tr_Otr(tr);
		
		if(invalid == 2 && tr.invalid == 2)
			return Otr_Otr(tr);
			
		if(invalid == 1 && tr.invalid == 2)
			return P_Otr(tr);
		
		if(invalid == 2 && tr.invalid == 1)
			return tr.P_Otr(*this);
		
		return false;
	}
//-------------------------------------------------------------------------------------------	
};
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void TestCrossLine()
{
	struct Point p0{0, 0, 3};
	struct Point p1{1, 0, 4};
	struct Line line1{p0, p1};	//line 1 for surface
	
	struct Point p2{0, 0, 3};
	struct Point p3{0, 1, 1};
	struct Line line2{p2, p3};	//line 2 for surface
	
	struct Surface sur{line1, line2};
	
	sur.print();
	
	((line1.v).vectmul(line2.v)).print();
	((line1.v).vectmul(line2.v)).norvec().print();
	
	struct Point p4{ -3, 0, -2};
	struct Point p5{-4, -3, -5};
	struct Line line3{p4, p5};	//line for cross
	
	struct Point res = sur.crossLine(line3);
	
	res.print();
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void TestCrossTriangle()
{	
	struct Point p2{1, 1, 1};
	struct Point p1{1, 1, 1};
	struct Point p3{1, 1, 1};

	p1.x = 0;	p1.y = 0;	p1.z = 0;
	p2.x = 2;	p2.y = 2;	p2.z = 1;
	p3.x = 0;	p3.y = 0;	p3.z = 2;
	struct Triangle T1{p1, p2, p3}; 	//основной
	p1.x = 0;	p1.y = 0;	p1.z = 2;
	p2.x = 0;	p2.y = 0;	p2.z = 10;
	p3.x = 5;	p3.y = 5;	p3.z = 5;
	struct Triangle T2{p1, p2, p3}; 	//пересекает в точке такой же
	p1.x = -2;	p1.y = -2;	p1.z = -1;
	p2.x = 4;	p2.y = 4;	p2.z = 2;
	p3.x = 0;	p3.y = 3;	p3.z = 0;
	struct Triangle T3{p1, p2, p3}; 	//пересекает по прямой но сторона бошльше
	p1.x = 10;	p1.y = 0;	p1.z = 0;
	p2.x = 19;	p2.y = 0;	p2.z = 0;
	p3.x = 18;	p3.y = 2;	p3.z = 2;
	struct Triangle T4{p1, p2, p3}; 	// не пересекает
	p1.x = 1;	p1.y = 1;	p1.z = 1;
	p2.x = 2;	p2.y = -1;	p2.z = 1;
	p3.x = 10;	p3.y = 0;	p3.z = 1;
	struct Triangle T5{p1, p2, p3}; 	//точка внутри
	p1.x = 0;	p1.y = 0;	p1.z = 1;
	p2.x = 0;	p2.y = -10;	p2.z = 1;
	p3.x = 4;	p3.y = -5;	p3.z = 1;
	struct Triangle T6{p1, p2, p3}; 	//точка на линии
	p1.x = 1;	p1.y = 1;	p1.z = 1;
	p2.x = 0.2;	p2.y = 0.2;	p2.z = 1.5;
	p3.x = 0.2;	p3.y = 0.2;	p3.z = 0.5;
	struct Triangle T7{p1, p2, p3}; 	//в одной плоскости внутри
	p1.x = -0.5;	p1.y = -0.5;	p1.z = 2.5;
	p2.x = -0.5;	p2.y = -0.5;	p2.z = -0.5;
	p3.x = 3;	p3.y = 3;	p3.z = 1;
	struct Triangle T8{p1, p2, p3}; 	//в одной плоскости снаружи
	p1.x = -0.5;	p1.y = -0.5;	p1.z = 2.5;
	p2.x = -0.5;	p2.y = -0.5;	p2.z = -0.5;
	p3.x = -6;	p3.y = -6;	p3.z = 1;
	struct Triangle T9{p1, p2, p3}; 	//в одной плоскости но не пересекает
	p1.x = 0;	p1.y = 0;	p1.z = 2.46;
	p2.x = 0.54;	p2.y = -0.6;	p2.z = 0;
	p3.x = -1.35;	p3.y = 0;	p3.z = 0;
	struct Triangle T10{p1, p2, p3}; 	//рядышком не в одной плоскости и не пересекает
	
	
	if(T1.crossTriangle(T2) && T2.crossTriangle(T1))
		std::cout<<"T1 & T2 cross"<<'\n';
	else
		std::cout<<"T1 & T2 error"<<'\n';
		
	if(T1.crossTriangle(T3) && T3.crossTriangle(T1))
		std::cout<<"T1 & T3 cross"<<'\n';
	else
		std::cout<<"T1 & T3 error"<<'\n';
		
	if(!(T1.crossTriangle(T4) || T4.crossTriangle(T1)))
		std::cout<<"T1 & T4 no cross"<<'\n';
	else
		std::cout<<"T1 & T4 error"<<'\n';
		
	if(T1.crossTriangle(T5) && T5.crossTriangle(T1))
		std::cout<<"T1 & T5 cross"<<'\n';
	else
		std::cout<<"T1 & T5 error"<<'\n';
		
	if(T1.crossTriangle(T6) && T6.crossTriangle(T1))
		std::cout<<"T1 & T6 cross"<<'\n';
	else
		std::cout<<"T1 & T6 error"<<'\n'; 		
		
	if(T1.crossTriangle(T7) && T7.crossTriangle(T1))
		std::cout<<"T1 & T7 cross"<<'\n';
	else
		std::cout<<"T1 & T7 error"<<'\n';
		
	if(T1.crossTriangle(T8) && T8.crossTriangle(T1))
		std::cout<<"T1 & T8 cross"<<'\n';
	else
		std::cout<<"T1 & T8 error"<<'\n'; 
		
	if(!(T1.crossTriangle(T9) || T9.crossTriangle(T1)))
		std::cout<<"T1 & T9 no cross"<<'\n';
	else
		std::cout<<"T1 & T9 error"<<'\n';
		
	if(T1.crossTriangle(T1))
		std::cout<<"T1 & T1 cross"<<'\n';
	else
		std::cout<<"T1 & T1 error"<<'\n';
		
	if(!(T1.crossTriangle(T10) || T10.crossTriangle(T1)))
		std::cout<<"T1 & T10 no cross"<<'\n';
	else
		std::cout<<"T1 & T10 error"<<'\n'; 	
}

			
		


