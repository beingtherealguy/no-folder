#include <iostream>
#include <string>
using namespace std;

class student {
public:
    string name;

    // Default constructor
    student() {
        name = "Krishna";
        cout << "Default constructor" << endl;
    }

    // Parameterized constructor
    student(string n) {
        name = n;
        cout << "Parameterized constructor" << endl;
    }

    // Copy constructor
    student(const student &s) {
        name = s.name;
        cout << "Copy constructor" << endl;
    }

    // Move constructor
    student(student &&s) {
        name = s.name;
        cout << "Move constructor" << endl;
    }

    ~student() {
        cout << "Destructor" << endl;
    }
};

int main() {
    student s1;
    cout << "Name: " << s1.name << endl;

    student s2("Krishna");
    cout << "Name: " << s2.name << endl;

    student s3(s2);
    cout << "Name: " << s3.name << endl;

    student s4(student("Rahul"));
    cout << "Name: " << s4.name << endl;

    return 0;
}
