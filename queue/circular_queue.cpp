#include <iostream>
#define MAX 5

using namespace std;

class Queue {
private:
    int front, rear;
    int arr[MAX];

public:
    Queue() {
        front = rear = -1;
        for(int i=0; i<MAX; i++) {
            arr[i] = 0;
        }
    }

    bool isFull() {
        return (front == 0 && rear == MAX-1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int new_value) {
        if(isFull()) {
            cout << "Queue overflow" << endl;
            return;
        }
        if(front == -1) {
            front = rear = 0;
        }
        else {
            if(rear == MAX-1) {
                rear = (rear+1) % MAX;
            }
            else {
                rear++;
            }
        }
        arr[rear] = new_value;
    }

    void dequeue() {
        if(isEmpty()) {
            cout << "Queue underflow" << endl;
            return;
        }
        if(front == rear) {
            front = rear = -1;
        }
        else {
            if(front == MAX-1) {
                front = (front+1) % MAX;
            }
            else {
                front++;
            }
        }
    }

    void display() {
        int front_pos = front, rear_pos = rear;
        if(isEmpty()) {
            cout << "Queue is empty" <<endl;
            return;
        }
        cout << "Queue elements: " << endl;
        if(front_pos <= rear_pos) {
            while(front_pos <= rear_pos) {
                cout << arr[front_pos] << " ";
                front_pos++;
            }
        }
        else {
            while(front_pos <= MAX-1) {
                cout << arr[front_pos] << " ";
                front_pos++;
            }
            front_pos = 0;
            while (front_pos <= rear_pos) {
                cout << arr[front_pos] << " ";
                front_pos++;
            }
        }
        cout << endl;
    }
};

int main()
{
    Queue q1;
    int choice, value;
    do {
        cout << "1. Insert a value into queue" << endl;
        cout << "2. Delete a value from the queue" << endl;
        cout << "3. Display queue" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Insert a value: ";
            cin >> value;
            q1.enqueue(value);
            break;

        case 2:
            q1.dequeue();
            break;

        case 3:
            q1.display();
            break;

        case 4:
            break;
        
        default:
            cout << "Wrong input.. please try again" << endl;
            break;
        }

    } while(choice != 4);
    return 0;
}