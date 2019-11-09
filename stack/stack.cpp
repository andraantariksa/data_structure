#include <iostream>

#define MAX 5

using namespace std;

class Stack {
private:
    int top;
    int arr[MAX];

public:
    Stack() {
        top = -1;
        for(int i=0; i<MAX; i++) {
            arr[i] = 0;
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX-1;
    }

    void push(int new_value) {
        if(isFull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        else {
            top++;
            arr[top] = new_value;
        }
    }

    int pop() {
        if(isEmpty()) {
            cout << "Stack Underflow" << endl;
            throw;
        }
        else {
            int popValue = arr[top];
            arr[top] = 0;
            top--;
            return popValue;
        }
    }

    int peek() {
        if(isEmpty()) {
            cout << "Stack are empty" << endl;
            throw;
        }
        return arr[top];
    }

    void display() {
        for(int i=MAX-1; i>=0; i--) {
            cout << arr[i] << endl;
        }
    }
};

int main() {
    Stack s1;
    int choice, value;
    do {
        

        cout << "1. Push value" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Stack display" << endl;
        cout << "4. Exit" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter a value: ";
            cin >> value;
            s1.push(value);
            break;

        case 2:
            cout << s1.pop() << endl;
            break;

        case 3:
            s1.display();

        case 4:
            break;
        
        default:
            cout << "Incorrect choice" << endl;
            break;
        }
        
    } while(choice != 4);
return 0;
}