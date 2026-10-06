#include <iostream>
using namespace std;

class Rectable
{
protected:
	double	width, height;

public:
	void  SetWidth(double d) { width = d; };
	void  SetHeight(double d) { height = d; };

	double  Area() { return  width * height; };
};

class Square : public Rectable
{
public:
	void SetWidth(double d) {
		width = d;
		height = d;       // 정사각형이므로 높이도 같이 변경
	}

	void SetHeight(double d) {
		width = d;        // 정사각형이므로 너비도 같이 변경
		height = d;
	}
};
  

int main() {
	Rectable	r;
	r.SetWidth(10);
	r.SetHeight(20);
	cout << "Rectangle: \t" << r.Area() << endl;

	Square	s;
	s.SetWidth(10);
	s.SetHeight(20);
	cout << "Square: \t" << s.Area() << endl;

	return 0;
}
