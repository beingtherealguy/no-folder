#include <iostream>
#include <string>
using namespace std;

class student {
private:
    string Name;
protected:
    int DOB;
public:
    student(string name, int dob) : Name(name), DOB(dob) {}

    void display() {
        cout << "Name: " << Name << ", DOB: " << DOB << endl;
    }
};

class Grade : public student {
    int marks;
public:
    Grade(string name, int dob, int m) : student(name, dob), marks(m) {}

    void showGrade() {
        display();
        cout << "Marks: " << marks << ", DOB (protected access): " << DOB << endl;
    }
};

int main() {
    Grade myDetails("Ronx", 2007, 96);
    myDetails.showGrade();
    return 0;
}
