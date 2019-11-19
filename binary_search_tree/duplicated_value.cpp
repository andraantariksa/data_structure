#include <iostream>

struct Node {
    int data;
    int count;
    Node *left, *right;
};

Node *newNode(int new_data) {
    Node *temp = new Node();
    temp->data = new_data;
    temp->left = temp->right = NULL;
    temp->count  = 1;
    return temp;
}

Node *insert(Node *root, int new_data) {
    if(root == NULL) return newNode(new_data);

    if(new_data == root->data) {
        root->count++;
        return root;
    }

    if(new_data < root->data) root->left = insert(root->left, new_data);
    else if(new_data > root->data) root->right = insert(root->right, new_data);

    return root;
}

Node *minValueNode(Node *root) {
    Node *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int data) {
    if(root == NULL) root;

    if(data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);

    else {
        if(root->count > 1) {
            root->count--;
            return root;
        }

        // Node with one child
        if(root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        Node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inOrder(Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        std::cout << root->data << "(" << root->count << ")" << std::endl;
        inOrder(root->right);
    }
}

void printTree(Node *tree, int depth = 0, int dir = 0) {
    if(tree) {
        printTree(tree->left, ++depth, 1);
        for(int i=10; i>depth; i--) std::cout << "          ";
        switch(dir) {
            case 1:
                std::cout << tree->data << "(" << tree->count << ")" << "\\" << std::endl;
                break;
            case 2:
                std::cout << tree->data << "(" << tree->count << ")" << "/" << std::endl;
                break;
            default:
                std::cout << tree->data << "(" << tree->count << ")" << std::endl;
                break;
        }
        printTree(tree->right, depth, 2);
    }
}

int main()
{
    Node *root = NULL;
    root = insert(root, 12); 
    root = insert(root, 10); 
    root = insert(root, 20); 
    root = insert(root, 9); 
    root = insert(root, 11); 
    root = insert(root, 10); 
    root = insert(root, 12); 
    root = insert(root, 12); 
  
    std::cout << "Inorder traversal of the given tree " 
         << std::endl; 
    inOrder(root); 

    printTree(root, 0, 0);
  
    std::cout << "\nDelete 20\n"; 
    root = deleteNode(root, 20); 
    std::cout << "Inorder traversal of the modified tree \n"; 
    inOrder(root); 

    printTree(root, 0, 0);
  
    std::cout << "\nDelete 12\n" ; 
    root = deleteNode(root, 12); 
    std::cout << "Inorder traversal of the modified tree \n"; 
    inOrder(root); 

    printTree(root, 0, 0);
  
    std::cout << "\nDelete 9\n"; 
    root = deleteNode(root, 9); 
    std::cout << "Inorder traversal of the modified tree \n"; 
    inOrder(root); 

    printTree(root, 0, 0);

    return 0;
}