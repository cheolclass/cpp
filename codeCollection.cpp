/// 그래픽 객체 모델링 예제 코드 공유

#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// 1. 모든 그래픽 객체의 기반 클래스
class Shape
{
public:
	virtual void draw() const = 0;  // 순수 가상 함수
	virtual string getName() const = 0;

	virtual ~Shape() = default;
};


// 2. 점(Point)
class Point  : public Shape  // <= correct? in reaworld view
{
private:
	double x, y;

public:
	Point(double x, double y)
		: x(x), y(y) {}

	double getX() const { return x; }
	double getY() const { return y; }

	void draw() const 
	{
		cout << "Point: (" << x << ", " << y << ")\n";
	}

	string getName() const 
	{
		return "Point";
	}
};


// 3. 선분(Line)
class Line : public Shape
{
private:
	Point start, end;

public:
	Line(Point start, Point end)
		: start(start), end(end) {}

	void draw() const override
	{
		cout << "Line: ("
			<< start.getX() << ", " << start.getY()
			<< ") -> ("
			<< end.getX() << ", " << end.getY()
			<< ")\n";
	}

	string getName() const override
	{
		return "Line";
	}
};


// 4. 다중 선분(Polyline)
class Polyline : public Shape
{
private:
	vector<Point> points;

public:
	void addPoint(const Point& p)
	{
		points.push_back(p);
	}

	void draw() const override
	{
		cout << "Polyline: ";

		for (const Point& p : points)
		{
			cout << "(" << p.getX()
				<< ", " << p.getY() << ") ";
		}

		cout << '\n';
	}

	string getName() const override
	{
		return "Polyline";
	}
};


// 5. 삼각형(Triangle)
class Triangle : public Shape
{
private:
	Point p1, p2, p3;

public:
	Triangle(Point p1, Point p2, Point p3)
		: p1(p1), p2(p2), p3(p3) {}

	void draw() const override
	{
		cout << "Triangle: "
			<< "(" << p1.getX() << ", " << p1.getY() << ") "
			<< "(" << p2.getX() << ", " << p2.getY() << ") "
			<< "(" << p3.getX() << ", " << p3.getY() << ")\n";
	}

	string getName() const override
	{
		return "Triangle";
	}
};


// 6. 직사각형(Rectangle)
class Rectangle : public Shape
{
protected:
	double x, y;
	double width, height;

public:
	Rectangle(double x, double y,
		double width, double height)
		: x(x), y(y),
		width(width), height(height) {}

	void draw() const override
	{
		cout << "Rectangle: origin=("
			<< x << ", " << y
			<< "), width=" << width
			<< ", height=" << height << '\n';
	}

	string getName() const override
	{
		return "Rectangle";
	}
};


// 7. 정사각형(Square)
// Rectangle의 파생 클래스
class Square : public Rectangle
{
public:
	Square(double x, double y, double side)
		: Rectangle(x, y, side, side) {}

	void draw() const override
	{
		cout << "Square: origin=("
			<< x << ", " << y
			<< "), side=" << width << '\n';
	}

	string getName() const override
	{
		return "Square";
	}
};


// 8. 실행 및 다형성 확인
int main()
{
	vector<unique_ptr<Shape>> shapes;

	shapes.push_back(make_unique<Point>(10, 20));

	shapes.push_back(
		make_unique<Line>(
			Point(0, 0), Point(100, 100)));

	auto polyline = make_unique<Polyline>();
	polyline->addPoint(Point(0, 0));
	polyline->addPoint(Point(20, 30));
	polyline->addPoint(Point(50, 10));
	shapes.push_back(move(polyline));

	shapes.push_back(
		make_unique<Triangle>(
			Point(0, 0),
			Point(50, 100),
			Point(100, 0)));

	shapes.push_back(
		make_unique<Rectangle>(10, 20, 100, 50));

	shapes.push_back(
		make_unique<Square>(10, 20, 50));

	for (const auto& shape : shapes)
	{
		cout << "[" << shape->getName() << "] ";
		shape->draw();
	}

	return 0;
}



///---------------------------------------------
/* 07.  클래스/상속 모델링 연습 & 과제 
그래픽 객체를 모델링 해보자.
	shape, point(다른 그래픽 객체간의 관계 검토), line, polyline, 
	triangle, rectangle, square, 
	circle(수학적 정의 vs. 타원을 이용한 그리기), cube(2차원 vs. 3차원), …
각 객체의 속성과 특징을 반영할 수 있는 멤버(변수/함수)를 선언해 보자.
다음 OOP 개념을 위한 문법적인 요소들을 1번 이상 활용할 것: 
	접근 지정자를 통한 정보은폐, 상속, 멤버변수 초기화 방법(3가지), 
	오버라이딩, 오버로딩, 연산자 오버로딩 (특히 객체 복사 대입 연산자),  
	this 포인터 사용한 멤버함수 체이닝, 복사생성자, 가상함수, 
	LSP, friend, 정적 멤버변수 등 
cpp 표준 라이브러리도 활용해 보자.
	vector 등
작성한 코드는 본인이 이해 할 수 있어야 함.	*/

