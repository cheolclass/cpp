#include <iostream>
using namespace std;

class Rectangle
{
protected:
	double	width, height;

public:
	virtual void  SetWidth(double d) { width = d; };
	virtual void  SetHeight(double d) { height = d; };

	double  GetWidth() { return width; }
	double  GetHeight() { return height; }

	double  Area() { return  width * height; };
};

class Square : public Rectangle
{
public:
	void SetWidth(double d) override {
		width = height = d;       // 정사각형이므로 높이도 같이 변경
	}

	void SetHeight(double d) override {
		width = height = d;        // 정사각형이므로 너비도 같이 변경
	}	 
};

void TestFunc(Rectangle& r)
{
	r.SetWidth(10);
	r.SetHeight(20);

	cout << "Width  :" << r.GetWidth() << endl;
	cout << "Height : " << r.GetHeight() << endl;
	cout << "Area   : " << r.Area() << endl;
}

int main() {
	Rectangle		r;
	TestFunc(r);

	Square		s;
	TestFunc(s);

	return 0;
}
