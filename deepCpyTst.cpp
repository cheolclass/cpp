/// Shallow copy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 사람 정보를 담는 구조체
struct Person {
	string name;  // 이름
	int age;      // 나이
	float height; // 키
	float weight; // 몸무게
};

// 벡터에 저장된 사람 정보 출력 함수
void print_person_all(vector<Person>& vec) {
	for (vector<Person>::iterator it = vec.begin(); it != vec.end();
		it++) {
		cout << "이름: " << it->name << "\t > " << "나이: " << it->age
			<< ", " << "키: " << it->height << ", " << "몸무게: "
			<< it->weight << endl;
	}
}

int main() {
	// Person 구조체 배열 생성
	Person p[5] = {
		{ "Brain", 24, 180, 70 },
		{ "Jessica", 22, 165, 55 },
		{ "James", 30, 170, 65 },
		{ "Tom", 12, 155, 46 },
		{ "Mary", 18, 172, 62 }
	};

	// from_vector에 Person 배열 순서대로 넣기
	vector<Person> from_vector;
	from_vector.push_back(p[0]);
	from_vector.push_back(p[1]);
	from_vector.push_back(p[2]);
	from_vector.push_back(p[3]);
	from_vector.push_back(p[4]);

	// from_vector 출력
	cout << "-----from_vector-----" << endl;
	print_person_all(from_vector);
	cout << endl;

	// to_vector에 from_vector의 원소를 ‘깊은 복사’ 수행
	vector<Person> to_vector;
	copy(from_vector.begin(), from_vector.end(),
		back_inserter(to_vector));  ////

	// 복사 후 to_vector 출력
	cout << "-----to_vector-----" << endl;
	print_person_all(to_vector);
	cout << endl;

	// from_vector의 첫 번째 원소 수정
	from_vector[0].name = "Chris";
	from_vector[0].age = 5;
	from_vector[0].height = 110;
	from_vector[0].weight = 20;

	// 수정 후 from_vector 출력
	cout << "-----from_vector-----" << endl;
	print_person_all(from_vector);
	cout << endl;

	// to_vector 출력
	cout << "-----to_vector-----" << endl;
	print_person_all(to_vector);
	cout << endl;

	return 0;
}


/// Deep copy
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 사람 정보를 담는 구조체
struct Person {
    char* name;  // 동적 메모리를 사용하는 문자열
    int age;
    float height;
    float weight;

    // 일반 생성자
    Person(const char* name, int age, float height, float weight)
        : age(age), height(height), weight(weight)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // 복사 생성자 (Deep Copy)
    Person(const Person& other)
        : age(other.age), height(other.height), weight(other.weight)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    // 복사 대입 연산자 (Deep Copy)
    Person& operator=(const Person& other)
    {
        if (this != &other) {
            char* newName = new char[strlen(other.name) + 1];
            strcpy(newName, other.name);

            delete[] name;
            name = newName;

            age = other.age;
            height = other.height;
            weight = other.weight;
        }

        return *this;
    }

    // 소멸자
    ~Person()
    {
        delete[] name;
    }
};

// 벡터에 저장된 사람 정보 출력 함수
void print_person_all(vector<Person>& vec) {
    for (vector<Person>::iterator it = vec.begin();
         it != vec.end(); it++) {

        cout << "이름: " << it->name
             << "\t > 나이: " << it->age
             << ", 키: " << it->height
             << ", 몸무게: " << it->weight << endl;
    }
}

int main() {
    // Person 객체 배열 생성
    Person p[5] = {
        { "Brain", 24, 180, 70 },
        { "Jessica", 22, 165, 55 },
        { "James", 30, 170, 65 },
        { "Tom", 12, 155, 46 },
        { "Mary", 18, 172, 62 }
    };

    // from_vector에 Person 배열 순서대로 넣기
    vector<Person> from_vector;

    for (int i = 0; i < 5; i++)
        from_vector.push_back(p[i]);

    cout << "-----from_vector-----" << endl;
    print_person_all(from_vector);
    cout << endl;

    // Deep Copy
    vector<Person> to_vector;

    copy(from_vector.begin(), from_vector.end(),
         back_inserter(to_vector));  ////

    cout << "-----to_vector-----" << endl;
    print_person_all(to_vector);
    cout << endl;

    // from_vector의 첫 번째 원소 수정
    delete[] from_vector[0].name;

    from_vector[0].name = new char[strlen("Chris") + 1];
    strcpy(from_vector[0].name, "Chris");

    from_vector[0].age = 5;
    from_vector[0].height = 110;
    from_vector[0].weight = 20;

    cout << "-----from_vector 수정 후-----" << endl;
    print_person_all(from_vector);
    cout << endl;

    cout << "-----to_vector-----" << endl;
    print_person_all(to_vector);

    return 0;
}

