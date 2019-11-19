#include <iostream>

using namespace std;

struct Node {
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
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->data << endl;
        inOrder(root->right);
    }
}

Node *insert(Node *root, int new_data) {
    if (root == NULL) return newNode(new_data);

    if(new_data < root->data) root->left = insert(root->left, new_data);
    else if(new_data > root->data) root->right = insert(root->right, new_data);

    return root;
}

void printTree(Node *root, int depth = 0, int dir = 0) {
    if(root) {
        printTree(root->left, ++depth, 1);
        for(int i=10; i>depth; i--) cout << "    ";
        switch(dir) {
            case 1:
                cout << root->data << "\\" << endl;
                break;
            case 2:
                cout << root->data << "/" << endl;
                break;
            default:
                cout << root->data << endl;
                break;
        }
        printTree(root->right, depth, 2);
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

    printTree(root, 0, 0);

   return 0;
}