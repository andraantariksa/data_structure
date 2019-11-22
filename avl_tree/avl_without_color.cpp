#include <iostream>
#include <fstream>

struct Node {
    int data;
    Node *left, *right;
    int height;
};

int height(Node *treeNode) {
    if(treeNode == NULL) return 0;
    else return treeNode->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *newNode(int data) {
    Node *temp = new Node();
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->height = 1;
    
    return temp;
}

Node *rightRotate(Node *y){
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *treeNode) {
    if(treeNode == NULL) return 0;
    return height(treeNode->left) - height(treeNode->right);
}

Node *insert(Node *treeNode, int data){
    if(treeNode == NULL) return newNode(data);

    if(data < treeNode->data) treeNode->left = insert(treeNode->left, data);
    else if(data > treeNode->data) treeNode->right = insert(treeNode->right, data);

    treeNode->height = 1 + max(height(treeNode->left), height(treeNode->right)); // Get current Node Height

    int balance = getBalance(treeNode); // Get the balance factor

    if(balance > 1 && data < treeNode->left->data) return rightRotate(treeNode);
    if(balance < -1 && data > treeNode->right->data) return leftRotate(treeNode);
    if(balance > 1 && data > treeNode->left->data) {
        treeNode->left = leftRotate(treeNode->left);
        return rightRotate(treeNode);
    } 
    if(balance < -1 && data < treeNode->right->data) {
        treeNode->right = rightRotate(treeNode->right);
        return leftRotate(treeNode);
    }

    return treeNode;
}

void preOrder(Node *root)
{
    if(root)
    {
        std::cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void printTree(Node *root, int depth = 0, int dir = 0) {
    if(root) {
        printTree(root->left, ++depth, 1);
        for(int i=10; i>depth; i--) std::cout << "    ";
        switch(dir) {
            case 1:
                std::cout << root->data << "\\" << std::endl;
                break;
            case 2:
                std::cout << root->data << "/" << std::endl;
                break;
            default:
                std::cout << root->data << std::endl;
                break;
        }
        printTree(root->right, depth, 2);
    }
}


int main()
{
    int number, choice;
    char flag;
    std::string fileName;
    std::ifstream infile;
    int get_num;


    do {
        Node *root = NULL;
        std::cout << "******************************" << std::endl;
        std::cout << "1. Insert node to the tree" << std::endl;
        std::cout << "2. Insert node from file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cin >> choice;
        switch(choice) {
            case 1:
                while(true) {
                    std::cout << "Enter the node: ";
                    std::cin >> number;
                    root = insert(root, number);
                    printTree(root, 0, 0);
                    std::cout << "Continue (y/n)" << std::endl;
                    std::cin >> flag;
                    if(flag == 'N' || flag == 'n') break;
                }
                break;

            case 2:
                std::cout << "Please enter the file name: ";
                std::cin >> fileName;
                infile.open(fileName);
                if(!infile.is_open()) {
                    std::cout << "File failed to open" << std::endl;
                    return 0;
                }

                while(infile >> get_num) {
                    root = insert(root, get_num);
                }

                printTree(root, 0, 0);

                break;
            case 0:
                break;

            default:
                std::cout << "Wrong input" << std::endl;
        }
    }
    while (choice != 0);

    return 0;
}
