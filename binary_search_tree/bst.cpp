#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

Node *newNode(int new_data) {
    Node *temp = new Node();
    temp->data = new_data;
    temp->left = temp->right = NULL;
    return temp;
}

void inOrder(Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        cout << root->data << endl;
        inOrder(root->right);
    }
}

Node *insert(Node *node, int data) {
    if(node == NULL) return newNode(data);

    if(data < node->data) node->left = insert(node->left, data);
    else if(data > node->data) node->right = insert(node->right, data);

    return node;
}

void printTree(Node* treeNode, int depth = 0, int dir = 0){
    if (treeNode){
        printTree(treeNode->left, ++depth, 1);
        for (int i = 10; i > depth; i--) cout << "    ";
        switch (dir){
        case 1:
            cout << treeNode->data << "\\" << endl;
            break;
        case 2:
            cout << treeNode->data << "/" << endl;
            break;
        default:
            cout << treeNode->data << endl;
            break;
        }

        printTree(treeNode->right, depth, 2);
    }
}


int main()
{
    Node *root = NULL;
    root = insert(root, 50);
    
    insert(root, 30);
    insert(root, 20); 
    insert(root, 40); 
    insert(root, 70); 
    insert(root, 60); 
    insert(root, 80); 

    inOrder(root);

    printTree(root,0,0);

    return 0;
}