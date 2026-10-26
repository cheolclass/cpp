////// 07.  클래스/상속 모델링 연습
////// 그래픽 객체를 모델링 해보자 - point, line, polyline, rectagnle, square, cube, ...
////// 각 객체의 속성과 특징을 반영할 수 있는 멤버(변수/함수)를 선언해 보자.
////// 문법적인 요소들도 활용해 보자 - virtual, LSP 등 
////// 작성한 코드는 본인이 이해 할 수 있어야 함.

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

////// 07-2 상속성과 다형성
////// 다형성이란 무엇일까? : 함수 재정의하기 — 오버라이딩
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
