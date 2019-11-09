#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *next;
};

class Queue {
    public:
    Node *front, *rear;
};

Node *newNode(int k) {
    Node *temp = new Node();
    temp->data = k;
    temp->next = NULL;
    return temp;
}

Queue *createQueue() {
    Queue *q = new Queue();
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, int k) {
    Node *temp = newNode(k);
    if(q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node *deQueue(Queue *q) {
    if(q->front == NULL) {
        return NULL;
    }
    Node *temp = q->front;
    free(temp);

    q->front = q->front->next;

    if(q->front == NULL) q->rear = NULL;
    return temp;
}

int main() 
{ 
    Queue* q = createQueue(); 
    enQueue(q, 10); 
    enQueue(q, 20); 
    deQueue(q); 
    deQueue(q); 
    enQueue(q, 30); 
    enQueue(q, 40); 
    enQueue(q, 50); 
    Node* n = deQueue(q); 
    if (n != NULL) 
        cout << "Dequeued item is " << n->data; 
    return 0; 
} 