/// 모델링 예: 아래 클래스들을 참고하여 수정 확장해 볼 것.
#include <iostream>
#include <string>
using namespace std;
 
class Shape
{
	int  someValue = 1;
public:
	virtual   double  Area() { return someValue; }
};

class		Rectangle : public Shape
{
public: // 생성자는 반드시 public 접근지정자
	Rectangle(int w, int h) : width{w}, height{h} {}

	int		width, height;

	double	Area()
	{
		return width * height;
	}

};

class		Square : public Shape
{
public:
	Square() : side{ 3 } {}

	int		side;

	double	Area()
	{
		return side * side;
		//return side ** 2;
	}

};

void Func(Shape& s)
{
	double		area;
	area = s.Area();

	cout << area << endl;
}

int main() {

	Shape sh;  // 다양한 방법으로 객체를 생성
	Square			s;
	Rectangle		r{4, 5};

	Func(sh);
	Func(s);
	Func(r);

 	return 0;
}

///---------------------------------------------
/// 07. 그래픽 객체 화면 그리기 - Windows API 활용
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Point {
	int		x, y;
};

class Shape {
public:
	virtual void draw(HDC hdc) const = 0;
	virtual ~Shape() = default;
};

class Circle : public Shape {
private:
	int x1, y1, x2, y2;

public:
	Circle(int x1, int y1, int x2, int y2)
		: x1(x1), y1(y1), x2(x2), y2(y2) {}

	void draw(HDC hdc) const override {
		Ellipse(hdc, x1, y1, x2, y2);
	}
};

class Line : public Shape {
private:
	int x1, y1, x2, y2;
	/// vector<Point> points;

public:
	Line(int x1, int y1, int x2, int y2)
		: x1(x1), y1(y1), x2(x2), y2(y2) {}

	void draw(HDC hdc) const override {
		MoveToEx(hdc, x1, y1, nullptr);
		LineTo(hdc, x2, y2);
	}
};

class Polyline : public Shape {
private:
	vector<POINT> points;  /// windows API 구조체 사용
	/// vector<Point> points;   /// 내가 선언한 구조체 사용

public:
	Polyline(vector<POINT> points)
		: points(points) {}

	void draw(HDC hdc) const override {
		if (points.size() >= 2) {
			::Polyline(
				hdc,
				points.data(),
				static_cast<int>(points.size())
			);
		}
	}
};

// 도형 객체들을 관리
vector<unique_ptr<Shape>> shapes;  /// 여러 종류의 도형 객체들을 저장하는 벡터. 자동 메모리 해제 
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		for (const auto& shape : shapes)
			shape->draw(hdc);

		EndPaint(hwnd, &ps);
		
		return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main() {
	//Shape sh;  // 다양한 방법으로 객체를 생성
	//Square			s;
	//Rectangle		r{4, 5};

	//Func(sh);
	//Func(s);
	//Func(r);

	/// console 창에 그리기
	/*HDC hdc = GetDC(GetConsoleWindow());
	Ellipse(hdc, 100, 100, 300, 300);
	ReleaseDC(GetConsoleWindow(), hdc);*/

	/// 별도 창에 그리기
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"CircleWindow";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0, L"CircleWindow", L"Circle Drawing",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
		nullptr, nullptr, hInstance, nullptr);
	if (!hwnd)
		return 1;

	// 다양한 도형 객체를 vector에 추가
	shapes.push_back(
		make_unique<Circle>(50, 50, 200, 200));  /// 내부적으로, new Circle() 느낌 => 이후 unique_ptr에 의해 관리 및 자동 삭제 

	shapes.push_back(
		make_unique<Line>(250, 50, 450, 150));

	vector <POINT>  pts =
	{
				{250, 250},
				{ 300, 180 },
				{ 350, 300 },
				{ 450, 220 }
	};
	shapes.push_back(
		make_unique< Polyline>  (pts)
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
	return 0;
}


///---------------------------------------------
/// 07. 컴포지션과 어그리게이션 - 생성자/소멸자 호출 테스트 

#include <iostream>
using namespace std;

// 캐릭터의 특성을 가지고 있는 캐릭터 클래스
class character {
public:
	character() : hp(100), power(100) { cout << "character" << endl; };
	virtual ~character() { cout << "~character" << endl; }

	int get_hp() { return hp; };
	int get_power() { return power; };

protected:
	int hp;
	int power;
};

//character 클래스를 상속 받은 player 클래스
class player {
public:
	player() { cout << "player" << endl;  };
	virtual ~player() { cout << "~player" << endl; };

