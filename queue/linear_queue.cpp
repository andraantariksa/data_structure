#include <iostream>
#define MAX 5

using namespace std;

class Queue {
private:
    int front;
    int rear;
    int arr[MAX];

public:
    Queue() {
        front = -1;
        rear = -1;
        for(int i=0; i<MAX; i++) {
            arr[i] = 0;
        }
    }

    bool isFull() {
        return rear == MAX-1;
    }

    bool isEmpty() {
        return rear == -1;
    }

    void enqueue(int new_value) {
        if(isFull()) {
            cout << "Queue overflow" << endl;
            return;
        }
        else {
            if(front == -1) {
                front++;
                rear++;
                arr[rear] = new_value;
            }
            else {
                rear++;
                arr[rear] = new_value;
            }
        }
    }

    int dequeue() {
        if(isEmpty()) {
            cout << "Queue underflow" << endl;
            throw;
        }
        else {
            if(front <= rear) {
                int queueValue = arr[front];
                arr[front] = 0;
                front++;
                return queueValue;
            }
            else {
                cout << "Queue is empty" << endl;
                throw;
            }
        }
    }

    void display() {
        for(int i=0; i<MAX; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Queue q1;

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.dequeue();
    q1.dequeue();
    q1.dequeue();
    q1.dequeue();
    q1.dequeue();
    q1.display();

    return 0;
}