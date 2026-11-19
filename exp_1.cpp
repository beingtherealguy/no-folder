#include <iostream>
using namespace std;

int main() {
    int age = 19;
    float height = 5.7;
    char grade = 'A';
    bool isstudent = true;
    const int Max_Marks = 100;
    int stud_age;
    int a = 10, b = 3;

    cout << "Age: " << age << ", Height: " << height << ", Grade: " << grade << endl;
    cout << "is student: " << isstudent << ", Max Marks: " << Max_Marks << endl;
    cout << "Sum: " << a + b << ", Diff: " << a - b << ", Product: " << a * b << endl;
    cout << "Quotient: " << a / b << ", Remainder: " << a % b << ", a > b: " << (a > b) << endl;

    cout << "Enter your age: ";
    cin >> stud_age;
    cout << "You entered: " << stud_age << endl;

    return 0;
}
