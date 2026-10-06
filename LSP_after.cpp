#include <iostream>
using namespace std;

class Shape
{
public:	
	virtual double  Area() = 0;  /// 공통 함수만 여기에 둠
};

class Rectangle : public Shape
{
	double width;  /// 직사각형의 가로/세로와 정사각형의 가로/세로를 다르게 처리
	double height;

public:
	void  SetWidth(double d)  { width = d; };
	void  SetHeight(double d)  { height = d; };

	double  GetWidth()  { return width; }
	virtual double  GetHeight()  { return height; }

	virtual double  Area() override { return  width * height; };
};

class Square : public Shape
{
private:
	double side;  /// 직사각형의 가로/세로와 정사각형의 가로/세로를 다르게 처리

public:
	void SetWidth(double d)  { side = d;	}
	void SetHeight(double d)  { side = d;	}

	double  GetWidth()  { return side; }
	double  GetHeight()  { return side; }

	virtual double  Area() override { return  side * side; };
};

void TestFunc(Shape& sh)
{
	cout << "Area   : " << sh.Area() << endl;
}

int main() 
{
	Rectangle r;
	r.SetWidth(10);
	r.SetHeight(20);

	cout << "** Rectangle" << endl;
	cout << "Width  : " << r.GetWidth() << endl;
	cout << "Height : " << r.GetHeight() << endl;
	cout << "Area   : " << r.Area() << endl;

	Square s;
	s.SetWidth(20);   // 또는 s.SetHeight(20);

	cout << endl << "** Square" << endl;
	cout << "Width  : " << s.GetWidth() << endl;
	cout << "Height : " << s.GetHeight() << endl;
	cout << "Area   : " << s.Area() << endl;


	cout << endl;
	TestFunc(r);
	TestFunc(s);

}
