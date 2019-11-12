#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// Node is used to make the treeNode
// Node has 2 pointers, left and right
// Node has data variable to store the data
class Node {
public:
    char data;
    Node *left, *right;
};

// When you created the instance of this class, there will be 2 stacks created
class Stack {
public:
    int tos;
    char inf[99]; // This stack is used for the infix to postfix conversion
    Node *tree[99]; // This stack is used for making the tree from treeNode
};

// Create new Stack and initialize the tos to -1
void create(Stack *st) {
    st->tos = -1;
}

// To check if the Stack is empty
bool isEmpty(Stack *st) {
    return st->tos == -1;
}

// To check if the Stack is full
bool isFull(Stack *st) {
    return st->tos == (int)sizeof(st->tree)-1;
}

// Adding new data to the Stack
void push(Node *treeNode, Stack *st, char data) {
    if(isFull(st)) {
        cout << "Stack Overflow" << endl;
    }
    else {
        st->tos++;
        st->inf[st->tos] = data;
        st->tree[st->tos] = treeNode;
    }
}

// Deleting data at the end of the stack
void pop(Stack *st) {
    if(isEmpty(st)) {
        cout << "Stack Underflow" << endl;
    }
    else {
        st->inf[st->tos] = 0;
        st->tree[st->tos] = 0;
        st->tos--;
    }
}

// Check the operator precedence
int precedence(char ch) {
    switch(ch) {
        case '^':
            return 3;
        case '*':
        case ':':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

// Check and compare the precedence between two operators
bool precedenceCheck(char ch1, char ch2) {
    return precedence(ch1) >= precedence(ch2);
}

// Check if the input is an operand or the operator
bool isOperand(char ch) {
    return (ch != '^') && (ch != '*') && (ch != '/') && (ch != '+') && (ch != '-') && (ch != '(') && (ch != ')') && (ch != '=');
}

// Used to find prefix expression
void preOrder(Node *tree) {
    if(tree) {
        cout << tree->data << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

// Used to find infix expression
void inOrder(Node *tree) {
    if(tree) {
        inOrder(tree->left);
        cout << tree->data << " ";
        inOrder(tree->right);
    }
}

// Used to find suffix/postfix expression
void postOrder(Node *tree) {
    if(tree) {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->data << " ";
    }
}

// Creating tree
Node *createTree(string input) {
    Stack *treeStack = new Stack(); // Creating an instance of stack class
    create(treeStack);  // Initialize the class and set the tos to -1
    Node *treeNode; // We will return this node

    for(int i=0; i<input.length(); i++) {
        if(isOperand(input[i])) { // Operand
            treeNode = new Node();
            treeNode->data = input[i];
            treeNode->left = treeNode->right = 0;
            push(treeNode, treeStack, treeNode->data);
        }
        else { // Operator
            treeNode = new Node();
            treeNode->data = input[i];
            treeNode->right = treeStack->tree[treeStack->tos];
            treeNode->left = treeStack->tree[treeStack->tos-1];
            pop(treeStack);
            pop(treeStack);
            push(treeNode, treeStack, treeNode->data);
        }
    }
    return treeNode;
}

// Removing any white spaces to make your expression looks tidy
string removeSpace(string in){
    string out = "";
    for (int i = 0; i < in.length(); i++){
        if (in[i] != ' ') out += in[i];
    }
    return out;
}

// Infix to suffix conversion function
string infixToSuffix(string input) {
    string suffix = "";
    Stack *infixStack  = new Stack();
    create(infixStack);
    Node *null = 0;

    for(int i=0; i<input.length(); i++) {
        if(isOperand(input[i])) {
            suffix += input[i];
        }
        else if(input[i] == '(') {
            push(null, infixStack, input[i]);
        }
        else if(input[i] == ')') {
            while(infixStack->inf[infixStack->tos] != '(' && !isEmpty(infixStack)) {
                suffix += infixStack->inf[infixStack->tos];
                pop(infixStack);
            }
            if(infixStack->inf[infixStack->tos] == '(') {
                pop(infixStack);
            }
        }
        else {
            if(isEmpty(infixStack)) {
                push(null, infixStack, input[i]);
            }
            else {
                while(precedenceCheck(infixStack->inf[infixStack->tos], input[i]) && !isEmpty(infixStack)) {
                    suffix += infixStack->inf[infixStack->tos];
                    pop(infixStack);
                }
                push(null, infixStack, input[i]);
            }
        }
    }

    while(!isEmpty(infixStack)) {
        suffix += infixStack->inf[infixStack->tos];
        pop(infixStack);
    }

    return removeSpace(suffix);
}

// Printing the tree
void printTree(Node* treeNode, int depth = 0, int dir = 0){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (treeNode){
        printTree(treeNode->left, ++depth, 1);
        for (int i = 10; i > depth; i--) cout << "    ";
        switch (dir){
        case 1:
            SetConsoleTextAttribute(hConsole, 9); // Left sub tree
            cout << treeNode->data << "\\" << endl;
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, 10); // Right sub tree
            cout << treeNode->data << "/" << endl;
            break;
        default:
            SetConsoleTextAttribute(hConsole, 14); // Root
            cout << treeNode->data << endl;
            break;
        }
        SetConsoleTextAttribute(hConsole, 15);

        printTree(treeNode->right, depth, 2);
    }
}

// Main Function
int main()
{
    string input, suffix, inputFiltered;   // Variable declaration
    Node *root;

    cout << "***Convert Infix to Prefix and Suffix using Binary Tree***\n" << endl;
    cout << "Enter the infix expression: "; // Input prompt
    getline(cin, input);
    for(int i = 0; i < input.length(); i++) // Removing white spaces
    {
        if (isspace(input[i])) continue;
        inputFiltered += input[i];
    }

    suffix = infixToSuffix(inputFiltered); // We have to convert to the suffix expression first

    cout<<"The Tree is: "<<endl;
    root = createTree(suffix);
    printTree(root,0,0);

    cout << endl << "Prefix: "; // Prefix expression
    preOrder(root);

    cout << endl << "Suffix: "; // Suffix expression
    postOrder(root);

    cout << endl << "press any key to exit" << endl;
    return 0;
}
