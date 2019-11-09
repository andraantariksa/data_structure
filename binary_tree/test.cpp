#include <iostream>
#include <string>

using namespace std;

/*
EXPRESSION TREE
In order Traversal = Postfix Expression
Pre-order Traversal = Prefix Expression

EVALUATING THE EXPRESSION REPRESENTED BY EXPRESSION TREE'S ALGORITHM:
Let t be the expression tree
If t != NULL
    if t.value == operand
        return t.value
    A = solve(t.left)
    B = solve(t.right)

    //calculate applies operator t.value
    //on A and B and returns value
    Return calculate(A,B,t.value)

CONSTRUCTION OF EXPRESSION TREE:
if character = OPERAND, PUSH to stack
if character = OPERATOR, POP two values from stack make them its child and PUSH current node again.
At the end only element of stack will be root of expression tree
*/
struct node{
    char data;
    node *left, *right;
};

struct STACK {
    char inf[99];
    node *tree[99];
    int Tos;
};

//proc create
// void Create(STACK *t) {
//     t->Tos = -1;
// }

// proc clear
void Clear(STACK *t) {
    t->Tos = -1;
}

//function empty
bool Empty(STACK *t) {
    return t->Tos == -1;
}

//function full
bool Full(STACK *t) {
    return t->Tos == (int)sizeof(t->tree)-1;
}

//proc PUSH
void PUSH(node *et, STACK *st, char data) {
    if (!Full(st)) {
        st->Tos+=1;
        st->inf[st->Tos] = data;
        st->tree[st->Tos] = et;
    }
    else {
        cout << "Error" << endl;
    }
}

void POP(STACK *st) {
    if(!Empty(st)) {
        st->Tos -= 1;
    }else {
        cout << "Pop Error" << endl;
    }
}

int precede(char chr){
    switch(chr){
    case '^':
        return 3;
        break;
    case '*':
    case '/':
        return 2;
        break;

    case '+':
    case '-':
        return 1;
        break;

    default:
        return 0;
    }
}

bool isPrcd(char symb1, char symb2){
    return precede(symb1) >= precede(symb2);
}

bool operandCheck(char op){
    return op != '*' && op != '/' && op != '+' && op != '-' && op != '^' && op != '(' && op != ')' && op != '=';
}


void preOrder(node *tree){
    if(tree){
        cout<<tree->data<< " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void inOrder(node *tree){
    if(tree){
        inOrder(tree->left);
        cout<<tree->data<< " ";
        inOrder(tree->right);
    }
}

void postOrder(node *tree){
    if(tree){
        postOrder(tree->left);
        postOrder(tree->right);
        cout<<tree->data<< " ";
    }
}

// #include <windows.h>   // WinApi header

// void printTree(node* p, int depth = 0, int dir = 0){
//     HANDLE  hConsole;
//     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     if (p){
//         printTree(p->left, ++depth, 1);
//         for (int i = 10; i > depth; i--) cout << "    ";
//         switch (dir){
//         case 1:
//             SetConsoleTextAttribute(hConsole, 11);
//             cout << p->data << "\\" << endl;
//             break;
//         case 2:
//             SetConsoleTextAttribute(hConsole, 14);
//             cout << p->data << "/" << endl;
//             break;
//         default:
//             SetConsoleTextAttribute(hConsole, 15);
//             cout << p->data << endl;
//             break;
//         }
//         SetConsoleTextAttribute(hConsole, 15);

//         printTree(p->right, depth, 2);
//     }
// }
/*
void printTree(node *tree, int dep = 0){
    if(tree){
        printTree(tree->left, dep+1);
        for (int i = 10; i > dep;i--)cout << "   ";
        cout << tree->data << endl;
        printTree(tree->right, dep+1);
    }
}
*/
node *createET(string input){
    STACK *stackET = new STACK();
    node *test;

    for (int i = 0; i < input.length(); i++){
        if (operandCheck(input[i])){
            test = new node();
            test->data = input[i];
            test->left = test->right = 0;
            PUSH(test, stackET, test->data);
        }else{
            test = new node();
            test->right = stackET->tree[stackET->Tos];
            test->left = stackET->tree[stackET->Tos-1];
            //cout << "currently at ; " << input[i] << ", with left child = " << test->left->data << ", right child = " << test->right->data << endl;
            POP(stackET);
            POP(stackET);
            test->data = input[i];
            PUSH(test, stackET, test->data);
        }
    }
    return test;
}

string removeSpace(string in){
    string out = "";
    for (int i = 0; i < in.length(); i++){
        if (in[i] != ' ') out += in[i];
    }
    return out;
}

string infix2suffix(string inp){
    string suffix= "", temp1 = "";
    STACK *infix = new STACK();
    Clear(infix);
    node *null = 0;
    for (int i = 0; i<inp.length();i++){
        if(operandCheck(inp[i])){
            suffix += inp[i];
        }else if(inp[i] == '('){
            PUSH(null, infix, inp[i]);
        }else if(inp[i] == ')'){
            while (infix->inf[infix->Tos] != '(' && !Empty(infix)){
                suffix += infix->inf[infix->Tos];
                POP(infix);
            }
            if(infix->inf[infix->Tos] == '(') POP(infix);
        }else{ //operator
            if (Empty(infix)){
                PUSH(null, infix, inp[i]);
            }else{
                while(isPrcd(infix->inf[infix->Tos], inp[i]) && !Empty(infix)){
                    suffix += infix->inf[infix->Tos];
                    POP(infix);
                }
                PUSH(null, infix, inp[i]);
            }
        }
    }

    while(!Empty(infix)){
        suffix += ' ';
        suffix += infix->inf[infix->Tos];
        POP(infix);
    }
    return removeSpace(suffix);
}


/*
CONSTRUCTION OF EXPRESSION TREE:
if character = OPERAND, PUSH to stack
if character = OPERATOR, POP two values from stack make them its child and PUSH current node again.
At the end only element of stack will be root of expression tree
*/

//((A+B) / (C-D)) * ((A+C) * E)
//* / + B A - C D * + A C E
int main(){
    string inp, postFix = "";
    node *root;
    cout<<"Put the infix expression: ";
    getline(cin,inp);
    postFix = infix2suffix(inp);
    cout<<"The Tree is: "<<endl;
    root = createET(postFix);
    // printTree(root,0,0);
    cout<<"Prefix: "<<endl;
    preOrder(root);
    cout<<endl<<"Postfix: "<<endl;
    postOrder(root);
    cout<<endl<<"Press any alphanumeric and enter keys to exit"<<endl;
return 0;
}