	player(const player& pl) : main_body{pl.main_body} {  /// copy constructor
	cout << "**player copy constructor" << endl; 
};


private:
	character main_body;
};

//Monster 클래스
class monster {
public:
	monster() { cout << "monster" << endl;  };
	virtual ~monster() { cout << "~monster" << endl; };

	void get_damage(int _damage) {};
	virtual void attack(player target_player) {
		cout << " 공격 : 데미지 - 10 hp" << endl;
	};
};

class monster_2nd_gen : public monster {
public:
	monster_2nd_gen() { cout << "monster_2nd_gen" << endl; }
	virtual ~monster_2nd_gen() { cout << "~monster_2nd_gen" << endl; }

	virtual void attack(player target_player) override {
		cout << " 새로운 공격 : 데미지 - 30 hp" << endl;
	};
};

//몬스터 A는 monster, charactoer 클래스를 컴포지션으로 포함
class monster_a {
public:
	monster_a() { cout << "monster_a" << endl; }
	virtual ~monster_a() { cout << "~monster_a" << endl; }

	void attack(player target_player) {
		main_role.attack(target_player);
	};
private:
	character main_body;
	monster main_role;
};

//몬스터 B는 monster, charactoer 클래스를 어그리게이션으로 포함
class monster_b {
public:
	// 레퍼런스 멤버 변수는 초기화 리스트로 초기화 진행
	monster_b(character& ref_character, monster& ref_monster)
		: main_body(ref_character), main_role(ref_monster) {
		cout << "monster_b" << endl;
	};
	virtual ~monster_b() { cout << "~monster_b" << endl; }

	void attack(player target_player) {
		main_role.attack(target_player);
	};
private:
	character& main_body;
	monster& main_role;
};

int main() {
	// 어그리게이션에 포함할 객체 생성 - 몬스터 클래스의 생명 주기 다름
	character chararater_obj;
	monster monster_obj;
	monster_2nd_gen monster_new_obj;

	player player_1;

	// 컴포지션을 객체와 생명주기가 같아 객체에서 직접 생성
	monster_a forest_monster;

	// 어그리게이션을 위해서 외부의 객체의 참조를 전달
	monster_b tutorial_monster(chararater_obj, monster_obj);
	monster_b urban_monster(chararater_obj, monster_new_obj);
	cout << "몬스터 A 공격" << endl;
	tutorial_monster.attack(player_1);

	cout << endl << "몬스터 B 공격" << endl;
	forest_monster.attack(player_1);
	urban_monster.attack(player_1);
	return 0;
}


///---------------------------------------------
/// 07-2 상속성과 다형성
/// 다형성이란 무엇일까? : 함수 재정의하기 — 오버라이딩
#include <iostream>
using namespace std;

class character {
public:
  character() : hp(100), power(100) {};

protected:
  int hp;
  int power;
};

//character 클래스를 상속 받은 player 클래스
class player : public character {
public:
  player() {};
};

//기본 Monster 클래스
class monster {
public:
  monster() {};
  void get_damage(int _damage) {};
  void attack(player target_player) {};
  void attack_special(player target_player);
};

void monster::attack_special(player target_player) {
  cout << "기본 공격 : 데미지 - 10 hp" << endl;
}

//몬스터 A는 기본 Monster 클래스로부터 상속
class monster_a : public monster, character {
public:
  //상속받은 함수 오버라이딩 
  void attack_special(player target_player);
};

void monster_a::attack_special(player target_player) {
  cout << "인텡글 공격 : 데미지 - 15 hp" << endl;
}

//몬스터 B는 기본 Monster 클래스로부터 상속
class monster_b : public monster, character {
public:
  //상속받은 함수 오버라이딩
  void attack_special(player target_player);
};

void monster_b::attack_special(player target_player) {
  cout << "가상 공격 : 데미지 - 0 hp" << endl;
}

//몬스터 C는 기본 Monster 클래스로부터 상속
class monster_c : public monster, character {
public:
  //상속받은 함수 오버라이딩
  void attack_special(player target_player);
};

void monster_c::attack_special(player target_player) {
  cout << "강력 뇌전 공격 : 데미지 - 100 hp" << endl;
}

int main() {
  player player_1;

  monster_a forest_monster;
  monster_b tutorial_monster;
  monster_c boss_monster;

  cout << "오버라이딩된 공격" << endl;
  tutorial_monster.attack_special(player_1);
  forest_monster.attack_special(player_1);
  boss_monster.attack_special(player_1);

  cout << endl << "기본(monster 클래스) 공격" << endl;
  tutorial_monster.monster::attack_special(player_1);
  forest_monster.monster::attack_special(player_1);
  boss_monster.monster::attack_special(player_1);

  return 0;
}
