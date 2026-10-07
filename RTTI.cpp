#include <iostream> 
#include <typeinfo> /// 

using namespace std;

class Human {
public:
	void normalFunc() {   /// => virtual 함수로 선언시 아래 실행 결과는?
		cout << "Human" << endl;
	}

	virtual ~Human() = default;  // 1.dynamic_cast 사용을 위한 다형성 제공 위해 => RTTI(Run-Time Type Information)
	// 2. body 구현 => 컴파일러에게 맡김
};

class Student : public Human {
public:
	void normalFunc() {
		cout << "Student" << endl;
	}
};

int main() 
{		
	Human h;
	h.normalFunc();

	Student s;
	s.normalFunc();
	
	Human h0 = static_cast<Human>(s); // Student => Human. Object slicing
	h0.normalFunc();

	Human& h1 = dynamic_cast<Human&>(s);  // *Reference: Student => Human. Upcasting
	h1.normalFunc();
	cout << typeid(h1).name() << endl;

	//Human& h = dynamic_cast<Human&>(Student()); // 임시 객체	 
	
	Human* h2 = dynamic_cast<Human*>(&s); // *Pointer: Student => Human
	h2->normalFunc();
		
	//Student& h3 = dynamic_cast<Student&>(h); // Undefined Behavior: Human => Student. Downcasting
	try  // 실행시간 casting 오류 체크 
	{
		Student& h3 = dynamic_cast<Student&>(h); // Undefined Behavior: Human => Student, Downcasting
	}
	catch (const exception& e)  // std::bad_cast& e
	{
		cout << e.what() << endl;
	}


	return 0;
}
