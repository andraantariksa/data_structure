#include <iostream>

using namespace std;

class Node 
{
public:
    int data;
    Node *next;
};

// Insert new value at the back of the list
void insertBack(Node **head, int new_value) {
    Node *new_node = new Node();
    Node *last = new Node();
    last = *head;
    new_node->data = new_value;
    new_node->next = NULL;

    if(*head == NULL) {
        *head = new_node;
        return;
    }

    while(last->next != NULL) last = last->next;

    last->next = new_node;
    return;
}

// Insert new value at the front of the list
void insertFront(Node **head, int new_value) {
    Node *new_node = new Node();
    new_node->data = new_value;
    new_node->next = *head;
    *head = new_node;
}

// Delete based on the value
void deleteNode_data(Node **head, int key) {
    Node *temp = *head, *prev;

    if(temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return; 
    }

    while(temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

// Delete node based on the position
void deleteNode_position(Node **head, int position) {
    if(*head == NULL) return;
    Node *temp = new Node();
    temp = *head;
    if(position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    for(int i=0; temp != NULL && i<position-1; i++) {
        temp = temp->next;
    }

    if(temp == NULL || temp->next == NULL) return;

    Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}


void printList(Node *head) {
    while(head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    Node *head = NULL;

    insertFront(&head, 1);
    insertFront(&head, 2);
    insertFront(&head, 3);

    deleteNode_data(&head, 2);
    deleteNode_position(&head, 1);

    
    printList(head);

    return 0;
}