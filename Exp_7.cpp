#include <iostream>
#include <string>
using namespace std;

template <class T>
class Stack {
    T arr[5];
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(T value) {
        if (top == 4) {
            cout << "Stack overflow!" << endl;
        } else {
            arr[++top] = value;
        }
    }

    void pop() {
        if (top == -1) {
            cout << "Stack underflow!" << endl;
        } else {
            cout << "Popped: " << arr[top--] << endl;
        }
    }

    void display() {
        if (top == -1) {
            cout << "Stack is empty" << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    cout << "Integer stack: ";
    s1.display();
    s1.pop();

    Stack<float> s2;
    s2.push(1.5f);
    s2.push(2.5f);
    cout << "Float stack: ";
    s2.display();

    Stack<string> s3;
    s3.push("Hello");
    s3.push("World");
    cout << "String stack: ";
    s3.display();

    return 0;
}
