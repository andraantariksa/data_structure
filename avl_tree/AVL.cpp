#if defined(_WIN32)
    #define PLATFORM_WINDOWS // Windows
#elif defined(_WIN64)
    #define PLATFORM_WINDOWS // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_WINDOWS // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__linux__)
    #define PLATFORM_LINUX // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#endif

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cmath>

enum color
{
    RED,
    GREEN,
    BLUE,
    DEFAULT
};

class Console {
    public:
    static std::string color(::color c)
    {
        #ifdef PLATFORM_WINDOWS
            // Windows color
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            switch (c)
            {
            case RED:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case GREEN:
                SetConsoleTextAttribute(hConsole, 10);
                break;
            case BLUE:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            default:
                FlushConsoleInputBuffer(hConsole);
                break;
            }
            return "";
        #endif
        #ifdef PLATFORM_LINUX
            // Linux color
            std::string color_code;
            switch (c)
            {
            case RED:
                color_code = "31";
                break;
            case GREEN:
                color_code = "32";
                break;
            case BLUE:
                color_code = "34";
                break;
            default:
                color_code = "39";
                break;
            }
            return "\033[" + color_code + "m";
        #endif
    }
};

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

class BTreePrinter {
    public:
    static void printNode(Node *root) {
        std::vector<Node*> nodes;
        nodes.push_back(root);
        printNodeInternal(nodes, 1, maxLevel(root));
    }

    static void printNodeInternal(std::vector<Node*> nodes, int level, int maxLevel) {
        if (nodes.empty() || isAllElementsNull(nodes))
            return;

        int floor = maxLevel - level;
        int edge_lines = (int) std::pow(2, (max(floor - 1, 0)));
        int firstSpaces = (int) std::pow(2, (floor)) - 1;
        int betweenSpaces = (int) std::pow(2, (floor + 1)) - 1;

        printWhitespaces(firstSpaces);

        std::vector<Node*> new_nodes;

        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] != NULL) {
                std::cout << nodes[i]->data;
                new_nodes.push_back(nodes[i]->left);
                new_nodes.push_back(nodes[i]->right);
            } else {
                new_nodes.push_back(NULL);
                new_nodes.push_back(NULL);
                std::cout << " ";
            }

            printWhitespaces(betweenSpaces);
        }

        std::cout << "\n";

        for (int i = 1; i <= edge_lines; i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                printWhitespaces(firstSpaces - i);
                if (nodes[j] == NULL)
                {
                    printWhitespaces(edge_lines * 2 + i + 1);
                    continue;
                }

                if (nodes[j]->left != NULL)
                {
                    std::cout << Console::color(color::RED) << "/" << Console::color(color::DEFAULT);
                }
                else
                {
                    printWhitespaces(1);
                }

                printWhitespaces(i * 2 - 1);

                if (nodes[j]->right != NULL)
                {
                    std::cout << Console::color(color::GREEN) << "\\" << Console::color(color::DEFAULT);
                }
                else
                {
                    printWhitespaces(1);
                }
                
                printWhitespaces(edge_lines * 2 - i);
            }
            std::cout << "\n";
        }

        printNodeInternal(new_nodes, level + 1, maxLevel);
    }

    static void printWhitespaces(int count) {
        for (int i = 0; i < count; i++)
            printf(" ");
    }

    static int maxLevel(Node *node) {
        if (node == NULL)
            return 0;
        return max(maxLevel(node->left), maxLevel(node->right)) + 1;
    }

    static bool isAllElementsNull(std::vector<Node*> list) {
        for(int i = 0; i < list.size(); i++) {
            if (list[i] != NULL)
                return false;
        }
        return true;
    }
};

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
                    // printTree(root, 0, 0);
                    BTreePrinter::printNode(root);
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

                // printTree(root, 0, 0);
                BTreePrinter::printNode(root);

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
